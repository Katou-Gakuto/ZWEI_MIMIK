#include <algorithm>
#include <cmath>
#include <stack>
#include <queue>
#include <vector>

#include "BitFlag.h"
#include "Vector2.h"

#include "DxLib.h"

#include "Master.h"

#include "ShineManager.h"
#include "ShineObject.h"
#include "TestObjectBase.h"
#include "WallObject.h"
#include "ImguiManager.h"

#ifdef _DEBUG
#include "DebugLogs/DebugLog.h"
#endif

enum TEST_INDEX_NUMBERS
{
    TEST_SHINE_TRIANGLE_DRAW_X = 0,
    TEST_SHINE_TRIANGLE_DRAW_Y,

    TEST_SHINE_RESULT_DRAW_INDEX,
    TEST_SHINE_RESULT_SINGLE_DRAW_INDEX,
    TEST_SHINE_TRIANGLE_SINGLE_DRAW_INDEX,
};

enum TEST_INDEX_NUMBERS_VALUE
{
    TEST_VALUE_SHINE_TRIANGLE_DRAW_X = 0,
    TEST_VALUE_SHINE_TRIANGLE_DRAW_Y,
    TEST_VALUE_MAX_NUMBER
};

enum TEST_INDEX_NUMBERS_BUTTON
{
    TEST_BUTTON_SHINE_RESULT_DRAW_INDEX = 0,
    TEST_BUTTON_SHINE_RESULT_SINGLE_DRAW_INDEX,
    TEST_BUTTON_SHINE_TRIANGLE_SINGLE_DRAW_INDEX,
    TEST_BUTTON_MAX_NUMBER
};

static int testNumber[TEST_INDEX_NUMBERS_VALUE::TEST_VALUE_MAX_NUMBER + TEST_INDEX_NUMBERS_BUTTON::TEST_BUTTON_MAX_NUMBER] = {};
static int testNumberValue[TEST_INDEX_NUMBERS_VALUE::TEST_VALUE_MAX_NUMBER] = {};
static int testNumberButton[TEST_INDEX_NUMBERS_BUTTON::TEST_BUTTON_MAX_NUMBER] = {};



ShineManager::ShineManager()
: mpObjects()
, mstSheineTriangles()
, mpShineObject(nullptr)
, mstShinePos()
, mstShineGridPos()
, mstCheckShineGridFlags()
, mstShineAreaResult()
, mnLineIdNowMax(0)
{
    for (int i = 0; i < DRAW_MODE_NUMBER::DRAW_MODE_NUMBER_MAX; ++i)
    {
        mnDrawMode[i] = SHINE_DRAW_MODE::NONE;
    }
    mnDrawMode[0] = SHINE_DRAW_MODE::GRID_SHINE_DRAW_MODE;
}

ShineManager::~ShineManager()
{
}

void ShineManager::Init()
{
    mpObjects.clear();

    // ここで生成
    WallObject* wallObject = new WallObject();
    wallObject->SetPosition(Vector2(1280 * 0.7f, 960 * 0.7f));
    wallObject->SetSize(Vector2(1280 * 0.05f, 960 * 0.05f));
    mpObjects.push_back(wallObject);
    wallObject = new WallObject();
    wallObject->SetPosition(Vector2(1280 * 0.5f, 960 * 0.5f));
    wallObject->SetSize(Vector2(1280 * 0.05f, 960 * 0.05f));
    mpObjects.push_back(wallObject);

    mpShineObject = new ShineObject();
    mpShineObject->Init();

    for (int y = 0; y < MAP_ARRAY_SIZE_Y; ++y)
    {
        for (int x = 0; x < MAP_ARRAY_SIZE_X; ++x)
        {
            mstMapObjectGridData[y][x].LinePoss.clear();
            mstMapObjectGridData[y][x].LitFlag = false;
        }
    }

    // 生成したオブジェクト初期化
    for (auto& object : mpObjects)
    {
        object->Init();
    }
}

void ShineManager::Finalize()
{
    for (auto& object : mpObjects)
    {
        object->Finalize();
    }

    mpObjects.clear();

    mpShineObject->Finalize();
    delete mpShineObject;
}

void ShineManager::Update()
{
    for (auto& object : mpObjects)
    {
        object->Update();
    }
    mpShineObject->Update();

    // 光領域作成
    CreateShineArea();

    for (int i = 0; i < DRAW_MODE_NUMBER::DRAW_MODE_NUMBER_MAX; ++i)
    {
        Master::mpImguiManager->AddDrawImgui(IMGUI_INT_DATA::GetImguiData(
            {&mnDrawMode[i]},
            0.1f, 
            0.1f, 
            0.1f, 
            0, 
            SHINE_DRAW_MODE::SHINE_DRAW_MODE_MAX - 1, 
            "_DRAW_MODE_" + std::to_string(i), 
            "%d", 
            0x10,
            IMGUI_TYPE::SLIDER1,
            false));
    }
    for (int i = 0; i < TEST_INDEX_NUMBERS_VALUE::TEST_VALUE_MAX_NUMBER; ++i)
    {
        testNumberValue[i] = testNumber[i];
    }
    for (int i = 0; i < TEST_INDEX_NUMBERS_BUTTON::TEST_BUTTON_MAX_NUMBER; ++i)
    {
        testNumberButton[i] = testNumber[i + TEST_INDEX_NUMBERS_VALUE::TEST_VALUE_MAX_NUMBER];
    }
    for (int i = 0; i < TEST_INDEX_NUMBERS_VALUE::TEST_VALUE_MAX_NUMBER; ++i)
    {
        Master::mpImguiManager->AddDrawImgui(IMGUI_INT_DATA::GetImguiData(
            {&testNumberValue[i]},
            0.1f, 
            0.1f, 
            0.1f, 
            -100, 
            100, 
            "_TEST_VALUE_NUMBER_", 
            "%d",
            0,
            IMGUI_TYPE::DRAG1));
    }
    for (int i = 0; i < TEST_INDEX_NUMBERS_BUTTON::TEST_BUTTON_MAX_NUMBER; ++i)
    {
        Master::mpImguiManager->AddDrawImgui(IMGUI_INT_DATA::GetImguiData(
            {&testNumberButton[i]},
            1.0f, 
            1.0f, 
            1.0f, 
            0, 
            100, 
            "_TEST_BUTTON_NUMBER", 
            "%d",
            0,
            IMGUI_TYPE::SLIDER1));
    }
    for (int i = 0; i < TEST_INDEX_NUMBERS_VALUE::TEST_VALUE_MAX_NUMBER; ++i)
    {
        testNumber[i] = testNumberValue[i];
    }
    for (int i = 0; i < TEST_INDEX_NUMBERS_BUTTON::TEST_BUTTON_MAX_NUMBER; ++i)
    {
        testNumber[i + TEST_INDEX_NUMBERS_VALUE::TEST_VALUE_MAX_NUMBER] = testNumberButton[i];
    }
}

