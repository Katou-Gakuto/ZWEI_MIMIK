#include "PuzzleScene1.h"

#include "../A_GameObject/GameObject2D.h"
#include "../A_GameObject/GameObjectManager.h"
#include "../A_GameObject/WallObject.h"
#include "../A_GameObject/MirrorObject.h"
#include "../A_GameObject/ButtonObject.h"
#include "../A_GameObject/LightObject.h"
#include "../A_GameObject/TeleportObject.h"

#include "../C_Component/HoldObjectController.h"
#include "../C_Component/TeleportObjectController.h"
#include "../C_Component/GimmickObjectController.h"

#include "../F_PuzzleGimmick/ButtonTrigger.h"
#include "../F_PuzzleGimmick/FalseTrigger.h"
#include "../F_PuzzleGimmick/LightExecutor.h"
#include "../F_PuzzleGimmick/RouteMoveExecutor.h"

#include "../G_LightArea/LightAreaManager.h"

#include "../Y_Tool/MyFunctions.h"

#include "../Z_Except/DxLibDataManager.h"
#include "../Z_Except/Master.h"

// 
PuzzleScene1_1::PuzzleScene1_1() :
    BasePuzzleScene(SceneTag::ST_Puzzle1_1)
{
    // 

}

// 
PuzzleScene1_1::~PuzzleScene1_1()
{
}

// 
int PuzzleScene1_1::MapCreate(GameObjectManager &objManager)
{
	// 
	Master::mpLightManager->ResizeArea(1);

	VECTOR2D objCenter;
	VECTOR2D blockSize;
	float objRadius = 0.0f;

	// 
	VECTOR2D mapSize;
	this->GetMapSize(mapSize);

	// 
	GameObject2D *currentObject = nullptr;
	BaseComponent *baseComponent = nullptr;
	LightObject *lightObject = nullptr;
	GimmickObjectController *gimmickController = nullptr;
	FalseTrigger *falseTrigger = nullptr;
	BaseGimmickExecutor *baseExecutor = nullptr;
	PuzzleGimmickActiveParam tempGimmickParam;

	// Wall_Top	
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.5f, 0.0f));
	blockSize = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(1.0f, 0.05f));
	currentObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(currentObject);

	// Wall_Bottom
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.5f, 1.0f));
	blockSize = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(1.0f, 0.05f));
	currentObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(currentObject);

	// Wall_Left
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.0f, 0.5f));
	blockSize = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.03030303f, 1.0f));
	currentObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(currentObject);

	// Wall_Right
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(1.0f, 0.5f));
	blockSize = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.03030303f, 1.0f));
	currentObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(currentObject);

	// Obstacle_Center
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.5f, 0.609f));
	blockSize = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.03030303f, 0.3f));
	currentObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(currentObject);

	// Obstacle_Upper
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.2678788f, 0.294f));
	blockSize = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.4848485f, 0.05f));
	currentObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(currentObject);

	// Light_01
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.43f, 0.82f));
	objRadius = 40.0f;
	lightObject = new LightObject(objCenter, objRadius);
	objManager.Add(lightObject);

	// 光のON/OFFのギミック
	gimmickController = lightObject->GetGimmickController();
	tempGimmickParam = PuzzleGimmickActiveParam::Create(true, false);
	falseTrigger = new FalseTrigger;
	baseExecutor = new LightExecutor(
		tempGimmickParam, lightObject, 0, 150, MyFunctions::Deg2Rad(90.0f), MyFunctions::Deg2Rad(90.0f), 1000.0f, true);
	gimmickController->AddGimmick(falseTrigger, baseExecutor);

	// ライトにHoldを追加する
	lightObject->AddComponent(new HoldObjectController(lightObject, false, true, false, true, false));

	// 
	return 0;
}

// 
void PuzzleScene1_1::GetMasterObjectsInitPos(
    VECTOR2D &playerLightPos,
    VECTOR2D &playerShadowPos,
    VECTOR2D &goalLightPos,
    VECTOR2D &goalShadowPos) const
{
	// 
	VECTOR2D mapSize;
	this->GetMapSize(mapSize);

	playerLightPos = VECTOR2D::GetLerpPos(
		VECTOR2D::GetZero(),
		mapSize,
		VECTOR2D(0.2575758f, 0.8f));

    playerShadowPos = VECTOR2D::GetLerpPos(
		VECTOR2D::GetZero(),
		mapSize,
		VECTOR2D(0.7424242f, 0.8f));

    goalLightPos = VECTOR2D::GetLerpPos(
		VECTOR2D::GetZero(), 
		mapSize,
		VECTOR2D(0.2575758f, 0.2f));
    
	goalShadowPos = VECTOR2D::GetLerpPos(
		VECTOR2D::GetZero(),
		mapSize,
		VECTOR2D(0.7424242f, 0.2f));
}

// 
void PuzzleScene1_1::GetMapSize(VECTOR2D &mapSize) const
{
	// 
	mapSize.SetXY(1920.0f, 1080.0f);
}

// 
uint32_t PuzzleScene1_1::GetUseLightAreaCount() const
{
	return 1;
}

// 
PuzzleScene1_2::PuzzleScene1_2() :
    BasePuzzleScene(SceneTag::ST_Puzzle1_2)
{
}

// 
PuzzleScene1_2::~PuzzleScene1_2()
{
}

