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


// INPROGRESS:_ 2-1作成中
// 
int PuzzleScene2_1::MapCreate(GameObjectManager &objManager)
{
	VECTOR2D objCenter;
	VECTOR2D blockSize;
	float objRadius = 0.0f;

	// 
	GameObject2D *currentObject = nullptr;
	BaseComponent *baseComponent = nullptr;
	LightObject *lightObject = nullptr;
	GimmickObjectController *gimmickController = nullptr;
	FalseTrigger *falseTrigger = nullptr;
	BaseGimmickExecutor *baseExecutor = nullptr;
	PuzzleGimmickActiveParam tempGimmickParam;

    // 枠
    {
        // Wall_Top	
        objCenter = VECTOR2D(960.0f, 0.0f);
        blockSize = VECTOR2D(1920.0f, 54.0f);
        currentObject = new WallObject(false, objCenter, blockSize, 0.0f);
        objManager.Add(currentObject);

        // Wall_Bottom
        objCenter = VECTOR2D(960.0f, 1080.0f);
        blockSize = VECTOR2D(1920.0f, 54.0f);
        currentObject = new WallObject(false, objCenter, blockSize, 0.0f);
        objManager.Add(currentObject);

        // Wall_Left
        objCenter = VECTOR2D(29.09091f, 540.0f);
        blockSize = VECTOR2D(58.18182f, 1080.0f);
        currentObject = new WallObject(false, objCenter, blockSize, 0.0f);
        objManager.Add(currentObject);

        // Wall_Right
        objCenter = VECTOR2D(1890.909f, 540.0f);
        blockSize = VECTOR2D(58.18182f, 1080.0f);
        currentObject = new WallObject(false, objCenter, blockSize, 0.0f);
        objManager.Add(currentObject);
    }

    // 壁
    {
        // Obstacle_Right
        objCenter = VECTOR2D(295.5636f, 540.0f);
        blockSize = VECTOR2D(465.4546f, 54.0f);
        currentObject = new WallObject(false, objCenter, blockSize, 0.0f);
        objManager.Add(currentObject);

        // Obstacle_Left
        objCenter = VECTOR2D(960.0f, 540.0f);
        blockSize = VECTOR2D(465.4546f, 54.0f);
        currentObject = new WallObject(false, objCenter, blockSize, 0.0f);
        objManager.Add(currentObject);

        // PushableBlock_1
        objCenter = VECTOR2D(634.1818f, 637.2f);
        blockSize = VECTOR2D(290.9091f, 54.0f);
        currentObject = new WallObject(false, objCenter, blockSize, 0.0f);
        objManager.Add(currentObject);

        // PushableBlock_2
        objCenter = VECTOR2D(877.3818f, 388.8f);
        blockSize = VECTOR2D(81.45454f, 270.0f);
        currentObject = new WallObject(false, objCenter, blockSize, 0.0f);
        objManager.Add(currentObject);
    }

    // ライト
    {
        // Light_Left(固定)
        objCenter = VECTOR2D(622.5455f, 1050.0f);
        objRadius = 40.0f;
        lightObject = new LightObject(objCenter, objRadius);
        objManager.Add(lightObject);

        // 光のON/OFFのギミック
        gimmickController = lightObject->GetGimmickController();
        tempGimmickParam = PuzzleGimmickActiveParam::Create(true, false, false);
        falseTrigger = new FalseTrigger;
        baseExecutor = new LightExecutor(
            tempGimmickParam, lightObject, 0, 150, MyFunctions::Deg2Rad(180.0f), MyFunctions::Deg2Rad(90.0f), 2000.0f, true);
        gimmickController->AddGimmick(falseTrigger, baseExecutor);

        // Light_Center(動かせる)
        objCenter = VECTOR2D(1309.091f, 324.0f);
        objRadius = 40.0f;
        lightObject = new LightObject(objCenter, objRadius);
        objManager.Add(lightObject);

        // 光のON/OFFのギミック
        gimmickController = lightObject->GetGimmickController();
        tempGimmickParam = PuzzleGimmickActiveParam::Create(true, false, false);
        falseTrigger = new FalseTrigger;
        baseExecutor = new LightExecutor(
            tempGimmickParam, lightObject, 1, 150, MyFunctions::Deg2Rad(90.0f), MyFunctions::Deg2Rad(90.0f), 2000.0f, true);
        gimmickController->AddGimmick(falseTrigger, baseExecutor);

        // Light_Right(固定)
        objCenter = VECTOR2D(1659.346f, 1050.0f);
        objRadius = 40.0f;
        lightObject = new LightObject(objCenter, objRadius);
        objManager.Add(lightObject);

        // 光のON/OFFのギミック
        gimmickController = lightObject->GetGimmickController();
        tempGimmickParam = PuzzleGimmickActiveParam::Create(true, false, false);
        falseTrigger = new FalseTrigger;
        baseExecutor = new LightExecutor(
            tempGimmickParam, lightObject, 2, 150, MyFunctions::Deg2Rad(180.0f), MyFunctions::Deg2Rad(90.0f), 2000.0f, true);
        gimmickController->AddGimmick(falseTrigger, baseExecutor);

    }

    // 
    return 0;
}

