#include "Player.h"
#include "GameObject2D.h"
#include "Master.h"

#include "../C_Component/BaseComponentList.h"
#include "../C_Component/HoldObjectController.h"

#include "../E_Scene/BaseScene.h"
#include "../E_Scene/BaseSceneManager.h"

#include "../T_Model/BaseModelList.h"
#include "../T_Model/DXModelAnim.h"

#include "../S_Collision/BaseCollision.h"
#include "../S_Collision/BaseCollisionList.h"
#include "../S_Collision/Circle2D.h"


Player::Player(GameObject* myObject, int playerNumber)
: BaseComponent(myObject, ComponentTagAndOrder::CTAO_PlayerController)
, mdBodyCollision()
, PlayerNum(playerNumber)
, mpHold(nullptr)
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
    obj->AddCollision(body, this->mdBodyCollision);

    // 
    body->WorldConnectMySelf();

    // 
    obj->AddModel(new DXAnimModel(obj), this->mdModelHandle);
   
    // 
    return 0;
}

int Player::Initialize()
{
    Pos = OldPos;
    //if (Master::mpResourceManager != nullptr);

    DXAnimModel *playerModel = this->GetPlayerModel();

    if (PlayerNum == 1)
    {
        PlayerGraphHandle = playerModel->SetAnimModel("Resource/Run1.png", 8, 30, 150.0f, 150.0f);
    }
    else
    {
        PlayerGraphHandle = playerModel->SetAnimModel("Resource/Run.png", 8, 30, 150.0f, 150.0f);
    }

    // 
    Circle2D *bodyCollision = GetBodyCollision();
    float circleRadius = 50.0f;
    bodyCollision->SetShapeParameter(this->Pos, circleRadius * circleRadius);

    // 
    return 0;
}


int Player::Finalize()
{
    return 0;
}


int Player::EarlyUpdate()
{
    moveVec = VECTOR2D::GetZero();

	//十字ボタン
	if (Master::mpKeyState->GetShadowGameKey(KEY_SHADOW_GAME_TYPE::UP, PlayerNum - 1)/*(CONTROLLER_KEY_TYPE::UP, CONTROLLER_KEY_NUMBER::CONTROLLER_1)*/)
	{
        moveVec.SetY(-4);
	}
	if (Master::mpKeyState->GetShadowGameKey(KEY_SHADOW_GAME_TYPE::DOWN, PlayerNum - 1)/*(CONTROLLER_KEY_TYPE::DOWN, CONTROLLER_KEY_NUMBER::CONTROLLER_1)*/)
	{
        moveVec.SetY(4);
	}
	if (Master::mpKeyState->GetShadowGameKey(KEY_SHADOW_GAME_TYPE::LEFT, PlayerNum - 1)/*(CONTROLLER_KEY_TYPE::LEFT, CONTROLLER_KEY_NUMBER::CONTROLLER_1)*/)
	{
        moveVec.SetX(-4);
	}
	if (Master::mpKeyState->GetShadowGameKey(KEY_SHADOW_GAME_TYPE::RIGHT, PlayerNum - 1)/*(CONTROLLER_KEY_TYPE::RIGHT, CONTROLLER_KEY_NUMBER::CONTROLLER_1)*/)
	{
        moveVec.SetX(4);
	}

	//ボタン
	if (Master::mpKeyState->GetShadowGameKey(KEY_SHADOW_GAME_TYPE::A, PlayerNum - 1)/*(CONTROLLER_KEY_TYPE::UP, CONTROLLER_KEY_NUMBER::CONTROLLER_1)*/)
	{
		// この中にAを押したときの処理を追加する
	}
	if (Master::mpKeyState->GetShadowGameKey(KEY_SHADOW_GAME_TYPE::B, PlayerNum - 1)/*(CONTROLLER_KEY_TYPE::DOWN, CONTROLLER_KEY_NUMBER::CONTROLLER_1)*/)
	{
		// この中にBを押したときの処理を追加する
	}
	if (Master::mpKeyState->GetShadowGameKey(KEY_SHADOW_GAME_TYPE::X, PlayerNum - 1)/*(CONTROLLER_KEY_TYPE::LEFT, CONTROLLER_KEY_NUMBER::CONTROLLER_1)*/)
	{
		// この中にXを押したときの処理を追加する
	}
	if (Master::mpKeyState->GetShadowGameKey(KEY_SHADOW_GAME_TYPE::Y, PlayerNum - 1)/*(CONTROLLER_KEY_TYPE::RIGHT, CONTROLLER_KEY_NUMBER::CONTROLLER_1)*/)
	{
		// この中にYを押したときの処理を追加する
	}


    return 0;
}


