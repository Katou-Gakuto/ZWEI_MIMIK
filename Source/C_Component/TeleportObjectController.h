#pragma once

#include "ButtonObjectController.h"

// 
class TeleportObjectController : public ButtonObjectController
{
public:
    // 
    TeleportObjectController(
        GameObject *myObject,
        const VECTOR2D &center,
        const VECTOR2D &blockSize);

    // 
    ~TeleportObjectController();

    int Create() override;
    int Initialize() override;
    int Finalize() override;
    int EarlyUpdate() override;
    int Update() override;
    int HitOnCollision(BaseCollision *myCollision, BaseCollision *hitCollision) override;
    int LateUpdate() override;
    int Draw() override;

    // 
    bool ConnectPair(TeleportObjectController *newPair);

private:
    // 
    TeleportObjectController *mpPair;

    // 
    bool mbTeleportedFromPair;
};