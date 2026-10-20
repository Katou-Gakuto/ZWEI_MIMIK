#include "WallObjectController.h"

#include "DxLib.h"

#include "../A_GameObject/GameObject2D.h"

#include "../S_Collision/BaseCollisionList.h"
#include "../S_Collision/Quadrangle2D.h"
#include "DrawSystem.h"

#include "../Y_Tool/MyMatrix.h"

#include "Master.h"
#include "ImguiManager.h"

WallObjectController::WallObjectController(GameObject *myObject, const VECTOR2D &centerPos, const VECTOR2D &blockSize, float radian) :
    mvCenterPosInit(centerPos),
    mvBlockSizeInit(blockSize),
    mfRadianInit(radian),
    mfRadian(0.0f),
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
    GameObject2D *obj = this->GetMyObject2D();
    if (obj == nullptr)
    {
        // 
        return -1;
    }

    // 
    obj->SetPosition(this->mvCenterPosInit);

    // 
    if (!this->SetBodyCollisionRotateAtNowPos(this->mfRadianInit))
    {
        // 
        return -1;
    }

    // 
    this->mfRadian = this->mfRadianInit;

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
     
     
    return 0;
}

int WallObjectController::Update()
{
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
    Quadrangle2D* bodyCollision = this->GetBody();

    /**/
    // ‰©F‚Ì“h‚è‚Â‚Ô‚µƒAƒŠ‚Å“–‚½‚è”»’è‚ÌŽlŠp‚ð•`‰æ‚·‚é
    DRAW_SYSTEM::DrawQuadrangle(
        bodyCollision->GetVertexPos(0),
        bodyCollision->GetVertexPos(1),
        bodyCollision->GetVertexPos(3),
        bodyCollision->GetVertexPos(2),
        0xaaaa00,
        true);
    // 
    return 0;
}

// 
bool WallObjectController::SetMoveVecObjAndBody(const VECTOR2D &moveVec)
{
    // 
    GameObject2D *obj = this->GetMyObject2D();
    if (obj == nullptr)
    {
        // 
        return false;
    }

    // 
    auto body = this->GetBody();
    if (body == nullptr)
    {
        // 
        return false;
    }

    // 
    obj->SetMoveVec(moveVec);

    // 
    body->SetMoveVec(moveVec);

    // 
    return true;
}

// 
bool WallObjectController::SetBodyCollisionRotateAtNowPos(float radian)
{
    // 
    GameObject2D *obj = this->GetMyObject2D();
    if (obj == nullptr)
    {
        // 
        return false;
    }

    // 
    auto body = this->GetBody();
    if (body == nullptr)
    {
        // 
        return false;
    }

    // 
    VECTOR2D pos = obj->GetPosition();

    // 
    const MyMatrix rotateMatrix = MyMatrix::GetRotation2D(radian);
    if (!rotateMatrix.CheckActive())
    {
        // 
        return false;
    }

    // 
    VECTOR2D tempVecBox[2]
    {
        VECTOR2D(-this->mvBlockSizeInit.GetX(), -this->mvBlockSizeInit.GetY()),
        VECTOR2D(+this->mvBlockSizeInit.GetX(), +this->mvBlockSizeInit.GetY()),
    };

    // 
    MyMatrix result(0, 0);
    for (int i = 0; i < 2; i++)
    {
        // 
        result = tempVecBox[i].ToMat() * rotateMatrix;

        // 
        tempVecBox[i] = result.ToV2D();
    }

    // 
    VECTOR2D tempPosBox[4];
    tempPosBox[0] = pos + VECTOR2D(tempVecBox[0].GetX(), tempVecBox[0].GetY());
    tempPosBox[1] = pos + VECTOR2D(tempVecBox[1].GetX(), tempVecBox[0].GetY());
    tempPosBox[2] = pos + VECTOR2D(tempVecBox[0].GetX(), tempVecBox[1].GetY());
    tempPosBox[3] = pos + VECTOR2D(tempVecBox[1].GetX(), tempVecBox[1].GetY());

    // 
    body->SetShapeParameter(
        tempPosBox[0],
        tempPosBox[1], 
        tempPosBox[2], 
        tempPosBox[3]);
    
    // 
    return true;
}


WallObjectController::WallObjectController(GameObject *myObject, ComponentTagAndOrder ctao, const VECTOR2D &centerPos, const VECTOR2D &blockSize, float radian) :
    mvCenterPosInit(centerPos),
    mvBlockSizeInit(blockSize),
    mfRadianInit(radian),
    mfRadian(0.0f),
    BaseComponent(myObject, ctao)
{
}

Quadrangle2D *WallObjectController::GetBody() const
{
    // 
    return static_cast<Quadrangle2D *>(this->GetMyObject()->GetBaseCollisionList()->SearchCollision(this->mdBody));
}