void ShineManager::Draw()
{
    int x = 0, y = 0;
    int magnification = 3000;
    for (int drawModeIndex = 0; drawModeIndex < DRAW_MODE_NUMBER::DRAW_MODE_NUMBER_MAX; ++drawModeIndex)
    {
        switch (mnDrawMode[drawModeIndex])
        {
        case SHINE_DRAW_MODE::OBJECT_SHINE_DRAW_MODE:
            for (auto& object : mpObjects)
            {
                object->Draw();
            }
            break;
        case SHINE_DRAW_MODE::GRID_SET_MAP_OBJECT_DRAW_MODE:
            for (int y = 0; y < MAP_ARRAY_SIZE_Y; ++y)
            {
                for (int x = 0; x < MAP_ARRAY_SIZE_X; ++x)
                {
                    for (int i = 0; i < static_cast<int>(mstMapObjectGridData[y][x].LinePoss.size()); ++i)
                    {
                        DrawLine(
                            mstMapObjectGridData[y][x].LinePoss[i].linePos1.x, mstMapObjectGridData[y][x].LinePoss[i].linePos1.y,
                            mstMapObjectGridData[y][x].LinePoss[i].linePos2.x, mstMapObjectGridData[y][x].LinePoss[i].linePos2.y,
                            GetColor(255, 255, 255));
                    }
                }
            }
            break;
        
        case SHINE_DRAW_MODE::TRIANGLE_SHINE_DRAW_MODE:
            for (const SHINE_TRIANGLE& shineTriangle : mstSheineTriangles)
            {
                x += testNumber[TEST_INDEX_NUMBERS::TEST_SHINE_TRIANGLE_DRAW_X];
                y += testNumber[TEST_INDEX_NUMBERS::TEST_SHINE_TRIANGLE_DRAW_Y];
                // 光領域の描画
                DrawTriangle(
                    shineTriangle.Vertex1.x + x, shineTriangle.Vertex1.y + y,
                    shineTriangle.Vertex2.x, shineTriangle.Vertex2.y,
                    shineTriangle.Vertex3.x, shineTriangle.Vertex3.y,
                    GetColor(255, 255, 255), FALSE
                );
            }
            break;
        
        case SHINE_DRAW_MODE::TRIANGLE_SHINE_DRAW_MODE_TRUE:
            for (const SHINE_TRIANGLE& shineTriangle : mstSheineTriangles)
            {
                x += testNumber[TEST_INDEX_NUMBERS::TEST_SHINE_TRIANGLE_DRAW_X];
                y += testNumber[TEST_INDEX_NUMBERS::TEST_SHINE_TRIANGLE_DRAW_Y];
                // 光領域の描画
                DrawTriangle(
                    shineTriangle.Vertex1.x + x, shineTriangle.Vertex1.y + y,
                    shineTriangle.Vertex2.x, shineTriangle.Vertex2.y,
                    shineTriangle.Vertex3.x, shineTriangle.Vertex3.y,
                    GetColor(255, 255, 255), TRUE
                );
            }
            break;
        
        case SHINE_DRAW_MODE::TRIANGLE_SHINE_SINGLE_DRAW_MODE_TRUE:
            if (mstSheineTriangles.size() <= 0)
            {
                break;
            }
            if (mstSheineTriangles.size() <= testNumber[TEST_INDEX_NUMBERS::TEST_SHINE_TRIANGLE_SINGLE_DRAW_INDEX])
            {
                testNumber[TEST_INDEX_NUMBERS::TEST_SHINE_TRIANGLE_SINGLE_DRAW_INDEX] = mstSheineTriangles.size() - 1;
            }
            {
                SHINE_TRIANGLE drawSingleTriangleData = mstSheineTriangles[testNumber[TEST_INDEX_NUMBERS::TEST_SHINE_TRIANGLE_SINGLE_DRAW_INDEX]];
                // 光領域の描画
                DrawTriangle(
                    drawSingleTriangleData.Vertex1.x, drawSingleTriangleData.Vertex1.y,
                    drawSingleTriangleData.Vertex2.x, drawSingleTriangleData.Vertex2.y,
                    drawSingleTriangleData.Vertex3.x, drawSingleTriangleData.Vertex3.y,
                    GetColor(255, 255, 255), TRUE
                );
            }
            break;
        
        case SHINE_DRAW_MODE::TRIANGLE_LINE_SHINE_SINGLE_DRAW_MODE_TRUE:
            if (mstSheineTriangles.size() <= 0)
            {
                break;
            }
            if (mstSheineTriangles.size() <= testNumber[TEST_INDEX_NUMBERS::TEST_SHINE_TRIANGLE_SINGLE_DRAW_INDEX])
            {
                testNumber[TEST_INDEX_NUMBERS::TEST_SHINE_TRIANGLE_SINGLE_DRAW_INDEX] = mstSheineTriangles.size() - 1;
            }
            {
                SHINE_TRIANGLE drawSingleTriangleData = mstSheineTriangles[testNumber[TEST_INDEX_NUMBERS::TEST_SHINE_TRIANGLE_SINGLE_DRAW_INDEX]];
                // 光領域の描画
                DrawLine(drawSingleTriangleData.Vertex1.x, drawSingleTriangleData.Vertex1.y,
                    drawSingleTriangleData.Vertex2.x, drawSingleTriangleData.Vertex2.y,
                    GetColor(255, 0, 0)
                );
                DrawLine(drawSingleTriangleData.Vertex1.x, drawSingleTriangleData.Vertex1.y,
                    drawSingleTriangleData.Vertex3.x, drawSingleTriangleData.Vertex3.y,
                    GetColor(0, 255, 0)
                );
            }
            break;
        
        case SHINE_DRAW_MODE::GRID_SHINE_DRAW_MODE:
            for (int y = 0; y < MAP_ARRAY_SIZE_Y; ++y)
            {
                for (int x = 0; x < MAP_ARRAY_SIZE_X; ++x)
                {
                    if (mstMapObjectGridData[y][x].LitFlag)
                    {
                        DrawBox(ONE_GRID_SIZE_X * x,       ONE_GRID_SIZE_Y * y,
                                ONE_GRID_SIZE_X * (x + 1), ONE_GRID_SIZE_Y * (y + 1),
                                GetColor(255, 255, 255),
                                FALSE);
                    }
                }
            }
            break;
        
        case SHINE_DRAW_MODE::GRID_SHINE_LOOP_NUMBER_DRAW_MODE:
            for (int y = 0; y < MAP_ARRAY_SIZE_Y; ++y)
            {
                for (int x = 0; x < MAP_ARRAY_SIZE_X; ++x)
                {
                    if (mstMapObjectGridData[y][x].LitFlag)
                    {
                        DrawBox(ONE_GRID_SIZE_X * x,       ONE_GRID_SIZE_Y * y,
                                ONE_GRID_SIZE_X * (x + 1), ONE_GRID_SIZE_Y * (y + 1),
                                GetColor(255, 255, 255),
                                FALSE);
                        DrawString(ONE_GRID_SIZE_X * x, ONE_GRID_SIZE_Y * y, std::to_string(mstMapObjectGridData[y][x].LitLoopNumber).c_str(), GetColor(255, 255, 255));
                    }
                }
            }
            break;
        
        case SHINE_DRAW_MODE::GRID_SHINE_NUMBER_DRAW_MODE:
            for (int y = 0; y < MAP_ARRAY_SIZE_Y; ++y)
            {
                for (int x = 0; x < MAP_ARRAY_SIZE_X; ++x)
                {
                    if (mstMapObjectGridData[y][x].LitFlag)
                    {
                        DrawBox(ONE_GRID_SIZE_X * x,       ONE_GRID_SIZE_Y * y,
                                ONE_GRID_SIZE_X * (x + 1), ONE_GRID_SIZE_Y * (y + 1),
                                GetColor(255, 255, 255),
                                FALSE);
                        DrawString(ONE_GRID_SIZE_X * x, ONE_GRID_SIZE_Y * y, std::to_string(mstMapObjectGridData[y][x].SetLitNumber).c_str(), GetColor(255, 255, 255));
                    }
                }
            }
            break;
        
        case SHINE_DRAW_MODE::ALL_GRID_SHINE_DRAW_MODE:
            for (int y = 0; y < MAP_ARRAY_SIZE_Y; ++y)
            {
                for (int x = 0; x < MAP_ARRAY_SIZE_X; ++x)
                {
                    {
                        DrawBox(ONE_GRID_SIZE_X * x,       ONE_GRID_SIZE_Y * y,
                                ONE_GRID_SIZE_X * (x + 1), ONE_GRID_SIZE_Y * (y + 1),
                                GetColor(255, 255, 255),
                                FALSE);
                    }
                }
            }
            break;
        
        case SHINE_DRAW_MODE::ALL_SHINE_RESULT_DRAW_MODE:
            if (mstShineAreaResult.size() <= 0)
            {
                break;
            }
            if (mstShineAreaResult.size() <= testNumber[TEST_INDEX_NUMBERS::TEST_SHINE_RESULT_DRAW_INDEX])
            {
                testNumber[TEST_INDEX_NUMBERS::TEST_SHINE_RESULT_DRAW_INDEX] = mstShineAreaResult.size() - 1;
            }
            for (auto shineAreaResult : mstShineAreaResult[testNumber[TEST_INDEX_NUMBERS::TEST_SHINE_RESULT_DRAW_INDEX]])
            {      
                DrawTriangle(
                    mpShineObject->GetPosition().x, mpShineObject->GetPosition().y,
                    mpShineObject->GetPosition().x + (shineAreaResult.shineDirectionLeft.x * magnification), mpShineObject->GetPosition().y + (shineAreaResult.shineDirectionLeft.y * magnification),
                    mpShineObject->GetPosition().x + (shineAreaResult.shineDirectionRight.x * magnification), mpShineObject->GetPosition().y + (shineAreaResult.shineDirectionRight.y * magnification),
                    GetColor(0,255,0),
                    TRUE
                );
            }
            break;
        
        case SHINE_DRAW_MODE::ALL_SHINE_RESULT_SINGLE_DRAW_MODE:
        {
            if (mstShineAreaResult.size() <= 0)
            {
                break;
            }
            if (mstShineAreaResult.size() <= testNumber[TEST_INDEX_NUMBERS::TEST_SHINE_RESULT_DRAW_INDEX])
            {
                testNumber[TEST_INDEX_NUMBERS::TEST_SHINE_RESULT_DRAW_INDEX] = mstShineAreaResult.size() - 1;
            }
            if (mstShineAreaResult[testNumber[TEST_INDEX_NUMBERS::TEST_SHINE_RESULT_DRAW_INDEX]].size() <= testNumber[TEST_INDEX_NUMBERS::TEST_SHINE_RESULT_SINGLE_DRAW_INDEX])
            {
                testNumber[TEST_INDEX_NUMBERS::TEST_SHINE_RESULT_SINGLE_DRAW_INDEX] = mstShineAreaResult[testNumber[TEST_INDEX_NUMBERS::TEST_SHINE_RESULT_DRAW_INDEX]].size() - 1;
            }
            SHINE_DIRECTION drawShineArea = mstShineAreaResult[testNumber[TEST_INDEX_NUMBERS::TEST_SHINE_RESULT_DRAW_INDEX]][testNumber[TEST_INDEX_NUMBERS::TEST_SHINE_RESULT_SINGLE_DRAW_INDEX]];
            DrawTriangle(
                mpShineObject->GetPosition().x, mpShineObject->GetPosition().y,
                mpShineObject->GetPosition().x + (drawShineArea.shineDirectionLeft.x * magnification), mpShineObject->GetPosition().y + (drawShineArea.shineDirectionLeft.y * magnification),
                mpShineObject->GetPosition().x + (drawShineArea.shineDirectionRight.x * magnification), mpShineObject->GetPosition().y + (drawShineArea.shineDirectionRight.y * magnification),
                GetColor(0,0,255),
                TRUE
            );
        }
            break;
        
        case SHINE_DRAW_MODE::TEST_ANGLE_DRAW_MODE:
            DrawTriangle(
                mpShineObject->GetPosition().x, mpShineObject->GetPosition().y,
                mpShineObject->GetPosition().x + (mpShineObject->GetShineDirection().shineDirectionLeft.x * magnification), mpShineObject->GetPosition().y + (mpShineObject->GetShineDirection().shineDirectionLeft.y * magnification),
                mpShineObject->GetPosition().x + (mpShineObject->GetShineDirection().shineDirectionRight.x * magnification), mpShineObject->GetPosition().y + (mpShineObject->GetShineDirection().shineDirectionRight.y * magnification),
                GetColor(255,255,255),
                FALSE
            );
            break;
        
        case SHINE_DRAW_MODE::TEST_ANGLE_DRAW_MODE_TRUE:
            DrawTriangle(
                mpShineObject->GetPosition().x, mpShineObject->GetPosition().y,
                mpShineObject->GetPosition().x + (mpShineObject->GetShineDirection().shineDirectionLeft.x * magnification), mpShineObject->GetPosition().y + (mpShineObject->GetShineDirection().shineDirectionLeft.y * magnification),
                mpShineObject->GetPosition().x + (mpShineObject->GetShineDirection().shineDirectionRight.x * magnification), mpShineObject->GetPosition().y + (mpShineObject->GetShineDirection().shineDirectionRight.y * magnification),
                GetColor(255,255,255),
                TRUE
            );
            break;
        
        case SHINE_DRAW_MODE::TEST_ANGLE_LEFT_DRAW_MODE:
            DrawLine(
                mpShineObject->GetPosition().x, mpShineObject->GetPosition().y,
                mpShineObject->GetPosition().x + (mpShineObject->GetShineDirection().shineDirectionLeft.x * magnification), mpShineObject->GetPosition().y + (mpShineObject->GetShineDirection().shineDirectionLeft.y * magnification),
                GetColor(255,255,255),
                TRUE
            );
            break;
        
        case SHINE_DRAW_MODE::TEST_ANGLE_RIGHT_DRAW_MODE:
            DrawLine(
                mpShineObject->GetPosition().x, mpShineObject->GetPosition().y,
                mpShineObject->GetPosition().x + (mpShineObject->GetShineDirection().shineDirectionRight.x * magnification), mpShineObject->GetPosition().y + (mpShineObject->GetShineDirection().shineDirectionRight.y * magnification),
                GetColor(255,255,255),
                TRUE
            );
            break;
        }
    }

    mpShineObject->Draw();
}

