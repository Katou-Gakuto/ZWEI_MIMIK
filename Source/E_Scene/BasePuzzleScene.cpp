#include "BasePuzzleScene.h"

#include "DxLib.h"

#include <string>

#include "../A_GameObject/GameObject2D.h"
#include "../A_GameObject/GameObjectManager.h"
#include "../A_GameObject/PlayerObject.h"
#include "../A_GameObject/GoalObject.h"
#include "../C_Component/Player.h"
#include "../C_Component/GoalObjectController.h"
#include "../G_LightArea/LightAreaManager.h"
#include "../S_Collision/BaseCollision2DManager.h"
#include "../E_Scene/BaseSceneManager.h"
#include "../H_Katou/Singleton/KeyState.h"
#include "../Y_Tool/VECTOR.h"
#include "../Y_Tool/MyEasing.h"
#include "../Z_Except/ResourceManager.h"
#include "../Z_Except/Master.h"
#include "DrawSystem.h"
// 
//#include "MallocData.h"
//#include "LightObject.h"
//#include "GimmickObjectController.h"
CursorMoveData BasePuzzleScene::smdMoveData;

BasePuzzleScene::BasePuzzleScene(SceneTag tag) :
    mpPlayerLight(nullptr),
    mpPlayerShadow(nullptr),
    mpGoalLight(nullptr),
    mpGoalShadow(nullptr),
    mbPouse(false),
    mbGoal(false),
    mbFailed(false),
    mnPouseCursorPos(0),
    mnResultCursorPos(1),
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
    CursorMoveElement newElement2;

    // 
    newElement.mnTargetKey = KEY_SHADOW_GAME_TYPE::UP;
    newElement.mnMoveVec = -1;
    smdMoveData.Add(newElement);

    // 
    newElement.mnTargetKey = KEY_SHADOW_GAME_TYPE::DOWN;
    newElement.mnMoveVec = +1;
    smdMoveData.Add(newElement);


    newElement.mnTargetKey = KEY_SHADOW_GAME_TYPE::RIGHT;
    newElement.mnMoveVec = +2;
    smdMoveData.Add(newElement);

    // 
    newElement.mnTargetKey = KEY_SHADOW_GAME_TYPE::LEFT;
    newElement.mnMoveVec = -2;
    smdMoveData.Add(newElement);

    // 
    this->mpGameObjectManager = new GameObjectManager();
    this->mpBaseCollision2DManager = new BaseCollision2DManager();    

    // 
    Master::mpLightManager->ResizeArea(this->GetUseLightAreaCount());

    // それぞれのマップを生成する
    this->MapCreate(*this->mpGameObjectManager);

    // 
    this->CreateAndAddMastObject();

    // 
    return 0;
}

int BasePuzzleScene::Initialize()
{
    // 
    Master::mpLightManager->ResizeArea(this->GetUseLightAreaCount());

    // 
    VECTOR2D initPosBox[4];
    this->GetMasterObjectsInitPos(initPosBox[0], initPosBox[1], initPosBox[2], initPosBox[3]);

    // 
    this->mpPlayerLight->InitPosition(initPosBox[0]);
    this->mpPlayerShadow->InitPosition(initPosBox[1]);
    this->mpGoalLight->InitPosition(initPosBox[2]);
    this->mpGoalShadow->InitPosition(initPosBox[3]);

    // 
    this->mpGameObjectManager->Initialize();

    // 
    this->mbPouse = false;

    // 
    this->mbGoal = false;

    // 
    this->mbFailed = false;


	this->ResultAnimCount = -10;



    PoseHandle = Master::mpResourceManager->LoadGraphics("Resource/文字/PAUSE_W.png");
    OptionHandle = Master::mpResourceManager->LoadGraphics("Resource/文字/OPTION_W.png");
    RetryHandle = Master::mpResourceManager->LoadGraphics("Resource/文字/RETRY_W.png");
    StageSelectHandle = Master::mpResourceManager->LoadGraphics("Resource/文字/STAGE_SELECT_W.png");
    TitleHandle = Master::mpResourceManager->LoadGraphics("Resource/文字/TITLE_W.png");

    ResultHandle = Master::mpResourceManager->LoadGraphics("Resource/文字/CLEAR_W.png");
    NextStageHandle = Master::mpResourceManager->LoadGraphics("Resource/文字/NEXT_STAGE_W.png");


    AButtonHandle = Master::mpResourceManager->LoadGraphics("Resource/AButton.png");
    BButtonHandle = Master::mpResourceManager->LoadGraphics("Resource/BButton.png");
    DecisionHandle = Master::mpResourceManager->LoadGraphics("Resource/文字/決定_W.png");
    BackHandle = Master::mpResourceManager->LoadGraphics("Resource/文字/戻る_W.png");

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
    if (this->mbFailed)
    {
        // 
        return this->FailedUpdate();
    }
    // 
    if (this->mbGoal)
    {
        // 
        return this->ResultUpdate();
    }

    // 
    this->mbFailed = 
        this->mpPlayerLight->GetInLightArea() == false ||
        this->mpPlayerShadow->GetInLightArea() == true;
    // this->mbFailed = false;
    if (this->mbFailed)
    {
        // 
        return this->FailedUpdate();
    }

    // 
    this->mbGoal = this->mpGoalLight->GetInPlayer() && this->mpGoalShadow->GetInPlayer();

#ifdef _DEBUG //マージするときここはしなくてもいい

    if (Master::mpKeyState->GetShadowGameKeyDown(KEY_SHADOW_GAME_TYPE::X, 0))
    {
        mbGoal = true;
    }

#endif

    if (this->mbGoal)
    {
        // 
        return this->ResultUpdate();
    }

    // ポーズ画面に移行するボタンを押している場合は処理を行う
    if (Master::mpKeyState->GetShadowGameKeyDown(KEY_SHADOW_GAME_TYPE::B, 0) ||
        Master::mpKeyState->GetShadowGameKeyDown(KEY_SHADOW_GAME_TYPE::B, 1))
    {
        // 
        this->mbPouse = !this->mbPouse;

        // 
        this->mnPouseCursorPos = 0;
    }



    // 
    if (this->mbPouse)
    {
        return this->PouseUpdate();
    }

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

    // 成功を返す
    return 0;
}

