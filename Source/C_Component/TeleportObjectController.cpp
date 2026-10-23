#include "TeleportObjectController.h"

#include "../A_GameObject/GameObject2D.h"

#include "Player.h"

#include "../S_Collision/Quadrangle2D.h"

#include "../Z_Except/DrawSystem.h"
#include "../Z_Except/DxLibDataManager.h"
#include "../Z_Except/Master.h"

// 
TeleportObjectController::TeleportObjectController(
    GameObject *myObject,
    const VECTOR2D &center,
    const VECTOR2D &blockSize) :
    mpPair(nullptr),
    mbTeleportedFromPair(false),
    ButtonObjectController(ComponentTagAndOrder::CTAO_TeleportController, myObject, center, blockSize)
{
}

// 
TeleportObjectController::~TeleportObjectController()
{
}

int TeleportObjectController::Create()
{
    // 
    return this->CreateBody();
}

int TeleportObjectController::Initialize()
{
    // 
    if (this->mpPair == nullptr)
    {
        // 
        return 0;
    }

    // 
    this->mbTeleportedFromPair = false;

    // 
    return 0;
}

int TeleportObjectController::Finalize()
{
    // 
    if (this->mpPair == nullptr)
    {
        // 
        return 0;
    }

    // 
    return 0;
}

int TeleportObjectController::EarlyUpdate()
{
    // 
    if (this->mpPair == nullptr)
    {
        // 
        return 0;
    }

    // 
    return this->BaseEarlyUpdate();
}

int TeleportObjectController::Update()
{
    // 
    if (this->mpPair == nullptr)
    {
        // 
        return 0;
    }

    // 
    return 0;
}

int TeleportObjectController::HitOnCollision(BaseCollision *myCollision, BaseCollision *hitCollision)
{
    // 
    if (this->mpPair == nullptr)
    {
        // 
        return 0;
    }

    // 
    return 0;
}

int TeleportObjectController::LateUpdate()
{
    // 
    if (this->mpPair == nullptr)
    {
        // 
        return 0;
    }

    // 
    int result = this->BaseLateUpdate();
    if (result != 0)
    {
        // 
        return result;
    }

    // 
    if (this->GetNowState())
    {
        // 
        if (!this->mbTeleportedFromPair)
        {
            // 
            auto mySidePlayer = Master::GetPlayerController(this->GetLightSide());
            if (mySidePlayer == nullptr)
            {
                // 
                return -1;
            }

            // 
            mySidePlayer->InitPosition(this->mpPair->GetMyObject2D()->GetPosition());

            // 
            mySidePlayer->ResetHold();

            // 
            this->mpPair->mbTeleportedFromPair = true;
        }
    }
    else
    {
        // 
        if (this->mbTeleportedFromPair)
        {
            // 
            this->mbTeleportedFromPair = false;
        }
    }

    // 
    return 0;
}

int TeleportObjectController::Draw()
{
    // 
    Quadrangle2D *bodyCollision = this->GetBody();

    // ‰©F‚Ì“h‚è‚Â‚Ô‚µƒAƒŠ‚Å“–‚½‚è”»’è‚ÌŽlŠp‚ð•`‰æ‚·‚é
    DRAW_SYSTEM::DrawQuadrangle(
        bodyCollision->GetVertexPos(0),
        bodyCollision->GetVertexPos(1),
        bodyCollision->GetVertexPos(3),
        bodyCollision->GetVertexPos(2),
        0xff00ff,
        true);

    // 
    return 0;
}

// 
bool TeleportObjectController::ConnectPair(TeleportObjectController *newPair)
{
    // 
    if (newPair == nullptr)
    {
        // 
        return false;
    }

    // 
    if (this->mpPair != nullptr)
    {
        // 
        this->mpPair->mpPair = nullptr;

        // 
        this->mpPair = nullptr;
    }

    // 
    this->mpPair = newPair;

    // 
    newPair->mpPair = this;

    // 
    return true;
}
