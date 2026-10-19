#include "ButtonObjectController.h"

#include "DxLib.h"

#include "../A_GameObject/GameObject2D.h"
#include "../A_GameObject/GameObjectManager.h"

#include "../C_Component/Player.h"

#include "../E_Scene/BaseSceneManager.h"

#include "../G_LightArea/LightAreaManager.h"

#include "../S_Collision/BaseCollision2DManager.h"
#include "../S_Collision/BaseCollisionList.h"
#include "../S_Collision/Quadrangle2D.h"
#include "../S_Collision/Point2D.h"

#include "../Z_Except/Master.h"

// 
ButtonObjectController::ButtonObjectController(
    GameObject *myObject,
    bool onePush,
    uint32_t onFrameCount,
    const VECTOR2D &center,
    const VECTOR2D &blockSize) :
    mbNowOn(false),
    mbHitButton(!onePush),
    mbPushLastFrame(false),
    mbLightSide(false),
    mbOnPlayer(false),
    mnOnFrameCount(onFrameCount),
    mnNowFrameCount(0),
    mvCenterPos(center),
    mvBlockSize(blockSize),
    BaseComponent(myObject, ComponentTagAndOrder::CTAO_ButtonController)
{
}

// 
ButtonObjectController::~ButtonObjectController()
{
}

int ButtonObjectController::Create()
{
    // 
    return this->CreateBody();
}

int ButtonObjectController::Initialize()
{
    // 
    return 0;
}

int ButtonObjectController::Finalize()
{
    // 
    return 0;
}

int ButtonObjectController::EarlyUpdate()
{
    // 
    return this->BaseEarlyUpdate();
}

int ButtonObjectController::Update()
{
    // 
    return 0;
}

int ButtonObjectController::HitOnCollision(BaseCollision *myCollision, BaseCollision *hitCollision)
{
    // 
    return 0;
}

int ButtonObjectController::LateUpdate()
{
    // 
    return this->BaseLateUpdate();
}

int ButtonObjectController::Draw()
{
    // 
    Quadrangle2D *body = this->GetBody();
    if (body == nullptr)
    {
        // 
        return false;
    }

    unsigned long color = 0x000000;
    if (this->mbNowOn)
    {
        // 
        color = 0xffffff;
    }
    else
    {
        if (this->mbLightSide)
        {
            // 
            color = 0xff0000;
        }
        else
        {
            // 
            color = 0x0000ff;
        }
    }

    // 
    DxLib::DrawBox(
        body->GetVertexPos(0).GetX(),
        body->GetVertexPos(0).GetY(),
        body->GetVertexPos(3).GetX(),
        body->GetVertexPos(3).GetY(),
        color,
        false);

    // 
    return 0;
}

// 現在このボタンはONの状態なのか
bool ButtonObjectController::GetNowState() const
{
    // 
    return this->mbNowOn;
}

// 現在このボタンの上にプレイヤーがいるのか
bool ButtonObjectController::GetLightSide() const
{
    // 
    return this->mbLightSide;
}

// 
ButtonObjectController::ButtonObjectController(
    ComponentTagAndOrder ctao,
    GameObject *myObject,
    const VECTOR2D &center,
    const VECTOR2D &blockSize) :
    mbNowOn(false),
    mbHitButton(true),
    mbPushLastFrame(false),
    mbLightSide(false),
    mbOnPlayer(false),
    mnOnFrameCount(0),
    mnNowFrameCount(0),
    mvCenterPos(center),
    mvBlockSize(blockSize),
    BaseComponent(myObject, ctao)
{
}

// 
int ButtonObjectController::CreateBody()
{
    // 
    GameObject2D *obj = this->GetMyObject2D();
    if (obj == nullptr)
    {
        // 
        return -1;
    }

    obj->SetPosition(this->mvCenterPos);

    VECTOR2D tempPos[4];
    tempPos[0] = this->mvCenterPos + (VECTOR2D(-this->mvBlockSize.GetX(), -this->mvBlockSize.GetY()) * 0.5f);
    tempPos[1] = this->mvCenterPos + (VECTOR2D(+this->mvBlockSize.GetX(), -this->mvBlockSize.GetY()) * 0.5f);
    tempPos[2] = this->mvCenterPos + (VECTOR2D(-this->mvBlockSize.GetX(), +this->mvBlockSize.GetY()) * 0.5f);
    tempPos[3] = this->mvCenterPos + (VECTOR2D(+this->mvBlockSize.GetX(), +this->mvBlockSize.GetY()) * 0.5f);

    // 
    Quadrangle2D *collision = new Quadrangle2D(
        tempPos[0],
        tempPos[1],
        tempPos[2],
        tempPos[3],
        obj,
        CollisionTag::CollisionTag_Button,
        CollisionNorm_Out,
        true,
        false,
        0.0f);

    // 
    obj->AddCollision(collision, this->mdBody);

    // 
    return 0;
}

// 
int ButtonObjectController::BaseEarlyUpdate()
{
    // 
    this->mbPushLastFrame = this->mbOnPlayer;

    // 
    return 0;
}

