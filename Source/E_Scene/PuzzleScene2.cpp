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
    // 
    return 0;
}

void PuzzleScene2_1::GetMastObjectsInitPos(
    VECTOR2D &playerLightPos,
    VECTOR2D &playerShadowPos,
    VECTOR2D &goalLightPos,
    VECTOR2D &goalShadowPos) const
{
}

// 
void PuzzleScene2_1::GetMapSize(VECTOR2D &mapSize) const
{
}

// 
uint32_t PuzzleScene2_1::GetUseLightAreaCount() const
{
    // 
    return 0;
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
}

// 
void PuzzleScene2_2::GetMapSize(VECTOR2D &mapSize) const
{
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
}

// 
void PuzzleScene2_3::GetMapSize(VECTOR2D &mapSize) const
{
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
}

// 
void PuzzleScene2_4::GetMapSize(VECTOR2D &mapSize) const
{
}

// 
uint32_t PuzzleScene2_4::GetUseLightAreaCount() const
{
    // 
    return 0;
}