// 
int PuzzleScene1_2::MapCreate(GameObjectManager &objManager)
{
	VECTOR2D objCenter;
	VECTOR2D blockSize;
	float objRadius = 0.0f;

	// 
	VECTOR2D mapSize;
	this->GetMapSize(mapSize);

	// 
	WallObject *wallObject = nullptr;
	BaseComponent *baseComponent = nullptr;
	std::vector<ButtonObject *> buttonObject;
	LightObject *lightObject = nullptr;
	GimmickObjectController *gimmickController = nullptr;
	ButtonTrigger *buttonTrigger = nullptr;
	BaseGimmickExecutor *baseExecutor = nullptr;
	PuzzleGimmickActiveParam tempGimmickParam;
	TeleportObject *teleportObjectA = nullptr;
	TeleportObject *teleportObjectB = nullptr;

	// 
	buttonObject.resize(3);

	// Wall_Top
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.5f, 0.0f));
	blockSize = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(1.0f, 0.05f));
	wallObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(wallObject);

	// Wall_Bottom
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.5f, 1.0f));
	blockSize = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(1.0f, 0.05f));
	wallObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(wallObject);

	// Wall_Left
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.0f, 0.5f));
	blockSize = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.03030303f, 1.0f));
	wallObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(wallObject);

	// Wall_Right
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(1.0f, 0.5f));
	blockSize = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.03030303f, 1.0f));
	wallObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(wallObject);

	// Obstacle_Upper
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.5f, 0.596f));
	blockSize = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.969697f, 0.05f));
	wallObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(wallObject);

	// Switch_1
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.3181818f, 0.9f));
	blockSize = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.06060606f, 0.1f));
	buttonObject[0] = new ButtonObject(false, 0, objCenter, blockSize);
	objManager.Add(buttonObject[0]);

	// Switch_2
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.5f, 0.3f));
	blockSize = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.06060606f, 0.1f));
	buttonObject[1] = new ButtonObject(false, 0, objCenter, blockSize);
	objManager.Add(buttonObject[1]);

	// Switch_3
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.6818182f, 0.9f));
	blockSize = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.06060606f, 0.1f));
	buttonObject[2] = new ButtonObject(false, 0, objCenter, blockSize);
	objManager.Add(buttonObject[2]);

	// Light_Up(1)
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.1363636f, 0.08899999f));
	objRadius = 40.0f;
	lightObject = new LightObject(objCenter, objRadius);
	objManager.Add(lightObject);

	// 光のON/OFFのギミック
	gimmickController = lightObject->GetGimmickController();
	tempGimmickParam = PuzzleGimmickActiveParam::Create(true, false);
	baseExecutor = new LightExecutor(
		tempGimmickParam, lightObject, 0, 150, MyFunctions::Deg2Rad(0.0f), MyFunctions::Deg2Rad(45.0f), 1000.0f, false);
	gimmickController->AddGimmick(new FalseTrigger, baseExecutor);

	// Light_Up(2)
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.3181818f, 0.08899999f));
	objRadius = 40.0f;
	lightObject = new LightObject(objCenter, objRadius);
	objManager.Add(lightObject);

	// 光のON/OFFのギミック
	gimmickController = lightObject->GetGimmickController();
	tempGimmickParam = PuzzleGimmickActiveParam::Create(false, false);
	buttonTrigger = new ButtonTrigger;
	buttonTrigger->AddButton(buttonObject[0], 0);
	baseExecutor = new LightExecutor(
		tempGimmickParam, lightObject, 1, 150, MyFunctions::Deg2Rad(0.0f), MyFunctions::Deg2Rad(45.0f), 1000.0f, false);
	gimmickController->AddGimmick(buttonTrigger, baseExecutor);

	// Light_Up(3)
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.5f, 0.08899999f));
	objRadius = 40.0f;
	lightObject = new LightObject(objCenter, objRadius);
	objManager.Add(lightObject);

	// 光のON/OFFのギミック
	gimmickController = lightObject->GetGimmickController();
	tempGimmickParam = PuzzleGimmickActiveParam::Create(true, false);
	baseExecutor = new LightExecutor(
		tempGimmickParam, lightObject, 2, 150, MyFunctions::Deg2Rad(0.0f), MyFunctions::Deg2Rad(45.0f), 1000.0f, false);
	gimmickController->AddGimmick(new FalseTrigger, baseExecutor);

	// Light_Up(4)
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.6818182f, 0.08899999f));
	objRadius = 40.0f;
	lightObject = new LightObject(objCenter, objRadius);
	objManager.Add(lightObject);

	// 光のON/OFFのギミック
	gimmickController = lightObject->GetGimmickController();
	tempGimmickParam = PuzzleGimmickActiveParam::Create(false, false);
	buttonTrigger = new ButtonTrigger;
	buttonTrigger->AddButton(buttonObject[2], 0);
	baseExecutor = new LightExecutor(
		tempGimmickParam, lightObject, 3, 150, MyFunctions::Deg2Rad(0.0f), MyFunctions::Deg2Rad(45.0f), 1000.0f, false);
	gimmickController->AddGimmick(buttonTrigger, baseExecutor);

	// Light_Up(5)
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.8636364f, 0.08899999f));
	objRadius = 40.0f;
	lightObject = new LightObject(objCenter, objRadius);
	objManager.Add(lightObject);

	// 光のON/OFFのギミック
	gimmickController = lightObject->GetGimmickController();
	tempGimmickParam = PuzzleGimmickActiveParam::Create(true, false);
	baseExecutor = new LightExecutor(
		tempGimmickParam, lightObject, 4, 150, MyFunctions::Deg2Rad(0.0f), MyFunctions::Deg2Rad(45.0f), 1000.0f, false);
	gimmickController->AddGimmick(new FalseTrigger, baseExecutor);

	// Light_Down
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.5f, 0.901f));
	objRadius = 40.0f;
	lightObject = new LightObject(objCenter, objRadius);
	objManager.Add(lightObject);

	// 光のON/OFFのギミック
	gimmickController = lightObject->GetGimmickController();
	tempGimmickParam = PuzzleGimmickActiveParam::Create(true, false);
	buttonTrigger = new ButtonTrigger;
	buttonTrigger->AddButton(buttonObject[1], 0);
	baseExecutor = new LightExecutor(
		tempGimmickParam, lightObject, 5, 150, MyFunctions::Deg2Rad(180.0f), MyFunctions::Deg2Rad(45.0f), 1000.0f, false);
	gimmickController->AddGimmick(buttonTrigger, baseExecutor);

	// 
	return 0;
}

void PuzzleScene1_2::GetMasterObjectsInitPos(
    VECTOR2D &playerLightPos,
    VECTOR2D &playerShadowPos,
    VECTOR2D &goalLightPos,
    VECTOR2D &goalShadowPos) const
{
	// 
	VECTOR2D mapSize;
	this->GetMapSize(mapSize);

	playerLightPos = VECTOR2D::GetLerpPos(
		VECTOR2D::GetZero(),
		mapSize,
		VECTOR2D(0.1363636f, 0.3f));

	playerShadowPos = VECTOR2D::GetLerpPos(
		VECTOR2D::GetZero(),
		mapSize,
		VECTOR2D(0.1363636f, 0.9f));

	goalLightPos = VECTOR2D::GetLerpPos(
		VECTOR2D::GetZero(),
		mapSize,
		VECTOR2D(0.8636364f, 0.3f));

	goalShadowPos = VECTOR2D::GetLerpPos(
		VECTOR2D::GetZero(),
		mapSize,
		VECTOR2D(0.8636364f, 0.9f));
}

// 
void PuzzleScene1_2::GetMapSize(VECTOR2D &mapSize) const
{
	// 
	mapSize.SetXY(1920.0f, 1080.0f);
}

// 
uint32_t PuzzleScene1_2::GetUseLightAreaCount() const
{
	return 6;
}

// 
PuzzleScene1_3::PuzzleScene1_3() :
	BasePuzzleScene(SceneTag::ST_Puzzle1_3)
{
}

// 
PuzzleScene1_3::~PuzzleScene1_3()
{
}

// 
int PuzzleScene1_3::MapCreate(GameObjectManager &objManager)
{
	VECTOR2D objCenter;
	VECTOR2D blockSize;
	float objRadius = 0.0f;

	// 
	VECTOR2D mapSize;
	this->GetMapSize(mapSize);

	// 
	WallObject *wallObject = nullptr;
	BaseComponent *baseComponent = nullptr;
	std::vector<ButtonObject *> buttonObject;
	LightObject *lightObject = nullptr;
	GimmickObjectController *gimmickController = nullptr;
	ButtonTrigger *buttonTrigger = nullptr;
	BaseGimmickExecutor *baseExecutor = nullptr;
	PuzzleGimmickActiveParam tempGimmickParam;
	TeleportObject *teleportObjectA = nullptr;
	TeleportObject *teleportObjectB = nullptr;

	// 
	buttonObject.resize(2);

	// Wall_Top
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.5f, 0.0f));
	blockSize = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(1.0f, 0.05f));
	wallObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(wallObject);

	// Wall_Bottom
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.5f, 1.0f));
	blockSize = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(1.0f, 0.05f));
	wallObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(wallObject);

	// Wall_Left
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.0f, 0.5f));
	blockSize = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.03030303f, 1.0f));
	wallObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(wallObject);

	// Wall_Right
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(1.0f, 0.5f));
	blockSize = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.03030303f, 1.0f));
	wallObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(wallObject);

	// Obstacle_Left
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.5757576f, 0.3f));
	blockSize = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.03030303f, 0.35f));
	wallObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(wallObject);

	// Obstacle_Right
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.4575758f, 0.9f));
	blockSize = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.03030303f, 0.35f));
	wallObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(wallObject);

	// Switch_1
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.6757576f, 0.9f));
	blockSize = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.06060606f, 0.1f));
	buttonObject[0] = new ButtonObject(false, 0, objCenter, blockSize);
	objManager.Add(buttonObject[0]);

	// Switch_2
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.6981818f, 0.3f));
	blockSize = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.06060606f, 0.1f));
	buttonObject[1] = new ButtonObject(false, 0, objCenter, blockSize);
	objManager.Add(buttonObject[1]);

	// Light_Left
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.04545455f, 0.92f));
	objRadius = 40.0f;
	lightObject = new LightObject(objCenter, objRadius);
	objManager.Add(lightObject);

	// 光のON/OFFのギミック
	gimmickController = lightObject->GetGimmickController();
	tempGimmickParam = PuzzleGimmickActiveParam::Create(true, false);
	baseExecutor = new LightExecutor(
		tempGimmickParam, lightObject, 0, 150, MyFunctions::Deg2Rad(270.0f), MyFunctions::Deg2Rad(30.0f), 1000.0f, false);
	gimmickController->AddGimmick(new FalseTrigger, baseExecutor);

	// Light_Center
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.04545455f, 0.6f));
	objRadius = 40.0f;
	lightObject = new LightObject(objCenter, objRadius);
	objManager.Add(lightObject);

	// 光のON/OFFのギミック
	gimmickController = lightObject->GetGimmickController();
	tempGimmickParam = PuzzleGimmickActiveParam::Create(false, false);
	buttonTrigger = new ButtonTrigger;
	buttonTrigger->AddButton(buttonObject[0], 0);
	buttonTrigger->AddButton(buttonObject[1], 1);
	baseExecutor = new LightExecutor(
		tempGimmickParam, lightObject, 1, 150, MyFunctions::Deg2Rad(270.0f), MyFunctions::Deg2Rad(90.0f), 2000.0f, false);
	gimmickController->AddGimmick(buttonTrigger, baseExecutor);

	// Light_Right
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.9545454f, 0.3f));
	objRadius = 40.0f;
	lightObject = new LightObject(objCenter, objRadius);
	objManager.Add(lightObject);

	// 光のON/OFFのギミック
	gimmickController = lightObject->GetGimmickController();
	tempGimmickParam = PuzzleGimmickActiveParam::Create(true, false);
	baseExecutor = new LightExecutor(
		tempGimmickParam, lightObject, 2, 150, MyFunctions::Deg2Rad(90.0f), MyFunctions::Deg2Rad(30.0f), 1000.0f, false);
	gimmickController->AddGimmick(new FalseTrigger, baseExecutor);

	// 
	return 0;
}

