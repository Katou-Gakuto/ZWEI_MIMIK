#include "WallObject.h"

#include "../C_Component/BaseComponentList.h"
#include "../C_Component/GimmickObjectController.h"
#include "../C_Component/WallObjectController.h"

WallObject::WallObject(bool gimmick, const VECTOR2D &center, const VECTOR2D &blockSize) :
    mbGimmick(gimmick),
    mvCenterPos(center),
    mvBlockSize(blockSize),
    mpTempGimmickPtr(nullptr),
    GameObject2D(GameObjectTag::GOT_Player)
{
    // 
    if (this->mbGimmick)
    {
        // 
        this->mpTempGimmickPtr = new GimmickObjectController(this);
    }
}

WallObject::~WallObject()
{
}

int WallObject::Create()
{
    // 
    this->AddComponent(new WallObjectController(this, this->mvCenterPos, this->mvBlockSize));

    // 
    this->AddComponent(this->mpTempGimmickPtr);

    // 
    this->mpTempGimmickPtr = nullptr;

    // 
    return 0;
}

// 
GimmickObjectController *WallObject::GetGimmickController() const
{
    // 
    if (!this->mbGimmick)
    {
        // 
        return nullptr;
    }

    // 
    if (this->mpTempGimmickPtr != nullptr)
    {
        // 
        return this->mpTempGimmickPtr;
    }

    // 
    auto controller = this->GetBaseComponentList()->SearchComponent(ComponentTagAndOrder::CTAO_GimmickController);
    if (controller.empty())
    {
        // 
        return nullptr;
    }

    // 
    return static_cast<GimmickObjectController *>(controller[0]);
}
