#pragma once
#include "TestObjectBase.h"

class WallObject : public TestObjectBase
{
private:
	bool mbMoveFlag;

public:
    WallObject();
    ~WallObject();

	void Init() override;
	void Finalize() override;

	void Update() override;

	void Draw() override;

private:
	// 全辺を光マップに設定
	void SetAllEdges_ShineMap();

	// 動いた辺情報を光マップ反映
	void ChangeMoveEdges_ShineMap();
};