void PuzzleScene1_3::GetMasterObjectsInitPos(
	VECTOR2D &playerLightPos,
	VECTOR2D &playerShadowPos,
	VECTOR2D &goalLightPos,
	VECTOR2D &goalShadowPos) const
{
	// 
	VECTOR2D mapSize;
	this->GetMapSize(mapSize);

	playerLightPos = VECTOR2D::GetLerpPos(
		VECTOR2D::GetZero(),
		mapSize,
		VECTOR2D(0.1363636f, 0.9f));

	playerShadowPos = VECTOR2D::GetLerpPos(
		VECTOR2D::GetZero(),
		mapSize,
		VECTOR2D(0.8636364f, 0.9f));

	goalLightPos = VECTOR2D::GetLerpPos(
		VECTOR2D::GetZero(),
		mapSize,
		VECTOR2D(0.8636364f, 0.3f));

	goalShadowPos = VECTOR2D::GetLerpPos(
		VECTOR2D::GetZero(),
		mapSize,
		VECTOR2D(0.1363636f, 0.3f));
}

// 
void PuzzleScene1_3::GetMapSize(VECTOR2D &mapSize) const
{
	// 
	mapSize.SetXY(1920.0f, 1080.0f);
}

// 
uint32_t PuzzleScene1_3::GetUseLightAreaCount() const
{
	return 3;
}

// 
PuzzleScene1_4::PuzzleScene1_4() :
	BasePuzzleScene(SceneTag::ST_Puzzle1_4)
{
}

// 
PuzzleScene1_4::~PuzzleScene1_4()
{
}

// 
int PuzzleScene1_4::MapCreate(GameObjectManager &objManager)
{
	VECTOR2D objCenter;
	VECTOR2D blockSize;
	float objRadius = 0.0f;

	// 
	VECTOR2D mapSize;
	this->GetMapSize(mapSize);

	// 
	WallObject *wallObject = nullptr;
	BaseComponent *baseComponent = nullptr;
	std::vector<ButtonObject *> buttonObject;
	LightObject *lightObject = nullptr;
	GimmickObjectController *gimmickController = nullptr;
	RouteMoveExecutor *moveExecutor = nullptr;
	LightExecutor *lightExecutor = nullptr;
	PuzzleGimmickActiveParam tempGimmickParam;
	TeleportObject *teleportObjectA = nullptr;
	TeleportObject *teleportObjectB = nullptr;

	// 
	buttonObject.resize(0);

	// Wall_Top
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.5f, 0.0f));
	blockSize = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(1.0f, 0.05f));
	wallObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(wallObject);

	// Wall_Bottom
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.5f, 1.0f));
	blockSize = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(1.0f, 0.05f));
	wallObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(wallObject);

	// Wall_Left
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.0f, 0.5f));
	blockSize = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.03030303f, 1.0f));
	wallObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(wallObject);

	// Wall_Right
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(1.0f, 0.5f));
	blockSize = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.03030303f, 1.0f));
	wallObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(wallObject);

	// Obstacle_Left
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.1f, 0.5f));
	blockSize = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.2f, 0.05f));
	wallObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(wallObject);

	// Obstacle_Right
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.9f, 0.5f));
	blockSize = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.2f, 0.05f));
	wallObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(wallObject);

	// Moving_Obstacle
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.3f, 0.5f));
	blockSize = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.2f, 0.05f));
	wallObject = new WallObject(true, objCenter, blockSize, 0.0f);
	objManager.Add(wallObject);

	// 自動移動のギミックの詳細を設定する
	RouteData tempRoute(RouteOffMode::RouteOffMode_Stop, true, 5);

	// 回転はずっとしません
	RouteKeyFrame keyFrame;
	keyFrame.mfRadian = 0.0f;

	// 1つ目のキーフレーム
	keyFrame.mnFrameCount = 0;
	keyFrame.mvPos = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.3f, 0.5f));
	tempRoute.Add(keyFrame);

	// 2つ目のキーフレーム
	keyFrame.mnFrameCount = 40;
	keyFrame.mvPos = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.3f, 0.5f));
	tempRoute.Add(keyFrame);

	// 3つ目のキーフレーム
	keyFrame.mnFrameCount = 300;
	keyFrame.mvPos = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.7f, 0.5f));
	tempRoute.Add(keyFrame);

	// 4つ目のキーフレーム
	keyFrame.mnFrameCount = 340;
	keyFrame.mvPos = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.7f, 0.5f));
	tempRoute.Add(keyFrame);

	// 5つ目のキーフレーム(ループの重なる地点)
	keyFrame.mnFrameCount = 600;
	keyFrame.mvPos = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.3f, 0.5f));
	tempRoute.Add(keyFrame);

	// 自動移動のギミックを追加する
	gimmickController = wallObject->GetGimmickController();
	tempGimmickParam = PuzzleGimmickActiveParam::Create(true, false);
	moveExecutor = new RouteMoveExecutor(tempGimmickParam, wallObject, tempRoute);
	gimmickController->AddGimmick(new FalseTrigger, moveExecutor);

	// Light_Left
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.1363636f, 0.15f));
	objRadius = 40.0f;
	lightObject = new LightObject(objCenter, objRadius);
	objManager.Add(lightObject);

	// 光のON/OFFのギミック
	gimmickController = lightObject->GetGimmickController();
	tempGimmickParam = PuzzleGimmickActiveParam::Create(true, false);
	lightExecutor = new LightExecutor(
		tempGimmickParam, lightObject, 0, 150, MyFunctions::Deg2Rad(0.0f), MyFunctions::Deg2Rad(60.0f), 2000.0f, false);
	gimmickController->AddGimmick(new FalseTrigger, lightExecutor);

	// Light_Center
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.5f, 0.15f));
	objRadius = 40.0f;
	lightObject = new LightObject(objCenter, objRadius);
	objManager.Add(lightObject);

	// 光のON/OFFのギミック
	gimmickController = lightObject->GetGimmickController();
	tempGimmickParam = PuzzleGimmickActiveParam::Create(true, false);
	lightExecutor = new LightExecutor(
		tempGimmickParam, lightObject, 1, 150, MyFunctions::Deg2Rad(0.0f), MyFunctions::Deg2Rad(90.0f), 2000.0f, false);
	gimmickController->AddGimmick(new FalseTrigger, lightExecutor);

	// Light_Right
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.8636364f, 0.15f));
	objRadius = 40.0f;
	lightObject = new LightObject(objCenter, objRadius);
	objManager.Add(lightObject);

	// 光のON/OFFのギミック
	gimmickController = lightObject->GetGimmickController();
	tempGimmickParam = PuzzleGimmickActiveParam::Create(true, false);
	lightExecutor = new LightExecutor(
		tempGimmickParam, lightObject, 2, 150, MyFunctions::Deg2Rad(0.0f), MyFunctions::Deg2Rad(60.0f), 2000.0f, false);
	gimmickController->AddGimmick(new FalseTrigger, lightExecutor);

	// 
	return 0;
}

