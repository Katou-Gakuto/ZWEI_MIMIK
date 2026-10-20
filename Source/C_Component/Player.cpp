#include "Player.h"
#include "GameObject2D.h"
#include "Master.h"

#include "../A_GameObject/MirrorObject.h"
#include "../A_GameObject/LightObject.h"
#include "../A_GameObject/WallObject.h"

#include "../C_Component/BaseComponentList.h"
#include "../C_Component/HoldObjectController.h"
#include "../C_Component/GoalObjectController.h"
#include "../C_Component/GimmickObjectController.h"
#include "../C_Component/MirrorObjectController.h"
#include "../C_Component/WallObjectController.h"

#include "../E_Scene/BaseScene.h"
#include "../E_Scene/BaseSceneManager.h"

#include "../F_PuzzleGimmick/LightExecutor.h"

#include "../G_LightArea/LightAreaManager.h"

#include "../T_Model/BaseModelList.h"
#include "../T_Model/DXModelAnim.h"

#include "../S_Collision/BaseCollision.h"
#include "../S_Collision/BaseCollision2DManager.h"
#include "../S_Collision/BaseCollisionList.h"
#include "../S_Collision/Point2D.h"
#include "../S_Collision/Circle2D.h"

#include "../Y_Tool/MyFunctions.h"

const int debugNum = 5;

Player::Player(GameObject *myObject, int playerNumber) :
    mnPlayerNum(playerNumber),
    PlayerGraphHandle(),
    mfSwingDegree(1.0f),
    mfNowSwingRadian(0.0f),
    mfMoveMagnitude(4),
    mpHold(nullptr),
    mdBodyCollision(),
    mdModelHandle(),
    mbHoldFlag(false),
    mbSwingFlag(false),
    mbLightSide(playerNumber == 1),
    mbInLightArea(false),
    BaseComponent(myObject, ComponentTagAndOrder::CTAO_PlayerController)
{
}

Player::~Player()
{
}

int Player::Create()
{
    // 
    GameObject2D *obj = this->GetMyObject2D();
    if (obj == nullptr)
    {
        // 
        return -1;
    }
    
    // 
    Circle2D *body = new Circle2D(
        VECTOR2D::GetZero(),
        0.0f,
        obj,
        CollisionTag::CollisionTag_CharaBody,
        CollisionNorm::CollisionNorm_Out,
        false,
        true,
        1.0f);

    // 
    body->AddProcessingTag(CollisionTag::CollisionTag_Wall);

    // 
    body->AddProcessingTag(CollisionTag::CollisionTag_LightBody);

    // 
    obj->AddCollision(body, this->mdBodyCollision);

    // 
    obj->AddModel(new DXAnimModel(obj), this->mdModelHandle);
   
    // 
    return 0;
}

int Player::Initialize()
{
    VECTOR2D pos = this->GetMyObject2D()->GetPosition();
    
    DXAnimModel *playerModel = this->GetPlayerModel();

    if (mnPlayerNum == 1)
    {
        PlayerGraphHandle = playerModel->SetAnimModel("Resource/Run1.png", 8, 30, 150.0f, 150.0f);
    }
    else
    {
        PlayerGraphHandle = playerModel->SetAnimModel("Resource/Run.png", 8, 30, 150.0f, 150.0f);
    }

    // 
    Circle2D *bodyCollision = GetBodyCollision();
    float circleRadius = 20.0f;
    bodyCollision->SetShapeParameter(pos, circleRadius);

    // 
    bodyCollision->WorldConnectMySelf();

    // 
    this->mbInLightArea = this->mbLightSide;

    // 
    this->mpHold = nullptr;

    // 
    return 0;
}


int Player::Finalize()
{
    // 
    Circle2D *bodyCollision = GetBodyCollision();
    bodyCollision->WorldIsolateMySelf();

    return 0;
}


int Player::EarlyUpdate()
{
    return 0;
}


