#pragma once
#include <stack>
#include <queue>
#include <vector>

#include "BitFlag.h"
#include "Vector2.h"

#include "MapObjectData.h"

class ShineObject;
class TestObjectBase;

struct SHINE_TRIANGLE
{
	Vector2_Int Vertex1;
	Vector2_Int Vertex2;
	Vector2_Int Vertex3;
};

enum class CHECK_SHINE_GRID_FLAGS
{
	NAXT_SHINE_AREA = 0,// 次の光領域を調べる
};

enum SHINE_DRAW_MODE
{
	OBJECT_SHINE_DRAW_MODE = 0,
	TRIANGLE_SHINE_DRAW_MODE,
	TRIANGLE_SHINE_DRAW_MODE_TRUE,
	TRIANGLE_SHINE_SINGLE_DRAW_MODE_TRUE,
	TRIANGLE_LINE_SHINE_SINGLE_DRAW_MODE_TRUE,
	GRID_SHINE_DRAW_MODE,
	GRID_SHINE_LOOP_NUMBER_DRAW_MODE,
	GRID_SHINE_NUMBER_DRAW_MODE,
	TEST_ANGLE_DRAW_MODE,
	TEST_ANGLE_LEFT_DRAW_MODE,
	TEST_ANGLE_RIGHT_DRAW_MODE,
	ALL_GRID_SHINE_DRAW_MODE,
	ALL_SHINE_RESULT_DRAW_MODE,
	ALL_SHINE_RESULT_SINGLE_DRAW_MODE,
	SHINE_DRAW_MODE_MAX
};

enum class SHINE_GRID_TYPE
{
	NOT_SHINE_GRID = 0,									// 光領域外
	SHINE_GRID,											// 光領域内
	SHINE_AND_OBJECT_GRID,								// 光領域内&オブジェクトがある

	SHINE_AND_OTHER_SHINE_AREA_GRID,					// 光領域内                 &ほかの光領域もある
	SHINE_AND_OBJECT_AND_OTHER_SHINE_AREA_GRID,			// 光領域内&オブジェクトがある&ほかの光領域もある
};

class ShineManager
{
private:
	static constexpr int MAP_SIZE_X = 1280;
	static constexpr int MAP_SIZE_Y = 960;

	static constexpr int MAP_ARRAY_SIZE_X = 10;
	static constexpr int MAP_ARRAY_SIZE_Y = 10;

	const int ONE_GRID_SIZE_X = MAP_SIZE_X / MAP_ARRAY_SIZE_X;
	const int ONE_GRID_SIZE_Y = MAP_SIZE_Y / MAP_ARRAY_SIZE_Y;

	std::vector<TestObjectBase*> mpObjects;

	std::vector<SHINE_TRIANGLE> mstSheineTriangles;

	// グリッド状にしたマップの当たり判定
	MAP_OBJECT_DATA mstMapObjectGridData[MAP_ARRAY_SIZE_Y][MAP_ARRAY_SIZE_X];

	// 光源オブジェクト
	ShineObject* mpShineObject;
	// 光源ポジション
	Vector2 mstShinePos;
	// 光源グリッドポジション
	Vector2_Int mstShineGridPos;

	// 描画モード
	int mnDrawMode;

	// フラグ
	BIT_FLAG<unsigned short> mstCheckShineGridFlags;

	// 光領域の偏移確認用変数
	std::vector<std::vector<SHINE_DIRECTION>> mstShineAreaResult;

public:
	ShineManager();
	~ShineManager();

	void Init();

	void Finalize();

	void Update();

	void Draw();
private:
	// 光領域の作成
	void CreateShineArea();

	// グリッドの探索
    void CheckShineGrid();

    // グリッドの状態を判定
    SHINE_GRID_TYPE JudgeGrid(const Vector2_Int& gridPos, const std::vector<SHINE_DIRECTION>& shineDirections, int shineDirectionsIndex);

    // 光を遮るものを確認し、それに応じた処理を行う
    void ShineBlockProcess(std::stack<BLOCK_POS_DATA>& blockPoss, std::queue<Vector2_Int>& nextCheckShinePos, std::vector<SHINE_DIRECTION>& shineDirections);

	// 光を遮る物の影響を与える処理
	int ShineBlockingProcess(LINE_POS bloakLinePos, const BLOCK_POS_DATA& bloakPoss, std::vector<SHINE_DIRECTION>& shineDirections);

    // マップ外判定
    bool IsOutsideShineStage(const Vector2_Int& gridPos);

	// 光領域を左端から右端へ走査するグリッドを取得
	std::vector<Vector2_Int> GetShineGridPositions(const Vector2_Int& nowCheckShinePos);

	// 描画三角追加
	void AddDrawTriangleData(Vector2 vertex1, Vector2 vertex2);
};