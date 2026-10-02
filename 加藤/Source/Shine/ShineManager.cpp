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
    TEST_SHINE_WALL_LOOP_INDEX,
    TEST_SHINE_WALL_NUMBER_INDEX,
    TEST_SHINE_GRID_SHINE_AREA_INDEX,
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
    TEST_BUTTON_SHINE_WALL_LOOP_INDEX,
    TEST_BUTTON_SHINE_WALL_NUMBER_INDEX,
    TEST_BUTTON_SHINE_GRID_SHINE_AREA_INDEX,
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
, mstShineAreaResult()
, mstLightAreaEndPoint()
, mnLineIdNowMax(0)
{
    for (int i = 0; i < DRAW_MODE_NUMBER::DRAW_MODE_NUMBER_MAX; ++i)
    {
        mnDrawMode[i] = SHINE_DRAW_MODE::NONE;
    }
    mnDrawMode[0] = SHINE_DRAW_MODE::TRIANGLE_SHINE_DRAW_MODE_TRUE;
    mnDrawMode[1] = SHINE_DRAW_MODE::TRIANGLE_SHINE_DRAW_MODE;
    mnDrawMode[2] = SHINE_DRAW_MODE::TEST_ANGLE_DRAW_MODE;
}

ShineManager::~ShineManager()
{
}

