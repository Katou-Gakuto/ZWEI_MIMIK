#pragma once

#include "BaseCollision.h"

#include <math.h>

#include "AABB.h"

class GameObject2D;
class BaseCollision2D : public BaseCollision
{
private:
    VECTOR2D mvBasePos;                         // カリング処理で作る円の中心点
    float mfBaseRadius;                         // カリング処理で作る円の大きさ
    bool mbBasePosUpdateFlag;                   // カリング処理で使用する円の中心座標を更新する必要があるかどうか    
    bool mbBaseRadiusUpdateFlag;                // カリング処理で使用する円の半径を更新する必要があるかどうか    
    VECTOR2D mvMoveVec;                         // 移動の進行ベクトル

    BaseCollision2D *mpPrevWorld;               // 前の当たり判定へのポインタ(ワールド線形リスト)
    BaseCollision2D *mpNextWorld;               // 次の当たり判定へのポインタ(ワールド線形リスト)

public:
    // 
    int mnHitCount;

    BaseCollision2D(
        GameObject *object, CollisionType type, CollisionTag tag, CollisionNorm normNum,
        bool penetrate, bool hitMove, float moveLate);
    virtual ~BaseCollision2D() override;

    virtual int Draw(const Material2D &color) override;
    virtual int SetPosToMoveVec() override;

    int SetMoveVec(const void *moveData) override;
    int SetNextPos(const void *posData) override;
    virtual int SlideMove(const CollisionCheckResult2D &result, float moveLate) = 0;

    int WorldConnectMySelf() override;
    int WorldIsolateMySelf() override;

    virtual int SetBaseParamMySelf();
    virtual int GetAABB(AABB2D &out) = 0;

    void SetBasePos(const VECTOR2D &pos)                { this->mvBasePos = pos; }
    void SetBaseRadius(float radius)                    { this->mfBaseRadius = radius; }
    void SetBasePosUpdateFlag(bool flag)                { this->mbBasePosUpdateFlag = flag; }
    void SetBaseRadiusUpdateFlag(bool flag)             { this->mbBaseRadiusUpdateFlag = flag; }
    void SetMoveVec(const VECTOR2D &vec)                { this->mvMoveVec = vec; }
    const VECTOR2D &GetBasePos()                const   { return this->mvBasePos; }
    float GetBaseRadius()                       const   { return this->mfBaseRadius; }
    bool GetBasePosUpdateFlag()                 const   { return this->mbBasePosUpdateFlag; }
    bool GetBaseRadiusUpdateFlag()              const   { return this->mbBaseRadiusUpdateFlag; }
    VECTOR2D GetMoveVec()                       const   { return this->mvMoveVec; }
    VECTOR2D GetMovedPos(const VECTOR2D &pos)   const   { return (pos + this->mvMoveVec); }

    void SetPrevWorld(BaseCollision2D *prev)            { this->mpPrevWorld = prev; }
    void SetNextWorld(BaseCollision2D *next)            { this->mpNextWorld = next; }
    BaseCollision2D *GetPrevWorld()             const   { return this->mpPrevWorld; }
    BaseCollision2D *GetNextWorld()             const   { return this->mpNextWorld; }
};