int Player::Update()
{
    // 
    GameObject2D *obj = this->GetMyObject2D();
    if (obj == nullptr)
    {
        // 
        return -1;
    }

    VECTOR2D moveVec = this->GetMoveVecNowFrame();

    // この中にAを押したときの処理がある
    int result = TryHold();

    // 
    if (this->mbHoldFlag)
    {
        // 
        result = this->HoldSwing();

        // 
        if (result != 0)
        {
            // 
            return -1;
        }

        if (!this->mbSwingFlag)
        {
            // 
            this->HoldMove(moveVec);
        }
    }
    else
    {
        // 
        if (this->mpHold != nullptr)
        {
            // 
            this->HoldMove(VECTOR2D::GetZero());

            // 
            this->mpHold->SetHoldFlag(this->mbLightSide, false);

            // 
            this->mpHold = nullptr;
        }
    }

    // 
    if (!this->mbSwingFlag &&
        moveVec != VECTOR2D::GetZero())
    {
        // 
        obj->SetMoveVec(moveVec);

        // 
        obj->GetBaseCollisionList()->SetCollisionMoveVec(CollisionDimension::CollisionDimension_2D, &moveVec);
    }

    if (Master::mpKeyState->GetShadowGameKey(KEY_SHADOW_GAME_TYPE::B, mnPlayerNum - 1)/*(CONTROLLER_KEY_TYPE::DOWN, CONTROLLER_KEY_NUMBER::CONTROLLER_1)*/)
    {
        // この中にBを押したときの処理を追加する
    }
    if (Master::mpKeyState->GetShadowGameKey(KEY_SHADOW_GAME_TYPE::X, mnPlayerNum - 1)/*(CONTROLLER_KEY_TYPE::LEFT, CONTROLLER_KEY_NUMBER::CONTROLLER_1)*/)
    {
        // この中にXを押したときの処理を追加する
    }
    if (Master::mpKeyState->GetShadowGameKey(KEY_SHADOW_GAME_TYPE::Y, mnPlayerNum - 1)/*(CONTROLLER_KEY_TYPE::RIGHT, CONTROLLER_KEY_NUMBER::CONTROLLER_1)*/)
    {
        // この中にYを押したときの処理を追加する
    }

    // 
    return 0;
}


int Player::HitOnCollision(BaseCollision *myCollision, BaseCollision *hitCollision)
{
    // 
    if (this->CheckHoldNow())
    {
        //
        HoldMove(this->GetMyObject2D()->GetMoveVec2D());
    }

    // 
    return 0;
}


int Player::LateUpdate()
{
    DXAnimModel *playerModel = this->GetPlayerModel();

    // ↓のコードでこのフレームの描画にこのモデルを描画を行うようにできる
    playerModel->SetDrawFlag(true);

    // 
    if (this->mpHold != nullptr &&
        this->mbSwingFlag)
    {
        // 
        this->mfNowSwingRadian = this->mpHold->GetRadianPlayerToHold(this->GetMyObject2D()->GetPosition(), debugNum);

        // 
        if (this->mpHold->GetMyObject()->GetObjectTag() == GameObjectTag::GOT_Light)
        {
            this->SetHoldRadian();
        }
    }

    // 
    int result = this->UpdateInLightArea();
    if (result != 0)
    {
        // 
        return result;
    }

    // 
    return 0;
}

int Player::Draw()
{
    // 
    bool grahpBoxDraw = false;
    bool bodyCircleDraw = true;

    GameObject2D *player = GetMyObject2D();
    if (player == nullptr)
    {
        // 
        return -1;
    }

    // 
    unsigned int color = 0;

    // p1かどうかで処理を変える
    if (mnPlayerNum == 1)
    {
        // プレイヤー1の場合は赤色で描画
        color = 0xff0000;
    }
    else
    {
        // プレイヤー2の場合は青色で描画
        color = 0x0000ff;
    }

    if (grahpBoxDraw)
    {
        // 描画を行う
        DrawBox(player->GetPosition().GetX() - (Master::PlayerSizeXY / 2),
            player->GetPosition().GetY() - (Master::PlayerSizeXY / 2),
            player->GetPosition().GetX() + (Master::PlayerSizeXY / 2),
            player->GetPosition().GetY() + (Master::PlayerSizeXY / 2),
            color, false);
    }

    // Aボタンを押していたら円を描画する
    if (bodyCircleDraw)
    {
        // 体の当たり判定である円を緑色で描画する
        Circle2D *bodyCollision = GetBodyCollision();
        DrawCircle(
            bodyCollision->GetBasePos().GetX(),
            bodyCollision->GetBasePos().GetY(),
            bodyCollision->GetBaseRadius(),
            color,
            false);
    }

    // Aボタンを押していたら円を描画する
    if (Master::mpKeyState->GetShadowGameKey(KEY_SHADOW_GAME_TYPE::A, this->mnPlayerNum - 1))
    {
        // ホールドの大体の範囲である円を緑色で描画する
        Circle2D *bodyCollision = GetBodyCollision();
        DrawCircle(
            bodyCollision->GetBasePos().GetX(),
            bodyCollision->GetBasePos().GetY(),
            bodyCollision->GetBaseRadius() + (this->mfMoveMagnitude * 1.5f),
            0x00ff00,
            false);
    }
    
    // 
    std::vector<int> inArea;
    if (Master::mpLightManager->CheckInLightArea(this->GetMyObject2D()->GetPosition(), inArea) != 0)
    {
        // 
        return -1;
    }
    
    // 
    bool inLightArea = !inArea.empty();
    
    // 
    float lightAreaParam = 5.0f;

    // 
    if (inLightArea)
    {
        DrawCircle(
            player->GetPosition().GetX(),
            player->GetPosition().GetY(),
            lightAreaParam,
            0xff0000,
            true);
    }

    // 
    return 0;
}