void ShineManager::Init()
{
    mpObjects.clear();

    // �����Ő���
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

    // ���������I�u�W�F�N�g������
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

    // ���̈�쐬
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
                // ���̈�̕`��
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
                // ���̈�̕`��
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
                // ���̈�̕`��
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
                // ���̈�̕`��
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
        
        case SHINE_DRAW_MODE::GRID_WALL_GRID_SHINE_INDEX_DRAW_MODE:
            for (int y = 0; y < MAP_ARRAY_SIZE_Y; ++y)
            {
                for (int x = 0; x < MAP_ARRAY_SIZE_X; ++x)
                {
                    if (mstMapObjectGridData[y][x].ShineAreaIndex.size() > 0)
                    {
                        DrawBox(ONE_GRID_SIZE_X * x,       ONE_GRID_SIZE_Y * y,
                                ONE_GRID_SIZE_X * (x + 1), ONE_GRID_SIZE_Y * (y + 1),
                                GetDebugColor(mnDrawMode[drawModeIndex]),
                                FALSE);
                        std::string shineAreaIndexNumber;
                        for (int i = 0; i < mstMapObjectGridData[y][x].ShineAreaIndex.size(); ++i)
                        {
                            shineAreaIndexNumber += std::to_string(mstMapObjectGridData[y][x].ShineAreaIndex[i]) + ":";
                        }
                        DrawString(ONE_GRID_SIZE_X * x, ONE_GRID_SIZE_Y * y, shineAreaIndexNumber.c_str(), GetDebugColor(mnDrawMode[drawModeIndex]));
                    }
                }
            }
            break;
        
        case SHINE_DRAW_MODE::SHINE_CHECK_GRID_DRAW_MODE:
            for (int y = 0; y < MAP_ARRAY_SIZE_Y; ++y)
            {
                for (int x = 0; x < MAP_ARRAY_SIZE_X; ++x)
                {
                    if (mstMapObjectGridData[y][x].ShineAreaCheckDatas.size() > 0)
                    {
   

                        std::string shineAreaIndexNumber = std::to_string(x) + ", " + std::to_string(y) + "\n";
                        for (int i = 0; i < mstMapObjectGridData[y][x].ShineAreaCheckDatas.size(); ++i)
                        {
                            const Vector2_Int centerAdjustment = Vector2_Int((ONE_GRID_SIZE_X * 0.5f), (ONE_GRID_SIZE_Y * 0.5f));
                            DrawLine(
                                (ONE_GRID_SIZE_X * x) + centerAdjustment.x + i, (ONE_GRID_SIZE_Y * y) + centerAdjustment.y + i,
                                (ONE_GRID_SIZE_X * mstMapObjectGridData[y][x].ShineAreaCheckDatas[i].CheckGridPos.x) + centerAdjustment.x + i, (ONE_GRID_SIZE_Y * mstMapObjectGridData[y][x].ShineAreaCheckDatas[i].CheckGridPos.y) + centerAdjustment.y + i,
                                GetDebugColor(mnDrawMode[drawModeIndex] + mstMapObjectGridData[y][x].ShineAreaCheckDatas[i].ShineAreaIndex));

                            shineAreaIndexNumber += std::to_string(mstMapObjectGridData[y][x].ShineAreaCheckDatas[i].ShineAreaIndex) + "��(" + std::to_string(mstMapObjectGridData[y][x].ShineAreaCheckDatas[i].CheckGridPos.x) + ", " + std::to_string(mstMapObjectGridData[y][x].ShineAreaCheckDatas[i].CheckGridPos.y) + ")\n";
                        }
                        DrawBox(ONE_GRID_SIZE_X * x,       ONE_GRID_SIZE_Y * y,
                                ONE_GRID_SIZE_X * (x + 1), ONE_GRID_SIZE_Y * (y + 1),
                                GetDebugColor(mnDrawMode[drawModeIndex]),
                                FALSE);
                        DrawString(ONE_GRID_SIZE_X * x, ONE_GRID_SIZE_Y * y, shineAreaIndexNumber.c_str(), GetDebugColor(mnDrawMode[drawModeIndex]));
                    }
                }
            }
            break;
        
        case SHINE_DRAW_MODE::SHINE_AREA_SELECT_CHECK_GRID_DRAW_MODE:
        {
            int maxShineAreaIndex = 0;
            for (int y = 0; y < MAP_ARRAY_SIZE_Y; ++y)
            {
                for (int x = 0; x < MAP_ARRAY_SIZE_X; ++x)
                {
                    if (mstMapObjectGridData[y][x].ShineAreaCheckDatas.size() > 0)
                    {
                        std::string shineAreaIndexNumber = std::to_string(x) + ", " + std::to_string(y) + "\n";
                        for (int i = 0; i < mstMapObjectGridData[y][x].ShineAreaCheckDatas.size(); ++i)
                        {
                            if (maxShineAreaIndex < mstMapObjectGridData[y][x].ShineAreaCheckDatas[i].ShineAreaIndex)
                            {
                                maxShineAreaIndex = mstMapObjectGridData[y][x].ShineAreaCheckDatas[i].ShineAreaIndex;
                            }
                            if (testNumber[TEST_INDEX_NUMBERS::TEST_SHINE_GRID_SHINE_AREA_INDEX] != mstMapObjectGridData[y][x].ShineAreaCheckDatas[i].ShineAreaIndex)
                            {
                                continue;
                            }
                            const Vector2_Int centerAdjustment = Vector2_Int((ONE_GRID_SIZE_X * 0.5f), (ONE_GRID_SIZE_Y * 0.5f));
                            DrawLine(
                                (ONE_GRID_SIZE_X * x) + centerAdjustment.x + i, (ONE_GRID_SIZE_Y * y) + centerAdjustment.y + i,
                                (ONE_GRID_SIZE_X * mstMapObjectGridData[y][x].ShineAreaCheckDatas[i].CheckGridPos.x) + centerAdjustment.x + i, (ONE_GRID_SIZE_Y * mstMapObjectGridData[y][x].ShineAreaCheckDatas[i].CheckGridPos.y) + centerAdjustment.y + i,
                                GetDebugColor(mnDrawMode[drawModeIndex] + mstMapObjectGridData[y][x].ShineAreaCheckDatas[i].ShineAreaIndex));

                            shineAreaIndexNumber += std::to_string(mstMapObjectGridData[y][x].ShineAreaCheckDatas[i].ShineAreaIndex) + "��(" + std::to_string(mstMapObjectGridData[y][x].ShineAreaCheckDatas[i].CheckGridPos.x) + ", " + std::to_string(mstMapObjectGridData[y][x].ShineAreaCheckDatas[i].CheckGridPos.y) + ")\n";
                        }
                        if (shineAreaIndexNumber == (std::to_string(x) + ", " + std::to_string(y) + "\n"))
                        {
                            continue;
                        }
                        DrawBox(ONE_GRID_SIZE_X * x,       ONE_GRID_SIZE_Y * y,
                                ONE_GRID_SIZE_X * (x + 1), ONE_GRID_SIZE_Y * (y + 1),
                                GetDebugColor(mnDrawMode[drawModeIndex]),
                                FALSE);
                        DrawString(ONE_GRID_SIZE_X * x, ONE_GRID_SIZE_Y * y, shineAreaIndexNumber.c_str(), GetDebugColor(mnDrawMode[drawModeIndex]));
                    }
                }
            }
            if (maxShineAreaIndex < testNumber[TEST_INDEX_NUMBERS::TEST_SHINE_GRID_SHINE_AREA_INDEX])
            {
                testNumber[TEST_INDEX_NUMBERS::TEST_SHINE_GRID_SHINE_AREA_INDEX] = maxShineAreaIndex;
            }
        }
            break;
        
        case SHINE_DRAW_MODE::SHINE_AREA_SELECT_LOOP_CHECK_GRID_DRAW_MODE:
        {
            if (mstCheckGridPos.size() <= 0)
            {
                break;
            }
            if (mstCheckGridPos.size() <= testNumber[TEST_INDEX_NUMBERS::TEST_SHINE_GRID_LOOP_COUNT_INDEX])
            {
                testNumber[TEST_INDEX_NUMBERS::TEST_SHINE_GRID_LOOP_COUNT_INDEX] = mstCheckGridPos.size() - 1;
            }
            for (int checkGirdPosIterator = 0; checkGirdPosIterator < mstCheckGridPos[testNumber[TEST_INDEX_NUMBERS::TEST_SHINE_GRID_LOOP_COUNT_INDEX]].size(); ++checkGirdPosIterator)
            {
                int y = mstCheckGridPos[testNumber[TEST_INDEX_NUMBERS::TEST_SHINE_GRID_LOOP_COUNT_INDEX]][checkGirdPosIterator].y;
                int x = mstCheckGridPos[testNumber[TEST_INDEX_NUMBERS::TEST_SHINE_GRID_LOOP_COUNT_INDEX]][checkGirdPosIterator].x;
                if (mstMapObjectGridData[y][x].ShineAreaCheckDatas.size() > 0)
                {
                    std::string shineAreaIndexNumber = std::to_string(x) + ", " + std::to_string(y) + "\n";
                    for (int i = 0; i < mstMapObjectGridData[y][x].ShineAreaCheckDatas.size(); ++i)
                    {
                        if (testNumber[TEST_INDEX_NUMBERS::TEST_SHINE_GRID_SHINE_AREA_INDEX] != mstMapObjectGridData[y][x].ShineAreaCheckDatas[i].ShineAreaIndex)
                        {
                            continue;
                        }
                        const Vector2_Int centerAdjustment = Vector2_Int((ONE_GRID_SIZE_X * 0.5f), (ONE_GRID_SIZE_Y * 0.5f));
                        DrawLine(
                            (ONE_GRID_SIZE_X * x) + centerAdjustment.x + i, (ONE_GRID_SIZE_Y * y) + centerAdjustment.y + i,
                            (ONE_GRID_SIZE_X * mstMapObjectGridData[y][x].ShineAreaCheckDatas[i].CheckGridPos.x) + centerAdjustment.x + i, (ONE_GRID_SIZE_Y * mstMapObjectGridData[y][x].ShineAreaCheckDatas[i].CheckGridPos.y) + centerAdjustment.y + i,
                            GetDebugColor(mnDrawMode[drawModeIndex] + mstMapObjectGridData[y][x].ShineAreaCheckDatas[i].ShineAreaIndex));
                        shineAreaIndexNumber += std::to_string(mstMapObjectGridData[y][x].ShineAreaCheckDatas[i].ShineAreaIndex) + "��(" + std::to_string(mstMapObjectGridData[y][x].ShineAreaCheckDatas[i].CheckGridPos.x) + ", " + std::to_string(mstMapObjectGridData[y][x].ShineAreaCheckDatas[i].CheckGridPos.y) + ")\n";
                    }
                    if (shineAreaIndexNumber == (std::to_string(x) + ", " + std::to_string(y) + "\n"))
                    {
                        continue;
                    }
                        
                    DrawBox(ONE_GRID_SIZE_X * mstCheckGridPos[testNumber[TEST_INDEX_NUMBERS::TEST_SHINE_GRID_LOOP_COUNT_INDEX]][checkGirdPosIterator].x,       ONE_GRID_SIZE_Y * mstCheckGridPos[testNumber[TEST_INDEX_NUMBERS::TEST_SHINE_GRID_LOOP_COUNT_INDEX]][checkGirdPosIterator].y,
                            ONE_GRID_SIZE_X * (mstCheckGridPos[testNumber[TEST_INDEX_NUMBERS::TEST_SHINE_GRID_LOOP_COUNT_INDEX]][checkGirdPosIterator].x + 1), ONE_GRID_SIZE_Y * (mstCheckGridPos[testNumber[TEST_INDEX_NUMBERS::TEST_SHINE_GRID_LOOP_COUNT_INDEX]][checkGirdPosIterator].y + 1),
                            GetDebugColor(mnDrawMode[drawModeIndex]),
                            FALSE);
                    DrawString(ONE_GRID_SIZE_X * x, ONE_GRID_SIZE_Y * y, shineAreaIndexNumber.c_str(), GetDebugColor(mnDrawMode[drawModeIndex]));
                }
            }
            int maxShineAreaIndex = 0;
            for (int y = 0; y < MAP_ARRAY_SIZE_Y; ++y)
            {
                for (int x = 0; x < MAP_ARRAY_SIZE_X; ++x)
                {
                    if (mstMapObjectGridData[y][x].ShineAreaCheckDatas.size() > 0)
                    {
                        for (int i = 0; i < mstMapObjectGridData[y][x].ShineAreaCheckDatas.size(); ++i)
                        {
                            if (maxShineAreaIndex < mstMapObjectGridData[y][x].ShineAreaCheckDatas[i].ShineAreaIndex)
                            {
                                maxShineAreaIndex = mstMapObjectGridData[y][x].ShineAreaCheckDatas[i].ShineAreaIndex;
                            }
                        }
                    }
                }
            }
            if (maxShineAreaIndex < testNumber[TEST_INDEX_NUMBERS::TEST_SHINE_GRID_SHINE_AREA_INDEX])
            {
                testNumber[TEST_INDEX_NUMBERS::TEST_SHINE_GRID_SHINE_AREA_INDEX] = maxShineAreaIndex;
            }
        }
            break;
        
        case SHINE_DRAW_MODE::OTHER_SHINE_AREA_CHECK_GRID_DRAW_MODE:
            for (int y = 0; y < MAP_ARRAY_SIZE_Y; ++y)
            {
                for (int x = 0; x < MAP_ARRAY_SIZE_X; ++x)
                {
                    if (mstMapObjectGridData[y][x].ShineChangeDatas.size() > 0)
                    {
                        std::string shineAreaIndexNumber = std::to_string(x) + ", " + std::to_string(y) + "\n";
                        for (int i = 0; i < mstMapObjectGridData[y][x].ShineChangeDatas.size(); ++i)
                        {
                            const Vector2_Int centerAdjustment = Vector2_Int((ONE_GRID_SIZE_X * 0.5f), (ONE_GRID_SIZE_Y * 0.5f));
                            DrawLine(
                                (ONE_GRID_SIZE_X * x) + centerAdjustment.x + i, (ONE_GRID_SIZE_Y * y) + centerAdjustment.y + i,
                                (ONE_GRID_SIZE_X * mstMapObjectGridData[y][x].ShineChangeDatas[i].CheckGridPos.x) + centerAdjustment.x + i, (ONE_GRID_SIZE_Y * mstMapObjectGridData[y][x].ShineChangeDatas[i].CheckGridPos.y) + centerAdjustment.y + i,
                                GetDebugColor(mnDrawMode[drawModeIndex] + mstMapObjectGridData[y][x].ShineChangeDatas[i].ShineAreaIndex));
                                
                            shineAreaIndexNumber += std::to_string(mstMapObjectGridData[y][x].ShineChangeDatas[i].ShineAreaIndex) + "��(" + std::to_string(mstMapObjectGridData[y][x].ShineChangeDatas[i].CheckGridPos.x) + ", " + std::to_string(mstMapObjectGridData[y][x].ShineChangeDatas[i].CheckGridPos.y) + ")\n";
                        }
                        DrawBox(ONE_GRID_SIZE_X * x,       ONE_GRID_SIZE_Y * y,
                                ONE_GRID_SIZE_X * (x + 1), ONE_GRID_SIZE_Y * (y + 1),
                                GetDebugColor(mnDrawMode[drawModeIndex]),
                                FALSE);
                        DrawString(ONE_GRID_SIZE_X * x, ONE_GRID_SIZE_Y * y, shineAreaIndexNumber.c_str(), GetDebugColor(mnDrawMode[drawModeIndex]));
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
        
        case SHINE_DRAW_MODE::WALL_LINE_DRAW_MODE:
            for (const std::vector<SHINE_AREA_END_POSITION>& wallLinePointDatas : mstDebugWallLinePointDrawData)
            {
                for (const SHINE_AREA_END_POSITION& wallLinePointData : wallLinePointDatas)
                {
                    DrawLine(
                        wallLinePointData.linePos1.x, wallLinePointData.linePos1.y,
                        wallLinePointData.linePos2.x, wallLinePointData.linePos2.y,
                        GetDebugColor(mnDrawMode[drawModeIndex]),
                        TRUE
                    );
                }
            }
            break;
        
        case SHINE_DRAW_MODE::WALL_LINE_SINGLE_LOOP_DRAW_MODE:
            if (mstDebugWallLinePointDrawData.size() <= 0)
            {
                break;
            }
            if (mstDebugWallLinePointDrawData.size() <= testNumber[TEST_INDEX_NUMBERS::TEST_SHINE_WALL_LOOP_INDEX])
            {
                testNumber[TEST_INDEX_NUMBERS::TEST_SHINE_WALL_LOOP_INDEX] = mstDebugWallLinePointDrawData.size() - 1;
            }
            for (const SHINE_AREA_END_POSITION& wallLinePointData : mstDebugWallLinePointDrawData[testNumber[TEST_INDEX_NUMBERS::TEST_SHINE_WALL_LOOP_INDEX]])
            {
                DrawLine(
                    wallLinePointData.linePos1.x, wallLinePointData.linePos1.y,
                    wallLinePointData.linePos2.x, wallLinePointData.linePos2.y,
                    GetDebugColor(mnDrawMode[drawModeIndex]),
                    TRUE
                );
            }
            break;
        
        case SHINE_DRAW_MODE::WALL_LINE_SINGLE_AND_INDEX_NUMBER_DRAW_MODE:
        {
            if (mstDebugWallLinePointDrawData.size() <= 0)
            {
                break;
            }
            if (mstDebugWallLinePointDrawData.size() <= testNumber[TEST_INDEX_NUMBERS::TEST_SHINE_WALL_LOOP_INDEX])
            {
                testNumber[TEST_INDEX_NUMBERS::TEST_SHINE_WALL_LOOP_INDEX] = mstDebugWallLinePointDrawData.size() - 1;
            }
            if (mstDebugWallLinePointDrawData[testNumber[TEST_INDEX_NUMBERS::TEST_SHINE_WALL_LOOP_INDEX]].size() <= 0)
            {
                break;
            }
            if (mstDebugWallLinePointDrawData[testNumber[TEST_INDEX_NUMBERS::TEST_SHINE_WALL_LOOP_INDEX]].size() <= testNumber[TEST_INDEX_NUMBERS::TEST_SHINE_WALL_NUMBER_INDEX])
            {
                testNumber[TEST_INDEX_NUMBERS::TEST_SHINE_WALL_NUMBER_INDEX] = mstDebugWallLinePointDrawData[testNumber[TEST_INDEX_NUMBERS::TEST_SHINE_WALL_LOOP_INDEX]].size() - 1;
            }
            const SHINE_AREA_END_POSITION& wallLinePointData = mstDebugWallLinePointDrawData[testNumber[TEST_INDEX_NUMBERS::TEST_SHINE_WALL_LOOP_INDEX]][testNumber[TEST_INDEX_NUMBERS::TEST_SHINE_WALL_NUMBER_INDEX]];
            {
                DrawLine(
                    wallLinePointData.linePos1.x, wallLinePointData.linePos1.y,
                    wallLinePointData.linePos2.x, wallLinePointData.linePos2.y,
                    GetDebugColor(mnDrawMode[drawModeIndex]),
                    TRUE
                );
                DrawString(wallLinePointData.linePos1.x, wallLinePointData.linePos1.y, std::to_string(wallLinePointData.shineDirectionIndex).c_str(), GetDebugColor(mnDrawMode[drawModeIndex]));
            }
        }
            break;
        
        case SHINE_DRAW_MODE::SHINE_CHECK_DATA_LINE_DRAW_MODE:
        {
            for (int y = 0; y < MAP_ARRAY_SIZE_Y; ++y)
            {
                for (int x = 0; x < MAP_ARRAY_SIZE_X; ++x)
                {
                    if (mstMapObjectGridData[y][x].ShineAreaCheckDatas.size() > 0)
                    {
                        for (int i = 0; i < mstMapObjectGridData[y][x].ShineAreaCheckDatas.size(); ++i)
                        {
                            const Vector2_Int centerAdjustment = Vector2_Int((ONE_GRID_SIZE_X * 0.5f), (ONE_GRID_SIZE_Y * 0.5f));
                            DrawLine(
                                (ONE_GRID_SIZE_X * x) + centerAdjustment.x + i, (ONE_GRID_SIZE_Y * y) + centerAdjustment.y + i,
                                (ONE_GRID_SIZE_X * mstMapObjectGridData[y][x].ShineAreaCheckDatas[i].CheckGridPos.x) + centerAdjustment.x + i, (ONE_GRID_SIZE_Y * mstMapObjectGridData[y][x].ShineAreaCheckDatas[i].CheckGridPos.y) + centerAdjustment.y + i,
                                GetDebugColor(mnDrawMode[drawModeIndex] + mstMapObjectGridData[y][x].ShineAreaCheckDatas[i].ShineAreaIndex));
                        }
                    }
                }
            }
        }
            break;
        }
    }

    mpShineObject->Draw();
}

// �w��̃O���b�h���ɕ␳�����l��Ԃ�
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

// ���̈�̍쐬
void ShineManager::CreateShineArea()
{
    mstSheineTriangles.clear();

    // ���̈�����Z�b�g
    for (int y = 0; y < MAP_ARRAY_SIZE_Y; ++y)
    {
        for (int x = 0; x < MAP_ARRAY_SIZE_X; ++x)
        {
            mstMapObjectGridData[y][x].LitFlag = false;
            mstMapObjectGridData[y][x].DebugDrawLiteFlag = false;
            mstMapObjectGridData[y][x].ConfiguredShineAreaIndex.clear();
            mstMapObjectGridData[y][x].ShineAreaIndex.clear();
            mstMapObjectGridData[y][x].ShineChangeDatas.clear();
            mstMapObjectGridData[y][x].ShineAreaCheckDatas.clear();
        }
    }

    // �����̈ʒu��ݒ�
    mstShinePos = mpShineObject->GetPosition();

    // ���������݂���O���b�h
    mstShineGridPos = Vector2_Int(static_cast<int>(mstShinePos.x / ONE_GRID_SIZE_X), static_cast<int>(mstShinePos.y / ONE_GRID_SIZE_Y));

    // �}�b�v�O�Ȃ珈�����Ȃ�
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

    // �O���b�h�̒T��
    CheckShineGrid();
}


// �O���b�h�̒T��
void ShineManager::CheckShineGrid()
{
    // ��������O���b�h
    std::queue<Vector2_Int> nextCheckShinePos;

    // �����̃O���b�h����J�n
    nextCheckShinePos.push(mstShineGridPos);
    
    // �����̃O���b�h�͕K�����̈�Ɋ܂߂�
    mstMapObjectGridData[mstShineGridPos.y][mstShineGridPos.x].LitFlag = true;
    mstMapObjectGridData[mstShineGridPos.y][mstShineGridPos.x].DebugDrawLiteFlag = true;

    // ���[�v�𐔂���
    int loopCount = 0;
    mstMapObjectGridData[mstShineGridPos.y][mstShineGridPos.x].LitLoopNumber = 0;

    // �ݒ肵�����C�g�̏��Ԃ�ݒ肷��
    int setLitNumber = 0;
    mstMapObjectGridData[mstShineGridPos.y][mstShineGridPos.x].SetLitNumber = 0;

    // INPROGRESS:_ ������ɕ����Ď���
    std::vector<SHINE_DIRECTION> shineDirections;
    shineDirections.push_back(mpShineObject->GetShineDirection());


    // ���̃G���A���L�^����
    mstShineAreaResult.clear();
    mstShineAreaResult.push_back(shineDirections);

    // �m�F����O���b�h������
    mstCheckGridPos.clear();

    // �ǂƂȂ郉�C����񏉊���
    mstDebugWallLinePointDrawData.clear();

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

        // ���񒲂ׂ�O���b�h�����o��
        std::queue<Vector2_Int> nowCheckShinePos;
        nowCheckShinePos.swap(nextCheckShinePos);

        // ����̒T�����Ɍ���������Q��
        std::stack<BLOCK_POS_DATA> blockPoss;

        ++loopCount;

        // After a shine area split, each grid must look up shineDirections by itself.
        while (0 < nowCheckShinePos.size())
        {
            Vector2_Int checkShinePos = nowCheckShinePos.front();
            nowCheckShinePos.pop();
            if (!mstMapObjectGridData[checkShinePos.y][checkShinePos.x].LitFlag)
            {
                mstMapObjectGridData[checkShinePos.y][checkShinePos.x].ConfiguredShineAreaIndex.clear();
                continue;
            }

            for (int shineDirectionsIndex = 0; shineDirectionsIndex < static_cast<int>(shineDirections.size()); ++shineDirectionsIndex)
            {
                std::vector<Vector2_Int> ShineGridPositions = GetShineGridPositions(checkShinePos, shineDirections[shineDirectionsIndex]);

                if (ShineGridPositions.size() <= 0)
                {
                    continue;
                }

                for (const Vector2_Int& checkPos : ShineGridPositions)
                {
                    SHINE_AREA_CHECK_DATA setShineAreaCheckData;
                    setShineAreaCheckData.ShineAreaIndex = shineDirectionsIndex;
                    setShineAreaCheckData.CheckGridPos = checkPos;
                    mstMapObjectGridData[checkShinePos.y][checkShinePos.x].ShineAreaCheckDatas.push_back(setShineAreaCheckData);

                    if (IsOutsideShineStage(checkPos))
                    {
                        continue;
                    }

                    bool checkConfiguredContinueFlag = false;
                    for (const int& checkConfigured : mstMapObjectGridData[checkPos.y][checkPos.x].ConfiguredShineAreaIndex)
                    {
                        if (checkConfigured == shineDirectionsIndex)
                        {
                            checkConfiguredContinueFlag = true;
                            break;
                        }
                    }
                    if (checkConfiguredContinueFlag)
                    {
                        continue;
                    }

                    switch (JudgeGrid(checkPos, shineDirections, shineDirectionsIndex))
                    {
                    case SHINE_GRID_TYPE::NOT_SHINE_GRID:
                    {
                        SHINE_AREA_CHECK_DATA setShineChangeData;
                        setShineChangeData.ShineAreaIndex = shineDirectionsIndex;
                        setShineChangeData.CheckGridPos = checkPos;
                        mstMapObjectGridData[checkShinePos.y][checkShinePos.x].ShineChangeDatas.push_back(setShineChangeData);
                    }
                        break;

                    case SHINE_GRID_TYPE::SHINE_GRID:
                    {
                        mstMapObjectGridData[checkPos.y][checkPos.x].ConfiguredShineAreaIndex.push_back(shineDirectionsIndex);
                        if (!mstMapObjectGridData[checkPos.y][checkPos.x].LitFlag)
                        {
                            nextCheckShinePos.push(checkPos);
                            mstMapObjectGridData[checkPos.y][checkPos.x].LitFlag = true;
                            mstMapObjectGridData[checkPos.y][checkPos.x].DebugDrawLiteFlag = true;
                            mstMapObjectGridData[checkPos.y][checkPos.x].LitLoopNumber = loopCount;
                            ++setLitNumber;
                            mstMapObjectGridData[checkPos.y][checkPos.x].SetLitNumber = setLitNumber;
                        }
                    }
                        break;

                    case SHINE_GRID_TYPE::SHINE_AND_OBJECT_GRID:
                    {
                        BLOCK_POS_DATA blockPos;
                        blockPos.BlockPos = checkPos;
                        blockPos.ArrayIndex = shineDirectionsIndex;
                        blockPoss.push(blockPos);
                        mstMapObjectGridData[checkPos.y][checkPos.x].ConfiguredShineAreaIndex.push_back(shineDirectionsIndex);
                        mstMapObjectGridData[checkPos.y][checkPos.x].ShineAreaIndex.push_back(shineDirectionsIndex);

                        if (!mstMapObjectGridData[checkPos.y][checkPos.x].LitFlag)
                        {
                            nextCheckShinePos.push(checkPos);
                            mstMapObjectGridData[checkPos.y][checkPos.x].LitFlag = true;
                            mstMapObjectGridData[checkPos.y][checkPos.x].DebugDrawLiteFlag = true;
                            mstMapObjectGridData[checkPos.y][checkPos.x].LitLoopNumber = loopCount;
                            ++setLitNumber;
                            mstMapObjectGridData[checkPos.y][checkPos.x].SetLitNumber = setLitNumber;
                        }
                    }
                        break;
                    }
                }
            }
        }

        // �����Ղ镨�̏���
        ShineBlockProcess(blockPoss, nextCheckShinePos, shineDirections);

        // ���T������O���b�h�̒���������͂��ĂȂ��O���b�h�𔻒�
        UpdateGridLightState(nextCheckShinePos, shineDirections);

        // ���̈���L�^
        mstShineAreaResult.push_back(shineDirections);
    }

    // ��ʂ̊p�|�W�V����
    const Vector2 displayCornerPosition[ANGLE_NUMBER::ANGLE_NUMBER_DISPLAY_MAX] =
    {
        Vector2(0.0f,       0.0f),
        Vector2(0.0f,       MAP_SIZE_Y), 
        Vector2(MAP_SIZE_X, 0.0f), 
        Vector2(MAP_SIZE_X, MAP_SIZE_Y)
    };
    // �������猩�ĉ�ʂ̊p�A���O��
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

        // ���捶�E�̕����ƌ�_���Z�o
        if (!GetShineDirectionIntersection(shineDirectionsLeftAndRight, shineAnglesLeftAndRight, shineAngleNumbers, intersectionPositions, displayCornerAngles, displayCornerPosition))
        {
            continue;
        }

        // �p���܂߂�Ȃ�p���`��p�O�p�ɒǉ�
        AddDisplayCornerToDrawTriangle(intersectionPositions, shineAngleNumbers, displayCornerPosition);
    }

    
