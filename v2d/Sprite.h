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
	int Image; //画像　これDxLibのハンドル
	vct2d Pos; //座標
	vct2d Cent; //中心座標
	vct2d Stren; //伸び
	double Size; //大きさ　100が基準
	double Deg; //回転　360度で一回転だﾖ
	void Draw();
	Sprite();
	Sprite(int i,vct2d p, vct2d c, double s, int hanten = 0);
};