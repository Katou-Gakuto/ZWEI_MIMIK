#include "PuzzleScene.h"

#include "../A_GameObject/GameObject2D.h"
#include "../A_GameObject/GameObjectManager.h"
#include "../A_GameObject/WallObject.h"
#include "../A_GameObject/ButtonObject.h"
#include "../A_GameObject/LightObject.h"

#include "../C_Component/HoldObjectController.h"
#include "../C_Component/GimmickObjectController.h"

#include "../F_PuzzleGimmick/ButtonTrigger.h"
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
	Master::mpLightManager->ResizeArea(3);

	VECTOR2D objCenter;
	VECTOR2D blockSize;
	float objRadius = 0.0f;

	// 
	VECTOR2D displaySize = Master::mpDxLibDataManager->GetDisplaySize();

	// 
	GameObject2D *currentObject = nullptr;
	BaseComponent *baseComponent = nullptr;
	LightObject *lightObject = nullptr;
	GimmickObjectController *gimmickController = nullptr;
	BaseGimmickTrigger *baseTrigger = nullptr;
	BaseGimmickExecutor *baseExecutor = nullptr;
	PuzzleGimmickActiveParam tempGimmickParam;

	// 
	objCenter = VECTOR2D(1300.0f * 0.5f, -0.5f);
	blockSize = VECTOR2D(1300.0f, 10.0f);

	/*
	// Wall_Top	
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), displaySize, VECTOR2D(0.6255666f, 0.3889141f));
	blockSize = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), displaySize, VECTOR2D(1.0f, 0.05f));
	currentObject = new WallObject(false, objCenter, blockSize);
	objManager.Add(currentObject);
	*/

	// Wall_Bottom
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), displaySize, VECTOR2D(0.6255666f, 1.388914));
	blockSize = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), displaySize, VECTOR2D(1.0f, 0.05f));
	currentObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(currentObject);

	// Wall_Left
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), displaySize, VECTOR2D(0.1407181f, 0.8889141f));
	blockSize = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), displaySize, VECTOR2D(0.03030303f, 1.0f));
	currentObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(currentObject);

	// Wall_Right
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), displaySize, VECTOR2D(1.1407181f, 0.8889141f));
	blockSize = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), displaySize, VECTOR2D(0.03030303f, 1.0f));
	currentObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(currentObject);

	// Obstacle_Center
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), displaySize, VECTOR2D(0.5f, 0.609f));
	blockSize = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), displaySize, VECTOR2D(0.03030303f, 0.3f));
	currentObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(currentObject);

	// Obstacle_Upper
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), displaySize, VECTOR2D(0.2678788f, 0.294f));
	blockSize = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), displaySize, VECTOR2D(0.4848485f, 0.05f));
	currentObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(currentObject);

	// Light_01
	//objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), displaySize, VECTOR2D(0.5f, 0.82f));
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), displaySize, VECTOR2D(0.45f, 0.82f));
	objRadius = 40.0f;
	lightObject = new LightObject(objCenter, objRadius);
	gimmickController = lightObject->GetGimmickController();

	// 光のON/OFFのギミック
	ButtonTrigger *buttonTrigger = new ButtonTrigger;
	tempGimmickParam = PuzzleGimmickActiveParam::Create(true, false);
	baseTrigger = buttonTrigger;
	baseExecutor = new LightExecutor(
		tempGimmickParam, lightObject, 0, 50, MyFunctions::Deg2Rad(90.0f), MyFunctions::Deg2Rad(90.0f), 1000.0f, true);
	gimmickController->AddGimmick(baseTrigger, baseExecutor);

	LightArea* lightArea = Master::mpLightManager->SearchArea(0);
	if (lightArea != nullptr)
	{
		lightArea->SetLightColor(0x000000);
	}

	// ライトにHoldを追加する
	lightObject->AddComponent(new HoldObjectController(lightObject, false, true, false, true, false));

	objManager.Add(lightObject);
	{
	// Light_01
	//objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), displaySize, VECTOR2D(0.5f, 0.82f));
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), displaySize, VECTOR2D(0.85f, 0.72f));
	objRadius = 40.0f;
	lightObject = new LightObject(objCenter, objRadius);
	gimmickController = lightObject->GetGimmickController();
	// 光のON/OFFのギミック
	buttonTrigger = new ButtonTrigger;
	baseTrigger = buttonTrigger;
	baseExecutor = new LightExecutor(
		tempGimmickParam, lightObject, 1, 50, MyFunctions::Deg2Rad(120.0f), MyFunctions::Deg2Rad(90.0f), 1000.0f, true);
	gimmickController->AddGimmick(baseTrigger, baseExecutor);

		LightArea* lightArea = Master::mpLightManager->SearchArea(1);
		if (lightArea != nullptr)
		{
			lightArea->SetLightColor(0xff0000);
		}

	// ライトにHoldを追加する
	lightObject->AddComponent(new HoldObjectController(lightObject, false, true, false, true, false));
	}
	objManager.Add(lightObject);

	{
	// Light_01
	//objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), displaySize, VECTOR2D(0.5f, 0.82f));
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), displaySize, VECTOR2D(0.25f, 0.52f));
	objRadius = 40.0f;
	lightObject = new LightObject(objCenter, objRadius);
	gimmickController = lightObject->GetGimmickController();
	// 光のON/OFFのギミック
	buttonTrigger = new ButtonTrigger;
	baseTrigger = buttonTrigger;
	baseExecutor = new LightExecutor(
		tempGimmickParam, lightObject, 2, 50, MyFunctions::Deg2Rad(280.0f), MyFunctions::Deg2Rad(90.0f), 1000.0f, true);
	gimmickController->AddGimmick(baseTrigger, baseExecutor);

		LightArea* lightArea = Master::mpLightManager->SearchArea(2);
		if (lightArea != nullptr)
		{
			lightArea->SetLightColor(0x000000);
		}

	// ライトにHoldを追加する
	lightObject->AddComponent(new HoldObjectController(lightObject, false, true, false, true, false));
	}

	objManager.Add(lightObject);

	// 
	return 0;
}

