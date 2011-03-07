// Note: compile with "Multi-threaded (/MT)" instead of "Multi-threaded DLL (/MD)" since
// GetOpenFileName changes FS9 settings (current dir, etc.) unless linked a private/static
// CRT runtime that isn't shared (see http://www.themssforum.com/VC/GetOpenFileName-changes)

#define PAGE_EXPIRY_SECONDS 30
#define PAGE_MIN_ZOOM 0.3F
#define GRABBAR 16
#define TITLETIME 3
#define RECALLWINDOW "Window"

#define WIN32_LEAN_AND_MEAN

#ifndef _WIN32_WINNT        
#define _WIN32_WINNT 0x0501
#endif
#ifndef _WIN32_WINDOWS        
#define _WIN32_WINDOWS 0x0501
#endif

#include <windows.h>
#include <commctrl.h>
#include <Commdlg.h>
#include <stdarg.h>
#include <time.h>
#include <D3D9.h>

extern "C"
{
 #include <fitz.h>
 #include <mupdf.h>
}

#include "PDFView.h"

/**
 * our pdfview (global) status
 */
struct bitmap_s
{
	fz_rect box;
	int width;
	int height;
	int size;
	float zoom; // level the image was zoomed at
	int rotate; // applied rotation
	char* pdata;
	time_t timestamp;
};

struct page_s
{
	float centerx;
	float centery;
	float zoom;
	int rotate;

	bitmap_s bitmap;

	int mediawidth;
	int mediaheight;
	pdf_page* ppdfpage;
};

struct document_s
{
	bool locked;

	document_s* pprev;
	document_s* pnext;

	char file[MAX_PATH];
	char* pname;

	int page;

	int npages;
	page_s* ppages;

	pdf_xref* ppdfxref;
};

struct pdfview_s 
{
	CRITICAL_SECTION lock;
	HANDLE signal;
	HWND window;

	int width;
	int height;

	document_s* firstdoc;

	bool useHideWindow;

	int page_modifier;
	int zoom_modifier;
	int rotate_modifier;

#ifdef FITZ_HEAD
    fz_graphics* pfzGraphics;
#else
    fz_renderer* pfzRenderer;
#endif

	char title[80];
	char pagetitle[80];
	time_t titletime;

	bool (*dragProc)(int dx, int dy);

	HBRUSH hbCanvas;
	HBRUSH hbBackground;

    HCURSOR arrowcurs;
    HCURSOR handcurs;
    HCURSOR waitcurs;
	HCURSOR sizecurs;
	HCURSOR movecurs;

	HFONT titlefont;
	HBRUSH titlebrush;
	HPEN titlepen;
}
pdfview;

/**
 * forwards 
 */
void render(HWND hwnd);
LRESULT CALLBACK viewproc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
DWORD WINAPI worker_main(void*);
void wake_worker(int delay = 0);
void repaint(bool showTitle = false);
void kneeboard_log(char* message, ... );
bool fz_result_ok(fz_error error, char* message);
void drop_bitmap(bitmap_s* pbitmap);
void drop_document(document_s* pdoc);

/**
 * constructor
 */
HWND pdfview_init(HWND hParent, char* ptitle, char* ppagetitle)
{
	memset(&pdfview, 0, sizeof(pdfview));

	pdfview.hbCanvas = CreateSolidBrush(RGB(0x70,0x70,0x70));
	pdfview.hbBackground = CreateSolidBrush(RGB(0xff,0xff,0xff));

	pdfview.useHideWindow = pdfview_recall("pdfview", "usehidewindow", 0.0) != NULL;
	if (pdfview.useHideWindow)
		kneeboard_log("init:will use HideWindow() for turning off kneeboard");

    pdfview.arrowcurs = LoadCursor(NULL, IDC_ARROW);
    pdfview.handcurs = LoadCursor(NULL, IDC_HAND);
    pdfview.waitcurs = LoadCursor(NULL, IDC_WAIT);
	pdfview.sizecurs = LoadCursor(NULL, IDC_SIZENWSE);
	pdfview.movecurs = LoadCursor(NULL, IDC_SIZEALL);
	pdfview.dragProc = NULL;

	pdfview.titlefont = CreateFont(
	  32,               // height of font
	  0,                // average character width
	  0,			    // angle of escapement
	  0,                // base-line orientation angle
	  FW_HEAVY,              // font weight
	  FALSE,            // italic attribute option
	  FALSE,            // underline attribute option
	  FALSE,            // strikeout attribute option
	  ANSI_CHARSET,     // character set identifier
	  OUT_DEFAULT_PRECIS,  // output precision
	  CLIP_DEFAULT_PRECIS, // clipping precision
	  ANTIALIASED_QUALITY, // output quality
	  VARIABLE_PITCH,   // pitch and family
	  "Verdana"          // typeface name
	);
	pdfview.titlepen = CreatePen(PS_SOLID, 1, RGB(0,0,0));
	pdfview.titlebrush = CreateSolidBrush(RGB(0xff,0xff,0xff));



	pdfview.page_modifier = 0;
	pdfview.zoom_modifier = MK_CONTROL;
	pdfview.rotate_modifier = MK_SHIFT;

	strcpy_s(pdfview.title, sizeof(pdfview.title), ptitle);
	strcpy_s(pdfview.pagetitle, sizeof(pdfview.pagetitle), ppagetitle);

	// window
    WNDCLASS wc;
	wc.style = CS_HREDRAW | CS_VREDRAW ;
    wc.lpfnWndProc = viewproc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = GetModuleHandle(NULL);
    wc.hIcon = NULL;
    wc.hCursor = NULL;
    wc.hbrBackground = NULL;
    wc.lpszMenuName = NULL;
    wc.lpszClassName = "pdfview";
    ATOM atom = RegisterClass(&wc);

    pdfview.window = CreateWindowEx(
		0,
		"pdfview", NULL, 
		WS_POPUP,
	    256, 256, 640, 400,
	    hParent, 0, 0, 0);


    SetCursor(pdfview.arrowcurs);

	// background task synchronization
	pdfview.signal = CreateEvent(NULL, false, false, NULL);
	InitializeCriticalSection(&pdfview.lock);

	// create a background thread
	CreateThread(NULL, 0, worker_main, NULL, 0, NULL);

	// init fitz
    fz_cpudetect();
    fz_accelerate();

	// create a new fitz renderer
	fz_result_ok(fz_newrenderer(&pdfview.pfzRenderer, pdf_devicergb, 0, 1024 * 512), "init:fz_newrenderer");

	// done
	return pdfview.window;
}


