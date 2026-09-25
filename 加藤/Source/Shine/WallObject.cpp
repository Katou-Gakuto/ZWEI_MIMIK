#include "DxLib.h"

#include "ShineManager.h"
#include "TestObjectBase.h"
#include "WallObject.h"

WallObject::WallObject()
: TestObjectBase()
, mstWallData()
{
}

WallObject::~WallObject()
{
}

void WallObject::Init()
{
    mstWallData.WallObjectVertexData[VERTEX_POS_NAME_NUMBER::VERTEX_POS_NAME_LEFT_UP]    = Vector2(mv2Position.x - (mv2Size.x * 0.5f), mv2Position.y - (mv2Size.y * 0.5f));
    mstWallData.WallObjectVertexData[VERTEX_POS_NAME_NUMBER::VERTEX_POS_NAME_LEFT_DOWN]  = Vector2(mv2Position.x - (mv2Size.x * 0.5f), mv2Position.y + (mv2Size.y * 0.5f));
    mstWallData.WallObjectVertexData[VERTEX_POS_NAME_NUMBER::VERTEX_POS_NAME_RIGHT_UP]   = Vector2(mv2Position.x + (mv2Size.x * 0.5f), mv2Position.y - (mv2Size.y * 0.5f));
    mstWallData.WallObjectVertexData[VERTEX_POS_NAME_NUMBER::VERTEX_POS_NAME_RIGHT_DOWN] = Vector2(mv2Position.x + (mv2Size.x * 0.5f), mv2Position.y + (mv2Size.y * 0.5f));
    SetAllEdges_ShineMap();
}

void WallObject::Finalize()
{
}

void WallObject::Update()
{
    if (mstWallData.MoveFlag)
    {
        ChangeMoveEdges_ShineMap();
        mstWallData.MoveFlag = false;
    }
}

void WallObject::Draw()
{
    const Vector2 leftUp = mstWallData.WallObjectVertexData[VERTEX_POS_NAME_NUMBER::VERTEX_POS_NAME_LEFT_UP];
    const Vector2 rightDown = mstWallData.WallObjectVertexData[VERTEX_POS_NAME_NUMBER::VERTEX_POS_NAME_RIGHT_DOWN];
    DrawBox(leftUp.x, leftUp.y, rightDown.x, rightDown.y, GetColor(0, 255, 0), TRUE);
}

