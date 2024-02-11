#pragma once
#include "vector.h"


class Sprite
{
private:
	bool ishanten;
public:
	int Image = -1; //画像　これDxLibのハンドル
	vector Pos; //座標
	vector Cent; //中心座標
	vector Stren; //伸縮
	int Size = 100; //大きさ　100が基準
	double Rotate = 0; //回転　360度で一回転だﾖ
	virtual void Draw();
	Sprite(int i,vector p, vector c, vector st, int s, double r,bool hanten = false);
	Sprite();
};