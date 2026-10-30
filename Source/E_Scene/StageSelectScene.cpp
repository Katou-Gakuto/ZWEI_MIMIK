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

    CubeHandle[0 ] = Master::mpResourceManager->LoadGraphics("Resource/kari1.png");
    CubeHandle[1 ] = Master::mpResourceManager->LoadGraphics("Resource/kari2.png");
    CubeHandle[2 ] = Master::mpResourceManager->LoadGraphics("Resource/kari3.png");
    CubeHandle[3 ] = Master::mpResourceManager->LoadGraphics("Resource/kari4.png");
    CubeHandle[4 ] = Master::mpResourceManager->LoadGraphics("Resource/kari5.png");
    CubeHandle[5 ] = Master::mpResourceManager->LoadGraphics("Resource/kari6.png");
    CubeHandle[6 ] = Master::mpResourceManager->LoadGraphics("Resource/kari7.png");
    CubeHandle[7 ] = Master::mpResourceManager->LoadGraphics("Resource/kari8.png");
    CubeHandle[8 ] = Master::mpResourceManager->LoadGraphics("Resource/kari9.png");
    CubeHandle[9 ] = Master::mpResourceManager->LoadGraphics("Resource/kari10.png");
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


    // 
    return 0;
}

// 
int StageSelectScene::Initialize()
{
    // 
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


    ChangeFlag = false;

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

		ChangeFlag = true;
        MoveDirection = stageMove;
    }

    // 
    return 0;
}

// 
int StageSelectScene::Draw()
{
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

    // 
    if(ChangeFlag)
    {
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

    if (MoveCount > 0)
    {
        MoveCount--;

        for (StageNum = 0; StageNum < StageMax; StageNum++)
        {
            if (MoveDirection == 1)// 進める
            {
                if (StageNum == CubeStage[(StageMax / 2) - 1] )
                {
                    //CubeSize[StageNum] = 150 - (70 * ((StageMax / 2) - 1));
                    CubeX[StageNum] = Interval * ((StageMax / 2) - 1);
                }
                else
                {
                    for (int i = 0; i < (StageMax / 2) - 1; i++)
                    {
                        /*if (CubeStage[i] == StageNum)
                            CubeSize[StageNum] += 7;
                        else
                            CubeSize[StageNum] -= 7;*/

                    }
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
                    CubeX[StageNum] += Interval/10;

                }
            }
        }

    }

    // 未開放のステージではなければスポットライトで照らす
    if (mnCurrentStage <= mnUnlockStageCount - 1)
    {
        DrawTriangle(960, -100, 660, 880, 1260, 880, 0xFFF2CC, true);
    }

    for (StageNum = 0; StageNum < StageMax; StageNum++)
    {
        DxLib::DrawExtendGraph(
            960 + CubeX[StageNum] - CubeSize[StageNum],
            300 + CubeY[StageNum] - CubeSize[StageNum],
            960 + CubeX[StageNum] + CubeSize[StageNum],
            300 + CubeY[StageNum] + CubeSize[StageNum],
            CubeHandle[StageNum],
            true);
    }

    




    // 
    return 0;
}
