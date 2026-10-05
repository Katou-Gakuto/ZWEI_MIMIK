#pragma once
#include <vector>

#include "Vector2.h"

struct LINE_POS
{
	Vector2 linePos1;
	Vector2 linePos2;

	int id = -1;
};

// 光領域調査情報
struct SHINE_AREA_CHECK_DATA
{
	// 光領域番号
    int ShineAreaIndex;

	// 調べていた先のグリッド座標
    Vector2_Int CheckGridPos;
};

// マップオブジェクト情報
struct MAP_OBJECT_DATA
{
public:
	std::vector<LINE_POS> LinePoss;

	// 光フラグ
	bool LitFlag;

	// 設定済み光領域添え字
	std::vector<int> ConfiguredShineAreaIndex;

	// デバッグ光フラグ描画用
	bool DebugDrawLiteFlag;

	// 設定したループ数
	int LitLoopNumber;

	// 設定した順番
	int SetLitNumber;
	
	// 別の光領域に参照を変えたときの情報
	std::vector<SHINE_AREA_CHECK_DATA> ShineChangeDatas;

	// 全調査時の光領域と参照先情報
	std::vector<SHINE_AREA_CHECK_DATA> ShineAreaCheckDatas;

	// 光領域添え字
	std::vector<int> ShineAreaIndex;
};

// 視界を遮る情報
struct BLOCK_POS_DATA
{
public:
	Vector2_Int BlockPos;
	int ArrayIndex;
};

// 光領域終了ポジション候補
struct SHINE_AREA_END_POSITION : public LINE_POS
{
public:
	SHINE_AREA_END_POSITION()
	: LINE_POS()
	, shineDirectionIndex(-1)
	{
	}
	SHINE_AREA_END_POSITION(LINE_POS linePos, int index)
	: LINE_POS(linePos)
	, shineDirectionIndex(index)
	{
	}

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