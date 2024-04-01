#pragma once
#include <nlohmann/json.hpp>
#include <fstream>
class Setting
{
public:
	unsigned int backgroundColor; //背景色 クロマキーで上手くいく色でも付けとけ
	int BodyY;          //体のY座標
	int BodyCentY;      //体の回転の中心
	int BodySize;       //体の大きさ
	int neckY;          //頭の中心からの首のY座標の相対座標
	int HeadY;          //頭の座標
	int HeadSize;       //頭の大きさ
	int EyePos;         //目の位置
	int EyeSize;        //目の大きさ
	int EyeKankaku;     //目の間隔
	int MabatakiKankaku;//瞬きの間隔
	int MabatakiTime;   //瞬きの時間
	int MabatakiSize;   //瞬きの大きさ
	int BodyFurehaba;   //体の振れ幅
	int HeadFurehaba;   //頭の振れ幅
	int FureSpeed;      //振れ幅スピード ÷1000で実際の値
	bool GetdownMode;    //ゲッダン☆モード
	int EyePointerSize; //目がどのくらいポインタに影響されるか
	int HeadPointerSize;//体がどのくらいポインタに影響されるか
	int PointerHoseX;   //ポインター追跡の補整
	int PointerHoseY;   //ポインター追跡の補整
	int MouthSize;      //口の大きさ
	int CloseMouthSize; //閉じてる口の大きさ
	int MouthY;         //口の位置
	int MouthPointerSize;//口がどのくらいポインタに影響されるか
	Setting();
	Setting(int a);
};