void PuzzleScene2_1::GetMastObjectsInitPos(
    VECTOR2D &playerLightPos,
    VECTOR2D &playerShadowPos,
    VECTOR2D &goalLightPos,
    VECTOR2D &goalShadowPos) const
{
	playerLightPos =  VECTOR2D(261.8182f, 634.0f);

    playerShadowPos = VECTOR2D(261.8182f, 378.0f);

    goalLightPos =    VECTOR2D(1658.182f, 864.0f);
    
	goalShadowPos =   VECTOR2D(1658.182f, 216.0f);
}

// 
void PuzzleScene2_1::GetMapSize(VECTOR2D &mapSize) const
{
	mapSize.SetXY(1920.0f, 1080.0f);
}

// ライト達の光取得
void PuzzleScene2_1::GetLightsColor(std::vector<uint32_t>& lightsColor) const
{
	lightsColor.push_back(0xff0000);
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
    // 
    return 0;
}

void PuzzleScene2_2::GetMastObjectsInitPos(
    VECTOR2D &playerLightPos,
    VECTOR2D &playerShadowPos,
    VECTOR2D &goalLightPos,
    VECTOR2D &goalShadowPos) const
{
	playerLightPos =  VECTOR2D(261.8182f, 864.0f);

    playerShadowPos = VECTOR2D(261.8182f, 216.0f);

    goalLightPos =    VECTOR2D(1658.182f, 864.0f);
    
	goalShadowPos =   VECTOR2D(1658.182f, 216.0f);
}

// 
void PuzzleScene2_2::GetMapSize(VECTOR2D &mapSize) const
{
	mapSize.SetXY(1920.0f, 1080.0f);
}

// ライト達の光取得
void PuzzleScene2_2::GetLightsColor(std::vector<uint32_t>& lightsColor) const
{
	lightsColor.push_back(0xff0000);
}

// 
uint32_t PuzzleScene2_2::GetUseLightAreaCount() const
{
    // 
    return 0;
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
    // 
    return 0;
}

void PuzzleScene2_3::GetMastObjectsInitPos(
    VECTOR2D &playerLightPos,
    VECTOR2D &playerShadowPos,
    VECTOR2D &goalLightPos,
    VECTOR2D &goalShadowPos) const
{
	playerLightPos =  VECTOR2D(261.8182f, 216.0f);

    playerShadowPos = VECTOR2D(261.8182f, 864.0f);

    goalLightPos =    VECTOR2D(1658.182f, 216.0f);
    
	goalShadowPos =   VECTOR2D(1658.182f, 864.0f);
}

// 
void PuzzleScene2_3::GetMapSize(VECTOR2D &mapSize) const
{
	mapSize.SetXY(1920.0f, 1080.0f);
}

// ライト達の光取得
void PuzzleScene2_3::GetLightsColor(std::vector<uint32_t>& lightsColor) const
{
	lightsColor.push_back(0xff0000);
}

// 
uint32_t PuzzleScene2_3::GetUseLightAreaCount() const
{
    // 
    return 0;
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
    // 
    return 0;
}

void PuzzleScene2_4::GetMastObjectsInitPos(
    VECTOR2D &playerLightPos,
    VECTOR2D &playerShadowPos,
    VECTOR2D &goalLightPos,
    VECTOR2D &goalShadowPos) const
{
	playerLightPos =  VECTOR2D(261.8182f, 216.0f);

    playerShadowPos = VECTOR2D(1658.182f, 864.0f);

    goalLightPos =    VECTOR2D(843.6364f, 432.0f);
    
	goalShadowPos =   VECTOR2D(1076.364f, 648.0f);
}

// 
void PuzzleScene2_4::GetMapSize(VECTOR2D &mapSize) const
{
	mapSize.SetXY(1920.0f, 1080.0f);
}

// ライト達の光取得
void PuzzleScene2_4::GetLightsColor(std::vector<uint32_t>& lightsColor) const
{
	lightsColor.push_back(0xff0000);
}

// 
uint32_t PuzzleScene2_4::GetUseLightAreaCount() const
{
    // 
    return 0;
}
