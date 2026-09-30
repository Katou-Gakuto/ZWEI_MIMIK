#include <algorithm>
#include <cmath>
#include <cfloat>
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
    TEST_SHINE_GRID_LOOP_COUNT_INDEX,
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
    TEST_BUTTON_SHINE_GRID_LOOP_COUNT_INDEX,
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
, mstLightAreaEndPoint()
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
            mstMapObjectGridData[y][x].DebugDrawLiteFlag = false;
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

static int GetDebugColor(int index)
{
    constexpr float SATURATION = 1.0f;
    constexpr float VALUE = 1.0f;

    float hue = std::fmod(index * 137.508f, 360.0f);

    float c = VALUE * SATURATION;
    float x = c * (1.0f - std::fabs(
        std::fmod(hue / 60.0f, 2.0f) - 1.0f));

    float m = VALUE - c;

    float r = 0.0f;
    float g = 0.0f;
    float b = 0.0f;

    if (hue < 60.0f)
    {
        r = c;
        g = x;
    }
    else if (hue < 120.0f)
    {
        r = x;
        g = c;
    }
    else if (hue < 180.0f)
    {
        g = c;
        b = x;
    }
    else if (hue < 240.0f)
    {
        g = x;
        b = c;
    }
    else if (hue < 300.0f)
    {
        r = x;
        b = c;
    }
    else
    {
        r = c;
        b = x;
    }

    return GetColor(
        static_cast<int>((r + m) * 255.0f),
        static_cast<int>((g + m) * 255.0f),
        static_cast<int>((b + m) * 255.0f));
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
                            GetDebugColor(mnDrawMode[drawModeIndex]));
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
                    GetDebugColor(mnDrawMode[drawModeIndex]), FALSE
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
                    GetDebugColor(mnDrawMode[drawModeIndex]), TRUE
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
                    GetDebugColor(mnDrawMode[drawModeIndex]), TRUE
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
                    GetDebugColor(mnDrawMode[drawModeIndex])
                );
                DrawLine(drawSingleTriangleData.Vertex1.x, drawSingleTriangleData.Vertex1.y,
                    drawSingleTriangleData.Vertex3.x, drawSingleTriangleData.Vertex3.y,
                    GetDebugColor(mnDrawMode[drawModeIndex])
                );
            }
            break;

        case SHINE_DRAW_MODE::GRID_SHINE_LOOP_COUNT_DRAW_MODE:
            if (mstCheckGridPos.size() <= 0)
            {
                break;
            }
            if (mstCheckGridPos.size() <= testNumber[TEST_INDEX_NUMBERS::TEST_SHINE_GRID_LOOP_COUNT_INDEX])
            {
                testNumber[TEST_INDEX_NUMBERS::TEST_SHINE_GRID_LOOP_COUNT_INDEX] = mstCheckGridPos.size() - 1;
            }
            for (int i = 0; i < mstCheckGridPos[testNumber[TEST_INDEX_NUMBERS::TEST_SHINE_GRID_LOOP_COUNT_INDEX]].size(); ++i)
            {
                DrawBox(ONE_GRID_SIZE_X * mstCheckGridPos[testNumber[TEST_INDEX_NUMBERS::TEST_SHINE_GRID_LOOP_COUNT_INDEX]][i].x,       ONE_GRID_SIZE_Y * mstCheckGridPos[testNumber[TEST_INDEX_NUMBERS::TEST_SHINE_GRID_LOOP_COUNT_INDEX]][i].y,
                        ONE_GRID_SIZE_X * (mstCheckGridPos[testNumber[TEST_INDEX_NUMBERS::TEST_SHINE_GRID_LOOP_COUNT_INDEX]][i].x + 1), ONE_GRID_SIZE_Y * (mstCheckGridPos[testNumber[TEST_INDEX_NUMBERS::TEST_SHINE_GRID_LOOP_COUNT_INDEX]][i].y + 1),
                        GetDebugColor(mnDrawMode[drawModeIndex]),
                        FALSE);
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
                                GetDebugColor(mnDrawMode[drawModeIndex]),
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
                                GetDebugColor(mnDrawMode[drawModeIndex]),
                                FALSE);
                        DrawString(ONE_GRID_SIZE_X * x, ONE_GRID_SIZE_Y * y, std::to_string(mstMapObjectGridData[y][x].LitLoopNumber).c_str(), GetDebugColor(mnDrawMode[drawModeIndex]));
                    }
                }
            }
            break;
        
        case SHINE_DRAW_MODE::GRID_DEBUG_SHINE_LOOP_NUMBER_DRAW_MODE:
            for (int y = 0; y < MAP_ARRAY_SIZE_Y; ++y)
            {
                for (int x = 0; x < MAP_ARRAY_SIZE_X; ++x)
                {
                    if (mstMapObjectGridData[y][x].DebugDrawLiteFlag)
                    {
                        DrawBox(ONE_GRID_SIZE_X * x,       ONE_GRID_SIZE_Y * y,
                                ONE_GRID_SIZE_X * (x + 1), ONE_GRID_SIZE_Y * (y + 1),
                                GetDebugColor(mnDrawMode[drawModeIndex]),
                                FALSE);
                        DrawString(ONE_GRID_SIZE_X * x, ONE_GRID_SIZE_Y * y, std::to_string(mstMapObjectGridData[y][x].LitLoopNumber).c_str(), GetDebugColor(mnDrawMode[drawModeIndex]));
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
                                GetDebugColor(mnDrawMode[drawModeIndex]),
                                FALSE);
                        DrawString(ONE_GRID_SIZE_X * x, ONE_GRID_SIZE_Y * y, std::to_string(mstMapObjectGridData[y][x].SetLitNumber).c_str(), GetDebugColor(mnDrawMode[drawModeIndex]));
                    }
                }
            }
            break;
        
        case SHINE_DRAW_MODE::GRID_DEBUG_SHINE_NUMBER_DRAW_MODE:
            for (int y = 0; y < MAP_ARRAY_SIZE_Y; ++y)
            {
                for (int x = 0; x < MAP_ARRAY_SIZE_X; ++x)
                {
                    if (mstMapObjectGridData[y][x].DebugDrawLiteFlag)
                    {
                        DrawBox(ONE_GRID_SIZE_X * x,       ONE_GRID_SIZE_Y * y,
                                ONE_GRID_SIZE_X * (x + 1), ONE_GRID_SIZE_Y * (y + 1),
                                GetDebugColor(mnDrawMode[drawModeIndex]),
                                FALSE);
                        DrawString(ONE_GRID_SIZE_X * x, ONE_GRID_SIZE_Y * y, std::to_string(mstMapObjectGridData[y][x].SetLitNumber).c_str(), GetDebugColor(mnDrawMode[drawModeIndex]));
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
                                GetDebugColor(mnDrawMode[drawModeIndex]),
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
                    GetDebugColor(mnDrawMode[drawModeIndex]),
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
                GetDebugColor(mnDrawMode[drawModeIndex]),
                TRUE
            );
        }
            break;
        
        case SHINE_DRAW_MODE::TEST_ANGLE_DRAW_MODE:
            DrawTriangle(
                mpShineObject->GetPosition().x, mpShineObject->GetPosition().y,
                mpShineObject->GetPosition().x + (mpShineObject->GetShineDirection().shineDirectionLeft.x * magnification), mpShineObject->GetPosition().y + (mpShineObject->GetShineDirection().shineDirectionLeft.y * magnification),
                mpShineObject->GetPosition().x + (mpShineObject->GetShineDirection().shineDirectionRight.x * magnification), mpShineObject->GetPosition().y + (mpShineObject->GetShineDirection().shineDirectionRight.y * magnification),
                GetDebugColor(mnDrawMode[drawModeIndex]),
                FALSE
            );
            break;
        
        case SHINE_DRAW_MODE::TEST_ANGLE_DRAW_MODE_TRUE:
            DrawTriangle(
                mpShineObject->GetPosition().x, mpShineObject->GetPosition().y,
                mpShineObject->GetPosition().x + (mpShineObject->GetShineDirection().shineDirectionLeft.x * magnification), mpShineObject->GetPosition().y + (mpShineObject->GetShineDirection().shineDirectionLeft.y * magnification),
                mpShineObject->GetPosition().x + (mpShineObject->GetShineDirection().shineDirectionRight.x * magnification), mpShineObject->GetPosition().y + (mpShineObject->GetShineDirection().shineDirectionRight.y * magnification),
                GetDebugColor(mnDrawMode[drawModeIndex]),
                TRUE
            );
            break;
        
        case SHINE_DRAW_MODE::TEST_ANGLE_LEFT_DRAW_MODE:
            DrawLine(
                mpShineObject->GetPosition().x, mpShineObject->GetPosition().y,
                mpShineObject->GetPosition().x + (mpShineObject->GetShineDirection().shineDirectionLeft.x * magnification), mpShineObject->GetPosition().y + (mpShineObject->GetShineDirection().shineDirectionLeft.y * magnification),
                GetDebugColor(mnDrawMode[drawModeIndex]),
                TRUE
            );
            break;
        
        case SHINE_DRAW_MODE::TEST_ANGLE_RIGHT_DRAW_MODE:
            DrawLine(
                mpShineObject->GetPosition().x, mpShineObject->GetPosition().y,
                mpShineObject->GetPosition().x + (mpShineObject->GetShineDirection().shineDirectionRight.x * magnification), mpShineObject->GetPosition().y + (mpShineObject->GetShineDirection().shineDirectionRight.y * magnification),
                GetDebugColor(mnDrawMode[drawModeIndex]),
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
            mstMapObjectGridData[y][x].DebugDrawLiteFlag = false;
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
    mstMapObjectGridData[mstShineGridPos.y][mstShineGridPos.x].DebugDrawLiteFlag = true;

    // ループを数える
    int loopCount = 0;
    mstMapObjectGridData[mstShineGridPos.y][mstShineGridPos.x].LitLoopNumber = 0;

    // 設定したライトの順番を設定する
    int setLitNumber = 0;
    mstMapObjectGridData[mstShineGridPos.y][mstShineGridPos.x].SetLitNumber = 0;

    std::vector<SHINE_DIRECTION> shineDirections;
    shineDirections.push_back(mpShineObject->GetShineDirection());


    // 光のエリアを記録する
    mstShineAreaResult.clear();
    mstShineAreaResult.push_back(shineDirections);

    // 確認するグリッド保存
    mstCheckGridPos.clear();

    while (!nextCheckShinePos.empty())
    {
        {
            std::vector<Vector2_Int> debugNextCheckGrid;
            debugNextCheckGrid.reserve(nextCheckShinePos.size());

            std::string debugTextData;
            
            std::queue<Vector2_Int> debugCheckShinePoss = nextCheckShinePos;
            while (0 < debugCheckShinePoss.size())
            {
                Vector2_Int  debugCheckShinePos = debugCheckShinePoss.front();
                debugCheckShinePoss.pop();
                
                debugNextCheckGrid.push_back(debugCheckShinePos);

                debugTextData += std::to_string(debugCheckShinePos.x) + ".x " + std::to_string(debugCheckShinePos.y) + ".y; ";
            }
            mstCheckGridPos.push_back(debugNextCheckGrid);
#ifdef _DEBUG
            debugTextData += "\n\n";
            DEBUG::SaveText(debugTextData, DEBUG::DEBUG_MAP_TYPE::DEBUG_SHINE_POS);
#endif
        }

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
            // INPROGRESS:_ 障害物に当たった後にこれだと判定するときに左から見て光が無いから飛ばしてるから光の方向を現在の光領域に変更
            std::vector<Vector2_Int> ShineGridPositions = GetShineGridPositions(checkShinePos);

            // 現在の光領域を左端から右端へ走査
            for (const Vector2_Int& checkPos : ShineGridPositions)
            {
                // マップ外なら除外
                if (IsOutsideShineStage(checkPos))
                {
                    continue;
                }

                // すでに光が届いているなら除外
                // DELETE:_ 多分届いても複数考えられる場合は戻らない気がする
                // それと斜め方向バグるかもしれないからなくしたけどそれが原因でバグる可能性もある少ないけど
                // if (mstMapObjectGridData[checkPos.y][checkPos.x].LitFlag)
                // {
                //     continue;
                // }

                // グリッドの状況によって処理
                switch (JudgeGrid(checkPos, shineDirections, shineDirectionsIndex))
                {
                // 光領域外なため次を調べる
                case SHINE_GRID_TYPE::NOT_SHINE_GRID:
                {
                    // 次の光領域を調べる対象にするフラグ設定
                    mstCheckShineGridFlags.SetFlag(true, CHECK_SHINE_GRID_FLAGS::NAXT_SHINE_AREA);
                }
                    break;

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
                    mstMapObjectGridData[checkPos.y][checkPos.x].DebugDrawLiteFlag = true;
                    mstMapObjectGridData[checkPos.y][checkPos.x].LitLoopNumber = loopCount;
                    ++setLitNumber;
                    mstMapObjectGridData[checkPos.y][checkPos.x].SetLitNumber = setLitNumber;
                    
                    // 他の光領域が同グリッド内にあるなら次の光領域を調べる対象にするフラグ設定
                    mstCheckShineGridFlags.SetFlag(HasOtherShineAreaInGrid(checkPos, shineDirections, shineDirectionsIndex), CHECK_SHINE_GRID_FLAGS::NAXT_SHINE_AREA);
                }
                    break;

                case SHINE_GRID_TYPE::SHINE_AND_OBJECT_GRID:
                {
                    // ここで光を遮るものを追加
                    BLOCK_POS_DATA blockPos;
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
                    mstMapObjectGridData[checkPos.y][checkPos.x].DebugDrawLiteFlag = true;
                    mstMapObjectGridData[checkPos.y][checkPos.x].LitLoopNumber = loopCount;
                    ++setLitNumber;
                    mstMapObjectGridData[checkPos.y][checkPos.x].SetLitNumber = setLitNumber;
                    
                    // 他の光領域が同グリッド内にあるなら次の光領域を調べる対象にするフラグ設定
                    mstCheckShineGridFlags.SetFlag(HasOtherShineAreaInGrid(checkPos, shineDirections, shineDirectionsIndex), CHECK_SHINE_GRID_FLAGS::NAXT_SHINE_AREA);
                }
                    break;
                }

                if (mstCheckShineGridFlags.GetFlag_BitShift(CHECK_SHINE_GRID_FLAGS::NAXT_SHINE_AREA))
                {
                    break;
                }
            }
        
            if (mstCheckShineGridFlags.GetFlag_BitShift(CHECK_SHINE_GRID_FLAGS::NAXT_SHINE_AREA))
            {
                shineDirectionsIndex++;
                mstCheckShineGridFlags.DisableFlag(CHECK_SHINE_GRID_FLAGS::NAXT_SHINE_AREA);
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

    // 画面の角ポジション
    const Vector2 displayCornerPosition[ANGLE_NUMBER::ANGLE_NUMBER_DISPLAY_MAX] =
    {
        Vector2(0.0f,       0.0f),
        Vector2(0.0f,       MAP_SIZE_Y), 
        Vector2(MAP_SIZE_X, 0.0f), 
        Vector2(MAP_SIZE_X, MAP_SIZE_Y)
    };
    // 光源から見て画面の角アングル
    float displayCornerAngles[ANGLE_NUMBER::ANGLE_NUMBER_DISPLAY_MAX] =
    {
        GetAngleToPoint(mstShinePos, displayCornerPosition[ANGLE_NUMBER::ANGLE_NUMBER_DISPLAY_LEFT_UP]),
        GetAngleToPoint(mstShinePos, displayCornerPosition[ANGLE_NUMBER::ANGLE_NUMBER_DISPLAY_LEFT_DOWN]), 
        GetAngleToPoint(mstShinePos, displayCornerPosition[ANGLE_NUMBER::ANGLE_NUMBER_DISPLAY_RIGHT_UP]), 
        GetAngleToPoint(mstShinePos, displayCornerPosition[ANGLE_NUMBER::ANGLE_NUMBER_DISPLAY_RIGHT_DOWN])
    };
    
    for (int shineIterator = 0; shineIterator < shineDirections.size(); ++shineIterator)
    {
        float shineAnglesLeftAndRight[ANGLE_NUMBER::ANGLE_NUMBER_SHINE_MAX] = { shineDirections[shineIterator].leftAngle, shineDirections[shineIterator].rightAngle };
        Vector2 shineDirectionsLeftAndRight[ANGLE_NUMBER::ANGLE_NUMBER_SHINE_MAX] = { shineDirections[shineIterator].shineDirectionLeft, shineDirections[shineIterator].shineDirectionRight };
        int shineAngleNumbers[ANGLE_NUMBER::ANGLE_NUMBER_SHINE_MAX] = {0 , 0};

        Vector2 intersectionPositions[ANGLE_NUMBER::ANGLE_NUMBER_SHINE_MAX];

        // 光域左右の方向と交点を算出
        if (!GetShineDirectionIntersection(shineDirectionsLeftAndRight, shineAnglesLeftAndRight, shineAngleNumbers, intersectionPositions, displayCornerAngles, displayCornerPosition))
        {
            continue;
        }

        // 角を含めるなら角も描画用三角に追加
        AddDisplayCornerToDrawTriangle(intersectionPositions, shineAngleNumbers, displayCornerPosition);
    }

    
#ifdef _DEBUG
        DEBUG::SaveText("END\n\n", DEBUG::DEBUG_MAP_TYPE::DEBUG_SHINE_POS);
#endif
}

bool IsRayIntersectRect(const Vector2& rayOrigin, const Vector2& rayDirection, float left, float right, float top, float bottom);

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

    
    if (IsRayIntersectRect(mstShinePos, direction1, left, right, top, bottom) ||
        IsRayIntersectRect(mstShinePos, direction2, left, right, top, bottom))
    {
        if (mstMapObjectGridData[gridPos.y][gridPos.x].LinePoss.size() > 0)
            return SHINE_GRID_TYPE::SHINE_AND_OBJECT_GRID;

        return SHINE_GRID_TYPE::SHINE_GRID;
    }

    // 光範囲外
    return SHINE_GRID_TYPE::NOT_SHINE_GRID;
}

// グリッド内に現在の光領域以外の光領域があるか判定
bool ShineManager::HasOtherShineAreaInGrid(const Vector2_Int& gridPos, const std::vector<SHINE_DIRECTION>& shineDirections, int shineDirectionsIndex)
{
    // 現在の光領域の次から調べる
    for (int i = (shineDirectionsIndex + 1); i < static_cast<int>(shineDirections.size()); ++i)
    {
        const SHINE_DIRECTION& shineDirection =
            shineDirections[i];

        const Vector2 direction1 =
            shineDirection.shineDirectionLeft;

        const Vector2 direction2 =
            shineDirection.shineDirectionRight;

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
            Vector2(left, top),
            Vector2(right, top),
            Vector2(left, bottom),
            Vector2(right, bottom)
        };

        // 四隅のいずれかが光範囲内か判定
        for (const Vector2& corner : gridCorners)
        {
            Vector2 toCorner = corner - mstShinePos;

            // 光源と角が同じ位置なら光範囲内
            if (toCorner.x == 0.0f &&
                toCorner.y == 0.0f)
            {
                return true;
            }

            const float cross1 =
                direction1.x * toCorner.y -
                direction1.y * toCorner.x;

            const float cross2 =
                direction2.x * toCorner.y -
                direction2.y * toCorner.x;

            bool isShineArea = false;

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

            if (isShineArea)
            {
                return true;
            }
        }

        // 光範囲の境界線がグリッドを通過しているか判定
        if (IsRayIntersectRect(mstShinePos, direction1, left, right, top, bottom) || IsRayIntersectRect(mstShinePos, direction2, left, right, top, bottom))
        {
            return true;
        }
    }

    return false;
}

