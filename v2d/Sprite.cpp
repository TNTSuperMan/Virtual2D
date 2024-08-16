#include "sprite.hpp"

void Sprite::Draw() {
	DrawRotaGraph3(Pos.x , Pos.y,
		Cent.x + (double)sizex / 2, Cent.y + (double)sizey / 2,
		Size / 100 * Stren.x,
		Size / 100 * Stren.y,
		Deg * A_DEG,
		Image, 1, isFlip ? 1 : 0);
}

Sprite::Sprite() {
	Image = -1;
	Pos = vct2d();
	Cent = vct2d();
	Stren = vct2d(1,1);
	Size = 100;
	Deg = 0;
	isFlip = 0;
	sizex = 0;
	sizey = 0;
};

Sprite::Sprite(int i, vct2d p, vct2d c, double s,  int flip) {
	Image = i;
	Pos = p;
	Size = s;
	Cent = c;
	Stren = vct2d(1, 1);
	Deg = 0;
	isFlip = flip;
	GetGraphSize(i, &sizex, &sizey);
}