void PuzzleScene1_4::GetMasterObjectsInitPos(
	VECTOR2D &playerLightPos,
	VECTOR2D &playerShadowPos,
	VECTOR2D &goalLightPos,
	VECTOR2D &goalShadowPos) const
{
	// 
	VECTOR2D mapSize;
	this->GetMapSize(mapSize);

	playerLightPos = VECTOR2D::GetLerpPos(
		VECTOR2D::GetZero(),
		mapSize,
		VECTOR2D(0.1363636f, 0.4f));

	playerShadowPos = VECTOR2D::GetLerpPos(
		VECTOR2D::GetZero(),
		mapSize,
		VECTOR2D(0.1363636f, 0.6f));

	goalLightPos = VECTOR2D::GetLerpPos(
		VECTOR2D::GetZero(),
		mapSize,
		VECTOR2D(0.8636364f, 0.3f));

	goalShadowPos = VECTOR2D::GetLerpPos(
		VECTOR2D::GetZero(),
		mapSize,
		VECTOR2D(0.8636364f, 0.9f));
}

// 
void PuzzleScene1_4::GetMapSize(VECTOR2D &mapSize) const
{
	// 
	mapSize.SetXY(1920.0f, 1080.0f);
}

// 
uint32_t PuzzleScene1_4::GetUseLightAreaCount() const
{
	return 3;
}

// 
PuzzleScene1_5::PuzzleScene1_5() :
	BasePuzzleScene(SceneTag::ST_Puzzle1_5)
{
}

// 
PuzzleScene1_5::~PuzzleScene1_5()
{
}

// 
int PuzzleScene1_5::MapCreate(GameObjectManager &objManager)
{
	VECTOR2D objCenter;
	VECTOR2D blockSize;
	float objRadius = 0.0f;

	// 
	VECTOR2D mapSize;
	this->GetMapSize(mapSize);

	// 
	WallObject *wallObject = nullptr;
	BaseComponent *baseComponent = nullptr;
	std::vector<ButtonObject *> buttonObject;
	LightObject *lightObject = nullptr;
	GimmickObjectController *gimmickController = nullptr;
	RouteMoveExecutor *moveExecutor = nullptr;
	LightExecutor *lightExecutor = nullptr;
	PuzzleGimmickActiveParam tempGimmickParam;
	TeleportObject *teleportObjectA = nullptr;
	TeleportObject *teleportObjectB = nullptr;

	// 
	buttonObject.resize(0);

	// Wall_Top
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.5f, 0.0f));
	blockSize = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(1.0f, 0.05f));
	wallObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(wallObject);

	// Wall_Bottom
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.5f, 1.0f));
	blockSize = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(1.0f, 0.05f));
	wallObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(wallObject);

	// Wall_Left
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.0f, 0.5f));
	blockSize = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.03030303f, 1.0f));
	wallObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(wallObject);

	// Wall_Right
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(1.0f, 0.5f));
	blockSize = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.03030303f, 1.0f));
	wallObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(wallObject);

	// Obstacle_Center
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.5f, 0.6f));
	blockSize = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.2424242f, 0.05f));
	wallObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(wallObject);

	// Obstacle_Left
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.1666667f, 0.6f));
	blockSize = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.2424242f, 0.05f));
	wallObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(wallObject);

	// Obstacle_Right
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.8333333f, 0.6f));
	blockSize = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.2424242f, 0.05f));
	wallObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(wallObject);

	// Light_Center
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.5f, 0.75f));
	objRadius = 40.0f;
	lightObject = new LightObject(objCenter, objRadius);
	objManager.Add(lightObject);

	// 光のON/OFFのギミック
	gimmickController = lightObject->GetGimmickController();
	tempGimmickParam = PuzzleGimmickActiveParam::Create(true, false);
	lightExecutor = new LightExecutor(
		tempGimmickParam, lightObject, 0, 150, MyFunctions::Deg2Rad(180.0f), MyFunctions::Deg2Rad(90.0f), 1000.0f, true);
	gimmickController->AddGimmick(new FalseTrigger, lightExecutor);

	// Light_Left
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.1363636f, 0.15f));
	objRadius = 40.0f;
	lightObject = new LightObject(objCenter, objRadius);
	objManager.Add(lightObject);

	// 光のON/OFFのギミック
	gimmickController = lightObject->GetGimmickController();
	tempGimmickParam = PuzzleGimmickActiveParam::Create(true, false);
	lightExecutor = new LightExecutor(
		tempGimmickParam, lightObject, 1, 150, MyFunctions::Deg2Rad(0.0f), MyFunctions::Deg2Rad(45.0f), 1000.0f, true);
	gimmickController->AddGimmick(new FalseTrigger, lightExecutor);

	// Light_Right
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.8636364f, 0.15f));
	objRadius = 40.0f;
	lightObject = new LightObject(objCenter, objRadius);
	objManager.Add(lightObject);

	// 光のON/OFFのギミック
	gimmickController = lightObject->GetGimmickController();
	tempGimmickParam = PuzzleGimmickActiveParam::Create(true, false);
	lightExecutor = new LightExecutor(
		tempGimmickParam, lightObject, 2, 150, MyFunctions::Deg2Rad(0.0f), MyFunctions::Deg2Rad(45.0f), 1000.0f, true);
	gimmickController->AddGimmick(new FalseTrigger, lightExecutor);

	// MovingLight
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.3f, 0.15f));
	objRadius = 40.0f;
	lightObject = new LightObject(objCenter, objRadius);
	objManager.Add(lightObject);

	// 光のON/OFFのギミック
	gimmickController = lightObject->GetGimmickController();
	tempGimmickParam = PuzzleGimmickActiveParam::Create(true, false);
	lightExecutor = new LightExecutor(
		tempGimmickParam, lightObject, 3, 150, MyFunctions::Deg2Rad(0.0f), MyFunctions::Deg2Rad(90.0f), 1000.0f, true);
	gimmickController->AddGimmick(new FalseTrigger, lightExecutor);

	// 光の自動移動ギミック
	RouteData tempRoute(RouteOffMode::RouteOffMode_Stop, true, 403);

	// 
	VECTOR2D centerPos = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.5f, 0.15f));
	centerPos.SetY(-200);
	VECTOR2D firstPos = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.3f, 0.15f));
	VECTOR2D lastPos = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.7f, 0.15f));
	VECTOR2D nowPos;
	VECTOR2D center2now = (firstPos - centerPos);

	// 1つ目のキーフレーム
	RouteKeyFrame keyFrame;
	keyFrame.mnFrameCount = 0;
	keyFrame.mfRadian = center2now.GetAngle();
	keyFrame.mvPos = firstPos;
	tempRoute.Add(keyFrame);

	// 
	uint32_t breathFrame = 10;

	// 
	uint32_t moveFrameMax = 300;
	uint32_t moveFrameCount = moveFrameMax + 1;
	float maxDistance = (centerPos - firstPos).Magnitude();
	float minDistance = maxDistance * 0.92f;
	float nowDistance = 0.0f;

	// 1～moveFrameMax + 1個目までのキーフレームを設定するfor文
	float nowLate = 0.0f;
	for (uint32_t i = 0; i <= moveFrameMax; i++)
	{
		// 
		if (i == 0)
		{
			nowLate = 0.0f;
		}
		else
		{
			nowLate = static_cast<float>(i) / static_cast<float>(moveFrameMax);
		}

		// 1個目のキーフレームからbreathFrame + iフレームを設定する
		keyFrame.mnFrameCount = breathFrame + i;

		// 
		nowPos = VECTOR2D::GetLerpPos(firstPos, lastPos, nowLate);

		// 
		if (i <= moveFrameMax * 0.5)
		{
			nowDistance = MyFunctions::GetFloatLerp(maxDistance, minDistance, nowLate * 2.0f);
		}
		else
		{
			nowDistance = MyFunctions::GetFloatLerp(minDistance, maxDistance, (nowLate * 2.0f) - 1.0f);
		}

		// 
		center2now = (nowPos - centerPos).Normalize() *	nowDistance;

		// 
		keyFrame.mvPos = centerPos + center2now;

		// 角度
		keyFrame.mfRadian = center2now.GetAngle();

		// 追加する
		tempRoute.Add(keyFrame);
	}

	// 
	RouteKeyFrame tempKeyFrame = tempRoute.GetKeyFrame(moveFrameMax);

	// 1 + moveFrameMax + 1個目のキーフレーム
	keyFrame.mnFrameCount = breathFrame + moveFrameCount + breathFrame;
	keyFrame.mfRadian = tempKeyFrame.mfRadian;
	keyFrame.mvPos = tempKeyFrame.mvPos;
	tempRoute.Add(keyFrame);

	// 1 + moveFrameMax + 2～1 + moveFrameMax + moveFrameMax + 1個目までのキーフレームを設定するfor文
	for (uint32_t i = 0; i <= moveFrameMax; i++)
	{
		// 
		tempKeyFrame = tempRoute.GetKeyFrame(1 + (moveFrameCount - i));

		// 1個目のキーフレームからbreathFrame + iフレームを設定する
		keyFrame.mnFrameCount = breathFrame + moveFrameCount + breathFrame + i;

		// 
		keyFrame.mfRadian = tempKeyFrame.mfRadian;
		keyFrame.mvPos = tempKeyFrame.mvPos;

		// 追加する
		tempRoute.Add(keyFrame);
	}

	// 自動移動のギミックを追加する
	gimmickController = lightObject->GetGimmickController();
	tempGimmickParam = PuzzleGimmickActiveParam::Create(true, false);
	moveExecutor = new RouteMoveExecutor(tempGimmickParam, lightObject, tempRoute);
	gimmickController->AddGimmick(new FalseTrigger, moveExecutor);

	// 
	return 0;
}

