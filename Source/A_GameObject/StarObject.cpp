#include "StarObject.h"

#include "../C_Component/BaseComponentList.h"
#include "../C_Component/StarObjectController.h"

// 
StarObject::StarObject(bool oneSide, bool playerLight) :
    mbOneSide(oneSide),
    mbPlayerLight(playerLight),
    GameObject2D(GameObjectTag::GOT_Star)
{
}

// 
StarObject::~StarObject()
{
}

// 
int StarObject::Create()
{
    // 
    this->AddComponent(new StarObjectController(this, this->mbOneSide, this->mbPlayerLight));

    // 
    return 0;
}

// 
StarObjectController *StarObject::GetStarController() const
{
    // 
    auto box = this->GetBaseComponentList()->SearchComponent(ComponentTagAndOrder::CTAO_StarController);

    // 
    if (box.empty() ||
        box[0] == nullptr)
    {
        // 
        return nullptr;
    }

    // 
    return static_cast<StarObjectController *>(box[0]);
}