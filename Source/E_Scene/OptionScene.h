#pragma once

#include "BaseScene.h"
#include "../Z_Except/CursorMoveSupporter.h"

// 
enum OptionSelectMode
{
   OptionSelectMode_BGMVolume = 0,      // BGMの音量調整
   OptionSelectMode_SEVolume,           // SEの音量調整
   OptionSelectMode_FullScreen,         // 全画面にするか
   OptionSelectMode_ColorVisionSupport, // 色覚サポートをオンにするか
   OptionSelectMode_Exit,               // タイトルに戻る
   
   OptionSelectMode_Max,
};

class OptionScene : public BaseScene
{
public:
    // 
    OptionScene();

    // 
    ~OptionScene();

    int Create() override;
    int Initialize() override;
    int Finalize() override;
    int Update() override;
    int Draw() override;

private:

    int UpdateModeSelect();

	OptionSelectMode mnCurrentMode;

    // 選択状態
	bool mbBGMVolumeChange;
	bool mbSEVolumeChange;
	bool mbFullScreen;
	bool mbColorVisionSupport;

    // 機能のONOFF状態
    bool FullScreen;
	bool ColorVisionSupport;

    // 0～100
    int mnVolumeBGM;
    int mnVolumeSE;
    int Save;

    // 
    int BerHandle;
    int BGMHandle;
    int SEHandle;
    int ScreenHandle;
    int ColorVisionHandle;
    int ExitHandle;

    int NUMBERHandle;
    int ONHandle;
    int OFFHandle;
    int FullHDHandle;
    int HDHandle;

    int NowSceneHandle;
    int AButtonHandle;
    int BButtonHandle;
    int DecisionHandle;
    int Choice;
    int BackHandle;
    int CancelHandle;

    // 上下入力のためのデータ
    CursorMoveData mdMoveData;
};