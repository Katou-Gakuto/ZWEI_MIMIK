#pragma once

#include "BaseComponent.h"

// 
class VECTOR2D;

class GoalObjectController : public BaseComponent
{
public:
    // 
    GoalObjectController(GameObject *myObject, bool playerLight, float goalRadius);
    virtual ~GoalObjectController();

    int Create() override;
    int Initialize() override;
    int Finalize() override;
    int EarlyUpdate() override;
    int Update() override;
    int HitOnCollision(BaseCollision *myCollision, BaseCollision *hitCollision) override;
    int LateUpdate() override;
    int Draw() override;

    // 
    bool InitPosition(const VECTOR2D &initPos);

    // 
    bool UpdateInPlayer();

    // 
    bool GetInPlayer() const;

private:
    // 光域のプレイヤーのゴールか
    bool mbPlayerLight;

    // 
    bool mbInPlayer;

    // 
    float mfGoalRadius;
};