// 
int Player::TryHold()
{
    // 
    this->mbHoldFlag = false;
    this->mbSwingFlag = false;

    // 
    bool holdCommandFlag = Master::mpKeyState->GetShadowGameKey(KEY_SHADOW_GAME_TYPE::A, mnPlayerNum - 1);

    // 
    if (this->mpHold != nullptr)
    {
        // 
        if (holdCommandFlag)
        {
            // 
            this->mbHoldFlag = true;
        }

        // 関数終了
        return 0;
    }

    //ボタンを押していない場合は処理を行う
    if (!holdCommandFlag)
    {
        // 
        return 0;
    }

    // 
    auto collisionManager = Master::mpBaseSceneManager->SearchSceneAuto()->GetBaseCollision2DManager();
    if (collisionManager == nullptr)
    {
        // 
        return 0;
    }

    // 
    Circle2D *body = this->GetBodyCollision();
    if (body == nullptr)
    {
        // 
        return 0;
    }

    GameObject2D *hitObject = nullptr;
    BaseComponentList *compList = nullptr;
    std::vector<BaseComponent *> componentBox;

    // 
    std::vector<CollisionTag> targetTagBox;
    targetTagBox.push_back(CollisionTag::CollisionTag_LightBody);
    targetTagBox.push_back(CollisionTag::CollisionTag_Mirror);
    targetTagBox.push_back(CollisionTag::CollisionTag_Wall);

    // 
    Circle2D tempCircle;

    // Bodyの半径に + 移動量1.5倍の大きさがHoldに使用する当たり判定の大きさ
    float radius = body->GetBaseRadius() + (this->mfMoveMagnitude * 1.5f);
    tempCircle.SetShapeParameter(this->GetMyObject2D()->GetPosition(), radius);
    tempCircle.SetPenetrate(true);

    // 
    CollisionCheckResult2D hitResult = GetCollisionCheckResult2DZero();
    std::vector<BaseCollision2D *> collisionBox;
    for (auto targetTag : targetTagBox)
    {
        // 
        if (collisionManager->SearchTag(targetTag, collisionBox) != 0)
        {
            // 
            return 0;
        }

        // 
        for (BaseCollision2D *hitCollision : collisionBox)
        {
            // 
            hitResult = BaseCollision2DManager::CheckHitCollision2DToCollision2D(&tempCircle, hitCollision);
            if (hitResult.mnResultParam < 0)
            {
                // 
                continue;
            }

            // 
            hitObject = hitCollision->GetMyObject2D();
            if (hitObject == nullptr)
            {
                // 
                continue;
            }

            compList = hitObject->GetBaseComponentList();
            if (compList == nullptr)
            {
                // 
                continue;
            }

            // 
            componentBox = compList->SearchComponent(ComponentTagAndOrder::CTAO_HoldController);
            if (componentBox.empty() ||
                componentBox[0] == nullptr)
            {
                // 
                continue;
            }

            // 
            HoldObjectController *hold = static_cast<HoldObjectController *>(componentBox[0]);

            // 
            if (!hold->SetHoldFlag(this->mbLightSide, true))
            {
                // 
                break;
            }

            // 
            this->mbHoldFlag = true;

            // 
            this->mpHold = hold;

            // 
            break;
        }

        // 
        if (this->mbHoldFlag)
        {
            // 
            break;
        }
    }

    // 
    if (this->mbHoldFlag)
    {
        // 
        if (this->mpHold->GetSwingFlag())
        {
            // これまで持っていなかったオブジェクトをホールドしたので角度を取得
            this->mfNowSwingRadian = this->mpHold->GetRadianPlayerToHold(this->GetMyObject2D()->GetPosition(), debugNum);

            // 
            if (this->mpHold->GetMyObject()->GetObjectTag() == GameObjectTag::GOT_Light)
            {
                this->SetHoldRadian();
            }
        }
    }

    // 
    return 0;
}

