#include "include.h"


void Sprite::Draw() {
	vector rp = Pos;
	vector rc = vector(
			0 - cos((double)Rotate * A_DEG - DX_PI / 2),
			0 - sin((double)Rotate * A_DEG - DX_PI / 2));
	rp = rp + rc * Cent.x + rc * Cent.y;
	DrawRotaGraph(rp.x, rp.y,
		(double)Size / 100,
		Rotate * A_DEG,
		Image, 1);
}

Sprite::Sprite() {};

Sprite::Sprite(int i,vector p, vector c, vector st, int s, int r) {
	Image = i;
	Pos = p;
	Cent = c;
	Stren = st;
	Size = s;
	Rotate = r;
}