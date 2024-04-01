#pragma once

#include "Windows.h"
#include "DxLib.h"
#include "vector.h"
#include <iostream>
#include <nlohmann/json.hpp>
#include <vector>
using namespace std;

class VoiceData {
public:
	vector<int> waittime;
	vector<char> saydata;
	bool isplay;
	ULONG tick;
	ULONG waitsum;
	VoiceData();
	void Add(int wait, char say);
	void Start();
	vct2d Loop(bool& isclose);
};

extern string vpath;
extern VoiceData vd;
LRESULT CALLBACK SpeakerAddProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);