int BasePuzzleScene::Draw()
{
    /*
    DRAW_SYSTEM::DrawString(
        VECTOR2D(0, 0),
        "BASE PUZZLE SCENE",
        GetColor(255, 255, 255));
        */

    // 
    this->mpGameObjectManager->Draw();



	Master::mpLightManager->Draw();
    // 
    if (this->mbGoal)
    {
        // 
        this->ResultDraw();
    }

    // 
    if (this->mbFailed)
    {
        // 
        this->FailedDraw();
    }

	// ポーズならポーズメニューを描画する
    if (this->mbPouse)
    {
        // 
        this->PouseDraw();
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
    case 9:
        temp = SceneTag::ST_Puzzle1_10;
        break;

    default:
        break;
    }

    // 
    return temp;
}

// 
unsigned long BasePuzzleScene::SceneTag2StageNum(SceneTag sceneTag)
{
    // 
    unsigned long temp = 0;
    switch (sceneTag)
    {
    case SceneTag::ST_Puzzle1_1:
        temp = 0;
        break;
    case SceneTag::ST_Puzzle1_2:
        temp = 1;
        break;
    case SceneTag::ST_Puzzle1_3:
        temp = 2;
        break;
    case SceneTag::ST_Puzzle1_4:
        temp = 3;
        break;
    case SceneTag::ST_Puzzle1_5:
        temp = 4;
        break;
    case SceneTag::ST_Puzzle1_6:
        temp = 5;
        break;
    case SceneTag::ST_Puzzle1_7:
        temp = 6;
        break;
    case SceneTag::ST_Puzzle1_8:
        temp = 7;
        break;
    case SceneTag::ST_Puzzle1_9:
        temp = 8;
        break;
    case SceneTag::ST_Puzzle1_10:
        temp = 9;
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
void BasePuzzleScene::CreateAndAddMastObject()
{
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

    // 
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
        switch (this->mnPouseCursorPos)
        {
        case PouseMenu::PouseMenu_Option:
            Master::mpBaseSceneManager->ChangeScene(SceneTag::ST_Option);
            Master::mpBaseSceneManager->SetResreveScene(this->GetTag());
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
    if (menuMove == 1 || menuMove == -1)
    {
        // 
        this->mnPouseCursorPos += PouseMenu::PouseMenu_Max;

        // 
        this->mnPouseCursorPos += menuMove;

        // 
        this->mnPouseCursorPos %= PouseMenu::PouseMenu_Max;
    }

    // 
    return 0;
}

// 
int BasePuzzleScene::PouseDraw()
{
    // 背景を暗くする
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
    DrawBox(0, 0, 1920, 1080, 0x000000, true);
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

    DrawExtendGraph(875, 170, 1375, 220, PoseHandle, true);
    DrawBox(0, 299, 1920, 301, 0xEEE2CC,true);
    // 選択中の表示
    switch (this->mnPouseCursorPos)
    {
    case PouseMenu::PouseMenu_Option:
        DrawBox(750, 400, 1170, 482, 0xEEE2CC, true);
        break;
    case PouseMenu::PouseMenu_Retry:
        DrawBox(750, 550, 1170, 632, 0xEEE2CC, true);
        break;
    case PouseMenu::PouseMenu_StageSelect:
        DrawBox(750, 700, 1170, 782, 0xEEE2CC, true);
        break;
    case PouseMenu::PouseMenu_Title:
        DrawBox(750, 850, 1170, 932, 0xEEE2CC, true);
        break;
    }

    DrawExtendGraph(860, 420, 1360, 470, OptionHandle, true);
    DrawExtendGraph(870, 570, 1370, 620, RetryHandle, true);
    DrawExtendGraph(780, 720, 1280, 770, StageSelectHandle, true);
    DrawExtendGraph(890, 870, 1390, 920, TitleHandle, true);

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


    /*
    {
        // 
        DRAW_SYSTEM::DrawString(
            VECTOR2D(500, 60 + 120 * 0),
            "POUSE MENU",
            GetColor(255, 255, 255));

        // 
        std::string message;

        // 
        for (int i = 0; i < PouseMenu::PouseMenu_Max; i++)
        {
            // 
            if (this->mnPouseCursorPos == i)
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
            DRAW_SYSTEM::DrawString(
                VECTOR2D(400, 120 + 120 * i),
                message.c_str(),
                GetColor(255, 255, 255));
        }
        
    }*/
    // 
    return 0;
}

// 
int BasePuzzleScene::ResultUpdate()
{
    // リザルトシーンって、どういう機能を持たせたい？
    // RETRYとか、STAGE SELECTとかそういうの
    // 

    // 
    if (ResultAnimCount > 30)
    {
        if (Master::mpKeyState->GetShadowGameKeyDown(KEY_SHADOW_GAME_TYPE::A, 0) ||
            Master::mpKeyState->GetShadowGameKeyDown(KEY_SHADOW_GAME_TYPE::A, 1))
        {
            // 
            unsigned long temp = 0;

            // 
            switch (this->mnResultCursorPos)
            {
            case ResultMenu::ResultMenu_NextStage:
                temp = BasePuzzleScene::SceneTag2StageNum(this->GetTag());

                Master::mpBaseSceneManager->ChangeScene(BasePuzzleScene::StageNum2SceneTag(temp + 1));
                this->OnResetFlag();
                break;
            case ResultMenu::ResultMenu_StageSelect:
                Master::mpBaseSceneManager->ChangeScene(SceneTag::ST_StageSelect);
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
        if (menuMove == 2 || menuMove == -2)
        {
            // 
            this->mnResultCursorPos += ResultMenu::ResultMenu_Max;

            // 
            this->mnResultCursorPos += menuMove / 2;

            // 
            this->mnResultCursorPos %= ResultMenu::ResultMenu_Max;
        }
    }
    else
    {
		ResultAnimCount++;
    }

    // 
    return 0;
}

// 
int BasePuzzleScene::ResultDraw()
{

    // 背景を暗くする
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
    DrawBox(0, 0, 1920, 1080, 0x000000, true);
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

    DrawTriangle(
        1400, -200,
        1400 - (ResultAnimCount * 100), -200 + (ResultAnimCount * 60),
        1400 + (ResultAnimCount * 10 ), -200 + (ResultAnimCount * 60), 0xEEE2CC, true);

    if (ResultAnimCount > 30)
    {
        DrawExtendGraph(875, 370, 1375, 420, ResultHandle, true);
        //DrawBox(0, 299, 1920, 301, 0xEEE2CC, true);

        switch (this->mnResultCursorPos)
        {
        case ResultMenu::ResultMenu_StageSelect:
            DrawBox(350, 860, 770, 930, 0x333333, true);
            break;
        case ResultMenu::ResultMenu_NextStage:
            DrawBox(1150, 860, 1515, 930, 0x333333, true);
            break;
        }

        DrawExtendGraph(375, 870, 875, 920, StageSelectHandle, true);
        DrawExtendGraph(1175, 870, 1675, 920, NextStageHandle, true);
    }

    // Aボタンの表示
    DxLib::DrawExtendGraph(
        1700, 1000,
        1740, 1040,
        AButtonHandle,
        true);

    // Aボタンの説明表示
    DxLib::DrawExtendGraph(
        1770, 1000,
        1830, 1030,
        DecisionHandle,
        true);

    /*{
    // 
    DRAW_SYSTEM::DrawString(
        VECTOR2D(500, 60),
        "STAGE CLEAR!",
        GetColor(255, 255, 255));

    // 
    std::string message = "";

    // 
    for (uint64_t i = 0; i < ResultMenu::ResultMenu_Max; i++)
    {
        // 
        if (this->mnResultCursorPos == i)
        {
            message = "⇒";
        }
        else
        {
            message = "　";
        }

        // 
        switch (i)
        {
        case ResultMenu::ResultMenu_NextStage:
            message += "NEXT STAGE";
            break;
        case ResultMenu::ResultMenu_StageSelect:
            message += "STAGE SELECT";
            break;
        default:
            message += "ERROR";
            break;
        }

        // 
        DRAW_SYSTEM::DrawString(
            VECTOR2D(450, 60 + 120 * (i + 1)),
            message.c_str(),
            GetColor(255, 255, 255));
    }
    }*/
    // 
    return 0;
}

// 
int BasePuzzleScene::FailedUpdate()
{
    // とりあえず強制RETRY
    Master::mpBaseSceneManager->ChangeScene(this->GetTag());
    this->OnResetFlag();

    // 
    return 0;
}

// 
int BasePuzzleScene::FailedDraw()
{
    // 
    return 0;
}