/**
 * show hide pdfview
 */
void pdfview_show() {

	// restore to known boundaries
	RECT r;
	r.left = 256;
	r.top = 256;
	r.right = 480;
	r.bottom = 480;
	pdfview_recall(RECALLWINDOW, &r);

	SetWindowPos(pdfview.window, NULL,
		r.left,r.top,r.right-r.left,r.bottom-r.top,
		(GetParent(pdfview.window)!=NULL ? SWP_NOACTIVATE : 0) |SWP_NOZORDER|SWP_SHOWWINDOW);

}

void pdfview_hide() {

	// we allow fallback to 'standard' way of hiding our child window
	// by default we're placing the window out of sight as that doesn't
	// lead to the observed behaviour of FS freezing for up to 5 secs
	// when in fullscreen mode
	if (pdfview.useHideWindow)
	{
	
		ShowWindow(pdfview.window, SW_HIDE);

	} else {

		// place window out of sight
		RECT r;

		HWND desktop = GetDesktopWindow();
		GetWindowRect(desktop, &r);

		r.left = r.right-1;
		r.top  = r.bottom-1;
		SetWindowPos(pdfview.window, NULL,
			r.left,r.top,r.right-r.left,r.bottom-r.top,
			SWP_NOACTIVATE|SWP_NOZORDER);

	}

	// stop any ongoing interactions
	pdfview.dragProc = NULL;

}

bool pdfview_visible() {
	if (!IsWindowVisible(pdfview.window))
		return false;
	RECT r;
	GetWindowRect(pdfview.window, &r);
	return (r.right-r.left)>1 && (r.bottom-r.top)>1;
//	return IsWindowVisible(pdfview.window) != FALSE;
}

void toggle_pdfview() {
	if (pdfview_visible())
		pdfview_hide();
	else
		pdfview_show();
}

bool fz_result_ok(fz_error error, char* message) 
{
	if (fz_okay!=error) 
	{
		kneeboard_log("%s:fitz error:%d", message, error);
	}
	return fz_okay==error;
}

/**
 * calculate whether rotation is landscape
 */
bool is_landscape(int rotation)
{
	return abs( (rotation)%180 )>0;
}

void lock() {
	EnterCriticalSection(&pdfview.lock);
}

void unlock() {
	LeaveCriticalSection(&pdfview.lock);
}

/**
 * current document
 */
int count_documents() 
{
	lock();

	int result = 0;
	document_s* pcursor = pdfview.firstdoc;
	while (pcursor!=NULL) {
		result++;
		pcursor = pcursor->pnext;
	}

	unlock();

	return result;
}

document_s* current_document() 
{
	return pdfview.firstdoc;
}

/**
 * navigate between documents
 */
void prev_document() 
{
	if (!pdfview_visible())
		return;

	lock();

	// find first
	document_s* pfirst = pdfview.firstdoc;
	if (pfirst!=NULL) {

		// find last
		document_s* plast = pfirst;
		while (plast->pnext!=NULL)
			plast = plast->pnext;

		if (plast!=pfirst) {

			// detach last
			plast->pprev->pnext = NULL;
			plast->pprev = NULL;

			// make last first
			plast->pnext = pfirst;
			pfirst->pprev = plast;
			pdfview.firstdoc = plast;
		}

	}

	unlock();

	// done
	repaint(true);
}

void next_document() 
{
	if (!pdfview_visible())
		return;

	lock();

	// find first
	document_s* pfirst = pdfview.firstdoc;
	if (pfirst!=NULL) {

		// find last
		document_s* plast = pfirst;
		while (plast->pnext!=NULL)
			plast = plast->pnext;

		if (plast!=pfirst) {

			// make 2nd first
			pdfview.firstdoc = pfirst->pnext;
			pfirst->pnext->pprev = NULL;

			// make first last
			pfirst->pprev = plast;
			pfirst->pnext = NULL;
			plast->pnext = pfirst;
		}

	}

	unlock();

	// done
	repaint(true);
}

/**
 * save document attributes
 */
static void remember(char* pdocname, int page, char* key, float value)
{
	char buf[10];
	sprintf_s(buf, sizeof(buf), "%d.%s", page, key);
	pdfview_remember(pdocname, buf, value);
}