#ifdef _DEBUG
        DEBUG::SaveText("END\n\n", DEBUG::DEBUG_MAP_TYPE::DEBUG_SHINE_POS);
#endif
}

bool IsRayIntersectRect(const Vector2& rayOrigin, const Vector2& rayDirection, float left, float right, float top, float bottom);

// �O���b�h�����͈͓�������
SHINE_GRID_TYPE ShineManager::JudgeGrid(const Vector2_Int& gridPos, const std::vector<SHINE_DIRECTION>& shineDirections, int shineDirectionsIndex)
{
    // ���̕���
    SHINE_DIRECTION shineDirection = shineDirections[shineDirectionsIndex];

    Vector2 direction1 = shineDirection.shineDirectionLeft;

    Vector2 direction2 = shineDirection.shineDirectionRight;

    // 2�{�̕����x�N�g���̊O��
    const float directionCross =
        direction1.x * direction2.y -
        direction1.y * direction2.x;

    // �O���b�h�̎l���̍��W
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

    // �l���̂����ꂩ�����͈͓�������
    for (const Vector2& corner : gridCorners)
    {
        // ��������O���b�h�̊p�ւ̕���
        Vector2 toCorner = corner - mstShinePos;

        // �����Ɗp�������ʒu�Ȃ���͈͓�
        if (toCorner.x == 0.0f &&
            toCorner.y == 0.0f)
        {
            if (mstMapObjectGridData[gridPos.y][gridPos.x].LinePoss.size() > 0)
            {
                return SHINE_GRID_TYPE::SHINE_AND_OBJECT_GRID;
            }
            return SHINE_GRID_TYPE::SHINE_GRID;
        }

        // 1�{�ڂ̕����Ƃ̊O��
        const float cross1 =
            direction1.x * toCorner.y -
            direction1.y * toCorner.x;

        // 2�{�ڂ̕����Ƃ̊O��
        const float cross2 =
            direction2.x * toCorner.y -
            direction2.y * toCorner.x;

        bool isShineArea = false;

        // 2�{�̕����x�N�g���̊Ԃɂ��邩����
        if (directionCross < 0.0f)
        {
            // ���v���
            isShineArea =
                cross1 <= 0.0f &&
                cross2 >= 0.0f;
        }
        else
        {
            // �����v���
            isShineArea =
                cross1 >= 0.0f &&
                cross2 <= 0.0f;
        }

        // ���͈͓�
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

    // ���͈͊O
    return SHINE_GRID_TYPE::NOT_SHINE_GRID;
}

// �O���b�h���Ɍ��݂̌��̈�ȊO�̌��̈悪���邩����
bool ShineManager::HasOtherShineAreaInGrid(const Vector2_Int& gridPos, const std::vector<SHINE_DIRECTION>& shineDirections, int shineDirectionsIndex)
{
    // ���݂̌��̈�̎����璲�ׂ�
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

        // �O���b�h�̎l���̍��W
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

        // �l���̂����ꂩ�����͈͓�������
        for (const Vector2& corner : gridCorners)
        {
            Vector2 toCorner = corner - mstShinePos;

            // �����Ɗp�������ʒu�Ȃ���͈͓�
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
                // ���v���
                isShineArea =
                    cross1 <= 0.0f &&
                    cross2 >= 0.0f;
            }
            else
            {
                // �����v���
                isShineArea =
                    cross1 >= 0.0f &&
                    cross2 <= 0.0f;
            }

            if (isShineArea)
            {
                return true;
            }
        }

        // ���͈͂̋��E�����O���b�h��ʉ߂��Ă��邩����
        if (IsRayIntersectRect(mstShinePos, direction1, left, right, top, bottom) || IsRayIntersectRect(mstShinePos, direction2, left, right, top, bottom))
        {
            return true;
        }
    }

    return false;
}