void PuzzleScene1_5::GetMasterObjectsInitPos(
	VECTOR2D &playerLightPos,
	VECTOR2D &playerShadowPos,
	VECTOR2D &goalLightPos,
	VECTOR2D &goalShadowPos) const
{
	// 
	VECTOR2D mapSize;
	this->GetMapSize(mapSize);

	playerLightPos = VECTOR2D::GetLerpPos(
		VECTOR2D::GetZero(),
		mapSize,
		VECTOR2D(0.1363636f, 0.3f));

	playerShadowPos = VECTOR2D::GetLerpPos(
		VECTOR2D::GetZero(),
		mapSize,
		VECTOR2D(0.1363636f, 0.7f));

	goalLightPos = VECTOR2D::GetLerpPos(
		VECTOR2D::GetZero(),
		mapSize,
		VECTOR2D(0.8636364f, 0.3f));

	goalShadowPos = VECTOR2D::GetLerpPos(
		VECTOR2D::GetZero(),
		mapSize,
		VECTOR2D(0.8636364f, 0.9f));
}

// 
void PuzzleScene1_5::GetMapSize(VECTOR2D &mapSize) const
{
	// 
	mapSize.SetXY(1920.0f, 1080.0f);
}

// 
uint32_t PuzzleScene1_5::GetUseLightAreaCount() const
{
	return 4;
}

// 
PuzzleScene1_6::PuzzleScene1_6() :
	BasePuzzleScene(SceneTag::ST_Puzzle1_6)
{
}

// 
PuzzleScene1_6::~PuzzleScene1_6()
{
}

// 
int PuzzleScene1_6::MapCreate(GameObjectManager &objManager)
{
	VECTOR2D objCenter;
	VECTOR2D blockSize;
	float objRadius = 0.0f;

	// 
	VECTOR2D mapSize;
	this->GetMapSize(mapSize);

	// 
	WallObject *wallObject = nullptr;
	BaseComponent *baseComponent = nullptr;
	std::vector<ButtonObject *> buttonObject;
	LightObject *lightObject = nullptr;
	GimmickObjectController *gimmickController = nullptr;
	BaseGimmickExecutor *baseExecutor = nullptr;
	PuzzleGimmickActiveParam tempGimmickParam;
	TeleportObject *teleportObjectA = nullptr;
	TeleportObject *teleportObjectB = nullptr;

	// 
	buttonObject.resize(0);

	// Wall_Top
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.5f, 0.0f));
	blockSize = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(1.0f, 0.05f));
	wallObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(wallObject);

	// Wall_Bottom
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.5f, 1.0f));
	blockSize = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(1.0f, 0.05f));
	wallObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(wallObject);

	// Wall_Left
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.0f, 0.5f));
	blockSize = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.03030303f, 1.0f));
	wallObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(wallObject);

	// Wall_Right
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(1.0f, 0.5f));
	blockSize = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.03030303f, 1.0f));
	wallObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(wallObject);

	// Obstacle_Left
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.3181818f, 0.596f));
	blockSize = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.6060606f, 0.05f));
	wallObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(wallObject);

	// Obstacle_Right
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.8636364f, 0.6f));
	blockSize = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.2121212f, 0.05f));
	wallObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(wallObject);

	// PushableBlock
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.5f, 0.42f));
	blockSize = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.06060606f, 0.275f));
	wallObject = new WallObject(true, objCenter, blockSize, 0.0f);
	objManager.Add(wallObject);

	// PushableBlockにHoldを追加
	wallObject->AddComponent(new HoldObjectController(wallObject, false, false, false, true, false));

	// Light_Right
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.9545454f, 0.3f));
	objRadius = 40.0f;
	lightObject = new LightObject(objCenter, objRadius);
	objManager.Add(lightObject);

	// 光のON/OFFのギミック
	gimmickController = lightObject->GetGimmickController();
	tempGimmickParam = PuzzleGimmickActiveParam::Create(true, false);
	baseExecutor = new LightExecutor(
		tempGimmickParam, lightObject, 0, 150, MyFunctions::Deg2Rad(90.0f), MyFunctions::Deg2Rad(90.0f), 2000.0f, true);
	gimmickController->AddGimmick(new FalseTrigger, baseExecutor);

	// 
	return 0;
}