static void remember_document(document_s* pdoc) 
{
	if (pdoc->npages==0)
		return;

	pdfview_remember(pdoc->pname, "p", (float)pdoc->page+1);

	for (int i=1, j=pdoc->npages; i<=j ; i++)
	{
		page_s* ppage = &pdoc->ppages[i-1];
		// non default center, zoom, rotate?
		if (ppage->centerx!=0.5)
			remember(pdoc->pname, i, "cx", ppage->centerx);
		if (ppage->centery!=0.5)
			remember(pdoc->pname, i, "cy", ppage->centery);
		if (ppage->zoom > 0)
			remember(pdoc->pname, i, "z", ppage->zoom);
		if (ppage->rotate!=0) 
		{
			float rotate = (float)ppage->rotate;
			remember(pdoc->pname, i, "r", rotate);
		}
	}
}

#define LIMIT(x,lower,upper) x = max(lower, min(upper, x))


float restore(char* pdocname, int page, char* key, float fallback)
{
	char buf[10];
	sprintf_s(buf, sizeof(buf), "%d.%s", page, key);
	return pdfview_recall(pdocname, buf, fallback);
}
static void restore_document(document_s* pdoc, int pages)
{
	pdoc->page = (int)pdfview_recall(pdoc->pname, "p", 1) - 1; 
	LIMIT(pdoc->page, 0, pages-1);

	for (int i=1; i<=pages ; i++)
	{
		page_s* ppage = &pdoc->ppages[i-1];

		// defaults
		ppage->centerx = 0.5;
		ppage->centery = 0.5;
		ppage->rotate = 0;
		ppage->zoom = -1.0; // unset

		// load saved
		restore(pdoc->pname, i, "cx", ppage->centerx);
		restore(pdoc->pname, i, "cy", ppage->centery);
		restore(pdoc->pname, i, "z", ppage->zoom);
		ppage->rotate = ((int)(restore(pdoc->pname, i, "r", 0)/90.0))*90;

		// verify
		LIMIT(ppage->centerx, 0, 1);
		LIMIT(ppage->centery, 0, 1);
		LIMIT(ppage->rotate , 0, 360);
		if (ppage->zoom<=0)
			ppage->zoom = -1.0;
		else
			LIMIT(ppage->zoom   , PAGE_MIN_ZOOM, 10);

	}
}

/**
 * close document
 */
bool close_document(document_s* pdoc) {

	lock();

	// unlink
	if (pdoc->pprev!=NULL) 
		pdoc->pprev->pnext = pdoc->pnext;
	else
		pdfview.firstdoc = pdoc->pnext;

	if (pdoc->pnext!=NULL)
		pdoc->pnext->pprev = pdoc->pprev;

	pdoc->pnext = NULL;
	pdoc->pprev = NULL;

	// persist current settings
	remember_document(pdoc);

	// expire allocations unlock locked
	if (!pdoc->locked)
		drop_document(pdoc);

	// show
	repaint(true);

	// done
	unlock();

	return true;
}

void close_document() {

	// this has to work regardless of visible or not to not get into endless loop in close_all
	lock();
	if (current_document()!=NULL)
		close_document(current_document());
	unlock();
}

void close_all_documents() {
	lock();
	while (current_document()!=NULL) {
		close_document(current_document()); // doesn't ignore our request anymore
	}
	unlock();
}


/**
 * open document
 */
void open_document(const char* file) {

	lock();

	// check existing docs
	document_s* pdoc = pdfview.firstdoc;
	while (pdoc!=NULL)
	{
		// already open
		if (strcmp(file, pdoc->file)==0) {
			kneeboard_log("ui:ignoring open for %s - switching to appropriate document", file);
			while (current_document()!=pdoc)
				next_document();
			unlock();
			return;
		}

		// next
		pdoc = pdoc->pnext;
	}

	// open
	kneeboard_log("ui:creating new document for %s", file);

	// create new object
	pdoc = (document_s*)malloc(sizeof(document_s));

	memset(pdoc, 0, sizeof(document_s));

	pdoc->locked = false;
	strcpy_s(pdoc->file, MAX_PATH, file);

	pdoc->pname = strrchr(pdoc->file, '\\');
	if (pdoc->pname==NULL) pdoc->pname = pdoc->file;
	else pdoc->pname++;

	// link up
	if (pdfview.firstdoc!=NULL) {
		pdfview.firstdoc->pprev = pdoc;
		pdoc->pnext = pdfview.firstdoc;
	}
	pdfview.firstdoc=pdoc;

	// done
	unlock();

	// show if not there
	pdfview_show();

	// show with title
	repaint(true);
}

void open_document() {

	char file[MAX_PATH];
	file[0] = '\0';

	char filter[] = "PDF File\0*.pdf\0\0";

	OPENFILENAME open;
	memset(&open, 0, sizeof(open));
	open.lStructSize = OPENFILENAME_SIZE_VERSION_400; //sizeof(open);
	open.hwndOwner = GetParent(pdfview.window)!=NULL ? GetParent(pdfview.window) : pdfview.window;
	open.lpstrFilter = filter;
	open.nFilterIndex = 1;
	open.lpstrFile = file;
	open.nMaxFile = sizeof(file);
	open.lpstrInitialDir = NULL;
	open.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
	if (GetOpenFileName(&open))
		open_document(open.lpstrFile);


}

/**
 * current page
 */
page_s* current_page() {

	page_s* result = NULL;

	lock();
	document_s* firstdoc = current_document();	
	if (firstdoc!=nil&&firstdoc->ppages!=NULL)
		result = &firstdoc->ppages[firstdoc->page];
	unlock();

	return result;
}

