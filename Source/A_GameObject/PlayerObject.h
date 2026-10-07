#pragma once
#include "GameObject2D.h"

class Player;

class PlayerObject : public GameObject2D
{
	int mnPlayerNumber;
public:
	PlayerObject(int playerNumber);
	~PlayerObject();

	int Create() override;

	// 
	Player *GetPlayerComponent()const;
};