bool IsAngleBetween(float targetAngle, float leftAngle, float rightAngle);

// �����Ղ���̂��m�F���A����ɉ������������s��
void ShineManager::ShineBlockProcess(std::stack<BLOCK_POS_DATA>& blockPoss, std::queue<Vector2_Int>& nextCheckShinePos, std::vector<SHINE_DIRECTION>& shineDirections)
{
    // �Ղ��Ă���ꏊ��T��
    while (!blockPoss.empty() && !shineDirections.empty())
    {
        BLOCK_POS_DATA blockPos = blockPoss.top();
        blockPoss.pop();

        if (blockPos.ArrayIndex >= shineDirections.size())
        {
            continue;
        }

        // TODO:_ �킴�킴����w���Ȃ��Ă��o�������������ꂶ��قƂ�Ǎ����Ȃ����������������
        std::vector<LINE_POS> linePoss = mstMapObjectGridData[blockPos.BlockPos.y][blockPos.BlockPos.x].LinePoss;
        std::sort(linePoss.begin(), linePoss.end(),
                [this](const LINE_POS& a, const LINE_POS& b)
                {
                    // --- 1. ���̍��[ (leftAngle) ����Ƃ������v��葊�Ίp�x���v�Z ---
                    const float leftAngle = mpShineObject->GetShineDirection().leftAngle;

                    // leftAngle �� 0 �Ƃ������v�������ւ̑��Ίp�x (0 �` 2��) ���Z�o����w���p�[�֐�
                    auto GetClockwiseAngleFromLeft = [](float angle, float baseLeft) {
                        static constexpr float TWO_PI = 6.28318530717958647692f;
                        float diff = std::fmod(angle - baseLeft, TWO_PI);
                        if (diff < 0.0f) diff += TWO_PI;
                        return diff; // 0�����[�A�l���傫���قǉE��
                    };

                    // a �� 2 �_�̃A���O�� (��������̑��Ίp�x)
                    const float aAngle1 = GetClockwiseAngleFromLeft(
                        std::atan2f(a.linePos1.y - mstShinePos.y, a.linePos1.x - mstShinePos.x), leftAngle);
                    const float aAngle2 = GetClockwiseAngleFromLeft(
                        std::atan2f(a.linePos2.y - mstShinePos.y, a.linePos2.x - mstShinePos.x), leftAngle);

                    // b �� 2 �_�̃A���O�� (��������̑��Ίp�x)
                    const float bAngle1 = GetClockwiseAngleFromLeft(
                        std::atan2f(b.linePos1.y - mstShinePos.y, b.linePos1.x - mstShinePos.x), leftAngle);
                    const float bAngle2 = GetClockwiseAngleFromLeft(
                        std::atan2f(b.linePos2.y - mstShinePos.y, b.linePos2.x - mstShinePos.x), leftAngle);

                    // �e�����̉E�[�A���O�� (�p�x���傫���قǉE��)
                    const float aMaxAngle = max(aAngle1, aAngle2);
                    const float bMaxAngle = max(bAngle1, bAngle2);

                    // �y�D�揇�� 1�z���W���A���O�������ĉE�ɂ�����̂�D��i���������_���̌덷�z���p�C�v�V�����t���j
                    constexpr float EPSILON_ANGLE = 0.0001f;
                    if (std::abs(aMaxAngle - bMaxAngle) > EPSILON_ANGLE)
                    {
                        return aMaxAngle > bMaxAngle; // �E�ɂ�����i�A���O�����傫�����j��O�ɔz�u
                    }

                    // --- 2 & 3. �����ɂ���r�����i�A���O���������ꍇ�̂ݎ��s�j ---
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

                    // �y�D�揇�� 2�z���W�����Č��ɋ߂����_�������
                    const float aNear = min(aDistance1, aDistance2);
                    const float bNear = min(bDistance1, bDistance2);

                    const int aNearInt = static_cast<int>(aNear);
                    const int bNearInt = static_cast<int>(bNear);

                    if (aNearInt != bNearInt)
                    {
                        return aNearInt < bNearInt;
                    }

                    // �y�D�揇�� 3�z�߂����������Ȃ�A�����������ċ߂���
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
    }

    mstSettingDebugWallLineResult.clear();

    auto remapGridShineAreaIndices = [this](int shineIndex, int newCount)
    {
        if (newCount == 1)
        {
            return;
        }

        for (int y = 0; y < MAP_ARRAY_SIZE_Y; ++y)
        {
            for (int x = 0; x < MAP_ARRAY_SIZE_X; ++x)
            {
                auto remapList = [shineIndex, newCount](std::vector<int>& indices)
                {
                    if (newCount <= 0)
                    {
                        std::vector<int> remapped;
                        remapped.reserve(indices.size());
                        for (int index : indices)
                        {
                            if (index == shineIndex)
                            {
                                continue;
                            }
                            remapped.push_back(index > shineIndex ? index - 1 : index);
                        }
                        indices.swap(remapped);
                        return;
                    }

                    const int delta = newCount - 1;
                    for (int& index : indices)
                    {
                        if (index > shineIndex)
                        {
                            index += delta;
                        }
                    }
                };

                remapList(mstMapObjectGridData[y][x].ConfiguredShineAreaIndex);
                remapList(mstMapObjectGridData[y][x].ShineAreaIndex);
            }
        }
    };

    for (int i = static_cast<int>(shineDirections.size()) - 1; i >= 0; --i)
    {
        std::vector<SHINE_DIRECTION> newShineDirections = ProcessShineAreaEndPointCandidates(i, shineDirections[i]);

        if (newShineDirections.size() != 1)
        {
            shineDirections.erase(shineDirections.begin() + i);
            shineDirections.insert(shineDirections.begin() + i, newShineDirections.begin(), newShineDirections.end());
            remapGridShineAreaIndices(i, static_cast<int>(newShineDirections.size()));
        }
        else
        {
            shineDirections[i] = newShineDirections[0];
        }
    }

    mstLightAreaEndPoint.clear();

    mstDebugWallLinePointDrawData.push_back(mstSettingDebugWallLineResult);
}

// leftAngle�i���̍��[�j����u0.0�v�Ƃ������v�������ւ̑��Ίp�x�i0 �` 2�΁j���Z�o����
static float GetClockwiseAngleFromLeft(float angle, float baseLeft)
{
    float diff = std::fmod(angle - baseLeft, DX_TWO_PI_F);
    if (diff < 0.0f) diff += DX_TWO_PI_F;
    return diff;
}
static float GetSignedAngleFromLeft(float angle, float baseLeft)
{
    float diff = std::fmod(angle - baseLeft, DX_TWO_PI_F);

    if (diff > DX_PI_F)
    {
        diff -= DX_TWO_PI_F;
    }
    else if (diff < -DX_PI_F)
    {
        diff += DX_TWO_PI_F;
    }

    return diff;
}

// ����̏I�[����o�^����
void ShineManager::RegisterShineAreaEndPointCandidate(LINE_POS blockLinePos, const BLOCK_POS_DATA& blockPos, std::vector<SHINE_DIRECTION>& shineDirections)
{
    // ���ݏ������Ă������ɑΉ�������������擾
    const SHINE_DIRECTION& currentShineDir =
        shineDirections[blockPos.ArrayIndex];

    // ��Q���̍��[�E�E�[��������ւ̊p�x�����߂�
    const float blockLeftAngle =
        GetAngleToPoint(mstShinePos, blockLinePos.linePos1);

    const float blockRightAngle =
        GetAngleToPoint(mstShinePos, blockLinePos.linePos2);

    // ����̍��[����Ƃ������Ίp�x�����߂�
    const float blockLeftRel =
        GetSignedAngleFromLeft(
            blockLeftAngle,
            currentShineDir.leftAngle);

    const float blockRightRel =
        GetSignedAngleFromLeft(
            blockRightAngle,
            currentShineDir.leftAngle);

    // ���݂̌���̊p�x��
    const float totalShineWidth =
        GetSignedAngleFromLeft(
            currentShineDir.rightAngle,
            currentShineDir.leftAngle);

    // ���S�Ɍ���̊O��
    const bool isOutsideLeft =
        blockLeftRel < 0.0f &&
        blockRightRel < 0.0f;

    const bool isOutsideRight =
        blockLeftRel > totalShineWidth &&
        blockRightRel > totalShineWidth;

    if (isOutsideLeft || isOutsideRight)
    {
        return;
    }

    // ��Q��������̍��[���Ղ��Ă��邩����
    const bool crossesLeftEdge =
    (blockLeftRel < 0.0f && blockRightRel >= 0.0f) ||
    (blockRightRel < 0.0f && blockLeftRel >= 0.0f);

    // ��Q��������̉E�[���Ղ��Ă��邩����
    const bool crossesRightEdge =
    (blockLeftRel < totalShineWidth && blockRightRel >= totalShineWidth) ||
    (blockRightRel < totalShineWidth && blockLeftRel >= totalShineWidth);

    // ����̍��E�[���Ղ��Ă���ꍇ
    if (crossesLeftEdge || crossesRightEdge)
    {
        const float RAY_LENGTH = 10000.0f;
     
        // ����̍��[���Ղ��Ă���ꍇ
        if (crossesLeftEdge)
        {
            const Vector2 leftRayEnd =
            {
                mstShinePos.x +
                    currentShineDir.shineDirectionLeft.x * RAY_LENGTH,

                mstShinePos.y +
                    currentShineDir.shineDirectionLeft.y * RAY_LENGTH
            };

            Vector2 intersection;

            if (GetIntersection(
                    mstShinePos,
                    leftRayEnd,
                    blockLinePos.linePos1,
                    blockLinePos.linePos2,
                    intersection))
            {
                // ���[���O���ɂ��������_�֒u��������
                if (blockLeftRel < 0.0f)
                {
                    blockLinePos.linePos1 = intersection;
                }
                else
                {
                    blockLinePos.linePos2 = intersection;
                }
            }
        }
        // ����̉E�[���Ղ��Ă���ꍇ
       if (crossesRightEdge)
        {
            const Vector2 rightRayEnd =
            {
                mstShinePos.x +
                    currentShineDir.shineDirectionRight.x * RAY_LENGTH,

                mstShinePos.y +
                    currentShineDir.shineDirectionRight.y * RAY_LENGTH
            };
            Vector2 intersection;

            if (GetIntersection(
                    mstShinePos,
                    rightRayEnd,
                    blockLinePos.linePos1,
                    blockLinePos.linePos2,
                    intersection))
            {
                // �E�[���O���ɂ��������_�֒u��������
                if (blockLeftRel > totalShineWidth)
                {
                    blockLinePos.linePos1 = intersection;
                }
                else
                {
                    blockLinePos.linePos2 = intersection;
                }
            }
        }

        // ��������̏�ł͕ύX�����A
        // ��_�ɂ���Ē���������Q����
        // ����̏I�[���Ƃ��ēo�^����
        mstLightAreaEndPoint.push_back(SHINE_AREA_END_POSITION(blockLinePos, blockPos.ArrayIndex));
    }
    // ���E�ǂ���̒[���Ղ��Ă��Ȃ��ꍇ
    else
    {
        // ����̓����ŏ�Q���ɎՂ��Ă����ԁB
        // ��Ō���̏I�[�����肷�邽�߂̌��Ƃ��ēo�^����B
        mstLightAreaEndPoint.push_back(SHINE_AREA_END_POSITION(blockLinePos, blockPos.ArrayIndex));
    }
}

// �o�^���ꂽ����I�[�����g�p���āA��������A�����������`��p�O�p�`�ɓo�^����
std::vector<SHINE_DIRECTION> ShineManager::ProcessShineAreaEndPointCandidates(int shineIndex, const SHINE_DIRECTION& shineDirections)
{
    // ���݂̌��̈�
    std::vector<SHINE_DIRECTION> newShineDirections;
    newShineDirections.push_back(shineDirections);

    // ����������̎O�p�`���
    std::vector<SHINE_TRIANGLE> savedTriangle;

    // �ΏۂƂȂ�I�[��������
    for (int lightIterator = (mstLightAreaEndPoint.size() - 1); lightIterator >= 0; --lightIterator)
    {
        const SHINE_AREA_END_POSITION endPoint = mstLightAreaEndPoint[lightIterator];
        if (endPoint.shineDirectionIndex != shineIndex)
        {
            continue;
        }
        // ��������I�[�����폜
        mstLightAreaEndPoint.erase(mstLightAreaEndPoint.begin() + lightIterator);

        mstSettingDebugWallLineResult.push_back(endPoint);
        
        // �O�p�ɓo�^
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

        /*�@ �����̗��[���������猩���p�x�ɕϊ�*/
        const float lineAngle1 =
            GetAngleToPoint(mstShinePos, endPoint.linePos1);

        const float lineAngle2 =
            GetAngleToPoint(mstShinePos, endPoint.linePos2);

        /*�A ���݂̌��̈�ɑ΂��āA���̐������Ղ�p�x�͈͂����߂�*/
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

        /*�B �Ղ��镔����newShineDirections ����폜�E����*/
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

            // ���݂̌��̈�ƎՕ��͈͂̏d�Ȃ�
            const float overlapLeft =
                max(currentLeftAngle, blockLeftAngle);

            const float overlapRight =
                min(currentRightAngle, blockRightAngle);

            // �d�Ȃ��Ă��Ȃ�
            if (overlapRight <= overlapLeft)
            {
                splitShineDirections.push_back(currentShineDirection);
                continue;
            }

            // �����Ɏc����̈�
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

            // �E���Ɏc����̈�
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

    // �O�p�����
    {
    }

    // �O�p�o�^
    for (int i = 0; i < savedTriangle.size(); ++i)
    {
        //AddDrawTriangleData(savedTriangle[i]);
    }

    return newShineDirections;
}

// �}�b�v�O����
bool ShineManager::IsOutsideShineStage(const Vector2_Int& gridPos)
{
    if (gridPos.x < 0 || gridPos.x >= MAP_ARRAY_SIZE_X ||
        gridPos.y < 0 || gridPos.y >= MAP_ARRAY_SIZE_Y)
    {
        return true;
    }

    return false;
}


// �p�x targetAngle �� leftAngle ���� rightAngle �͈̔͂Ɋ܂܂�邩���肷��֐�
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
        // 0 / 2�� �̋��E���ׂ��ꍇ
        return target >= left || target <= right;
    }
}


static bool IsRayIntersectRect(const Vector2& rayOrigin, const Vector2& rayDirection, float left, float right, float top, float bottom)
{
    float tMin = 0.0f;
    float tMax = FLT_MAX;

    // X����
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

    // Y����
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

// �w�肵���O���b�h�Ɍ����ʂ��Ă��邩����
bool ShineManager::IsGridInsideShine(const Vector2_Int& gridPos, const SHINE_DIRECTION& shineDirection)
{
    const Vector2 shinePos = mpShineObject->GetPosition();

    const Vector2 leftDirection =
        shineDirection.shineDirectionLeft;

    const Vector2 rightDirection =
        shineDirection.shineDirectionRight;

    // ���E�̏Ǝ˕����̊O��
    const float directionCross =
        leftDirection.x * rightDirection.y -
        leftDirection.y * rightDirection.x;

    // �O���b�h�̎l�ӂ̍��W���Z�o
    const float left =
        static_cast<float>(gridPos.x * ONE_GRID_SIZE_X);

    const float right =
        left + static_cast<float>(ONE_GRID_SIZE_X);

    const float top =
        static_cast<float>(gridPos.y * ONE_GRID_SIZE_Y);

    const float bottom =
        top + static_cast<float>(ONE_GRID_SIZE_Y);

    // �O���b�h�̎l���̍��W
    const Vector2 corners[4] =
    {
        { left,  top },
        { right, top },
        { left,  bottom },
        { right, bottom }
    };

    for (const Vector2& corner : corners)
    {
        const Vector2 dirToCorner =
        {
            corner.x - shinePos.x,
            corner.y - shinePos.y
        };

        const float leftCross =
            leftDirection.x * dirToCorner.y -
            leftDirection.y * dirToCorner.x;

        const float rightCross =
            dirToCorner.x * rightDirection.y -
            dirToCorner.y * rightDirection.x;

        if (directionCross > 0.0f)
        {
            if (leftCross >= 0.0f &&
                rightCross >= 0.0f)
            {
                return true;
            }
        }
        else
        {
            if (leftCross <= 0.0f &&
                rightCross <= 0.0f)
            {
                return true;
            }
        }
    }

    return IsRayIntersectRect(shinePos, leftDirection, left, right, top, bottom) ||
           IsRayIntersectRect(shinePos, rightDirection, left, right, top, bottom);
}

std::vector<Vector2_Int> ShineManager::GetShineGridPositions(const Vector2_Int& nowCheckShinePos, const SHINE_DIRECTION& shineDirection)
{
    std::vector<Vector2_Int> shineGridPositions;

    // ���݃O���b�h���g�ɁA���̕����̌����ʂ��Ă��邩�m�F
    if (!IsGridInsideShine(nowCheckShinePos, shineDirection))
    {
        return {};
    }

    // �����̃��[���h�ʒu����яƎ˕����i���E�̌��E�p�x�j���擾
    const Vector2 shinePos = mpShineObject->GetPosition();
    const SHINE_DIRECTION shineDir = shineDirection;

    // ���E�̏Ǝ˕���
    const Vector2 leftDirection = shineDir.shineDirectionLeft;
    const Vector2 rightDirection = shineDir.shineDirectionRight;

    // ���E�̕����̊O��
    const float directionCross =
        leftDirection.x * rightDirection.y -
        leftDirection.y * rightDirection.x;

    // ����8�����̗אڃO���b�h�𒲂ׂ�
    for (int y = -1; y <= 1; ++y)
    {
        for (int x = -1; x <= 1; ++x)
        {
            if (x == 0 && y == 0)
            {
                continue;
            }

            const Vector2_Int nextPos =
            {
                nowCheckShinePos.x + x,
                nowCheckShinePos.y + y
            };

            // �O���b�h�Ɍ����ʂ��Ă���ꍇ�͑Ώ�
            if (IsGridInsideShine(nextPos, shineDirection))
            {
                shineGridPositions.push_back(nextPos);
            }
        }
    }

       // --- �\�[�g�����i���́u���[�v����ɂ��āA������E�֐��������񂳂���j ---
    std::sort(
            shineGridPositions.begin(),
            shineGridPositions.end(),
            [&](const Vector2_Int& lhs, const Vector2_Int& rhs)
        {
            // �e�O���b�h�̒��S���W
            const Vector2 lhsCenter = {
                lhs.x * ONE_GRID_SIZE_X + ONE_GRID_SIZE_X * 0.5f,
                lhs.y * ONE_GRID_SIZE_Y + ONE_GRID_SIZE_Y * 0.5f
            };
            const Vector2 rhsCenter = {
                rhs.x * ONE_GRID_SIZE_X + ONE_GRID_SIZE_X * 0.5f,
                rhs.y * ONE_GRID_SIZE_Y + ONE_GRID_SIZE_Y * 0.5f
            };

            // ��������O���b�h���S�ւ̐�Ίp�x (���W�A��: -�� �` +��)
            const float lhsAngle = std::atan2f(lhsCenter.y - shinePos.y, lhsCenter.x - shinePos.x);
            const float rhsAngle = std::atan2f(rhsCenter.y - shinePos.y, rhsCenter.x - shinePos.x);

            // ���̍��[�̕��� (���W�A��)
            const float leftAngle = shineDir.leftAngle; // �����[�p�x���擾

            // ���[�p�x (leftAngle) ����̑��Ίp�x�� [-��, +��] �͈̔͂ŎZ�o����֐�
            // (���[���킸���ɍ��ɂ���O���b�h�� 2�� �߂��ɔ��Ŗ����ɉ��̂�h��)
            auto GetSignedAngleFromLeft = [](float angle, float baseLeft) {
                static constexpr float TWO_PI = 6.28318530717958647692f;
                static constexpr float PI     = 3.14159265358979323846f;

                float diff = std::fmod(angle - baseLeft, TWO_PI);
                if (diff > PI)  diff -= TWO_PI;
                if (diff < -PI) diff += TWO_PI;
                return diff; // ���̒l�����[��肳��ɍ��A0�����[�҂�����A���̒l���E����
            };

            const float lhsDiff = GetSignedAngleFromLeft(lhsAngle, leftAngle);
            const float rhsDiff = GetSignedAngleFromLeft(rhsAngle, leftAngle);

            // �����i�l�����������́j����E���i�l���傫�����́j�֏����\�[�g
            return lhsDiff < rhsDiff;
        });

    return shineGridPositions;
}

// �`��O�p�ǉ�
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


// ��Q���Ƃ̌�_���擾
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

    // ������1�Ƃ̌�_
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

        // ���̑O���ɂ����_������Ώۂɂ���
        if (t >= 0.0f)
        {
            const Vector2 candidate =
                mstShinePos +
                shineDirection.shineDirectionLeft * t;

            const Vector2 toCandidate =
                candidate - edgePos1;

            // edgePos1 �` edgePos2 �̂ǂ��ɂ��邩
            const float u =
                (toCandidate.x * edge.x +
                 toCandidate.y * edge.y) /
                edgeLengthSquared;

            // �n���ꂽ���̓����ɂ���ꍇ�����̗p
            if (u >= 0.0f && u <= 1.0f)
            {
                intersection1 = candidate;
            }
        }
    }

    // ������2�Ƃ̌�_
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
 
        // ���̑O���ɂ����_������Ώۂɂ���
        if (t >= 0.0f)
        {
            const Vector2 candidate =
                mstShinePos +
                shineDirection.shineDirectionRight * t;

            const Vector2 toCandidate =
                candidate - edgePos1;

            // edgePos1 �` edgePos2 �̂ǂ��ɂ��邩
            const float u =
                (toCandidate.x * edge.x +
                 toCandidate.y * edge.y) /
                edgeLengthSquared;

            // �n���ꂽ���̓����ɂ���ꍇ�����̗p
            if (u >= 0.0f && u <= 1.0f)
            {
                intersection2 = candidate;
            }
        }
    }

    {
        // �O���b�h���ɕ␳
        intersection1 = AdjustPositionToGrid(blockPos, intersection1);
        intersection2 = AdjustPositionToGrid(blockPos, intersection2);
    }
}