//HBITMAP CreateBitmapMask(HBITMAP hBitmap)
//{
//    // Create monochrome (1 bit) mask bitmap.  
//    BITMAP bm;
//    GetObject(hBitmap, sizeof(BITMAP), &bm);
//    HBITMAP hbmMask = CreateBitmap(bm.bmWidth, bm.bmHeight, 1, 1, NULL);
//
//    // Get HDC that is compatible with the display driver
//    HDC hdcBitmap = CreateCompatibleDC(0);
//    HDC hdcMask = CreateCompatibleDC(0);
//    SelectObject(hdcBitmap, hBitmap);
//    SelectObject(hdcMask, hbmMask);
//
//	SetBkColor(hdcBitmap, RGB(0, 0, 0));
//
//    // Copy the bits from the colour image to the B+W mask... everything
//    // with the background colour ends up white while everythig else ends up
//    // black...Just what we wanted.
//    BitBlt(hdcMask, 0, 0, bm.bmWidth, bm.bmHeight, hdcBitmap, 0, 0, SRCCOPY);
//
//    // Clean up.
//    DeleteDC(hdcBitmap);
//    DeleteDC(hdcMask);
//
//    return hbmMask;
//}

/**
 * render watersign
 */
void render_watersign(HDC hdc)
{
	document_s* pdoc = current_document();

	// only for 5 secs if we got a doc
	if (pdoc!=NULL)
	{
		time_t now;
		time(&now);
		if (now-pdfview.titletime>TITLETIME)
			return;
		// schedule clean-up
		SetTimer(pdfview.window, WM_PAINT, (int)(TITLETIME-(now-pdfview.titletime))*1000+100, NULL);
	}

	// assemble text
	char buf[256];

	if (current_page()!=NULL)
		sprintf_s(buf, sizeof(buf), pdfview.pagetitle, pdoc->pname, pdoc->page+1, pdoc->npages);
	else
		sprintf_s(buf, sizeof(buf), pdfview.title);

	// stroke title
	SelectObject(hdc, pdfview.titlefont);
	SetBkMode(hdc, TRANSPARENT);
	SelectObject(hdc, pdfview.titlepen);
	SelectObject(hdc, pdfview.titlebrush);
	BeginPath(hdc);
	RECT r;
	r.top = 0; r.left = 0; r.right = pdfview.width; r.bottom = pdfview.height;
	DrawText(hdc, buf, (int)strlen(buf), &r, DT_TOP|DT_LEFT|DT_SINGLELINE);
	EndPath(hdc);

	StrokeAndFillPath(hdc);

	// done
}

/**
 * render canvas/background
 */
void render_background(HDC hdc) 
{

	TRIVERTEX        vert[2] ;
	vert [0] .x      = 0;
	vert [0] .y      = 0;
	vert [0] .Red    = 0xff00;
	vert [0] .Green  = 0xff00;
	vert [0] .Blue   = 0xff00;
	vert [0] .Alpha  = 0x0000;
	vert [1] .x      = pdfview.width;
	vert [1] .y      = pdfview.height; 
	vert [1] .Red    = 0xc000;
	vert [1] .Green  = 0xc000;
	vert [1] .Blue   = 0xc000;
	vert [1] .Alpha  = 0x0000;

	GRADIENT_RECT    gRect;
	gRect.UpperLeft  = 0;
	gRect.LowerRight = 1;

	// intersect with a rounded rectang;e
	//HRGN outline = CreateRoundRectRgn(0,0,pdfview.width,pdfview.height, 20, 20);
	//ExtSelectClipRgn(hdc, outline, RGN_AND);
	//DeleteObject(outline);

	// calculate position
	int w = 0, h = 0;
	page_s* ppage = current_page();
	if (ppage!=NULL) 
	{
		w = (int)(ppage->mediawidth * abs(ppage->zoom));
		h = (int)(ppage->mediaheight* abs(ppage->zoom));
		if (is_landscape(ppage->rotate)) {
			int t=w; w=h; h=t;
		}
	}

	int x1 = pdfview.width/2 - w/2;
	int x2 = x1 + w;
	int y1 = pdfview.height/2 - h/2;
	int y2 = y1 + h;

	int save = SaveDC(hdc);
	if (x2>x1&&y2>y1)
		ExcludeClipRect(hdc,x1,y1,x2,y2);
	GradientFill(hdc,vert,2,&gRect,1,GRADIENT_FILL_RECT_V);

	// paint an image
	//HBITMAP hbitmap = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(2), IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR|LR_LOADTRANSPARENT);
	//HBITMAP hmask = CreateBitmapMask(hbitmap);
	//BITMAP bitmap;
	//GetObject(hbitmap, sizeof(bitmap), &bitmap);
	//HDC hdcBitmap = CreateCompatibleDC(hdc);
	//HGDIOBJ hbmOld = SelectObject(hdcBitmap, hmask);
	//BitBlt(hdc, 0, 0, bitmap.bmWidth, bitmap.bmHeight, hdcBitmap, 0, 0, SRCAND);
	//SelectObject(hdcBitmap, hbitmap);
	//BitBlt(hdc, 0, 0, bitmap.bmWidth, bitmap.bmHeight, hdcBitmap, 0, 0, SRCPAINT);
	//SelectObject(hdcBitmap, hbmOld);
	//DeleteDC(hdcBitmap);
	//DeleteObject(hbitmap);

	// restore and draw text or border
	RestoreDC(hdc, save);

	if (ppage!=NULL && (x2>x1) && (y2>y1) )
	{
		HPEN border = CreatePen(PS_SOLID, 1, RGB(0,0,0));
		HPEN shadow = CreatePen(PS_SOLID, 4, RGB(0x80,0x80,0x80));
		SelectObject(hdc, shadow);
		MoveToEx(hdc, x2+4, y1+2, NULL);
		LineTo(hdc,x2+4,y2+4);
		LineTo(hdc,x1+2,y2+4);
		SelectObject(hdc, border);
		MoveToEx(hdc, x1-1, y1-1, NULL);
		LineTo(hdc,x2+1,y1-1);
		LineTo(hdc,x2+1,y2+1);
		LineTo(hdc,x1-1,y2+1);
		LineTo(hdc,x1-1,y1-1);
		DeleteObject(border);
		DeleteObject(shadow);
	}

	// done
}