// 全辺を光マップに設定
void WallObject::SetAllEdges_ShineMap()
{    
    Vector2_Int gridLeftUpVertexData =
        Vector2_Int(mstWallData.WallObjectVertexData[VERTEX_POS_NAME_NUMBER::VERTEX_POS_NAME_LEFT_UP].x * mpShineManager->MAP_TO_GRID_SCALE_X,
                    mstWallData.WallObjectVertexData[VERTEX_POS_NAME_NUMBER::VERTEX_POS_NAME_LEFT_UP].y * mpShineManager->MAP_TO_GRID_SCALE_Y);

    Vector2_Int gridRightDownVertexData =
        Vector2_Int(mstWallData.WallObjectVertexData[VERTEX_POS_NAME_NUMBER::VERTEX_POS_NAME_RIGHT_DOWN].x * mpShineManager->MAP_TO_GRID_SCALE_X,
                    mstWallData.WallObjectVertexData[VERTEX_POS_NAME_NUMBER::VERTEX_POS_NAME_RIGHT_DOWN].y * mpShineManager->MAP_TO_GRID_SCALE_Y);

    // 辺が含まれるグリッドの数
    Vector2_Int GridNumber =
        Vector2_Int(gridRightDownVertexData.x - gridLeftUpVertexData.x,
                    gridRightDownVertexData.y - gridLeftUpVertexData.y);

    // 右上のグリッドの数
    Vector2_Int GridIndex =
        Vector2_Int(gridLeftUpVertexData.x,
                    gridLeftUpVertexData.y);
    
    // 光の辺情報クリア
    mstWallData.ShineMapMyEdfeData.clear();

    // 全体がマップ外か判定
    if ((((GridIndex.x + GridNumber.x) < 0) || (mpShineManager->MAP_ARRAY_SIZE_X <= GridIndex.x)) ||
        (((GridIndex.y + GridNumber.y) < 0) || (mpShineManager->MAP_ARRAY_SIZE_Y <= GridIndex.y)))
    {
        return;
    }

    // 左右の辺を入力
    for (int yNumber = 0; yNumber <= GridNumber.y; ++yNumber)
    {
        // 高さがグリッド内か
        if (((GridIndex.y + yNumber) < 0) || (mpShineManager->MAP_ARRAY_SIZE_Y <= (GridIndex.y + yNumber)))
        {
            //continue;
        }

        // 【左】
        LineDataSetting(Vector2_Int(GridIndex.x, GridIndex.y + yNumber),
                        mstWallData.WallObjectVertexData[VERTEX_POS_NAME_NUMBER::VERTEX_POS_NAME_LEFT_UP],
                        mstWallData.WallObjectVertexData[VERTEX_POS_NAME_NUMBER::VERTEX_POS_NAME_LEFT_DOWN],
                        false
                    );

        // 【左】
        LineDataSetting(Vector2_Int(GridIndex.x + GridNumber.x, GridIndex.y + yNumber),
                        mstWallData.WallObjectVertexData[VERTEX_POS_NAME_NUMBER::VERTEX_POS_NAME_RIGHT_UP],
                        mstWallData.WallObjectVertexData[VERTEX_POS_NAME_NUMBER::VERTEX_POS_NAME_RIGHT_DOWN],
                        false
                    );
    }

    // 上下の辺を入力
    for (int xNumber = 0; xNumber <= GridNumber.x; ++xNumber)
    {
        // 横がグリッド内か
        if (((GridIndex.x + xNumber) < 0) || (mpShineManager->MAP_ARRAY_SIZE_X <= (GridIndex.x + xNumber)))
        {
            continue;
        }

        // 【上】
        LineDataSetting(Vector2_Int(GridIndex.x + xNumber, GridIndex.y),
                        mstWallData.WallObjectVertexData[VERTEX_POS_NAME_NUMBER::VERTEX_POS_NAME_LEFT_UP],
                        mstWallData.WallObjectVertexData[VERTEX_POS_NAME_NUMBER::VERTEX_POS_NAME_RIGHT_UP],
                        true
                    );

        // 【下】
        LineDataSetting(Vector2_Int(GridIndex.x + xNumber, GridIndex.y + GridNumber.y),
                        mstWallData.WallObjectVertexData[VERTEX_POS_NAME_NUMBER::VERTEX_POS_NAME_LEFT_DOWN],
                        mstWallData.WallObjectVertexData[VERTEX_POS_NAME_NUMBER::VERTEX_POS_NAME_RIGHT_DOWN],
                        true
                    );
    }
}

// 動いた辺情報を光マップ反映
void WallObject::ChangeMoveEdges_ShineMap()
{
}

// ライン情報設定処理
void WallObject::LineDataSetting(Vector2_Int gridIndex, Vector2 linePos1, Vector2 linePos2, bool yFlag)
{
    int checkValue = yFlag ? gridIndex.y : gridIndex.x;
    if ((0 <= checkValue) && (checkValue < (yFlag ? mpShineManager->MAP_ARRAY_SIZE_Y : mpShineManager->MAP_ARRAY_SIZE_X)))
    {
        LINE_POS linePos;
        linePos.id = mpShineManager->GetNewLineID();
        linePos.linePos1 = mpShineManager->AdjustPositionToGrid(Vector2_Int(gridIndex.x, gridIndex.y), linePos1);
        linePos.linePos2 = mpShineManager->AdjustPositionToGrid(Vector2_Int(gridIndex.x, gridIndex.y), linePos2);
        mpShineManager->mstMapObjectGridData[gridIndex.y][gridIndex.x].LinePoss.push_back(linePos);

        // データとして保持
        int linePosIndex = static_cast<int>(mpShineManager->mstMapObjectGridData[gridIndex.y][gridIndex.x].LinePoss.size()) - 1;
        LINE_POS& linePosAddress = mpShineManager->mstMapObjectGridData[gridIndex.y][gridIndex.x].LinePoss[linePosIndex];
        mstWallData.ShineMapMyEdfeData.push_back(SHINE_GRID_SET_LINE_DATA(&linePosAddress.linePos1, &linePosAddress.linePos2, linePos.id));
    }
}