#pragma once

#include "BaseComponent.h"

#include "../S_Collision/CollisionHandle.h"
#include "../T_Model/BaseModelHandle.h"
#include "../Y_Tool/VECTOR.h"

class LightExecutor;
class BaseGimmickTrigger;
class DXModelRotaObj;
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
	const float mfRadiusInit; // 当たり判定の半径

    VECTOR2D mvCenterPos;// 中心座標
    CollisionHandle mdBody;

    // このオブジェクトのDXModelRotaObjをBaseModelListから取得するためのハンドル
    BaseModelHandle mdModelHandle;

    DXModelRotaObj *GetModel()const;

    // 
    Circle2D *GetBody() const;
};