/**
 * render pdf - assuming mutex is owned already 
 */
void render_page(HDC hdc) 
{
	lock();

	page_s* ppage = current_page();
	if (ppage==nil) {
		wake_worker();
		return unlock();
	}

	// what to render
	int rotate = ppage->rotate;
	float zoom = abs(ppage->zoom);
	int w = (int)(ppage->mediawidth *zoom);
	int h = (int)(ppage->mediaheight*zoom);
	if (is_landscape(rotate))  {
		int t=w; w=h; h=t;
	}
	int x = w>pdfview.width ? min(0,max(pdfview.width-w,pdfview.width/2-(int)(w*ppage->centerx))) : pdfview.width/2 - w/2;
	int y = h>pdfview.height ? min(0,max(pdfview.height-h,pdfview.height/2-(int)(h*ppage->centery))) : pdfview.height/2 - h/2;

//	fz_rect box;
//	box.x0 = x>0 ? 0 : -x;
//	box.y0 = y>0 ? 0 : -y;
//	box.x1 = x+w<pdfview.width ? ppage->mediawidth : ;
	

	// no suitable bitmap at all to work with?
	if (ppage->bitmap.size==0 || rotate!=ppage->bitmap.rotate) {
		// clear background 
		RECT r;
		r.left = x; r.right = x+w;
		r.top = y; r.bottom = y+h;
	    FillRect(hdc, &r, pdfview.hbBackground);
		// need worker to validate
		wake_worker(ppage->bitmap.size==0 ? 0 : 250);
		return unlock();
	}

	// render bitmap
	BITMAPINFO dibinf;
	dibinf.bmiHeader.biSize = sizeof(dibinf);
	dibinf.bmiHeader.biPlanes = 1;
	dibinf.bmiHeader.biBitCount = 24;
	dibinf.bmiHeader.biCompression = BI_RGB;
	dibinf.bmiHeader.biXPelsPerMeter = 2834/2;
	dibinf.bmiHeader.biYPelsPerMeter = 2834/2;
	dibinf.bmiHeader.biClrUsed = 0;
	dibinf.bmiHeader.biClrImportant = 0;
	dibinf.bmiHeader.biClrUsed = 0;
	dibinf.bmiHeader.biWidth = ppage->bitmap.width;
	dibinf.bmiHeader.biHeight = -ppage->bitmap.height;
	dibinf.bmiHeader.biSizeImage = ppage->bitmap.size;

	// zoomed image?
	if (zoom!=ppage->bitmap.zoom) {

		StretchDIBits(
		  hdc,                     // handle to DC
		  x,                       // x-coord of destination upper-left corner
		  y,                       // y-coord of destination upper-left corner
		  w,                     // width of destination rectangle
		  h,                     // height of destination rectangle
		  0,                       // x-coord of source upper-left corner
		  0,                       // y-coord of source upper-left corner
		  ppage->bitmap.width, // width of source rectangle
		  ppage->bitmap.height,// height of source rectangle
		  ppage->bitmap.pdata,  // bitmap bits
		  &dibinf,                 // bitmap pdata
		  DIB_RGB_COLORS,          // usage options
		  SRCCOPY                  // raster operation code
		);

		// need worker to validate (delayed)
		wake_worker(250);
		return unlock();
	}

	// original
	SetDIBitsToDevice(
		hdc,
		x, /* destx */
		y, /* desty */
		ppage->bitmap.width, /* destw */
		ppage->bitmap.height, /* desth */
		0, /* srcx */
		0, /* srcy */
		0, /* startscan */
		ppage->bitmap.height, /* numscans */
		ppage->bitmap.pdata, /* pBits */
		&dibinf, /* pInfo */
		DIB_RGB_COLORS /* color use flag */
	 );

	// done
	unlock();
}

void render(HWND hwnd) 
{
	kneeboard_log("ui:render");

	lock();

	// prepare
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hwnd, &ps);

	// background
	render_background(hdc);

	// page
	render_page(hdc);

	// watersign
	render_watersign(hdc);

	// done
	EndPaint(hwnd, &ps);

	unlock();
}

/**
 * changes rotation for current page
 */
void rotate_clockwise() {
	current_page()->rotate += 90;
	kneeboard_log("ui:clockwise");
	repaint();
}

void rotate_counterclockwise() {
	current_page()->rotate -= 90;
	kneeboard_log("ui:counter-clockwise");
	repaint();
}


/**
 * flip page
 */
