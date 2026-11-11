#include "StageSelectScene.h"

#include "DxLib.h"

#include <string>

#include "../E_Scene/BaseSceneManager.h"
#include "../E_Scene/BasePuzzleScene.h"
#include "../H_Katou/Singleton/KeyState.h"

#include "../Z_Except/ResourceManager.h"
#include "../Z_Except/Master.h"
#include "DrawSystem.h"

// 
StageSelectScene::StageSelectScene() :
    mnCurrentStage(0),
    mnUnlockStageCount(10),
    mdMoveData(),
    StageNum(0),
    MoveDirection(0),
    BaseScene(SceneTag::ST_StageSelect)
{
}

// 
StageSelectScene::~StageSelectScene()
{
}

// 
int StageSelectScene::Create()
{
    // 
    CursorMoveElement element;

    // 
    element.mnTargetKey = KEY_SHADOW_GAME_TYPE::LEFT;
    element.mnMoveVec = -1;
    this->mdMoveData.Add(element);

    // 
    element.mnTargetKey = KEY_SHADOW_GAME_TYPE::RIGHT;
    element.mnMoveVec = +1;
    this->mdMoveData.Add(element);

    mnCurrentStage = 0;
    for (StageNum = 0; StageNum < StageMax; StageNum++)
    {
        /*switch (StageNum)
        {
        case 0:
            CubeSize[StageNum] = 150;
            CubeX[StageNum] = 0;
            CubeY[StageNum] = 150;
            break;

        case 1:
            CubeSize[StageNum] = 100;
            CubeX[StageNum] = 300;
            CubeY[StageNum] = 0;
            break;

        case 2:
            CubeSize[StageNum] = 50;
            CubeX[StageNum] = 0;
            CubeY[StageNum] = -150;
            break;

        case 3:
            CubeSize[StageNum] = 100;
            CubeX[StageNum] = -300;
            CubeY[StageNum] = 0;
            break;
        }*/

        if (StageNum < StageMax / 2)
        {
            CubeSize[StageNum] = 150;// -(70 * StageNum);
            CubeX[StageNum] = (Interval * StageNum);
            CubeY[StageNum] = 300;
        }
        else
        {
            CubeSize[StageNum] = 150;// +(-70 * (StageMax / 2) + (70 * (StageNum - StageMax / 2)));
            CubeX[StageNum] = -Interval * (StageMax / 2) + (Interval * (StageNum - StageMax / 2));
            CubeY[StageNum] = 300;
        }

        CubeStage[StageNum] = StageNum;
    }

    CubeHandle[0] = Master::mpResourceManager->LoadGraphics("Resource/kari1.png");
    CubeHandle[1] = Master::mpResourceManager->LoadGraphics("Resource/kari2.png");
    CubeHandle[2] = Master::mpResourceManager->LoadGraphics("Resource/kari3.png");
    CubeHandle[3] = Master::mpResourceManager->LoadGraphics("Resource/kari4.png");
    CubeHandle[4] = Master::mpResourceManager->LoadGraphics("Resource/kari5.png");
    CubeHandle[5] = Master::mpResourceManager->LoadGraphics("Resource/kari6.png");
    CubeHandle[6] = Master::mpResourceManager->LoadGraphics("Resource/kari7.png");
    CubeHandle[7] = Master::mpResourceManager->LoadGraphics("Resource/kari8.png");
    CubeHandle[8] = Master::mpResourceManager->LoadGraphics("Resource/kari9.png");
    CubeHandle[9] = Master::mpResourceManager->LoadGraphics("Resource/kari10.png");
    CubeHandle[10] = Master::mpResourceManager->LoadGraphics("Resource/kari11.png");
    CubeHandle[11] = Master::mpResourceManager->LoadGraphics("Resource/kari12.png");
    /*CubeHandle[12] = Master::mpResourceManager->LoadGraphics("Resource/mato.png");
    CubeHandle[13] = Master::mpResourceManager->LoadGraphics("Resource/mato.png");
    CubeHandle[14] = Master::mpResourceManager->LoadGraphics("Resource/mato.png");
    CubeHandle[15] = Master::mpResourceManager->LoadGraphics("Resource/mato.png");
    CubeHandle[16] = Master::mpResourceManager->LoadGraphics("Resource/mato.png");
    CubeHandle[17] = Master::mpResourceManager->LoadGraphics("Resource/mato.png");
    CubeHandle[18] = Master::mpResourceManager->LoadGraphics("Resource/mato.png");
    CubeHandle[19] = Master::mpResourceManager->LoadGraphics("Resource/mato.png");*/

	StageNameHandle[0] = Master::mpResourceManager->LoadGraphics("Resource/文字/STAGEName0.png");
    StageNameHandle[1] = Master::mpResourceManager->LoadGraphics("Resource/文字/STAGEName0.png");
    StageNameHandle[2] = Master::mpResourceManager->LoadGraphics("Resource/文字/STAGEName0.png");
    StageNameHandle[3] = Master::mpResourceManager->LoadGraphics("Resource/文字/STAGEName0.png");
    StageNameHandle[4] = Master::mpResourceManager->LoadGraphics("Resource/文字/STAGEName0.png");
    StageNameHandle[5] = Master::mpResourceManager->LoadGraphics("Resource/文字/STAGEName0.png");
    StageNameHandle[6] = Master::mpResourceManager->LoadGraphics("Resource/文字/STAGEName0.png");
    StageNameHandle[7] = Master::mpResourceManager->LoadGraphics("Resource/文字/STAGEName0.png");
    StageNameHandle[8] = Master::mpResourceManager->LoadGraphics("Resource/文字/STAGEName0.png");
    StageNameHandle[9] = Master::mpResourceManager->LoadGraphics("Resource/文字/STAGEName0.png");
    StageNameHandle[10] = Master::mpResourceManager->LoadGraphics("Resource/文字/STAGEName0.png");
    StageNameHandle[11] = Master::mpResourceManager->LoadGraphics("Resource/文字/STAGEName0.png");


    STAGE = Master::mpResourceManager->LoadGraphics("Resource/文字/STAGE_W.png");
    NotOpenStageHandle = Master::mpResourceManager->LoadGraphics("Resource/文字/NotOpenStage_W.png");
    NUMBERHandle = Master::mpResourceManager->LoadGraphics("Resource/文字/NUMBER_W.png");

    NowSceneHandle = Master::mpResourceManager->LoadGraphics("Resource/文字/STAGE_SELECT_W.png");
    AButtonHandle = Master::mpResourceManager->LoadGraphics("Resource/AButton.png");
    BButtonHandle = Master::mpResourceManager->LoadGraphics("Resource/BButton.png");
    DecisionHandle = Master::mpResourceManager->LoadGraphics("Resource/文字/決定_W.png");
    BackHandle = Master::mpResourceManager->LoadGraphics("Resource/文字/戻る_W.png");

    // 
    return 0;
}

