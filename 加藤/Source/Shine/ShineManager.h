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

enum DRAW_MODE_NUMBER
{
	DRAW_MODE_NUMBER_1 = 0,
	DRAW_MODE_NUMBER_2,
	DRAW_MODE_NUMBER_3,
	DRAW_MODE_NUMBER_4,
	DRAW_MODE_NUMBER_5,
	DRAW_MODE_NUMBER_6,
	DRAW_MODE_NUMBER_7,
	DRAW_MODE_NUMBER_MAX
};

enum SHINE_DRAW_MODE
{
	NONE = 0,// 何もない
	OBJECT_SHINE_DRAW_MODE,							// オブジェクト描画
	GRID_SET_MAP_OBJECT_DRAW_MODE,					// グリッドに設定済みオブジェクト描画
	TRIANGLE_SHINE_DRAW_MODE,						// 光の三角をフレーム描画
	TRIANGLE_SHINE_DRAW_MODE_TRUE,					// 光の三角を塗りつぶし描画
	TRIANGLE_SHINE_SINGLE_DRAW_MODE_TRUE,			// 光の三角を一つだけ塗りつぶし描画
	TRIANGLE_LINE_SHINE_SINGLE_DRAW_MODE_TRUE,		// 光の三角を一つだけフレーム描画
	ALL_GRID_SHINE_DRAW_MODE,						// 全グリッド描画
	GRID_SHINE_LOOP_COUNT_DRAW_MODE,				// 光のグリッドを処理したループ数を選択して描画
	GRID_SHINE_DRAW_MODE,							// 光のグリッド描画
	GRID_SHINE_LOOP_NUMBER_DRAW_MODE,				// 光のグリッドを処理したループ数と同時に描画
	GRID_DEBUG_SHINE_LOOP_NUMBER_DRAW_MODE,			// デバッグ光のグリッドを処理したループ数と同時に描画
	GRID_SHINE_NUMBER_DRAW_MODE,					// 光のグリッドを設定した順数と同時に描画
	GRID_DEBUG_SHINE_NUMBER_DRAW_MODE,				// デバッグ光のグリッドを設定した順数と同時に描画
	GRID_WALL_GRID_SHINE_INDEX_DRAW_MODE,			// 壁があるグリッドを光領域の添え字と同時に描画
	SHINE_CHECK_GRID_DRAW_MODE,						// 調べるたときの光領域とグリッドと調べていた先のグリッド描画
	SHINE_AREA_SELECT_CHECK_GRID_DRAW_MODE,			// 光領域を選択してその光領域を参照して調べていたグリッドと調べていた先のグリッド座標を描画
	SHINE_AREA_SELECT_LOOP_CHECK_GRID_DRAW_MODE,	// 処理順と光領域を選択してその光領域を参照して調べていたグリッドと調べていた先のグリッド座標を描画
	OTHER_SHINE_AREA_CHECK_GRID_DRAW_MODE,			// 別の光領域があった判定をした光領域とグリッドと調べていたグリッド座標を描画
	TEST_ANGLE_DRAW_MODE,							// 光のアングル描画
	TEST_ANGLE_DRAW_MODE_TRUE,						// 光のアングル塗りつぶし描画
	TEST_ANGLE_LEFT_DRAW_MODE,						// 光のアングル左直線描画
	TEST_ANGLE_RIGHT_DRAW_MODE,						// 光のアングル右直線描画
	ALL_SHINE_RESULT_DRAW_MODE,						// 光のアングルの偏移をループを選択して描画
	ALL_SHINE_RESULT_SINGLE_DRAW_MODE,				// 光のアングルの偏移をループと個数目を選択して描画
	WALL_LINE_DRAW_MODE,							// 壁となるライン全描画
	WALL_LINE_SINGLE_LOOP_DRAW_MODE,				// 壁となるライン1ループ分描画
	WALL_LINE_SINGLE_AND_INDEX_NUMBER_DRAW_MODE,	// 壁となるライン1個を添え字数と同時に描画
	SHINE_CHECK_DATA_LINE_DRAW_MODE,				// 光の調べたデータを線描画
	SHINE_DRAW_MODE_MAX// 最大
};

enum class SHINE_GRID_TYPE
{
	NOT_SHINE_GRID = 0,									// 光領域外
	SHINE_GRID,											// 光領域内
	SHINE_AND_OBJECT_GRID,								// 光領域内&オブジェクトがある
};

