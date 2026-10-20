#include "LightObjectController.h"

#include "DxLib.h"

#include "../A_GameObject/GameObject2D.h"

#include "../S_Collision/BaseCollisionList.h"
#include "../S_Collision/Circle2D.h"
#include "DrawSystem.h"
// 
LightObjectController::LightObjectController(GameObject *myObject, const VECTOR2D &center, float radius) :
    mvCenterPosInit(center),
    mfRadiusInit(radius),
    mvCenterPos(center),
    BaseComponent(myObject, ComponentTagAndOrder::CTAO_LightController)
{
}

LightObjectController::~LightObjectController()
{
}

int LightObjectController::Create()
{
    // 
    Circle2D *body = new Circle2D(
        VECTOR2D::GetZero(),
        0,
        this->GetMyObject(),
        CollisionTag::CollisionTag_LightBody,
        CollisionNorm::CollisionNorm_Out,
        false,
        false,
        0.0f);

    // 
    body->AddProcessingTag(CollisionTag::CollisionTag_CharaBody);
    body->AddProcessingTag(CollisionTag::CollisionTag_Wall);
    body->AddProcessingTag(CollisionTag::CollisionTag_Mirror);
    body->AddProcessingTag(CollisionTag::CollisionTag_LightBody);

    // 
    this->GetMyObject()->AddCollision(body, this->mdBody);

    // 
    body->WorldConnectMySelf();

    // 
    return true;
}

int LightObjectController::Initialize()
{
    // 
    this->mvCenterPos = this->mvCenterPosInit;

    // 
    this->GetMyObject2D()->SetPosition(this->mvCenterPos);

    // 
    Circle2D *body = this->GetBody();
    if (body == nullptr)
    {
        return -1;
    }

    // 
    body->SetShapeParameter(this->mvCenterPos, this->mfRadiusInit);

    // 
    return 0;
}

int LightObjectController::Finalize()
{
    // 
    return 0;
}

int LightObjectController::EarlyUpdate()
{
    // 
    return 0;
}

int LightObjectController::Update()
{
    // 
    return 0;
}

int LightObjectController::HitOnCollision(BaseCollision *myCollision, BaseCollision *hitCollision)
{
    // 
    return 0;
}

int LightObjectController::LateUpdate()
{
    // 
    return 0;
}

int LightObjectController::Draw()
{
    // 
    Circle2D *body = this->GetBody();
    if (body == nullptr)
    {
        return -1;
    }

    // 
    DRAW_SYSTEM::DrawCircle(
        body->GetBasePos(),
        body->GetBaseRadius(),
        0xffff00,
        false);

    // 
    return 0;
}

// 
Circle2D *LightObjectController::GetBody() const
{
    // 
    return static_cast<Circle2D *>(this->GetMyObject()->GetBaseCollisionList()->SearchCollision(this->mdBody));
}

