#include "TitleScene.h"

#include "DxLib.h"

#include "BaseSceneManager.h"

#include "../H_Katou/Singleton/KeyState.h"
#include "../H_Katou/Singleton/EndManager.h"

#include "../Z_Except/ResourceManager.h"
#include "../Z_Except/SoundManager.h"
#include "../Z_Except/Master.h"

#include "DrawSystem.h"

TitleScene::TitleScene() :
  mbLogoPhase(true),
  mnCurrentMode(TitleSelectMode::TitleSelectMode_StageSelect),
  BaseScene(SceneTag::ST_Title),
  Character1(*(new VECTOR2D(1920, 250))), // Dynamically allocate VECTOR2D object
  Character2(*(new VECTOR2D(0, 790)))  // Dynamically allocate VECTOR2D object
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

    TitleLogo = Master::mpResourceManager->LoadGraphics("Resource/ZWEI_MIMIKロゴ(仮).png");
    Light = Master::mpResourceManager->LoadGraphics("Resource/仮.png");
    PRESSANYBUTTON = Master::mpResourceManager->LoadGraphics("Resource/文字/PRESS_ANY_BUTTON_B.png");
    STAGESELECT    = Master::mpResourceManager->LoadGraphics("Resource/文字/STAGE_SELECT_B.png");
    OPTION         = Master::mpResourceManager->LoadGraphics("Resource/文字/OPTION_B.png");
    CREDIT         = Master::mpResourceManager->LoadGraphics("Resource/文字/CREDIT_B.png");
    EXIT           = Master::mpResourceManager->LoadGraphics("Resource/文字/EXIT_B.png");

    AButtonHandle = Master::mpResourceManager->LoadGraphics("Resource/AButton.png");
    BButtonHandle = Master::mpResourceManager->LoadGraphics("Resource/BButton.png");

    DecisionHandle = Master::mpResourceManager->LoadGraphics("Resource/文字/決定_B.png");
    BackHandle = Master::mpResourceManager->LoadGraphics("Resource/文字/戻る_B.png");
    Master::mpSoundManager->SetBGMVolume(180);
    Master::mpSoundManager->SetSEVolume(180);
    Master::mpSoundManager->ChangeVolume();

    // 
    return 0;
}

// 
int TitleScene::Initialize()
{
	// カーソルを一番上に設定する
    this->mnCurrentMode = TitleSelectMode::TitleSelectMode_StageSelect;

    Master::mpSoundManager->PlayBGM("Resource/Sound/空.wav");
    fwfw = 0;
    Time = 0;
    vec = 20;

    CannotOperate = 0;
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

    // 画像をふわふわさせる
    Time += 0.05f;

    fwfw = sinf(Time) * vec;
    Character1.SetX(Character1.GetX() - 10);
    Character2.SetX(Character2.GetX() + 10);

    if (Character1.GetX() <= -200)
    {
		Character1.SetX(2120);
    }
    if (Character2.GetX() >= 2120)
    {
		Character2.SetX(-200);
    }

    // 操作不能時間で画像をずらす
    if(CannotOperate > 0)
    {
        CannotOperate--;
        Swipe += 200;
    }
    else if (CannotOperate < 0)
    {
        CannotOperate++;
        Swipe -= 200;
    }

    // 
    return temp;
}

// 
int TitleScene::Draw()
{
    // 
    int returnValue = 0;
    std::string message;

    DRAW_SYSTEM::DrawBox(VECTOR2D(0, 540), VECTOR2D(1920, 1080), 0xFFFDF7, true);

    DrawBox(Character1.GetX(), Character1.GetY(),
        Character1.GetX() + 100, Character1.GetY() + 200,
        0xFF0000, true);
    DrawBox(Character2.GetX(), Character2.GetY(),
        Character2.GetX() + 100, Character2.GetY() + 200,
        0xFF0000, true);


    // タイトルロゴを描画
    DrawExtendGraph(550 + Swipe, 471       , 1375 + Swipe, 611       , TitleLogo, true);
    DrawExtendGraph(680 + Swipe, 850 + fwfw, 1280 + Swipe, 900 + fwfw, PRESSANYBUTTON, true);

	// モード選択肢を描画(選択中ならふわふわ)
    if (this->mnCurrentMode == TitleSelectMode_StageSelect)
    {
        DrawExtendGraph(-1310 + Swipe, 575       , -1260 + Swipe, 625       , Light, true);
        DrawExtendGraph(-1250 + Swipe, 575 + fwfw, -750 + Swipe, 625 + fwfw, STAGESELECT, true);
        message = "ゲームを開始します";
    }
    else
    {
        DrawExtendGraph(-1250 + Swipe, 575, -750 + Swipe, 625, STAGESELECT, true);
    }

    if (this->mnCurrentMode == TitleSelectMode_Option)
    {
        DrawExtendGraph(-1310 + Swipe, 675       , -1260 + Swipe, 725       , Light, true);
        DrawExtendGraph(-1250 + Swipe, 675 + fwfw, -750 + Swipe, 725 + fwfw, OPTION, true);
        message = "オプション画面に移動します";
    }
    else
    {
        DrawExtendGraph(-1250 + Swipe, 675, -750 + Swipe, 725, OPTION, true);
    }

    if (this->mnCurrentMode == TitleSelectMode_Credit)
    {
        DrawExtendGraph(-1310 + Swipe, 775       , -1260 + Swipe, 825       , Light, true);
        DrawExtendGraph(-1250 + Swipe, 775 + fwfw, -750 + Swipe, 825 + fwfw, CREDIT, true);
        message = "クレジット表記へ移動します";
    }
    else
    {
        DrawExtendGraph(-1250 + Swipe, 775, -750 + Swipe, 825, CREDIT, true);
    }

    if (this->mnCurrentMode == TitleSelectMode_Exit)
    {
        DrawExtendGraph(-1310 + Swipe, 875       , -1260 + Swipe, 925       , Light, true);
        DrawExtendGraph(-1250 + Swipe, 875 + fwfw, -750 + Swipe, 925 + fwfw, EXIT, true);
        message = "ゲームを終了します";
    }
    else
    {
        DrawExtendGraph(-1250 + Swipe, 875, -750 + Swipe, 925, EXIT, true);
    }



    if (!mbLogoPhase)
    {
        // 
        DRAW_SYSTEM::DrawString(
            VECTOR2D(750, 1000),
            message.c_str(),
            GetColor(255, 255, 255));

        // Aボタンの表示
        DxLib::DrawExtendGraph(
            1500, 1000,
            1540, 1040,
            AButtonHandle,
            true);

        // Aボタンの説明表示
        DxLib::DrawExtendGraph(
            1570, 1000,
            1630, 1030,
            DecisionHandle,
            true);

        // Bボタンの表示
        DxLib::DrawExtendGraph(
            1700, 1000,
            1740, 1040,
            BButtonHandle,
            true);

        // Bボタンの説明表示
        DxLib::DrawExtendGraph(
            1770, 1000,
            1830, 1030,
            BackHandle,
            true);
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

            this->CannotOperate = 10;
        }
    }
    else if(CannotOperate == 0)
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

        if (currentUp || currentDown)
        {
            fwfw = 0;
            Time = 0;
            vec = 20;
        }

        // Bが押されたらロゴの画面に戻る
        if (Back)
        {
            // ロゴを移すフェーズにする
            this->mbLogoPhase = true;

            // 
            this->CannotOperate = -10;

            // 同時押しによる例外を防ぐ
            return returnValue;
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
