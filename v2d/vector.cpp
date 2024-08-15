#include "vector.hpp"
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


vct2d turn(double deg) {
	return vct2d(
		sin(deg * A_DEG),-cos(deg * A_DEG)
	);
}


vct2d TurnV(vct2d Cent, vct2d Str, double Deg) {
	vct2d t = vct2d();
	vct2d tf = turn(Deg);
	t = t + tf * Str.y;
	tf = turn(Deg + 90);
	t = t + tf * Str.x;
	return t + Cent;
}