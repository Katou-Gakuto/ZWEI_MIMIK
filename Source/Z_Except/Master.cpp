#include <Windows.h>

#include "Master.h"
#include "KeyState.h"
#include "EndManager.h"
#include "TimeManager.h"
#include "VECTOR.h"

#include "DxLibDataManager.h"

#include "ImguiManager.h"

#include "../A_GameObject/PlayerObject.h"
#include "../A_GameObject/GoalObject.h"
#include "../C_Component/Player.h"
#include "../C_Component/GoalObjectController.h"
#include "../G_LightArea/LightAreaManager.h"
#include "../E_Scene/BaseSceneManager.h"
#include "../E_Scene/BasePuzzleScene.h"
#include "../T_Model/DXModelAnim.h"
#include "../Z_Except/CursorMoveSupporter.h"
#include "../Z_Except/ResourceManager.h"
#include "../Z_Except/SoundManager.h"

#include "DrawSystem.h"

// 静的メンバーの初期化

BaseSceneManager *Master::mpBaseSceneManager = nullptr;

EndManager* Master::mpEndManager = nullptr;
TimeManager* Master::mpTimeManager = nullptr;
ResourceManager *Master::mpResourceManager = nullptr;
SoundManager *Master::mpSoundManager = nullptr;

KeyState* Master::mpKeyState = nullptr;
DxLibDataManager* Master::mpDxLibDataManager = nullptr;

ImguiManager* Master::mpImguiManager = nullptr;

LightAreaManager* Master::mpLightManager = nullptr;

CursorMoveSupporter *Master::mpCursorMoveSupporter = nullptr;

// 
Player *Master::GetPlayerController(int playerNumber)
{
    auto autoScene = mpBaseSceneManager->SearchSceneAuto();
    if (autoScene->GetTag() < SceneTag::ST_Puzzle1_1)
    {
        return nullptr;
    }

    return (static_cast<BasePuzzleScene *>(autoScene))->GetPlayer(playerNumber);
}

// 
GoalObjectController *Master::GetGoalController(bool lightSide)
{
    auto autoScene = mpBaseSceneManager->SearchSceneAuto();
    if (autoScene->GetTag() < SceneTag::ST_Puzzle1_1)
    {
        return nullptr;
    }

    return (static_cast<BasePuzzleScene *>(autoScene))->GetGoal(lightSide);
}

// DxLibの前の初期化
int Master::DxInitPreInitialize()
{
    // ウインドウモードで起動
    ChangeWindowMode(true);

    // ディスプレイの解像度を取得
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);
    mpDxLibDataManager = new DxLibDataManager(VECTOR2D(screenWidth, screenHeight));
    mpDxLibDataManager->DxInitPreInitialize();

    return 0;
}


// Masterの各メンバをnewする関数
int Master::Initialize()
{
    mpEndManager = new EndManager();
    mpTimeManager = new TimeManager(/*/1/*/17/**/);
    mpTimeManager->Initilize();
	mpResourceManager = new ResourceManager();
	mpSoundManager = new SoundManager();
    // mpDXAnimModel = new DXAnimModel();

    mpKeyState = new KeyState();
    // 

    mpCursorMoveSupporter = new CursorMoveSupporter;

    mpBaseSceneManager = new BaseSceneManager();
    mpBaseSceneManager->Initialize();

    mpLightManager = new LightAreaManager();
    mpLightManager->Initilize();

    // imguiマネージャー
    mpImguiManager = new ImguiManager(false);// 使うかどうかのフラグ
    mpImguiManager->Initilize();

    // ラストに初期化して
    mpDxLibDataManager->Initialize();
    return 0;
}

// Masterの各メンバをdeleteする関数
int Master::Finalize()
{
    mpBaseSceneManager->Finalize();

    // 
    mpImguiManager->Finalize();

    mpDxLibDataManager->Finalize();

    // 削除
    delete mpImguiManager;
    delete mpBaseSceneManager;
    delete mpEndManager;
    delete mpTimeManager;
	delete mpResourceManager;
	delete mpSoundManager;
    delete mpKeyState;
    delete mpDxLibDataManager;

    return 0;
}

// 画像を拡大/縮小し、UV座標を指定して描画する関数
int Master::DrawGraphAnim(
	const VECTOR2D &posLeftUp, const VECTOR2D &posRightDown,
	const VECTOR2D &uvLeftUp, const VECTOR2D &uvRightDown,
	int graphHandle)
{
	// プレイヤー画像描画
    DRAW_SYSTEM::DrawRectExtendGraph(posLeftUp, posRightDown, uvLeftUp, uvRightDown, graphHandle);

	return 0;
}
