#include "ButtonObject.h"

#include "../C_Component/BaseComponentList.h"
#include "../C_Component/ButtonObjectController.h"

ButtonObject::ButtonObject(bool onePush, uint32_t onFrameCount, const VECTOR2D &center, const VECTOR2D &blockSize) :
    mbOnePush(onePush),
    mnOnFrameCount(onFrameCount),
    mvCenter(center),
    mvBlockSize(blockSize),
    GameObject2D(GameObjectTag::GOT_Button)
{
}

ButtonObject::~ButtonObject()
{
}

int ButtonObject::Create()
{
    // 
    this->AddComponent(new ButtonObjectController(
        this,
        this->mbOnePush,
        this->mnOnFrameCount,
        this->mvCenter,
        this->mvBlockSize));

    // 
    return 0;
}

// 
ButtonObjectController *ButtonObject::GetButtonController()const
{
    // 
    auto list = this->GetBaseComponentList();
    if (list == nullptr)
    {
        // 
        return nullptr;
    }

    // 
    auto tempBox = list->SearchComponent(ComponentTagAndOrder::CTAO_ButtonController);
    if (tempBox.empty() ||
        tempBox[0] == nullptr)
    {
        // 
        return nullptr;
    }

    // 
    return static_cast<ButtonObjectController *>(tempBox[0]);
}