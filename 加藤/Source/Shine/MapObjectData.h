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
};

// 光を遮る
struct SHINE_AREA_END_POINT : public LINE_POS
{
public:
    // 光域を遮る線分
    LINE_POS linePos;

    // 対象となる光領域のインデックス
    int shineDirectionIndex = -1;
};

// 視界
struct SHINE_DIRECTION
{
	Vector2 shineDirectionLeft;
	Vector2 shineDirectionRight;

	float angle;
	float leftAngle;
	float rightAngle;

	float visionAngle;
};