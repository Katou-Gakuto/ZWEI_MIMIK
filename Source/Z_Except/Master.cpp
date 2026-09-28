#include "Master.h"
#include "KeyState.h"
#include "EndManager.h"
#include "TimeManager.h"
#include "VECTOR.h"

#include "../C_Component/Player.h"
#include "../G_LightArea/LightAreaManager.h"
#include "../E_Scene/BaseSceneManager.h"
#include "../Z_Except/ResourceManager.h"
#include "../T_Model/DXModelAnim.h"


// 静的メンバーの初期化

BaseSceneManager *Master::mpBaseSceneManager = nullptr;

EndManager* Master::mpEndManager = nullptr;
TimeManager* Master::mpTimeManager = nullptr;
ResourceManager *Master::mpResourceManager = nullptr;
DXAnimModel *Master::mpDXAnimModel = nullptr;
KeyState* Master::mpKeyState = nullptr;

Player* Master::mpPlayerLight = nullptr;
Player* Master::mpPlayerShadow = nullptr;
LightAreaManager* Master::mpLightManager = nullptr;


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

    mpBaseSceneManager = new BaseSceneManager();
    mpBaseSceneManager->Initialize();

    mpLightManager = new LightAreaManager();


    return 0;
}

// Masterの各メンバをdeleteする関数
int Master::Finalize()
{
    mpBaseSceneManager->Finalize();

    // 
    delete mpBaseSceneManager;
    delete mpEndManager;
    delete mpTimeManager;
	delete mpResourceManager;
	delete mpDXAnimModel;
    delete mpKeyState;

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
