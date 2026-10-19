#pragma once
#include "GameObject2D.h"

#include <cstdint>

class ButtonObjectController;

class ButtonObject : public GameObject2D
{
	bool mbOnePush;
	uint32_t mnOnFrameCount;
	VECTOR2D mvCenter;
	VECTOR2D mvBlockSize;

public:
	ButtonObject(bool onePush, uint32_t onFrameCount, const VECTOR2D &center, const VECTOR2D &blockSize);
	~ButtonObject();

	int Create() override;

	// 
	ButtonObjectController *GetButtonController()const;
};