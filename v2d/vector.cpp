#include "vector.h"


vct2d::vct2d() {}

vct2d::vct2d(double ax, double ay) {
	x = ax;
	y = ay;
}

vct2d vct2d::operator+(vct2d v) {
	return vct2d(x + v.x, y + v.y);
}

vct2d vct2d::operator-(vct2d v) {
	return vct2d(x - v.x, y - v.y);
}

vct2d vct2d::operator*(double v) {
	return vct2d(x * v, y * v);
}


vct2d vct2d::operator/(double v) {
	return vct2d(x / v, y / v);
}

vct2d TurnV(vct2d Cent, vct2d Str, double Deg) {
	vct2d t = vct2d();
	vct2d tf = vct2d(
		sin(Deg * A_DEG),
		-cos(Deg * A_DEG));
	t = t + tf * Str.y;
	tf = vct2d(
		sin((Deg + 90) * A_DEG),
		-cos((Deg + 90) * A_DEG));
	t = t + tf * Str.x;
	return t + Cent;
}