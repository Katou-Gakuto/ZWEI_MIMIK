#include "MirrorObject.h"

#include "../C_Component/BaseComponentList.h"
#include "../C_Component/GimmickObjectController.h"
#include "../C_Component/MirrorObjectController.h"

MirrorObject::MirrorObject(bool gimmick, const VECTOR2D &leftUp, const VECTOR2D &rightDown, float radian, unsigned char mirrorFace) :
    mnMirrorFace(mirrorFace),
    WallObject(gimmick, leftUp, rightDown, radian)
{
}

MirrorObject::~MirrorObject()
{
}

int MirrorObject::Create()
{
    // 
    this->AddComponent(new MirrorObjectController(this, this->mvCenterPos, this->mvBlockSize, this->mfRadian, this->mnMirrorFace));

    // 
    if (this->mbGimmick)
    {
        // 
        this->AddComponent(new GimmickObjectController(this));
    }

    // 
    return 0;
}

// 
MirrorObjectController *MirrorObject::GetMirrorController() const
{
    // 
    auto controller = this->GetBaseComponentList()->SearchComponent(ComponentTagAndOrder::CTAO_MirrorController);
    if (controller.empty())
    {
        // 
        return nullptr;
    }

    // 
    return static_cast<MirrorObjectController *>(controller[0]);
}
