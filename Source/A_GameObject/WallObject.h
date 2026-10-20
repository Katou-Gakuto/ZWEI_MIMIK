#pragma once
#include "GameObject2D.h"

class GimmickObjectController;
class WallObjectController;

class WallObject : public GameObject2D
{
protected:
	// 
	WallObject(GameObjectTag tag, bool gimmick, const VECTOR2D &center, const VECTOR2D &blockSize, float radian);

	// 
	bool mbGimmick;

	// 
	VECTOR2D mvCenterPos;

	// 
	VECTOR2D mvBlockSize;

	// 
	float mfRadian;

	// 
	GimmickObjectController *mpTempGimmickPtr;

public:
	WallObject(bool gimmick, const VECTOR2D &center, const VECTOR2D &blockSize, float radian);
	virtual ~WallObject() override;

	virtual int Create() override;

	// 
	WallObjectController *GetWallController() const;

	// 
	GimmickObjectController *GetGimmickController() const;
};