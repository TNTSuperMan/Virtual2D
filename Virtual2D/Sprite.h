#pragma once
#include <DxLib.h>
#include "Vector.h"

class Sprite { //�摜�̎x�z�N���X
	Vector Pos; //���W
	Vector Cent; //�摜�̒��S����̒��S�̑��΍��W
	double Deg; //�p�x
	double Size; //�傫���@100���
	int Image; //DxLib�̉摜�n���h��
	bool isHanten; //���]���Ă邩
	Sprite();
	Sprite(int img,Vector cent,double size,bool ishanten = false);
};