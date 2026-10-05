#pragma once
#include <vector>

#include "Vector2.h"

#include "TestObjectBase.h"

enum VERTEX_POS_NAME_NUMBER
{
	VERTEX_POS_NAME_LEFT_UP = 0,
	VERTEX_POS_NAME_LEFT_DOWN,
	VERTEX_POS_NAME_RIGHT_UP,
	VERTEX_POS_NAME_RIGHT_DOWN,
	VERTEX_POS_NAME_MAX
};

struct SHINE_GRID_SET_LINE_DATA
{
public:
	SHINE_GRID_SET_LINE_DATA()
	: LinePosData1(nullptr)
	, LinePosData2(nullptr)
	, DataId(-1)
	{
	}
	SHINE_GRID_SET_LINE_DATA(Vector2* posData1, Vector2* posData2, int id)
	: LinePosData1(posData1)
	, LinePosData2(posData2)
	, DataId(id)
	{
	}
	Vector2* LinePosData1;
	Vector2* LinePosData2;
	int DataId;
};

struct SHINE_MAP_MY_WALL_DATAS
{
	Vector2 WallObjectVertexData[VERTEX_POS_NAME_NUMBER::VERTEX_POS_NAME_MAX];

	std::vector<SHINE_GRID_SET_LINE_DATA> ShineMapMyEdfeData;

	bool MoveFlag = false;
};

class WallObject : public TestObjectBase
{
private:
	// 自身の壁情報
	SHINE_MAP_MY_WALL_DATAS mstWallData;

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

	// ライン情報設定処理
	void LineDataSetting(Vector2_Int gridIndex, Vector2 linePos1, Vector2 linePos2, bool yFlag);
};