#include "PlayerObject.h"
#include "Player.h"

#include "../C_Component/BaseComponentList.h"

PlayerObject::PlayerObject(int playerNumber)
: GameObject2D(GameObjectTag::GOT_Player)
, mnPlayerNumber(playerNumber)
{
}

PlayerObject::~PlayerObject()
{
}

int PlayerObject::Create()
{
	this->AddComponent(new Player(this, mnPlayerNumber));

	return 0;
}

// 
Player *PlayerObject::GetPlayerComponent()const
{
	// 
	auto playerBox = this->GetBaseComponentList()->SearchComponent(ComponentTagAndOrder::CTAO_PlayerController);

	// 
	return static_cast<Player *>(playerBox[0]);
}
