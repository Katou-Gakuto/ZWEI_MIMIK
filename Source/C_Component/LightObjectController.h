#pragma once

#include "BaseComponent.h"

#include "../S_Collision/CollisionHandle.h"
#include "../Y_Tool/VECTOR.h"

class LightExecutor;
class BaseGimmickTrigger;
class Circle2D;

class LightObjectController : public BaseComponent
{
public:
    // 
    LightObjectController(GameObject *myObject, const VECTOR2D &center, float radius);
    ~LightObjectController() override;

    int Create() override;
    int Initialize() override;
    int Finalize() override;
    int EarlyUpdate() override;
    int Update() override;
    int HitOnCollision(BaseCollision *myCollision, BaseCollision *hitCollision) override;
    int LateUpdate() override;
    int Draw() override;

private:
    const VECTOR2D mvCenterPosInit;
    const float mfRadiusInit;

    VECTOR2D mvCenterPos;
    CollisionHandle mdBody;

    // 
    Circle2D *GetBody() const;
};