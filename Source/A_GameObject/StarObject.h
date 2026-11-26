#pragma once

#include "GameObject2D.h"

// 
class StarObjectController;

// 
class StarObject : public GameObject2D
{
public:
	// 
	StarObject(bool oneSide, bool playerLight);

	// 
	~StarObject() override;

	// 
	int Create() override;

	// 
	StarObjectController *GetStarController() const;

private:
	// 
	bool mbOneSide;

	// 
	bool mbPlayerLight;
};