// 指定のグリッド内に補正した値を返す
Vector2 ShineManager::AdjustPositionToGrid(const Vector2_Int gridIndex, Vector2 pos)
{
    if (pos.x < ((gridIndex.x) * ONE_GRID_SIZE_X))
    {
        pos.x = (gridIndex.x * ONE_GRID_SIZE_X);
    }
    else if (pos.x > ((gridIndex.x + 1) * ONE_GRID_SIZE_X))
    {
        pos.x = ((gridIndex.x + 1) * ONE_GRID_SIZE_X);
    }
    
    if (pos.y < (gridIndex.y * ONE_GRID_SIZE_Y))
    {
        pos.y = (gridIndex.y * ONE_GRID_SIZE_Y);
    }
    else if (pos.y > ((gridIndex.y + 1) * ONE_GRID_SIZE_Y))
    {
        pos.y = ((gridIndex.y + 1) * ONE_GRID_SIZE_Y);
    }

    return pos;
}

// 光領域の作成
void ShineManager::CreateShineArea()
{
    mstSheineTriangles.clear();

    // 光領域をリセット
    for (int y = 0; y < MAP_ARRAY_SIZE_Y; ++y)
    {
        for (int x = 0; x < MAP_ARRAY_SIZE_X; ++x)
        {
            mstMapObjectGridData[y][x].LitFlag = false;
        }
    }

    // 光源の位置を設定
    mstShinePos = mpShineObject->GetPosition();

    // 光源が存在するグリッド
    mstShineGridPos = Vector2_Int(static_cast<int>(mstShinePos.x / ONE_GRID_SIZE_X), static_cast<int>(mstShinePos.y / ONE_GRID_SIZE_Y));

    // マップ外なら処理しない
    if (IsOutsideShineStage(mstShineGridPos))
    {
        return;
    }

#ifdef _DEBUG
        std::string debugTextStart = "PREREQUISITES\n\n";
        debugTextStart += std::to_string(mpShineObject->GetShineDirection().leftAngle) + ".leftAngle " + std::to_string(mpShineObject->GetShineDirection().angle) + ".angle " + std::to_string(mpShineObject->GetShineDirection().rightAngle) + ".rightAngle ";

        debugTextStart += std::to_string(mstShineGridPos.x) + ".xPos " + std::to_string(mstShineGridPos.y) + ".yPos ";
        DEBUG::SaveText(debugTextStart + "\n\nSTART\n\n", DEBUG::DEBUG_MAP_TYPE::DEBUG_SHINE_POS);
#endif

    // 調査するグリッド
    std::queue<Vector2_Int> nextCheckShinePos;

    // 光源のグリッドから開始
    nextCheckShinePos.push(mstShineGridPos);

    // グリッドの探索
    CheckShineGrid();
}


