#include "Sprite.h"

void Sprite::Draw() {
	vct2d rp = Pos;
	vct2d rc = vct2d(
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
	Pos = vct2d();
	Cent = vct2d();
	Size = 100;
	Deg = 0;
	ishanten = 0;
};

Sprite::Sprite(int i, vct2d p, vct2d c, double s,  int hanten) {
	Image = i;
	Pos = p;
	Cent = c;
	Size = s;
	Deg = 0;
	ishanten = hanten;
}