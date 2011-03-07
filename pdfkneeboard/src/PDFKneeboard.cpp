
#include <windows.h>
#include <stdio.h>
#include <commctrl.h>

#include "FSCUtil.h"
#include "FSCUtil.h"
#include "FSCJoy.h"

#include "PDFView.h"


#define INI_KEY_ENABLED "Enabled"
#define INI_KEY_CTRLZOOM "CtrlWheelZooms"
#define INI_KEY_CTRLPAGE "CtrlPage"

/**
 * our kneeboard (global) status
 */
struct action_s {
	char name[32];
	int button;
	bool is_toggle;
	int hotkey;
	void (*action)();
};

static action_s actions[] = { 
	{ "Toggle kneeboard"   , 0xffff, true , 0x004b, toggle_pdfview     }, // k
	{ "Open document"      , 0xffff, true , 0x024f, open_document      }, // ctrl+o
	{ "Close document"     , 0xffff, true , 0x0257, close_document     }, // ctrl+w
	{ "Close all documents", 0xffff, true , 0x0357, close_all_documents}, // ctrl+shift+w
	{ "Next document"      , 0xffff, true , 0x0209, next_document  }, // ctrl+tab
	{ "Previous document"  , 0xffff, true , 0x0309, prev_document  }, // ctrl+shift+tab
	{ "Next page"          , 0xffff, true , 0x0822, next_page      }, // page down
	{ "Previous page"      , 0xffff, true , 0x0821, prev_page      }, // page up
	{ "Zoom In"            , 0xffff, false, 0x02bb, zoom_in        }, // ctrl+=
	{ "Zoom Out"           , 0xffff, false, 0x02bd, zoom_out       }, // ctrl+-
	{ "Zoom 100%"          , 0xffff, true , 0x0230, zoom_100       }, // ctrl+0
	{ NULL,0,0,NULL }
};

struct kneeboard_s
{
	bool enabled;

	HWND hwndSim;
	HWND hwndKneeboard;
	HMODULE hdll;

	bool enableCtrlPage;
	int gotoPage;
} kneeboard;

/** close pdfview (before module unload) */
void kneeboard_close()
{
	FSC_Log("closing kneeboard");

	// close all docs
	close_all_documents();

	// done
	pdfview_hide();
}

/** keypress handler */
bool check_pressed(int vk) { return (GetKeyState(vk)&0x8000) != 0; }
bool kneeboard_keyup(UWORD key)
{
	// control key? commit/end goto page
	if (key==VK_CONTROL)
	{
		if (kneeboard.gotoPage>0)
			goto_page(kneeboard.gotoPage-1);
		kneeboard.gotoPage = -1;
	}

	// not handled
	return false;
}
bool kneeboard_keydown(UWORD key)
{

	// disabled?
	if (!kneeboard.enabled) 
		return false;

	// goto page - start w/control key - add digit - cancel?
	if (!kneeboard.enableCtrlPage || !pdfview_visible())
		kneeboard.gotoPage = -1;
	else 
	{
		if (key==VK_CONTROL)
		{
			if (kneeboard.gotoPage<0)
				kneeboard.gotoPage = 0;
		} else {
			int digit = key-48;
			if (digit<0 || digit>9)
			{
				kneeboard.gotoPage = -1;
			} else {
				kneeboard.gotoPage = kneeboard.gotoPage*10 + digit;
				// handled
				return true;
			}
		}
	}
	// look through actions
	for (int i=0; actions[i].action!=NULL; i++)
	{
		// mod+vk check
		unsigned char mod = HIBYTE(actions[i].hotkey);
		if (( (mod&HOTKEYF_CONTROL) == (check_pressed(VK_CONTROL)?HOTKEYF_CONTROL:0) ) &&
			( (mod&HOTKEYF_SHIFT  ) == (check_pressed(VK_SHIFT  )?HOTKEYF_SHIFT  :0) ) &&
			(LOBYTE(actions[i].hotkey)==key))
		{
			// we handle it
			actions[i].action();
			return true;
		}

		// aside from first action all others require visible
		if (!pdfview_visible())
			break;
	}

	// not handled
	return false;
}

/** timer handler */
void kneeboard_timer()
{
	// check joysticks
	FSC_PollJoysticks();

	// not for me?
	if (!kneeboard.enabled) 
		return;

	// look through actions
	for (int i=0; actions[i].action!=NULL; i++)
	{
		int btn = actions[i].button;
		if (btn!=FSC_NO_BUTTON && FSC_TestButton(btn, actions[i].is_toggle))
		{
			actions[i].action();
			break;
		}

		// aside from first action all others require visible
		if (!pdfview_visible())
			break;
	}
}

