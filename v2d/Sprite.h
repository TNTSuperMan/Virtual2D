#pragma once
#include "vector.h"


class Sprite
{
private:
	bool ishanten;
public:
	int Image; //画像　これDxLibのハンドル
	vector Pos; //座標
	vector Cent; //中心座標
	double Size; //大きさ　100が基準
	double Deg; //回転　360度で一回転だﾖ
	virtual void Draw();
	Sprite();
	Sprite(int i);
	Sprite(int i,vector p, vector c, double s, double r,bool hanten = false);
};