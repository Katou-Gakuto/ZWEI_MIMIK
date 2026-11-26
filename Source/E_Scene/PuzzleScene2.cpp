#include "PuzzleScene2.h"

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
PuzzleScene2_1::PuzzleScene2_1() :
    BasePuzzleScene(SceneTag::ST_Puzzle2_1)
{
}

// 
PuzzleScene2_1::~PuzzleScene2_1()
{
}

// 
int PuzzleScene2_1::MapCreate(GameObjectManager &objManager)
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
	RouteMoveExecutor *moveExecutor = nullptr;
	PuzzleGimmickActiveParam tempGimmickParam;
	TeleportObject *teleportObjectA = nullptr;
	TeleportObject *teleportObjectB = nullptr;

	// Wall_Top
	objCenter = VECTOR2D(960.0f, 0.0f);
	blockSize = VECTOR2D(1920.0f, 54.0f);
	wallObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(wallObject);

	// Wall_Bottom
	objCenter = VECTOR2D(960.0f, 1080.0f);
	blockSize = VECTOR2D(1920.0f, 54.0f);
	wallObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(wallObject);

	//  Wall_Left
	objCenter = VECTOR2D(29.09091f, 540.0f);
	blockSize = VECTOR2D(58.18182f, 1080.0f);
	wallObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(wallObject);

	// Wall_Right
	objCenter = VECTOR2D(1890.909f, 540.0f);
	blockSize = VECTOR2D(58.18182f, 1080.0f);
	wallObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(wallObject);

	// Obstacle_Right
	objCenter = VECTOR2D(295.5636f, 540.0f);
	blockSize = VECTOR2D(465.4546f, 54.0f);
	wallObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(wallObject);

	// Obstacle_Left
	objCenter = VECTOR2D(960.0f, 540.0f);
	blockSize = VECTOR2D(465.4546f, 54.0f);
	wallObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(wallObject);

	// Light_Left(固定)
	objCenter = VECTOR2D(622.5455f, 1074.6f);
	objRadius = 40.0f;
	lightObject = new LightObject(objCenter, objRadius);
	objManager.Add(lightObject);

	// 光のON/OFFのギミック
	gimmickController = lightObject->GetGimmickController();
	tempGimmickParam = PuzzleGimmickActiveParam::Create(true, false, false);
	baseExecutor = new LightExecutor(
		tempGimmickParam, lightObject, 0, 150, MyFunctions::Deg2Rad(0.0f), MyFunctions::Deg2Rad(90.0f), 2000.0f, true);
	gimmickController->AddGimmick(new FalseTrigger, baseExecutor);

	// Light_Center(動かせる)
	objCenter = VECTOR2D(1309.091f, 324.0f);
	objRadius = 40.0f;
	lightObject = new LightObject(objCenter, objRadius);
	objManager.Add(lightObject);

	// 光のON/OFFのギミック
	gimmickController = lightObject->GetGimmickController();
	tempGimmickParam = PuzzleGimmickActiveParam::Create(true, false, false);
	baseExecutor = new LightExecutor(
		tempGimmickParam, lightObject, 1, 150, MyFunctions::Deg2Rad(0.0f), MyFunctions::Deg2Rad(90.0f), 2000.0f, true);
	gimmickController->AddGimmick(new FalseTrigger, baseExecutor);

	// Light_CenterにHoldを追加
	lightObject->AddComponent(new HoldObjectController(lightObject, false, false, false, true, false));

	// Light_Right(固定)
	objCenter = VECTOR2D(1659.346f, 1055.16f);
	objRadius = 40.0f;
	lightObject = new LightObject(objCenter, objRadius);
	objManager.Add(lightObject);

	// 光のON/OFFのギミック
	gimmickController = lightObject->GetGimmickController();
	tempGimmickParam = PuzzleGimmickActiveParam::Create(true, false, false);
	baseExecutor = new LightExecutor(
		tempGimmickParam, lightObject, 2, 150, MyFunctions::Deg2Rad(0.0f), MyFunctions::Deg2Rad(90.0f), 2000.0f, true);
	gimmickController->AddGimmick(new FalseTrigger, baseExecutor);

	// PushableBlock_1
	objCenter = VECTOR2D(612.0728f, 622.08f);
	blockSize = VECTOR2D(290.9091f, 54.0f);
	wallObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(wallObject);

	// PushableBlock_1にHoldを追加
	wallObject->AddComponent(new HoldObjectController(wallObject, false, false, false, true, false));

	// PushableBlock_2
	objCenter = VECTOR2D(877.3818f, 388.8f);
	blockSize = VECTOR2D(81.45454f, 270.0f);
	wallObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(wallObject);

	// PushableBlock_2にHoldを追加
	wallObject->AddComponent(new HoldObjectController(wallObject, false, false, false, true, false));

	// 
	return 0;
}

