#pragma once
#include "BaseModel.h"
#include "VECTOR.h"
#include <string>
using namespace std;

// アニメーションの保存番号
enum AnimationList
{
	Anim_Idle,
	Anim_Walk,
	Anim_Push,
	Anim_Max
};


class DXAnimModel : public BaseModel
{
public:
	DXAnimModel(GameObject *myObject);
	~DXAnimModel();

	int Initialize();
	int Update();
	int Draw();
	int Finalize();

	// 画像とページ数、間隔、アニメーションの保存番号を設定する
	int SetAnimModel(string pathName, int maxPage, int maxPageFrame, float uvdown, float uvright, int animnum);

	void SetNowPage(int nowpage) { NowPage = nowpage; }
	void SetMaxPage(int maxpage) { MaxPage = maxpage; }
	void SetMaxPageFrame(int maxpageframe) { MaxPageFrame = maxpageframe; }
	void ChangeAnimNum(int animnum) { AnimNum = animnum; } //アニメーション番号を指定してアニメーションを変更出来る様にする

private:

	VECTOR2D uvLeftUp;
	VECTOR2D uvRightDown;

	int NowPage; // 現在のフレーム
	int MaxPage; // 最大フレーム数
	int NowPageFrame;
	int MaxPageFrame; // ページをめくるまでのフレーム数
	float UVWidth;

	int AnimNum; // アニメーションの番号

	int GraphHandle[Anim_Max];
};