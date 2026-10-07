#include "PuzzleScene.h"

#include "../A_GameObject/GameObject2D.h"
#include "../A_GameObject/GameObjectManager.h"


// 
PuzzleScene1_1::PuzzleScene1_1() :
    BasePuzzleScene(SceneTag::ST_Puzzle1_1)
{
}

// 
PuzzleScene1_1::~PuzzleScene1_1()
{
}

// 
int PuzzleScene1_1::MapCreate(GameObjectManager &objManager)
{
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
    playerLightPos = VECTOR2D(50, 0);
    playerShadowPos = VECTOR2D(50, 50);
    goalLightPos = VECTOR2D(1000, 50);
    goalShadowPos = VECTOR2D(500, 500);
}
