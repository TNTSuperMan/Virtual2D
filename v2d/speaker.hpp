#pragma once

#include "Windows.h"
#include "DxLib.h"
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <vector>
#include "vector.hpp"
#include "anilua.hpp"
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
	vct2d Loop();
};

extern string vpath;
extern VoiceData vd;
extern bool isNeedReload;
LRESULT CALLBACK SpeakerAddProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);