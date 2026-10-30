#include "TitleScene.h"

#include "DxLib.h"

#include "BaseSceneManager.h"

#include "../H_Katou/Singleton/KeyState.h"

#include "../Z_Except/ResourceManager.h"
#include "../Z_Except/SoundManager.h"
#include "../Z_Except/Master.h"
#include "DrawSystem.h"

// 
TitleScene::TitleScene() :
    mbLogoPhase(true),
    mnCurrentMode(TitleSelectMode::TitleSelectMode_StageSelect),
    BaseScene(SceneTag::ST_Title)
{
}

// 
TitleScene::~TitleScene()
{
}

// 
int TitleScene::Create()
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


    // タイトルの一番最初のやつを描画するフェーズに設定する
    this->mbLogoPhase = true;

    TitleLogo = Master::mpResourceManager->LoadGraphics("Resource/ZWEI_MIMIKロゴW(仮).png");
    Master::mpSoundManager->SetBGMVolume(180);
    Master::mpSoundManager->SetSEVolume(180);
    Master::mpSoundManager->ChangeVolume();

    // 
    return 0;
}

// 
int TitleScene::Initialize()
{
    // 
    this->mbLogoPhase = true;

	// カーソルを一番上に設定する
    this->mnCurrentMode = TitleSelectMode::TitleSelectMode_StageSelect;

    Master::mpSoundManager->PlayBGM("Resource/Sound/空.wav");

    // 
    return 0;
}

// 
int TitleScene::Finalize()
{
    // 
    return 0;
}

// 
int TitleScene::Update()
{
    // 
    int temp = 0;

    // 
    temp = this->UpdateModeSelect();

    // 
    return temp;
}

// 
int TitleScene::Draw()
{
    // 
    int returnValue = 0;

    // タイトルの一番最初のやつを描画する
    DRAW_SYSTEM::DrawString(
        VECTOR2D(0.0f, 0.0f),
        "TITLE SCENE\n",
        GetColor(255, 255, 255));

    // 
    if (this->mbLogoPhase)
    {
        // タイトルの一番最初のやつを描画する
        DRAW_SYSTEM::DrawString(
            VECTOR2D(900, 400),
            "   ZWEI MIMIK   \n"
            "                \n"
            "PRESS ANY BUTTON",
            GetColor(255, 255, 255));

        // タイトルロゴを描画
        DrawExtendGraph(700, 200,1250,300, TitleLogo, true);
    }
    else
    {
        // 描画する文字列
        std::string message = "";

        // 現在EXITを指している場合と層でない場合で処理を変える
        if (this->mnCurrentMode == TitleSelectMode::TitleSelectMode_StageSelect)
        {
            // 右矢印を設定する
            message = "⇒";
        }
        else
        {
            // 矢印分の空白を設定する
            message = "　";
        }

        // 文字列をさらに追加する
        message += "STAGE SELECT";

        // 文字列を描画する
        DRAW_SYSTEM::DrawString(
            VECTOR2D(400, 200),
            message.c_str(),
            GetColor(255, 255, 255));

        // 現在EXITを指している場合と層でない場合で処理を変える
        if (this->mnCurrentMode == TitleSelectMode::TitleSelectMode_Option)
        {
            // 右矢印を設定する
            message = "⇒";
        }
        else
        {
            // 矢印分の空白を設定する
            message = "　";
        }

        // 文字列をさらに追加する
        message += "OPTION";

        // 文字列を描画する
        DxLib::DrawString(
            400,
            400,
            message.c_str(),
            GetColor(255, 255, 255));

        // 現在CREDITを指している場合と層でない場合で処理を変える
        if (this->mnCurrentMode == TitleSelectMode::TitleSelectMode_Credit)
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
        message += "CREDIT";

        // 文字列を描画する
        DxLib::DrawString(
            400,
            600,
            message.c_str(),
            GetColor(255, 255, 255));

        // 現在EXITを指している場合と層でない場合で処理を変える
        if (this->mnCurrentMode == TitleSelectMode::TitleSelectMode_Exit)
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
        message += "EXIT";

        // 文字列を描画する
        DRAW_SYSTEM::DrawString(
            VECTOR2D(400, 800),
            message.c_str(),
            GetColor(255, 255, 255));
    }

    // 
    return returnValue;
}

