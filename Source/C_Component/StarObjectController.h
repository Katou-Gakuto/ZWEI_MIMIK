#pragma once

#include "BaseComponent.h"

// 
#include "../Y_Tool/VECTOR.h"

// 
class StarObjectController : public BaseComponent
{
public:
    // 
    StarObjectController(GameObject *myObject, bool oneSide, bool playerLight);
    virtual ~StarObjectController();

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
    // 
    bool mbOneSide;

    // 
    bool mbPlayerLight;

    // 
    bool UpdateInPlayer();
};