void PuzzleScene2_1::GetMastObjectsInitPos(
	VECTOR2D &playerLightPos,
	VECTOR2D &playerShadowPos,
	VECTOR2D &goalLightPos,
	VECTOR2D &goalShadowPos) const
{
	// WhiteSpawn
	playerLightPos = VECTOR2D(261.8182f, 864.0f);

	// BlackSpawn
	playerShadowPos = VECTOR2D(261.8182f, 378.0f);

	// WhiteGoal
	goalLightPos = VECTOR2D(1658.182f, 864.0f);

	// BlackGoal
	goalLightPos = VECTOR2D(1658.182f, 216.0f);
}

// 
void PuzzleScene2_1::GetMapSize(VECTOR2D &mapSize) const
{
	// 
	mapSize = VECTOR2D(1920.0f, 1080.0f);
}

// 
uint32_t PuzzleScene2_1::GetUseLightAreaCount() const
{
    // 
    return 3;
}

// 
PuzzleScene2_2::PuzzleScene2_2() :
    BasePuzzleScene(SceneTag::ST_Puzzle2_2)
{
}

// 
PuzzleScene2_2::~PuzzleScene2_2()
{
}

// 
int PuzzleScene2_2::MapCreate(GameObjectManager &objManager)
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
	RouteMoveExecutor *moveExecutor = nullptr;
	PuzzleGimmickActiveParam tempGimmickParam;
	TeleportObject *teleportObjectA = nullptr;
	TeleportObject *teleportObjectB = nullptr;

	// 
	buttonObject.resize(4);

	// Wall_Top
	objCenter = VECTOR2D(960.0f, 0.0f);
	blockSize = VECTOR2D(1920.0f, 54.0f);
	wallObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(wallObject);

	// Wall_Bottom
	objCenter = VECTOR2D(960.0f, 1080.0f);
	blockSize = VECTOR2D(1920.0f, 54.0f);
	wallObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(wallObject);

	//  Wall_Left
	objCenter = VECTOR2D(29.09091f, 540.0f);
	blockSize = VECTOR2D(58.18182f, 1080.0f);
	wallObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(wallObject);

	// Wall_Right
	objCenter = VECTOR2D(1890.909f, 540.0f);
	blockSize = VECTOR2D(58.18182f, 1080.0f);
	wallObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(wallObject);

	// Obstacle_Upper
	objCenter = VECTOR2D(960.0f, 535.68f);
	blockSize = VECTOR2D(1920.0f, 54.0f);
	wallObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(wallObject);

	// Switch_1
	objCenter = VECTOR2D(610.9091f, 216.0f);
	blockSize = VECTOR2D(116.3636f, 108.0f);
	buttonObject[0] = new ButtonObject(false, 0, objCenter, blockSize);
	objManager.Add(buttonObject[0]);

	// Switch_2
	objCenter = VECTOR2D(1192.727f, 216.0f);
	blockSize = VECTOR2D(116.3636f, 108.0f);
	buttonObject[1] = new ButtonObject(false, 0, objCenter, blockSize);
	objManager.Add(buttonObject[1]);

	// Switch_3
	objCenter = VECTOR2D(378.1818f, 864.0f);
	blockSize = VECTOR2D(116.3636f, 108.0f);
	buttonObject[2] = new ButtonObject(false, 0, objCenter, blockSize);
	objManager.Add(buttonObject[2]);

	// Switch_4
	objCenter = VECTOR2D(960.0f, 864.0f);
	blockSize = VECTOR2D(116.3636f, 108.0f);
	buttonObject[3] = new ButtonObject(false, 0, objCenter, blockSize);
	objManager.Add(buttonObject[3]);

	// Light_1
	objCenter = VECTOR2D(610.9091f, 513.0f);
	objRadius = 40.0f;
	lightObject = new LightObject(objCenter, objRadius);
	objManager.Add(lightObject);

	// 光のON/OFFのギミック
	gimmickController = lightObject->GetGimmickController();
	tempGimmickParam = PuzzleGimmickActiveParam::Create(true, false, false);
	baseExecutor = new LightExecutor(
		tempGimmickParam, lightObject, 1, 150, MyFunctions::Deg2Rad(0.0f), MyFunctions::Deg2Rad(90.0f), 2000.0f, true);
	gimmickController->AddGimmick(new FalseTrigger, baseExecutor);

	// Light_2
	objCenter = VECTOR2D(1192.727f, 513.0f);
	objRadius = 40.0f;
	lightObject = new LightObject(objCenter, objRadius);
	objManager.Add(lightObject);

	// 光のON/OFFのギミック
	gimmickController = lightObject->GetGimmickController();
	tempGimmickParam = PuzzleGimmickActiveParam::Create(true, false, false);
	baseExecutor = new LightExecutor(
		tempGimmickParam, lightObject, 1, 150, MyFunctions::Deg2Rad(0.0f), MyFunctions::Deg2Rad(90.0f), 2000.0f, true);
	gimmickController->AddGimmick(new FalseTrigger, baseExecutor);

	// Light_3
	objCenter = VECTOR2D(1658.182f, 513.0f);
	objRadius = 40.0f;
	lightObject = new LightObject(objCenter, objRadius);
	objManager.Add(lightObject);

	// 光のON/OFFのギミック
	gimmickController = lightObject->GetGimmickController();
	tempGimmickParam = PuzzleGimmickActiveParam::Create(true, false, false);
	baseExecutor = new LightExecutor(
		tempGimmickParam, lightObject, 1, 150, MyFunctions::Deg2Rad(0.0f), MyFunctions::Deg2Rad(90.0f), 2000.0f, true);
	gimmickController->AddGimmick(new FalseTrigger, baseExecutor);

	// Light_4
	objCenter = VECTOR2D(261.8182f, 1026.0f);
	objRadius = 40.0f;
	lightObject = new LightObject(objCenter, objRadius);
	objManager.Add(lightObject);

	// 光のON/OFFのギミック
	gimmickController = lightObject->GetGimmickController();
	tempGimmickParam = PuzzleGimmickActiveParam::Create(true, false, false);
	baseExecutor = new LightExecutor(
		tempGimmickParam, lightObject, 1, 150, MyFunctions::Deg2Rad(0.0f), MyFunctions::Deg2Rad(90.0f), 2000.0f, true);
	gimmickController->AddGimmick(new FalseTrigger, baseExecutor);

	// Light_5
	objCenter = VECTOR2D(960.0f, 1026.0f);
	objRadius = 40.0f;
	lightObject = new LightObject(objCenter, objRadius);
	objManager.Add(lightObject);

	// 光のON/OFFのギミック
	gimmickController = lightObject->GetGimmickController();
	tempGimmickParam = PuzzleGimmickActiveParam::Create(true, false, false);
	baseExecutor = new LightExecutor(
		tempGimmickParam, lightObject, 1, 150, MyFunctions::Deg2Rad(0.0f), MyFunctions::Deg2Rad(90.0f), 2000.0f, true);
	gimmickController->AddGimmick(new FalseTrigger, baseExecutor);

	// Light_6
	objCenter = VECTOR2D(1658.182f, 1026.0f);
	objRadius = 40.0f;
	lightObject = new LightObject(objCenter, objRadius);
	objManager.Add(lightObject);

	// 光のON/OFFのギミック
	gimmickController = lightObject->GetGimmickController();
	tempGimmickParam = PuzzleGimmickActiveParam::Create(true, false, false);
	baseExecutor = new LightExecutor(
		tempGimmickParam, lightObject, 1, 150, MyFunctions::Deg2Rad(0.0f), MyFunctions::Deg2Rad(90.0f), 2000.0f, true);
	gimmickController->AddGimmick(new FalseTrigger, baseExecutor);

	// 
	return 0;
}

