#include "LightObject.h"

#include "../C_Component/BaseComponentList.h"
#include "../C_Component/LightObjectController.h"
#include "../C_Component/GimmickObjectController.h"

#include "../F_PuzzleGimmick/LightExecutor.h"

// 
LightObject::LightObject(const VECTOR2D &initPos, float initRadius) :
    mpTempGimmickPtr(nullptr),
    mvInitPos(initPos),
    mfInitRadius(initRadius),
    GameObject2D(GameObjectTag::GOT_Light)
{
    // 
    this->mpTempGimmickPtr = new GimmickObjectController(this);
}

// 
LightObject::~LightObject()
{
}

// 
int LightObject::Create()
{
    // 
    this->AddComponent(new LightObjectController(this, this->mvInitPos, this->mfInitRadius));

    // 
    this->AddComponent(this->mpTempGimmickPtr);

    // 
    this->mpTempGimmickPtr = nullptr;

    // 
    return 0;
}

// 
GimmickObjectController *LightObject::GetGimmickController() const
{
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