// 
int ButtonObjectController::BaseLateUpdate()
{
    // 
    this->UpdateLightSide();

    // 
    this->UpdateNowState();

    // 
    return 0;
}

// 現在このボタンの上にプレイヤーがいるのか
bool ButtonObjectController::CheckOnPlayer() const
{
    // 
    GameObject2D *myObj = this->GetMyObject2D();
    if (myObj == nullptr)
    {
        // 
        return false;
    }

    // 
    BaseCollisionList *list = myObj->GetBaseCollisionList();
    if (list == nullptr)
    {
        // 
        return false;
    }

    // 
    Quadrangle2D *collision = static_cast<Quadrangle2D *>(list->SearchCollision(this->mdBody));
    if (collision == nullptr)
    {
        // 
        return false;
    }

    // このボタンがある領域の方のプレイヤー
    GameObject2D *mySidePlayer = nullptr;

    // このボタンが現在光域にある場合と影域にある場合で処理を変える
    if (this->mbLightSide)
    {
        mySidePlayer = Master::GetPlayerController(1)->GetMyObject2D();
    }
    else
    {
        mySidePlayer = Master::GetPlayerController(2)->GetMyObject2D();
    }

    // 
    Point2D tempPoint;
    tempPoint.SetShapeParameter(mySidePlayer->GetPosition());

    // 
    auto result = BaseCollision2DManager::CheckHitCollision2DToCollision2D(&tempPoint, collision);
    if (result.mnResultParam < 0)
    {
        // 
        return false;
    }

    // 
    return true;
}

// 
void ButtonObjectController::UpdateNowState()
{
    // 
    this->mbOnPlayer = this->CheckOnPlayer();
    if (this->mbOnPlayer)
    {
        this->mbOnPlayer = this->CheckOnPlayer();
    }
    else
    {
        this->mbOnPlayer = this->CheckOnPlayer();
    }

    // 
    if (this->mbHitButton)
    {
        // 
        if (this->mnOnFrameCount == 0)
        {
            // 
            if (this->mbOnPlayer)
            {
                // 
                if (this->mbNowOn)
                {
                    // 
                    this->mnNowFrameCount++;
                }
                else
                {
                    // 
                    this->mbNowOn = true;

                    // 
                    this->mnNowFrameCount = 0;
                }
            }
            else
            {
                // 
                if (this->mbNowOn)
                {
                    // 
                    this->mbNowOn = false;

                    // 
                    this->mnNowFrameCount = 0;
                }
                else
                {
                    // 
                    this->mnNowFrameCount++;
                }
            }
        }
        else
        {
            // 
            if (this->mbNowOn)
            {
                // 
                if (this->mbOnPlayer)
                {
                    // 
                    this->mnNowFrameCount = 0;
                }
                else
                {
                    // 
                    if (this->mnOnFrameCount <= this->mnNowFrameCount)
                    {
                        // 
                        this->mbNowOn = false;

                        // 
                        this->mnNowFrameCount = 0;
                    }
                    else
                    {
                        // 
                        this->mnNowFrameCount++;
                    }
                }
            }
            else
            {
                // 
                if (this->mbOnPlayer)
                {
                    // 
                    this->mbNowOn = true;

                    // 
                    this->mnNowFrameCount = 0;
                }
                else
                {
                    // 
                    this->mnNowFrameCount++;
                }
            }
        }
    }
    else
    {
        // 
        if (this->mnOnFrameCount == 0)
        {
            // 
            if (this->mbOnPlayer && !this->mbPushLastFrame)
            {
                // 
                this->mbNowOn = !this->mbNowOn;

                // 
                this->mnNowFrameCount = 0;
            }
            else
            {
                this->mnNowFrameCount++;
            }
        }
        else
        {
            // 
            if (this->mbNowOn)
            {
                // 
                if (this->mnOnFrameCount <= this->mnNowFrameCount)
                {
                    // 
                    if (this->mbOnPlayer)
                    {
                        // 
                        this->mnNowFrameCount = 0;
                    }
                    else
                    {
                        // 
                        this->mbNowOn = false;

                        // 
                        this->mnNowFrameCount = 0;
                    }
                }
                else
                {
                    // 
                    this->mnNowFrameCount++;
                }
            }
            else
            {
                // 
                if (this->mbOnPlayer)
                {
                    // 
                    this->mbNowOn = true;

                    // 
                    this->mnNowFrameCount = 0;
                }
                else
                {
                    // 
                    this->mnNowFrameCount++;
                }
            }
        }
    }
}

// 
void ButtonObjectController::UpdateLightSide()
{
    // 
    VECTOR2D myObjPos = this->GetMyObject2D()->GetPosition();

    // 
    std::vector<int> outBox;
    if (Master::mpLightManager->CheckInLightArea(myObjPos, outBox) != 0)
    {
        return;
    }

    // 
    this->mbLightSide = !outBox.empty();
}

Quadrangle2D *ButtonObjectController::GetBody() const
{
    // 
    return static_cast<Quadrangle2D *>(this->GetMyObject()->GetBaseCollisionList()->SearchCollision(this->mdBody));
}
