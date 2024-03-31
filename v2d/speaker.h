#pragma once

#include "Windows.h"
#include "DxLib.h"
#include "vector.h"
#include <iostream>
#include <vector>
using namespace std;

class VoiceData {
private:
	vector<int> waittime;
	vector<char> saydata;
	bool isstart;
	ULONG tick;
public:
	VoiceData();
	void Add(int wait, char say);
	void Start();
	vct2d Loop();
};

extern string vpath;
extern VoiceData vd;
LRESULT CALLBACK SpeakerAddProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);