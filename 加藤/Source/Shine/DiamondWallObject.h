#pragma once

#include "TestObjectBase.h"
#include "WallObject.h"

class ShineManager;

class DiamondWallObject : public TestObjectBase
{
public:
    DiamondWallObject();
    ~DiamondWallObject();

    void Init() override;
    void Finalize() override;
    void Update() override;
    void Draw() override;

private:

    enum class VERTEX_POS_NAME_NUMBER
    {
        TOP,
        LEFT,
        BOTTOM,
        RIGHT,

        MAX
    };

    struct DIAMOND_WALL_DATA
    {
        Vector2 WallObjectVertexData[static_cast<int>(VERTEX_POS_NAME_NUMBER::MAX)];

        // Œõƒ}ƒbƒv‚Ö“o˜^‚µ‚½•Ó
        std::vector<SHINE_GRID_SET_LINE_DATA> ShineMapMyEdfeData;

        bool MoveFlag = false;
    };

private:

    // ‚Ð‚µŒ`‚Ì‘S•Ó‚ðŒõƒ}ƒbƒv‚Ö“o˜^
    void SetAllEdges_ShineMap();

    // ‚Ð‚µŒ`‚Ì1•Ó‚ðŒõƒ}ƒbƒv‚Ö“o˜^
    void SetEdge_ShineMap(
        Vector2 linePos1,
        Vector2 linePos2
    );

    // •Ó‚ª’Ê‰ß‚·‚éƒOƒŠƒbƒh‚Ö“o˜^
    void SetLineDataToGrid(
        Vector2_Int gridIndex,
        Vector2 linePos1,
        Vector2 linePos2
    );

private:

    DIAMOND_WALL_DATA mstDiamondWallData;
};