bool IsAngleBetween(float targetAngle, float leftAngle, float rightAngle);

// 光を遮るものを確認し、それに応じた処理を行う
void ShineManager::ShineBlockProcess(std::stack<BLOCK_POS_DATA>& blockPoss, std::queue<Vector2_Int>& nextCheckShinePos, std::vector<SHINE_DIRECTION>& shineDirections)
{
    // 遮っている場所を探す
    while (!blockPoss.empty() && !shineDirections.empty())
    {
        BLOCK_POS_DATA blockPos = blockPoss.top();
        blockPoss.pop();

        if (blockPos.ArrayIndex >= shineDirections.size())
        {
            continue;
        }

        // TODO:_ わざわざ整列指せなくても出来そうだしこれじゃほとんど今がなかったから消すかも
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
            RegisterShineAreaEndPointCandidate(checkLine, blockPos, shineDirections);
        }
        // グリッドに光が残っているか判定してフラグ更新
        //UpdateGridLightState(blockPos, shineDirections);

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

    for (int i = (shineDirections.size() - 1); i >= 0; --i)
    {
        std::vector<SHINE_DIRECTION> newShineDirections = ProcessShineAreaEndPointCandidates(i, shineDirections[i]);
        
        // 光の領域数が変更無いなら何もしない
        if (newShineDirections.size() != 1)
        {
            shineDirections.erase(shineDirections.begin() + i);
            shineDirections.insert(shineDirections.begin() + i, newShineDirections.begin(), newShineDirections.end());
        }
        // サイズが元と変わらないなら入れ替えるだけなら
        else
        {
            shineDirections[i] = newShineDirections[0];
        }
    }
    mstLightAreaEndPoint.clear();
}

