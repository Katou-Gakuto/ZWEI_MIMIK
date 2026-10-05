#include "MirrorObject.h"

#include "../C_Component/BaseComponentList.h"
#include "../C_Component/GimmickObjectController.h"
#include "../C_Component/MirrorObjectController.h"

MirrorObject::MirrorObject(bool gimmick, const VECTOR2D &leftUp, const VECTOR2D &rightDown, unsigned char mirrorFace) :
    mnMirrorFace(mirrorFace),
    WallObject(gimmick, leftUp, rightDown)
{
}

MirrorObject::~MirrorObject()
{
}

int MirrorObject::Create()
{
    // 
    this->AddComponent(new MirrorObjectController(this, this->mvCenterPos, this->mvBlockSize, this->mnMirrorFace));

    // 
    if (this->mbGimmick)
    {
        // 
        this->AddComponent(new GimmickObjectController(this));
    }

    // 
    return 0;
}
