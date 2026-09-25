#pragma once
#include <vector>

#include "Vector2.h"

struct LINE_POS
{
	Vector2 linePos1;
	Vector2 linePos2;

	int id = -1;
};

// マップオブジェクト情報
struct MAP_OBJECT_DATA
{
public:
	std::vector<LINE_POS> LinePoss;

	// 光フラグ
	bool LitFlag;

	// 設定したループ数
	int LitLoopNumber;

	// 設定した順番
	int SetLitNumber;
};

// 視界を遮る情報
struct BLOCK_POS_DATA
{
public:
	Vector2_Int BlockPos;
	int ArrayIndex;
	bool OutsideGridFlag;
};

// 視界
struct SHINE_DIRECTION
{
	Vector2 shineDirectionLeft;
	Vector2 shineDirectionRight;

	float angle;
	float leftAngle;
	float rightAngle;
};