#pragma once

// 
#include "BaseComponent.h"

#include "../Y_Tool/FlagByte.h"

// 
class GameObject2D;
class VECTOR2D;

// 
class HoldObjectController : public BaseComponent
{
private:
    // 
    enum HoldFlagBitIndex
    {
        HoldFlagBitIndex_DoubleHold = 0,
        HoldFlagBitIndex_OneSide,
        HoldFlagBitIndex_OneSideLight,
        HoldFlagBitIndex_MoveSync,
        HoldFlagBitIndex_Swing,

        HoldFlagBitIndex_Max,
    };

public:
    // 
    HoldObjectController(GameObject2D *myObj, bool doubleHold, bool oneSide, bool oneSideLight, bool move, bool swing);

    // 
    ~HoldObjectController();

    int Create() override;
    int Initialize() override;
    int Finalize() override;
    int EarlyUpdate() override;
    int Update() override;
    int HitOnCollision(BaseCollision *myCollision, BaseCollision *hitCollision) override;
    int LateUpdate() override;
    int Draw() override;

    // 
    bool CheckHoldNow() const;

    // 
    bool SetHoldFlag(bool lightPlayer, bool flag);

    // 
    float GetRadianPlayerToHold(const VECTOR2D &playerPos, int debugNum) const;

    // 
    bool SetSwingParam(const VECTOR2D &centerPos, float radian, float distance);

    // 
    void SyncMoveVecToHold(const VECTOR2D &moveVec);

    // 
    bool GetDoubleHold() const;

    // 
    bool GetSwingFlag() const;

private:
    // 
    int mnState;

    // íÜêgÇÕHoldFlagBitIndexÇÃí ÇËÇ≈Ç∑
    const FlagByte mbFlags;

    // 
    bool mbHoldLight;

    // 
    bool mbHoldShadow;

    // 
    bool mbSwingNow;
};