/**
 * persist/restore page attrs
 */
float pdfview_recall(char* section, char* key, float fallback)
{
	return (float)FSC_ReadDoubleFromProfile(section, key, fallback);
}

void pdfview_remember(char* section, char* key, float value)
{
	FSC_WriteDoubleToProfile(section, key, (double)value);
}

void pdfview_remember(char* section, RECT* r)
{
	FSC_WriteRectToProfile(section, r);
}

bool pdfview_recall(char* section, RECT* r)
{
	return FSC_ReadRectFromProfile(section, r);
}

/** initialization */
void kneeboard_init(HWND hFlightSimWindow, HMODULE hModule)
{
	// reset state
	memset(&kneeboard, 0, sizeof(kneeboard));
	kneeboard.hwndSim = hFlightSimWindow;
	kneeboard.hwndKneeboard = pdfview_init(hFlightSimWindow, "PDFKneeboard by Nils Meier", "%s (%d/%d) - PDFKneeboard");
	kneeboard.hdll = hModule;
	kneeboard.gotoPage = -1;

	// read settings and assignments
	kneeboard.enabled = FSC_ReadBoolFromProfile(INI_KEY_ENABLED, true);

	if (FSC_ReadBoolFromProfile(INI_KEY_CTRLZOOM, true))
		set_wheel_modifiers(0, MK_CONTROL, MK_SHIFT);
	else
		set_wheel_modifiers(MK_CONTROL, 0, MK_SHIFT);


	for (int i=0; actions[i].action!=NULL ; i++) 
	{
		char buf[256];
		sprintf_s(buf, sizeof(buf), "%s.button", actions[i].name);
		actions[i].button = FSC_ReadHexFromProfile(buf, actions[i].button);
		sprintf_s(buf, sizeof(buf), "%s.hotkey", actions[i].name);
		actions[i].hotkey = FSC_ReadHexFromProfile(buf, actions[i].hotkey);
	}

	kneeboard.enableCtrlPage = FSC_ReadBoolFromProfile(INI_KEY_CTRLPAGE, false);

	// done
}

/**
 * Settings dialog
 */
#define IDD_CLOSE 1
#define IDD_CTRLISZOOM 21
#define IDD_CTRLISPAGE 22
#define IDD_ACTION_SELECT 31
#define IDD_BUTTON_SELECT 33
#define IDD_KEY_SELECT 35
#define IDD_CTRLPAGE 41

