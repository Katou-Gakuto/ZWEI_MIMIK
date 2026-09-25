#include "TitleScene.h"

#include "DxLib.h"

#include "BaseSceneManager.h"

#include "../H_Katou/Singleton/KeyState.h"

#include "../Z_Except/Master.h"

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
    return 0;
}

// 
int TitleScene::Initialize()
{
    // 
    this->mbLogoPhase = true;

    // 
    this->mnCurrentMode = TitleSelectMode::TitleSelectMode_StageSelect;

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

    // ƒ^ƒCƒgƒ‹‚Ìˆê”ÔÅ‰‚Ì‚â‚Â‚ð•`‰æ‚·‚é
    DxLib::DrawString(
        0.0f,
        0.0f,
        "TITLE SCENE\n",
        GetColor(255, 255, 255));

    // 
    if (this->mbLogoPhase)
    {
        // ƒ^ƒCƒgƒ‹‚Ìˆê”ÔÅ‰‚Ì‚â‚Â‚ð•`‰æ‚·‚é
        DxLib::DrawString(
            600,
            400,
            "   ZWEI MIMIK   \n"
            "                \n"
            "PRESS ANY BUTTON",
            GetColor(255, 255, 255));
    }
    else
    {
        // •`‰æ‚·‚é•¶Žš—ñ
        std::string message = "";

        // Œ»ÝEXIT‚ðŽw‚µ‚Ä‚¢‚éê‡‚Æ‘w‚Å‚È‚¢ê‡‚Åˆ—‚ð•Ï‚¦‚é
        if (this->mnCurrentMode == TitleSelectMode::TitleSelectMode_StageSelect)
        {
            // ‰E–îˆó‚ðÝ’è‚·‚é
            message = "Ë";
        }
        else
        {
            // –îˆó•ª‚Ì‹ó”’‚ðÝ’è‚·‚é
            message = "@";
        }

        // •¶Žš—ñ‚ð‚³‚ç‚É’Ç‰Á‚·‚é
        message += "STAGE SELECT";

        // •¶Žš—ñ‚ð•`‰æ‚·‚é
        DxLib::DrawString(
            400,
            200,
            message.c_str(),
            GetColor(255, 255, 255));

        // Œ»ÝEXIT‚ðŽw‚µ‚Ä‚¢‚éê‡‚Æ‘w‚Å‚È‚¢ê‡‚Åˆ—‚ð•Ï‚¦‚é
        if (this->mnCurrentMode == TitleSelectMode::TitleSelectMode_Option)
        {
            // ‰E–îˆó‚ðÝ’è‚·‚é
            message = "Ë";
        }
        else
        {
            // –îˆó•ª‚Ì‹ó”’‚ðÝ’è‚·‚é
            message = " ";
        }

        // •¶Žš—ñ‚ð‚³‚ç‚É’Ç‰Á‚·‚é
        message += "OPTION";

        // •¶Žš—ñ‚ð•`‰æ‚·‚é
        DxLib::DrawString(
            400,
            400,
            message.c_str(),
            GetColor(255, 255, 255));

        // Œ»ÝEXIT‚ðŽw‚µ‚Ä‚¢‚éê‡‚Æ‘w‚Å‚È‚¢ê‡‚Åˆ—‚ð•Ï‚¦‚é
        if (this->mnCurrentMode == TitleSelectMode::TitleSelectMode_Exit)
        {
            // ‰E–îˆó‚ðÝ’è‚·‚é
            message = "Ë";
        }
        else
        {
            // –îˆó•ª‚Ì‹ó”’‚ðÝ’è‚·‚é
            message = " ";
        }

        // 
        message += "EXIT";

        // •¶Žš—ñ‚ð•`‰æ‚·‚é
        DxLib::DrawString(
            400,
            600,
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
        // “K“–‚ÈƒL[‚ª‰Ÿ‚³‚ê‚Ä‚¢‚½‚çˆ—‚ðs‚¤
        if (Master::mpKeyState->GetShadowGameKey(KEY_SHADOW_GAME_TYPE::A, 0))
        {
            // 
            this->mbLogoPhase = false;

            // 
            this->mnCurrentMode = TitleSelectMode_StageSelect;
        }
    }
    else
    {
        // ª•ûŒü‚Ì“ü—Í‚ª‚³‚ê‚Ä‚¢‚é‚©
        bool currentUp = Master::mpKeyState->GetShadowGameKeyDown(KEY_SHADOW_GAME_TYPE::UP, 0);

        // ª•ûŒü‚Ì“ü—Í‚ª‚³‚ê‚Ä‚¢‚é‚©
        bool currentDown = Master::mpKeyState->GetShadowGameKeyDown(KEY_SHADOW_GAME_TYPE::DOWN, 0);

        // Œˆ’èƒ{ƒ^ƒ“‚ª‰Ÿ‚³‚ê‚Ä‚¢‚é‚©
        bool sceneMove = Master::mpKeyState->GetShadowGameKeyDown(KEY_SHADOW_GAME_TYPE::A, 0);

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

                // 
                Master::mpBaseSceneManager->SetResreveScene(SceneTag::ST_Title);
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
                    this->mnCurrentMode = TitleSelectMode::TitleSelectMode_Option;
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
