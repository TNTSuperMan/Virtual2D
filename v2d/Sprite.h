#pragma once
#include "vector.h"


class Sprite
{
public:
	int Image = -1; //�摜�@����DxLib�̃n���h��
	vector Pos; //���W
	vector Cent; //���S���W
	vector Stren; //�L�k
	int Size = 100; //�傫���@100���
	int Rotate = 0; //��]�@360�x�ň��]���
	virtual void Draw();
	Sprite(int i,vector p, vector c, vector st, int s, int r);
	Sprite();
};