void PuzzleScene2_2::GetMastObjectsInitPos(
    VECTOR2D &playerLightPos,
    VECTOR2D &playerShadowPos,
    VECTOR2D &goalLightPos,
    VECTOR2D &goalShadowPos) const
{
	// WhiteSpawn
	playerLightPos = VECTOR2D(261.8182f, 864.0f);

	// BlackSpawn
	playerShadowPos = VECTOR2D(261.8182f, 216.0f);

	// WhiteGoal
	goalLightPos = VECTOR2D(1658.182f, 864.0f);

	// BlackGoal
	goalLightPos = VECTOR2D(1658.182f, 216.0f);
}

// 
void PuzzleScene2_2::GetMapSize(VECTOR2D &mapSize) const
{
	// 
	mapSize = VECTOR2D(1920.0f, 1080.0f);
}

// 
uint32_t PuzzleScene2_2::GetUseLightAreaCount() const
{
    // 
    return 6;
}

// 
PuzzleScene2_3::PuzzleScene2_3() :
    BasePuzzleScene(SceneTag::ST_Puzzle2_3)
{
}

// 
PuzzleScene2_3::~PuzzleScene2_3()
{
}

// 
int PuzzleScene2_3::MapCreate(GameObjectManager &objManager)
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
	RouteMoveExecutor *moveExecutor = nullptr;
	PuzzleGimmickActiveParam tempGimmickParam;
	TeleportObject *teleportObjectA = nullptr;
	TeleportObject *teleportObjectB = nullptr;

	// 
	buttonObject.resize(2);

	// Wall_Top
	objCenter = VECTOR2D(960.0f, 0.0f);
	blockSize = VECTOR2D(1920.0f, 54.0f);
	wallObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(wallObject);

	// Wall_Bottom
	objCenter = VECTOR2D(960.0f, 1080.0f);
	blockSize = VECTOR2D(1920.0f, 54.0f);
	wallObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(wallObject);

	//  Wall_Left
	objCenter = VECTOR2D(29.09091f, 540.0f);
	blockSize = VECTOR2D(58.18182f, 1080.0f);
	wallObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(wallObject);

	// Wall_Right
	objCenter = VECTOR2D(1890.909f, 540.0f);
	blockSize = VECTOR2D(58.18182f, 1080.0f);
	wallObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(wallObject);

	// Obstacle_FixedBlue
	objCenter = VECTOR2D(354.9091f, 540.0f);
	blockSize = VECTOR2D(651.6364f, 86.4f);
	wallObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(wallObject);

	// RotatingBlock_Pivot
	objCenter = VECTOR2D(727.2728f, 540.0f);
	blockSize = VECTOR2D(116.3636f, 108.0f);
	wallObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(wallObject);

	// RotatingBlock_PivotにHoldを追加
	wallObject->AddComponent(new HoldObjectController(wallObject, false, false, false, false, true));

	// CoopSwitch_Lower
	objCenter = VECTOR2D(436.3636f, 864.0f);
	blockSize = VECTOR2D(93.0909f, 86.39999f);
	buttonObject[0] = new ButtonObject(false, 0, objCenter, blockSize);
	objManager.Add(buttonObject[0]);

	// CoopSwitch_Upper
	objCenter = VECTOR2D(436.3636f, 216.0f);
	blockSize = VECTOR2D(93.0909f, 86.39999f);
	buttonObject[0] = new ButtonObject(false, 0, objCenter, blockSize);
	objManager.Add(buttonObject[0]);

	// Light_UpperLeft_1
	objCenter = VECTOR2D(316.5091f, 0.0f);
	objRadius = 40.0f;
	lightObject = new LightObject(objCenter, objRadius);
	objManager.Add(lightObject);

	// 光のON/OFFのギミック
	gimmickController = lightObject->GetGimmickController();
	tempGimmickParam = PuzzleGimmickActiveParam::Create(true, false, false);
	baseExecutor = new LightExecutor(
		tempGimmickParam, lightObject, 1, 150, MyFunctions::Deg2Rad(0.0f), MyFunctions::Deg2Rad(90.0f), 2000.0f, true);
	gimmickController->AddGimmick(new FalseTrigger, baseExecutor);

	// Light_Center
	objCenter = VECTOR2D(855.2728f, 0.0f);
	objRadius = 40.0f;
	lightObject = new LightObject(objCenter, objRadius);
	objManager.Add(lightObject);

	// 光のON/OFFのギミック
	gimmickController = lightObject->GetGimmickController();
	tempGimmickParam = PuzzleGimmickActiveParam::Create(true, false, false);
	baseExecutor = new LightExecutor(
		tempGimmickParam, lightObject, 1, 150, MyFunctions::Deg2Rad(0.0f), MyFunctions::Deg2Rad(90.0f), 2000.0f, true);
	gimmickController->AddGimmick(new FalseTrigger, baseExecutor);

	// Light_Right
	objCenter = VECTOR2D(1381.236f, 882.36f);
	objRadius = 40.0f;
	lightObject = new LightObject(objCenter, objRadius);
	objManager.Add(lightObject);

	// 光のON/OFFのギミック
	gimmickController = lightObject->GetGimmickController();
	tempGimmickParam = PuzzleGimmickActiveParam::Create(true, false, false);
	baseExecutor = new LightExecutor(
		tempGimmickParam, lightObject, 1, 150, MyFunctions::Deg2Rad(0.0f), MyFunctions::Deg2Rad(90.0f), 2000.0f, true);
	gimmickController->AddGimmick(new FalseTrigger, baseExecutor);

	// 
	return 0;
}

