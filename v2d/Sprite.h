#pragma once
#include <DxLib.h>
#include <cmath>
#include "vector.h"
#include "define.h"
#include "vector.h"


class Sprite
{
private:
	bool ishanten;
public:
	int Image; //�摜�@����DxLib�̃n���h��
	vct2d Pos; //���W
	vct2d Cent; //���S���W
	double Size; //�傫���@100���
	double Deg; //��]�@360�x�ň��]���
	virtual void Draw();
	Sprite();
	Sprite(int i,vct2d p, vct2d c, double s, int hanten = 0);
};