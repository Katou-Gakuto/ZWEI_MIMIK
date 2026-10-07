#include "WallObjectController.h"

#include "DxLib.h"

#include "../A_GameObject/GameObject2D.h"

#include "../S_Collision/BaseCollisionList.h"
#include "../S_Collision/Quadrangle2D.h"


WallObjectController::WallObjectController(GameObject *myObject, const VECTOR2D &centerPos, const VECTOR2D &blockSize) :
    mvCenterPosInit(centerPos),
    mvBlockSizeInit(blockSize),
    mvCenterPos(centerPos),
    mvBlockSize(blockSize),
    BaseComponent(myObject, ComponentTagAndOrder::CTAO_MirrorController)
{
}

WallObjectController::~WallObjectController()
{
}

int WallObjectController::Create()
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

    // 
    VECTOR2D tempPos[4];

    // 
    collision = new Quadrangle2D(
        tempPos[0],
        tempPos[1],
        tempPos[2],
        tempPos[3],
        obj,
        CollisionTag::CollisionTag_Wall,
        CollisionNorm::CollisionNorm_Out,
        false,
        false,
        0.0f);
    collision->AddProcessingTag(CollisionTag::CollisionTag_CharaBody);
    collision->AddProcessingTag(CollisionTag::CollisionTag_Wall);

    // 
    if (obj->AddCollision(collision, this->mdBody) != 0)
    {
        // 
        return -1;
    }


    // 
    collision->WorldConnectMySelf();

    // 
    return 0;
}

int WallObjectController::Initialize()
{
    // 
    this->mvCenterPos = this->mvCenterPosInit;
    this->mvBlockSize = this->mvBlockSizeInit;

    // 
    GameObject2D *obj = this->GetMyObject2D();
    if (obj == nullptr)
    {
        // 
        return -1;
    }

    obj->SetPosition(this->mvCenterPos);

    // 
    VECTOR2D tempPos[4];
    tempPos[0] = this->mvCenterPos + (VECTOR2D(-this->mvBlockSize.GetX(), -this->mvBlockSize.GetY()) * 0.5f);
    tempPos[1] = this->mvCenterPos + (VECTOR2D(+this->mvBlockSize.GetX(), -this->mvBlockSize.GetY()) * 0.5f);
    tempPos[2] = this->mvCenterPos + (VECTOR2D(-this->mvBlockSize.GetX(), +this->mvBlockSize.GetY()) * 0.5f);
    tempPos[3] = this->mvCenterPos + (VECTOR2D(+this->mvBlockSize.GetX(), +this->mvBlockSize.GetY()) * 0.5f);

    // 
    Quadrangle2D *collision = this->GetBody();

    // 
    collision->SetShapeParameter(tempPos[0], tempPos[1], tempPos[2], tempPos[3]);

    // 
    return 0;
}

int WallObjectController::Finalize()
{
    // 
    return 0;
}

int WallObjectController::EarlyUpdate()
{
    // 
    return 0;
}

int WallObjectController::Update()
{
    // 
    return 0;
}

int WallObjectController::HitOnCollision(BaseCollision *myCollision, BaseCollision *hitCollision)
{
    // 
    return 0;
}

int WallObjectController::LateUpdate()
{
    // 
    return 0;
}

int WallObjectController::Draw()
{
    // 
    Quadrangle2D *bodyCollision = this->GetBody();

    
    // ‰©F‚Ì“h‚è‚Â‚Ô‚µƒAƒŠ‚Å“–‚½‚è”»’è‚ÌŽlŠp‚ð•`‰æ‚·‚é
    DxLib::DrawBox(
        bodyCollision->GetVertexPos(0).GetX(),
        bodyCollision->GetVertexPos(0).GetY(),
        bodyCollision->GetVertexPos(3).GetX(),
        bodyCollision->GetVertexPos(3).GetY(),
        0xaaaa00,
        true);

    // 
    return 0;
}

WallObjectController::WallObjectController(GameObject *myObject, ComponentTagAndOrder ctao, const VECTOR2D &leftUp, const VECTOR2D &rightDown) :
    mvCenterPosInit(leftUp),
    mvBlockSizeInit(rightDown),
    mvCenterPos(leftUp),
    mvBlockSize(rightDown),
    BaseComponent(myObject, ctao)
{
}

Quadrangle2D *WallObjectController::GetBody() const
{
    // 
    return static_cast<Quadrangle2D *>(this->GetMyObject()->GetBaseCollisionList()->SearchCollision(this->mdBody));
}
