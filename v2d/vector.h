#pragma once

struct vector { //���W�R���g���[��
	double x = 0;
	double y = 0;
	vector operator +(vector v);
	vector operator -(vector v);
	vector operator *(double v);
	vector operator /(double v);
	vector(double ax, double ay);
	vector();
};
vector TurnV(vector Cent, vector Str, double Deg); //��]�������W