// グリッドの探索
void ShineManager::CheckShineGrid()
{
    // 調査するグリッド
    std::queue<Vector2_Int> nextCheckShinePos;

    // 光源のグリッドから開始
    nextCheckShinePos.push(Vector2_Int(static_cast<int>(mstShinePos.x / ONE_GRID_SIZE_X), static_cast<int>(mstShinePos.y / ONE_GRID_SIZE_Y)));
    
    // 光源のグリッドは必ず光領域に含める
    mstMapObjectGridData[mstShineGridPos.y][mstShineGridPos.x].LitFlag = true;

    // ループを数える
    int loopCount = 0;
    mstMapObjectGridData[mstShineGridPos.y][mstShineGridPos.x].LitLoopNumber = 0;

    // 設定したライトの順番を設定する
    int setLitNumber = 0;
    mstMapObjectGridData[mstShineGridPos.y][mstShineGridPos.x].SetLitNumber = 0;

    std::vector<SHINE_DIRECTION> shineDirections;
    SHINE_DIRECTION test;
    /**/shineDirections.push_back(mpShineObject->GetShineDirection());
    /*/
    {
        test = mpShineObject->GetShineDirection();
        test.rightAngle = test.angle;
        test.angle = test.leftAngle * 0.5f;
    // 視界の左端ベクトル
    test.shineDirectionLeft =
    {
        std::cos(test.leftAngle),
        std::sin(test.leftAngle)
    };
    // 視界の右端ベクトル
    test.shineDirectionRight =
    {
        std::cos(test.rightAngle),
        std::sin(test.rightAngle)
    };
    }
    shineDirections.push_back(test);
    {
        test = mpShineObject->GetShineDirection();
        test.leftAngle = test.angle;
        test.angle = test.rightAngle * 0.5f;
    // 視界の左端ベクトル
    test.shineDirectionLeft =
    {
        std::cos(test.leftAngle),
        std::sin(test.leftAngle)
    };
    // 視界の右端ベクトル
    test.shineDirectionRight =
    {
        std::cos(test.rightAngle),
        std::sin(test.rightAngle)
    };
    }
    shineDirections.push_back(test);//*/

    // 光のエリアを記録する6
    mstShineAreaResult.clear();
    mstShineAreaResult.push_back(shineDirections);

    while (!nextCheckShinePos.empty())
    {
#ifdef _DEBUG
        std::string debugTextData;
        std::queue<Vector2_Int> debugCheckShinePoss = nextCheckShinePos;
        while (0 < debugCheckShinePoss.size())
        {
            Vector2_Int  debugCheckShinePos = debugCheckShinePoss.front();
            debugCheckShinePoss.pop();
            debugTextData += std::to_string(debugCheckShinePos.x) + ".x " + std::to_string(debugCheckShinePos.y) + ".y; ";
        }
        debugTextData += "\n\n";
        DEBUG::SaveText(debugTextData, DEBUG::DEBUG_MAP_TYPE::DEBUG_SHINE_POS);
#endif
        // フラグデータ初期化
        mstCheckShineGridFlags.Init();

        // 今回調べるグリッドを取り出す
        std::queue<Vector2_Int> nowCheckShinePos;
        nowCheckShinePos.swap(nextCheckShinePos);

        // 今回の探索中に見つかった障害物
        std::stack<BLOCK_POS_DATA> blockPoss;
        
        // 指している光の配列数
        int shineDirectionsIndex = 0;

        // ループカウントを加算する
        ++loopCount;
        
        // 光源から見て左側の光領域から順番に処理する
        while ((shineDirectionsIndex < static_cast<int>(shineDirections.size())) &&
                (0 < nowCheckShinePos.size()))
        {
            Vector2_Int checkShinePos = nowCheckShinePos.front();
            if (!mstMapObjectGridData[checkShinePos.y][checkShinePos.x].LitFlag)
            {
                nowCheckShinePos.pop();
                continue;
            }
            std::vector<Vector2_Int> ShineGridPositions = GetShineGridPositions(checkShinePos);

            // 現在の光領域を左端から右端へ走査
            for (const Vector2_Int& checkPos : ShineGridPositions)
            {
                // マップ外なら除外
                if (IsOutsideShineStage(checkPos))
                {
                    // ここで光を遮るものを追加
                    BLOCK_POS_DATA blockPos;
                    blockPos.OutsideGridFlag = true;
                    blockPos.BlockPos = checkPos;
                    blockPos.ArrayIndex = shineDirectionsIndex;
                    blockPoss.push(blockPos);
                    continue;
                }

                // すでに光が届いているなら除外
                // TODO:_ 多分届いても複数考えられる場合は戻らない気がする
                if (mstMapObjectGridData[checkPos.y][checkPos.x].LitFlag)
                {
                    continue;
                }

                // グリッドの判定
                SHINE_GRID_TYPE shineGridResult = JudgeGrid(checkPos, shineDirections, shineDirectionsIndex);

                // グリッドの状況によって処理
                switch (shineGridResult)
                {
                // 光領域外なため次を調べる
                case SHINE_GRID_TYPE::NOT_SHINE_GRID:
                {
                    // 次の光領域を調べる対象にするフラグ設定
                    mstCheckShineGridFlags.SetFlag(true, CHECK_SHINE_GRID_FLAGS::NAXT_SHINE_AREA);
                    break;
                }
                // 光領域内で他に情報がない
                case SHINE_GRID_TYPE::SHINE_GRID:
                {
                    // 光領域として登録されていなければ調べるグリッドとして追加
                    if (!mstMapObjectGridData[checkPos.y][checkPos.x].LitFlag)
                    {
                        // 次に調べるグリッドへ追加
                        nextCheckShinePos.push(checkPos);
                    }
                    // 光範囲内として登録
                    mstMapObjectGridData[checkPos.y][checkPos.x].LitFlag = true;
                    mstMapObjectGridData[checkPos.y][checkPos.x].LitLoopNumber = loopCount;
                    ++setLitNumber;
                    mstMapObjectGridData[checkPos.y][checkPos.x].SetLitNumber = setLitNumber;
                    break;
                }
                case SHINE_GRID_TYPE::SHINE_AND_OBJECT_GRID:
                {
                    // ここで光を遮るものを追加
                    BLOCK_POS_DATA blockPos;
                    blockPos.OutsideGridFlag = false;
                    blockPos.BlockPos = checkPos;
                    blockPos.ArrayIndex = shineDirectionsIndex;
                    blockPoss.push(blockPos);

                    // 光領域として登録されていなければ調べるグリッドとして追加
                    if (!mstMapObjectGridData[checkPos.y][checkPos.x].LitFlag)
                    {
                        // 次に調べるグリッドへ追加
                        nextCheckShinePos.push(checkPos);
                    }
                    // 光範囲内として登録
                    mstMapObjectGridData[checkPos.y][checkPos.x].LitFlag = true;
                    mstMapObjectGridData[checkPos.y][checkPos.x].LitLoopNumber = loopCount;
                    ++setLitNumber;
                    mstMapObjectGridData[checkPos.y][checkPos.x].SetLitNumber = setLitNumber;
                    break;
                }
                case SHINE_GRID_TYPE::SHINE_AND_OTHER_SHINE_AREA_GRID:
                {
                    // 光領域として登録されていなければ調べるグリッドとして追加
                    if (!mstMapObjectGridData[checkPos.y][checkPos.x].LitFlag)
                    {
                        // 次に調べるグリッドへ追加
                        nextCheckShinePos.push(checkPos);
                    }
                    // 光範囲内として登録
                    mstMapObjectGridData[checkPos.y][checkPos.x].LitFlag = true;
                    mstMapObjectGridData[checkPos.y][checkPos.x].LitLoopNumber = loopCount;
                    ++setLitNumber;
                    mstMapObjectGridData[checkPos.y][checkPos.x].SetLitNumber = setLitNumber;

                    // 次の光領域を調べる対象にするフラグ設定
                    mstCheckShineGridFlags.SetFlag(true, CHECK_SHINE_GRID_FLAGS::NAXT_SHINE_AREA);
                    break;;
                }
                case SHINE_GRID_TYPE::SHINE_AND_OBJECT_AND_OTHER_SHINE_AREA_GRID:
                {
                    // ここで光を遮るものを追加
                    BLOCK_POS_DATA blockPos;
                    blockPos.OutsideGridFlag = false;
                    blockPos.BlockPos = checkPos;
                    blockPos.ArrayIndex = shineDirectionsIndex;
                    blockPoss.push(blockPos);

                    // 光領域として登録されていなければ調べるグリッドとして追加
                    if (!mstMapObjectGridData[checkPos.y][checkPos.x].LitFlag)
                    {
                        // 次に調べるグリッドへ追加
                        nextCheckShinePos.push(checkPos);
                    }
                    // 光範囲内として登録
                    mstMapObjectGridData[checkPos.y][checkPos.x].LitFlag = true;
                    mstMapObjectGridData[checkPos.y][checkPos.x].LitLoopNumber = loopCount;
                    ++setLitNumber;
                    mstMapObjectGridData[checkPos.y][checkPos.x].SetLitNumber = setLitNumber;

                    // 次の光領域を調べる対象にするフラグ設定
                    mstCheckShineGridFlags.SetFlag(true, CHECK_SHINE_GRID_FLAGS::NAXT_SHINE_AREA);
                    break;;
                }
                }
                if (mstCheckShineGridFlags.GetFlag_BitShift(CHECK_SHINE_GRID_FLAGS::NAXT_SHINE_AREA))
                {
                    break;
                }
            }
        
            if (mstCheckShineGridFlags.GetFlag_BitShift(CHECK_SHINE_GRID_FLAGS::NAXT_SHINE_AREA))
            {
                shineDirectionsIndex++;
                continue;
            }
            nowCheckShinePos.pop();
        }

        if (shineDirectionsIndex >= static_cast<int>(shineDirections.size()))
        {
#ifndef _DEBUG
#endif
        }

        // 光を遮る物の処理
        ShineBlockProcess(blockPoss, nextCheckShinePos, shineDirections);

        // 光領域を記録
        mstShineAreaResult.push_back(shineDirections);
    }

    
#ifdef _DEBUG
        DEBUG::SaveText("END\n\n", DEBUG::DEBUG_MAP_TYPE::DEBUG_SHINE_POS);
#endif
}

// グリッドが光範囲内か判定
SHINE_GRID_TYPE ShineManager::JudgeGrid(const Vector2_Int& gridPos, const std::vector<SHINE_DIRECTION>& shineDirections, int shineDirectionsIndex)
{
    // 光の方向
    SHINE_DIRECTION shineDirection = shineDirections[shineDirectionsIndex];

    Vector2 direction1 = shineDirection.shineDirectionLeft;

    Vector2 direction2 = shineDirection.shineDirectionRight;

    // 2本の方向ベクトルの外積
    const float directionCross =
        direction1.x * direction2.y -
        direction1.y * direction2.x;

    // グリッドの四隅の座標
    const float left =
        gridPos.x * ONE_GRID_SIZE_X;

    const float right =
        left + ONE_GRID_SIZE_X;

    const float top =
        gridPos.y * ONE_GRID_SIZE_Y;

    const float bottom =
        top + ONE_GRID_SIZE_Y;

    const Vector2 gridCorners[4] =
    {
        Vector2(left,  top),
        Vector2(right, top),
        Vector2(left,  bottom),
        Vector2(right, bottom)
    };

    // 四隅のいずれかが光範囲内か判定
    for (const Vector2& corner : gridCorners)
    {
        // 光源からグリッドの角への方向
        Vector2 toCorner = corner - mstShinePos;

        // 光源と角が同じ位置なら光範囲内
        if (toCorner.x == 0.0f &&
            toCorner.y == 0.0f)
        {
            if (mstMapObjectGridData[gridPos.y][gridPos.x].LinePoss.size() > 0)
            {
                return SHINE_GRID_TYPE::SHINE_AND_OBJECT_GRID;
            }
            return SHINE_GRID_TYPE::SHINE_GRID;
        }

        // 1本目の方向との外積
        const float cross1 =
            direction1.x * toCorner.y -
            direction1.y * toCorner.x;

        // 2本目の方向との外積
        const float cross2 =
            direction2.x * toCorner.y -
            direction2.y * toCorner.x;

        bool isShineArea = false;

        // 2本の方向ベクトルの間にあるか判定
        if (directionCross < 0.0f)
        {
            // 時計回り
            isShineArea =
                cross1 <= 0.0f &&
                cross2 >= 0.0f;
        }
        else
        {
            // 反時計回り
            isShineArea =
                cross1 >= 0.0f &&
                cross2 <= 0.0f;
        }

        // 光範囲内
        if (isShineArea)
        {
            if (mstMapObjectGridData[gridPos.y][gridPos.x].LinePoss.size() > 0)
            {
                return SHINE_GRID_TYPE::SHINE_AND_OBJECT_GRID;
            }
            return SHINE_GRID_TYPE::SHINE_GRID;
        }
    }

    // 光範囲外
    return SHINE_GRID_TYPE::NOT_SHINE_GRID;
}