// 
void PuzzleScene1_1::GetMasterObjectsInitPos(
    VECTOR2D &playerLightPos,
    VECTOR2D &playerShadowPos,
    VECTOR2D &goalLightPos,
    VECTOR2D &goalShadowPos)
{
	// 
	VECTOR2D displaySize = Master::mpDxLibDataManager->GetDisplaySize();

	playerLightPos = VECTOR2D::GetLerpPos(
		VECTOR2D::GetZero(),
		displaySize,
		VECTOR2D(0.2575758f, 0.8f));

    playerShadowPos = VECTOR2D::GetLerpPos(
		VECTOR2D::GetZero(),
		displaySize,
		VECTOR2D(0.7424242f, 0.8f));

    goalLightPos = VECTOR2D::GetLerpPos(
		VECTOR2D::GetZero(), 
		displaySize,
		VECTOR2D(0.2575758f, 0.2f));
    
	goalShadowPos = VECTOR2D::GetLerpPos(
		VECTOR2D::GetZero(),
		displaySize,
		VECTOR2D(0.7424242f, 0.2f));
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
	// 
	Master::mpLightManager->ResizeArea(1);

	VECTOR2D objCenter;
	VECTOR2D blockSize;
	float objRadius = 0.0f;

	// 
	VECTOR2D displaySize = Master::mpDxLibDataManager->GetDisplaySize();

	// 
	GameObject2D *currentObject = nullptr;
	BaseComponent *baseComponent = nullptr;
	WallObject *wallObject = nullptr;
	LightObject *lightObject = nullptr;
	std::vector<ButtonObject *> buttonObject;
	GimmickObjectController *gimmickController = nullptr;
	BaseGimmickTrigger *baseTrigger = nullptr;
	BaseGimmickExecutor *baseExecutor = nullptr;
	PuzzleGimmickActiveParam tempGimmickParam;

	// 
	objCenter = VECTOR2D(1300.0f * 0.5f, -0.5f);
	blockSize = VECTOR2D(1300.0f, 10.0f);

	/*
	// Wall_Top
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), displaySize, VECTOR2D(0.6255666f, 0.3889141f));
	blockSize = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), displaySize, VECTOR2D(1.0f, 0.05f));
	currentObject = new WallObject(false, objCenter, blockSize);
	objManager.Add(currentObject);
	*/

	// Wall_Bottom
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), displaySize, VECTOR2D(0.6255666f, 1.388914));
	blockSize = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), displaySize, VECTOR2D(1.0f, 0.05f));
	currentObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(currentObject);

	// Wall_Left
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), displaySize, VECTOR2D(0.1407181f, 0.8889141f));
	blockSize = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), displaySize, VECTOR2D(0.03030303f, 1.0f));
	currentObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(currentObject);

	// Wall_Right
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), displaySize, VECTOR2D(1.1407181f, 0.8889141f));
	blockSize = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), displaySize, VECTOR2D(0.03030303f, 1.0f));
	currentObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(currentObject);

	// Obstacle_Center
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), displaySize, VECTOR2D(0.5f, 0.609f));
	blockSize = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), displaySize, VECTOR2D(0.03030303f, 0.3f));
	currentObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(currentObject);

	// Obstacle_Upper
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), displaySize, VECTOR2D(0.2678788f, 0.294f));
	blockSize = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), displaySize, VECTOR2D(0.4848485f, 0.05f));
	currentObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(currentObject);

	// Button_Start
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), displaySize, VECTOR2D(0.4f, 0.82f));
	blockSize = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), displaySize, VECTOR2D(0.05f, 0.05f));
	buttonObject.push_back(new ButtonObject(false, 0, objCenter, blockSize));
	objManager.Add(buttonObject[buttonObject.size() - 1]);

	// Button_Goal
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), displaySize, VECTOR2D(0.2575758f, 0.2f));
	blockSize = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), displaySize, VECTOR2D(0.05f, 0.05f));
	buttonObject.push_back(new ButtonObject(false, 0, objCenter, blockSize));
	objManager.Add(buttonObject[buttonObject.size() - 1]);

	// Light_01
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), displaySize, VECTOR2D(0.6f, 0.82f));
	objRadius = 40.0f;
	lightObject = new LightObject(objCenter, objRadius);
	gimmickController = lightObject->GetGimmickController();

	// 光のON/OFFのギミック
	ButtonTrigger *buttonTrigger = new ButtonTrigger;
	buttonTrigger->AddButton(buttonObject[0], 0);
	buttonTrigger->AddButton(buttonObject[1], 1);
	tempGimmickParam = PuzzleGimmickActiveParam::Create(false, true);
	baseTrigger = buttonTrigger;
	baseExecutor = new LightExecutor(
		tempGimmickParam, lightObject, 0, 50, MyFunctions::Deg2Rad(270.0f), MyFunctions::Deg2Rad(90.0f), 1000.0f, true);
	gimmickController->AddGimmick(baseTrigger, baseExecutor);

	// ライトにHoldを追加する
	lightObject->AddComponent(new HoldObjectController(lightObject, false, true, true, true, true));

	objManager.Add(lightObject);

	// 
	return 0;
}

