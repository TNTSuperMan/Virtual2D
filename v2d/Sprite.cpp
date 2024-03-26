#include "Sprite.h"

void Sprite::Draw() {
	DrawRotaGraph3(Pos.x , Pos.y,
		Cent.x + sizex / 2, Cent.y + sizey / 2,
		Size / 100 * Stren.x,
		Size / 100 * Stren.y,
		Deg * A_DEG,
		Image, 1,ishanten ? 1 : 0);
}

Sprite::Sprite() {
	Image = -1;
	Pos = vct2d();
	Cent = vct2d();
	Stren = vct2d(1,1);
	Size = 100;
	Deg = 0;
	ishanten = 0;
	sizex = 0;
	sizey = 0;
};

Sprite::Sprite(int i, vct2d p, vct2d c, double s,  int hanten) {
	Image = i;
	Pos = p;
	Size = s;
	Cent = c;
	Stren = vct2d(1, 1);
	Deg = 0;
	ishanten = hanten;
	int* sxp = new int;
	int* syp = new int;
	GetGraphSize(i, sxp, syp);
	sizex = *sxp;
	sizey = *syp;
}