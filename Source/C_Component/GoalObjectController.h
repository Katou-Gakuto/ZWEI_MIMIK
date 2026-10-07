#pragma once

#include "BaseComponent.h"

// 
class VECTOR2D;

class GoalObjectController : public BaseComponent
{
public:
    // 
    GoalObjectController(GameObject *myObject, bool playerLight);
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

private:
    // 光域のプレイヤーのゴールか
    bool mbPlayerLight;
};