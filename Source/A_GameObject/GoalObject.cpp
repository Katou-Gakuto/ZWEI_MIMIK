#include "GoalObject.h"

#include "../C_Component/BaseComponentList.h"
#include "../C_Component/GoalObjectController.h"

GoalObject::GoalObject(bool playerLight) :
    mbPlayerLight(playerLight),  
    GameObject2D(GameObjectTag::GOT_Goal)
{
}

GoalObject::~GoalObject()
{
}

int GoalObject::Create()
{
    // 
    this->AddComponent(new GoalObjectController(this, this->mbPlayerLight));

    // 
    return 0;
}

// 
GoalObjectController *GoalObject::GetGoalController() const
{
    // 
    auto box = this->GetBaseComponentList()->SearchComponent(ComponentTagAndOrder::CTAO_GoalController);

    // 
    if (box.empty() ||
        box[0] == nullptr)
    {
        // 
        return nullptr;
    }

    // 
    return static_cast<GoalObjectController *>(box[0]);
}
