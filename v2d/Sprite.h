#pragma once
#include <DxLib.h>
#include <cmath>
#include "vector.h"
#include "define.h"
#include "vector.h"


class Sprite
{
private:
	int sizex;
	int sizey;
public:
	bool ishanten;
	int Image; //�摜�@����DxLib�̃n���h��
	vct2d Pos; //���W
	vct2d Cent; //���S���W
	vct2d Stren; //�L��
	double Size; //�傫���@100���
	double Deg; //��]�@360�x�ň��]���
	void Draw();
	Sprite();
	Sprite(int i,vct2d p, vct2d c, double s, int hanten = 0);
};