// 
int StageSelectScene::Initialize()
{
    // 
    LightColor = 0xFFF2CC;
    return 0;
}

// 
int StageSelectScene::Finalize()
{
    // 
    return 0;
}

// 
int StageSelectScene::Update()
{
    // 
    if (Master::mpKeyState->GetShadowGameKeyDown(KEY_SHADOW_GAME_TYPE::A, 0) ||
        Master::mpKeyState->GetShadowGameKeyDown(KEY_SHADOW_GAME_TYPE::A, 1))
    {
        bool moveTestScene = false;
        if (moveTestScene)
        {
            // 
            Master::mpBaseSceneManager->ChangeScene(SceneTag::ST_Test);

            // 
            this->OnResetFlag();
        }
        else
        {
            // 未開放のステージではなければ
            if(mnCurrentStage <= mnUnlockStageCount - 1)
            {
                // 選択したステージのシーンに遷移する
                Master::mpBaseSceneManager->ChangeScene(BasePuzzleScene::StageNum2SceneTag(this->mnCurrentStage));
				LightColor = 0xFF4747; // ライトの色を変える
                this->OnResetFlag();
            }
        }
    }

    // 
    if (Master::mpKeyState->GetShadowGameKeyDown(KEY_SHADOW_GAME_TYPE::B, 0) ||
        Master::mpKeyState->GetShadowGameKeyDown(KEY_SHADOW_GAME_TYPE::B, 1))
    {
        // 
        Master::mpBaseSceneManager->ChangeScene(SceneTag::ST_Title);
        // 
        this->OnResetFlag();
    }

    // 
    const signed long baseCount = +100;

    // 
    const unsigned long pushHoldFrameMax = +3;

    // 
    bool push = false;

    // 
    int stageMove = 0;

    // 
    Master::mpCursorMoveSupporter->Move(this->mdMoveData, stageMove);


    // 
    if (stageMove != 0 && MoveCount == 0)
    {
        // 
        this->mnCurrentStage += this->StageMax;

        // 
        this->mnCurrentStage += stageMove;

        // 
        this->mnCurrentStage %= this->StageMax;

        MoveDirection = stageMove;

		// ステージを移動させる
        for (StageNum = 0; StageNum < StageMax; StageNum++)
        {
            CubeStage[StageNum] += MoveDirection;
            // 超えたら戻す
            if (CubeStage[StageNum] > StageMax - 1)
            {
                CubeStage[StageNum] -= StageMax;
            }
            else if (CubeStage[StageNum] < 0)
            {
                CubeStage[StageNum] += StageMax;
            }

        }
        MoveCount = 10;
    }

	// 10フレームかけて移動させる
    if (MoveCount > 0)
    {
        MoveCount--;

        for (StageNum = 0; StageNum < StageMax; StageNum++)
        {
            if (MoveDirection == 1)// 進める
            {
                if (StageNum == CubeStage[(StageMax / 2) - 1])
                {
                    //CubeSize[StageNum] = 150 - (70 * ((StageMax / 2) - 1));
                    CubeX[StageNum] = Interval * ((StageMax / 2) - 1);
                }
                else
                {
                    //CubeSize[StageNum] += 7;
                    CubeX[StageNum] -= Interval / 10;
                }
            }

            if (MoveDirection == -1)// 戻す
            {
                if (StageNum == CubeStage[StageMax / 2])
                {
                    CubeX[StageNum] = -Interval * (StageMax / 2);
                }
                else
                {
                    //CubeSize[StageNum] -= 7;
                    CubeX[StageNum] += Interval / 10;

                }
            }
        }

    }

    // 
    return 0;
}

