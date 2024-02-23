#pragma once
#include <cmath>
#include "define.h"

struct vct2d { //座標コントロール
	double x = 0;
	double y = 0;
	vct2d operator +(vct2d v);
	vct2d operator -(vct2d v);
	vct2d operator *(double v);
	vct2d operator /(double v);
	vct2d(double ax, double ay);
	vct2d();
};
vct2d TurnV(vct2d Cent, vct2d Str, double Deg); //回転した座標