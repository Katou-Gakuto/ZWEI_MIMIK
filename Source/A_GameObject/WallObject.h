#pragma once
#include "GameObject2D.h"

class GimmickObjectController;

class WallObject : public GameObject2D
{
protected:
	// 
	bool mbGimmick;

	// 
	VECTOR2D mvCenterPos;

	// 
	VECTOR2D mvBlockSize;

public:
	WallObject(bool gimmick, const VECTOR2D &leftUp, const VECTOR2D &rightDown);
	virtual ~WallObject() override;

	virtual int Create() override;

	// 
	GimmickObjectController *GetGimmickController() const;
};