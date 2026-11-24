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

    BaseCollision* HitCollision;      // 当たっているコリジョン
    BaseCollision* PreHitCollision;   // 前に当たっていたコリジョン
    BaseCollision* OtherCollision;    // 判定に使ったもう一方のコリジョン
    VECTOR2D LineStartPos;
    VECTOR2D LineEndPos;

    float LightStartAlphaRange; // 開始地点のアルファ値
    float LightEndAlphaRange;   // 終了地点のアルファ値

    float LightIntensity;   // 光のラインが中央に近いほど1.0f

    bool IsSetup;   // 補正するフラグ

    unsigned int LightNodeId;   // ライトノードのID
    
    HIT_COLLISION_LINE()
    : HitCollision(nullptr)
    , PreHitCollision(nullptr)
    , OtherCollision(nullptr)
    , LineStartPos(VECTOR2D::GetZero())
    , LineEndPos(VECTOR2D::GetZero())
    , LightStartAlphaRange(-1.0f)
    , LightEndAlphaRange(-1.0f)
    , LightIntensity(0)
    , IsSetup(true)
    , LightNodeId(0u)
    {
    }

    HIT_COLLISION_LINE(BaseCollision* hitCollision, BaseCollision* preHitCollision, BaseCollision* otherCollision, VECTOR2D lineStartPos, VECTOR2D lineEndPos, float lightStartAlphaRange, float lightEndAlphaRange, float lightIntensity)
    : HitCollision(hitCollision)
    , PreHitCollision(preHitCollision)
    , OtherCollision(otherCollision)
    , LineStartPos(lineStartPos)
    , LineEndPos(lineEndPos)
    , LightStartAlphaRange(lightStartAlphaRange)
    , LightEndAlphaRange(lightEndAlphaRange)
    , LightIntensity(lightIntensity)
    , IsSetup(true)
    , LightNodeId(0u)
    {
    }
};

struct AREA_ROUTE_JUDGE_DATA
{
    bool IsAddSet;
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

    // ライトエリア描画
    void DrawLightArea();

    // ライトエリア描画時当たっている
    std::vector<std::vector<std::vector<HIT_COLLISION_LINE>>> DrawLingAreaHitCollisionsGetProcess();

private:
    // ライトエリアの描画情報設定処理
    bool SettingDrawLightAreaData(const std::vector<BaseCollision2D *> &objectCollBox, const std::vector<BaseCollision2D *> &mirrorCollBox);

    // 指定した2点を通る直線上に点があるかを判定
    bool IsPointOnLine(const VECTOR2D& linePos1, const VECTOR2D& linePos2, const VECTOR2D& checkPos);

    // 光領域を描画用に調整する
    int SetupLightAreaForDrawing(const std::vector<HIT_COLLISION_LINE>& hitCollisionLine, std::vector<HIT_COLLISION_LINE>* drawHitCollisionLine, const size_t& lineIndex, const int& drawHitCollisionLineIteratorPlusNumber, const std::vector<BaseCollision2D *> *objectCollBox = nullptr, const std::vector<BaseCollision2D *> *mirrorCollBox = nullptr);

    // 角を取得する
    std::vector<VECTOR2D> GetVertexPositions(BaseCollision* collision, const VECTOR2D& viewPos1, const VECTOR2D* viewPos2 = nullptr);
    // 辺を取得する
    std::vector<LIGHT_EDGE_DATA> GetVisibleEdges(BaseCollision* collision, const VECTOR2D& viewPos1, const VECTOR2D* viewPos2 = nullptr);

    // 	2本のラインの間にある頂点まで描画用ラインを追加する
    bool AddDrawLineToVertexBetweenLines(std::vector<HIT_COLLISION_LINE>* addDrawHitCollisionLine, const VECTOR2D& startPos, const VECTOR2D& endPos, Quadrangle2D& tempQuadrangle, std::vector<VECTOR2D>& vertexPositions, BaseCollision* hitCollision, BaseCollision* preHitCollision, BaseCollision* otherHitCollision, bool isEqualAngleFrontSet, float startAlphaRange, float lightIntensity, std::vector<VECTOR2D>* excludeVertexPositions = nullptr);

    // 当たっている辺を求める
    LIGHT_EDGE_DATA GettingHitCollisionEdge(const HIT_COLLISION_LINE& hitCollisionLine);

    // 延長した光を取得する
    bool GettingExtendedLight(const HIT_COLLISION_LINE& extendedLightLine, const HIT_COLLISION_LINE& hitCollisionLine, HIT_COLLISION_LINE* setExtendedLight, const VECTOR2D& shiftVec);

    // 当たっている辺以外の辺まで光を延長する
    bool GettingExtendedLightToOtherEdge(const HIT_COLLISION_LINE& hitCollisionLine, HIT_COLLISION_LINE* setExtendedLight);

    // 2本の衝突辺が平行か判定
    bool IsParallelHitCollisionEdge(const HIT_COLLISION_LINE& firstLine, const HIT_COLLISION_LINE& secondLine);

    // 点が線分上にあるか確認
    bool IsPointOnLineSegment(const VECTOR2D& point, const VECTOR2D& lineStart, const VECTOR2D& lineEnd);
        
    // 2つの線分の交差点を取得
    bool GetIntersectionPosition(const VECTOR2D& lineOneStart, const VECTOR2D& lineOneEnd, const VECTOR2D& lineTwoStart, const VECTOR2D& lineTwoEnd, VECTOR2D* intersectionPos);

    // 3角情報にして描画
    void SettingDrawHitCollisionLineData(const std::vector<std::vector<std::vector<HIT_COLLISION_LINE>>> &hitCollisionLineData);

    // ライトアルファ値補正
    float SetupLightAlphaRange(float lightAlphaRange);
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

    // ライトの強さ
    const float LIGHT_POWER;

    // 追加したライン
    std::vector<HIT_COLLISION_LINE> mstAddDrawHitCollisionLine;
    
    // 追加のライトラインノードの始まり
    std::vector<LightLineNode *> mlAddLightFirstNode;
    // 追加のライトラインノードのアングル
    std::vector<float> mlAddLineAngleBox;
    // 追加ライトノードの始まりの数
    unsigned int munAddLightLineCount;

    // 更新フラグ
    bool mbIdLightNodeUpdate;
};