// // // グ光を遮るものを確認し、それに応じた処理を行う
// // void ShineManager::LightBlockProcess(std::stack<BLOCK_POS_DATA>& blockPoss, std::queue<Vector2_Int>& nextCheckShinePos, std::vector<SHINE_DIRECTION>& shineDirections)
// // {
// //     // 遮っている場所探す
// //     while (blockPoss.size())
// //     {
// //         BLOCK_POS_DATA blockPos = blockPoss.top();
// //         blockPoss.pop();

// //         // 光を遮る位置にオブジェクトがあるなら三角頂点入力
// //         if (blockPos.OutsideGridFlag)
// //         {
// //         }
// //         else
// //         {
// //         }
// //     }
// // }
// // 光を遮るものを確認し、それに応じた処理を行う
// void ShineManager::LightBlockProcess(std::stack<BLOCK_POS_DATA>& blockPoss, std::queue<Vector2_Int>& nextCheckShinePos, std::vector<SHINE_DIRECTION>& shineDirections)
// {

//     // 光源の位置
//     const Vector2 shinePos = mpShineObject->GetPosition();
    
//     // 遮っている場所を探す
//     while (!blockPoss.empty())
//     {
//         BLOCK_POS_DATA blockPos = blockPoss.top();
//         blockPoss.pop();

//         // 現在の光方向を取得
//         const SHINE_DIRECTION& shineDirection =
//             shineDirections[blockPos.ArrayIndex];

//         // グリッドの範囲
//         const float left =
//             blockPos.BlockPos.x * ONE_GRID_SIZE_X;

//         const float right =
//             left + ONE_GRID_SIZE_X;

//         const float top =
//             blockPos.BlockPos.y * ONE_GRID_SIZE_Y;

//         const float bottom =
//             top + ONE_GRID_SIZE_Y;

//         // 光源から各方向へ伸ばした線と
//         // グリッドの辺との交点を求める
//         Vector2 intersection1;
//         Vector2 intersection2;

//         auto GetIntersection =
//             [&](const Vector2& direction, Vector2& intersection) -> bool
//         {
//             float nearestT = FLT_MAX;
//             bool found = false;

//             // 左辺・右辺・上辺・下辺
//             const Vector2 edgeStart[4] =
//             {
//                 Vector2(left,  top),
//                 Vector2(right, top),
//                 Vector2(left,  top),
//                 Vector2(left,  bottom)
//             };

//             const Vector2 edgeEnd[4] =
//             {
//                 Vector2(left,  bottom),
//                 Vector2(right, bottom),
//                 Vector2(right, top),
//                 Vector2(right, bottom)
//             };

//             for (int i = 0; i < 4; ++i)
//             {
//                 const Vector2 edge = edgeEnd[i] - edgeStart[i];

//                 const float cross =
//                     direction.x * edge.y -
//                     direction.y * edge.x;

//                 // 平行なら交わらない
//                 if (cross == 0.0f)
//                 {
//                     continue;
//                 }

//                 const Vector2 toEdge =
//                     edgeStart[i] - shinePos;

//                 const float t =
//                     (toEdge.x * edge.y -
//                      toEdge.y * edge.x) / cross;

//                 const float u =
//                     (toEdge.x * direction.y -
//                      toEdge.y * direction.x) / cross;

//                 // 光源から前方にあり、
//                 // 辺の範囲内にある交点だけを使用
//                 if (t < 0.0f ||
//                     u < 0.0f ||
//                     u > 1.0f)
//                 {
//                     continue;
//                 }

//                 // 最も光源に近い交点を取得
//                 if (t < nearestT)
//                 {
//                     nearestT = t;

//                     intersection =
//                         shinePos + direction * t;

//                     found = true;
//                 }
//             }

//             return found;
//         };

//         // 光を遮る位置にオブジェクトがあるなら三角頂点入力
//         if (blockPos.OutsideGridFlag)
//         {
//             // マップ外の場合
//             // TODO: マップ端との交点を求める
//         }
//         else
//         {
//             // 1本目の光境界との交点
//             const bool found1 =
//                 GetIntersection(
//                     shineDirection.shineDirection1,
//                     intersection1);

//             // 2本目の光境界との交点
//             const bool found2 =
//                 GetIntersection(
//                     shineDirection.shineDirection2,
//                     intersection2);

//             if (found1 && found2)
//             {
//                 // 遮蔽物によってできる光領域の三角形
//                 SHINE_TRIANGLE shineTriangle;

//                 shineTriangle.Vertex1 =
//                     Vector2_Int(
//                         static_cast<int>(shinePos.x),
//                         static_cast<int>(shinePos.y));

//                 shineTriangle.Vertex2 =
//                     Vector2_Int(
//                         static_cast<int>(intersection1.x),
//                         static_cast<int>(intersection1.y));

//                 shineTriangle.Vertex3 =
//                     Vector2_Int(
//                         static_cast<int>(intersection2.x),
//                         static_cast<int>(intersection2.y));

//                 mstSheineTriangles.push_back(shineTriangle);
//             }
//         }
//     }
// }

bool IsAngleBetween(float targetAngle, float leftAngle, float rightAngle);