// �O���b�h�̌���Ԃ��X�V
void ShineManager::UpdateGridLightState(std::queue<Vector2_Int>& nextCheckShinePos, const std::vector<SHINE_DIRECTION>& shineDirections)
{
    std::queue<Vector2_Int> checkGridPoss = nextCheckShinePos;
    std::queue<Vector2_Int> nextGridPoss;

    while (!checkGridPoss.empty())
    {
        const Vector2_Int checkPos = checkGridPoss.front();
        checkGridPoss.pop();

        bool isStillLit = false;

        for (const SHINE_DIRECTION& shineDir : shineDirections)
        {
            if (IsGridInsideShine(checkPos, shineDir))
            {
                isStillLit = true;
                break;
            }
        }

        // ���̈�O�ɂȂ����ꍇ�̓t���O������
        if (!isStillLit)
        {
            if (mstMapObjectGridData[checkPos.y][checkPos.x].LitFlag)
            {
                mstMapObjectGridData[checkPos.y][checkPos.x].LitFlag = false;
            }
            mstMapObjectGridData[checkPos.y][checkPos.x].ConfiguredShineAreaIndex.clear();
            continue;
        }

        nextGridPoss.push(checkPos);
    }

    nextCheckShinePos.swap(nextGridPoss);

    //     // �O���b�h�̋�`���W
    //     const float gridLeft =
    //         static_cast<float>(checkPos.x * ONE_GRID_SIZE_X);

    //     const float gridRight =
    //         gridLeft + static_cast<float>(ONE_GRID_SIZE_X);

    //     const float gridTop =
    //         static_cast<float>(checkPos.y * ONE_GRID_SIZE_Y);

    //     const float gridBottom =
    //         gridTop + static_cast<float>(ONE_GRID_SIZE_Y);

    //     const Vector2 corners[4] =
    //     {
    //         { gridLeft,  gridTop },
    //         { gridRight, gridTop },
    //         { gridLeft,  gridBottom },
    //         { gridRight, gridBottom }
    //     };

    //     bool isStillLit = false;

    //     for (const SHINE_DIRECTION& shineDir : shineDirections)
    //     {
    //         /*
    //          * ---------------------------------------------------------
    //          * 1. �O���b�h�̎l�������͈͓��ɂ��邩
    //          * ---------------------------------------------------------
    //          */
    //         for (const Vector2& corner : corners)
    //         {
    //             const float cornerAngle =
    //                 GetAngleToPoint(mstShinePos, corner);

    //             if (IsAngleBetween(
    //                     cornerAngle,
    //                     shineDir.leftAngle,
    //                     shineDir.rightAngle))
    //             {
    //                 isStillLit = true;
    //                 break;
    //             }
    //         }

    //         if (isStillLit)
    //         {
    //             break;
    //         }

    //         /*
    //          * ---------------------------------------------------------
    //          * 2. ���͈͂̋��E�����O���b�h��ʉ߂��Ă��邩
    //          * ---------------------------------------------------------
    //          */
    //         const Vector2 leftDirection =
    //         {
    //             std::cos(shineDir.leftAngle),
    //             std::sin(shineDir.leftAngle)
    //         };

    //         const Vector2 rightDirection =
    //         {
    //             std::cos(shineDir.rightAngle),
    //             std::sin(shineDir.rightAngle)
    //         };

    //         // �����E
    //         if (IsRayIntersectRect(mstShinePos, leftDirection, gridLeft, gridRight, gridTop, gridBottom))
    //         {
    //             isStillLit = true;
    //             break;
    //         }

    //         // �E���E
    //         if (IsRayIntersectRect(mstShinePos, rightDirection, gridLeft, gridRight, gridTop, gridBottom))
    //         {
    //             isStillLit = true;
    //             break;
    //         }
    //     }

    //     // ���̈悪�c���Ă���ꍇ�̓t���O���X�V���Ď��̒T���L���[�ɒǉ�
    //     if (!isStillLit && mstMapObjectGridData[checkPos.y][checkPos.x].LitFlag)
    //     {
    //         mstMapObjectGridData[checkPos.y][checkPos.x].ConfiguredShineAreaIndex.clear();
    //         mstMapObjectGridData[checkPos.y][checkPos.x].LitFlag = false;
    //     }
    // }
}

