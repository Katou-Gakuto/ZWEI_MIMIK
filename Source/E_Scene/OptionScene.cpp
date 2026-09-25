#include "OptionScene.h"

#include "DxLib.h"

#include "BaseSceneManager.h"

#include "../H_Katou/Singleton/KeyState.h"

#include "../Z_Except/Master.h"

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
    return 0;
}

int OptionScene::Initialize()
{
    // 
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
    if (Master::mpKeyState->GetShadowGameKey(KEY_SHADOW_GAME_TYPE::X, 0) ||
        Master::mpKeyState->GetShadowGameKey(KEY_SHADOW_GAME_TYPE::X, 1))
    {
        // 
        Master::mpBaseSceneManager->ChangeSceneMySelf();

        // 
        this->OnResetFlag();
    }

    // 
    return 0;
}

int OptionScene::Draw()
{
    // 
    DxLib::DrawString(
        0,
        0,
        "OPTION SCENE",
        GetColor(255, 255, 255));

    // 
    DxLib::DrawString(
        400,
        400,
        "PRESS X KEY",
        GetColor(255, 255, 255));

    // 
    return 0;
}