// 光を遮るものを確認し、それに応じた処理を行う
void ShineManager::ShineBlockProcess(std::stack<BLOCK_POS_DATA>& blockPoss, std::queue<Vector2_Int>& nextCheckShinePos, std::vector<SHINE_DIRECTION>& shineDirections)
{
    // 遮っている場所を探す
    while (!blockPoss.empty())
    {
        BLOCK_POS_DATA blockPos = blockPoss.top();
        blockPoss.pop();

        // 画面外
        if (blockPos.OutsideGridFlag)
        {
            // 現在の光方向を取得
            const SHINE_DIRECTION& shineDirection =
                shineDirections[blockPos.ArrayIndex];

            // X・Yの両方が範囲外なら判定しない
            const bool outsideX =
                blockPos.BlockPos.x < 0 ||
                blockPos.BlockPos.x >= MAP_ARRAY_SIZE_X;

            const bool outsideY =
                blockPos.BlockPos.y < 0 ||
                blockPos.BlockPos.y >= MAP_ARRAY_SIZE_Y;

            if (outsideX && outsideY)
            {
                continue;
            }

            // 画面端の2点
            Vector2 edgePos1;
            Vector2 edgePos2;

            // TODO:_角追加白
            // 左端
            if (blockPos.BlockPos.x < 0)
            {
                edgePos1 = Vector2(0.0f, 0.0f);
                edgePos2 = Vector2(0.0f, static_cast<float>(MAP_SIZE_Y));
            }
            // 右端
            else if (blockPos.BlockPos.x >= MAP_ARRAY_SIZE_X)
            {
                edgePos1 = Vector2(static_cast<float>(MAP_SIZE_X), 0.0f);

                edgePos2 = Vector2(static_cast<float>(MAP_SIZE_X), static_cast<float>(MAP_SIZE_Y));
            }
            // 上端
            else if (blockPos.BlockPos.y < 0)
            {
                edgePos1 = Vector2(0.0f, 0.0f);
                edgePos2 = Vector2(static_cast<float>(MAP_SIZE_X), 0.0f);
            }
            // 下端
            else
            {
                edgePos1 = Vector2(0.0f, static_cast<float>(MAP_SIZE_Y));

                edgePos2 = Vector2(static_cast<float>(MAP_SIZE_X), static_cast<float>(MAP_SIZE_Y));
            }

            const Vector2 edge =
                edgePos2 - edgePos1;

            Vector2 intersection1;
            Vector2 intersection2;

            // 光方向1との交点
            const float cross1 =
                shineDirection.shineDirectionLeft.x * edge.y -
                shineDirection.shineDirectionLeft.y * edge.x;

            if (cross1 != 0.0f)
            {
                const Vector2 toEdge =
                    edgePos1 - mstShinePos;

                const float t =
                    (toEdge.x * edge.y -
                     toEdge.y * edge.x) / cross1;

                intersection1 =
                    mstShinePos +
                    shineDirection.shineDirectionLeft * t;
            }

            // 光方向2との交点
            const float cross2 =
                shineDirection.shineDirectionRight.x * edge.y -
                shineDirection.shineDirectionRight.y * edge.x;

            if (cross2 != 0.0f)
            {
                const Vector2 toEdge =
                    edgePos1 - mstShinePos;

                const float t =
                    (toEdge.x * edge.y -
                     toEdge.y * edge.x) / cross2;

                intersection2 =
                    mstShinePos +
                    shineDirection.shineDirectionRight * t;
            }

            {
                // グリッド内に補正
                AdjustPositionToGrid(blockPos.BlockPos, intersection1);
                AdjustPositionToGrid(blockPos.BlockPos, intersection2);
                // {// intersection1
                //     if (intersection1.x < ((blockPos.BlockPos.x) * ONE_GRID_SIZE_X))
                //     {
                //         intersection1.x = (blockPos.BlockPos.x * ONE_GRID_SIZE_X);
                //     }
                //     else if (intersection1.x > ((blockPos.BlockPos.x + 1) * ONE_GRID_SIZE_X))
                //     {
                //         intersection1.x = ((blockPos.BlockPos.x + 1) * ONE_GRID_SIZE_X);
                //     }
                    
                //     if (intersection1.y < (blockPos.BlockPos.y * ONE_GRID_SIZE_Y))
                //     {
                //         intersection1.y = (blockPos.BlockPos.y * ONE_GRID_SIZE_Y);
                //     }
                //     else if (intersection1.y > ((blockPos.BlockPos.y + 1) * ONE_GRID_SIZE_Y))
                //     {
                //         intersection1.y = ((blockPos.BlockPos.y + 1) * ONE_GRID_SIZE_Y);
                //     }
                // }
                // {// intersection2
                //     if (intersection2.x < (blockPos.BlockPos.x * ONE_GRID_SIZE_X))
                //     {
                //         intersection2.x = (blockPos.BlockPos.x * ONE_GRID_SIZE_X);
                //     }
                //     else if (intersection2.x > ((blockPos.BlockPos.x + 1) * ONE_GRID_SIZE_X))
                //     {
                //         intersection2.x = ((blockPos.BlockPos.x + 1) * ONE_GRID_SIZE_X);
                //     }
                    
                //     if (intersection2.y < (blockPos.BlockPos.y * ONE_GRID_SIZE_Y))
                //     {
                //         intersection2.y = (blockPos.BlockPos.y * ONE_GRID_SIZE_Y);
                //     }
                //     else if (intersection2.y > ((blockPos.BlockPos.y + 1) * ONE_GRID_SIZE_Y))
                //     {
                //         intersection2.y = ((blockPos.BlockPos.y + 1) * ONE_GRID_SIZE_Y);
                //     }
                // }
            }

            LINE_POS checkLine = {intersection1, intersection2};
            if (ShineBlockingProcess(checkLine, blockPos, shineDirections) != 0x2)
            {
                continue;
            }

            // // 光源と画面端との交点2つで三角形を作成
            // SHINE_TRIANGLE shineTriangle;

            // shineTriangle.Vertex1 =
            // {
            //     static_cast<int>(mstShinePos.x),
            //     static_cast<int>(mstShinePos.y)
            // };

            // shineTriangle.Vertex2 =
            // {
            //     static_cast<int>(intersection1.x),
            //     static_cast<int>(intersection1.y)
            // };

            // shineTriangle.Vertex3 =
            // {
            //     static_cast<int>(intersection2.x),
            //     static_cast<int>(intersection2.y)
            // };

            // mstSheineTriangles.push_back(shineTriangle);
        }
        else
        {
            std::vector<LINE_POS> linePoss = mstMapObjectGridData[blockPos.BlockPos.y][blockPos.BlockPos.x].LinePoss;
            std::sort(linePoss.begin(), linePoss.end(),
                    [this](const LINE_POS& a, const LINE_POS& b)
                    {
                        // --- 1. 光の左端 (leftAngle) を基準とした時計回り相対角度を計算 ---
                        const float leftAngle = mpShineObject->GetShineDirection().leftAngle;

                        // leftAngle を 0 とした時計回り方向への相対角度 (0 ～ 2π) を算出するヘルパー関数
                        auto GetClockwiseAngleFromLeft = [](float angle, float baseLeft) {
                            static constexpr float TWO_PI = 6.28318530717958647692f;
                            float diff = std::fmod(angle - baseLeft, TWO_PI);
                            if (diff < 0.0f) diff += TWO_PI;
                            return diff; // 0＝左端、値が大きいほど右側
                        };

                        // a の 2 点のアングル (光源からの相対角度)
                        const float aAngle1 = GetClockwiseAngleFromLeft(
                            std::atan2f(a.linePos1.y - mstShinePos.y, a.linePos1.x - mstShinePos.x), leftAngle);
                        const float aAngle2 = GetClockwiseAngleFromLeft(
                            std::atan2f(a.linePos2.y - mstShinePos.y, a.linePos2.x - mstShinePos.x), leftAngle);

                        // b の 2 点のアングル (光源からの相対角度)
                        const float bAngle1 = GetClockwiseAngleFromLeft(
                            std::atan2f(b.linePos1.y - mstShinePos.y, b.linePos1.x - mstShinePos.x), leftAngle);
                        const float bAngle2 = GetClockwiseAngleFromLeft(
                            std::atan2f(b.linePos2.y - mstShinePos.y, b.linePos2.x - mstShinePos.x), leftAngle);

                        // 各線分の右端アングル (角度が大きいほど右側)
                        const float aMaxAngle = max(aAngle1, aAngle2);
                        const float bMaxAngle = max(bAngle1, bAngle2);

                        // 【優先順位 1】座標をアングル化して右にあるものを優先（浮動小数点数の誤差吸収用イプシロン付き）
                        constexpr float EPSILON_ANGLE = 0.0001f;
                        if (std::abs(aMaxAngle - bMaxAngle) > EPSILON_ANGLE)
                        {
                            return aMaxAngle > bMaxAngle; // 右にある方（アングルが大きい方）を前に配置
                        }

                        // --- 2 & 3. 距離による比較処理（アングルが同じ場合のみ実行） ---
                        auto GetDistanceSquared = [this](const Vector2& pos)
                        {
                            const float x = pos.x - mstShinePos.x;
                            const float y = pos.y - mstShinePos.y;
                            return x * x + y * y;
                        };

                        const float aDistance1 = GetDistanceSquared(a.linePos1);
                        const float aDistance2 = GetDistanceSquared(a.linePos2);
                        const float bDistance1 = GetDistanceSquared(b.linePos1);
                        const float bDistance2 = GetDistanceSquared(b.linePos2);

                        // 【優先順位 2】座標を見て光に近い頂点がある方
                        const float aNear = min(aDistance1, aDistance2);
                        const float bNear = min(bDistance1, bDistance2);

                        const int aNearInt = static_cast<int>(aNear);
                        const int bNearInt = static_cast<int>(bNear);

                        if (aNearInt != bNearInt)
                        {
                            return aNearInt < bNearInt;
                        }

                        // 【優先順位 3】近い方が同じなら、遠い方を見て近い方
                        const float aFar = max(aDistance1, aDistance2);
                        const float bFar = max(bDistance1, bDistance2);

                        const int aFarInt = static_cast<int>(aFar);
                        const int bFarInt = static_cast<int>(bFar);

                        return aFarInt < bFarInt;
                    });

            for (LINE_POS checkLine :  linePoss)
            {
                int debugVariable = ShineBlockingProcess(checkLine, blockPos, shineDirections);
            }

            // -------------------------------------------------------------------
            // 遮蔽処理後、光領域が該当グリッド内に残っているか判定して queue に追加
            // -------------------------------------------------------------------
            bool isStillLit = false;

            // 四隅の頂点座標を算出
            const float gridLeft   = static_cast<float>(blockPos.BlockPos.x * ONE_GRID_SIZE_X);
            const float gridRight  = gridLeft + static_cast<float>(ONE_GRID_SIZE_X);
            const float gridTop    = static_cast<float>(blockPos.BlockPos.y * ONE_GRID_SIZE_Y);
            const float gridBottom = gridTop + static_cast<float>(ONE_GRID_SIZE_Y);

            const Vector2 corners[4] = {
                { gridLeft,  gridTop },
                { gridRight, gridTop },
                { gridLeft,  gridBottom },
                { gridRight, gridBottom }
            };

            // 分割・調整されたすべての光方向データ（shineDirections）に対して判定
            for (const SHINE_DIRECTION& shineDir : shineDirections)
            {
                for (const Vector2& corner : corners)
                {
                    const Vector2 dirToCorner = {
                        corner.x - mstShinePos.x,
                        corner.y - mstShinePos.y
                    };

                    const float cornerAngle = std::atan2f(dirToCorner.y, dirToCorner.x);

                    // 頂点が残っている光の照射領域内（leftAngle ～ rightAngle）に入っているか
                    if (IsAngleBetween(cornerAngle, shineDir.leftAngle, shineDir.rightAngle))
                    {
                        isStillLit = true;
                        break;
                    }
                }

                if (isStillLit) break;
            }

            // 光領域が残っている場合はフラグを更新して次の探索キューに追加
            if (!isStillLit && mstMapObjectGridData[blockPos.BlockPos.y][blockPos.BlockPos.x].LitFlag)
            {
                mstMapObjectGridData[blockPos.BlockPos.y][blockPos.BlockPos.x].LitFlag = false;
            }
        }
    }
}

// leftAngle（光の左端）を基準「0.0」とした時計回り方向への相対角度（0 ～ 2π）を算出する
static float GetClockwiseAngleFromLeft(float angle, float baseLeft)
{
    static constexpr float TWO_PI = 6.28318530717958647692f;
    float diff = std::fmod(angle - baseLeft, TWO_PI);
    if (diff < 0.0f) diff += TWO_PI;
    return diff;
}