INT_PTR CALLBACK SettingsDialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static boolean ignore = false;

	// init dialog state
	if (uMsg==WM_INITDIALOG) 
	{
		// option for mouse wheel modifiers
		if (FSC_ReadBoolFromProfile(INI_KEY_CTRLZOOM, true))
			SendDlgItemMessage(hwndDlg, IDD_CTRLISZOOM, BM_CLICK, 0, 0); 
		else
			SendDlgItemMessage(hwndDlg, IDD_CTRLISPAGE, BM_CLICK, 0, 0); 


		// setup actions for keyboard/joystick bindings
		for (int i=0;actions[i].action!=NULL;i++) 
			SendDlgItemMessage(hwndDlg, IDD_ACTION_SELECT, CB_ADDSTRING, 0, (LPARAM)actions[i].name);
		SendDlgItemMessage(hwndDlg, IDD_ACTION_SELECT, CB_SETCURSEL, 0, 0);
		PostMessage(hwndDlg, WM_COMMAND, MAKEWPARAM(IDD_ACTION_SELECT,CBN_SELCHANGE), 0);

		// setup hotkey rules
		SendDlgItemMessage(hwndDlg, IDD_KEY_SELECT, HKM_SETRULES, HKCOMB_A, HOTKEYF_CONTROL);

		// other options
		if (kneeboard.enableCtrlPage)
			SendDlgItemMessage(hwndDlg, IDD_CTRLPAGE, BM_CLICK, 0, 0);

		// create a timer for our polling needs
		SetTimer(hwndDlg, 0, 1000/20, NULL);

		// proceed with generation
		return TRUE;
	}

	// we're focussed in button selector?
	if (GetFocus()==GetDlgItem(hwndDlg, IDD_BUTTON_SELECT)) 
	{
		// joystick button press?
		if (uMsg==WM_TIMER) {

			FSC_PollJoysticks();

			int btn = FSC_TestAnyButton();
			if (btn!=FSC_NO_BUTTON) 
			{
				int i = SendDlgItemMessage(hwndDlg, IDD_ACTION_SELECT, CB_GETCURSEL, 0, 0);
				actions[i].button = btn;

				char buf[256];
				sprintf_s(buf, sizeof(buf), "%s.button", actions[i].name);
				FSC_WriteHexToProfile(buf, btn);

				FSC_Log("Switching button for %s to %x",  actions[i].name, btn);

				PostMessage(hwndDlg, WM_COMMAND, MAKEWPARAM(IDD_ACTION_SELECT,CBN_SELCHANGE), 0);
			}
		}

		// check for user text-change to button text
		if (uMsg==WM_COMMAND && HIWORD(wParam)==EN_CHANGE && LOWORD(wParam)==IDD_BUTTON_SELECT && !ignore) {
			int i = SendDlgItemMessage(hwndDlg, IDD_ACTION_SELECT, CB_GETCURSEL, 0, 0);
			actions[i].button = FSC_NO_BUTTON;
			FSC_Log("Deleting button assignment for %s",  actions[i].name);
			PostMessage(hwndDlg, WM_COMMAND, MAKEWPARAM(IDD_ACTION_SELECT,CBN_SELCHANGE), 0);
			return TRUE;
		}
	}

	// stuff happening to our widgets?
	if (uMsg==WM_COMMAND) {

		int idd = LOWORD(wParam);
		int note = HIWORD(wParam);

		// ctrl mode switch?
		if (idd==IDD_CTRLISZOOM) 
		{
			set_wheel_modifiers(0, MK_CONTROL, MK_SHIFT);
			FSC_WriteBoolToProfile(INI_KEY_CTRLZOOM, true);
		}
		if (idd==IDD_CTRLISPAGE)
		{
			set_wheel_modifiers(MK_CONTROL, 0, MK_SHIFT);
			FSC_WriteBoolToProfile(INI_KEY_CTRLZOOM, false);
		}

		// action selection changed?
		if (idd==IDD_ACTION_SELECT&&note==CBN_SELCHANGE)
		{
			ignore = true;
			int i = SendDlgItemMessage(hwndDlg, IDD_ACTION_SELECT, CB_GETCURSEL, 0, 0); 
			char buf[256];
			strcpy_s(buf, sizeof(buf), "None");
			FSC_Button2Name(buf, sizeof(buf), actions[i].button);
			SendDlgItemMessage(hwndDlg, IDD_BUTTON_SELECT, WM_SETTEXT, 0, (LPARAM)&buf); 
			SendDlgItemMessage(hwndDlg, IDD_KEY_SELECT   , HKM_SETHOTKEY, actions[i].hotkey, 0); 
			ignore = false;
		}

		// hotkey changed?
		if (idd==IDD_KEY_SELECT && note==EN_CHANGE)
		{
			int hotkey = SendDlgItemMessage(hwndDlg, IDD_KEY_SELECT, HKM_GETHOTKEY, 0, 0);
			int i = SendDlgItemMessage(hwndDlg, IDD_ACTION_SELECT, CB_GETCURSEL, 0, 0);

			if (LOBYTE(hotkey)==VK_CAPITAL) 
				hotkey = MAKEWORD(VK_TAB, HIBYTE(hotkey));
			actions[i].hotkey = hotkey;

			char buf[256];
			sprintf_s(buf, sizeof(buf), "%s.hotkey", actions[i].name);
			FSC_WriteHexToProfile(buf, hotkey);

			FSC_Log("Switching hotkey for %s to %x",  actions[i].name, hotkey);

			PostMessage(hwndDlg, WM_COMMAND, MAKEWPARAM(IDD_ACTION_SELECT,CBN_SELCHANGE), 0);
		}

		// options
		if (idd==IDD_CTRLPAGE)
		{
			kneeboard.enableCtrlPage = BST_CHECKED ==IsDlgButtonChecked(hwndDlg, IDD_CTRLPAGE);
			FSC_WriteBoolToProfile(INI_KEY_CTRLPAGE, kneeboard.enableCtrlPage);
		}

		// done with dialog?
		if (idd==IDD_CLOSE) 
		{
			EndDialog(hwndDlg, IDD_CLOSE);
		}
	}


	// done here
	return FALSE;
}

void kneeboard_settings()
{
	bool restore = pdfview_visible();
	pdfview_hide();
	DialogBox(kneeboard.hdll, MAKEINTRESOURCE(1), kneeboard.hwndSim, SettingsDialogProc);
	if (restore)
		pdfview_show();
}


/**
 * module logging wrapper
 */
void kneeboard_log(char* message, ... ) {
	va_list parms;
	va_start(parms, message);
	FSC_LogVA(message, parms);
	va_end(parms);
}

