#include "vector.h"
#include "define.h"

vector::vector() {}

vector::vector(double ax, double ay) {
	x = ax;
	y = ay;
}

vector vector::operator+(vector v) {
	return vector(x + v.x, y + v.y);
}

vector vector::operator-(vector v) {
	return vector(x - v.x, y - v.y);
}

vector vector::operator*(double v) {
	return vector(x * v, y * v);
}


vector vector::operator/(double v) {
	return vector(x / v, y / v);
}

vector TurnV(vector Cent, vector Str, double Deg) {
	vector t = vector();
	vector tf = vector(
		sin(Deg * A_DEG),
		-cos(Deg * A_DEG));
	t = t + tf * Str.y;
	tf = vector(
		sin((Deg + 90) * A_DEG),
		-cos((Deg + 90) * A_DEG));
	t = t + tf * Str.x;
	return t + Cent;
}