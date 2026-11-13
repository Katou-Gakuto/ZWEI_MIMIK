#pragma once


#include <cstdint>
#include <vector>

#include "BitFlag.h"
#include "VECTOR.h"

#include "DxLib.h"

#include "BaseCollision.h"

class LightLineNode;

class BaseCollision2D;
class Point2D;
class Ray2D;
struct CollisionCheckResult2D;
class Quadrangle2D;

struct HIT_COLLISION_LINE
{
    BaseCollision* HitCollision;
    VECTOR2D LineStartPos;
    VECTOR2D LineEndPos;
};

struct AREA_ROUTE_JUDGE_DATA
{
    BaseCollision* PreLineHitCollision;
    int LightAreaRouteID;
    int PlusLightAreaRouteID;
};

struct LIGHT_EDGE_DATA
{
    VECTOR2D LineOne;
    VECTOR2D LineTwo;

    bool IsExist;

    LIGHT_EDGE_DATA()
    : LineOne()
    , LineTwo()
    , IsExist(false)
    {
    }

    LIGHT_EDGE_DATA(VECTOR2D lineOne, VECTOR2D lineTwo)
    : LineOne(lineOne)
    , LineTwo(lineTwo)
    , IsExist(true)
    {
    }

    LIGHT_EDGE_DATA(bool isExist)
    : LineOne()
    , LineTwo()
    , IsExist(isExist)
    {
    }

    LIGHT_EDGE_DATA(VECTOR2D lineOne, VECTOR2D lineTwo, bool isExist)
    : LineOne(lineOne)
    , LineTwo(lineTwo)
    , IsExist(isExist)
    {
    }
};
class LightArea
{
public:
    // 
    LightArea();

    // 
    ~LightArea();

    // 自身の光のレイの角度を設定する関数
    void SetParam(void *parentObject, uint32_t lineCount, float stockMagnitude, float baseAngle, float lightAngle, bool final2start);

    // 自身の光の終了地点を計算し、設定する関数
    // 次のノードにつながる場合はtrueを返す
    bool CalculateNode(
        const std::vector<BaseCollision2D *> &objectCollBox,
        const std::vector<BaseCollision2D *> &mirrorCollBox,
        Ray2D &tempRay,
        CollisionCheckResult2D &tempResultCurrent,
        CollisionCheckResult2D &tempResultNewr);

    // 
    LightLineNode **GetFirstNodeBox();

    // 
    LightLineNode *const *GetFirstNodeBox() const;

    // 
    uint32_t GetLightLineCount() const;

    // 
    VECTOR2D GetStartPosition() const;

    // 
    void SetLightLineCount(uint32_t count);

    // 
    bool CheckInArea(Point2D &targetPoint) const;

    // 
    bool GetOffLight() const;

    // 
    bool OnLight();

    // 
    bool OffLight();

    // 光の色設定
    // 0xffffffで色決めれる
    void SetLightColor(uint32_t lightColor) { mnLightColor = lightColor; }
    // 光の色取得
    uint32_t GetLightColor() { return mnLightColor; }

    // ライトエリアの描画
    void DrawLightArea();
    void A();

    // ライトエリア再描画
    void ReDrawLightArea();


    // ライトエリア描画時当たっている
    std::vector<std::vector<std::vector<HIT_COLLISION_LINE>>> DrawLingAreaHitCollisionsGetProcess();

    // ライト有効フラグ設定
    void SetLightFlag(bool flag) { mbIsLightFlag = flag; }

private:
    // 指定した2点を通る直線上に点があるかを判定
    bool IsPointOnLine(const VECTOR2D& linePos1, const VECTOR2D& linePos2, const VECTOR2D& checkPos);


    // 光領域を描画用に調整する
    int SetupLightAreaForDrawing(const std::vector<HIT_COLLISION_LINE>& hitCollisionLine, std::vector<HIT_COLLISION_LINE>& drawHitCollisionLine, size_t lineIndex, int drawHitCollisionLineIteratorPlusNumber);

    // 角を取得する
    std::vector<VECTOR2D> GetVertexPositions(BaseCollision* collision, VECTOR2D viewPos);
    // 辺を取得する
    std::vector<LIGHT_EDGE_DATA> GetVisibleEdges(BaseCollision* collision, const VECTOR2D& viewPos);

    // 	2本のラインの間にある頂点まで描画用ラインを追加する
    bool AddDrawLineToVertexBetweenLines(std::vector<HIT_COLLISION_LINE>* addDrawHitCollisionLine, VECTOR2D startPos, VECTOR2D endPos, Quadrangle2D& tempQuadrangle, std::vector<VECTOR2D> vertexPositions, BaseCollision* hitCollision, bool isEqualAngleFrontSet);

    // 当たっている辺を求める
    LIGHT_EDGE_DATA GettingHitCollisionEdge(const HIT_COLLISION_LINE& hitCollisionLine);

    // 延長した光を取得する
    bool GettingExtendedLight(HIT_COLLISION_LINE extendedLightLine, const HIT_COLLISION_LINE& hitCollisionLine, HIT_COLLISION_LINE* setExtendedLight);

    // 当たっている辺以外の辺まで光を延長する
    bool GettingExtendedLightToOtherEdge(const HIT_COLLISION_LINE& hitCollisionLine, HIT_COLLISION_LINE* setExtendedLight);

    // 2本の衝突辺が平行か判定
    bool IsParallelHitCollisionEdge(const HIT_COLLISION_LINE& firstLine, const HIT_COLLISION_LINE& secondLine);

    // 点が線分上にあるか確認
    bool IsPointOnLineSegment(const VECTOR2D& point, const VECTOR2D& lineStart, const VECTOR2D& lineEnd);

    // 3角情報にして描画
    void DrawHitCollisionLineData(const std::vector<std::vector<std::vector<HIT_COLLISION_LINE>>> &hitCollisionLineData);
private:
    // とりあえず用意しておこうか
    std::vector<LightLineNode *> mlLightFirstNode;

    // 
    std::vector<float> mlLineAngleBox;

    // 
    void *mpParentObject;

    // 
    uint32_t mnLightLineCount;

    // 
    float mfStockMagnitude;

    // 
    bool mbOffLight;

    // 光が一周回っている
    bool mbFinal2Start;

    // 光の色
    uint32_t mnLightColor = 0xffffff;

    // 最大ノード数
    int mnNodeMaxCount;

    // ライトエリア三角
    VERTEX2D* mstLightAreaTriangleVertex;

    // ライトエリア三角の数
    unsigned int munLightAreaTriangleSize;

    // 前の三角の配列数
    int mnPreLightAreaTriangleVertexIndexCount;

    // ライト点灯フラグ
    bool mbIsLightFlag;
};
