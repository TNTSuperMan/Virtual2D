#pragma once
#include "vector.h"


class Sprite
{
private:
	bool ishanten;
public:
	int Image; //�摜�@����DxLib�̃n���h��
	vector Pos; //���W
	vector Cent; //���S���W
	double Size; //�傫���@100���
	double Deg; //��]�@360�x�ň��]���
	virtual void Draw();
	Sprite();
	Sprite(int i);
	Sprite(int i,vector p, vector c, double s, double r,bool hanten = false);
};