// 光を遮る物の影響を与える処理
int ShineManager::ShineBlockingProcess(LINE_POS bloakLinePos, const BLOCK_POS_DATA& bloakPoss, std::vector<SHINE_DIRECTION>& shineDirections)
{
    // 対象の光方向データを参照取得
    SHINE_DIRECTION& currentShineDir = shineDirections[bloakPoss.ArrayIndex];

    const Vector2 shinePos = mpShineObject->GetPosition();
    const float leftAngle  = currentShineDir.leftAngle;   // 光の左端角度 (ラジアン)
    const float rightAngle = currentShineDir.rightAngle;  // 光の右端角度 (ラジアン)

    // 1. 光源から障害物の2点（StartPos / EndPos）への絶対角度（-π ～ +π）を算出
    Vector2 dirStart = { bloakLinePos.linePos1.x - shinePos.x, bloakLinePos.linePos1.y - shinePos.y };
    Vector2 dirEnd   = { bloakLinePos.linePos2.x - shinePos.x,   bloakLinePos.linePos2.y - shinePos.y };

    float startAngle = std::atan2f(dirStart.y, dirStart.x);
    float endAngle   = std::atan2f(dirEnd.y,   dirEnd.x);

    // 2. 光の左端 (leftAngle) を 0 とした「相対角度」に変換 (0 ～ 2π)
    float startRel = GetClockwiseAngleFromLeft(startAngle, leftAngle);
    float endRel   = GetClockwiseAngleFromLeft(endAngle, leftAngle);

    // 光全体の照射範囲の幅 (0 ～ 2π)
    float totalShineWidth = GetClockwiseAngleFromLeft(rightAngle, leftAngle);

    // 障害物の2点のうち、時計回り順で「より左側（数値が小さい方）」と「より右側（数値が大きい方）」を整理
    float blockLeftRel   = (startRel < endRel ? startRel : endRel);
    float blockRightRel  = (startRel > endRel ? startRel : endRel);
    
    float blockLeftAngle  = (startRel < endRel) ? startAngle : endAngle;
    float blockRightAngle = (startRel < endRel) ? endAngle   : startAngle;

    // -------------------------------------------------------------------
    // 判定 1: 遮っているか判定
    // -------------------------------------------------------------------
    // 障害物の2点ともが光の範囲外（右側外側）にあり、かつ光をまたぎ越していない場合
    if (blockLeftRel > totalShineWidth && blockRightRel > totalShineWidth)
    {
        // 障害物の角度幅自体も光にかかっていない場合、完全に光の外側なので終了
        // ※「障害物の開き角度」が光の裏側や範囲外にあるケースの除外
        if (blockRightRel - blockLeftRel < 3.14159265f) 
        {
            return 0x1; // 何もしないで終了
        }
    }

    // -------------------------------------------------------------------
    // 判定 2: 左右の端（光の左境界・右境界）のどちらかを遮っているか
    // -------------------------------------------------------------------
    // 左境界 (0.0) を障害物が跨いでいるか（＝左端を遮っているか）
    // （障害物の左端は照射範囲外で、右端は照射範囲内にある状態）
    bool crossesLeftEdge  = (blockLeftRel > totalShineWidth && blockRightRel <= totalShineWidth);

    // 右境界 (totalShineWidth) を障害物が跨いでいるか（＝右端を遮っているか）
    // （障害物の右端が照射範囲の外側へ飛び出している状態）
    bool crossesRightEdge = (blockRightRel > totalShineWidth);

    // -------------------------------------------------------------------
    // 3パターン分岐処理
    // -------------------------------------------------------------------
    if (crossesLeftEdge || crossesRightEdge)
    {
        // 描画三角追加
        AddDrawTriangleData(bloakLinePos.linePos1, bloakLinePos.linePos2);
        if (crossesLeftEdge && crossesRightEdge)
        {
            // 【パターンA-1】光の左右両端とも跨いで完全に覆い隠している（光の全消滅）
            shineDirections.erase(shineDirections.begin() + bloakPoss.ArrayIndex);
        }
        else if (crossesLeftEdge)
        {
            // 【パターンA-2】左端のみを遮っている（光の左側が削れる）
            // -> 光の左端角度を「障害物の右端角度」に変更
            currentShineDir.leftAngle = blockRightAngle;
            currentShineDir.shineDirectionLeft = { std::cos(blockRightAngle), std::sin(blockRightAngle) };
        }
        else if (crossesRightEdge)
        {
            // 【パターンA-3】右端のみを遮っている（光の右側が削れる）
            // -> 光の右端角度を「障害物の左端角度」に変更
            currentShineDir.rightAngle = blockLeftAngle;
            currentShineDir.shineDirectionRight = { std::cos(blockLeftAngle), std::sin(blockLeftAngle) };
        }

        return 0x2;
    }
    else
    {
        // 描画三角追加
        AddDrawTriangleData(bloakLinePos.linePos1, bloakLinePos.linePos2);

        // ---------------------------------------------------------------
        // 【パターンB】左右の端どちらも遮っていない（光の中に完全にある障害物）
        // ---------------------------------------------------------------
        // 光を2つに分割する

        float origRightAngle = currentShineDir.rightAngle;

        // 1. 元の光（左側）の右端を「障害物の左端角度」に縮める
        currentShineDir.rightAngle = blockLeftAngle;
        currentShineDir.shineDirectionRight = { std::cos(blockLeftAngle), std::sin(blockLeftAngle) };

        // 2. 新しい光（右側）を「障害物の右端角度 ～ 元の右端角度」として作成
        SHINE_DIRECTION newRightShine;
        newRightShine.leftAngle  = blockRightAngle;
        newRightShine.rightAngle = origRightAngle;
        newRightShine.shineDirectionLeft  = { std::cos(blockRightAngle), std::sin(blockRightAngle) };
        newRightShine.shineDirectionRight = { std::cos(origRightAngle),   std::sin(origRightAngle) };

        // 分割した光を追加
        shineDirections.insert(shineDirections.begin() + bloakPoss.ArrayIndex + 1, newRightShine);

        return 0x4;
    }
}

// マップ外判定
bool ShineManager::IsOutsideShineStage(const Vector2_Int& gridPos)
{
    if (gridPos.x < 0 || gridPos.x >= MAP_ARRAY_SIZE_X ||
        gridPos.y < 0 || gridPos.y >= MAP_ARRAY_SIZE_Y)
    {
        return true;
    }

    return false;
}

// // 光領域を左端から右端へ走査するグリッドを取得
// std::vector<Vector2_Int> ShineManager::GetLightGridPositions(const std::queue<Vector2_Int>& nowCheckShinePos)
// {
//     std::vector<Vector2_Int> lightGridPositions;

//     // 光源から見た左方向
//     const Vector2 leftDirection =
//     {
//         -mpShineObject->GetShineDirection().shineDirectionLeft.y,
//          mpShineObject->GetShineDirection().shineDirectionLeft.x
//     };

//     std::queue<Vector2_Int> checkPos = nowCheckShinePos;

//     while (!checkPos.empty())
//     {
//         const Vector2_Int nowPos = checkPos.front();
//         checkPos.pop();

//         for (int y = -1; y <= 1; ++y)
//         {
//             for (int x = -1; x <= 1; ++x)
//             {
//                 if (x == 0 && y == 0)
//                 {
//                     continue;
//                 }

//                 Vector2_Int nextPos =
//                 {
//                     nowPos.x + x,
//                     nowPos.y + y
//                 };

//                 // マップ外でも光ないなら欲しい(マップ外判定は別でやる)
//                 // if (IsOutsideLightStage(nextPos))
//                 // {
//                 //     continue;
//                 // }

//                 bool isAlreadyAdded = false;

//                 for (const Vector2_Int& addedPos : lightGridPositions)
//                 {
//                     if (addedPos.x == nextPos.x &&
//                         addedPos.y == nextPos.y)
//                     {
//                         isAlreadyAdded = true;
//                         break;
//                     }
//                 }

//                 if (!isAlreadyAdded)
//                 {
//                     lightGridPositions.push_back(nextPos);
//                 }
//             }
//         }
//     }

//     // 光源から見て左側から右側へ並べる
//     std::sort(
//         lightGridPositions.begin(),
//         lightGridPositions.end(),
//         [&](const Vector2_Int& lhs, const Vector2_Int& rhs)
//         {
//             const Vector2 lhsPos =
//             {
//                 lhs.x * ONE_GRID_SIZE_X + ONE_GRID_SIZE_X * 0.5f,
//                 lhs.y * ONE_GRID_SIZE_Y + ONE_GRID_SIZE_Y * 0.5f
//             };

//             const Vector2 rhsPos =
//             {
//                 rhs.x * ONE_GRID_SIZE_X + ONE_GRID_SIZE_X * 0.5f,
//                 rhs.y * ONE_GRID_SIZE_Y + ONE_GRID_SIZE_Y * 0.5f
//             };

//             const Vector2 lhsToGrid =
//             {
//                 lhsPos.x - mstShinePos.x,
//                 lhsPos.y - mstShinePos.y
//             };

//             const Vector2 rhsToGrid =
//             {
//                 rhsPos.x - mstShinePos.x,
//                 rhsPos.y - mstShinePos.y
//             };

//             const float lhsValue =
//                 lhsToGrid.x * leftDirection.x +
//                 lhsToGrid.y * leftDirection.y;

