#include "StageSelectScene.h"

#include "DxLib.h"

#include <string>

#include "../E_Scene/BaseSceneManager.h"
#include "../H_Katou/Singleton/KeyState.h"
#include "../Z_Except/Master.h"

// 
StageSelectScene::StageSelectScene() :
    mnCurrentStage(0),
    mnUnlockStageCount(1),
    mdMoveData(),
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
    element.mnTargetKey = KEY_SHADOW_GAME_TYPE::UP;
    element.mnMoveVec = -1;
    this->mdMoveData.Add(element);

    // 
    element.mnTargetKey = KEY_SHADOW_GAME_TYPE::DOWN;
    element.mnMoveVec = +1;
    this->mdMoveData.Add(element);

    // 
    return 0;
}

// 
int StageSelectScene::Initialize()
{
    // 
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
    if (Master::mpKeyState->GetShadowGameKey(KEY_SHADOW_GAME_TYPE::A, 0) ||
        Master::mpKeyState->GetShadowGameKey(KEY_SHADOW_GAME_TYPE::A, 1))
    {
        // 
        Master::mpBaseSceneManager->ChangeScene(SceneTag::ST_Test);

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
    if (stageMove != 0)
    {
        // 
        this->mnCurrentStage += this->mnUnlockStageCount;

        // 
        this->mnCurrentStage += stageMove;

        // 
        this->mnCurrentStage %= this->mnUnlockStageCount;
    }

    // 
    return 0;
}

// 
int StageSelectScene::Draw()
{
    // 
    DxLib::DrawString(
        0,
        0,
        "STAGE SELECT SCENE",
        GetColor(255, 255, 255));

    // 
    std::string message = "Unlock Stage Count : " + std::to_string(this->mnUnlockStageCount);

    // 
    DxLib::DrawString(
        150 * 1,
        400,
        message.c_str(),
        GetColor(255, 255, 255));

    // 
    message = "Current Select Stage : " + std::to_string(this->mnCurrentStage);

    // 
    DxLib::DrawString(
        150 * 2,
        400,
        message.c_str(),
        GetColor(255, 255, 255));

    // 
    return 0;
}