// 2�����x�N�g�����m�̊O�ς�Z���������߂�
float ShineManager::Cross(const Vector2& src, const Vector2& dst)
{
    return src.x * dst.y - src.y * dst.x;
}

// 2�{�̐����̌�_�����߂�
bool ShineManager::GetIntersection(const Vector2 srcA, const Vector2 srcB, const Vector2 dstC, const Vector2 dstD, Vector2& intersection)
{
    // ����srcAB�̕����x�N�g�������߂�
    Vector2 srcAB =
    {
        srcB.x - srcA.x,
        srcB.y - srcA.y
    };

    // ����dstCD�̕����x�N�g�������߂�
    Vector2 dstCD =
    {
        dstD.x - dstC.x,
        dstD.y - dstC.y
    };

    // srcAB��dstCD�̊O�ς����߂�
    float denominator = Cross(srcAB, dstCD);

    // �O�ς�0�̏ꍇ�A2�{�̐����͕��s
    // ���s�ȏꍇ�͌�_�����߂��Ȃ�
    if (fabsf(denominator) < 0.000001f)
    {
        return false;
    }

    // ����srcAB�̎n�_srcA����
    // ����dstCD�̎n�_dstC�܂ł̃x�N�g�������߂�
    Vector2 srcAdstC =
    {
        dstC.x - srcA.x,
        dstC.y - srcA.y
    };

    // ����srcAB��̂ǂ̈ʒu�Ɍ�_�����邩�����߂�
    // 0�Ȃ�srcA�A1�Ȃ�srcB�A0.5�Ȃ�srcA��srcB�̒���
    float t = Cross(srcAdstC, dstCD) / denominator;

    // ����dstCD��̂ǂ̈ʒu�Ɍ�_�����邩�����߂�
    // 0�Ȃ�dstC�A1�Ȃ�dstD�A0.5�Ȃ�dstC��dstD�̒���
    float u = Cross(srcAdstC, srcAB) / denominator;

    // t��0�`1�͈̔͊O�Ȃ�A��_�͐���srcAB�̊O��
    // u��0�`1�͈̔͊O�Ȃ�A��_�͐���dstCD�̊O��
    if (t < 0.0f || t > 1.0f ||
        u < 0.0f || u > 1.0f)
    {
        return false;
    }

    // ����srcAB���t�̈ʒu�����_�̍��W�����߂�
    intersection =
    {
        srcA.x + srcAB.x * t,
        srcA.y + srcAB.y * t
    };

    // �������m���������Ă���
    return true;
}

