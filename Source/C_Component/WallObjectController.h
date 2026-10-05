#pragma once

#include "BaseComponent.h"

#include "../S_Collision/CollisionHandle.h"

#include "../Y_Tool/VECTOR.h"

class Quadrangle2D;

// 
class WallObjectController : public BaseComponent
{
public:
    WallObjectController(GameObject *myObject, const VECTOR2D &leftUp, const VECTOR2D &rightDown);
    virtual ~WallObjectController() override;

    virtual int Create() override;
    virtual int Initialize() override;
    virtual int Finalize() override;
    virtual int EarlyUpdate() override;
    virtual int Update() override;
    virtual int HitOnCollision(BaseCollision *myCollision, BaseCollision *hitCollision) override;
    virtual int LateUpdate() override;
    virtual int Draw() override;

protected:
    const VECTOR2D mvCenterPosInit;
    const VECTOR2D mvBlockSizeInit;
    VECTOR2D mvCenterPos;
    VECTOR2D mvBlockSize;
    CollisionHandle mdBody;

    WallObjectController(GameObject *myObject, ComponentTagAndOrder ctao, const VECTOR2D &leftUp, const VECTOR2D &rightDown);

    Quadrangle2D *GetBody() const;
};