void PuzzleScene1_6::GetMasterObjectsInitPos(
	VECTOR2D &playerLightPos,
	VECTOR2D &playerShadowPos,
	VECTOR2D &goalLightPos,
	VECTOR2D &goalShadowPos) const
{
	// 
	VECTOR2D mapSize;
	this->GetMapSize(mapSize);

	playerLightPos = VECTOR2D::GetLerpPos(
		VECTOR2D::GetZero(),
		mapSize,
		VECTOR2D(0.1363636f, 0.2f));

	playerShadowPos = VECTOR2D::GetLerpPos(
		VECTOR2D::GetZero(),
		mapSize,
		VECTOR2D(0.1363636f, 0.4f));

	goalLightPos = VECTOR2D::GetLerpPos(
		VECTOR2D::GetZero(),
		mapSize,
		VECTOR2D(0.8636364f, 0.3f));

	goalShadowPos = VECTOR2D::GetLerpPos(
		VECTOR2D::GetZero(),
		mapSize,
		VECTOR2D(0.8636364f, 0.9f));
}

// 
void PuzzleScene1_6::GetMapSize(VECTOR2D &mapSize) const
{
	// 
	mapSize.SetXY(1920.0f, 1080.0f);
}

// 
uint32_t PuzzleScene1_6::GetUseLightAreaCount() const
{
	return 1;
}

// 
PuzzleScene1_7::PuzzleScene1_7() :
	BasePuzzleScene(SceneTag::ST_Puzzle1_7)
{
}

// 
PuzzleScene1_7::~PuzzleScene1_7()
{
}

// 
int PuzzleScene1_7::MapCreate(GameObjectManager &objManager)
{
	VECTOR2D objCenter;
	VECTOR2D blockSize;
	float objRadius = 0.0f;

	// 
	VECTOR2D mapSize;
	this->GetMapSize(mapSize);

	// 
	WallObject *wallObject = nullptr;
	BaseComponent *baseComponent = nullptr;
	std::vector<ButtonObject *> buttonObject;
	LightObject *lightObject = nullptr;
	GimmickObjectController *gimmickController = nullptr;
	ButtonTrigger *buttonTrigger = nullptr;
	BaseGimmickExecutor *baseExecutor = nullptr;
	PuzzleGimmickActiveParam tempGimmickParam;
	TeleportObject *teleportObjectA = nullptr;
	TeleportObject *teleportObjectB = nullptr;

	// 
	buttonObject.resize(1);

	// Wall_Top
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.5f, 0.0f));
	blockSize = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(1.0f, 0.05f));
	wallObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(wallObject);

	// Wall_Bottom
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.5f, 1.0f));
	blockSize = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(1.0f, 0.05f));
	wallObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(wallObject);

	// Wall_Left
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.0f, 0.5f));
	blockSize = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.03030303f, 1.0f));
	wallObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(wallObject);

	// Wall_Right
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(1.0f, 0.5f));
	blockSize = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.03030303f, 1.0f));
	wallObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(wallObject);

	// Obstacle_Left
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.8030303f, 0.6f));
	blockSize = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.3333333f, 0.05f));
	wallObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(wallObject);

	// Obstacle_Right
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.1969697f, 0.6f));
	blockSize = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.3333333f, 0.05f));
	wallObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(wallObject);

	// Switch_1
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.2933333f, 0.394f));
	blockSize = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.06060606f, 0.1f));
	buttonObject[0] = new ButtonObject(false, 0, objCenter, blockSize);
	objManager.Add(buttonObject[0]);

	// Light_Left
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.1666667f, 0.651f));
	objRadius = 40.0f;
	lightObject = new LightObject(objCenter, objRadius);
	objManager.Add(lightObject);

	// 光のON/OFFのギミック
	gimmickController = lightObject->GetGimmickController();
	tempGimmickParam = PuzzleGimmickActiveParam::Create(true, false);
	baseExecutor = new LightExecutor(
		tempGimmickParam, lightObject, 0, 150, MyFunctions::Deg2Rad(0.0f), MyFunctions::Deg2Rad(75.0f), 1000.0f, true);
	gimmickController->AddGimmick(new FalseTrigger, baseExecutor);

	// Light_Center
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.5f, 0.15f));
	objRadius = 40.0f;
	lightObject = new LightObject(objCenter, objRadius);
	objManager.Add(lightObject);

	// 光のON/OFFのギミック
	gimmickController = lightObject->GetGimmickController();
	tempGimmickParam = PuzzleGimmickActiveParam::Create(false, false);
	buttonTrigger = new ButtonTrigger;
	buttonTrigger->AddButton(buttonObject[0], 0);
	baseExecutor = new LightExecutor(
		tempGimmickParam, lightObject, 1, 150, MyFunctions::Deg2Rad(0.0f), MyFunctions::Deg2Rad(90.0f), 1000.0f, true);
	gimmickController->AddGimmick(buttonTrigger, baseExecutor);

	// Light_Right
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.8242424f, 0.143f));
	objRadius = 40.0f;
	lightObject = new LightObject(objCenter, objRadius);
	objManager.Add(lightObject);

	// 光のON/OFFのギミック
	gimmickController = lightObject->GetGimmickController();
	tempGimmickParam = PuzzleGimmickActiveParam::Create(true, false);
	baseExecutor = new LightExecutor(
		tempGimmickParam, lightObject, 2, 150, MyFunctions::Deg2Rad(0.0f), MyFunctions::Deg2Rad(75.0f), 1000.0f, true);
	gimmickController->AddGimmick(new FalseTrigger, baseExecutor);

	// 
	return 0;
}

void PuzzleScene1_7::GetMasterObjectsInitPos(
	VECTOR2D &playerLightPos,
	VECTOR2D &playerShadowPos,
	VECTOR2D &goalLightPos,
	VECTOR2D &goalShadowPos) const
{
	// 
	VECTOR2D mapSize;
	this->GetMapSize(mapSize);

	playerLightPos = VECTOR2D::GetLerpPos(
		VECTOR2D::GetZero(),
		mapSize,
		VECTOR2D(0.1363636f, 0.9f));

	playerShadowPos = VECTOR2D::GetLerpPos(
		VECTOR2D::GetZero(),
		mapSize,
		VECTOR2D(0.1363636f, 0.3f));

	goalLightPos = VECTOR2D::GetLerpPos(
		VECTOR2D::GetZero(),
		mapSize,
		VECTOR2D(0.8636364f, 0.3f));

	goalShadowPos = VECTOR2D::GetLerpPos(
		VECTOR2D::GetZero(),
		mapSize,
		VECTOR2D(0.8636364f, 0.9f));
}

// 
void PuzzleScene1_7::GetMapSize(VECTOR2D &mapSize) const
{
	// 
	mapSize.SetXY(1920.0f, 1080.0f);
}

// 
uint32_t PuzzleScene1_7::GetUseLightAreaCount() const
{
	return 3;
}

// 
PuzzleScene1_8::PuzzleScene1_8() :
	BasePuzzleScene(SceneTag::ST_Puzzle1_8)
{
}

// 
PuzzleScene1_8::~PuzzleScene1_8()
{
}

