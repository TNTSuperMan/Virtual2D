#pragma once
#include "include.h"
class Setting
{
public:
	unsigned int backgroundColor; //背景色 クロマキーで上手くいく色でも付けとけ
	int BodyY;  //体のY座標
	int BodyCentY; //体の回転の中心
	int BodySize; //体の大きさ
	int neckY;  //頭の中心からの首のY座標の相対座標
	int HeadY;  //頭の座標
	int HeadSize; //頭の大きさ
	int EyePos; //目の位置
	int EyeSize; //目の大きさ
	int EyeKankaku; //目の間隔
	Setting();
};

