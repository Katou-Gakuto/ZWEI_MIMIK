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
	bool mbBGMVolumeChange;
	bool mbSEVolumeChange;
	bool mbFullScreen;
	bool mbColorVisionSupport;

    bool FullScreen;
	bool ColorVisionSupport;

    // 0～100
    int mnVolumeBGM;
    int mnVolumeSE;

    // 上下入力のためのデータ
    CursorMoveData mdMoveData;
};