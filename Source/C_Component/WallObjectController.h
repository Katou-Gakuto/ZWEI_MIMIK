#pragma once

#include "BaseComponent.h"

#include "../S_Collision/CollisionHandle.h"
#include "../T_Model/BaseModelHandle.h"

#include "../Y_Tool/VECTOR.h"


class Quadrangle2D;
class DXModelRotaObj;

// 
class WallObjectController : public BaseComponent
{
public:
    WallObjectController(GameObject* myObject, const VECTOR2D& leftUp, const VECTOR2D& rightDown, float radian);
    virtual ~WallObjectController() override;

    virtual int Create() override;
    virtual int Initialize() override;
    virtual int Finalize() override;
    virtual int EarlyUpdate() override;
    virtual int Update() override;
    virtual int HitOnCollision(BaseCollision* myCollision, BaseCollision* hitCollision) override;
    virtual int LateUpdate() override;
    virtual int Draw() override;

    // 
    bool SetMoveVecObjAndBody(const VECTOR2D& moveVec);

    // 
    bool SetBodyCollisionRotateAtNowPos(float radian);

protected:
    const VECTOR2D mvCenterPosInit;
    const VECTOR2D mvBlockSizeInit;
    const float mfRadianInit;
    float mfRadian;
    CollisionHandle mdBody;
    BaseModelHandle mdModel;

    WallObjectController(
        GameObject* myObject,
        ComponentTagAndOrder ctao,
        const VECTOR2D& centerPos,
        const VECTOR2D& blockSize,
        float radian);

    Quadrangle2D* GetBody() const;
    DXModelRotaObj* GetModel() const;
};
