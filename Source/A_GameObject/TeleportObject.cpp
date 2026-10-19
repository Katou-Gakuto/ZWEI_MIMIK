#include "TeleportObject.h"

#include "../C_Component/BaseComponentList.h"
#include "../C_Component/TeleportObjectController.h"

TeleportObject::TeleportObject(const VECTOR2D &center, const VECTOR2D &blockSize) :
    mpTempController(new TeleportObjectController(this, center, blockSize)),
    GameObject2D(GameObjectTag::GOT_Teleport)
{
}

TeleportObject::~TeleportObject()
{
}

int TeleportObject::Create()
{
    // 
    if (this->mpTempController == nullptr)
    {
        // 
        return false;
    }

    // 
    this->AddComponent(this->mpTempController);

    // 
    this->mpTempController = nullptr;

    // 
    return 0;
}

// 
TeleportObjectController *TeleportObject::GetButtonController()const
{
    // 
    if (this->mpTempController != nullptr)
    {
        // 
        return this->mpTempController;
    }

    // 
    auto list = this->GetBaseComponentList();
    if (list == nullptr)
    {
        // 
        return nullptr;
    }

    // 
    auto box = list->SearchComponent(ComponentTagAndOrder::CTAO_ButtonController);
    if (box.empty() ||
        box[0] == nullptr)
    {
        // 
        return nullptr;
    }

    // 
    return static_cast<TeleportObjectController *>(box[0]);
}
