#pragma once
#include "vector.h"
#include "Windows.h"
#include <future>
#define APP_ID "Virutal2D-Voice-Window_by-TNTSuperMan"


LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);

class Mouth {
public:
	static HWND wind;
	static HWND btn;
	static HWND inp;
	static long saytick;
	static bool end;
	static vct2d* mouthvect;
	static int* mouthtick;
	Mouth(HINSTANCE hci);
	BOOL RegisterApp(const char* windowID, WNDPROC windowProc);
	static std::thread ef;
};