#include "PuzzleScene.h"

#include "DxLib.h"

#include <string>

#include "../A_GameObject/GameObject2D.h"
#include "../A_GameObject/GameObjectManager.h"
#include "../A_GameObject/PlayerObject.h"
#include "../C_Component/Player.h"
#include "../S_Collision/BaseCollision2DManager.h"
#include "../E_Scene/BaseSceneManager.h"
#include "../H_Katou/Singleton/KeyState.h"
#include "../Z_Except/Master.h"

// 
CursorMoveData BasePuzzleScene::smdMoveData;

BasePuzzleScene::BasePuzzleScene(SceneTag tag) :
    mbPouse(false),
    mnCursorPos(0),
    BaseScene(tag)
{
}

BasePuzzleScene::~BasePuzzleScene()
{
}

int BasePuzzleScene::Create()
{
    // 
    CursorMoveElement newElement;

    // 
    newElement.mnTargetKey = KEY_SHADOW_GAME_TYPE::UP;
    newElement.mnMoveVec = -1;
    smdMoveData.Add(newElement);

    // 
    newElement.mnTargetKey = KEY_SHADOW_GAME_TYPE::DOWN;
    newElement.mnMoveVec = +1;
    smdMoveData.Add(newElement);

    // 
    this->mpGameObjectManager = new GameObjectManager();
    this->mpBaseCollision2DManager = new BaseCollision2DManager();    
    
    this->mpGameObjectManager->Add(Master::mpPlayerLight->GetMyObject());
    this->mpGameObjectManager->Add(Master::mpPlayerShadow->GetMyObject());

    // 
    this->MapCreate();

    // 
    return 0;
}

int BasePuzzleScene::Initialize()
{
    // 
    this->mpGameObjectManager->Initialize();

    // 
    this->mbPouse = false;

    // 
    return 0;
}

int BasePuzzleScene::Finalize()
{
    // 
    this->mpGameObjectManager->Finalize();

    // 
    return 0;
}

int BasePuzzleScene::Update()
{
    // ポーズ画面に移行するボタンを押している場合は処理を行う
    if (Master::mpKeyState->GetShadowGameKeyDown(KEY_SHADOW_GAME_TYPE::B, 0))
    {
        // 
        this->mbPouse = !this->mbPouse;
    }

    // 
    if (this->mbPouse)
    {
        // 
        if (Master::mpKeyState->GetShadowGameKeyDown(KEY_SHADOW_GAME_TYPE::A, 0) ||
            Master::mpKeyState->GetShadowGameKeyDown(KEY_SHADOW_GAME_TYPE::A, 1))
        {
            // 
            switch (this->mnCursorPos)
            {
            case PouseMenu::PouseMenu_Option:
                Master::mpBaseSceneManager->ChangeScene(SceneTag::ST_Option);
                break;
            case PouseMenu::PouseMenu_Retry:
                Master::mpBaseSceneManager->ChangeScene(this->GetTag());
                this->OnResetFlag();
                break;
            case PouseMenu::PouseMenu_StageSelect:
                Master::mpBaseSceneManager->ChangeScene(SceneTag::ST_StageSelect);
                this->OnResetFlag();
                break;
            case PouseMenu::PouseMenu_Title:
                Master::mpBaseSceneManager->ChangeScene(SceneTag::ST_Title);
                this->OnResetFlag();
                break;
            default:
                // 何もしない
                break;
            }
        }

        // 
        int menuMove = 0;

        // 
        Master::mpCursorMoveSupporter->Move(this->smdMoveData, menuMove);

        // 
        if (menuMove != 0)
        {
            // 
            this->mnCursorPos += PouseMenu::PouseMenu_Max;

            // 
            this->mnCursorPos += menuMove;

            // 
            this->mnCursorPos %= PouseMenu::PouseMenu_Max;
        }
    }
    else
    {
        // ここでMoveVecを0にしておく
        this->mpGameObjectManager->ResetMoveVec();

        // 先にやりたい処理
        this->mpGameObjectManager->EarlyUpdate();

        // 通常処理
        this->mpGameObjectManager->Update();

        // 当たり判定の計算 + スライド移動 + 当たり判定のイベント通知
        this->mpBaseCollision2DManager->CheckHitAllMove();

        // ゲームオブジェクトの座標を更新
        this->mpGameObjectManager->SetPositionToMoveVec();

        // 当たり判定の座標を更新
        this->mpGameObjectManager->SetCollisionPosToCollisionMoveVec();

        // 座標更新後の処理
        this->mpGameObjectManager->LateUpdate();

        // モデルの更新処理
        this->mpGameObjectManager->UpdateModel();
    }

    // 成功を返す
    return 0;
}

int BasePuzzleScene::Draw()
{
    // 
    DxLib::DrawString(
        0,
        0,
        "BASE PUZZLE SCENE",
        GetColor(255, 255, 255));

    // 
    this->mpGameObjectManager->Draw();

    // 
    if (this->mbPouse)
    {
        // 
        DxLib::DrawString(
            500,
            60 + 120 * 0,
            "POUSE MENU",
            GetColor(255, 255, 255));

        // 
        std::string message;

        // 
        for (int i = 0; i < PouseMenu::PouseMenu_Max; i++)
        {
            // 
            if (this->mnCursorPos == i)
            {
                message = "⇒";
            }
            else
            {
                message = "　";
            }

            // 
            message = " ";

            // 
            switch (i)
            {
            case PouseMenu::PouseMenu_Option:
                message = "OPTION";
                break;
            case PouseMenu::PouseMenu_Retry:
                message = "RETRY";
                break;
            case PouseMenu::PouseMenu_StageSelect:
                message = "STAGE SELECT";
                break;
            case PouseMenu::PouseMenu_Title:
                message = "TITLE";
                break;
            default:
                message += "bgbgbgbgbgbgbgbgbgbgbg";
                break;
            }

            // 
            DxLib::DrawString(
                400,
                60 + 120 * i,
                message.c_str(),
                GetColor(255, 255, 255));
        }
    }

    // 
    return 0;
}
