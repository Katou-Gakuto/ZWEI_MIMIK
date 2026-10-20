#pragma once
#include "GameObject2D.h"

class TeleportObjectController;

class TeleportObject : public GameObject2D
{
	TeleportObjectController *mpTempController;

public:
	TeleportObject(const VECTOR2D &center, const VECTOR2D &blockSize);
	~TeleportObject();

	int Create() override;

	// 
	TeleportObjectController *GetButtonController()const;
};