// ����AB�̉������Ɛ���CD�̉������̌�_�����߂�
bool ShineManager::GetLineIntersection(const Vector2& srcA, const Vector2& srcB, const Vector2& dstC, const Vector2& dstD, Vector2& intersection)
{
    // ����srcAB�̕����x�N�g�������߂�
    Vector2 srcAB =
    {
        srcB.x - srcA.x,
        srcB.y - srcA.y
    };

    // ����dstCD�̕����x�N�g�������߂�
    Vector2 dstCD =
    {
        dstD.x - dstC.x,
        dstD.y - dstC.y
    };

    // srcAB��dstCD�̊O�ς����߂�
    float denominator = Cross(srcAB, dstCD);

    // �O�ς�0�̏ꍇ�A2�{�̐����͕��s
    // ���s�ȏꍇ�͌�_�����߂��Ȃ�
    if (denominator == 0.0f)
    {
        return false;
    }

    // ����srcAB�̎n�_srcA����
    // ����dstCD�̎n�_dstC�܂ł̃x�N�g�������߂�
    Vector2 srcAdstC =
    {
        dstC.x - srcA.x,
        dstC.y - srcA.y
    };

    // ����srcAB��̂ǂ̈ʒu�Ɍ�_�����邩�����߂�
    // 0�Ȃ�srcA�A1�Ȃ�srcB�A0.5�Ȃ�srcA��srcB�̒���
    float t = Cross(srcAdstC, dstCD) / denominator;

    // ����dstCD��̂ǂ̈ʒu�Ɍ�_�����邩�����߂�
    // 0�Ȃ�dstC�A1�Ȃ�dstD�A0.5�Ȃ�dstC��dstD�̒���
    float u = Cross(srcAdstC, srcAB) / denominator;

    // ����srcAB���t�̈ʒu�����_�̍��W�����߂�
    intersection =
    {
        srcA.x + srcAB.x * t,
        srcA.y + srcAB.y * t
    };

    // �������m���������Ă���
    return true;
}

