#include "PuzzleScene.h"

#include "DxLib.h"

#include <string>

#include "../A_GameObject/GameObject2D.h"
#include "../A_GameObject/GameObjectManager.h"
#include "../A_GameObject/PlayerObject.h"
#include "../A_GameObject/GoalObject.h"
#include "../C_Component/Player.h"
#include "../C_Component/GoalObjectController.h"
#include "../S_Collision/BaseCollision2DManager.h"
#include "../E_Scene/BaseSceneManager.h"
#include "../H_Katou/Singleton/KeyState.h"
#include "../Y_Tool/VECTOR.h"
#include "../Z_Except/Master.h"

// 
CursorMoveData BasePuzzleScene::smdMoveData;

BasePuzzleScene::BasePuzzleScene(SceneTag tag) :
    mpPlayerLight(nullptr),
    mpPlayerShadow(nullptr),
    mpGoalLight(nullptr),
    mpGoalShadow(nullptr),
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

    // 
    GameObject2D *currentObject = nullptr;
    currentObject = new PlayerObject(1);
    currentObject->Initialize();
    currentObject->Finalize();
    this->mpPlayerLight = (static_cast<PlayerObject *>(currentObject))->GetPlayerComponent();

    currentObject = new PlayerObject(2);
    currentObject->Initialize();
    currentObject->Finalize();
    this->mpPlayerShadow = (static_cast<PlayerObject *>(currentObject))->GetPlayerComponent();

    currentObject = new GoalObject(true);
    currentObject->Initialize();
    currentObject->Finalize();
    this->mpGoalLight = (static_cast<GoalObject *>(currentObject))->GetGoalController();

    currentObject = new GoalObject(false);
    currentObject->Initialize();
    currentObject->Finalize();
    this->mpGoalShadow = (static_cast<GoalObject *>(currentObject))->GetGoalController();

    // それぞれのマップを生成する
    this->MapCreate(*this->mpGameObjectManager);

    // 
    return 0;
}

int BasePuzzleScene::Initialize()
{
    // 
    VECTOR2D initPosBox[4];
    this->GetMasterObjectsInitPos(initPosBox[0], initPosBox[1], initPosBox[2], initPosBox[3]);

    // 
    this->mpPlayerLight->InitPosition(initPosBox[0]);
    this->mpPlayerShadow->InitPosition(initPosBox[1]);
    this->mpGoalLight->InitPosition(initPosBox[2]);
    this->mpGoalShadow->InitPosition(initPosBox[3]);

    // 
    this->AddMasterObjects();

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
    if (this->mpGameObjectManager != nullptr)
    {
        // 
        this->mpGameObjectManager->Finalize();
    }

    // 
    return 0;
}

int BasePuzzleScene::Update()
{
    // 
    if (this->mpPlayerLight->CheckGoal() &&
        this->mpPlayerShadow->CheckGoal())
    {
        // 
        Master::mpBaseSceneManager->ChangeScene(SceneTag::ST_StageSelect);

        // 
        this->OnResetFlag();

        // 
        return 0;
    }

    // ポーズ画面に移行するボタンを押している場合は処理を行う
    if (Master::mpKeyState->GetShadowGameKeyDown(KEY_SHADOW_GAME_TYPE::B, 0) ||
        Master::mpKeyState->GetShadowGameKeyDown(KEY_SHADOW_GAME_TYPE::B, 1))
    {
        // 
        this->mbPouse = !this->mbPouse;
    }

    // 
    if (this->mbPouse)
    {
        this->PouseUpdate();
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

	// ポーズならポーズメニューを描画する
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
            message += " ";

            // 
            switch (i)
            {
            case PouseMenu::PouseMenu_Option:
                message += "OPTION";
                break;
            case PouseMenu::PouseMenu_Retry:
                message += "RETRY";
                break;
            case PouseMenu::PouseMenu_StageSelect:
                message += "STAGE SELECT";
                break;
            case PouseMenu::PouseMenu_Title:
                message += "TITLE";
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

// 
SceneTag BasePuzzleScene::StageNum2SceneTag(unsigned long stageNum)
{
    // 
    SceneTag temp = SceneTag::ST_Max;
    switch (stageNum)
    {
    case 0:
        temp = SceneTag::ST_Puzzle1_1;
        break;
    case 1:
        temp = SceneTag::ST_Puzzle1_2;
        break;
    case 2:
        temp = SceneTag::ST_Puzzle1_3;
        break;
    case 3:
        temp = SceneTag::ST_Puzzle1_4;
        break;
    case 4:
        temp = SceneTag::ST_Puzzle1_5;
        break;
    case 5:
        temp = SceneTag::ST_Puzzle1_6;
        break;
    case 6:
        temp = SceneTag::ST_Puzzle1_7;
        break;
    case 7:
        temp = SceneTag::ST_Puzzle1_8;
        break;
    case 8:
        temp = SceneTag::ST_Puzzle1_9;
        break;

    default:
        break;
    }

    // 
    return temp;
}

// 
Player *BasePuzzleScene::GetPlayer(int playerNumber)const
{
    if (playerNumber == 1)
    {
        // 
        return this->mpPlayerLight;
    }

    return this->mpPlayerShadow;
}

// 
GoalObjectController *BasePuzzleScene::GetGoal(bool lightSide)const
{
    if (lightSide == 1)
    {
        // 
        return this->mpGoalLight;
    }

    return this->mpGoalShadow;
}

// 
void BasePuzzleScene::AddMasterObjects()
{
    this->mpGameObjectManager->Add(this->mpPlayerLight->GetMyObject());
    this->mpGameObjectManager->Add(this->mpPlayerShadow->GetMyObject());
    this->mpGameObjectManager->Add(this->mpGoalLight->GetMyObject());
    this->mpGameObjectManager->Add(this->mpGoalShadow->GetMyObject());
}

// 
int BasePuzzleScene::PouseUpdate()
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

    // 
    return 0;
}