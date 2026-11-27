#include "PuzzleScene4.h"

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
PuzzleScene4_1::PuzzleScene4_1() :
    BasePuzzleScene(SceneTag::ST_Puzzle4_1)
{
}

// 
PuzzleScene4_1::~PuzzleScene4_1()
{
}

// 
int PuzzleScene4_1::MapCreate(GameObjectManager &objManager)
{
    // 
    return 0;
}

void PuzzleScene4_1::GetMastObjectsInitPos(
    VECTOR2D &playerLightPos,
    VECTOR2D &playerShadowPos,
    VECTOR2D &goalLightPos,
    VECTOR2D &goalShadowPos) const
{
	playerLightPos =  VECTOR2D(145.4545f, 108.0f);

    playerShadowPos = VECTOR2D(145.4545f, 972.0f);

    goalLightPos =    VECTOR2D(203.6364f, 486.0f);
    
	goalShadowPos =   VECTOR2D(1716.364f, 486.0f);
}

// 
void PuzzleScene4_1::GetMapSize(VECTOR2D &mapSize) const
{
	mapSize.SetXY(1920.0f, 1080.0f);
}

// ライト達の光取得
void PuzzleScene4_1::GetLightsColor(std::vector<uint32_t>& lightsColor) const
{
	lightsColor.push_back(0xff0000);
}

// 
uint32_t PuzzleScene4_1::GetUseLightAreaCount() const
{
    // 
    return 0;
}

// 
PuzzleScene4_2::PuzzleScene4_2() :
    BasePuzzleScene(SceneTag::ST_Puzzle4_2)
{
}

// 
PuzzleScene4_2::~PuzzleScene4_2()
{
}

// 
int PuzzleScene4_2::MapCreate(GameObjectManager &objManager)
{
    // 
    return 0;
}

void PuzzleScene4_2::GetMastObjectsInitPos(
    VECTOR2D &playerLightPos,
    VECTOR2D &playerShadowPos,
    VECTOR2D &goalLightPos,
    VECTOR2D &goalShadowPos) const
{
	playerLightPos =  VECTOR2D(167.5636f, 155.52f);

    playerShadowPos = VECTOR2D(531.7818f, 160.92f);

    goalLightPos =    VECTOR2D(1483.636f, 108.0f);
    
	goalShadowPos =   VECTOR2D(1658.182f, 108.0f);
}

// 
void PuzzleScene4_2::GetMapSize(VECTOR2D &mapSize) const
{
	mapSize.SetXY(1920.0f, 1080.0f);
}

// ライト達の光取得
void PuzzleScene4_2::GetLightsColor(std::vector<uint32_t>& lightsColor) const
{
	lightsColor.push_back(0xff0000);
}

// 
uint32_t PuzzleScene4_2::GetUseLightAreaCount() const
{
    // 
    return 0;
}

// 
PuzzleScene4_3::PuzzleScene4_3() :
    BasePuzzleScene(SceneTag::ST_Puzzle4_3)
{
}

// 
PuzzleScene4_3::~PuzzleScene4_3()
{
}

// 
int PuzzleScene4_3::MapCreate(GameObjectManager &objManager)
{
    // 
    return 0;
}

void PuzzleScene4_3::GetMastObjectsInitPos(
    VECTOR2D &playerLightPos,
    VECTOR2D &playerShadowPos,
    VECTOR2D &goalLightPos,
    VECTOR2D &goalShadowPos) const
{
	playerLightPos =  VECTOR2D(267.6364f, 275.4f);

    playerShadowPos = VECTOR2D(261.8182f, 756.0f);

    goalLightPos =    VECTOR2D(1658.182f, 864.0f);
    
	goalShadowPos =   VECTOR2D(1658.182f, 216.0f);
}

// 
void PuzzleScene4_3::GetMapSize(VECTOR2D &mapSize) const
{
	mapSize.SetXY(1920.0f, 1080.0f);
}

// ライト達の光取得
void PuzzleScene4_3::GetLightsColor(std::vector<uint32_t>& lightsColor) const
{
	lightsColor.push_back(0xff0000);
}

// 
uint32_t PuzzleScene4_3::GetUseLightAreaCount() const
{
    // 
    return 0;
}

// 
PuzzleScene4_4::PuzzleScene4_4() :
    BasePuzzleScene(SceneTag::ST_Puzzle4_4)
{
}

// 
PuzzleScene4_4::~PuzzleScene4_4()
{
}

// 
int PuzzleScene4_4::MapCreate(GameObjectManager &objManager)
{
    // 
    return 0;
}

void PuzzleScene4_4::GetMastObjectsInitPos(
    VECTOR2D &playerLightPos,
    VECTOR2D &playerShadowPos,
    VECTOR2D &goalLightPos,
    VECTOR2D &goalShadowPos) const
{
	playerLightPos =  VECTOR2D(261.8182f, 108.0f);

    playerShadowPos = VECTOR2D(1658.182f, 972.0f);

    goalLightPos =    VECTOR2D(261.8182f, 972.0f);
    
	goalShadowPos =   VECTOR2D(1658.182f, 108.0f);
}

// 
void PuzzleScene4_4::GetMapSize(VECTOR2D &mapSize) const
{
	mapSize.SetXY(1920.0f, 1080.0f);
}

// ライト達の光取得
void PuzzleScene4_4::GetLightsColor(std::vector<uint32_t>& lightsColor) const
{
	lightsColor.push_back(0xff0000);
}

// 
uint32_t PuzzleScene4_4::GetUseLightAreaCount() const
{
    // 
    return 0;
}
