#pragma once

#include "GameObject2D.h"

class BaseGimmickTrigger;
class LightExecutor;
class GimmickObjectController;

class LightObject : public GameObject2D
{
public:
    // 
    LightObject(const VECTOR2D &initPos, float initRadius);

    // 
    ~LightObject();

    // 
    int Create() override;

    // 
    GimmickObjectController *GetGimmickController() const;

private:
    // 
    GimmickObjectController *mpTempGimmickPtr;

    // 
    VECTOR2D mvInitPos;

    // 
    float mfInitRadius;
};