#pragma once

struct vector { //座標コントロール
	double x = 0;
	double y = 0;
	vector operator +(vector v);
	vector operator -(vector v);
	vector operator *(double v);
	vector operator /(double v);
	vector(double ax, double ay);
	vector();
};
vector TurnV(vector Cent, vector Str, double Deg); //回転した座標