int TitleScene::UpdateModeSelect()
{
    // 
    int returnValue = 0;

    // 
    if (this->mbLogoPhase)
    {
        // 適当なキーが押されていたら処理を行う
        if (Master::mpKeyState->GetShadowGameKeyDown(KEY_SHADOW_GAME_TYPE::A, 0) ||
            Master::mpKeyState->GetShadowGameKeyDown(KEY_SHADOW_GAME_TYPE::A, 1) ||
            Master::mpKeyState->GetShadowGameKeyDown(KEY_SHADOW_GAME_TYPE::B, 0) ||
            Master::mpKeyState->GetShadowGameKeyDown(KEY_SHADOW_GAME_TYPE::B, 1) ||
            Master::mpKeyState->GetShadowGameKeyDown(KEY_SHADOW_GAME_TYPE::X, 0) ||
            Master::mpKeyState->GetShadowGameKeyDown(KEY_SHADOW_GAME_TYPE::X, 1) ||
            Master::mpKeyState->GetShadowGameKeyDown(KEY_SHADOW_GAME_TYPE::Y, 0) ||
            Master::mpKeyState->GetShadowGameKeyDown(KEY_SHADOW_GAME_TYPE::Y, 1))
        {
            // 
            this->mbLogoPhase = false;

            // 
            this->mnCurrentMode = TitleSelectMode_StageSelect;
        }
    }
    else
    {
        // 
        int modeSelect = 0;

        Master::mpCursorMoveSupporter->Move(this->mdMoveData, modeSelect);

        // ↑方向の入力がされているか
        bool currentUp = modeSelect < 0;

        // ↑方向の入力がされているか
        bool currentDown = 0 < modeSelect;

        // 決定ボタンが押されているか
        bool sceneMove = 
            Master::mpKeyState->GetShadowGameKeyDown(KEY_SHADOW_GAME_TYPE::A, 0) ||
            Master::mpKeyState->GetShadowGameKeyDown(KEY_SHADOW_GAME_TYPE::A, 1);

		// キャンセルボタンが押されているか
		bool Back = 
            Master::mpKeyState->GetShadowGameKeyDown(KEY_SHADOW_GAME_TYPE::B, 0) ||
			Master::mpKeyState->GetShadowGameKeyDown(KEY_SHADOW_GAME_TYPE::B, 1);


        // Bが押されたらロゴの画面に戻る
        if (Back)
        {
            // 
            this->mbLogoPhase = true;
        }

        // 
        switch (this->mnCurrentMode)
        {
        case TitleSelectMode::TitleSelectMode_StageSelect:
            if (sceneMove)
            {
                // 
                Master::mpBaseSceneManager->ChangeScene(SceneTag::ST_StageSelect);

                // 
                this->OnResetFlag();
            }
            else
            {
                if (currentUp)
                {
                    // 
                    this->mnCurrentMode = TitleSelectMode::TitleSelectMode_Exit;
                }
                if (currentDown)
                {
                    // 
                    this->mnCurrentMode = TitleSelectMode::TitleSelectMode_Option;
                }
            }
            break;

        case TitleSelectMode::TitleSelectMode_Option:
            if (sceneMove)
            {
                // 
                Master::mpBaseSceneManager->ChangeScene(SceneTag::ST_Option);
            }
            else
            {
                if (currentUp)
                {
                    // 
                    this->mnCurrentMode = TitleSelectMode::TitleSelectMode_StageSelect;
                }
                if (currentDown)
                {
                    // 
                    this->mnCurrentMode = TitleSelectMode::TitleSelectMode_Credit;
                }
            }
            break;

		case TitleSelectMode::TitleSelectMode_Credit:
			if (sceneMove)
			{
				// 
				Master::mpBaseSceneManager->ChangeScene(SceneTag::ST_Credit);
			}
			else
			{
				if (currentUp)
				{
					// 
					this->mnCurrentMode = TitleSelectMode::TitleSelectMode_Option;
				}
				if (currentDown)
				{
					// 
					this->mnCurrentMode = TitleSelectMode::TitleSelectMode_Exit;
				}
			}
			break;

        case TitleSelectMode::TitleSelectMode_Exit:
            if (sceneMove)
            {
                // 
                Master::mpEndManager;

                // 
                this->OnResetFlag();
            }
            else
            {
                if (currentUp)
                {
                    // 
                    this->mnCurrentMode = TitleSelectMode::TitleSelectMode_Credit;
                }
                if (currentDown)
                {
                    // 
                    this->mnCurrentMode = TitleSelectMode::TitleSelectMode_StageSelect;
                }
            }
            break;
        default:
            returnValue = -1;
            break;
        }
    }
    // 
    return returnValue;
}