// 
int PuzzleScene1_8::MapCreate(GameObjectManager &objManager)
{
	VECTOR2D objCenter;
	VECTOR2D blockSize;
	float objRadius = 0.0f;

	// 
	VECTOR2D mapSize;
	this->GetMapSize(mapSize);

	// 
	WallObject *wallObject = nullptr;
	BaseComponent *baseComponent = nullptr;
	std::vector<ButtonObject *> buttonObject;
	LightObject *lightObject = nullptr;
	GimmickObjectController *gimmickController = nullptr;
	ButtonTrigger *buttonTrigger = nullptr;
	BaseGimmickExecutor *baseExecutor = nullptr;
	PuzzleGimmickActiveParam tempGimmickParam;
	TeleportObject *teleportObjectA = nullptr;
	TeleportObject *teleportObjectB = nullptr;

	// 
	buttonObject.resize(2);

	// Wall_Top
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.5f, 0.0f));
	blockSize = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(1.0f, 0.05f));
	wallObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(wallObject);

	// Wall_Bottom
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.5f, 1.0f));
	blockSize = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(1.0f, 0.05f));
	wallObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(wallObject);

	// Wall_Left
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.0f, 0.5f));
	blockSize = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.03030303f, 1.0f));
	wallObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(wallObject);

	// Wall_Right
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(1.0f, 0.5f));
	blockSize = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.03030303f, 1.0f));
	wallObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(wallObject);

	// Switch_Black
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.1363636f, 0.9f));
	blockSize = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.04848485f, 0.08f));
	buttonObject[0] = new ButtonObject(false, 0, objCenter, blockSize);
	objManager.Add(buttonObject[0]);

	// Switch_White
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.1363636f, 0.3f));
	blockSize = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.04848485f, 0.08f));
	buttonObject[1] = new ButtonObject(false, 0, objCenter, blockSize);
	objManager.Add(buttonObject[1]);

	// Light_Left
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.1363636f, 0.15f));
	objRadius = 40.0f;
	lightObject = new LightObject(objCenter, objRadius);
	objManager.Add(lightObject);

	// 光のON/OFFのギミック
	gimmickController = lightObject->GetGimmickController();
	tempGimmickParam = PuzzleGimmickActiveParam::Create(true, false);
	baseExecutor = new LightExecutor(
		tempGimmickParam, lightObject, 0, 150, MyFunctions::Deg2Rad(0.0f), MyFunctions::Deg2Rad(90.0f), 1000.0f, true);
	gimmickController->AddGimmick(new FalseTrigger, baseExecutor);

	// Light_Center
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.5f, 0.15f));
	objRadius = 40.0f;
	lightObject = new LightObject(objCenter, objRadius);
	objManager.Add(lightObject);

	// 光のON/OFFのギミック
	gimmickController = lightObject->GetGimmickController();
	tempGimmickParam = PuzzleGimmickActiveParam::Create(false, false);
	buttonTrigger = new ButtonTrigger;
	buttonTrigger->AddButton(buttonObject[0], 0);
	buttonTrigger->AddButton(buttonObject[1], 0);
	baseExecutor = new LightExecutor(
		tempGimmickParam, lightObject, 1, 150, MyFunctions::Deg2Rad(0.0f), MyFunctions::Deg2Rad(90.0f), 1000.0f, true);
	gimmickController->AddGimmick(buttonTrigger, baseExecutor);

	// Light_Right
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.8636364f, 0.15f));
	objRadius = 40.0f;
	lightObject = new LightObject(objCenter, objRadius);
	objManager.Add(lightObject);

	// 光のON/OFFのギミック
	gimmickController = lightObject->GetGimmickController();
	tempGimmickParam = PuzzleGimmickActiveParam::Create(true, false);
	baseExecutor = new LightExecutor(
		tempGimmickParam, lightObject, 2, 150, MyFunctions::Deg2Rad(0.0f), MyFunctions::Deg2Rad(90.0f), 1000.0f, true);
	gimmickController->AddGimmick(new FalseTrigger, baseExecutor);

	// 
	return 0;
}

void PuzzleScene1_8::GetMasterObjectsInitPos(
	VECTOR2D &playerLightPos,
	VECTOR2D &playerShadowPos,
	VECTOR2D &goalLightPos,
	VECTOR2D &goalShadowPos) const
{
	// 
	VECTOR2D mapSize;
	this->GetMapSize(mapSize);

	playerLightPos = VECTOR2D::GetLerpPos(
		VECTOR2D::GetZero(),
		mapSize,
		VECTOR2D(0.07575758f, 0.3f));

	playerShadowPos = VECTOR2D::GetLerpPos(
		VECTOR2D::GetZero(),
		mapSize,
		VECTOR2D(0.07575758f, 0.9f));

	goalLightPos = VECTOR2D::GetLerpPos(
		VECTOR2D::GetZero(),
		mapSize,
		VECTOR2D(0.8636364f, 0.3f));

	goalShadowPos = VECTOR2D::GetLerpPos(
		VECTOR2D::GetZero(),
		mapSize,
		VECTOR2D(0.8636364f, 0.9f));
}

// 
void PuzzleScene1_8::GetMapSize(VECTOR2D &mapSize) const
{
	// 
	mapSize.SetXY(1920.0f, 1080.0f);
}

// 
uint32_t PuzzleScene1_8::GetUseLightAreaCount() const
{
	return 3;
}

// 
PuzzleScene1_9::PuzzleScene1_9() :
	BasePuzzleScene(SceneTag::ST_Puzzle1_9)
{
}

// 
PuzzleScene1_9::~PuzzleScene1_9()
{
}

// 
int PuzzleScene1_9::MapCreate(GameObjectManager &objManager)
{
	VECTOR2D objCenter;
	VECTOR2D blockSize;
	float objRadius = 0.0f;

	// 
	VECTOR2D mapSize;
	this->GetMapSize(mapSize);

	// 
	WallObject *wallObject = nullptr;
	BaseComponent *baseComponent = nullptr;
	std::vector<ButtonObject *> buttonObject;
	LightObject *lightObject = nullptr;
	GimmickObjectController *gimmickController = nullptr;
	ButtonTrigger *buttonTrigger = nullptr;
	BaseGimmickExecutor *baseExecutor = nullptr;
	PuzzleGimmickActiveParam tempGimmickParam;
	TeleportObject *teleportObjectA = nullptr;
	TeleportObject *teleportObjectB = nullptr;

	// 
	buttonObject.resize(0);

	// Wall_Top
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.5f, 0.0f));
	blockSize = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(1.0f, 0.05f));
	wallObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(wallObject);

	// Wall_Bottom
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.5f, 1.0f));
	blockSize = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(1.0f, 0.05f));
	wallObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(wallObject);

	// Wall_Left
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.0f, 0.5f));
	blockSize = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.03030303f, 1.0f));
	wallObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(wallObject);

	// Wall_Right
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(1.0f, 0.5f));
	blockSize = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.03030303f, 1.0f));
	wallObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(wallObject);


	// Obstacle_Upper
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.5f, 0.8f));
	blockSize = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.4848485f, 0.05f));
	wallObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(wallObject);

	// Mirror_1
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.1672727f, 0.5f)) + VECTOR2D(100.f, 0.0f);
	blockSize = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.1212121f, 0.015f));
	wallObject = new MirrorObject(false, objCenter, blockSize, MyFunctions::Deg2Rad(45.0000038f), 0);
	objManager.Add(wallObject);

	// Mirror_2
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.8333333f, 0.2f));
	blockSize = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.1212121f, 0.015f));
	wallObject = new MirrorObject(false, objCenter, blockSize, MyFunctions::Deg2Rad(32.0993814f), 2);
	objManager.Add(wallObject);

	// Light_Left
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.1666667f, 0.1f)) + VECTOR2D(100.f, 0.0f);
	objRadius = 40.0f;
	lightObject = new LightObject(objCenter, objRadius);
	objManager.Add(lightObject);

	// 光のON/OFFのギミック
	gimmickController = lightObject->GetGimmickController();
	tempGimmickParam = PuzzleGimmickActiveParam::Create(true, false);
	baseExecutor = new LightExecutor(
		tempGimmickParam, lightObject, 0, 100, MyFunctions::Deg2Rad(0.0f), MyFunctions::Deg2Rad(90.0f), 1500.0f, true);
	gimmickController->AddGimmick(new FalseTrigger, baseExecutor);

	// 
	return 0;
}

