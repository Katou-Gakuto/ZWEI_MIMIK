#pragma once

// 
#include "GameObject2D.h"

// 
class GoalObjectController;

// 
class GoalObject : public GameObject2D
{
public:
	GoalObject(bool playerLight);
	~GoalObject() override;

	int Create() override;

	// 
	GoalObjectController *GetGoalController() const;

private:
	// 
	bool mbPlayerLight;
};