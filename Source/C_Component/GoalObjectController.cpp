#include "GoalObjectController.h"

#include "../A_GameObject/GameObject2D.h"

#include "Player.h"

#include "../Z_Except/Master.h"

// 
GoalObjectController::GoalObjectController(GameObject *myObject, bool playerLight) :
    mbPlayerLight(playerLight),
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
    return 0;
}

int GoalObjectController::Draw()
{
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