// 方向を数字で変換する物
enum ANGLE_NUMBER
{
	ANGLE_NUMBER_SHINE_LEFT = 0,
	ANGLE_NUMBER_SHINE_RIGHT,
	ANGLE_NUMBER_SHINE_MAX,

	ANGLE_NUMBER_DISPLAY_LEFT_UP = 0,
	ANGLE_NUMBER_DISPLAY_LEFT_DOWN,
	ANGLE_NUMBER_DISPLAY_RIGHT_UP,
	ANGLE_NUMBER_DISPLAY_RIGHT_DOWN,
	ANGLE_NUMBER_DISPLAY_MAX,
};

// 方向を数字で変換する物(BIT)
enum ANGLE_BIT_NUMBER
{
	ANGLE_BIT_NUMBER_LEFT       = 0b0001,
	ANGLE_BIT_NUMBER_RIGHT      = 0b0010,
	ANGLE_BIT_NUMBER_UP         = 0b0100,
	ANGLE_BIT_NUMBER_DOWN       = 0b1000,
	ANGLE_BIT_NUMBER_LEFT_UP    = 0b0101,
	ANGLE_BIT_NUMBER_LEFT_DOWN  = 0b1001,
	ANGLE_BIT_NUMBER_RIGHT_UP   = 0b0110,
	ANGLE_BIT_NUMBER_RIGHT_DOWN = 0b1010,

	ANGLE_BIT_NUMBER_LEFT_RIGHT = 0b0011,
	ANGLE_BIT_NUMBER_UP_DOWN    = 0b1100,
};

class ShineManager
{
public:
	static constexpr int MAP_SIZE_X = 1280;
	static constexpr int MAP_SIZE_Y = 960;

#if false
	static constexpr int MAP_ARRAY_SIZE_X = 1;
	static constexpr int MAP_ARRAY_SIZE_Y = 1;
#else
	static constexpr int MAP_ARRAY_SIZE_X = /*/3/*/10/**/;
	static constexpr int MAP_ARRAY_SIZE_Y = /*/3/*/10/**/;
#endif

	const int ONE_GRID_SIZE_X = MAP_SIZE_X / MAP_ARRAY_SIZE_X;
	const int ONE_GRID_SIZE_Y = MAP_SIZE_Y / MAP_ARRAY_SIZE_Y;

	const float MAP_TO_GRID_SCALE_X = 1.0f / ONE_GRID_SIZE_X;
	const float MAP_TO_GRID_SCALE_Y = 1.0f / ONE_GRID_SIZE_Y;

	// グリッド状にしたマップの当たり判定
	MAP_OBJECT_DATA mstMapObjectGridData[MAP_ARRAY_SIZE_Y][MAP_ARRAY_SIZE_X];

private:
	std::vector<TestObjectBase*> mpObjects;

	std::vector<SHINE_TRIANGLE> mstSheineTriangles;

	// 光源オブジェクト
	ShineObject* mpShineObject;
	// 光源ポジション
	Vector2 mstShinePos;
	// 光源グリッドポジション
	Vector2_Int mstShineGridPos;

	// 描画モード
	int mnDrawMode[DRAW_MODE_NUMBER::DRAW_MODE_NUMBER_MAX];

	// 光領域の偏移確認用変数
	std::vector<std::vector<SHINE_DIRECTION>> mstShineAreaResult;

	// 終わりを迎えた光域(未確定情報保存用)
	std::vector<SHINE_AREA_END_POSITION> mstLightAreaEndPoint;

	// 確認するグリッド確認用変数
	std::vector<std::vector<Vector2_Int>> mstCheckGridPos;

	// 壁ライン設定用
	std::vector<SHINE_AREA_END_POSITION> mstSettingDebugWallLineResult;
	// 壁ライン描画用
	std::vector<std::vector<SHINE_AREA_END_POSITION>> mstDebugWallLinePointDrawData;

	// ラインid現在最大値
	int mnLineIdNowMax;

public:
	ShineManager();
	~ShineManager();

	void Init();

	void Finalize();

	void Update();

	void Draw();

	// ラインID取得
	inline int GetNewLineID()
	{
		++mnLineIdNowMax;
		return mnLineIdNowMax - 1;
	}

	// 指定のグリッド内に補正した値を返す
	Vector2 AdjustPositionToGrid(const Vector2_Int gridIndex, Vector2 pos);

private:
	// 光領域の作成
	void CreateShineArea();

	// グリッドの探索
    void CheckShineGrid();

