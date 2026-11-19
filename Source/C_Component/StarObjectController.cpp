#include "StarObjectController.h"

#include "Player.h"

#include "../A_GameObject/GameObject2D.h"
#include "../E_Scene/BaseSceneManager.h"
#include "../S_Collision/BaseCollision2DManager.h"
#include "../S_Collision/Circle2D.h"
#include "../S_Collision/Point2D.h"
#include "../Z_Except/Master.h"

#include "DrawSystem.h"

// 
const float gfStarRadius = 40.0f;

// 
StarObjectController::StarObjectController(GameObject *myObject, bool oneSide, bool playerLight) :
    mbOneSide(oneSide),
    mbPlayerLight(playerLight),
    BaseComponent(myObject, ComponentTagAndOrder::CTAO_StarController)
{
}

StarObjectController::~StarObjectController()
{
}

int StarObjectController::Create()
{
    // 
    return 0;
}

int StarObjectController::Initialize()
{
    // 
    return 0;
}

int StarObjectController::Finalize()
{
    // 
    return 0;
}

int StarObjectController::EarlyUpdate()
{
    // 
    return 0;
}

int StarObjectController::Update()
{
    // 
    return 0;
}

int StarObjectController::HitOnCollision(BaseCollision *myCollision, BaseCollision *hitCollision)
{
    // 
    return 0;
}

int StarObjectController::LateUpdate()
{
    // 
    if (!this->UpdateInPlayer())
    {
        // 
        return -1;
    }

    // 
    return 0;
}

int StarObjectController::Draw()
{
    // 
    GameObject2D *obj = this->GetMyObject2D();
    if (obj == nullptr)
    {
        // 
        return -1;
    }

    // •`‰æ‚ðs‚¤
    int result = DRAW_SYSTEM::DrawCircle(
        obj->GetPosition(),
        gfStarRadius,
        0xffff00,
        true);

    // 
    return result;
}

// 
bool StarObjectController::InitPosition(const VECTOR2D &initPos)
{
    // 
    this->GetMyObject2D()->SetPosition(initPos);

    // 
    return true;
}

// 
bool StarObjectController::UpdateInPlayer()
{
    // 
    Player *player = nullptr;

    // 
    Circle2D tempCircle;
    tempCircle.SetShapeParameter(this->GetMyObject2D()->GetPosition(), gfStarRadius);

    // 
    Point2D tempPoint;

    // 
    if (this->mbOneSide)
    {
        // 
        if (this->mbPlayerLight)
        {
            // 
            player = Master::GetPlayerController(1);
        }
        else
        {
            // 
            player = Master::GetPlayerController(2);
        }

        // 
        tempPoint.SetShapeParameter(player->GetMyObject2D()->GetPosition());

        // 
        auto result = BaseCollision2DManager::CheckHitCollision2DToCollision2D(&tempPoint, &tempCircle);
        if (0 <= result.mnResultParam)
        {
            // 
            this->GetMyObject()->SetActiveFlag(false);
        }

    }
    else
    {
        // 
        player = Master::GetPlayerController(1);

        // 
        tempPoint.SetShapeParameter(player->GetMyObject2D()->GetPosition());

        // 
        auto result = BaseCollision2DManager::CheckHitCollision2DToCollision2D(&tempPoint, &tempCircle);
        if (0 <= result.mnResultParam)
        {
            // 
            this->GetMyObject()->SetActiveFlag(false);
        }

        // 
        player = Master::GetPlayerController(2);

        // 
        tempPoint.SetShapeParameter(player->GetMyObject2D()->GetPosition());

        // 
        result = BaseCollision2DManager::CheckHitCollision2DToCollision2D(&tempPoint, &tempCircle);
        if (0 <= result.mnResultParam)
        {
            // 
            this->GetMyObject()->SetActiveFlag(false);
        }
    }

    // 
    return true;
}
