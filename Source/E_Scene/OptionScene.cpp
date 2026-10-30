#include "OptionScene.h"

#include "DxLib.h"

#include "BaseSceneManager.h"

#include "../H_Katou/Singleton/KeyState.h"

#include "../Z_Except/DxLibDataManager.h"
#include "../Z_Except/SoundManager.h"
#include "../Z_Except/Master.h"
#include "DrawSystem.h"
// 
OptionScene::OptionScene() :
    mnVolumeBGM(0xaf),
    mnVolumeSE(0xaf),
    BaseScene(SceneTag::ST_Option)
{
}

// 
OptionScene::~OptionScene()
{
}

int OptionScene::Create()
{
    // 
    CursorMoveElement newElement;

    // 
    newElement.mnTargetKey = KEY_SHADOW_GAME_TYPE::UP;
    newElement.mnMoveVec = -1;
    this->mdMoveData.Add(newElement);

    // 
    newElement.mnTargetKey = KEY_SHADOW_GAME_TYPE::DOWN;
    newElement.mnMoveVec = +1;
    this->mdMoveData.Add(newElement);
    // 
    newElement.mnTargetKey = KEY_SHADOW_GAME_TYPE::LEFT;
    newElement.mnMoveVec = -2;
    this->mdMoveData.Add(newElement);

    // 
    newElement.mnTargetKey = KEY_SHADOW_GAME_TYPE::RIGHT;
    newElement.mnMoveVec = +2;
    this->mdMoveData.Add(newElement);

    FullScreen = true;
    ColorVisionSupport = false;

    mnVolumeBGM = 80;
    mnVolumeSE = 80;

    return 0;
}

int OptionScene::Initialize()
{
	// カーソルを一番上に設定する
    this->mnCurrentMode = OptionSelectMode::OptionSelectMode_BGMVolume;
    mbBGMVolumeChange = false;
    mbSEVolumeChange = false;
    mbFullScreen = false;
    mbColorVisionSupport = false;


    return 0;
}

int OptionScene::Finalize()
{
    // 
    return 0;
}

int OptionScene::Update()
{
    // 
    int temp = 0;

    // 
    temp = this->UpdateModeSelect();

    // 
    return temp;
}


