#include "vector.h"

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
