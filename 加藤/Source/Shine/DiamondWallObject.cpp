#include "DxLib.h"

#include "ShineManager.h"
#include "TestObjectBase.h"
#include "DiamondWallObject.h"

DiamondWallObject::DiamondWallObject()
    : TestObjectBase()
    , mstDiamondWallData()
{
}

DiamondWallObject::~DiamondWallObject()
{
}

void DiamondWallObject::Init()
{
    const float halfWidth = mv2Size.x * 0.5f;
    const float halfHeight = mv2Size.y * 0.5f;

    // 上
    mstDiamondWallData.WallObjectVertexData[
        static_cast<int>(VERTEX_POS_NAME_NUMBER::TOP)]
        = Vector2(
            mv2Position.x,
            mv2Position.y - halfHeight
        );

    // 左
    mstDiamondWallData.WallObjectVertexData[
        static_cast<int>(VERTEX_POS_NAME_NUMBER::LEFT)]
        = Vector2(
            mv2Position.x - halfWidth,
            mv2Position.y
        );

    // 下
    mstDiamondWallData.WallObjectVertexData[
        static_cast<int>(VERTEX_POS_NAME_NUMBER::BOTTOM)]
        = Vector2(
            mv2Position.x,
            mv2Position.y + halfHeight
        );

    // 右
    mstDiamondWallData.WallObjectVertexData[
        static_cast<int>(VERTEX_POS_NAME_NUMBER::RIGHT)]
        = Vector2(
            mv2Position.x + halfWidth,
            mv2Position.y
        );

    SetAllEdges_ShineMap();
}

void DiamondWallObject::Finalize()
{
}

void DiamondWallObject::Update()
{
    if (mstDiamondWallData.MoveFlag)
    {
        // 現時点では移動処理なし
        mstDiamondWallData.MoveFlag = false;
    }
}

void DiamondWallObject::Draw()
{
    const Vector2 top =
        mstDiamondWallData.WallObjectVertexData[
            static_cast<int>(VERTEX_POS_NAME_NUMBER::TOP)];

    const Vector2 left =
        mstDiamondWallData.WallObjectVertexData[
            static_cast<int>(VERTEX_POS_NAME_NUMBER::LEFT)];

    const Vector2 bottom =
        mstDiamondWallData.WallObjectVertexData[
            static_cast<int>(VERTEX_POS_NAME_NUMBER::BOTTOM)];

    const Vector2 right =
        mstDiamondWallData.WallObjectVertexData[
            static_cast<int>(VERTEX_POS_NAME_NUMBER::RIGHT)];

    const unsigned int drawColor = GetColor(0, 255, 0);

    // 左上
    DrawTriangle(
        static_cast<int>(top.x),
        static_cast<int>(top.y),
        static_cast<int>(left.x),
        static_cast<int>(left.y),
        static_cast<int>(bottom.x),
        static_cast<int>(bottom.y),
        drawColor,
        TRUE
    );

    // 右上
    DrawTriangle(
        static_cast<int>(top.x),
        static_cast<int>(top.y),
        static_cast<int>(bottom.x),
        static_cast<int>(bottom.y),
        static_cast<int>(right.x),
        static_cast<int>(right.y),
        drawColor,
        TRUE
    );
}

// 全辺を光マップへ設定
void DiamondWallObject::SetAllEdges_ShineMap()
{
    // 以前の登録情報を削除
    mstDiamondWallData.ShineMapMyEdfeData.clear();

    const Vector2 top =
        mstDiamondWallData.WallObjectVertexData[
            static_cast<int>(VERTEX_POS_NAME_NUMBER::TOP)];

    const Vector2 left =
        mstDiamondWallData.WallObjectVertexData[
            static_cast<int>(VERTEX_POS_NAME_NUMBER::LEFT)];

    const Vector2 bottom =
        mstDiamondWallData.WallObjectVertexData[
            static_cast<int>(VERTEX_POS_NAME_NUMBER::BOTTOM)];

    const Vector2 right =
        mstDiamondWallData.WallObjectVertexData[
            static_cast<int>(VERTEX_POS_NAME_NUMBER::RIGHT)];

    // 上 → 左
    SetEdge_ShineMap(
        top,
        left
    );

    // 左 → 下
    SetEdge_ShineMap(
        left,
        bottom
    );

    // 下 → 右
    SetEdge_ShineMap(
        bottom,
        right
    );

    // 右 → 上
    SetEdge_ShineMap(
        right,
        top
    );
}

// ひし形の1辺を光マップへ登録
void DiamondWallObject::SetEdge_ShineMap(
    Vector2 linePos1,
    Vector2 linePos2
)
{
    const Vector2_Int gridPos1 =
        Vector2_Int(
            static_cast<int>(
                linePos1.x * mpShineManager->MAP_TO_GRID_SCALE_X
                ),
            static_cast<int>(
                linePos1.y * mpShineManager->MAP_TO_GRID_SCALE_Y
                )
        );

    const Vector2_Int gridPos2 =
        Vector2_Int(
            static_cast<int>(
                linePos2.x * mpShineManager->MAP_TO_GRID_SCALE_X
                ),
            static_cast<int>(
                linePos2.y * mpShineManager->MAP_TO_GRID_SCALE_Y
                )
        );

    const int minX = min(gridPos1.x, gridPos2.x);
    const int maxX = max(gridPos1.x, gridPos2.x);

    const int minY = min(gridPos1.y, gridPos2.y);
    const int maxY = max(gridPos1.y, gridPos2.y);

    /*
        辺が通過する可能性のあるグリッドを全て確認する。

        ここでは矩形範囲を候補として取得し、
        各グリッドの範囲と線分が交差するかを確認する。
    */
    for (int y = minY; y <= maxY; ++y)
    {
        for (int x = minX; x <= maxX; ++x)
        {
            if (x < 0 ||
                mpShineManager->MAP_ARRAY_SIZE_X <= x ||
                y < 0 ||
                mpShineManager->MAP_ARRAY_SIZE_Y <= y)
            {
                continue;
            }

            SetLineDataToGrid(
                Vector2_Int(x, y),
                linePos1,
                linePos2
            );
        }
    }
}

// 指定グリッドへ辺情報を登録
void DiamondWallObject::SetLineDataToGrid(
    Vector2_Int gridIndex,
    Vector2 linePos1,
    Vector2 linePos2
)
{
    /*
        現在は辺の両端を含む範囲のグリッドへ登録する。

        AdjustPositionToGrid() によって
        グリッド基準の座標へ変換する。
    */

    LINE_POS linePos;

    linePos.id = mpShineManager->GetNewLineID();

    linePos.linePos1 =
        mpShineManager->AdjustPositionToGrid(
            gridIndex,
            linePos1
        );

    linePos.linePos2 =
        mpShineManager->AdjustPositionToGrid(
            gridIndex,
            linePos2
        );

    mpShineManager
        ->mstMapObjectGridData[gridIndex.y][gridIndex.x]
        .LinePoss.push_back(linePos);

    // 登録した辺を保持
    const int linePosIndex =
        static_cast<int>(
            mpShineManager
            ->mstMapObjectGridData[gridIndex.y][gridIndex.x]
            .LinePoss.size()
            ) - 1;

    LINE_POS& linePosAddress =
        mpShineManager
        ->mstMapObjectGridData[gridIndex.y][gridIndex.x]
        .LinePoss[linePosIndex];

    mstDiamondWallData.ShineMapMyEdfeData.push_back(
        SHINE_GRID_SET_LINE_DATA(
            &linePosAddress.linePos1,
            &linePosAddress.linePos2,
            linePos.id
        )
    );
}