void goto_page(int page)
{
	lock();

	document_s* pdoc = current_document();
	if (pdoc!=NULL && page>=0 && page<pdoc->npages) {

		kneeboard_log("ui:goto page %d", page);

		int old = pdoc->page;
		pdoc->page = page;

		// transfer zoom
		if (pdoc->ppages[pdoc->page].zoom <=0)
			pdoc->ppages[pdoc->page].zoom = -abs(pdoc->ppages[old].zoom);

	}

	// show
	repaint(true);

	unlock();
}

void next_page() 
{
	lock();
	document_s* pdoc = current_document();
	if (pdoc!=NULL&&(pdoc->page<pdoc->npages-1))
		goto_page(pdoc->page+1);
	unlock();
}

void prev_page() {
	lock();
	document_s* pdoc = current_document();
	if (pdoc!=NULL&&(pdoc->page>0))
		goto_page(pdoc->page-1);
	unlock();
}

/**
 * change meaning of modfiers for wheel actions
 */
void set_wheel_modifiers(int vkpage, int vkzoom, int vkrotate) {
	pdfview.page_modifier = vkpage;
	pdfview.zoom_modifier = vkzoom;
	pdfview.rotate_modifier = vkrotate;
}

/**
 * zoom in/out
 */
void zoom_in() {

	lock();

	page_s* ppage = current_page();
	if (ppage!=NULL)
	{
		ppage->zoom = abs(ppage->zoom) + 0.25F;
		kneeboard_log("ui:zoom to %f", ppage->zoom);
		repaint();
	}

	unlock();
}

void zoom_out() 
{
	lock();
	page_s* ppage = current_page();
	if (ppage!=NULL)
	{
		ppage->zoom = max(PAGE_MIN_ZOOM, abs(ppage->zoom) - 0.25F);
		kneeboard_log("ui:zoom to %f", ppage->zoom);
		repaint();
	}
	unlock();
}

void zoom_100() 
{
	lock();
	page_s* ppage = current_page();
	if (ppage!=NULL)
	{
		ppage->zoom = 1.0F;
		kneeboard_log("ui:zoom to 100%%");
		repaint();
	}
	unlock();
}



/**
 * move page content
 */
void move_page(float centerx, float centery) {
	lock();
	page_s* ppage = current_page();
	ppage->centerx = centerx;
	ppage->centery = centery; 
	kneeboard_log("center %f/%f", centerx, centery); 
	unlock();
	pdfview.titletime = 0;
	repaint();
}

bool move_page_by(int deltax, int deltay) {
	page_s* ppage = current_page();
	if (ppage!=NULL)
		move_page(max(0, min(1, ppage->centerx - deltax / abs(ppage->zoom) / ppage->mediawidth)), max(0, min(1, ppage->centery - deltay / abs(ppage->zoom) / ppage->mediaheight )));
	return true;
}

/**
 * move window
 */
bool size_window_by(int deltax, int deltay)
{
	pdfview.titletime = 0;
	RECT r;
	GetWindowRect(pdfview.window, &r);
	SetWindowPos(pdfview.window, NULL, 0, 0, max(GRABBAR*4, r.right-r.left+deltax), max(GRABBAR*4, r.bottom-r.top+deltay), SWP_NOMOVE|SWP_NOZORDER|SWP_NOACTIVATE);
	return true;
}

bool move_window_by(int deltax, int deltay)
{
	pdfview.titletime = 0;
	RECT r;
	GetWindowRect(pdfview.window, &r);
	SetWindowPos(pdfview.window, NULL, r.left+deltax, r.top+deltay, 0, 0, SWP_NOSIZE|SWP_NOZORDER|SWP_NOACTIVATE);
	return false;
}

/**
 * Our main window event handler
 */
LRESULT CALLBACK viewproc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// visible?
	if (!pdfview_visible())
	    return DefWindowProc(hwnd, message, wParam, lParam);

	// mouse operations status
    static int startx = 0;
    static int starty = 0;
	int x = (signed short) LOWORD(lParam);
	int y = (signed short) HIWORD(lParam);

	// analyze msg
    switch (message)
	{	
		case WM_TIMER:
			if (wParam==WM_PAINT) {
				KillTimer(hwnd, WM_PAINT);
				repaint();
			}
			break;
		case WM_SIZE:
			if (wParam != SIZE_MINIMIZED) {
				pdfview.width = LOWORD(lParam);
				pdfview.height = HIWORD(lParam);
			}
			break;
	    case WM_PAINT: 
			render(hwnd);
			break;
		case WM_LBUTTONDOWN:
			startx = x;
			starty = y;
			if (x>pdfview.width-GRABBAR&&y>pdfview.height-GRABBAR)
			{
				pdfview.dragProc = &size_window_by;
				SetCapture(hwnd);
				SetCursor(pdfview.sizecurs);
				break;
			}
			if (y<GRABBAR)
			{
				pdfview.dragProc = &move_window_by;
				SetCapture(hwnd);
				SetCursor(pdfview.movecurs);
				break;
			}
			if (current_page()!=NULL)
			{
				pdfview.dragProc = &move_page_by;
				SetCapture(hwnd);
				SetCursor(pdfview.handcurs);
			}
			break;
		case WM_LBUTTONUP:
			pdfview.dragProc = NULL;
			ReleaseCapture();
			SetCursor(pdfview.arrowcurs);

			// remember current window position
			RECT r;
			GetWindowRect(pdfview.window, &r);
			pdfview_remember(RECALLWINDOW, &r);
			// restore active window
			if (GetParent(pdfview.window)!=NULL)
				SetActiveWindow(GetParent(pdfview.window));
			break;
		case WM_MOUSEMOVE:
			// already dragging ?
			if (pdfview.dragProc)
			{
				if (pdfview.dragProc(x-startx, y-starty))
				{
					startx = x;
					starty = y;
				}
				break;
			} 
			// prep for resizing
			if (x>pdfview.width-GRABBAR&&y>pdfview.height-GRABBAR)
			{
				SetCursor(pdfview.sizecurs);
				break;
			}
			// prep for titlebar
			if (y<GRABBAR)
			{
				if (GetCursor()!=pdfview.movecurs)
				{
					SetCursor(pdfview.movecurs);
					repaint(true);
				}
				break;
			}
			SetCursor(pdfview.arrowcurs);
			break;
		case WM_MOUSEWHEEL:
			int modifier = GET_KEYSTATE_WPARAM(wParam)&(MK_CONTROL|MK_SHIFT);
			// rotate?
			if (modifier==pdfview.rotate_modifier) 
			{
				if (current_page()!=NULL) {
					if (GET_WHEEL_DELTA_WPARAM(wParam)<0)
						rotate_clockwise();
					else
						rotate_counterclockwise();
				}
				break;
			}
			// zoom?
			if (modifier==pdfview.zoom_modifier) 
			{
				if (GET_WHEEL_DELTA_WPARAM(wParam) > 0)
					zoom_in();
				else
					zoom_out();
				break;
			}
			// page up/down?
			if (modifier==pdfview.page_modifier) 
			{
				if (current_page()!=NULL) 
				{
					if (GET_WHEEL_DELTA_WPARAM(wParam) < 0)
						next_page();
					else 
						prev_page();
				}
			}
			break;
	}

    /* Pass on unhandled events to Windows */
    return DefWindowProc(hwnd, message, wParam, lParam);
} 