// 
int StageSelectScene::Draw()
{
	DrawExtendGraph(20, 20, 520, 70, NowSceneHandle, true);

    // 未開放のステージではなければスポットライトで照らす
    if (mnCurrentStage <= mnUnlockStageCount - 1)
    {
        DrawTriangle(960, -100, 660, 880, 1260, 880, LightColor, true);
        DrawOval(960, 880, 300, 90, LightColor, true);
        DrawExtendGraph(840, 275, 1340, 325, STAGE, true);
        if (mnCurrentStage < 9)// ステージ番号
        {
            DrawRectExtendGraph(1020, 275, 1070, 325, ((mnCurrentStage + 1) * 128), 0, 128, 128, NUMBERHandle, true);
        }
        else
        {
            DrawRectExtendGraph(1020, 275, 1070, 325, (((mnCurrentStage + 1) / 10) % 10 * 128), 0, 128, 128, NUMBERHandle, true);
            DrawRectExtendGraph(1050, 275, 1100, 325, (((mnCurrentStage + 1) / 1 ) % 10 * 128), 0, 128, 128, NUMBERHandle, true);
        }
        DrawExtendGraph(710, 375, 1210, 425, StageNameHandle[mnCurrentStage], true);
    }
    else //未開放なら文言だけ表示
    {
        DrawExtendGraph(740, 300, 1240, 350, NotOpenStageHandle, true);
    }


    for (StageNum = 0; StageNum < StageMax; StageNum++)
    {
        // ステージ画像表示
        DxLib::DrawExtendGraph(
            960 + CubeX[StageNum] - CubeSize[StageNum],
            300 + CubeY[StageNum] - CubeSize[StageNum],
            960 + CubeX[StageNum] + CubeSize[StageNum],
            300 + CubeY[StageNum] + CubeSize[StageNum],
            CubeHandle[StageNum],
            true);
        // スポットライトの影
        DrawOval(960 + CubeX[StageNum], 880, 150, 50, 0x000000, true);
    }

    for (StageNum = 0; StageNum < StageMax; StageNum++)
    {
        if (mnCurrentStage == StageNum)
        {
            DrawCircle(100 + StageNum * 30, 1000, 10, 0xFFFFFF, true);
        }
        else
        {
			DrawCircle(100 + StageNum * 30, 1000, 10, 0x777777, true);
        }
    }

    

	// Aボタンの表示
    DxLib::DrawExtendGraph(
        1500,1000,
        1540,1040,
        AButtonHandle,
        true); 

    // Aボタンの説明表示
    DxLib::DrawExtendGraph(
        1570,1000,
        1630,1030,
        DecisionHandle,
        true);

    // Bボタンの表示
    DxLib::DrawExtendGraph(
        1700,1000,
        1740,1040,
        BButtonHandle,
        true);

    // Bボタンの説明表示
    DxLib::DrawExtendGraph(
        1770,1000,
        1830,1030,
        BackHandle,
        true);


    /*{

        // 
        DRAW_SYSTEM::DrawString(
            VECTOR2D(0, 0),
            "STAGE SELECT SCENE",
            GetColor(255, 255, 255));

        // 
        std::string message = "Unlock Stage Count : " + std::to_string(this->mnUnlockStageCount);

        // 
        DRAW_SYSTEM::DrawString(
            VECTOR2D(400, 150 * 1),
            message.c_str(),
            GetColor(255, 255, 255));

        // 
        message = "Current Select Stage : " + std::to_string(this->mnCurrentStage);

        // 
        DRAW_SYSTEM::DrawString(
            VECTOR2D(400, 150 * 2),
            message.c_str(),
            GetColor(255, 255, 255));

        // 
        message = "Title (Pless B Key)";

        // 
        DRAW_SYSTEM::DrawString(
            VECTOR2D(400, 150 * 3),
            message.c_str(),
            GetColor(255, 255, 255));
    }
    */




    // 
    return 0;
}
