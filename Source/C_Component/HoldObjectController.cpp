#include "HoldObjectController.h"

#include "../A_GameObject/GameObject2D.h"

#include "../C_Component/BaseComponentList.h"
#include "../C_Component/Player.h"
#include "../C_Component/GimmickObjectController.h"

#include "../S_Collision/BaseCollisionList.h"

#include "../Z_Except/Master.h"

// 
HoldObjectController::HoldObjectController(GameObject2D *myObj, bool doubleHold, bool oneSide, bool oneSideLight, bool move, bool swing) :
    mnState(0),
    mbFlags(doubleHold, oneSide, oneSideLight, move, swing, false, false, false),
    mbHoldLight(false),
    mbHoldShadow(false),
    BaseComponent(myObj, ComponentTagAndOrder::CTAO_HoldController)
{
}

// 
HoldObjectController::~HoldObjectController()
{
}

// 
int HoldObjectController::Create()
{
    // 
    return 0;
}

// 
int HoldObjectController::Initialize()
{
    // 
    return 0;
}

// 
int HoldObjectController::Finalize()
{
    // 
    return 0;
}

// 
int HoldObjectController::EarlyUpdate()
{
    // 
    this->mnState = 0;

    // 
    this->mbSwingNow = false;

    // 
    return 0;
}

// 
int HoldObjectController::Update()
{
    // 
    return 0;
}

// 
int HoldObjectController::HitOnCollision(BaseCollision *myCollision, BaseCollision *hitCollision)
{
    // Hold‚É‚æ‚éˆÚ“®‚ª‹–‰Â‚³‚ê‚Ä‚¢‚éê‡‚Íˆ—‚ðs‚¤
    if (this->mbFlags[HoldFlagBitIndex::HoldFlagBitIndex_MoveSync])
    {
        // 
        if (this->mnState == HoldFlagBitIndex::HoldFlagBitIndex_MoveSync)
        {
            // 
            if (this->mbFlags[HoldFlagBitIndex::HoldFlagBitIndex_DoubleHold])
            {
                if (this->mbHoldLight && this->mbHoldShadow)
                {
                    Master::GetPlayerController(1)->SyncPlayerMoveVec(this->GetMyObject2D()->GetMoveVec2D());
                    Master::GetPlayerController(2)->SyncPlayerMoveVec(this->GetMyObject2D()->GetMoveVec2D());
                }
            }
            else
            {
                if (this->mbHoldLight)
                {
                    Master::GetPlayerController(1)->SyncPlayerMoveVec(this->GetMyObject2D()->GetMoveVec2D());
                }
                else if (this->mbHoldShadow)
                {
                    Master::GetPlayerController(2)->SyncPlayerMoveVec(this->GetMyObject2D()->GetMoveVec2D());
                }
            }
        }
        else if (this->mnState == HoldFlagBitIndex::HoldFlagBitIndex_Swing)
        {
            // 
            VECTOR2D zeroVec;

            // 
            this->GetMyObject2D()->SetMoveVec(zeroVec);

            // 
            this->GetMyObject2D()->GetBaseCollisionList()->SetCollisionMoveVec(CollisionDimension::CollisionDimension_2D, &zeroVec);
        }
    }

    // 
    return 0;
}

int HoldObjectController::LateUpdate()
{
    // 
    return 0;
}

int HoldObjectController::Draw()
{
    // 
    return 0;
}

// 
bool HoldObjectController::CheckHoldNow() const
{
    // 
    if (this->GetMyObject2D() == nullptr)
    {
        // 
        return false;
    }

    // 
    bool result = false;

    // 
    if (this->mbFlags[HoldFlagBitIndex::HoldFlagBitIndex_DoubleHold])
    {
        // 
        if (this->mbHoldLight && this->mbHoldShadow)
        {
            // 
            result = true;
        }
    }
    else
    {
        // 
        if (this->mbHoldLight != this->mbHoldShadow)
        {
            // 
            result = true;
        }
    }

    // 
    return result;
}

