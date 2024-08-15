#pragma once
#include <Windows.h>
#include <DxLib.h>
#include "define.hpp"
#include "Dialog.hpp"

class Initializer
{
public:
	static void DxLib();
	static void Image(int& BodyImage, int& HeadImage, int& EyeImage, int& MouthImage, int& MouthCloseImage);
};
