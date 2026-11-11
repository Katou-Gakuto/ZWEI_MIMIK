#pragma once

#include "BaseScene.h"

#include "../Z_Except/CursorMoveSupporter.h"

class VECTOR2D;
// 
enum TitleSelectMode
{
    TitleSelectMode_ModeSelect = 0,     // モード選択
    TitleSelectMode_StageSelect,        // ステージ選択に移る
    TitleSelectMode_Option,             // 設定(音量とか)に移る
	TitleSelectMode_Credit,             // クレジット画面に移る
    TitleSelectMode_Exit,               // ゲーム終了

    TitleSelectMode_Max,
};

class TitleScene : public BaseScene
{
public:
    // 
    TitleScene();

    // 
    ~TitleScene();

    // 
    int Create() override;

    // 
    int Initialize() override;

    // 
    int Finalize() override;

    // 
    int Update() override;

    // 
    int Draw() override;

    float EaseOutSine(float t) { return sinf(t * 3.14159265f * 0.5f); }

private:

    VECTOR2D &Character1;
    VECTOR2D &Character2;

    int UpdateModeSelect();

    // 「ボタンを押してください！」のフェーズか
    bool mbLogoPhase;

    // カーソルで選択しているモード
    TitleSelectMode mnCurrentMode;

	// 上下入力のためのデータ
    CursorMoveData mdMoveData;

	// 画像等をふわふわさせるための変数
    float fwfw;
    float vec;
	float Time;

    // 操作不能時間
    int CannotOperate;
    // 画像を右にずらす 
    int Swipe;

	// 画像ハンドル
    int TitleLogo;
    int Light;
    int PRESSANYBUTTON;
	int STAGESELECT;
	int OPTION;
	int CREDIT;
	int EXIT;

    int AButtonHandle;
    int BButtonHandle;
    int DecisionHandle;
    int BackHandle;
};