// 
bool HoldObjectController::SetHoldFlag(bool lightPlayer, bool flag)
{
    if (this->mbFlags[HoldFlagBitIndex::HoldFlagBitIndex_DoubleHold])
    {
        // 
        if (lightPlayer)
        {
            this->mbHoldLight = flag;
        }
        else
        {
            this->mbHoldShadow = flag;
        }

        // 
        return true;
    }

    // 
    if (this->mbFlags[HoldFlagBitIndex::HoldFlagBitIndex_OneSide])
    {
        // 
        if (this->mbFlags[HoldFlagBitIndex::HoldFlagBitIndex_OneSideLight] && lightPlayer)
        {
            // 
            this->mbHoldLight = flag;

            // 
            return true;
        }
        else if (!this->mbFlags[HoldFlagBitIndex::HoldFlagBitIndex_OneSideLight] && !lightPlayer)
        {
            // 
            this->mbHoldShadow = flag;

            // 
            return true;
        }
    }
    else
    {
        // 
        if (lightPlayer)
        {
            if (!this->mbHoldShadow)
            {
                this->mbHoldLight = flag;
                return true;
            }
        }
        else
        {
            if (!this->mbHoldLight)
            {
                this->mbHoldShadow = flag;
                return true;
            }
        }
    }

    // 
    return false;
}

// 
float HoldObjectController::GetRadianPlayerToHold(const VECTOR2D &playerPos, int debugNum) const
{
    // 
    VECTOR2D nowPos = this->GetMyObject2D()->GetPosition();

    // 
    VECTOR2D distanceVec = nowPos - playerPos;

    // 
    float radian = 0.0f;
    switch (debugNum)
    {
    case 0:
        radian = atan2f(distanceVec.GetY(), distanceVec.GetX());
        break;
    case 1:
        radian = atan2f(-distanceVec.GetY(), distanceVec.GetX());
        break;
    case 2:
        radian = atan2f(distanceVec.GetY(), -distanceVec.GetX());
        break;
    case 3:
        radian = atan2f(-distanceVec.GetY(), -distanceVec.GetX());
        break;
    case 4:
        radian = atan2f(distanceVec.GetX(), distanceVec.GetY());
        break;
    case 5:
        radian = atan2f(-distanceVec.GetX(), distanceVec.GetY());
        break;
    case 6:
        radian = atan2f(distanceVec.GetX(), -distanceVec.GetY());
        break;
    case 7:
        radian = atan2f(-distanceVec.GetX(), -distanceVec.GetY());
        break;
    default:
        break;
    }
    
    // 
    return radian;
}

// 
bool HoldObjectController::SetSwingParam(const VECTOR2D &centerPos, float radian, float distance)
{
    // 
    if (!this->mbFlags[HoldFlagBitIndex::HoldFlagBitIndex_Swing])
    {
        // 
        return true;
    }

    // 
    if (this->GetMyObject2D() == nullptr)
    {
        // 
        return false;
    }

    // 
    if (this->mnState != 0)
    {
        // 
        return false;
    }

    // 
    VECTOR2D normVec = VECTOR2D::GetOnUnitCirclePos('x', 'y', radian);
    if (normVec == VECTOR2D::GetZero())
    {
        // 
        return false;
    }

    // 
    VECTOR2D distanceVec = normVec * distance;
    VECTOR2D newPos = centerPos + distanceVec;
    VECTOR2D newMoveVec = newPos - this->GetMyObject2D()->GetPosition();

    // 
    this->GetMyObject2D()->SetMoveVec(newMoveVec);

    // 
    this->GetMyObject2D()->GetBaseCollisionList()->SetCollisionMoveVec(CollisionDimension::CollisionDimension_2D, &newMoveVec);

    // 
    this->mnState = HoldFlagBitIndex::HoldFlagBitIndex_Swing;

    // 
    this->mbSwingNow = true;

    // 
    return true;
}

// 
void HoldObjectController::SyncMoveVecToHold(const VECTOR2D &moveVec)
{
    // 
    if (!this->mbFlags[HoldFlagBitIndex::HoldFlagBitIndex_MoveSync])
    {
        // 
        return;
    }

    // 
    if (this->GetMyObject2D() == nullptr)
    {
        // 
        return;
    }

    // 
    if (!(this->mnState == 0 || this->mnState == HoldFlagBitIndex::HoldFlagBitIndex_MoveSync))
    {
        // 
        return;
    }

    // 
    this->GetMyObject2D()->SetMoveVec(moveVec);

    // 
    BaseCollisionList *list = this->GetMyObject2D()->GetBaseCollisionList();
    if (list == nullptr)
    {
        // 
        return;
    }

    // 
    list->SetCollisionMoveVec(CollisionDimension::CollisionDimension_2D, &moveVec);

    // 
    this->mnState = HoldFlagBitIndex::HoldFlagBitIndex_MoveSync;
}

// 
bool HoldObjectController::GetDoubleHold() const
{
    // 
    return this->mbFlags[HoldFlagBitIndex::HoldFlagBitIndex_DoubleHold];
}

// 
bool HoldObjectController::GetSwingFlag() const
{
    // 
    return this->mbFlags[HoldFlagBitIndex::HoldFlagBitIndex_Swing];
}