/**
 * repaint view
 */
void repaint(bool showTitle) {
	RedrawWindow(pdfview.window, NULL, NULL, RDW_INVALIDATE);
	if (showTitle)
		time(&pdfview.titletime);
}

/**
 * wake worker
 */
void CALLBACK wake_worker(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime) {
	KillTimer(hwnd, idEvent);
	wake_worker(0);
}

void wake_worker(int delay) {
	if (delay==0) {
		kneeboard_log("ui:signal_worker");
		SetEvent(pdfview.signal);
	} else {
		kneeboard_log("ui:schedule_worker");
		SetTimer(pdfview.window, 25051970, 500, &wake_worker);
	}
}

/**
 * pdf validation (reading/transformation)
 */
void drop_bitmap(bitmap_s* pbitmap) {
	if (pbitmap->pdata==NULL)
		return;
	kneeboard_log("worker:dropping image");
	lock();
	fz_free(pbitmap->pdata);
	pbitmap->pdata = NULL;
	pbitmap->size = 0;
	unlock();
}

void render_page(fz_pixmap* pfzpixmap, page_s* ppage, int rotate, float zoom)
{
	// allocate and render
    int bmpstride = ((pfzpixmap->w * 3 + 3) / 4) * 4;
	int bmpsize = pfzpixmap->h * bmpstride;
	char* bmpbuf = (char*)fz_malloc(bmpsize);
	if (!bmpbuf)  
	{
		kneeboard_log("worker:couldn't allocate %d bytes for image", pfzpixmap->h * bmpstride);
	}
	else 
	{

		for (int y = 0; y < pfzpixmap->h; y++)
		{
			char *p = bmpbuf + y * bmpstride;
			unsigned char *s = pfzpixmap->samples + y * pfzpixmap->w * 4;
			for (int x = 0; x < pfzpixmap->w; x++)
			{
				p[x * 3 + 0] = s[x * 4 + 3];
				p[x * 3 + 1] = s[x * 4 + 2];
				p[x * 3 + 2] = s[x * 4 + 1];
			}
		}

		// commit result
		lock();
		ppage->bitmap.size = 0;
		if (ppage->bitmap.pdata!=NULL) 
			fz_free(ppage->bitmap.pdata);
		ppage->bitmap.width = pfzpixmap->w;
		ppage->bitmap.height = pfzpixmap->h;
		ppage->bitmap.pdata = bmpbuf;
		ppage->bitmap.size = bmpsize;
		ppage->bitmap.zoom = zoom;
		ppage->bitmap.rotate = rotate;
		time(&ppage->bitmap.timestamp);
		unlock();
	}

	// done
}

/**
 * drop document
 */
void drop_document(document_s* pdoc) 
{
	lock();

	kneeboard_log("ui:dropping document %s", pdoc->pname);

	for (int p=0;p<pdoc->npages;p++) 
	{
		if (pdoc->ppages[p].bitmap.pdata!=NULL)
			free(pdoc->ppages[p].bitmap.pdata);
		if (pdoc->ppages[p].ppdfpage!=NULL)
		{
			pdf_droppage(pdoc->ppages[p].ppdfpage);
			pdoc->ppages[p].ppdfpage = NULL;
		}
	}

	if (pdoc->ppdfxref!=NULL)
	{
		pdf_closexref(pdoc->ppdfxref);
	}

	free(pdoc);

	unlock();
}

/**
 * render current document's current page as required
 */