int Player::Update()
{
    GameObject2D* player = GetMyObject2D();
    player->SetMoveVec(moveVec);
    player->GetBaseCollisionList()->SetCollisionMoveVec(CollisionDimension::CollisionDimension_2D, &moveVec);
    return 0;
}


int Player::HitOnCollision(BaseCollision *myCollision, BaseCollision *hitCollision)
{
    // 自身の体の当たり判定と当たっている場合は処理を行う
    if (myCollision->GetMyObject() != hitCollision->GetMyObject() &&
        myCollision->GetCollisionTag() == CollisionTag::CollisionTag_CharaBody)
    {
        // 当たったオブジェクトが普通のオブジェクト、ライト、鏡のいずれかの場合は処理を行う
        Hold(hitCollision);
    }

    // 
    if (this->CheckHoldNow())
    {
        //
        HoldMove();
    }

    // 
    return 0;
}


int Player::LateUpdate()
{
    DXAnimModel *playerModel = this->GetPlayerModel();

    // ↓のコードでこのフレームの描画にこのモデルを描画を行うようにできる
    playerModel->SetDrawFlag(true);

    return 0;
}

int Player::Draw()
{
    // 
    bool grahpBoxDraw = false;
    bool bodyCircleDraw = true;

    if (grahpBoxDraw)
    {
        // 
        unsigned int color = 0;
        GameObject2D *player = GetMyObject2D();

        // p1かどうかで処理を変える
        if (PlayerNum == 1)
        {
            // プレイヤー1の場合は赤色で描画
            color = 0xff0000;
        }
        else
        {
            // プレイヤー2の場合は青色で描画
            color = 0x0000ff;
        }

        // 描画を行う
        DrawBox(player->GetPosition().GetX() - (Master::PlayerSizeXY / 2),
            player->GetPosition().GetY() - (Master::PlayerSizeXY / 2),
            player->GetPosition().GetX() + (Master::PlayerSizeXY / 2),
            player->GetPosition().GetY() + (Master::PlayerSizeXY / 2),
            color, false);
    }

    if (bodyCircleDraw)
    {
        // 緑色で円を描画する
        Circle2D *bodyCollision = GetBodyCollision();
        DrawCircle(
            bodyCollision->GetBasePos().GetX(),
            bodyCollision->GetBasePos().GetY(),
            bodyCollision->GetBaseRadius(),
            0x00ff00,
            false);
    }

    return 0;
}

// 
int Player::Hold(BaseCollision *hitCollision)
{
    // @Debug
    // アクションボタン
    // 現在はTEST_1だけど、後々は違うボタンに
    if (!Master::mpKeyState->GetShadowGameKey(KEY_SHADOW_GAME_TYPE::TEST_1, PlayerNum - 1))
    {
        // 何もしない
        return 0;
    }

    // 当たったオブジェクトが普通のオブジェクト、ライト、鏡のいずれでもないなら処理を行う
    if ((hitCollision->GetCollisionTag() == CollisionTag::CollisionTag_Wall ||
        hitCollision->GetCollisionTag() == CollisionTag::CollisionTag_LightBody ||
        hitCollision->GetCollisionTag() == CollisionTag::CollisionTag_Mirror) == false)
    {
        // 何もしない
        return 0;
    }

    // 既にオブジェクトをつかんでいる場合は処理を行う
    if (this->mpHold != nullptr)
    {
        // 掴みっぱなしなので
        return 0;
    }

    // 
    GameObject2D *hitObject = hitCollision->GetMyObject2D();
    if (hitObject == nullptr)
    {
        // 
        return 0;
    }

    // 
    BaseComponentList *compList = hitObject->GetBaseComponentList();
    if (compList == nullptr)
    {
        // 
        return 0;
    }

    // 
    auto conponentBox = compList->SearchComponent(ComponentTagAndOrder::CTAO_HoldController);
    if (conponentBox.empty() ||
        conponentBox[0] == nullptr)
    {
        // 
        return 0;
    }

    // 
    mbHoldFlag = true;

    // 
    this->mpHold = static_cast<HoldObjectController *>(conponentBox[0]);

    // 
    return 0;
}

// 
int Player::HoldMove()
{
    // 
    if (this->mpHold != nullptr)
    {
        // 現状のMoveVecを更新する
        this->mpHold->SyncHoldMoveVec(this->GetMyObject2D()->GetMoveVec2D());
    }

    // 
    return 0;
}

// 
bool Player::CheckHoldObject(const HoldObjectController *hold) const
{
    // 
    return this->mpHold == hold;
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