int OptionScene::UpdateModeSelect()
{

    // 
    int modeSelect = 0;

    Master::mpCursorMoveSupporter->Move(this->mdMoveData, modeSelect);

    // ↑方向の入力がされているか
    bool currentUp = modeSelect == -1;

    // ↓方向の入力がされているか
    bool currentDown = modeSelect == 1;

    // ←方向の入力がされているか
    bool currentLeft = modeSelect == -2;

    // →方向の入力がされているか
    bool currentRight = modeSelect == 2;

    // 決定ボタンが押されているか
    bool sceneMove =
        Master::mpKeyState->GetShadowGameKeyDown(KEY_SHADOW_GAME_TYPE::A, 0) ||
        Master::mpKeyState->GetShadowGameKeyDown(KEY_SHADOW_GAME_TYPE::A, 1);

    // Bが押された処理
    if (Master::mpKeyState->GetShadowGameKey(KEY_SHADOW_GAME_TYPE::B, 0))
    {
        // どこかしらの選択状態なら解除する
        if (mbBGMVolumeChange || mbSEVolumeChange || mbFullScreen || mbColorVisionSupport)
        {
            mbBGMVolumeChange = false;
            mbSEVolumeChange = false;
            mbFullScreen = false;
            mbColorVisionSupport = false;
        }
        else // タイトルに戻る
        {
            // 
            Master::mpBaseSceneManager->ChangeScene(SceneTag::ST_Title);

            // 
            this->OnResetFlag();
        }
    }

    // 各状態の処理
    if (mbBGMVolumeChange)
    {
        // 左右の移動
        if (currentRight)
            mnVolumeBGM++;
        if (currentLeft)
            mnVolumeBGM--;

        // 音量の上限と下限に制限をかける
        if (mnVolumeBGM > 100)
            mnVolumeBGM = 100;
        if (mnVolumeBGM < 0)
            mnVolumeBGM = 0;

        Master::mpSoundManager->SetBGMVolume(mnVolumeBGM * 2.25);
        Master::mpSoundManager->ChangeVolume();

        // Aを押したら音量変更を終了する
        if (sceneMove)
            mbBGMVolumeChange = false;
    }
    else if (mbSEVolumeChange)
    {
        // 左右の移動
        if (currentRight)
            mnVolumeSE++;
        if (currentLeft)
            mnVolumeSE--;

        // 音量の上限と下限に制限をかける
        if (mnVolumeSE > 100)
            mnVolumeSE = 100;
        if (mnVolumeSE < 0)
            mnVolumeSE = 0;

        Master::mpSoundManager->SetSEVolume(mnVolumeSE * 2.25);
        Master::mpSoundManager->ChangeVolume();

        // Aを押したら音量変更を終了する
        if (sceneMove)
            mbSEVolumeChange = false;
    }
    else if (mbFullScreen)
    {
        // 左右で切り替え
        if (currentRight || currentLeft)
            FullScreen = !FullScreen;

            VECTOR2D DispSize;
        if(FullScreen)
        {
            DispSize = Master::mpDxLibDataManager->GetStartDisplaySize();
            // DispSize.SetX(1920);
            // DispSize.SetY(1080);
        }
        else
        {
            DispSize = (Master::mpDxLibDataManager->GetStartDisplaySize() * 2.0f) / 3.0f;
            // DispSize.SetX(1280);
            // DispSize.SetY(720);
        }

        // Aを押したら変更を終了する
        if (sceneMove)
        {
            mbFullScreen = false;
            Master::mpDxLibDataManager->SettingNewDisplaySize(DispSize);
        }
    }
    else if (mbColorVisionSupport)
    {
        // 左右で切り替え
        if (currentRight || currentLeft)
            ColorVisionSupport = !ColorVisionSupport;

        // Aを押したら変更を終了する
        if (sceneMove)
            mbColorVisionSupport = false;
    }
    else
    {
        // 選択中のカーソルに応じてボタンの処理を変える
        switch (this->mnCurrentMode)
        {
            // BGM音量
        case OptionSelectMode::OptionSelectMode_BGMVolume:
            if (sceneMove)
            {
                mbBGMVolumeChange = true;
            }
            else
            {
                if (currentUp)
                {
                    // 
                    this->mnCurrentMode = OptionSelectMode::OptionSelectMode_Exit;
                }
                if (currentDown)
                {
                    // 
                    this->mnCurrentMode = OptionSelectMode::OptionSelectMode_SEVolume;
                }
            }
            break;
            // SE音量
        case OptionSelectMode::OptionSelectMode_SEVolume:
            if (sceneMove)
            {
                mbSEVolumeChange = true;
            }
            else
            {
                if (currentUp)
                {
                    // 
                    this->mnCurrentMode = OptionSelectMode::OptionSelectMode_BGMVolume;
                }
                if (currentDown)
                {
                    // 
                    this->mnCurrentMode = OptionSelectMode::OptionSelectMode_FullScreen;
                }
            }
            break;
            // フルスクリーン
        case OptionSelectMode::OptionSelectMode_FullScreen:
            if (sceneMove)
            {
                mbFullScreen = true;
            }
            else
            {
                if (currentUp)
                {
                    // 
                    this->mnCurrentMode = OptionSelectMode::OptionSelectMode_SEVolume;
                }
                if (currentDown)
                {
                    // 
                    this->mnCurrentMode = OptionSelectMode::OptionSelectMode_ColorVisionSupport;
                }
            }
            break;
            // 色覚サポート
        case OptionSelectMode::OptionSelectMode_ColorVisionSupport:
            if (sceneMove)
            {
                mbColorVisionSupport = true;
            }
            else
            {
                if (currentUp)
                {
                    // 
                    this->mnCurrentMode = OptionSelectMode::OptionSelectMode_FullScreen;
                }
                if (currentDown)
                {
                    // 
                    this->mnCurrentMode = OptionSelectMode::OptionSelectMode_Exit;
                }
            }
            break;
            // タイトルに戻る
        case OptionSelectMode::OptionSelectMode_Exit:
            if (sceneMove)
            {
                // ここをBaseSceneManagerのSearchSceneOldで前のシーンに戻るようにする
                Master::mpBaseSceneManager->ChangeScene(SceneTag::ST_Title);

                // 
                this->OnResetFlag();
            }
            else
            {
                if (currentUp)
                {
                    // 
                    this->mnCurrentMode = OptionSelectMode::OptionSelectMode_ColorVisionSupport;
                }
                if (currentDown)
                {
                    // 
                    this->mnCurrentMode = OptionSelectMode::OptionSelectMode_BGMVolume;
                }
            }
            break;
        default:
            break;
        }
    }

	// 
	return 0;
}

