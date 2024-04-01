#pragma once
#include <Windows.h>
#include <DxLib.h>
#include "define.h"

class Initializer
{
public:
	static void DxLib();
	static void Image(int& BodyImage, int& HeadImage, int& EyeImage, int& MouthImage, int& MouthCloseImage);
};