void PuzzleScene1_2::GetMasterObjectsInitPos(
    VECTOR2D &playerLightPos,
    VECTOR2D &playerShadowPos,
    VECTOR2D &goalLightPos,
    VECTOR2D &goalShadowPos)
{
	// 
	VECTOR2D displaySize = Master::mpDxLibDataManager->GetDisplaySize();

	playerLightPos = VECTOR2D::GetLerpPos(
		VECTOR2D::GetZero(),
		displaySize,
		VECTOR2D(0.7424242f, 0.8f));

	playerShadowPos = VECTOR2D::GetLerpPos(
		VECTOR2D::GetZero(),
		displaySize,
		VECTOR2D(0.4f, 0.82f));

	goalLightPos = VECTOR2D::GetLerpPos(
		VECTOR2D::GetZero(),
		displaySize,
		VECTOR2D(0.2575758f, 0.2f));

	goalShadowPos = VECTOR2D::GetLerpPos(
		VECTOR2D::GetZero(),
		displaySize,
		VECTOR2D(0.7424242f, 0.2f));
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
	// 
	Master::mpLightManager->ResizeArea(1);

	VECTOR2D objCenter;
	VECTOR2D blockSize;
	float objRadius = 0.0f;

	// 
	VECTOR2D displaySize = Master::mpDxLibDataManager->GetDisplaySize();

	// 
	WallObject *wallObject = nullptr;
	BaseComponent *baseComponent = nullptr;
	LightObject *lightObject = nullptr;
	GimmickObjectController *gimmickController = nullptr;
	BaseGimmickTrigger *baseTrigger = nullptr;
	BaseGimmickExecutor *baseExecutor = nullptr;
	PuzzleGimmickActiveParam tempGimmickParam;

	// 
	objCenter = VECTOR2D(1300.0f * 0.5f, -0.5f);
	blockSize = VECTOR2D(1300.0f, 10.0f);

	// Wall_Bottom
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), displaySize, VECTOR2D(0.6255666f, 1.388914));
	blockSize = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), displaySize, VECTOR2D(1.0f, 0.05f));
	wallObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(wallObject);

	// Wall_Left
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), displaySize, VECTOR2D(0.1407181f, 0.8889141f));
	blockSize = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), displaySize, VECTOR2D(0.03030303f, 1.0f));
	wallObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(wallObject);

	// Wall_Right
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), displaySize, VECTOR2D(1.1407181f, 0.8889141f));
	blockSize = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), displaySize, VECTOR2D(0.03030303f, 1.0f));
	wallObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(wallObject);

	// Obstacle_Center
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), displaySize, VECTOR2D(0.5f, 0.609f));
	blockSize = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), displaySize, VECTOR2D(0.03030303f, 0.3f));
	wallObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(wallObject);

	// Obstacle_Upper
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), displaySize, VECTOR2D(0.2678788f, 0.294f));
	blockSize = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), displaySize, VECTOR2D(0.4848485f, 0.05f));
	wallObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(wallObject);

	// Light_01
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), displaySize, VECTOR2D(0.5f, 0.82f));
	objRadius = 40.0f;
	lightObject = new LightObject(objCenter, objRadius);
	gimmickController = lightObject->GetGimmickController();

	// 光のON/OFFのギミック
	ButtonTrigger *buttonTrigger = new ButtonTrigger();
	tempGimmickParam = PuzzleGimmickActiveParam::Create(true, false);
	baseTrigger = buttonTrigger;
	baseExecutor = new LightExecutor(
		tempGimmickParam, lightObject, 0, 50, MyFunctions::Deg2Rad(90.0f), MyFunctions::Deg2Rad(90.0f), 1000.0f, true);
	gimmickController->AddGimmick(baseTrigger, baseExecutor);

	// ライトにHoldを追加する
	lightObject->AddComponent(new HoldObjectController(lightObject, false, true, false, true, false));

	// ライトをオブジェクトに追加する
	objManager.Add(lightObject);

	// 回転する四角
	objCenter = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), displaySize, VECTOR2D(0.1f, 0.5f));
	blockSize = VECTOR2D::GetLerpPos(VECTOR2D::GetZero(), displaySize, VECTOR2D(0.2f, 0.2f));
	wallObject = new WallObject(true, objCenter, blockSize, 0.0f);
	gimmickController = wallObject->GetGimmickController();

	// 時間経過で回転するギミック
	RouteData routeData(RouteOffMode::RouteOffMode_Stop, true);
	tempGimmickParam = PuzzleGimmickActiveParam::Create(true, false);
	baseTrigger = new ButtonTrigger();
	baseExecutor = new RouteMoveExecutor(tempGimmickParam, wallObject, routeData);
	gimmickController->AddGimmick(baseTrigger, baseExecutor);

	// 回転する四角を追加する
	objManager.Add(wallObject);

	// 
	return 0;
}

