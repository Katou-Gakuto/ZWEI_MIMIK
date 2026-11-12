#include "OptionScene.h"

#include "DxLib.h"

#include "BaseSceneManager.h"

#include "../H_Katou/Singleton/KeyState.h"

#include "../Z_Except/DxLibDataManager.h"
#include "../Z_Except/ResourceManager.h"
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
    Save = 0;


    BerHandle = Master::mpResourceManager->LoadGraphics("Resource/Ber.png");
    BGMHandle = Master::mpResourceManager->LoadGraphics("Resource/文字/BGM_W.png");
    SEHandle = Master::mpResourceManager->LoadGraphics("Resource/文字/SE_W.png");
    ScreenHandle = Master::mpResourceManager->LoadGraphics("Resource/文字/画面サイズ_W.png");
    ColorVisionHandle = Master::mpResourceManager->LoadGraphics("Resource/文字/色覚サポート_W.png");
    ExitHandle = Master::mpResourceManager->LoadGraphics("Resource/文字/戻る_W.png");

    NUMBERHandle = Master::mpResourceManager->LoadGraphics("Resource/文字/NUMBER_W.png");
    ONHandle = Master::mpResourceManager->LoadGraphics("Resource/文字/ON_W.png");
    OFFHandle = Master::mpResourceManager->LoadGraphics("Resource/文字/OFF_W.png");
    FullHDHandle = Master::mpResourceManager->LoadGraphics("Resource/文字/FullHD_W.png");
    HDHandle = Master::mpResourceManager->LoadGraphics("Resource/文字/HD_W.png");

    NowSceneHandle = Master::mpResourceManager->LoadGraphics("Resource/文字/OPTION_W.png");
    AButtonHandle = Master::mpResourceManager->LoadGraphics("Resource/AButton.png");
    BButtonHandle = Master::mpResourceManager->LoadGraphics("Resource/BButton.png");
    DecisionHandle = Master::mpResourceManager->LoadGraphics("Resource/文字/決定_W.png");
    Choice = Master::mpResourceManager->LoadGraphics("Resource/文字/選択_W.png");
    BackHandle = Master::mpResourceManager->LoadGraphics("Resource/文字/戻る_W.png");
    CancelHandle = Master::mpResourceManager->LoadGraphics("Resource/文字/キャンセル_W.png");

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

    bool sceneCancel = 
        Master::mpKeyState->GetShadowGameKeyDown(KEY_SHADOW_GAME_TYPE::B, 0) ||
        Master::mpKeyState->GetShadowGameKeyDown(KEY_SHADOW_GAME_TYPE::B, 1);

    // Bが押された処理
    if (sceneCancel)
    {
        // どこかしらの選択状態なら解除する
        if (mbBGMVolumeChange || mbSEVolumeChange || mbFullScreen || mbColorVisionSupport)
        {
			if (mbBGMVolumeChange)
				mnVolumeBGM = Save;
			else if (mbSEVolumeChange)
				mnVolumeSE = Save;
			else if (mbFullScreen)
				FullScreen = Save;
			else if (mbColorVisionSupport)
				ColorVisionSupport = Save;

            mbBGMVolumeChange = false;
            mbSEVolumeChange = false;
            mbFullScreen = false;
            mbColorVisionSupport = false;

            Master::mpSoundManager->SetBGMVolume(mnVolumeBGM * 2.25);
            Master::mpSoundManager->SetSEVolume(mnVolumeSE * 2.25);
            Master::mpSoundManager->ChangeVolume();

        }
        else // タイトルに戻る
        {
            // ここをBaseSceneManagerのSearchSceneOldで前のシーンに戻るようにする
            Master::mpBaseSceneManager->ChangeScene(Master::mpBaseSceneManager->GetSneceOld(), SCAN::SCAN_None, false, SOAN_None, false);

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
				Save = mnVolumeBGM;
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
				Save = mnVolumeSE;
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
				Save = FullScreen;
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
				Save = ColorVisionSupport;
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
                Master::mpBaseSceneManager->ChangeScene(Master::mpBaseSceneManager->GetSneceOld(), SCAN::SCAN_None, false, SOAN_None, false);

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
    DrawBox(0, 0, 1920, 1080, 0x0E192C, true);
    //DrawLine(960, 0, 960, 1080, GetColor(255, 0, 0));
    DrawExtendGraph(860, 170, 1360, 220, NowSceneHandle, true);

    // 選択中の表示
    switch (this->mnCurrentMode)
    {
    case OptionSelectMode::OptionSelectMode_BGMVolume:
        DrawBox(410, 310, 1530, 392, 0xAAAAAA, true);
        break;
    case OptionSelectMode::OptionSelectMode_SEVolume:
        DrawBox(410, 460, 1530, 542, 0xAAAAAA, true);
        break;
    case OptionSelectMode::OptionSelectMode_FullScreen:
        DrawBox(410, 610, 1530, 692, 0xAAAAAA, true);
        break;
    case OptionSelectMode::OptionSelectMode_ColorVisionSupport:
        DrawBox(410, 760, 1530, 842, 0xAAAAAA, true);
        break;
    case OptionSelectMode::OptionSelectMode_Exit:
        DrawBox(860, 910, 1000, 960, 0xAAAAAA, true);
        break;
    }

    // 各選択肢のバーと書いてあること
    // BGM
    DrawExtendGraph(370, 300, 1570, 400, BerHandle, true);
    DrawExtendGraph(360, 325, 760, 365, BGMHandle, true);
    DrawBox(720, 348, 1220, 350, 0xFFFFFF, true);
	DrawCircle(720 + mnVolumeBGM * 5, 349, 10, 0xFFFFFF, true);
    if (mbBGMVolumeChange)
    {
        if (mnVolumeBGM != 0)
		DrawTriangle(690 + mnVolumeBGM * 5, 349, 700 + mnVolumeBGM * 5, 339, 700 + mnVolumeBGM * 5, 359, 0xFFFFFF, true);
        if (mnVolumeBGM != 100)
        DrawTriangle(750 + mnVolumeBGM * 5, 349, 740 + mnVolumeBGM * 5, 339, 740 + mnVolumeBGM * 5, 359, 0xFFFFFF, true);
    }
    if(mnVolumeBGM == 100)
        DrawRectExtendGraph(1325, 325, 1375, 375, ((mnVolumeBGM / 100) % 10 * 128), 0, 128, 128, NUMBERHandle, true);
    DrawRectExtendGraph(1360, 325, 1410, 375, ((mnVolumeBGM / 10) % 10 * 128), 0, 128, 128, NUMBERHandle, true);
    DrawRectExtendGraph(1395, 325, 1445, 375, ((mnVolumeBGM / 1 ) % 10 * 128), 0, 128, 128, NUMBERHandle, true);

    // SE
    DrawExtendGraph(370, 450, 1570, 550, BerHandle, true);
    DrawExtendGraph(360, 475, 760, 515, SEHandle, true);
    DrawBox(720, 498, 1220, 500, 0xFFFFFF, true);
    DrawCircle(720 + mnVolumeSE * 5, 499, 10, 0xFFFFFF, true);
    if (mbSEVolumeChange)
    {
        if (mnVolumeSE != 0)
            DrawTriangle(690 + mnVolumeSE * 5, 499, 700 + mnVolumeSE * 5, 489, 700 + mnVolumeSE * 5, 509, 0xFFFFFF, true);
        if (mnVolumeSE != 100)
            DrawTriangle(750 + mnVolumeSE * 5, 499, 740 + mnVolumeSE * 5, 489, 740 + mnVolumeSE * 5, 509, 0xFFFFFF, true);
    }
    if (mnVolumeSE == 100)
        DrawRectExtendGraph(1325, 475, 1375, 525, ((mnVolumeSE / 100) % 10 * 128), 0, 128, 128, NUMBERHandle, true);
    DrawRectExtendGraph(1360, 475, 1410, 525, ((mnVolumeSE / 10) % 10 * 128), 0, 128, 128, NUMBERHandle, true);
    DrawRectExtendGraph(1395, 475, 1445, 525, ((mnVolumeSE / 1) % 10 * 128), 0, 128, 128, NUMBERHandle, true);

    // フルスクリーン
    DrawExtendGraph(370, 600, 1570, 700, BerHandle, true);
    DrawExtendGraph(360, 625, 760, 665, ScreenHandle, true);
    if(FullScreen)// ONOFF表示
        DrawExtendGraph(895, 625, 1295, 665, FullHDHandle, true);
    else
        DrawExtendGraph(895, 625, 1295, 665, HDHandle, true);
    if (mbFullScreen)// 矢印
    {
        DrawTriangle(820, 650, 850, 630, 850, 670, 0xFFFFFF, true);
        DrawTriangle(1345, 650, 1315, 630, 1315, 670, 0xFFFFFF, true);
    }

    // 色覚サポート
    DrawExtendGraph(370, 750, 1570, 850, BerHandle, true);
    DrawExtendGraph(360, 775, 760, 815, ColorVisionHandle, true);
    if (ColorVisionSupport)// ONOFF表示
        DrawExtendGraph(895, 775, 1295, 815, ONHandle, true);
    else
        DrawExtendGraph(895, 775, 1295, 815, OFFHandle, true);
    if (mbColorVisionSupport)// 矢印
    {
        DrawTriangle(945, 800, 975, 820, 975, 780, 0xFFFFFF, true);
        DrawTriangle(1245, 800, 1215, 820, 1215, 780, 0xFFFFFF, true);
    }

    // 戻る
    DrawExtendGraph(880, 910, 980, 960, ExitHandle, true);



    // Aボタンの表示
    DxLib::DrawExtendGraph(
        1500, 1000,
        1540, 1040,
        AButtonHandle,
        true);
    // Bボタンの表示
    DxLib::DrawExtendGraph(
        1700, 1000,
        1740, 1040,
        BButtonHandle,
        true);

    if(mbBGMVolumeChange || mbSEVolumeChange || mbFullScreen || mbColorVisionSupport)
    {
        // Aボタンの説明表示
        DxLib::DrawExtendGraph(
            1570, 1000,
            1630, 1030,
            DecisionHandle,
            true);
        // Bボタンの説明表示
        DxLib::DrawExtendGraph(
            1750, 1000,
            2050, 1030,
            CancelHandle,
            true);
    }
    else
    {
        // Aボタンの説明表示
        DxLib::DrawExtendGraph(
            1570, 1000,
            1630, 1030,
            Choice,
            true);
        // Bボタンの説明表示
        DxLib::DrawExtendGraph(
            1770, 1000,
            1830, 1030,
            BackHandle,
            true);
    }




    /*{
        // 
        DRAW_SYSTEM::DrawString(
            VECTOR2D(0, 0),
            "OPTION SCENE",
            GetColor(255, 255, 255));

        DRAW_SYSTEM::DrawString(
            VECTOR2D(400, 100),
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
        DRAW_SYSTEM::DrawString(
            VECTOR2D(400, 200),
            message.c_str(),
            GetColor(255, 255, 255));

        DRAW_SYSTEM::DrawLine(
            VECTOR2D(600, 210),
            VECTOR2D(700, 210),
            GetColor(255, 255, 255));

        DxLib::DrawCircle(
            600 + mnVolumeBGM,
            210,
            5,
            GetColor(255, 255, 255)),
            true;

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
        DRAW_SYSTEM::DrawString(
            VECTOR2D(400, 300),
            message.c_str(),
            GetColor(255, 255, 255));

        DRAW_SYSTEM::DrawLine(
            VECTOR2D(600, 310),
            VECTOR2D(700, 310),
            GetColor(255, 255, 255));

        DxLib::DrawCircle(
            600 + mnVolumeSE,
            310,
            5,
            GetColor(255, 255, 255)),
            true;

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
        DRAW_SYSTEM::DrawString(
            VECTOR2D(400, 400),
            message.c_str(),
            GetColor(255, 255, 255));

        if (FullScreen)
        {
            DRAW_SYSTEM::DrawString(
                VECTOR2D(700, 400),
                "ON",
                GetColor(255, 255, 255));
        }
        else
        {
            DRAW_SYSTEM::DrawString(
                VECTOR2D(700, 400),
                "OFF",
                GetColor(255, 255, 255));
        }


        if (mbFullScreen)
        {
            DRAW_SYSTEM::DrawString(
                VECTOR2D(660, 400),
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
        DRAW_SYSTEM::DrawString(
            VECTOR2D(400, 500),
            message.c_str(),
            GetColor(255, 255, 255));

        if (ColorVisionSupport)
        {
            DRAW_SYSTEM::DrawString(
                VECTOR2D(700, 500),
                "ON",
                GetColor(255, 255, 255));
        }
        else
        {
            DRAW_SYSTEM::DrawString(
                VECTOR2D(700, 500),
                "OFF",
                GetColor(255, 255, 255));
        }

        if (mbColorVisionSupport)
        {
            DRAW_SYSTEM::DrawString(
                VECTOR2D(660, 500),
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
        message += "BACK";

        // 文字列を描画する
        DRAW_SYSTEM::DrawString(
            VECTOR2D(400, 600),
            message.c_str(),
            GetColor(255, 255, 255));
    }*/
    // 
    return 0;
}
