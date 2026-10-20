#include "GoalObjectController.h"

#include "DxLib.h"

#include "../A_GameObject/GameObject2D.h"

#include "Player.h"

#include "../S_Collision/BaseCollision2DManager.h"
#include "../S_Collision/Point2D.h"
#include "../S_Collision/Circle2D.h"

#include "../Z_Except/Master.h"

#include "DrawSystem.h"

// 
GoalObjectController::GoalObjectController(GameObject *myObject, bool playerLight, float goalRadius) :
    mbPlayerLight(playerLight),
    mbInPlayer(false),
    mfGoalRadius(goalRadius),
    BaseComponent(myObject, ComponentTagAndOrder::CTAO_GoalController)
{
}

GoalObjectController::~GoalObjectController()
{

}

int GoalObjectController::Create()
{
    // 
    return 0;
}

int GoalObjectController::Initialize()
{
    // 
    this->mbInPlayer = false;

    // 
    return 0;
}

int GoalObjectController::Finalize()
{
    // 
    return 0;
}

int GoalObjectController::EarlyUpdate()
{
    // 
    return 0;
}

int GoalObjectController::Update()
{
    // 
    return 0;
}

int GoalObjectController::HitOnCollision(BaseCollision *myCollision, BaseCollision *hitCollision)
{
    // 
    return 0;
}

int GoalObjectController::LateUpdate()
{
    // 
    if (!this->UpdateInPlayer())
    {
        // 
        return -1;
    }

    // 
    return 0;
}

int GoalObjectController::Draw()
{
    // 
    unsigned long color = 0x000000;
    if (this->mbInPlayer)
    {
        // 
        color = 0xffffff;
    }
    else
    {
        if (this->mbPlayerLight)
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
    GameObject2D *obj = this->GetMyObject2D();
    if (obj == nullptr)
    {
        // 
        return -1;
    }

    // 
    int result = DRAW_SYSTEM::DrawCircle(
        obj->GetPosition(),
        this->mfGoalRadius,
        color,
        false);

    // 
    return 0;
}

// 
bool GoalObjectController::InitPosition(const VECTOR2D &initPos)
{
    // 
    GameObject2D *obj = this->GetMyObject2D();
    if (obj == nullptr)
    {
        // 
        return false;
    }

    // 
    obj->SetPosition(initPos);

    // 
    return true;
}

// 
bool GoalObjectController::UpdateInPlayer()
{
    // 
    GameObject2D *playerObj = Master::GetPlayerController(this->mbPlayerLight)->GetMyObject2D();
    if (playerObj == nullptr ||
        this->GetMyObject2D() == nullptr)
    {
        // 
        return false;
    }

    // 
    Point2D playerlPoint;
    playerlPoint.SetShapeParameter(playerObj->GetPosition());

    // 
    Circle2D goalCircle;
    goalCircle.SetShapeParameter(this->GetMyObject2D()->GetPosition(), this->mfGoalRadius);

    // 
    auto hitResult = BaseCollision2DManager::CheckHitCollision2DToCollision2D(&playerlPoint, &goalCircle);

    // 
    this->mbInPlayer = (0 <= hitResult.mnResultParam);

    // 
    return true;
}

// 
bool GoalObjectController::GetInPlayer() const
{
    // 
    return this->mbInPlayer;
}