//             const float rhsValue =
//                 rhsToGrid.x * leftDirection.x +
//                 rhsToGrid.y * leftDirection.y;

//             return lhsValue > rhsValue;
//         });

//     return lightGridPositions;
// }
// // 光領域を左端から右端へ走査するグリッドを取得
// std::vector<Vector2_Int> ShineManager::GetShineGridPositions(const Vector2_Int& nowCheckShinePos)
// {
//     // 光領域のポジション情報
//     std::vector<Vector2_Int> ShineGridPositions;

//     // 光源から見た左方向
//     const Vector2 leftDirection =
//         mpShineObject->GetShineDirection().shineDirectionLeft;


//     // 光方向のみ取得する
//     for (int y = -1; y <= 1; ++y)
//     {
//         for (int x = -1; x <= 1; ++x)
//         {
//             if (x == 0 && y == 0)
//             {
//                 continue;
//             }

//             Vector2_Int nextPos =
//             {
//                 nowCheckShinePos.x + x,
//                 nowCheckShinePos.y + y
//             };

//             bool isAlreadyAdded = false;

//             for (const Vector2_Int& addedPos : ShineGridPositions)
//             {
//                 if (addedPos.x == nextPos.x &&
//                     addedPos.y == nextPos.y)
//                 {
//                     isAlreadyAdded = true;
//                     break;
//                 }
//             }

//             if (!isAlreadyAdded)
//             {
//                 ShineGridPositions.push_back(nextPos);
//             }
//         }
//     }

//     // 光源から見た角度で左側から右側へ並べる
//     std::sort(
//         ShineGridPositions.begin(),
//         ShineGridPositions.end(),
//         [&](const Vector2_Int& lhs, const Vector2_Int& rhs)
//         {
//             const Vector2 lhsPos =
//             {
//                 lhs.x * ONE_GRID_SIZE_X + ONE_GRID_SIZE_X * 0.5f,
//                 lhs.y * ONE_GRID_SIZE_Y + ONE_GRID_SIZE_Y * 0.5f
//             };

//             const Vector2 rhsPos =
//             {
//                 rhs.x * ONE_GRID_SIZE_X + ONE_GRID_SIZE_X * 0.5f,
//                 rhs.y * ONE_GRID_SIZE_Y + ONE_GRID_SIZE_Y * 0.5f
//             };

//             // 光源からグリッド中心への方向
//             const Vector2 lhsDirection =
//             {
//                 lhsPos.x - mstShinePos.x,
//                 lhsPos.y - mstShinePos.y
//             };

//             const Vector2 rhsDirection =
//             {
//                 rhsPos.x - mstShinePos.x,
//                 rhsPos.y - mstShinePos.y
//             };

//             // 光源から見た角度
//             const float lhsAngle =
//                 std::atan2(-lhsDirection.y, lhsDirection.x);

//             const float rhsAngle =
//                 std::atan2(-rhsDirection.y, rhsDirection.x);

//             return lhsAngle > rhsAngle;
//         });

//     return ShineGridPositions;
// }

// 角度 targetAngle が leftAngle から rightAngle の範囲に含まれるか判定する関数
static bool IsAngleBetween(float targetAngle, float leftAngle, float rightAngle)
{
    static constexpr float TWO_PI = 6.28318530717958647692f;

    auto NormalizeAngle = [](float angle) {
        angle = std::fmod(angle, TWO_PI);
        if (angle < 0.0f) angle += TWO_PI;
        return angle;
    };

    float target = NormalizeAngle(targetAngle);
    float left   = NormalizeAngle(leftAngle);
    float right  = NormalizeAngle(rightAngle);

    if (left <= right)
    {
        return target >= left && target <= right;
    }
    else
    {
        // 0 / 2π の境界を跨ぐ場合
        return target >= left || target <= right;
    }
}

std::vector<Vector2_Int> ShineManager::GetShineGridPositions(const Vector2_Int& nowCheckShinePos)
{
    std::vector<Vector2_Int> shineGridPositions;

    // 光源のワールド位置および照射方向（左右の限界角度）を取得
    const Vector2 shinePos = mpShineObject->GetPosition();
    const SHINE_DIRECTION shineDir = mpShineObject->GetShineDirection();

    // 左右の方向ベクトルから std::atan2f で照射角度（ラジアン: -π?+π）を計算
    const float leftAngle  = std::atan2f(shineDir.shineDirectionLeft.y, shineDir.shineDirectionLeft.x);
    const float rightAngle = std::atan2f(shineDir.shineDirectionRight.y, shineDir.shineDirectionRight.x);

    // 周囲8方向の隣接グリッドを調べる
    for (int y = -1; y <= 1; ++y)
    {
        for (int x = -1; x <= 1; ++x)
        {
            if (x == 0 && y == 0) continue;

            const Vector2_Int nextPos =
            {
                nowCheckShinePos.x + x,
                nowCheckShinePos.y + y
            };

            // グリッドの四隅（左上、右上、左下、右下）の座標を算出
            const float left   = static_cast<float>(nextPos.x * ONE_GRID_SIZE_X);
            const float right  = left + static_cast<float>(ONE_GRID_SIZE_X);
            const float top    = static_cast<float>(nextPos.y * ONE_GRID_SIZE_Y);
            const float bottom = top + static_cast<float>(ONE_GRID_SIZE_Y);

            const Vector2 corners[4] =
            {
                { left,  top },
                { right, top },
                { left,  bottom },
                { right, bottom }
            };

            bool isInsideShine = false;

            // 四隅の頂点のうち、どれか1つでも光の角度範囲内に入っているか確認
            for (const Vector2& corner : corners)
            {
                const Vector2 dirToCorner =
                {
                    corner.x - shinePos.x,
                    corner.y - shinePos.y
                };

                // 頂点への方向角度（ラジアン）
                const float cornerAngle = std::atan2f(dirToCorner.y, dirToCorner.x);

                if (IsAngleBetween(cornerAngle, leftAngle, rightAngle))
                {
                    isInsideShine = true;
                    break; // 1つでも入っていれば対象として判定確定
                }
            }

            // 頂点が照射角度に入っている場合追加
            if (isInsideShine)
            {
                shineGridPositions.push_back(nextPos);
            }
        }
    }

       // --- ソート処理（光の「左端」を基準にして、左から右へ正しく整列させる） ---
    std::sort(
            shineGridPositions.begin(),
            shineGridPositions.end(),
            [&](const Vector2_Int& lhs, const Vector2_Int& rhs)
        {
            // 各グリッドの中心座標
            const Vector2 lhsCenter = {
                lhs.x * ONE_GRID_SIZE_X + ONE_GRID_SIZE_X * 0.5f,
                lhs.y * ONE_GRID_SIZE_Y + ONE_GRID_SIZE_Y * 0.5f
            };
            const Vector2 rhsCenter = {
                rhs.x * ONE_GRID_SIZE_X + ONE_GRID_SIZE_X * 0.5f,
                rhs.y * ONE_GRID_SIZE_Y + ONE_GRID_SIZE_Y * 0.5f
            };

            // 光源からグリッド中心への絶対角度 (ラジアン: -π ～ +π)
            const float lhsAngle = std::atan2f(lhsCenter.y - shinePos.y, lhsCenter.x - shinePos.x);
            const float rhsAngle = std::atan2f(rhsCenter.y - shinePos.y, rhsCenter.x - shinePos.x);

            // 光の左端の方向 (ラジアン)
            const float leftAngle = mpShineObject->GetShineDirection().leftAngle; // ※左端角度を取得

            // 左端角度 (leftAngle) からの相対角度を [-π, +π] の範囲で算出する関数
            // (左端よりわずかに左にあるグリッドが 2π 近くに飛んで末尾に回るのを防ぐ)
            auto GetSignedAngleFromLeft = [](float angle, float baseLeft) {
                static constexpr float TWO_PI = 6.28318530717958647692f;
                static constexpr float PI     = 3.14159265358979323846f;

                float diff = std::fmod(angle - baseLeft, TWO_PI);
                if (diff > PI)  diff -= TWO_PI;
                if (diff < -PI) diff += TWO_PI;
                return diff; // 負の値＝左端よりさらに左、0＝左端ぴったり、正の値＝右方向
            };

            const float lhsDiff = GetSignedAngleFromLeft(lhsAngle, leftAngle);
            const float rhsDiff = GetSignedAngleFromLeft(rhsAngle, leftAngle);

            // 左側（値が小さいもの）から右側（値が大きいもの）へ昇順ソート
            return lhsDiff < rhsDiff;
        });

    return shineGridPositions;
}

// 描画三角追加
void ShineManager::AddDrawTriangleData(Vector2 vertex1, Vector2 vertex2)
{
    SHINE_TRIANGLE shineTriangle;
    shineTriangle.Vertex1 =
    {
        static_cast<int>(mstShinePos.x),
        static_cast<int>(mstShinePos.y)
    };
    shineTriangle.Vertex2 =
    {
        static_cast<int>(vertex1.x),
        static_cast<int>(vertex1.y)
    };
    shineTriangle.Vertex3 =
    {
        static_cast<int>(vertex2.x),
        static_cast<int>(vertex2.y)
    };
    mstSheineTriangles.push_back(shineTriangle);
}