#include "Master.h"
#include "KeyState.h"
#include "EndManager.h"
#include "TimeManager.h"
#include "VECTOR.h"

#include "DxLibDataManager.h"

#include "ImguiManager.h"

#include "../A_GameObject/PlayerObject.h"
#include "../C_Component/Player.h"
#include "../G_LightArea/LightAreaManager.h"
#include "../E_Scene/BaseSceneManager.h"
#include "../T_Model/DXModelAnim.h"
#include "../Z_Except/CursorMoveSupporter.h"
#include "../Z_Except/ResourceManager.h"


// 静的メンバーの初期化

BaseSceneManager *Master::mpBaseSceneManager = nullptr;

EndManager* Master::mpEndManager = nullptr;
TimeManager* Master::mpTimeManager = nullptr;
ResourceManager *Master::mpResourceManager = nullptr;
KeyState* Master::mpKeyState = nullptr;
DxLibDataManager* Master::mpDxLibDataManager = nullptr;

ImguiManager* Master::mpImguiManager = nullptr;

Player* Master::mpPlayerLight = nullptr;
Player* Master::mpPlayerShadow = nullptr;
LightAreaManager* Master::mpLightManager = nullptr;

CursorMoveSupporter *Master::mpCursorMoveSupporter = nullptr;

// DxLibの前の初期化
int Master::DxInitPreInitialize()
{
    // ウインドウモードで起動
    ChangeWindowMode(true);

    // 画面サイズ
    SetGraphMode(1280, 960, 32);

    mpDxLibDataManager = new DxLibDataManager();
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

    // mpDXAnimModel = new DXAnimModel();

    mpKeyState = new KeyState();
    // 

    mpCursorMoveSupporter = new CursorMoveSupporter;

    mpBaseSceneManager = new BaseSceneManager();
    mpBaseSceneManager->Initialize();

    mpLightManager = new LightAreaManager();
    mpLightManager->Initilize();

    // imguiマネージャー
    mpImguiManager = new ImguiManager(true);// 使うかどうかのフラグ
    mpImguiManager->Initilize();

    // 
    GameObject *playerObjectLight = new PlayerObject(1);
    playerObjectLight->Create();
    mpPlayerLight = static_cast<PlayerObject *>(playerObjectLight)->GetPlayerComponent();

    GameObject *playerObjectShadow = new PlayerObject(2);
    playerObjectShadow->Create();
    mpPlayerShadow = static_cast<PlayerObject *>(playerObjectShadow)->GetPlayerComponent();


    // ラストに初期化して
    mpDxLibDataManager->Initialize();
    return 0;
}

// Masterの各メンバをdeleteする関数
int Master::Finalize()
{
    mpBaseSceneManager->Finalize();

    GameObject *playerObjectLight = mpPlayerLight->GetMyObject();

    GameObject *playerObjectShadow = mpPlayerShadow->GetMyObject();

    // 
    mpImguiManager->Finalize();

    mpDxLibDataManager->Finalize();

    // 削除
    delete playerObjectLight;
    delete playerObjectShadow;
    delete mpImguiManager;
    delete mpBaseSceneManager;
    delete mpEndManager;
    delete mpTimeManager;
	delete mpResourceManager;
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
	// 
    DrawRectExtendGraphF(
        posLeftUp.GetX(), posLeftUp.GetY(), posRightDown.GetX(), posRightDown.GetY(),
        uvLeftUp.GetX(), uvLeftUp.GetY(), uvRightDown.GetX(), uvRightDown.GetY(), graphHandle, true);

	return 0;
}
