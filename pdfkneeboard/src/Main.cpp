#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

#include "PDFView.h"

char ini[MAX_PATH];

/**
 * our logging
 */
void kneeboard_log(char* message, ... ) 
{
	va_list parms;
	va_start(parms, message);
	char buf[4096];
	vsprintf_s(buf, sizeof(buf), message, parms);
	va_end(parms);
	strcat_s(buf, sizeof(buf), "\r\n"); 
	OutputDebugString(buf); 
}

/**
 * key stuff
 */
bool check_pressed(int vk) {
	return (GetKeyState(vk)&0x8000) != 0;
}

/**
 * persist/restore page attrs
 */
float pdfview_recall(char* doc, char* key, float fallback)
{
	char buf[16];
	GetPrivateProfileString(doc, key, "", buf, sizeof(buf), ini);
	double result = strtod(buf, NULL);
	return result == 0 ? fallback : (float)result;
}

void pdfview_remember(char* doc, char* key, float value)
{
	kneeboard_log("Remembering %s/%s=%f", doc, key, value);

	char buf[16+1];
	sprintf_s(buf, sizeof(buf), "%.2f", value);
	WritePrivateProfileString(doc, key, buf, ini);
}

void pdfview_remember(char* key, RECT* r)
{
	kneeboard_log("Remembering %s, [%d,%d]x[%d,%d]", key, r->left, r->top, r->right, r->bottom);

	char value[256];
	sprintf_s(value, sizeof(value), "%d,%d,%d,%d", r->left, r->top,  r->right-r->left, r->bottom-r->top);
	WritePrivateProfileString("pdfkneeboard", key, value, ini);
}

bool pdfview_recall(char* key, RECT* r)
{
	char value[256];
	GetPrivateProfileString("pdfkneeboard", key, "", value, sizeof(value), ini);
	if (strlen(value)==0)
		return false;


	char* p = value;
	r->left = strtol(p, &p, 10);
	r->top = strtol(++p, &p, 10);
	r->right = strtol(++p, &p, 10);
	r->right += r->left;
	r->bottom = strtol(++p, &p, 10);
	r->bottom += r->top;

	// done
	return true;
}

/**
 * Main
 */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pargs, int nCmdShow)
{
	// initialize kneeboard
	HWND hwnd = pdfview_init(NULL, "PDFView by Nils Meier", "%s (%d/%d) - PDFView");

	// determine ini file
	ExpandEnvironmentStrings("%USERPROFILE%", ini, sizeof(ini));
	strcat_s(ini, sizeof(ini), "\\pdfkneeboard.ini");
	kneeboard_log("Ini file is %s", ini);

	// show it
	pdfview_show();

	// load files?
	if (strlen(pargs)>0) {
		open_document(pargs);
	}

	// handle events
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
		// normal msg loop magic
		TranslateMessage(&msg);

		// we're interested in it?
		if (msg.message==WM_KEYDOWN) {

			// ctrl tab = previous doc
			if (msg.wParam == VK_TAB) {
				if (check_pressed(VK_SHIFT))
					prev_document();
				else
					next_document();
			}

			// ctrl o = open doc
			if (check_pressed(VK_CONTROL) && msg.wParam=='O') 
				open_document();

			// ctrl w = close doc
			if (check_pressed(VK_CONTROL) && msg.wParam=='W')
				close_document();

			// ctrl x = exit
			if (check_pressed(VK_CONTROL) && msg.wParam=='X') {
				close_all_documents();
				break;
			}

		}

		// dispatch
		DispatchMessage(&msg);
    }

	// done
	return 0;
}
