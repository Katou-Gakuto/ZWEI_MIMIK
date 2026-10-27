#pragma once

#include "BaseScene.h"


class CreditScene : public BaseScene
{
public:

	CreditScene();
	~CreditScene();
	int Create() override;
	int Initialize() override;
	int Finalize() override;
	int Update() override;
	int Draw() override;

};