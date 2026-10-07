#pragma once

#include <cstdint>
#include <vector>

class LightLineNode;

class VECTOR2D;
class BaseCollision2D;
class Point2D;
class Ray2D;
struct CollisionCheckResult2D;

// TODO:_ライト

// 
class LightArea
{
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

    // 光が一周回っているか取得
    inline bool GetFinal2Start() const { return mbFinal2Start; }

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
};