void PuzzleScene1_3::GetMasterObjectsInitPos(
	VECTOR2D &playerLightPos,
	VECTOR2D &playerShadowPos,
	VECTOR2D &goalLightPos,
	VECTOR2D &goalShadowPos)
{
	// 
	VECTOR2D displaySize = Master::mpDxLibDataManager->GetDisplaySize();

	playerLightPos = VECTOR2D::GetLerpPos(
		VECTOR2D::GetZero(),
		displaySize,
		VECTOR2D(0.7424242f, 0.8f));

	playerShadowPos = VECTOR2D::GetLerpPos(
		VECTOR2D::GetZero(),
		displaySize,
		VECTOR2D(0.4f, 0.82f));

	goalLightPos = VECTOR2D::GetLerpPos(
		VECTOR2D::GetZero(),
		displaySize,
		VECTOR2D(0.2575758f, 0.2f));

	goalShadowPos = VECTOR2D::GetLerpPos(
		VECTOR2D::GetZero(),
		displaySize,
		VECTOR2D(0.7424242f, 0.2f));
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
	// 
	return 0;
}

void PuzzleScene1_4::GetMasterObjectsInitPos(
	VECTOR2D &playerLightPos,
	VECTOR2D &playerShadowPos,
	VECTOR2D &goalLightPos,
	VECTOR2D &goalShadowPos)
{
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
	// 
	return 0;
}

void PuzzleScene1_5::GetMasterObjectsInitPos(
	VECTOR2D &playerLightPos,
	VECTOR2D &playerShadowPos,
	VECTOR2D &goalLightPos,
	VECTOR2D &goalShadowPos)
{
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
	// 
	return 0;
}

void PuzzleScene1_6::GetMasterObjectsInitPos(
	VECTOR2D &playerLightPos,
	VECTOR2D &playerShadowPos,
	VECTOR2D &goalLightPos,
	VECTOR2D &goalShadowPos)
{
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
	// 
	return 0;
}

void PuzzleScene1_7::GetMasterObjectsInitPos(
	VECTOR2D &playerLightPos,
	VECTOR2D &playerShadowPos,
	VECTOR2D &goalLightPos,
	VECTOR2D &goalShadowPos)
{
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
	// 
	return 0;
}

void PuzzleScene1_8::GetMasterObjectsInitPos(
	VECTOR2D &playerLightPos,
	VECTOR2D &playerShadowPos,
	VECTOR2D &goalLightPos,
	VECTOR2D &goalShadowPos)
{
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
	// 
	return 0;
}

void PuzzleScene1_9::GetMasterObjectsInitPos(
	VECTOR2D &playerLightPos,
	VECTOR2D &playerShadowPos,
	VECTOR2D &goalLightPos,
	VECTOR2D &goalShadowPos)
{
}
