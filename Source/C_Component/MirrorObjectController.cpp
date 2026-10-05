#include "MirrorObjectController.h"

#include "DxLib.h"

#include "../A_GameObject/GameObject2D.h"

#include "../S_Collision/BaseCollisionList.h"
#include "../S_Collision/Quadrangle2D.h"
#include "../S_Collision/Ray2D.h"

MirrorObjectController::MirrorObjectController(GameObject *myObject, const VECTOR2D &leftUp, const VECTOR2D &rightDown, unsigned char mirrorFace) :
    mnMirrorFace(mirrorFace),
    WallObjectController(myObject, ComponentTagAndOrder::CTAO_MirrorController, leftUp, rightDown)
{
}

MirrorObjectController::~MirrorObjectController()
{
}

int MirrorObjectController::Create()
{
    // 
    GameObject2D *obj = this->GetMyObject2D();
    if (obj == nullptr)
    {
        // 
        return -1;
    }

    // 
    BaseCollision *collision = nullptr;
    collision = new Quadrangle2D(
        VECTOR2D(),
        VECTOR2D(),
        VECTOR2D(),
        VECTOR2D(),
        obj,
        CollisionTag::CollisionTag_Wall,
        CollisionNorm::CollisionNorm_Out,
        false,
        false,
        0.0f);
    collision->AddProcessingTag(CollisionTag::CollisionTag_CharaBody);
    collision->AddProcessingTag(CollisionTag::CollisionTag_Wall);
    if (obj->AddCollision(collision, this->mdBody) != 0)
    {
        return -1;
    }
    collision->WorldConnectMySelf();

    // 
    collision = new Ray2D(VECTOR2D(), VECTOR2D(), obj, CollisionTag::CollisionTag_Mirror, false, false, 0.0f);
    if (obj->AddCollision(collision, this->mdMirrorFaceRay) != 0)
    {
        return -1;
    }
    collision->WorldConnectMySelf();

    // 
    return 0;
}

int MirrorObjectController::Initialize()
{
    // 
    this->mvCenterPos = this->mvCenterPosInit;
    
    // 
    this->mvBlockSize = this->mvBlockSizeInit;

    // 
    this->GetMyObject2D()->SetPosition(this->mvCenterPos);

    // 
    VECTOR2D tempPos[4];
    tempPos[0] = this->mvCenterPos + (VECTOR2D(-this->mvBlockSize.GetX(), -this->mvBlockSize.GetY()) * 0.5f);
    tempPos[1] = this->mvCenterPos + (VECTOR2D(+this->mvBlockSize.GetX(), -this->mvBlockSize.GetY()) * 0.5f);
    tempPos[2] = this->mvCenterPos + (VECTOR2D(-this->mvBlockSize.GetX(), +this->mvBlockSize.GetY()) * 0.5f);
    tempPos[3] = this->mvCenterPos + (VECTOR2D(+this->mvBlockSize.GetX(), +this->mvBlockSize.GetY()) * 0.5f);

    // 
    GameObject2D *obj = this->GetMyObject2D();
    if (obj == nullptr)
    {
        // 
        return -1;
    }

    // 
    BaseCollisionList *list = obj->GetBaseCollisionList();

    // 
    Quadrangle2D *body = static_cast<Quadrangle2D *>(list->SearchCollision(this->mdBody));
    Ray2D *mirrorRay = static_cast<Ray2D *>(list->SearchCollision(this->mdMirrorFaceRay));
    if (mirrorRay == nullptr || body == nullptr)
    {
        // 
        return -1;
    }

    // 
    body->SetShapeParameter(tempPos[0], tempPos[1], tempPos[2], tempPos[3]);

    // 
    switch (this->mnMirrorFace)
    {
    case 0:
        mirrorRay->SetShapeParameter(tempPos[0], tempPos[1]);
        break;
    case 1:
        mirrorRay->SetShapeParameter(tempPos[1], tempPos[3]);
        break;
    case 2:
        mirrorRay->SetShapeParameter(tempPos[3], tempPos[2]);
        break;
    case 3:
        mirrorRay->SetShapeParameter(tempPos[2], tempPos[0]);
        break;
    default:
        break;
    }

    // 
    return 0;
}

int MirrorObjectController::Finalize()
{
    // 
    return 0;
}

int MirrorObjectController::EarlyUpdate()
{
    // 
    return 0;
}

int MirrorObjectController::Update()
{
    // 
    return 0;
}

int MirrorObjectController::HitOnCollision(BaseCollision *myCollision, BaseCollision *hitCollision)
{
    // 
    return 0;
}

int MirrorObjectController::LateUpdate()
{
    // 
    return 0;
}

int MirrorObjectController::Draw()
{
    // 
    GameObject2D *obj = this->GetMyObject2D();
    if (obj == nullptr)
    {
        // 
        return -1;
    }

    // 
    BaseCollisionList *list = obj->GetBaseCollisionList();

    // 
    unsigned int color = 0x000000;

    // 
    Quadrangle2D *body = static_cast<Quadrangle2D *>(list->SearchCollision(this->mdBody));
    Ray2D *mirrorRay = static_cast<Ray2D *>(list->SearchCollision(this->mdMirrorFaceRay));
    if (mirrorRay == nullptr || body == nullptr)
    {
        // 
        return -1;
    }

    // ‹¾–Êo‚È‚¢•”•ª‚ÍÂF‚Å•`‰æ
    color = 0x0000ff;

    // 
    DxLib::DrawBox(
        body->GetVertexPos(0).GetX(),
        body->GetVertexPos(0).GetY(),
        body->GetVertexPos(3).GetX(),
        body->GetVertexPos(3).GetY(),
        color,
        false);

    // ‹¾–Ê‚Ì‚ÝŽ‡F‚Å•`‰æ
    color = 0xff00ff;

    // 
    const float offsetParam = 3.0f;
    VECTOR2D offset;
    switch (this->mnMirrorFace)
    {
    case 0:
        offset.SetXY(0.0f, -offsetParam);
        break;
    case 1:
        offset.SetXY(-offsetParam, 0.0f);
        break;
    case 2:
        offset.SetXY(0.0f, offsetParam);
        break;
    case 3:
        offset.SetXY(offsetParam, 0.0f);
        break;
    default:
        break;
    }

    
    // 
    DxLib::DrawLine(
        offset.GetX() + mirrorRay->GetStartPos().GetX(),
        offset.GetY() + mirrorRay->GetStartPos().GetY(),
        offset.GetX() + mirrorRay->GetEndPos().GetX(),
        offset.GetY() + mirrorRay->GetEndPos().GetY(),
        color);

    // 
    return 0;
}