// leftAngle（光の左端）を基準「0.0」とした時計回り方向への相対角度（0 ～ 2π）を算出する
static float GetClockwiseAngleFromLeft(float angle, float baseLeft)
{
    static constexpr float TWO_PI = 6.28318530717958647692f;
    float diff = std::fmod(angle - baseLeft, TWO_PI);
    if (diff < 0.0f) diff += TWO_PI;
    return diff;
}
static float GetSignedAngleFromLeft(float angle, float baseLeft)
{
    static constexpr float TWO_PI = 6.28318530717958647692f;
    static constexpr float PI = 3.14159265358979323846f;

    float diff = std::fmod(angle - baseLeft, TWO_PI);

    if (diff > PI)
    {
        diff -= TWO_PI;
    }
    else if (diff < -PI)
    {
        diff += TWO_PI;
    }

    return diff;
}

// 光域の終端候補を登録する
void ShineManager::RegisterShineAreaEndPointCandidate(LINE_POS blockLinePos, const BLOCK_POS_DATA& blockPos, std::vector<SHINE_DIRECTION>& shineDirections)
{
    // 現在処理している光域に対応する光方向を取得
    const SHINE_DIRECTION& currentShineDir =
        shineDirections[blockPos.ArrayIndex];

    // 障害物の左端・右端から光源への角度を求める
    const float blockLeftAngle =
        GetAngleToPoint(mstShinePos, blockLinePos.linePos1);

    const float blockRightAngle =
        GetAngleToPoint(mstShinePos, blockLinePos.linePos2);

    // 光域の左端を基準とした相対角度を求める
    const float blockLeftRel =
        GetSignedAngleFromLeft(
            blockLeftAngle,
            currentShineDir.leftAngle);

    const float blockRightRel =
        GetSignedAngleFromLeft(
            blockRightAngle,
            currentShineDir.leftAngle);

    // 現在の光域の角度幅
    const float totalShineWidth =
        GetSignedAngleFromLeft(
            currentShineDir.rightAngle,
            currentShineDir.leftAngle);

    // 障害物が現在の光域の外側にある場合は、
    // この光域の終端候補にはならないため処理しない
    if (blockLeftRel > totalShineWidth &&
        blockRightRel > totalShineWidth &&
        blockRightRel - blockLeftRel < DX_PI_F)
    {
        return;
    }

    // 障害物が光域の左端を遮っているか判定
    const bool crossesLeftEdge =
        blockLeftRel <= 0.0f &&
        blockRightRel >= 0.0f;

    // 障害物が光域の右端を遮っているか判定
    const bool crossesRightEdge =
        blockLeftRel <= totalShineWidth &&
        blockRightRel >= totalShineWidth;

    // 光域の左右端を遮っている場合
    if (crossesLeftEdge || crossesRightEdge)
    {
        // 光域の左端を遮っている場合
        if (crossesLeftEdge)
        {
            Vector2 intersection;

            // 光域左端の光線と障害物の線分との交点を求める
            if (GetIntersection(mstShinePos, mstShinePos + currentShineDir.shineDirectionLeft, blockLinePos.linePos1, blockLinePos.linePos2, intersection))
            {
                // 光源から見て角度が小さい方を
                // 光域の左側にある点として交点に置き換える
                if (blockLeftRel < blockRightRel)
                {
                    blockLinePos.linePos1 = intersection;
                }
                else
                {
                    blockLinePos.linePos2 = intersection;
                }
            }
        }
        // 光域の右端を遮っている場合
        if (crossesRightEdge)
        {
            Vector2 intersection;

            // 光域左端の光線と障害物の線分との交点を求める
            if (GetIntersection(mstShinePos, mstShinePos + currentShineDir.shineDirectionRight, blockLinePos.linePos1, blockLinePos.linePos2, intersection))
            {
                // 光源から見て角度が小さい方を
                // 光域の左側にある点として交点に置き換える
                if (blockLeftRel < blockRightRel)
                {
                    blockLinePos.linePos1 = intersection;
                }
                else
                {
                    blockLinePos.linePos2 = intersection;
                }
            }
        }

        // 光域をその場では変更せず、
        // 交点によって調整した障害物を
        // 光域の終端候補として登録する
        mstLightAreaEndPoint.push_back(SHINE_AREA_END_POSITION(blockLinePos, blockPos.ArrayIndex));
    }
    // 左右どちらの端も遮っていない場合
    else
    {
        // 光域の内部で障害物に遮られている状態。
        // 後で光域の終端を決定するための候補として登録する。
        mstLightAreaEndPoint.push_back(SHINE_AREA_END_POSITION(blockLinePos, blockPos.ArrayIndex));
    }
}