void PuzzleScene1_9::GetMasterObjectsInitPos(
	VECTOR2D &playerLightPos,
	VECTOR2D &playerShadowPos,
	VECTOR2D &goalLightPos,
	VECTOR2D &goalShadowPos) const
{
	// 
	VECTOR2D mapSize;
	this->GetMapSize(mapSize);

	playerLightPos = VECTOR2D::GetLerpPos(
		VECTOR2D::GetZero(),
		mapSize,
		VECTOR2D(0.1666667f, 0.3f));

	playerShadowPos = VECTOR2D::GetLerpPos(
		VECTOR2D::GetZero(),
		mapSize,
		VECTOR2D(0.5f, 0.9f));

	goalLightPos = VECTOR2D::GetLerpPos(
		VECTOR2D::GetZero(),
		mapSize,
		VECTOR2D(0.8636364f, 0.45f));

	goalShadowPos = VECTOR2D::GetLerpPos(
		VECTOR2D::GetZero(),
		mapSize,
		VECTOR2D(0.5f, 0.7f));
}

// 
void PuzzleScene1_9::GetMapSize(VECTOR2D &mapSize) const
{
	// 
	mapSize.SetXY(1920.0f, 1080.0f);
}

// 
uint32_t PuzzleScene1_9::GetUseLightAreaCount() const
{
	return 1;
}

// 
PuzzleScene1_10::PuzzleScene1_10() :
	BasePuzzleScene(SceneTag::ST_Puzzle1_10)
{
}

// 
PuzzleScene1_10::~PuzzleScene1_10()
{
}

// 
int PuzzleScene1_10::MapCreate(GameObjectManager &objManager)
{
	VECTOR2D objCenter;
	VECTOR2D blockSize;
	float objRadius = 0.0f;

	// 
	VECTOR2D mapSize;
	this->GetMapSize(mapSize);

	// 
	WallObject *wallObject = nullptr;
	BaseComponent *baseComponent = nullptr;
	std::vector<ButtonObject *> buttonObject;
	LightObject *lightObject = nullptr;
	GimmickObjectController *gimmickController = nullptr;
	ButtonTrigger *buttonTrigger = nullptr;
	BaseGimmickExecutor *baseExecutor = nullptr;
	PuzzleGimmickActiveParam tempGimmickParam;
	TeleportObject *teleportObjectA = nullptr;
	TeleportObject *teleportObjectB = nullptr;

	// 
	buttonObject.resize(0);

	// Wall_Top
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.5f, 0.0f));
	blockSize = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(1.0f, 0.05f));
	wallObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(wallObject);

	// Wall_Bottom
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.5f, 1.0f));
	blockSize = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(1.0f, 0.05f));
	wallObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(wallObject);

	// Wall_Left
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.0f, 0.5f));
	blockSize = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.03030303f, 1.0f));
	wallObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(wallObject);

	// Wall_Right
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(1.0f, 0.5f));
	blockSize = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.03030303f, 1.0f));
	wallObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(wallObject);

	// Obstacle_Upper
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.5f, 0.5f));
	blockSize = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.969697f, 0.05f));
	wallObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(wallObject);

	// Obstacle_Lower
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.4393939f, 0.85f));
	blockSize = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.8484849f, 0.05f));
	wallObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(wallObject);

	// Obstacle_Vertical
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.3787879f, 0.4f));
	blockSize = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.04848485f, 0.2f));
	wallObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(wallObject);

	// Light_Left
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.04545455f, 0.2f));
	objRadius = 40.0f;
	lightObject = new LightObject(objCenter, objRadius);
	objManager.Add(lightObject);

	// 光のON/OFFのギミック
	gimmickController = lightObject->GetGimmickController();
	tempGimmickParam = PuzzleGimmickActiveParam::Create(true, false);
	baseExecutor = new LightExecutor(
		tempGimmickParam, lightObject, 0, 150, MyFunctions::Deg2Rad(270.0f), MyFunctions::Deg2Rad(90.0f), 1500.0f, true);
	gimmickController->AddGimmick(new FalseTrigger, baseExecutor);

	// Light_Center
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.04545455f, 0.6f));
	objRadius = 40.0f;
	lightObject = new LightObject(objCenter, objRadius);
	objManager.Add(lightObject);

	// 光のON/OFFのギミック
	gimmickController = lightObject->GetGimmickController();
	tempGimmickParam = PuzzleGimmickActiveParam::Create(true, false);
	baseExecutor = new LightExecutor(
		tempGimmickParam, lightObject, 1, 150, MyFunctions::Deg2Rad(270.0f), MyFunctions::Deg2Rad(90.0f), 1500.0f, true);
	gimmickController->AddGimmick(new FalseTrigger, baseExecutor);

	// Light_Right
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.9545454f, 0.7f));
	objRadius = 40.0f;
	lightObject = new LightObject(objCenter, objRadius);
	objManager.Add(lightObject);

	// 光のON/OFFのギミック
	gimmickController = lightObject->GetGimmickController();
	tempGimmickParam = PuzzleGimmickActiveParam::Create(true, false);
	baseExecutor = new LightExecutor(
		tempGimmickParam, lightObject, 2, 150, MyFunctions::Deg2Rad(90.0f), MyFunctions::Deg2Rad(90.0f), 1500.0f, true);
	gimmickController->AddGimmick(new FalseTrigger, baseExecutor);

	// WarpSwitch_Red_1
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.8636364f, 0.2f));
	blockSize = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.04848485f, 0.08f));
	teleportObjectA = new TeleportObject(objCenter, blockSize);
	objManager.Add(teleportObjectA);

	// WarpSwitch_Red_2
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.8636364f, 0.7f));
	blockSize = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.04848485f, 0.08f));
	teleportObjectB = new TeleportObject(objCenter, blockSize);
	objManager.Add(teleportObjectB);

	// WarpSwitch_Red_1とWarpSwitch_Red_2を紐づける
	teleportObjectA->GetTeleportController()->ConnectPair(teleportObjectB->GetTeleportController());

	// WarpSwitch_Green_1
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.8636364f, 1.0f));
	blockSize = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.04848485f, 0.08f));
	teleportObjectA = new TeleportObject(objCenter, blockSize);
	objManager.Add(teleportObjectA);

	// WarpSwitch_Green_2
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.8636364f, 0.4f));
	blockSize = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), mapSize, VECTOR2D(0.04848485f, 0.08f));
	teleportObjectB = new TeleportObject(objCenter, blockSize);
	objManager.Add(teleportObjectB);

	// WarpSwitch_Green_1とWarpSwitch_Green_2を紐づける
	teleportObjectA->GetTeleportController()->ConnectPair(teleportObjectB->GetTeleportController());

	// 
	return 0;
}

void PuzzleScene1_10::GetMasterObjectsInitPos(
	VECTOR2D &playerLightPos,
	VECTOR2D &playerShadowPos,
	VECTOR2D &goalLightPos,
	VECTOR2D &goalShadowPos) const
{
	// 
	VECTOR2D mapSize;
	this->GetMapSize(mapSize);

	playerLightPos = VECTOR2D::GetLerpPos(
		VECTOR2D::GetZero(),
		mapSize,
		VECTOR2D(0.1363636f, 0.2f));

	playerShadowPos = VECTOR2D::GetLerpPos(
		VECTOR2D::GetZero(),
		mapSize,
		VECTOR2D(0.1363636f, 1.0f));

	goalLightPos = VECTOR2D::GetLerpPos(
		VECTOR2D::GetZero(),
		mapSize,
		VECTOR2D(0.4393939f, 0.7f));

	goalShadowPos = VECTOR2D::GetLerpPos(
		VECTOR2D::GetZero(),
		mapSize,
		VECTOR2D(0.4393939f, 0.4f));
}

// 
void PuzzleScene1_10::GetMapSize(VECTOR2D &mapSize) const
{
	// 
	mapSize.SetXY(1920.0f, 1080.0f);
}

// 
uint32_t PuzzleScene1_10::GetUseLightAreaCount() const
{
	return 3;
}