// 2�_�Ԃ̊p�x���擾���܂��B
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

// ���̉E�ƍ��̕����ƌ�_���Z�o
bool ShineManager::GetShineDirectionIntersection(const Vector2 shineDirections[ANGLE_NUMBER::ANGLE_NUMBER_SHINE_MAX], float shineAngles[ANGLE_NUMBER::ANGLE_NUMBER_SHINE_MAX], int shineAngleNumbers[ANGLE_NUMBER::ANGLE_NUMBER_SHINE_MAX], Vector2 intersectionPositions[ANGLE_NUMBER::ANGLE_NUMBER_SHINE_MAX], float displayCornerAngles[ANGLE_NUMBER::ANGLE_NUMBER_DISPLAY_MAX], const Vector2 displayCornerPosition[ANGLE_NUMBER::ANGLE_NUMBER_DISPLAY_MAX])
{
    // �Z�o&�ǂ̕������擾
    for(int i = 0; i < ANGLE_NUMBER::ANGLE_NUMBER_SHINE_MAX; ++i)
    {
        // 0�`PI*2 �̊ԂɎ��߂�
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
        
        // ��
        if ((displayCornerAngles[ANGLE_NUMBER::ANGLE_NUMBER_DISPLAY_LEFT_UP]    >= shineAngles[i]) &&
            (displayCornerAngles[ANGLE_NUMBER::ANGLE_NUMBER_DISPLAY_LEFT_DOWN] <= shineAngles[i]))
        {
            shineAngleNumbers[i] = ANGLE_BIT_NUMBER::ANGLE_BIT_NUMBER_LEFT;
            // �Z�o
            if (!GetLineIntersection(displayCornerPosition[ANGLE_NUMBER::ANGLE_NUMBER_DISPLAY_LEFT_UP], displayCornerPosition[ANGLE_NUMBER::ANGLE_NUMBER_DISPLAY_LEFT_DOWN],
                                    mstShinePos, mstShinePos + shineDirections[i], 
                                    intersectionPositions[i]))
            {
                return false;
            }
        }
        // �E(0���E�Ȃ���||)
        else if ((displayCornerAngles[ANGLE_NUMBER::ANGLE_NUMBER_DISPLAY_RIGHT_UP]   <= shineAngles[i]) ||
                (displayCornerAngles[ANGLE_NUMBER::ANGLE_NUMBER_DISPLAY_RIGHT_DOWN] >= shineAngles[i]))
        {
            shineAngleNumbers[i] = ANGLE_BIT_NUMBER::ANGLE_BIT_NUMBER_RIGHT;
            // �Z�o
            if (!GetLineIntersection(displayCornerPosition[ANGLE_NUMBER::ANGLE_NUMBER_DISPLAY_RIGHT_UP], displayCornerPosition[ANGLE_NUMBER::ANGLE_NUMBER_DISPLAY_RIGHT_DOWN],
                                    mstShinePos, mstShinePos + shineDirections[i], 
                                    intersectionPositions[i]))
            {
                return false;
            }
        }
        // ��
        else if ((displayCornerAngles[ANGLE_NUMBER::ANGLE_NUMBER_DISPLAY_LEFT_UP]  <= shineAngles[i]) &&
                (displayCornerAngles[ANGLE_NUMBER::ANGLE_NUMBER_DISPLAY_RIGHT_UP] >= shineAngles[i]))
        {
            shineAngleNumbers[i] = ANGLE_BIT_NUMBER::ANGLE_BIT_NUMBER_UP;
            // �Z�o
            if (!GetLineIntersection(displayCornerPosition[ANGLE_NUMBER::ANGLE_NUMBER_DISPLAY_LEFT_UP], displayCornerPosition[ANGLE_NUMBER::ANGLE_NUMBER_DISPLAY_RIGHT_UP],
                                    mstShinePos, mstShinePos + shineDirections[i], 
                                    intersectionPositions[i]))
            {
                return false;
            }
        }
        // ��
        else if ((displayCornerAngles[ANGLE_NUMBER::ANGLE_NUMBER_DISPLAY_RIGHT_DOWN]   <= shineAngles[i]) &&
                (displayCornerAngles[ANGLE_NUMBER::ANGLE_NUMBER_DISPLAY_LEFT_DOWN]    >= shineAngles[i]))
        {
            shineAngleNumbers[i] = ANGLE_BIT_NUMBER::ANGLE_BIT_NUMBER_DOWN;
            // �Z�o
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

// �p���܂܂��Ȃ�p��`��ɒǉ�
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
            // ����
            AddDrawTriangleData(shineDirections[ANGLE_NUMBER::ANGLE_NUMBER_SHINE_LEFT], displayCornerPosition[ANGLE_NUMBER::ANGLE_NUMBER_DISPLAY_LEFT_UP]);
            // �E��
            AddDrawTriangleData(shineDirections[ANGLE_NUMBER::ANGLE_NUMBER_SHINE_RIGHT], displayCornerPosition[ANGLE_NUMBER::ANGLE_NUMBER_DISPLAY_RIGHT_UP]);
            
            // ��
            AddDrawTriangleData(displayCornerPosition[ANGLE_NUMBER::ANGLE_NUMBER_DISPLAY_LEFT_UP], displayCornerPosition[ANGLE_NUMBER::ANGLE_NUMBER_DISPLAY_RIGHT_UP]);
        }
        else
        {
            // ����
            AddDrawTriangleData(shineDirections[ANGLE_NUMBER::ANGLE_NUMBER_SHINE_RIGHT], displayCornerPosition[ANGLE_NUMBER::ANGLE_NUMBER_DISPLAY_LEFT_DOWN]);
            // �E��
            AddDrawTriangleData(shineDirections[ANGLE_NUMBER::ANGLE_NUMBER_SHINE_LEFT], displayCornerPosition[ANGLE_NUMBER::ANGLE_NUMBER_DISPLAY_RIGHT_DOWN]);

            // ��
            AddDrawTriangleData(displayCornerPosition[ANGLE_NUMBER::ANGLE_NUMBER_DISPLAY_LEFT_DOWN], displayCornerPosition[ANGLE_NUMBER::ANGLE_NUMBER_DISPLAY_RIGHT_DOWN]);
        }
        break;
        
    case ANGLE_BIT_NUMBER::ANGLE_BIT_NUMBER_UP_DOWN:
        if (shineAngleNumbers[ANGLE_NUMBER::ANGLE_NUMBER_SHINE_LEFT] == ANGLE_BIT_NUMBER::ANGLE_BIT_NUMBER_UP)
        {
            // �E��
            AddDrawTriangleData(shineDirections[ANGLE_NUMBER::ANGLE_NUMBER_SHINE_LEFT], displayCornerPosition[ANGLE_NUMBER::ANGLE_NUMBER_DISPLAY_RIGHT_UP]);
            // �E��
            AddDrawTriangleData(shineDirections[ANGLE_NUMBER::ANGLE_NUMBER_SHINE_RIGHT], displayCornerPosition[ANGLE_NUMBER::ANGLE_NUMBER_DISPLAY_RIGHT_DOWN]);
            
            // �E
            AddDrawTriangleData(displayCornerPosition[ANGLE_NUMBER::ANGLE_NUMBER_DISPLAY_RIGHT_UP], displayCornerPosition[ANGLE_NUMBER::ANGLE_NUMBER_DISPLAY_RIGHT_DOWN]);
        }
        else
        {
            // ����
            AddDrawTriangleData(shineDirections[ANGLE_NUMBER::ANGLE_NUMBER_SHINE_RIGHT], displayCornerPosition[ANGLE_NUMBER::ANGLE_NUMBER_DISPLAY_LEFT_UP]);
            // ����
            AddDrawTriangleData(shineDirections[ANGLE_NUMBER::ANGLE_NUMBER_SHINE_LEFT], displayCornerPosition[ANGLE_NUMBER::ANGLE_NUMBER_DISPLAY_LEFT_DOWN]);
            
            // ��
            AddDrawTriangleData(displayCornerPosition[ANGLE_NUMBER::ANGLE_NUMBER_DISPLAY_LEFT_UP], displayCornerPosition[ANGLE_NUMBER::ANGLE_NUMBER_DISPLAY_LEFT_DOWN]);
        }
        break;

    default:
        // �`��p�O�p�ɒǉ�
        AddDrawTriangleData(shineDirections[ANGLE_NUMBER::ANGLE_NUMBER_SHINE_LEFT], shineDirections[ANGLE_NUMBER::ANGLE_NUMBER_SHINE_RIGHT]);
        break;
    }
}