void PuzzleScene2_3::GetMastObjectsInitPos(
    VECTOR2D &playerLightPos,
    VECTOR2D &playerShadowPos,
    VECTOR2D &goalLightPos,
    VECTOR2D &goalShadowPos) const
{
	// WhiteSpawn
	playerLightPos = VECTOR2D(261.8182f, 216.0f);

	// BlackSpawn
	playerShadowPos = VECTOR2D(261.8182f, 864.0f);

	// WhiteGoal
	goalLightPos = VECTOR2D(1658.182f, 216.0f);

	// BlackGoal
	goalLightPos = VECTOR2D(1658.182f, 864.0f);
}

// 
void PuzzleScene2_3::GetMapSize(VECTOR2D &mapSize) const
{
	// 
	mapSize = VECTOR2D(1920.0f, 1080.0f);
}

// 
uint32_t PuzzleScene2_3::GetUseLightAreaCount() const
{
    // 
    return 3;
}

// 
PuzzleScene2_4::PuzzleScene2_4() :
    BasePuzzleScene(SceneTag::ST_Puzzle2_4)
{
}

// 
PuzzleScene2_4::~PuzzleScene2_4()
{
}

// 
int PuzzleScene2_4::MapCreate(GameObjectManager &objManager)
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
	RouteMoveExecutor *moveExecutor = nullptr;
	PuzzleGimmickActiveParam tempGimmickParam;
	TeleportObject *teleportObjectA = nullptr;
	TeleportObject *teleportObjectB = nullptr;

	// 
	buttonObject.resize(4);

	// Wall_Top
	objCenter = VECTOR2D(960.0f, 0.0f);
	blockSize = VECTOR2D(1920.0f, 54.0f);
	wallObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(wallObject);

	// Wall_Bottom
	objCenter = VECTOR2D(960.0f, 1080.0f);
	blockSize = VECTOR2D(1920.0f, 54.0f);
	wallObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(wallObject);

	//  Wall_Left
	objCenter = VECTOR2D(29.09091f, 540.0f);
	blockSize = VECTOR2D(58.18182f, 1080.0f);
	wallObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(wallObject);

	// Wall_Right
	objCenter = VECTOR2D(1890.909f, 540.0f);
	blockSize = VECTOR2D(58.18182f, 1080.0f);
	wallObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(wallObject);

	// Obstacle_1
	objCenter = VECTOR2D(517.8182f, 324.0f);
	blockSize = VECTOR2D(930.9091f, 54.0f);
	wallObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(wallObject);

	// Obstacle_2
	objCenter = VECTOR2D(960.0f, 540.0f);
	blockSize = VECTOR2D(814.5455f, 54.0f);
	wallObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(wallObject);

	// Obstacle_3
	objCenter = VECTOR2D(960.0f, 540.0f);
	blockSize = VECTOR2D(58.18182f, 432.0f);
	wallObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(wallObject);

	// Obstacle_4
	objCenter = VECTOR2D(552.7273f, 432.0f);
	blockSize = VECTOR2D(58.18182f, 270.0f);
	wallObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(wallObject);

	// Obstacle_5
	objCenter = VECTOR2D(1367.273f, 648.0f);
	blockSize = VECTOR2D(58.18182f, 270.0f);
	wallObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(wallObject);

	// Obstacle_6
	objCenter = VECTOR2D(1192.727f, 162.0f);
	blockSize = VECTOR2D(58.18182f, 270.0f);
	wallObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(wallObject);

	// Obstacle_7
	objCenter = VECTOR2D(1402.182f, 756.0f);
	blockSize = VECTOR2D(930.9091f, 54.0f);
	wallObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(wallObject);

	// BlockBody
	objCenter = VECTOR2D(552.7273f, 818.64f);
	blockSize = VECTOR2D(58.18182f, 162.0f);
	wallObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(wallObject);

	// PushableBlock_1
	objCenter = VECTOR2D(1425.455f, 918.0f);
	blockSize = VECTOR2D(81.45454f, 270.0f);
	wallObject = new WallObject(false, objCenter, blockSize, 0.0f);
	objManager.Add(wallObject);

	// PushableBlock_1にHoldを追加
	wallObject->AddComponent(new HoldObjectController(wallObject, false, false, false, true, false));

	// Light_Left_1(持てる)
	objCenter = VECTOR2D(190.8363f, 181.44f);
	objRadius = 40.0f;
	lightObject = new LightObject(objCenter, objRadius);
	objManager.Add(lightObject);

	// 光のON/OFFのギミック
	gimmickController = lightObject->GetGimmickController();
	tempGimmickParam = PuzzleGimmickActiveParam::Create(true, false, false);
	baseExecutor = new LightExecutor(
		tempGimmickParam, lightObject, 1, 150, MyFunctions::Deg2Rad(0.0f), MyFunctions::Deg2Rad(90.0f), 2000.0f, true);
	gimmickController->AddGimmick(new FalseTrigger, baseExecutor);

	// Light_Left_1にHoldを追加
	lightObject->AddComponent(new HoldObjectController(lightObject, false, false, false, true, false));

	// Light_Left_2(持てない)
	objCenter = VECTOR2D(18.61816f, 785.16f);
	objRadius = 40.0f;
	lightObject = new LightObject(objCenter, objRadius);
	objManager.Add(lightObject);

	// 光のON/OFFのギミック
	gimmickController = lightObject->GetGimmickController();
	tempGimmickParam = PuzzleGimmickActiveParam::Create(true, false, false);
	baseExecutor = new LightExecutor(
		tempGimmickParam, lightObject, 1, 150, MyFunctions::Deg2Rad(0.0f), MyFunctions::Deg2Rad(90.0f), 2000.0f, true);
	gimmickController->AddGimmick(new FalseTrigger, baseExecutor);

	// Light_Right_1(持てない)
	objCenter = VECTOR2D(1648.873f, 0.0f);
	objRadius = 40.0f;
	lightObject = new LightObject(objCenter, objRadius);
	objManager.Add(lightObject);

	// 光のON/OFFのギミック
	gimmickController = lightObject->GetGimmickController();
	tempGimmickParam = PuzzleGimmickActiveParam::Create(true, false, false);
	baseExecutor = new LightExecutor(
		tempGimmickParam, lightObject, 1, 150, MyFunctions::Deg2Rad(0.0f), MyFunctions::Deg2Rad(90.0f), 2000.0f, true);
	gimmickController->AddGimmick(new FalseTrigger, baseExecutor);

		// Light_Right_2(持てない)
	objCenter = VECTOR2D(552.7273f, 432.0f);
	objRadius = 40.0f;
	lightObject = new LightObject(objCenter, objRadius);
	objManager.Add(lightObject);

	// 光のON/OFFのギミック
	gimmickController = lightObject->GetGimmickController();
	tempGimmickParam = PuzzleGimmickActiveParam::Create(true, false, false);
	baseExecutor = new LightExecutor(
		tempGimmickParam, lightObject, 1, 150, MyFunctions::Deg2Rad(0.0f), MyFunctions::Deg2Rad(90.0f), 2000.0f, true);
	gimmickController->AddGimmick(new FalseTrigger, baseExecutor);
	
	// WarpSwitch_Red_1
	objCenter = VECTOR2D(164.0727f, 531.36f);
	blockSize = VECTOR2D(93.0909f, 86.39999f);
	teleportObjectA = new TeleportObject(objCenter, blockSize);
	objManager.Add(teleportObjectA);

	// WarpSwitch_Red_2
	objCenter = VECTOR2D(1245.091f, 648.0f);
	blockSize = VECTOR2D(93.0909f, 86.39999f);
	teleportObjectB = new TeleportObject(objCenter, blockSize);
	objManager.Add(teleportObjectB);

	// WarpSwitch_Red_1とWarpSwitch_Red_2を紐づける
	teleportObjectA->GetTeleportController()->ConnectPair(teleportObjectB->GetTeleportController());

	// WarpSwitch_Green_1
	objCenter = VECTOR2D(1744.291f, 603.72f);
	blockSize = VECTOR2D(93.0909f, 86.39999f);
	teleportObjectA = new TeleportObject(objCenter, blockSize);
	objManager.Add(teleportObjectA);

	// WarpSwitch_Green_2
	objCenter = VECTOR2D(679.5637f, 434.16f);
	blockSize = VECTOR2D(93.0909f, 86.39999f);
	teleportObjectB = new TeleportObject(objCenter, blockSize);
	objManager.Add(teleportObjectB);

	// WarpSwitch_Green_1とWarpSwitch_Green_2を紐づける
	teleportObjectA->GetTeleportController()->ConnectPair(teleportObjectB->GetTeleportController());

	/*
		// MovePoint_Left
		pos(x, y) : (552.7273f, 648.0f)
		size(x, y) : (116.3636f, 108.0f)

		// MovePoint_Right
		pos(x, y) : (552.7273f, 972.0f)
		size(x, y) : (116.3636f, 108.0f)
	*/

	// 
    return 0;
}

void PuzzleScene2_4::GetMastObjectsInitPos(
    VECTOR2D &playerLightPos,
    VECTOR2D &playerShadowPos,
    VECTOR2D &goalLightPos,
    VECTOR2D &goalShadowPos) const
{
	// WhiteSpawn
	playerLightPos = VECTOR2D(261.8182f, 216.0f);

	// BlackSpawn
	playerShadowPos = VECTOR2D(1658.182f, 864.0f);

	// WhiteGoal
	goalLightPos = VECTOR2D(843.6364f, 432.0f);

	// BlackGoal
	goalLightPos = VECTOR2D(1076.364f, 648.0f);
}

// 
void PuzzleScene2_4::GetMapSize(VECTOR2D &mapSize) const
{
	// 
	mapSize = VECTOR2D(1920.0f, 1080.0f);
}

// 
uint32_t PuzzleScene2_4::GetUseLightAreaCount() const
{
    // 
    return 0;
}