// 登録された光域終端候補を使用して、光域を削り、削った部分を描画用三角形に登録する
std::vector<SHINE_DIRECTION> ShineManager::ProcessShineAreaEndPointCandidates(int shineIndex, const SHINE_DIRECTION& shineDirections)
{
    // 現在の光領域
    std::vector<SHINE_DIRECTION> newShineDirections;
    newShineDirections.push_back(shineDirections);

    // 削った部分の三角形候補
    std::vector<SHINE_TRIANGLE> savedTriangle;

    // 対象となる終端候補を処理
    for (int lightIterator = (mstLightAreaEndPoint.size() - 1); lightIterator >= 0; --lightIterator)
    {
        const SHINE_AREA_END_POSITION& endPoint = mstLightAreaEndPoint[lightIterator];
        if (endPoint.shineDirectionIndex != shineIndex)
        {
            continue;
        }
        // 処理する終端候補を削除
        mstLightAreaEndPoint.erase(mstLightAreaEndPoint.begin() + lightIterator);
        
        // 三角に登録
        {
            SHINE_TRIANGLE triangle;

            triangle.Vertex1 =
                Vector2_Int(
                    static_cast<int>(mstShinePos.x),
                    static_cast<int>(mstShinePos.y));

            triangle.Vertex2 =
                Vector2_Int(
                    static_cast<int>(endPoint.linePos1.x),
                    static_cast<int>(endPoint.linePos1.y));

            triangle.Vertex3 =
                Vector2_Int(
                    static_cast<int>(endPoint.linePos2.x),
                    static_cast<int>(endPoint.linePos2.y));

            savedTriangle.push_back(triangle);
        }

        /*① 線分の両端を光源から見た角度に変換*/
        const float lineAngle1 =
            GetAngleToPoint(mstShinePos, endPoint.linePos1);

        const float lineAngle2 =
            GetAngleToPoint(mstShinePos, endPoint.linePos2);

        /*② 現在の光領域に対して、この線分が遮る角度範囲を求める*/
        const float lineRelativeAngle1 =
            GetSignedAngleFromLeft(
                lineAngle1,
                shineDirections.leftAngle);

        const float lineRelativeAngle2 =
            GetSignedAngleFromLeft(
                lineAngle2,
                shineDirections.leftAngle);

        const float blockLeftAngle =
            min(lineRelativeAngle1, lineRelativeAngle2);

        const float blockRightAngle =
            max(lineRelativeAngle1, lineRelativeAngle2);

        /*③ 遮られる部分をnewShineDirections から削除・分割*/
        std::vector<SHINE_DIRECTION> splitShineDirections;

        for (const SHINE_DIRECTION& currentShineDirection : newShineDirections)
        {
            const float currentLeftAngle =
                GetSignedAngleFromLeft(
                    currentShineDirection.leftAngle,
                    shineDirections.leftAngle);

            const float currentRightAngle =
                GetSignedAngleFromLeft(
                    currentShineDirection.rightAngle,
                    shineDirections.leftAngle);

            // 現在の光領域と遮蔽範囲の重なり
            const float overlapLeft =
                max(currentLeftAngle, blockLeftAngle);

            const float overlapRight =
                min(currentRightAngle, blockRightAngle);

            // 重なっていない
            if (overlapRight <= overlapLeft)
            {
                splitShineDirections.push_back(currentShineDirection);
                continue;
            }

            // 左側に残る光領域
            if (currentLeftAngle < overlapLeft)
            {
                SHINE_DIRECTION leftShineDirection = currentShineDirection;

                leftShineDirection.leftAngle =
                    shineDirections.leftAngle + currentLeftAngle;

                leftShineDirection.rightAngle =
                    shineDirections.leftAngle + overlapLeft;

                leftShineDirection.visionAngle =
                    leftShineDirection.rightAngle -
                    leftShineDirection.leftAngle;

                leftShineDirection.angle =
                    (leftShineDirection.leftAngle +
                     leftShineDirection.rightAngle) * 0.5f;

                leftShineDirection.shineDirectionLeft =
                {
                    std::cos(leftShineDirection.leftAngle),
                    std::sin(leftShineDirection.leftAngle)
                };

                leftShineDirection.shineDirectionRight =
                {
                    std::cos(leftShineDirection.rightAngle),
                    std::sin(leftShineDirection.rightAngle)
                };

                splitShineDirections.push_back(leftShineDirection);
            }

            // 右側に残る光領域
            if (overlapRight < currentRightAngle)
            {
                SHINE_DIRECTION rightShineDirection = currentShineDirection;

                rightShineDirection.leftAngle =
                    shineDirections.leftAngle + overlapRight;

                rightShineDirection.rightAngle =
                    shineDirections.leftAngle + currentRightAngle;

                rightShineDirection.visionAngle =
                    rightShineDirection.rightAngle -
                    rightShineDirection.leftAngle;

                rightShineDirection.angle =
                    (rightShineDirection.leftAngle +
                     rightShineDirection.rightAngle) * 0.5f;

                rightShineDirection.shineDirectionLeft =
                {
                    std::cos(rightShineDirection.leftAngle),
                    std::sin(rightShineDirection.leftAngle)
                };

                rightShineDirection.shineDirectionRight =
                {
                    std::cos(rightShineDirection.rightAngle),
                    std::sin(rightShineDirection.rightAngle)
                };

                splitShineDirections.push_back(rightShineDirection);
            }
        }

        newShineDirections = splitShineDirections;
    }

    // 三角を削る
    {
    }

    // 三角登録
    for (int i = 0; i < savedTriangle.size(); ++i)
    {
        //AddDrawTriangleData(savedTriangle[i]);
    }

    return newShineDirections;
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


static bool IsRayIntersectRect(const Vector2& rayOrigin, const Vector2& rayDirection, float left, float right, float top, float bottom)
{
    float tMin = 0.0f;
    float tMax = FLT_MAX;

    // X方向
    if (rayDirection.x == 0.0f)
    {
        if (rayOrigin.x < left || rayOrigin.x > right)
            return false;
    }
    else
    {
        float t1 = (left - rayOrigin.x) / rayDirection.x;
        float t2 = (right - rayOrigin.x) / rayDirection.x;

        if (t1 > t2)
            std::swap(t1, t2);

        tMin = max(tMin, t1);
        tMax = min(tMax, t2);

        if (tMin > tMax)
            return false;
    }

    // Y方向
    if (rayDirection.y == 0.0f)
    {
        if (rayOrigin.y < top || rayOrigin.y > bottom)
            return false;
    }
    else
    {
        float t1 = (top - rayOrigin.y) / rayDirection.y;
        float t2 = (bottom - rayOrigin.y) / rayDirection.y;

        if (t1 > t2)
            std::swap(t1, t2);

        tMin = max(tMin, t1);
        tMax = min(tMax, t2);

        if (tMin > tMax)
            return false;
    }

    return tMax >= 0.0f;
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

    // // 周囲8方向の隣接グリッドを調べる
    // for (int y = -1; y <= 1; ++y)
    // {
    //     for (int x = -1; x <= 1; ++x)
    //     {
    //         if (x == 0 && y == 0) continue;

    //         const Vector2_Int nextPos =
    //         {
    //             nowCheckShinePos.x + x,
    //             nowCheckShinePos.y + y
    //         };

    // 上下左右の4方向の隣接グリッドを調べる
    const int checkDirections[4][2] =
    {
        {  0, -1 }, // 上
        {  1,  0 }, // 右
        {  0,  1 }, // 下
        { -1,  0 }  // 左
    };

    for (const auto& direction : checkDirections)
    {
        const Vector2_Int nextPos =
        {
            nowCheckShinePos.x + direction[0],
            nowCheckShinePos.y + direction[1]
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
        
        // 四隅がすべて範囲外でも左右の照射境界線がグリッドを通過していれば対象
        if (!isInsideShine)
        {
            isInsideShine = IsRayIntersectRect(shinePos, shineDir.shineDirectionLeft, left, right, top, bottom) || 
                            IsRayIntersectRect(shinePos, shineDir.shineDirectionRight, left, right, top, bottom);
        }

        // 頂点が照射角度に入っている場合追加
        if (isInsideShine)
        {
            shineGridPositions.push_back(nextPos);
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
    if (shineTriangle.Vertex2 == shineTriangle.Vertex3)
    {
        return;
    }
    mstSheineTriangles.push_back(shineTriangle);
}


// 障害物との交点を取得
void ShineManager::GetShineBlockingIntersection(const Vector2& edgePos1, const Vector2& edgePos2, const SHINE_DIRECTION& shineDirection, const Vector2_Int& blockPos, Vector2& intersection1, Vector2& intersection2)
{
    const Vector2 edge = edgePos2 - edgePos1;

    const float edgeLengthSquared =
        edge.x * edge.x +
        edge.y * edge.y;
    if (edgeLengthSquared == 0.0f)
    {
        return;
    }

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

        // 光の前方にある交点だけを対象にする
        if (t >= 0.0f)
        {
            const Vector2 candidate =
                mstShinePos +
                shineDirection.shineDirectionLeft * t;

            const Vector2 toCandidate =
                candidate - edgePos1;

            // edgePos1 ～ edgePos2 のどこにあるか
            const float u =
                (toCandidate.x * edge.x +
                 toCandidate.y * edge.y) /
                edgeLengthSquared;

            // 渡された縁の内側にある場合だけ採用
            if (u >= 0.0f && u <= 1.0f)
            {
                intersection1 = candidate;
            }
        }
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
 
        // 光の前方にある交点だけを対象にする
        if (t >= 0.0f)
        {
            const Vector2 candidate =
                mstShinePos +
                shineDirection.shineDirectionRight * t;

            const Vector2 toCandidate =
                candidate - edgePos1;

            // edgePos1 ～ edgePos2 のどこにあるか
            const float u =
                (toCandidate.x * edge.x +
                 toCandidate.y * edge.y) /
                edgeLengthSquared;

            // 渡された縁の内側にある場合だけ採用
            if (u >= 0.0f && u <= 1.0f)
            {
                intersection2 = candidate;
            }
        }
    }

    {
        // グリッド内に補正
        intersection1 = AdjustPositionToGrid(blockPos, intersection1);
        intersection2 = AdjustPositionToGrid(blockPos, intersection2);
    }
}

// グリッドの光状態を更新
void ShineManager::UpdateGridLightState(const BLOCK_POS_DATA& blockPos, const std::vector<SHINE_DIRECTION>& shineDirections)
{
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

        if (isStillLit)
        {
            break;
        }
    }

    // 光領域が残っている場合はフラグを更新して次の探索キューに追加
    if (!isStillLit && mstMapObjectGridData[blockPos.BlockPos.y][blockPos.BlockPos.x].LitFlag)
    {
        mstMapObjectGridData[blockPos.BlockPos.y][blockPos.BlockPos.x].LitFlag = false;
    }
}

// 2次元ベクトル同士の外積のZ成分を求める
float ShineManager::Cross(const Vector2& src, const Vector2& dst)
{
    return src.x * dst.y - src.y * dst.x;
}

// 2本の線分の交点を求める
bool ShineManager::GetIntersection(const Vector2& srcA, const Vector2& srcB, const Vector2& dstC, const Vector2& dstD, Vector2& intersection)
{
    // 線分srcABの方向ベクトルを求める
    Vector2 srcAB =
    {
        srcB.x - srcA.x,
        srcB.y - srcA.y
    };

    // 線分dstCDの方向ベクトルを求める
    Vector2 dstCD =
    {
        dstD.x - dstC.x,
        dstD.y - dstC.y
    };

    // srcABとdstCDの外積を求める
    float denominator = Cross(srcAB, dstCD);

    // 外積が0の場合、2本の線分は平行
    // 平行な場合は交点を求められない
    if (fabsf(denominator) < 0.000001f)
    {
        return false;
    }

    // 線分srcABの始点srcAから
    // 線分dstCDの始点dstCまでのベクトルを求める
    Vector2 srcAdstC =
    {
        dstC.x - srcA.x,
        dstC.y - srcA.y
    };

    // 線分srcAB上のどの位置に交点があるかを求める
    // 0ならsrcA、1ならsrcB、0.5ならsrcAとsrcBの中間
    float t = Cross(srcAdstC, dstCD) / denominator;

    // 線分dstCD上のどの位置に交点があるかを求める
    // 0ならdstC、1ならdstD、0.5ならdstCとdstDの中間
    float u = Cross(srcAdstC, srcAB) / denominator;

    // tが0～1の範囲外なら、交点は線分srcABの外側
    // uが0～1の範囲外なら、交点は線分dstCDの外側
    if (t < 0.0f || t > 1.0f ||
        u < 0.0f || u > 1.0f)
    {
        return false;
    }

    // 線分srcAB上のtの位置から交点の座標を求める
    intersection =
    {
        srcA.x + srcAB.x * t,
        srcA.y + srcAB.y * t
    };

    // 線分同士が交差している
    return true;
}

// 線分ABの延長線と線分CDの延長線の交点を求める
bool ShineManager::GetLineIntersection(const Vector2& srcA, const Vector2& srcB, const Vector2& dstC, const Vector2& dstD, Vector2& intersection)
{
    // 線分srcABの方向ベクトルを求める
    Vector2 srcAB =
    {
        srcB.x - srcA.x,
        srcB.y - srcA.y
    };

    // 線分dstCDの方向ベクトルを求める
    Vector2 dstCD =
    {
        dstD.x - dstC.x,
        dstD.y - dstC.y
    };

    // srcABとdstCDの外積を求める
    float denominator = Cross(srcAB, dstCD);

    // 外積が0の場合、2本の線分は平行
    // 平行な場合は交点を求められない
    if (denominator == 0.0f)
    {
        return false;
    }

    // 線分srcABの始点srcAから
    // 線分dstCDの始点dstCまでのベクトルを求める
    Vector2 srcAdstC =
    {
        dstC.x - srcA.x,
        dstC.y - srcA.y
    };

    // 線分srcAB上のどの位置に交点があるかを求める
    // 0ならsrcA、1ならsrcB、0.5ならsrcAとsrcBの中間
    float t = Cross(srcAdstC, dstCD) / denominator;

    // 線分dstCD上のどの位置に交点があるかを求める
    // 0ならdstC、1ならdstD、0.5ならdstCとdstDの中間
    float u = Cross(srcAdstC, srcAB) / denominator;

    // 線分srcAB上のtの位置から交点の座標を求める
    intersection =
    {
        srcA.x + srcAB.x * t,
        srcA.y + srcAB.y * t
    };

    // 線分同士が交差している
    return true;
}

// 2点間の角度を取得します。
float ShineManager::GetAngleToPoint(const Vector2& from, const Vector2& to)
{
    const float dx = to.x - from.x;
    const float dy = to.y - from.y;

    float angle = std::atan2(dy, dx);

    if (angle < 0.0f)
    {
        angle += DX_TWO_PI;
    }

    return angle;
}

// 光の右と左の方向と交点を算出
bool ShineManager::GetShineDirectionIntersection(const Vector2 shineDirections[ANGLE_NUMBER::ANGLE_NUMBER_SHINE_MAX], float shineAngles[ANGLE_NUMBER::ANGLE_NUMBER_SHINE_MAX], int shineAngleNumbers[ANGLE_NUMBER::ANGLE_NUMBER_SHINE_MAX], Vector2 intersectionPositions[ANGLE_NUMBER::ANGLE_NUMBER_SHINE_MAX], float displayCornerAngles[ANGLE_NUMBER::ANGLE_NUMBER_DISPLAY_MAX], const Vector2 displayCornerPosition[ANGLE_NUMBER::ANGLE_NUMBER_DISPLAY_MAX])
{
    // 算出&どの方向か取得
    for(int i = 0; i < ANGLE_NUMBER::ANGLE_NUMBER_SHINE_MAX; ++i)
    {
        // 0～PI*2 の間に収める
        {
            while (shineAngles[i] < 0.0f)
            {
                shineAngles[i] += (DX_TWO_PI_F);
            }

            while (shineAngles[i] > DX_TWO_PI_F)
            {
                shineAngles[i] -= (DX_TWO_PI_F);
            }
        }

        shineAngleNumbers[i] = -1;
        
        // 左
        if ((displayCornerAngles[ANGLE_NUMBER::ANGLE_NUMBER_DISPLAY_LEFT_UP]    >= shineAngles[i]) &&
            (displayCornerAngles[ANGLE_NUMBER::ANGLE_NUMBER_DISPLAY_LEFT_DOWN] <= shineAngles[i]))
        {
            shineAngleNumbers[i] = ANGLE_BIT_NUMBER::ANGLE_BIT_NUMBER_LEFT;
            // 算出
            if (!GetLineIntersection(displayCornerPosition[ANGLE_NUMBER::ANGLE_NUMBER_DISPLAY_LEFT_UP], displayCornerPosition[ANGLE_NUMBER::ANGLE_NUMBER_DISPLAY_LEFT_DOWN],
                                    mstShinePos, mstShinePos + shineDirections[i], 
                                    intersectionPositions[i]))
            {
                return false;
            }
        }
        // 右(0が右なため||)
        else if ((displayCornerAngles[ANGLE_NUMBER::ANGLE_NUMBER_DISPLAY_RIGHT_UP]   <= shineAngles[i]) ||
                (displayCornerAngles[ANGLE_NUMBER::ANGLE_NUMBER_DISPLAY_RIGHT_DOWN] >= shineAngles[i]))
        {
            shineAngleNumbers[i] = ANGLE_BIT_NUMBER::ANGLE_BIT_NUMBER_RIGHT;
            // 算出
            if (!GetLineIntersection(displayCornerPosition[ANGLE_NUMBER::ANGLE_NUMBER_DISPLAY_RIGHT_UP], displayCornerPosition[ANGLE_NUMBER::ANGLE_NUMBER_DISPLAY_RIGHT_DOWN],
                                    mstShinePos, mstShinePos + shineDirections[i], 
                                    intersectionPositions[i]))
            {
                return false;
            }
        }
        // 上
        else if ((displayCornerAngles[ANGLE_NUMBER::ANGLE_NUMBER_DISPLAY_LEFT_UP]  <= shineAngles[i]) &&
                (displayCornerAngles[ANGLE_NUMBER::ANGLE_NUMBER_DISPLAY_RIGHT_UP] >= shineAngles[i]))
        {
            shineAngleNumbers[i] = ANGLE_BIT_NUMBER::ANGLE_BIT_NUMBER_UP;
            // 算出
            if (!GetLineIntersection(displayCornerPosition[ANGLE_NUMBER::ANGLE_NUMBER_DISPLAY_LEFT_UP], displayCornerPosition[ANGLE_NUMBER::ANGLE_NUMBER_DISPLAY_RIGHT_UP],
                                    mstShinePos, mstShinePos + shineDirections[i], 
                                    intersectionPositions[i]))
            {
                return false;
            }
        }
        // 下
        else if ((displayCornerAngles[ANGLE_NUMBER::ANGLE_NUMBER_DISPLAY_RIGHT_DOWN]   <= shineAngles[i]) &&
                (displayCornerAngles[ANGLE_NUMBER::ANGLE_NUMBER_DISPLAY_LEFT_DOWN]    >= shineAngles[i]))
        {
            shineAngleNumbers[i] = ANGLE_BIT_NUMBER::ANGLE_BIT_NUMBER_DOWN;
            // 算出
            if (!GetLineIntersection(displayCornerPosition[ANGLE_NUMBER::ANGLE_NUMBER_DISPLAY_RIGHT_DOWN], displayCornerPosition[ANGLE_NUMBER::ANGLE_NUMBER_DISPLAY_LEFT_DOWN],
                                    mstShinePos, mstShinePos + shineDirections[i], 
                                    intersectionPositions[i]))
            {
                return false;
            }
        }

        if (shineAngleNumbers[i] == -1)
        {
            return false;
        }
    }

    return true;
}

// 角が含まれるなら角を描画に追加
void ShineManager::AddDisplayCornerToDrawTriangle(const Vector2 shineDirections[ANGLE_NUMBER::ANGLE_NUMBER_SHINE_MAX], const int shineAngleNumbers[ANGLE_NUMBER::ANGLE_NUMBER_SHINE_MAX], const Vector2 displayCornerPosition[ANGLE_NUMBER::ANGLE_NUMBER_DISPLAY_MAX])
{
    switch (shineAngleNumbers[ANGLE_NUMBER::ANGLE_NUMBER_SHINE_LEFT] | shineAngleNumbers[ANGLE_NUMBER::ANGLE_NUMBER_SHINE_RIGHT])
    {
    case ANGLE_BIT_NUMBER::ANGLE_BIT_NUMBER_LEFT_UP:
        AddDrawTriangleData(shineDirections[ANGLE_NUMBER::ANGLE_NUMBER_SHINE_LEFT], displayCornerPosition[ANGLE_NUMBER::ANGLE_NUMBER_DISPLAY_LEFT_UP]);
        AddDrawTriangleData(shineDirections[ANGLE_NUMBER::ANGLE_NUMBER_SHINE_RIGHT], displayCornerPosition[ANGLE_NUMBER::ANGLE_NUMBER_DISPLAY_LEFT_UP]);
        break;
        
    case ANGLE_BIT_NUMBER::ANGLE_BIT_NUMBER_LEFT_DOWN:
        AddDrawTriangleData(shineDirections[ANGLE_NUMBER::ANGLE_NUMBER_SHINE_LEFT], displayCornerPosition[ANGLE_NUMBER::ANGLE_NUMBER_DISPLAY_LEFT_DOWN]);
        AddDrawTriangleData(shineDirections[ANGLE_NUMBER::ANGLE_NUMBER_SHINE_RIGHT], displayCornerPosition[ANGLE_NUMBER::ANGLE_NUMBER_DISPLAY_LEFT_DOWN]);
        break;
        
    case ANGLE_BIT_NUMBER::ANGLE_BIT_NUMBER_RIGHT_UP:
        AddDrawTriangleData(shineDirections[ANGLE_NUMBER::ANGLE_NUMBER_SHINE_LEFT], displayCornerPosition[ANGLE_NUMBER::ANGLE_NUMBER_DISPLAY_RIGHT_UP]);
        AddDrawTriangleData(shineDirections[ANGLE_NUMBER::ANGLE_NUMBER_SHINE_RIGHT], displayCornerPosition[ANGLE_NUMBER::ANGLE_NUMBER_DISPLAY_RIGHT_UP]);
        break;
        
    case ANGLE_BIT_NUMBER::ANGLE_BIT_NUMBER_RIGHT_DOWN:
        AddDrawTriangleData(shineDirections[ANGLE_NUMBER::ANGLE_NUMBER_SHINE_LEFT], displayCornerPosition[ANGLE_NUMBER::ANGLE_NUMBER_DISPLAY_RIGHT_DOWN]);
        AddDrawTriangleData(shineDirections[ANGLE_NUMBER::ANGLE_NUMBER_SHINE_RIGHT], displayCornerPosition[ANGLE_NUMBER::ANGLE_NUMBER_DISPLAY_RIGHT_DOWN]);
        break;
        
    case ANGLE_BIT_NUMBER::ANGLE_BIT_NUMBER_LEFT_RIGHT:
        if (shineAngleNumbers[ANGLE_NUMBER::ANGLE_NUMBER_SHINE_LEFT] == ANGLE_BIT_NUMBER::ANGLE_BIT_NUMBER_LEFT)
        {
            // 左上
            AddDrawTriangleData(shineDirections[ANGLE_NUMBER::ANGLE_NUMBER_SHINE_LEFT], displayCornerPosition[ANGLE_NUMBER::ANGLE_NUMBER_DISPLAY_LEFT_UP]);
            // 右上
            AddDrawTriangleData(shineDirections[ANGLE_NUMBER::ANGLE_NUMBER_SHINE_RIGHT], displayCornerPosition[ANGLE_NUMBER::ANGLE_NUMBER_DISPLAY_RIGHT_UP]);
            
            // 上
            AddDrawTriangleData(displayCornerPosition[ANGLE_NUMBER::ANGLE_NUMBER_DISPLAY_LEFT_UP], displayCornerPosition[ANGLE_NUMBER::ANGLE_NUMBER_DISPLAY_RIGHT_UP]);
        }
        else
        {
            // 左下
            AddDrawTriangleData(shineDirections[ANGLE_NUMBER::ANGLE_NUMBER_SHINE_RIGHT], displayCornerPosition[ANGLE_NUMBER::ANGLE_NUMBER_DISPLAY_LEFT_DOWN]);
            // 右下
            AddDrawTriangleData(shineDirections[ANGLE_NUMBER::ANGLE_NUMBER_SHINE_LEFT], displayCornerPosition[ANGLE_NUMBER::ANGLE_NUMBER_DISPLAY_RIGHT_DOWN]);

            // 下
            AddDrawTriangleData(displayCornerPosition[ANGLE_NUMBER::ANGLE_NUMBER_DISPLAY_LEFT_DOWN], displayCornerPosition[ANGLE_NUMBER::ANGLE_NUMBER_DISPLAY_RIGHT_DOWN]);
        }
        break;
        
    case ANGLE_BIT_NUMBER::ANGLE_BIT_NUMBER_UP_DOWN:
        if (shineAngleNumbers[ANGLE_NUMBER::ANGLE_NUMBER_SHINE_LEFT] == ANGLE_BIT_NUMBER::ANGLE_BIT_NUMBER_UP)
        {
            // 右上
            AddDrawTriangleData(shineDirections[ANGLE_NUMBER::ANGLE_NUMBER_SHINE_LEFT], displayCornerPosition[ANGLE_NUMBER::ANGLE_NUMBER_DISPLAY_RIGHT_UP]);
            // 右下
            AddDrawTriangleData(shineDirections[ANGLE_NUMBER::ANGLE_NUMBER_SHINE_RIGHT], displayCornerPosition[ANGLE_NUMBER::ANGLE_NUMBER_DISPLAY_RIGHT_DOWN]);
            
            // 右
            AddDrawTriangleData(displayCornerPosition[ANGLE_NUMBER::ANGLE_NUMBER_DISPLAY_RIGHT_UP], displayCornerPosition[ANGLE_NUMBER::ANGLE_NUMBER_DISPLAY_RIGHT_DOWN]);
        }
        else
        {
            // 左上
            AddDrawTriangleData(shineDirections[ANGLE_NUMBER::ANGLE_NUMBER_SHINE_RIGHT], displayCornerPosition[ANGLE_NUMBER::ANGLE_NUMBER_DISPLAY_LEFT_UP]);
            // 左下
            AddDrawTriangleData(shineDirections[ANGLE_NUMBER::ANGLE_NUMBER_SHINE_LEFT], displayCornerPosition[ANGLE_NUMBER::ANGLE_NUMBER_DISPLAY_LEFT_DOWN]);
            
            // 左
            AddDrawTriangleData(displayCornerPosition[ANGLE_NUMBER::ANGLE_NUMBER_DISPLAY_LEFT_UP], displayCornerPosition[ANGLE_NUMBER::ANGLE_NUMBER_DISPLAY_LEFT_DOWN]);
        }
        break;

    default:
        // 描画用三角に追加
        AddDrawTriangleData(shineDirections[ANGLE_NUMBER::ANGLE_NUMBER_SHINE_LEFT], shineDirections[ANGLE_NUMBER::ANGLE_NUMBER_SHINE_RIGHT]);
        break;
    }
}