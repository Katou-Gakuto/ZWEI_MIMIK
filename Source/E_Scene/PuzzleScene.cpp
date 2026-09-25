#include "PuzzleScene.h"

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
int PuzzleScene1_1::MapCreate()
{
    // 
    this->GetGameObjectManager();

    // 
    return 0;
}

