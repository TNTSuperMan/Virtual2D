#include "include.h"


void Sprite::Draw() {
	vector rp = Pos;
	vector rc = vector(
			-cos(Rotate * A_DEG - DX_PI / 2),
			-sin(Rotate * A_DEG - DX_PI / 2));
	rp = rp + rc * Cent.x + rc * Cent.y;
	DrawRotaGraph(rp.x, rp.y,
		(double)Size / 100,
		Rotate * A_DEG,
		Image, 1,ishanten ? 1 : 0);
}

Sprite::Sprite() {};

Sprite::Sprite(int i,vector p, vector c, vector st, int s, double r,bool hanten) {
	Image = i;
	Pos = p;
	Cent = c;
	Stren = st;
	Size = s;
	Rotate = r;
	ishanten = hanten;
}