int OptionScene::Draw()
{
    // 
    DRAW_SYSTEM::DrawString(
        VECTOR2D(0, 0),
        "OPTION SCENE",
        GetColor(255, 255, 255));

    DxLib::DrawString(
        400,
        100,
        "CONFIG",
        GetColor(255, 255, 255));


        // 描画する文字列
        std::string message = "";

        // 現在EXITを指している場合と層でない場合で処理を変える
        // BGM
        if (this->mnCurrentMode == OptionSelectMode::OptionSelectMode_BGMVolume)
        {
            if (mbBGMVolumeChange)
            {
                message = "◎";
            }
            else
            {
                // 右矢印を設定する
                message = "⇒";
            }
        }
        else
        {
            // 矢印分の空白を設定する
            message = "　";
        }

        // 文字列をさらに追加する
        message += "BGMVolume";

        // 文字列を描画する
        DxLib::DrawString(
            400,
            200,
            message.c_str(),
            GetColor(255, 255, 255));
		DxLib::DrawLine(
			600,
            210,
			700,
            210,
			GetColor(255, 255, 255));
		DxLib::DrawCircle(
			600 + mnVolumeBGM,
            210,
            5,
			GetColor(255, 255, 255));
        DxLib::DrawFormatString(
            720,
            200,
            GetColor(255, 255, 255),
            "%d%",
			mnVolumeBGM);
        

        // SE
        if (this->mnCurrentMode == OptionSelectMode::OptionSelectMode_SEVolume)
        {
            if (mbSEVolumeChange)
            {
                message = "◎";
            }
            else
            {
                // 右矢印を設定する
                message = "⇒";
            }
        }
        else
        {
            // 矢印分の空白を設定する
            message = "　";
        }

        // 文字列をさらに追加する
        message += "SEVolume";

        // 文字列を描画する
        DxLib::DrawString(
            400,
            300,
            message.c_str(),
            GetColor(255, 255, 255));
        DxLib::DrawLine(
            600,
            310,
            700,
            310,
            GetColor(255, 255, 255));
        DxLib::DrawCircle(
            600 + mnVolumeSE,
            310,
            5,
            GetColor(255, 255, 255));
        DxLib::DrawFormatString(
            720,
            300,
            GetColor(255, 255, 255),
            "%d %",
            mnVolumeSE);


        // フルスクリーン
        if (this->mnCurrentMode == OptionSelectMode::OptionSelectMode_FullScreen)
        {
            if (mbFullScreen)
            {
                message = "◎";
            }
            else
            {
                // 右矢印を設定する
                message = "⇒";
            }
        }
        else
        {
            // 矢印分の空白を設定する
            message = "　";
        }

        // 文字列をさらに追加する
        message += "FullScreen";

        // 文字列を描画する
        DxLib::DrawString(
            400,
            400,
            message.c_str(),
            GetColor(255, 255, 255));

        if(FullScreen)
            DxLib::DrawString(
                700,
                400,
                "ON",
                GetColor(255, 255, 255));
        else
			DxLib::DrawString(
				700,
				400,
				"OFF",
				GetColor(255, 255, 255));
        if (mbFullScreen)
        {
            DxLib::DrawString(
                660,
                400,
                "←　　　→",
                GetColor(255, 255, 255));
        }
        

        // 色覚サポート
        if (this->mnCurrentMode == OptionSelectMode::OptionSelectMode_ColorVisionSupport)
        {
            if (mbColorVisionSupport)
            {
                message = "◎";
            }
            else
            {
                // 右矢印を設定する
                message = "⇒";
            }
        }
        else
        {
            // 矢印分の空白を設定する
            message = "　";
        }

        // 文字列をさらに追加する
        message += "ColorVisionSupport";

        // 文字列を描画する
        DxLib::DrawString(
            400,
            500,
            message.c_str(),
            GetColor(255, 255, 255));

        if (ColorVisionSupport)
            DxLib::DrawString(
                700,
                500,
                "ON",
                GetColor(255, 255, 255));
        else
            DxLib::DrawString(
                700,
                500,
                "OFF",
                GetColor(255, 255, 255));

        if (mbColorVisionSupport)
        {
            DxLib::DrawString(
                660,
                500,
                "←　　　→",
                GetColor(255, 255, 255));
        }


        // タイトルへ
        if (this->mnCurrentMode == OptionSelectMode::OptionSelectMode_Exit)
        {
            // 右矢印を設定する
            message = "⇒";
        }
        else
        {
            // 矢印分の空白を設定する
            message = "　";
        }

        // 
        message += "TITLE";

        // 文字列を描画する
        DRAW_SYSTEM::DrawString(
            VECTOR2D(400, 600),
            message.c_str(),
            GetColor(255, 255, 255));

    // 
    return 0;
}