void worker_render(document_s* pdoc) {

	kneeboard_log("worker:validating %s", pdoc->file);

	// lazi xref load
	if (pdoc->ppdfxref==NULL) {

		kneeboard_log("worker:load xrefs");

		fz_result_ok(pdf_newxref(&pdoc->ppdfxref), "worker:pdf_newxref");
		if (!fz_result_ok(pdf_loadxref(pdoc->ppdfxref, pdoc->file), "worker:pdf_load_xref")) {
			if (!fz_result_ok(pdf_repairxreft(pdoc->ppdfxref, pdoc->file), "worker:pdf_repairxreft")) {
				MessageBox(pdfview.window, pdoc->file, "Couldn't open PDF file", MB_OK|MB_ICONERROR);
				close_document(pdoc);
				return;
			}
		}

		// decrypt
		fz_result_ok(pdf_decryptxref(pdoc->ppdfxref), "worker:pdf_decryptxref");
		if (pdf_needspassword(pdoc->ppdfxref)) {
			int okay = pdf_authenticatepassword(pdoc->ppdfxref, "");
			if (okay)
				kneeboard_log("worker:pdf_needspassword");
		}

		// prepare pages
		int npages = 0;
		fz_result_ok(pdf_getpagecount(pdoc->ppdfxref, &npages), "worker:pdf_getpagecount");
		kneeboard_log("worker:loaded %d pages", npages);

		// commit pages
		lock();
		pdoc->npages = npages;
		pdoc->ppages = (page_s*)malloc(sizeof(page_s) * npages);
		memset(pdoc->ppages, 0, sizeof(page_s) * npages);
		restore_document(pdoc, npages);
		unlock();

	}

	// lazy load page
	int pageno = pdoc->page;
	page_s* ppage = &pdoc->ppages[pageno];
	if (ppage->ppdfpage==NULL)
	{
		kneeboard_log("worker:loading page %d", pageno);

		// load page
		fz_obj* page;
		fz_result_ok(pdf_getpageobject(pdoc->ppdfxref, pageno+1, &page), "worker:pdf_getpageobject");
		fz_result_ok(pdf_loadpage(&ppage->ppdfpage, pdoc->ppdfxref, page), "pdf__loadpage");
		if (ppage->ppdfpage==NULL)
			return;

		// commit
		lock();
		ppage->mediawidth  = (int)(ppage->ppdfpage->mediabox.x1 - ppage->ppdfpage->mediabox.x0);
		ppage->mediaheight = (int)(ppage->ppdfpage->mediabox.y1 - ppage->ppdfpage->mediabox.y0);
		unlock();

		// signal repaint so the outline can be shown
		repaint();
	}

	// lazy render page
	if (ppage->bitmap.pdata==NULL
		||ppage->bitmap.zoom!=abs(ppage->zoom)
		||ppage->bitmap.rotate!=ppage->rotate)
	{
		// render page into image
		kneeboard_log("worker:rendering page %d", pageno);

		float zoom = abs(ppage->zoom);
		int rotate = ppage->rotate;
		fz_rect box;
		memcpy(&box, &ppage->ppdfpage->mediabox, sizeof(fz_rect));

//		box.w = pdfview.width;
//		box.h = pdfview.height;

		// prepare a matrix with
		// + 0,0 at top left corner (inverting pdf coords)
		// + zoomed
		// + rotated
		fz_matrix matrix = fz_identity();
		matrix = fz_concat(matrix, fz_translate(0, -box.y1));
		matrix = fz_concat(matrix, fz_scale(zoom, -zoom));
		if (rotate!=0)
			matrix = fz_concat(matrix, fz_rotate((float)rotate));


		fz_pixmap* pfzpixmap;
		box = fz_transformaabb(matrix, box);

		// commmit
		if (fz_result_ok(fz_rendertree(&pfzpixmap, pdfview.pfzRenderer, ppage->ppdfpage->tree, matrix, fz_roundrect(box), 1), "fz_rendertree")) {
			render_page(pfzpixmap, ppage, rotate, zoom);
			fz_droppixmap(pfzpixmap);
		}
	}

	// signal repaint
	repaint();
}

void worker_expire() {

	// check expiry
	time_t expiry;
	time(&expiry);
	expiry -= PAGE_EXPIRY_SECONDS;

	// something we can work on?
	lock();

	document_s* pdoc = pdfview.firstdoc;
	while (pdoc!=NULL)
	{
		for (int i=0;i<pdoc->npages;i++) 
		{
			// never expire current page
			if (i==pdoc->page)
				continue;

			// check other pages
			page_s* ppage = &pdoc->ppages[i];
			if (ppage->bitmap.pdata!=nil && ppage->bitmap.timestamp<expiry)
			{
				kneeboard_log("worker:page %d has expired", i+1);
				drop_bitmap(&ppage->bitmap);
			}
		}

		// next
		pdoc = pdoc->pnext;
	}

	unlock();
	// done
}

DWORD WINAPI worker_main(void*) {

	kneeboard_log("worker:starting");
	while (true) {

		// wait for signal
		WaitForSingleObject(pdfview.signal, INFINITE);
		kneeboard_log("worker:triggered");

		// lock current document if avail
		lock();
		document_s* pdoc = current_document();
		if (pdoc!=NULL) 
			pdoc->locked = true;
		unlock();

		if (pdoc==NULL)
			continue;

		// let worker lazily render what needs to
		worker_render(pdoc);

		// unlock and check if meanwhile closed
		lock();
		pdoc->locked = false;
		if (pdfview.firstdoc!=pdoc && pdoc->pprev==NULL && pdoc->pnext==NULL)
			drop_document(pdoc);
		unlock();

		// drop old images
		worker_expire();

	}

	kneeboard_log("worker:terminating");

	return 0;
}