    // グリッドの状態を判定
    SHINE_GRID_TYPE JudgeGrid(const Vector2_Int& gridPos, const std::vector<SHINE_DIRECTION>& shineDirections, int shineDirectionsIndex);

	// グリッド内に現在の光領域以外の光領域があるか判定
	bool HasOtherShineAreaInGrid(const Vector2_Int& gridPos, const std::vector<SHINE_DIRECTION>& shineDirections, int shineDirectionsIndex);

    // 光を遮るものを確認し、それに応じた処理を行う
    void ShineBlockProcess(std::stack<BLOCK_POS_DATA>& blockPoss, std::queue<Vector2_Int>& nextCheckShinePos, std::vector<SHINE_DIRECTION>& shineDirections);

	// 光域の終端候補を登録する
	void RegisterShineAreaEndPointCandidate(LINE_POS blockLinePos, const BLOCK_POS_DATA& blockPos, std::vector<SHINE_DIRECTION>& shineDirections);
	
	// 登録された光域終端候補を使用して、光域を削り、削った部分を描画用三角形に登録する
	std::vector<SHINE_DIRECTION> ProcessShineAreaEndPointCandidates(int shineIndex, const SHINE_DIRECTION& shineDirections);
	void AddVisibleShineTriangles(const SHINE_DIRECTION& shineDirections);

    // マップ外判定
    bool IsOutsideShineStage(const Vector2_Int& gridPos);

	// 指定したグリッドに光が通っているか判定
	bool IsGridInsideShine(const Vector2_Int& gridPos, const SHINE_DIRECTION& shineDirection);

	// 光領域を左端から右端へ走査するグリッドを取得
	std::vector<Vector2_Int> GetShineGridPositions(const Vector2_Int& nowCheckShinePos, const SHINE_DIRECTION& shineDirection);

	// 描画三角追加
	void AddDrawTriangleData(Vector2 vertex1, Vector2 vertex2);
	// 描画三角追加
	inline void AddDrawTriangleData(SHINE_TRIANGLE shineTriangle) { mstSheineTriangles.push_back(shineTriangle); }

	// DELETE:_ 使用してない関数化してるだけだから使う可能性はある
	// 障害物との交点を取得
	void GetShineBlockingIntersection(const Vector2& edgePos1, const Vector2& edgePos2, const SHINE_DIRECTION& shineDirection, const Vector2_Int& blockPos, Vector2& intersection1, Vector2& intersection2);

	// グリッドの光状態を更新
	void UpdateGridLightState(std::queue<Vector2_Int>& nextCheckShinePos, const std::vector<SHINE_DIRECTION>& shineDirections);

	// 2次元ベクトル同士の外積のZ成分を求める
	float Cross(const Vector2& a, const Vector2& b);

	// 2本の線分の交点を求める
	bool GetIntersection(const Vector2 a, const Vector2 b, const Vector2 c, const Vector2 d, Vector2& intersection);
	
	// 線分ABの延長線と線分CDの延長線の交点を求める
	bool GetLineIntersection(const Vector2& srcA, const Vector2& srcB, const Vector2& dstC, const Vector2& dstD, Vector2& intersection);

	// 2点間の角度を取得します。
	float GetAngleToPoint(const Vector2& from, const Vector2& to);

	// 光の右と左の方向と交点を算出
	bool GetShineDirectionIntersection(const Vector2 shineDirections[ANGLE_NUMBER::ANGLE_NUMBER_SHINE_MAX], float shineAngles[ANGLE_NUMBER::ANGLE_NUMBER_SHINE_MAX], int shineAngleNumbers[ANGLE_NUMBER::ANGLE_NUMBER_SHINE_MAX], Vector2 intersectionPositions[ANGLE_NUMBER::ANGLE_NUMBER_SHINE_MAX], float displayCornerAngles[ANGLE_NUMBER::ANGLE_NUMBER_DISPLAY_MAX], const Vector2 displayCornerPosition[ANGLE_NUMBER::ANGLE_NUMBER_DISPLAY_MAX]);

	// 角が含まれるなら角を描画に追加
	void AddDisplayCornerToDrawTriangle(const Vector2 shineDirections[ANGLE_NUMBER::ANGLE_NUMBER_SHINE_MAX], const int shineAngleNumbers[ANGLE_NUMBER::ANGLE_NUMBER_SHINE_MAX], const Vector2 displayCornerPosition[ANGLE_NUMBER::ANGLE_NUMBER_DISPLAY_MAX]);
};