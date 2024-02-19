#include "include.h"


void Sprite::Draw() {
	vector rp = Pos;
	vector rc = vector(
			-cos(Deg * A_DEG - DX_PI / 2),
			-sin(Deg * A_DEG - DX_PI / 2));
	rp = rp + rc * Cent.x + rc * Cent.y;
	DrawRotaGraph(rp.x, rp.y,
		(double)Size / 100,
		Deg * A_DEG,
		Image, 1,ishanten ? 1 : 0);
}

Sprite::Sprite() {
	Image = -1;
	Pos = vector();
	Cent = vector();
	Size = 100;
	Deg = 0;
	ishanten = 0;
};

Sprite::Sprite(int i, vector p, vector c, double s,  int hanten) {
	Image = i;
	Pos = p;
	Cent = c;
	Size = s;
	Deg = 0;
	ishanten = hanten;
}