// オブジェクトをつかんでいる状態でHitOnCollision()が呼ばれたら行う関数
int Player::HoldSwing()
{
    // 
    if (!this->mpHold->GetSwingFlag())
    {
        // 
        return 0;
    }

    // 
    bool clockwise = Master::mpKeyState->GetShadowGameKey(KEY_SHADOW_GAME_TYPE::Y, this->mnPlayerNum - 1);
    bool counterClockwise = Master::mpKeyState->GetShadowGameKey(KEY_SHADOW_GAME_TYPE::X, this->mnPlayerNum - 1);

    // 
    if (!clockwise && !counterClockwise)
    {
        // 
        return 0;
    }

    // 
    if (clockwise && counterClockwise)
    {
        // 
        return 1;
    }

    // 
    float addRad = MyFunctions::Deg2Rad(this->mfSwingDegree);
    if (counterClockwise)
    {
        // 
        addRad = -addRad;
    }

    VECTOR2D nowPos = this->GetMyObject2D()->GetPosition();

    // 
    VECTOR2D nowDinstance = this->mpHold->GetMyObject2D()->GetPosition() - nowPos;

    // 
    float distanceMag = nowDinstance.Magnitude();

    // 
    float newRadian = this->mfNowSwingRadian + addRad;

    // 
    bool result = this->mpHold->SetSwingParam(nowPos, newRadian, distanceMag);

    // 
    this->mbSwingFlag = true;

    // 
    return 0;
}

// 
int Player::HoldMove(const VECTOR2D &moveVec)
{
    // 
    if (this->mpHold != nullptr)
    {
        // ほぼ0ベクトルの場合は処理を行う
        if (moveVec == VECTOR2D::GetZero())
        {
            this->mpHold = this->mpHold;
        }

        // 現状のMoveVecを更新する
        this->mpHold->SyncMoveVecToHold(moveVec);

        // 
        if (this->mpHold->GetDoubleHold())
        {
            // 
            int targetPlayerNum = this->mnPlayerNum == 1 ? 2 : 1;

            // 
            Player *target = Master::GetPlayerController(targetPlayerNum);
            target->SyncPlayerMoveVec(moveVec);
        }

    }

    // 
    return 0;
}

// 
bool Player::SyncPlayerMoveVec(const VECTOR2D &holdMoveVec)
{
    // 
    this->GetMyObject2D()->SetMoveVec(holdMoveVec);

    // 
    BaseCollisionList *list = this->GetMyObject2D()->GetBaseCollisionList();
    if (list == nullptr)
    {
        // 
        return 0;
    }

    // 
    list->SetCollisionMoveVec(CollisionDimension::CollisionDimension_2D, &holdMoveVec);

    // 
    return true;
}

// 
VECTOR2D Player::GetMoveVecNowFrame()const
{
    VECTOR2D moveVec = VECTOR2D::GetZero();

    //十字ボタン
    if (Master::mpKeyState->GetShadowGameKey(KEY_SHADOW_GAME_TYPE::UP, mnPlayerNum - 1)/*(CONTROLLER_KEY_TYPE::UP, CONTROLLER_KEY_NUMBER::CONTROLLER_1)*/)
    {
        moveVec.SetY(-1);
    }
    if (Master::mpKeyState->GetShadowGameKey(KEY_SHADOW_GAME_TYPE::DOWN, mnPlayerNum - 1)/*(CONTROLLER_KEY_TYPE::DOWN, CONTROLLER_KEY_NUMBER::CONTROLLER_1)*/)
    {
        moveVec.SetY(1);
    }
    if (Master::mpKeyState->GetShadowGameKey(KEY_SHADOW_GAME_TYPE::LEFT, mnPlayerNum - 1)/*(CONTROLLER_KEY_TYPE::LEFT, CONTROLLER_KEY_NUMBER::CONTROLLER_1)*/)
    {
        moveVec.SetX(-1);
    }
    if (Master::mpKeyState->GetShadowGameKey(KEY_SHADOW_GAME_TYPE::RIGHT, mnPlayerNum - 1)/*(CONTROLLER_KEY_TYPE::RIGHT, CONTROLLER_KEY_NUMBER::CONTROLLER_1)*/)
    {
        moveVec.SetX(1);
    }

    // 
    moveVec = moveVec.SetMagnitude(mfMoveMagnitude);

    // 
    return moveVec;
}

