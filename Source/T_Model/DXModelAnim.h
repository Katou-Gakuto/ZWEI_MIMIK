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

	
	void SetNowPage(int nowpage) { NowPage = nowpage; }// 現在のページを設定する
	void SetMaxPage(int maxpage, int animnum) { MaxPage[animnum] = maxpage; } // 最大ページ数を設定する
	void SetMaxPageFrame(int maxpageframe, int animnum) { MaxPageFrame[animnum] = maxpageframe; } // ページをめくるまでのフレーム数を設定する
	void ChangeAnimNum(int animnum);//アニメーション番号を指定してアニメーションを変更出来る様にする

private:

	VECTOR2D uvLeftUp;
	VECTOR2D uvRightDown;

	int NowPage; // 現在のフレーム
	int NowPageFrame;// ページをめくるまでのフレーム数
	int MaxPage[Anim_Max]; // 最大フレーム数
	int MaxPageFrame[Anim_Max]; // ページをめくるまでのフレーム数の最大値

	float UVWidth;

	int AnimNum; // アニメーションの番号

	int GraphHandle[Anim_Max];
};