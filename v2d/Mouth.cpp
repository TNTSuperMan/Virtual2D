#include "DxLib.h"
#include "vector.h"
#include "Mouth.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);


BOOL Mouth::RegisterApp(const char* windowID, WNDPROC windowProc) {
		WNDCLASSEXA wc;
		wc.cbSize = sizeof(WNDCLASSEXA);
		wc.style = CS_HREDRAW | CS_VREDRAW;
		wc.lpfnWndProc = windowProc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = GetModuleHandleA(NULL);
		wc.hIcon = (HICON)LoadIconA(NULL, IDI_APPLICATION);
		wc.hCursor = (HCURSOR)LoadCursorA(NULL, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
		wc.lpszMenuName = NULL;
		wc.lpszClassName = windowID;
		wc.hIconSm = (HICON)LoadImageA(NULL, IDI_APPLICATION, IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_SHARED);
		return (RegisterClassExA(&wc));
	}

Mouth::Mouth(HINSTANCE hci) {
		if (!RegisterApp(APP_ID, &WndProc)) return;

		wind = CreateWindow(
			APP_ID, "”­º - Virtual2D",
			WS_OVERLAPPEDWINDOW,
			0, 0, 300, 300,
			NULL, NULL, hci, NULL);

		saytick = -1;
		end = false;
		ShowWindow(wind, SW_SHOW);
		UpdateWindow(wind);
	}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
	switch (msg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_CREATE:
		Mouth::btn = CreateWindow(
			"BUTTON",
			"”­º",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			0, 40, 100, 30,
			hWnd, (HMENU)1, ((LPCREATESTRUCT)(lp))->hInstance, NULL);
		Mouth::btn = CreateWindow(
			"BUTTON",
			"”­º",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			0, 40, 100, 30,
			hWnd, (HMENU)1, ((LPCREATESTRUCT)(lp))->hInstance, NULL);
	}
	return DefWindowProcA(hWnd, msg, wp, lp);
}
