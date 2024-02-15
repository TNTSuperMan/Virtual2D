#pragma once

#include "DxLib.h"

struct Vector {
	double X;
	double Y;
	Vector();
	Vector(double x, double y);
	void Turn(double deg,Vector adv);
	VECTOR operator + (VECTOR v);
	VECTOR operator - (VECTOR v);
	VECTOR operator * (double v);
	VECTOR operator / (double v);
};