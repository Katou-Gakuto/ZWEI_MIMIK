#pragma once


#include <cstdint>
#include <vector>

#include "VECTOR.h"

#include "DxLib.h"

#include "BaseCollision.h"

struct HIT_COLLISION_LINE
{
    BaseCollision* HitCollision;
    VECTOR2D LineStartPos;
    VECTOR2D LineEndPos;
};

class LightLineNode;

class BaseCollision2D;
class Point2D;
class Ray2D;
struct CollisionCheckResult2D;

// 
class LightArea
{
private:
    struct LIGHT_DATA
    {
        VECTOR2D lineOne;
        VECTOR2D lineTwo;
    };

public:
    // 
    LightArea();

    // 
    ~LightArea();

    // 自身の光のレイの角度を設定する関数
    void SetParam(void *parentObject, uint32_t lineCount, float baseAngle, float lightAngle, bool final2start);

    // 自身の光の終了地点を計算し、設定する関数
    // 次のノードにつながる場合はtrueを返す
    bool CalculateNode(
        float baseAngle,
        float stockMagunitude,
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

    // ライトエリア再描画
    void ReDrawLightArea();

    // ライトエリア描画時当たっている
    std::vector<std::vector<HIT_COLLISION_LINE>> DrawLingAreaHitCollisionsGetProcess();

    // ライト有効フラグ設定
    void SetLightFlag(bool flag) { mbIsLightFlag = flag; }

private:
    // 指定した2点を通る直線上に点があるかを判定
    bool IsPointOnLine(const VECTOR2D& linePos1, const VECTOR2D& linePos2, const VECTOR2D& checkPos);

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
    bool mbOffLight;

    // 光が一周回っている
    bool mbFinal2Start;

    // 光の色
    uint32_t mnLightColor = 0xffffff;

    // ライトラインポジションデータ
    std::vector<std::vector<LIGHT_DATA>> mstLightLine;

    // ライトエリア三角
    VERTEX2D* mstLightAreaTriangleVertex;

    // ライトエリア三角の数
    unsigned int munLightAreaTriangleSize;

    // 前の三角の配列数
    int mnPreLightAreaTriangleVertexIndexCount;

    // ライト点灯フラグ
    bool mbIsLightFlag;
};
