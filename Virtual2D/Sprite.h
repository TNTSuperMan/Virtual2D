#pragma once
#include <DxLib.h>
#include "Vector.h"

class Sprite { //画像の支配クラス
	Vector Pos; //座標
	Vector Cent; //画像の中心からの中心の相対座標
	double Deg; //角度
	double Size; //大きさ　100が基準
	int Image; //DxLibの画像ハンドル
	bool isHanten; //反転してるか
	Sprite();
	Sprite(int img,Vector cent,double size,bool ishanten = false);
};