// 
bool Player::InitPosition(const VECTOR2D &pos)
{
    // 
    GameObject2D *obj = this->GetMyObject2D();
    if (obj == nullptr)
    {
        // 
        return false;
    }

    // 
    obj->SetPosition(pos);

    // 
    Circle2D *bodyCollision = GetBodyCollision();
    float circleRadius = 20.0f;
    bodyCollision->SetShapeParameter(pos, circleRadius);

    // 
    return false;
}

// 
bool Player::ChangeLightSide()
{
    // 
    this->mbLightSide = !this->mbLightSide;

    // 
    return true;
}

bool Player::GetInLightArea() const
{
    // 
    return this->mbInLightArea;
}

// 
bool Player::CheckHoldNow() const
{
    // 
    return this->mpHold != nullptr;
}

// 
DXAnimModel *Player::GetPlayerModel()const
{
    GameObject *myObject = this->GetMyObject();
    BaseModelList *modelList = myObject->GetModelList();
    DXAnimModel *playerModel = static_cast<DXAnimModel *>(modelList->SearchModelNumber(this->mdModelHandle));
    // 
    return playerModel;
}

// 
Circle2D *Player::GetBodyCollision() const
{
    // 
    return static_cast<Circle2D *>(this->GetMyObject()->GetBaseCollisionList()->SearchCollision(this->mdBodyCollision));
}

// 
bool Player::SetHoldRadian()
{
    // 
    if (this->mpHold == nullptr ||
        this->mpHold->GetMyObject() == nullptr)
    {
        // 
        return false;
    }

    // 
    float setRagian = this->mfNowSwingRadian;

    // 
    if (this->mpHold->GetMyObject()->GetObjectTag() == GameObjectTag::GOT_Light)
    {
        // 
        if (this->mbLightSide)
        {
            // 
            setRagian += MyFunctions::GetMaxRad() * 0.5f;

            // 
            setRagian = MyFunctions::GetArrangeRad(setRagian);
        }

        // 
        GimmickObjectController *gimmickController = (static_cast<LightObject *>(this->mpHold->GetMyObject()))->GetGimmickController();
        if (gimmickController == nullptr)
        {
            // 
            return false;
        }

        // 
        LightExecutor *currentExecutor = nullptr;

        // 
        auto box = gimmickController->GetGimmickBox();
        auto count = gimmickController->GetGimmickCount();
        for (uint32_t i = 0; i < count; i++)
        {
            currentExecutor = dynamic_cast<LightExecutor *>(box[i].mpExecutor);
            if (currentExecutor != nullptr)
            {
                // 
                currentExecutor->SetBaseAngle(setRagian);
            }
        }
    }
    else if (this->mpHold->GetMyObject()->GetObjectTag() == GameObjectTag::GOT_Mirror)
    {
        // 
        if (this->mbLightSide)
        {
            // 
            setRagian += MyFunctions::GetMaxRad() * 0.5f;

            // 
            setRagian = MyFunctions::GetArrangeRad(setRagian);
        }

        // 
        auto *mirrorObject = static_cast<MirrorObject *>(this->mpHold->GetMyObject());
        if (mirrorObject == nullptr)
        {
            // 
            return false;
        }

        // 
        auto mirrorController = mirrorObject->GetMirrorController();
        if (mirrorController == nullptr)
        {
            // 
            return false;
        }

        // 
        if (!mirrorController->SetBodyCollisionRotateAtNowPos(setRagian))
        {
            // 
            return false;
        }
    }
    else if (this->mpHold->GetMyObject()->GetObjectTag() == GameObjectTag::GOT_Wall)
    {
        // 
        auto *wallObject = static_cast<WallObject *>(this->mpHold->GetMyObject());
        if (wallObject == nullptr)
        {
            // 
            return false;
        }

        // 
        auto wallController = wallObject->GetWallController();
        if (wallController == nullptr)
        {
            // 
            return false;
        }

        // 
        if (!wallController->SetBodyCollisionRotateAtNowPos(setRagian))
        {
            // 
            return false;
        }
    }

    // 
    return true;
}

// 
int Player::UpdateInLightArea()
{
    // 
    GameObject2D *obj = this->GetMyObject2D();
    if (obj == nullptr)
    {
        // 
        return false;
    }

    // 
    std::vector<int> hitArea;
    if (Master::mpLightManager->CheckInLightArea(obj->GetPosition(), hitArea) != 0)
    {
        // 
        return false;
    }

    // 
    this->mbInLightArea = !(hitArea.empty());

    // 
    return 0;
}

