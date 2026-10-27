#include <algorithm>
#include <cstddef>

#include "../S_Collision/BaseCollision2DManager.h"
#include "../S_Collision/Point2D.h"
#include "../S_Collision/Quadrangle2D.h"
#include "../S_Collision/Triangle2D.h"
#include "../S_Collision/Capsule2D.h"
#include "../S_Collision/Circle2D.h"
#include "../S_Collision/Ray2D.h"

#include "DxLib.h"
#include "LightAreaManager.h"

#include "LightArea.h"

#include "LightLineNode.h"

#include "Master.h"

#include "DxLibDataManager.h"

#include "DrawSystem.h"

#include "ResourceManager.h"

#include "ImguiManager.h"
static int DrawSelectNumber = 0;
static int DrawSelectNumber2 = 0;
static int DrawSelectNumber3 = 0;

namespace
{
    static bool IsPointInsideLightArea(const LightArea *lightArea, const VECTOR2D &point)
    {
        if (lightArea == nullptr)
        {
            return false;
        }

        Point2D tempPoint;
        tempPoint.SetShapeParameter(point);

        return lightArea->CheckInArea(tempPoint);
    }


    static int ExtendHitCollisionLineToLightCorner(LightArea* lightArea, std::vector<HIT_COLLISION_LINE>& hitCollisionLine, std::vector<HIT_COLLISION_LINE>& drawHitCollisionLine, size_t lineIndex, int drawHitCollisionLineIteratorPlusNumber)
    {
        if (lightArea == nullptr)
        {
            return 0;
        }

        if (lineIndex >= hitCollisionLine.size())
        {
            return 0;
        }

        const HIT_COLLISION_LINE& hitLine = hitCollisionLine[lineIndex];

        if (hitLine.HitCollision == nullptr)
        {
            return 0;
        }

        BaseCollision* collision = hitLine.HitCollision;

        if (collision == nullptr)
        {
            return 0;
        }

        const VECTOR2D currentLineVec = hitLine.LineEndPos - hitLine.LineStartPos;

        const float baseDistanceSq = currentLineVec.MagnitudeNoSqrt();

        if (baseDistanceSq <= 0.0001f)
        {
            return 0;
        }

        const VECTOR2D forwardDir = currentLineVec.Normalize();

        std::vector<VECTOR2D> addPointList;

        auto tryExtend = [&](const VECTOR2D& vertexPos)
        {
            const VECTOR2D delta = vertexPos - hitLine.LineStartPos;
            const float dot = VECTOR2D::Dot(delta, forwardDir);

            if (dot <= 0.0f)
            {
                return;
            }

            if (delta.MagnitudeNoSqrt() <= baseDistanceSq)
            {
                return;
            }

            if (!IsPointInsideLightArea(lightArea, vertexPos))
            {
                return;
            }

            addPointList.push_back(vertexPos);
        };

        switch (collision->GetCollisionType())
        {
        case CollisionType::CollisionType_Point2D:
        {
            auto* point = dynamic_cast<Point2D*>(collision);
            if (point != nullptr)
            {
                tryExtend(point->GetBasePos());
            }
            break;
        }

        case CollisionType::CollisionType_Circle2D:
        {
            auto* circle = dynamic_cast<Circle2D*>(collision);
            if (circle != nullptr)
            {
                tryExtend(circle->GetBasePos());
            }
            break;
        }

        case CollisionType::CollisionType_Capsule2D:
        {
            auto* capsule = dynamic_cast<Capsule2D*>(collision);
            if (capsule != nullptr)
            {
                tryExtend(capsule->GetStartPos());
                tryExtend(capsule->GetEndPos());
            }
            break;
        }

        case CollisionType::CollisionType_Triangle2D:
        {
            auto* triangle = dynamic_cast<Triangle2D*>(collision);
            if (triangle != nullptr)
            {
                tryExtend(triangle->GetVertexPos(0));
                tryExtend(triangle->GetVertexPos(1));
                tryExtend(triangle->GetVertexPos(2));
            }
            break;
        }

        case CollisionType::CollisionType_Quadrangle2D:
        {
            auto* quadrangle = dynamic_cast<Quadrangle2D*>(collision);
            if (quadrangle != nullptr)
            {
                tryExtend(quadrangle->GetVertexPos(0));
                tryExtend(quadrangle->GetVertexPos(1));
                tryExtend(quadrangle->GetVertexPos(2));
                tryExtend(quadrangle->GetVertexPos(3));
            }
            break;
        }

        case CollisionType::CollisionType_Ray2D:
        {
            auto* ray = dynamic_cast<Ray2D*>(collision);
            if (ray != nullptr)
            {
                tryExtend(ray->GetStartPos());
                tryExtend(ray->GetEndPos());
            }
            break;
        }

        default:
            break;
        }

        if (addPointList.empty())
        {
            return 0;
        }

        auto& destinationLines = drawHitCollisionLine;

        int insertIndex = lineIndex + drawHitCollisionLineIteratorPlusNumber + 1;

        int addedCount = 0;

        for (const VECTOR2D& point : addPointList)
        {
            HIT_COLLISION_LINE extendedHitLine = hitLine;
            extendedHitLine.LineStartPos = hitLine.LineEndPos;
            extendedHitLine.LineEndPos = point;

            destinationLines.insert(destinationLines.begin() + static_cast<std::ptrdiff_t>(insertIndex + addedCount), extendedHitLine);

            ++addedCount;
        }

        return addedCount;
    }
/*
    static int ExtendHitCollisionLineToLightCorner(LightArea *lightArea, std::vector<HIT_COLLISION_LINE> &hitLines, size_t lineIndex)
    {
        if (lightArea == nullptr || lineIndex >= hitLines.size())
        {
            return;
        }

        HIT_COLLISION_LINE &hitLine = hitLines[lineIndex];
        if (hitLine.HitCollision == nullptr)
        {
            return;
        }

        BaseCollision2D *collision = dynamic_cast<BaseCollision2D *>(hitLine.HitCollision);
        if (collision == nullptr)
        {
            return;
        }

        const VECTOR2D currentLineVec = hitLine.LineEndPos - hitLine.LineStartPos;
        if (currentLineVec.MagnitudeNoSqrt() <= 0.0001f)
        {
            return;
        }

        const VECTOR2D forwardDir = currentLineVec.Normalize();
        const float baseDistanceSq = currentLineVec.MagnitudeNoSqrt();
        std::vector<VECTOR2D> addPointList;

        auto tryExtend = [&](const VECTOR2D &vertexPos)
        {
            const VECTOR2D delta = vertexPos - hitLine.LineStartPos;
            const float dot = VECTOR2D::Dot(delta, forwardDir);
            if (dot <= 0.0f)
            {
                return;
            }

            const float distanceSq = delta.MagnitudeNoSqrt();
            if (distanceSq <= baseDistanceSq)
            {
                return;
            }

            if (IsPointInsideLightArea(lightArea, vertexPos))
            {
                addPointList.push_back(vertexPos);
            }
        };

        switch (collision->GetCollisionType())
        {
        case CollisionType::CollisionType_Point2D:
            {
                Point2D *point = dynamic_cast<Point2D *>(collision);
                if (point != nullptr)
                {
                    tryExtend(point->GetBasePos());
                }
            }
            break;

        case CollisionType::CollisionType_Circle2D:
            {
                Circle2D *circle = dynamic_cast<Circle2D *>(collision);
                if (circle != nullptr)
                {
                    tryExtend(circle->GetBasePos());
                }
            }
            break;

        case CollisionType::CollisionType_Capsule2D:
            {
                Capsule2D *capsule = dynamic_cast<Capsule2D *>(collision);
                if (capsule != nullptr)
                {
                    tryExtend(capsule->GetStartPos());
                    tryExtend(capsule->GetEndPos());
                }
            }
            break;

        case CollisionType::CollisionType_Triangle2D:
            {
                Triangle2D *triangle = dynamic_cast<Triangle2D *>(collision);
                if (triangle != nullptr)
                {
                    tryExtend(triangle->GetVertexPos(0));
                    tryExtend(triangle->GetVertexPos(1));
                    tryExtend(triangle->GetVertexPos(2));
                }
            }
            break;

        case CollisionType::CollisionType_Quadrangle2D:
            {
                Quadrangle2D *quadrangle = dynamic_cast<Quadrangle2D *>(collision);
                if (quadrangle != nullptr)
                {
                    tryExtend(quadrangle->GetVertexPos(0));
                    tryExtend(quadrangle->GetVertexPos(1));
                    tryExtend(quadrangle->GetVertexPos(2));
                    tryExtend(quadrangle->GetVertexPos(3));
                }
            }
            break;

        case CollisionType::CollisionType_Ray2D:
            {
                Ray2D *ray = dynamic_cast<Ray2D *>(collision);
                if (ray != nullptr)
                {
                    tryExtend(ray->GetStartPos());
                    tryExtend(ray->GetEndPos());
                }
            }
            break;

        default:
            break;
        }

        if (addPointList.empty())
        {
            return;
        }

        for (auto it = addPointList.rbegin(); it != addPointList.rend(); ++it)
        {
            HIT_COLLISION_LINE extendedHitLine = hitLine;
            extendedHitLine.LineStartPos = hitLine.LineEndPos;
            extendedHitLine.LineEndPos = *it;
            hitLines.insert(hitLines.begin() + static_cast<std::ptrdiff_t>(lineIndex + 1), extendedHitLine);
        }
    }
*/
    // 3角情報にして描画
    static void DrawHitCollisionLineData(const std::vector<std::vector<HIT_COLLISION_LINE>> &hitCollisionLineData)
    {
        VERTEX2D* mstLightAreaTriangleVertex = nullptr;
        // 四角設定用変数設定
        constexpr unsigned int boxIndexMax = 4;
        VERTEX2D setBoxPosDatas[boxIndexMax];
        {
            VERTEX2D startBoxPosData;
            startBoxPosData.rhw = 1.0f;
            startBoxPosData.dif = GetColorU8(((/*mnLightColor*/0xffffff & 0xff0000) >> 16), ((/*mnLightColor*/0xffffff & 0x000000) >> 8), (/*mnLightColor*/0xffffff & 0x000000), 255);
            startBoxPosData.u = 0.0f;
            startBoxPosData.v = 0.0f;
            for (int i = 0; i < boxIndexMax; ++i)
            {
                setBoxPosDatas[i] = startBoxPosData;
            }
        }
        
        // 三角形を入力する情報の数を測定
        int munLightAreaTriangleSize = 0;
        for (int i = 0; i < hitCollisionLineData.size(); ++i)
        {
            // 四角ができるか判定
            if (hitCollisionLineData[i].size() < 2)
            {
                continue;
            }
            munLightAreaTriangleSize += hitCollisionLineData[i].size() - 1/*一番後ろは計測しない*/;
        }

        munLightAreaTriangleSize *= 6;/*一つの4角で6個頂点を登録する*/

        //if (mnPreLightAreaTriangleVertexIndexCount != munLightAreaTriangleSize)
        {
            // 中に何か入っているなら消して新しくメモリを用意する
            if (mstLightAreaTriangleVertex != nullptr)
            {
                free(mstLightAreaTriangleVertex);
            }
            mstLightAreaTriangleVertex = static_cast<VERTEX2D*>(malloc(sizeof(VERTEX2D) * munLightAreaTriangleSize));
            //mnPreLightAreaTriangleVertexIndexCount = munLightAreaTriangleSize;
        }

        // 四角を三角で設定
        unsigned int lightAreaIndex = 0;
        for (size_t i = 0; i < hitCollisionLineData.size(); ++i)
        {
            // 四角ができるか判定
            if (hitCollisionLineData[i].size() < 2)
            {
                continue;
            }
            for (size_t l = 0; l < (hitCollisionLineData[i].size() - 1)/*四角にするために最後を除いて処理*/; ++l)
            {
                if (((DrawSelectNumber != l) && (DrawSelectNumber != 30)) || (DrawSelectNumber2 != 0))
                {
                    continue;
                }
                // 4頂点入力
                {
                    VECTOR2D lightLeftDataStart = hitCollisionLineData[i][l].LineStartPos;
                    VECTOR2D lightLeftDataEnd = hitCollisionLineData[i][l].LineEndPos;
                    VECTOR2D lightRightDataStart = hitCollisionLineData[i][l + 1].LineStartPos;
                    VECTOR2D lightRightDataEnd = hitCollisionLineData[i][l + 1].LineEndPos;

                    setBoxPosDatas[0].pos = VGet(lightLeftDataStart.GetX(), lightLeftDataStart.GetY(), 0.0f);
                    setBoxPosDatas[1].pos = VGet(lightLeftDataEnd.GetX(), lightLeftDataEnd.GetY(), 0.0f);
                    setBoxPosDatas[2].pos = VGet(lightRightDataStart.GetX(), lightRightDataStart.GetY(), 0.0f);
                    setBoxPosDatas[3].pos = VGet(lightRightDataEnd.GetX(), lightRightDataEnd.GetY(), 0.0f);
                }
                mstLightAreaTriangleVertex[lightAreaIndex++] = setBoxPosDatas[0];
                mstLightAreaTriangleVertex[lightAreaIndex++] = setBoxPosDatas[1];
                mstLightAreaTriangleVertex[lightAreaIndex++] = setBoxPosDatas[2];

                mstLightAreaTriangleVertex[lightAreaIndex++] = setBoxPosDatas[1];
                mstLightAreaTriangleVertex[lightAreaIndex++] = setBoxPosDatas[2];
                mstLightAreaTriangleVertex[lightAreaIndex++] = setBoxPosDatas[3];
            }
        }
        // 設定した3角を全部描画
        DRAW_SYSTEM::DrawPolygon(mstLightAreaTriangleVertex, munLightAreaTriangleSize / 3, Master::mpLightManager->GetLightAreaGraphHandle(), TRUE, false); 
    }
}

// 
LightAreaManager::LightAreaManager() :
    mlNode(),
    mnDeactivateStartIndex(0),
    mnLightScreenHandle(),
    mnAllLightScreenHandle(-1),
    mstMaskData(),
    mnLightAreaGraphHandle(-1)
{
}

// 
LightAreaManager::~LightAreaManager()
{
    // 
    for (auto node : this->mlNode)
    {
        // 
        if (node == nullptr)
        {
            continue;
        }

        // 
        delete node;

        // 
        node = nullptr;
    }

    // 
    this->mlNode.clear();

    // 
    this->mnDeactivateStartIndex = 0;


    // スクリーン終了
    for (int i = 0; i < mnLightScreenHandle.size(); ++i)
    {
        if (mnLightScreenHandle[i].SceneObjectScreenHandle != -1)
        {
            DeleteGraph(mnLightScreenHandle[i].SceneObjectScreenHandle);
            mnLightScreenHandle[i].SceneObjectScreenHandle = -1;
        }
        if (mnLightScreenHandle[i].FilpScreenHandle != -1)
        {
            DeleteGraph(mnLightScreenHandle[i].FilpScreenHandle);
            mnLightScreenHandle[i].FilpScreenHandle = -1;
        }
        if (mnLightScreenHandle[i].ScreenHandle != -1)
        {
            DeleteGraph(mnLightScreenHandle[i].ScreenHandle);
            mnLightScreenHandle[i].ScreenHandle = -1;
        }
    }
    mnLightScreenHandle.clear();
    if (mnAllLightScreenHandle != -1)
    {
        DeleteGraph(mnAllLightScreenHandle);
        mnAllLightScreenHandle = -1;
    }

    // マスクデータ削除
    if (mstMaskData.maskData != nullptr)
    {
        free(mstMaskData.maskData);
    }
}

// 初期化
void LightAreaManager::Initilize()
{
    mnLightAreaGraphHandle = Master::mpResourceManager->LoadGraphics(ResourceManager::msResourceFile + "LightArea/LightColor.png");
    ScreenSizeChange();
}

// 描画
void LightAreaManager::Draw()
{
    Master::mpImguiManager->AddDrawImgui(
        IMGUI_VARIABLE_CONTROL::GetImguiData(
            {
                &DrawSelectNumber
            },
            1.0f,
            1.0f,
            1.0f,
            0,
            30,
            "NONE_",
            "%d",
            0,
            IMGUI_TYPE::SLIDER1
        )
    );
    Master::mpImguiManager->AddDrawImgui(
        IMGUI_VARIABLE_CONTROL::GetImguiData(
            {
                &DrawSelectNumber2
            },
            1.0f,
            1.0f,
            1.0f,
            0,
            2,
            "NONE_",
            "%d",
            0,
            IMGUI_TYPE::SLIDER1
        )
    );
    Master::mpImguiManager->AddDrawImgui(
        IMGUI_VARIABLE_CONTROL::GetImguiData(
            {
                &DrawSelectNumber3
            },
            1.0f,
            1.0f,
            1.0f,
            0,
            1,
            "NONE_",
            "%d",
            0,
            IMGUI_TYPE::SLIDER1
        )
    );

    // ライト描画処理
    { 
        // 開始
        StartLightDraw();
        // 描画
        LightDraw();
        // 終了
        EndLightDraw();
    }
}


// 
LightArea *LightAreaManager::SearchArea(int areaIndex)
{
    // 
    if (areaIndex < 0 ||
        this->mnDeactivateStartIndex <= areaIndex)
    {
        // 
        return nullptr;
    }

    // 
    return this->mlNode[areaIndex];
}

// 
bool LightAreaManager::ResizeArea(uint32_t useAreaCount)
{
    // 
    if (useAreaCount < this->mnDeactivateStartIndex)
    {
        // 
        this->mnDeactivateStartIndex = useAreaCount;

        // 
        return true;
    }

    // 
    if (this->mlNode.size() < useAreaCount)
    {
        this->mlNode.resize(useAreaCount);
    }

    for (uint32_t i = 0; i < useAreaCount; i++)
    {
        // 
        if (this->mlNode[i] == nullptr)
        {
            // 
            this->mlNode[i] = new LightArea();
        }
    }

    // 
    this->mnDeactivateStartIndex = useAreaCount;

    // 
    return true;
}

// どの光域に入っているかを確認する関数
// 返り値のintは0で処理の成功の可否、引数のoutは自身が入っているAreaIndexを返す関数
int LightAreaManager::CheckInLightArea(const VECTOR2D &pos, std::vector<int> &out)
{
    // 
    Point2D tempPoint;

    // 
    tempPoint.SetShapeParameter(pos);

    // 
    for (uint16_t i = 0; i < this->mnDeactivateStartIndex; i++)
    {
        // 
        if (this->mlNode[i]->GetOffLight())
        {
            // 
            continue;
        }

        // 
        if (this->mlNode[i]->CheckInArea(tempPoint))
        {
            // 
            out.push_back(i);
        }
    }

    // 
    return 0;
}

// スクリーンサイズ変更
void LightAreaManager::ScreenSizeChange()
{
    VECTOR2D displaySize = Master::mpDxLibDataManager->GetDisplaySize();
    for (int i = 0; i < mnLightScreenHandle.size(); ++i)
    {
        if (mnLightScreenHandle[i].SceneObjectScreenHandle != -1)
        {
            DeleteGraph(mnLightScreenHandle[i].SceneObjectScreenHandle);
            mnLightScreenHandle[i].SceneObjectScreenHandle = -1;
        }
        if (mnLightScreenHandle[i].FilpScreenHandle != -1)
        {
            DeleteGraph(mnLightScreenHandle[i].FilpScreenHandle);
            mnLightScreenHandle[i].FilpScreenHandle = -1;
        }
        if (mnLightScreenHandle[i].ScreenHandle != -1)
        {
            DeleteGraph(mnLightScreenHandle[i].ScreenHandle);
            mnLightScreenHandle[i].ScreenHandle = -1;
        }
        mnLightScreenHandle[i].SceneObjectScreenHandle = MakeScreen(displaySize.GetX(), displaySize.GetY(), TRUE);
        mnLightScreenHandle[i].FilpScreenHandle = MakeScreen(displaySize.GetX(), displaySize.GetY(), TRUE);
        mnLightScreenHandle[i].ScreenHandle = MakeScreen(displaySize.GetX(), displaySize.GetY(), TRUE);
    }
    if (mnAllLightScreenHandle != -1)
    {
        DeleteGraph(mnAllLightScreenHandle);
        mnAllLightScreenHandle = -1;
    }
    mnAllLightScreenHandle = MakeScreen(displaySize.GetX(), displaySize.GetY(), TRUE);

    if (mstMaskData.maskData != nullptr)
    {
        free(mstMaskData.maskData);
    }
    mstMaskData.maskData = static_cast<unsigned char*>(malloc(sizeof(unsigned char) * displaySize.GetX() * displaySize.GetY()));
    mstMaskData.maskSize = displaySize;

    if (mstMaskData.maskData == nullptr)
    {
        return;
    }
    // マスクを1ピクセルずつ記入
    for (int y = 0; y < mstMaskData.maskSize.GetY(); ++y)
    {
        for (int x = 0; x < mstMaskData.maskSize.GetX(); ++x)
        {
            mstMaskData.maskData[(y * static_cast<int>(mstMaskData.maskSize.GetX())) + x] = 0xff;
        }
    }
}

// 描画毎初期化
void LightAreaManager::StartLightDraw()
{
    {
        // 描画先を変更
        SetDrawScreen(mnAllLightScreenHandle);
        ClearDrawScreen();

        // マスク画面を作成します
        CreateMaskScreen();

        DrawMaskToDirectData(0, 0, mstMaskData.maskSize.GetX(), mstMaskData.maskSize.GetY(), mstMaskData.maskData, DX_MASKTRANS_NONE);

        // マスク画面を削除します
        DeleteMaskScreen();
    }
    
    for (int i = 0; i < mnLightScreenHandle.size(); ++i)
    {
        {
            // 描画先を変更
            SetDrawScreen(mnLightScreenHandle[i].SceneObjectScreenHandle);
            ClearDrawScreen();

            // マスク画面を作成します
            CreateMaskScreen();

            DrawMaskToDirectData(0, 0, mstMaskData.maskSize.GetX(), mstMaskData.maskSize.GetY(), mstMaskData.maskData, DX_MASKTRANS_NONE);

            // マスク画面を削除します
            DeleteMaskScreen();
        }

        {
            // 描画先を変更
            SetDrawScreen(mnLightScreenHandle[i].FilpScreenHandle);
            ClearDrawScreen();

            // マスク画面を作成します
            CreateMaskScreen();

            DrawMaskToDirectData(0, 0, mstMaskData.maskSize.GetX(), mstMaskData.maskSize.GetY(), mstMaskData.maskData, DX_MASKTRANS_NONE);

            // マスク画面を削除します
            DeleteMaskScreen();
        }
        
        {
            // 描画先を変更
            SetDrawScreen(mnLightScreenHandle[i].ScreenHandle);
            ClearDrawScreen();

            // マスク画面を作成します
            CreateMaskScreen();

            DrawMaskToDirectData(0, 0, mstMaskData.maskSize.GetX(), mstMaskData.maskSize.GetY(), mstMaskData.maskData, DX_MASKTRANS_NONE);

            // マスク画面を削除します
            DeleteMaskScreen();
        }
    }
}

// ライト描画処理
void LightAreaManager::LightDraw()
{
    // 光の種類数を調べる
    int colorCount = 0;
    std::vector<uint32_t> colorNumbers;
    for (int lightAreaIndex = 0; lightAreaIndex < this->mnDeactivateStartIndex; ++lightAreaIndex)
    {
        LightArea* lightArea = mlNode[lightAreaIndex];
        bool newColorFlag = true;
        for (int i = 0; i < colorNumbers.size(); ++i)
        {
            if (lightArea->GetLightColor() == colorNumbers[i])
            {
                newColorFlag = false;
                break;
            }
        }

        if (newColorFlag)
        {
            ++colorCount;
            colorNumbers.push_back(lightArea->GetLightColor());
        }
    }

    // 光描画用スクリーンの数が合わないなら変更
    if (mnLightScreenHandle.size() != colorCount)
    {
        if (mnLightScreenHandle.size() < colorCount)
        {
            while (mnLightScreenHandle.size() < colorCount)
            {
                mnLightScreenHandle.push_back({ MakeScreen(Master::mpDxLibDataManager->GetDisplaySize().GetX(), Master::mpDxLibDataManager->GetDisplaySize().GetY(), TRUE), MakeScreen(Master::mpDxLibDataManager->GetDisplaySize().GetX(), Master::mpDxLibDataManager->GetDisplaySize().GetY(), TRUE), MakeScreen(Master::mpDxLibDataManager->GetDisplaySize().GetX(), Master::mpDxLibDataManager->GetDisplaySize().GetY(), TRUE) });
            }
        }
        else
        {
            while (mnLightScreenHandle.size() > colorCount)
            {
                if (mnLightScreenHandle[mnLightScreenHandle.size() - 1].SceneObjectScreenHandle != -1)
                {
                    DeleteGraph(mnLightScreenHandle[mnLightScreenHandle.size() - 1].SceneObjectScreenHandle);
                }
                if (mnLightScreenHandle[mnLightScreenHandle.size() - 1].FilpScreenHandle != -1)
                {
                    DeleteGraph(mnLightScreenHandle[mnLightScreenHandle.size() - 1].FilpScreenHandle);
                }
                if (mnLightScreenHandle[mnLightScreenHandle.size() - 1].ScreenHandle != -1)
                {
                    DeleteGraph(mnLightScreenHandle[mnLightScreenHandle.size() - 1].ScreenHandle);
                }
                mnLightScreenHandle.pop_back();
            }
        }
    }

    // 光描画
    for (int i = 0; i < mnLightScreenHandle.size(); ++i)
    {
        SetDrawScreen(mnLightScreenHandle[i].FilpScreenHandle);
        for (int lightAreaIndex = 0; lightAreaIndex < this->mnDeactivateStartIndex; ++lightAreaIndex)
        {
            LightArea* lightArea = mlNode[lightAreaIndex];
            if (lightArea->GetLightColor() == colorNumbers[i])
            {
                if (DrawSelectNumber3 != 0)
                {
                    continue;
                }
                lightArea->DrawLightArea();
            }
        }
    }
    for (int i = 0; i < mnLightScreenHandle.size(); ++i)
    {
        SetDrawScreen(mnLightScreenHandle[i].ScreenHandle);
        for (int lightAreaIndex = 0; lightAreaIndex < this->mnDeactivateStartIndex; ++lightAreaIndex)
        {
            LightArea* lightArea = mlNode[lightAreaIndex];
            if (lightArea->GetLightColor() == colorNumbers[i])
            {
                if (DrawSelectNumber2 != 1)
                {
                    continue;
                }
                lightArea->ReDrawLightArea();
            }
        }
    }

    // 当たっているオブジェクトに沿った描画を行う
    for (int i = 0; i < mnLightScreenHandle.size(); ++i)
    {
        if (i != 1)
        {
            continue;
        }
        SetDrawScreen(mnLightScreenHandle[i].ScreenHandle);
        for (LightArea* lightArea : mlNode)
        {
            if (lightArea->GetLightColor() == colorNumbers[i])
            {
                std::vector<std::vector<HIT_COLLISION_LINE>> hitCollisionLine = lightArea->DrawLingAreaHitCollisionsGetProcess();
                std::vector<std::vector<HIT_COLLISION_LINE>> drawHitCollisionLine = hitCollisionLine;
                if (hitCollisionLine.size() == 0)
                {
                    continue;
                }

                // 光の中に入る影の線をすべて描画用データとして追加する
                for (int hitCollisionLinesIterator = 0; hitCollisionLinesIterator < hitCollisionLine.size(); ++hitCollisionLinesIterator)
                {
                    int drawHitCollisionLineIteratorPlusNumber = 0;
                    for (int hitLineIndex = 0; (hitLineIndex + 1) < hitCollisionLine[hitCollisionLinesIterator].size(); ++hitLineIndex)
                    {
                        drawHitCollisionLineIteratorPlusNumber += SetupLightAreaForDrawing(hitCollisionLine[hitCollisionLinesIterator], drawHitCollisionLine[hitCollisionLinesIterator], hitLineIndex, drawHitCollisionLineIteratorPlusNumber);
                    }
                }

                DrawHitCollisionLineData(drawHitCollisionLine);
            }
        }
    }

    if (DrawSelectNumber2 != 2)
    {
        return;
    }
    for (LightArea* lightArea : mlNode)
    {
        for (uint32_t i = 0; i < lightArea->GetLightLineCount(); i++)
        {
            LightLineNode *currentNode = lightArea->GetFirstNodeBox()[i];
            LightLineNode *nextNode;

            if (currentNode == nullptr)
            {
                continue;
            }

            while (true)
            {                
                // デバッグ用レイの可視化
                DRAW_SYSTEM::DrawLine(
                    currentNode->GetMyStartPos(),
                    currentNode->GetMyEndPos(),
                    0x00ffff);
                
                
                if (!currentNode->AccessNext(&nextNode))
                {
                    break;
                }

                currentNode = nextNode;
            }
        }
    }
}

// ライト描画終了時処理
void LightAreaManager::EndLightDraw()
{
    // 描画先戻す
    SetDrawScreen(DX_SCREEN_BACK);

    FlipLightAreaScreen();

    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 125);
    for (int i = 0; i < mnLightScreenHandle.size(); ++i)
    {
        // 描画対象画像を画面いっぱいに拡大して描画する
        DrawExtendGraph(0, 0, mstMaskData.maskSize.GetX(), mstMaskData.maskSize.GetY(), mnLightScreenHandle[i].ScreenHandle, TRUE);
    }
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

// 光領域内の描画済み画面を反転
void LightAreaManager::FlipLightAreaScreen()
{
    // // // // // // // const int screenWidth = static_cast<int>(mstMaskData.maskSize.GetX());

    // // // // // // // const int screenHeight = static_cast<int>(mstMaskData.maskSize.GetY());
 
    // // // // // // // for (LIGHT_SCREEN_HANDLE& screenHandle : mnLightScreenHandle)
    // // // // // // // {
    // // // // // // //     // 画面の内容を一時スクリーンへ取得
    // // // // // // //     // 呼び出し時点では DX_SCREEN_BACK が描画先であること
    // // // // // // //     if (GetDrawScreenGraph(0, 0, screenWidth, screenHeight, screenHandle.SceneObjectScreenHandle) != 0)
    // // // // // // //     {
    // // // // // // //         return;
    // // // // // // //     }

    // // // // // // //     // 保存した画面を描画先にする
    // // // // // // //     SetDrawScreen(screenHandle.SceneObjectScreenHandle);

    // // // // // // //     // マスクの透明部分を反転対象から除外
    // // // // // // //     SetDrawAlphaTest(DX_CMP_GREATER, 0);

    // // // // // // //     // 描画先の色を反転するブレンドモード
    // // // // // // //     SetDrawBlendMode(DX_BLENDMODE_INVDESTCOLOR, 255);

    // // // // // // //     // 光領域のマスクを重ねる
    // // // // // // //     DrawGraph(0, 0, screenHandle.FilpScreenHandle, TRUE);

    // // // // // // //     // 描画設定を元に戻す
    // // // // // // //     SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
    // // // // // // //     SetDrawAlphaTest(-1, 0);

    // // // // // // //     // 元の描画先へ戻す
    // // // // // // //     SetDrawScreen(DX_SCREEN_BACK);

    // // // // // // //     // 反転済みの画面を合成
    // // // // // // //     DrawGraph(0, 0, screenHandle.SceneObjectScreenHandle, FALSE);
    // // // // // // // }


    // // // // // // // 描画先を裏画面に設定
    // // // // // // SetDrawScreen(DX_SCREEN_BACK);

    // // // // // // // 光領域外を暗くするための黒いレイヤーを重ねる
    // // // // // // SetDrawBlendMode(DX_BLENDMODE_ALPHA, 160);

    // // // // // // // 画面全体を黒くする
    // // // // // // DrawBox(0, 0, static_cast<int>(mstMaskData.maskSize.GetX()), static_cast<int>(mstMaskData.maskSize.GetY()), GetColor(0, 0, 0), TRUE);

    // // // // // // SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

    // // // // // SetDrawScreen(mnAllLightScreenHandle);
    // // // // // for (int i = 0; i < mnLightScreenHandle.size(); ++i)
    // // // // // {
    // // // // //     DrawExtendGraph(0, 0, mstMaskData.maskSize.GetX(), mstMaskData.maskSize.GetY(), mnLightScreenHandle[i].FilpScreenHandle, TRUE);
    // // // // // }

    // // // // // SetDrawScreen(DX_SCREEN_BACK);

    // // // // // // マスクを有効化
    // // // // // SetMaskScreenGraph(mnAllLightScreenHandle);
    // // // // // SetUseMaskScreenFlag(TRUE);

    // // // // // // 光領域内外の効果を反転
    // // // // // SetMaskReverseEffectFlag(TRUE);

    // // // // // // 光領域外だけを暗くする
    // // // // // SetDrawBlendMode(DX_BLENDMODE_ALPHA, 160);

    // // // // // DrawBox(0, 0, static_cast<int>(mstMaskData.maskSize.GetX()), static_cast<int>(mstMaskData.maskSize.GetY()), GetColor(0, 0, 0), TRUE);

    // // // // // // マスクと描画設定を解除
    // // // // // SetMaskReverseEffectFlag(FALSE);
    // // // // // SetUseMaskScreenFlag(FALSE);
    // // // // // SetMaskScreenGraph(-1);

    // // // // // SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

    // // // // // 光領域の統合マスクを作成
    // // // // SetDrawScreen(mnAllLightScreenHandle);
    // // // // ClearDrawScreen();

    // // // // // 各光領域を統合する
    // // // // for (const auto& screenHandle : mnLightScreenHandle)
    // // // // {
    // // // //     DrawExtendGraph(0, 0, static_cast<int>(mstMaskData.maskSize.GetX()), static_cast<int>(mstMaskData.maskSize.GetY()), screenHandle.FilpScreenHandle, TRUE);
    // // // // }

    // // // // // バックバッファに戻す
    // // // // SetDrawScreen(DX_SCREEN_BACK);

    // // // // // マスクを有効にする
    // // // // SetMaskScreenGraph(mnAllLightScreenHandle);
    // // // // SetUseMaskScreenFlag(TRUE);
    // // // // SetMaskReverseEffectFlag(TRUE);

    // // // // // 光領域外だけを暗くする
    // // // // SetDrawBlendMode(DX_BLENDMODE_ALPHA, 160);

    // // // // DrawBox(0, 0, static_cast<int>(mstMaskData.maskSize.GetX()), static_cast<int>(mstMaskData.maskSize.GetY()), GetColor(0, 0, 0), TRUE);

    // // // // // 設定を戻す
    // // // // SetUseMaskScreenFlag(FALSE);
    // // // // SetMaskReverseEffectFlag(FALSE);
    // // // // SetMaskScreenGraph(-1);

    // // // // SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

    // // // SetDrawScreen(DX_SCREEN_BACK);

    // // // // 画面全体を暗くする
    // // // SetDrawBlendMode(DX_BLENDMODE_ALPHA, 160);
    // // // DrawBox(0, 0, static_cast<int>(mstMaskData.maskSize.GetX()), static_cast<int>(mstMaskData.maskSize.GetY()), GetColor(0, 0, 0), TRUE);

    // // // // 描画設定を戻す
    // // // SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

    // // // // 光領域を再描画する
    // // // for (const auto& screenHandle : mnLightScreenHandle)
    // // // {
    // // //     DrawExtendGraph(0, 0, static_cast<int>(mstMaskData.maskSize.GetX()), static_cast<int>(mstMaskData.maskSize.GetY()), screenHandle.FilpScreenHandle, TRUE);
    // // // }

    // // // 全光領域を統合するスクリーンを初期化
    // // SetDrawScreen(mnAllLightScreenHandle);
    // // ClearDrawScreen();

    // // // 各光領域を統合
    // // for (const auto& screenHandle : mnLightScreenHandle)
    // // {
    // //     DrawExtendGraph(0, 0, static_cast<int>(mstMaskData.maskSize.GetX()), static_cast<int>(mstMaskData.maskSize.GetY()), screenHandle.FilpScreenHandle, TRUE);
    // // }

    // // // デバッグ確認：
    // // // この行を有効にすると、統合したマスクを画面に表示する
    // // SetDrawScreen(DX_SCREEN_BACK);
    // // DrawExtendGraph(0, 0, static_cast<int>(mstMaskData.maskSize.GetX()), static_cast<int>(mstMaskData.maskSize.GetY()), mnAllLightScreenHandle, TRUE);
    // // return;

    // // // マスクを使って背景を暗くする
    // // SetDrawScreen(DX_SCREEN_BACK);

    // // SetMaskScreenGraph(mnAllLightScreenHandle);
    // // SetMaskReverseEffectFlag(FALSE);
    // // SetUseMaskScreenFlag(TRUE);

    // // SetDrawBlendMode(DX_BLENDMODE_ALPHA, 160);

    // // DrawBox(0, 0, static_cast<int>(mstMaskData.maskSize.GetX()), static_cast<int>(mstMaskData.maskSize.GetY()), GetColor(0, 0, 0), TRUE);

    // // SetUseMaskScreenFlag(FALSE);
    // // SetMaskReverseEffectFlag(FALSE);
    // // SetMaskScreenGraph(-1);

    // // SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
    
    // 全光領域を統合するスクリーンを初期化
    SetDrawScreen(mnAllLightScreenHandle);

    constexpr int EXPAND_SIZE = 2;
    const int offsets[][2] =
    {
        { -EXPAND_SIZE, -EXPAND_SIZE }, // 左上
        {  EXPAND_SIZE, -EXPAND_SIZE }, // 右上
        { -EXPAND_SIZE,  EXPAND_SIZE }, // 左下
        {  EXPAND_SIZE,  EXPAND_SIZE }, // 右下
        {  0,           -EXPAND_SIZE * 2 }, // 上
        {  0,            EXPAND_SIZE * 2 }, // 下
        { -EXPAND_SIZE * 2,  0            }, // 左
        {  EXPAND_SIZE * 2,  0            }, // 右
        {  0,            0            }  // 元の位置
    };

    // 各光領域を統合
    for (const auto& screenHandle : mnLightScreenHandle)
    {
        for (const auto& offset : offsets)
        {
            DrawExtendGraph(0 + offset[0], 0 + offset[1], static_cast<int>(mstMaskData.maskSize.GetX()) + offset[0], static_cast<int>(mstMaskData.maskSize.GetY()) + offset[1], screenHandle.FilpScreenHandle, TRUE);
        }
    }

	// 描画先を裏画面にする
	SetDrawScreen(DX_SCREEN_BACK);

    CreateMaskScreen();
    SetMaskScreenGraph(mnAllLightScreenHandle);



    // マスクを有効にする
    SetUseMaskScreenFlag(TRUE);

    // SetDrawBlendMode(DX_BLENDMODE_ALPHA, 50);
    // DrawBox(0, 0, static_cast<int>(mstMaskData.maskSize.GetX()), static_cast<int>(mstMaskData.maskSize.GetY()), GetColor(0, 0, 0), TRUE);

    SetDrawBlendMode(DX_BLENDMODE_SUB, 50);
    DrawBox(0, 0, static_cast<int>(mstMaskData.maskSize.GetX()), static_cast<int>(mstMaskData.maskSize.GetY()), GetColor(255, 255, 255), TRUE);

    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

    // マスクを無効にする
    SetUseMaskScreenFlag(FALSE);
    SetMaskScreenGraph(-1);
    DeleteMaskScreen();


    // for (LIGHT_SCREEN_HANDLE& screenHandle : mnLightScreenHandle)
    // {
        
    //     // 全光領域を統合するスクリーンを初期化
    //     SetDrawScreen(screenHandle.SceneObjectScreenHandle);

    //     constexpr int EXPAND_SIZE = 5;
    //     const int offsets[][2] =
    //     {
    //         // { -EXPAND_SIZE, -EXPAND_SIZE }, // 左上
    //         // {  EXPAND_SIZE, -EXPAND_SIZE }, // 右上
    //         // { -EXPAND_SIZE,  EXPAND_SIZE }, // 左下
    //         // {  EXPAND_SIZE,  EXPAND_SIZE }, // 右下
    //         // {  0,           -EXPAND_SIZE * 2 }, // 上
    //         // {  0,            EXPAND_SIZE * 2 }, // 下
    //         // { -EXPAND_SIZE * 2,  0            }, // 左
    //         // {  EXPAND_SIZE * 2,  0            }, // 右
    //         {  0,            0            }  // 元の位置
    //     };

    //     // 各光領域を統合
    //     for (const auto& offset : offsets)
    //     {
    //         DrawExtendGraph(0 + offset[0], 0 + offset[1], static_cast<int>(mstMaskData.maskSize.GetX()) + offset[0], static_cast<int>(mstMaskData.maskSize.GetY()) + offset[1], screenHandle.FilpScreenHandle, TRUE);
    //     }

    //     // 描画先を裏画面にする
    //     SetDrawScreen(DX_SCREEN_BACK);

    //     CreateMaskScreen();
    //     SetMaskScreenGraph(screenHandle.SceneObjectScreenHandle);

    //     // マスクを有効にする
    //     SetUseMaskScreenFlag(TRUE);

    //     SetDrawBlendMode(DX_BLENDMODE_ALPHA, 20);

    //     DrawBox(0, 0, static_cast<int>(mstMaskData.maskSize.GetX()), static_cast<int>(mstMaskData.maskSize.GetY()), GetColor(0, 0, 0), TRUE);

    //     SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

    //     // マスクを無効にする
    //     SetUseMaskScreenFlag(FALSE);
    //     SetMaskScreenGraph(-1);
    //     DeleteMaskScreen();
    // }
}


// 光領域を描画用に調整する
int LightAreaManager::SetupLightAreaForDrawing(const std::vector<HIT_COLLISION_LINE>& hitCollisionLine, std::vector<HIT_COLLISION_LINE>& drawHitCollisionLine, size_t lineIndex, int drawHitCollisionLineIteratorPlusNumber)
{
    // 必要条件を満たしているか確認
    {
        if ((lineIndex + 1) >= hitCollisionLine.size())
        {
            return 0;
        }
    }
    
    // 参照しているライン
    HIT_COLLISION_LINE nowCheckHitLine = hitCollisionLine[lineIndex];
    // 次のライン
    HIT_COLLISION_LINE nextCheckHitLine = hitCollisionLine[lineIndex + 1];

    // 追加するライン
    std::vector<HIT_COLLISION_LINE> addDrawHitCollisionLine = {};

    // 当たり判定 三角
    Triangle2D tempTriangle;
    tempTriangle.SetShapeParameter(nowCheckHitLine.LineStartPos, nowCheckHitLine.LineEndPos, nextCheckHitLine.LineEndPos);

    // 当たり判定 点
    Point2D tempPoint;

    // 参照してるラインと次のラインを調べて必要なら描画用に追加する
    do {
        // 参照してるラインと次のラインが同じ物体に当たっているなら角を追加する
        if (nowCheckHitLine.HitCollision != nextCheckHitLine.HitCollision)
        {
            // ×次のラインが何も当たっていないなら参照ラインが当たっている辺の次に近い方を追加する
            // 参照ラインが当たっている当たり判定の角が参照ラインと次のラインの間か調べる
            if (nextCheckHitLine.HitCollision == nullptr)
            {
                std::vector<VECTOR2D> vertexPositions = GetVertexPositions(nowCheckHitLine.HitCollision);
                AddDrawLineToVertexBetweenLines(&addDrawHitCollisionLine, nowCheckHitLine.LineStartPos, nowCheckHitLine.LineEndPos, tempTriangle, vertexPositions, nowCheckHitLine.HitCollision);
                break;
            }
            // 次のラインが当たっている当たり判定の角が参照ラインと次のラインの間か調べる
            else if (nowCheckHitLine.HitCollision == nullptr)
            {
                std::vector<VECTOR2D> vertexPositions = GetVertexPositions(nextCheckHitLine.HitCollision);
                AddDrawLineToVertexBetweenLines(&addDrawHitCollisionLine, nowCheckHitLine.LineStartPos, nowCheckHitLine.LineEndPos, tempTriangle, vertexPositions, nextCheckHitLine.HitCollision);
                break;
            }

            // 当たっている辺同士が交差してるなら交差点を追加
            {
                std::vector<VECTOR2D> nowCollisionPositions = GetHitCollisionEdge(nowCheckHitLine);
                std::vector<VECTOR2D> nextCollisionPositions = GetHitCollisionEdge(nextCheckHitLine);
                std::vector<VECTOR2D> intersectionPos;

                if ((nowCollisionPositions.size() == 2) && (nextCollisionPositions.size() == 2))
                {
                    const VECTOR2D& nowStart = nowCollisionPositions[0];
                    const VECTOR2D& nowEnd = nowCollisionPositions[1];

                    const VECTOR2D& nextStart = nextCollisionPositions[0];
                    const VECTOR2D& nextEnd = nextCollisionPositions[1];

                    const VECTOR2D nowEdgeDirection = nowEnd - nowStart;
                    const VECTOR2D nextEdgeDirection = nextEnd - nextStart;

                    const float denominator = nowEdgeDirection.GetX() * nextEdgeDirection.GetY() - nowEdgeDirection.GetY() * nextEdgeDirection.GetX();

                    // 平行または同一直線上ならスキップ
                    if (fabsf(denominator) <= 0.0001f)
                    {
                        continue;
                    }

                    const VECTOR2D diff = nextStart - nowStart;

                    const float nowEdgeIntersectionRatio = (diff.GetX() * nextEdgeDirection.GetY() - diff.GetY() * nextEdgeDirection.GetX()) / denominator;
                    const float startPositionDifference = (diff.GetX() * nowEdgeDirection.GetY() - diff.GetY() * nowEdgeDirection.GetX()) / denominator;

                    // 両方の線分の範囲内で交差しているか確認
                    if (nowEdgeIntersectionRatio < 0.0f || nowEdgeIntersectionRatio > 1.0f || startPositionDifference < 0.0f || startPositionDifference > 1.0f)
                    {
                        continue;
                    }

                    intersectionPos.push_back(nowStart + nowEdgeDirection * nowEdgeIntersectionRatio);
                    for (int intersectionPosIndex = 0; intersectionPosIndex < intersectionPos.size(); ++intersectionPosIndex)
                    {
                        addDrawHitCollisionLine.push_back({nowCheckHitLine.HitCollision, nowCheckHitLine.LineStartPos, intersectionPos[intersectionPosIndex]});
                    }
                }
            }

            // 当たっている辺同士が交差してるなら交差点を追加
            if (false)
            {
                std::vector<VECTOR2D> nowCollisionPositions = GetVertexPositions(nowCheckHitLine.HitCollision);
                std::vector<VECTOR2D> nextCollisionPositions = GetVertexPositions(nextCheckHitLine.HitCollision);
                VECTOR2D intersectionPos;
                AddDrawLineToVertexBetweenLines(&addDrawHitCollisionLine, nowCheckHitLine.LineStartPos, nowCheckHitLine.LineEndPos, tempTriangle, {intersectionPos}, nowCheckHitLine.HitCollision);
                break;
            }

            std::vector<VECTOR2D> vertexPositions = GetVertexPositions(nowCheckHitLine.HitCollision);
            AddDrawLineToVertexBetweenLines(&addDrawHitCollisionLine, nowCheckHitLine.LineStartPos, nowCheckHitLine.LineEndPos, tempTriangle, vertexPositions, nowCheckHitLine.HitCollision);
            vertexPositions = GetVertexPositions(nextCheckHitLine.HitCollision);
            AddDrawLineToVertexBetweenLines(&addDrawHitCollisionLine, nowCheckHitLine.LineStartPos, nowCheckHitLine.LineEndPos, tempTriangle, vertexPositions, nextCheckHitLine.HitCollision);
        }
        // nowCheckHitLine.HitCollision == nextCheckHitLine.HitCollision
        else
        {
            if (nowCheckHitLine.HitCollision == nullptr)
            {
                break;
            }

            std::vector<VECTOR2D> vertexPositions = GetVertexPositions(nowCheckHitLine.HitCollision);
            AddDrawLineToVertexBetweenLines(&addDrawHitCollisionLine, nowCheckHitLine.LineStartPos, nowCheckHitLine.LineEndPos, tempTriangle, vertexPositions, nowCheckHitLine.HitCollision);
        }
    } while (false);

    constexpr int INSERT_AFTER_REFERENCED_LINE_OFFSET = 1;

    // INPROGRESS:_ 追加設定したラインを伸ばして描画
    // 追加されたラインを反映
    drawHitCollisionLine.insert(drawHitCollisionLine.begin() + lineIndex + drawHitCollisionLineIteratorPlusNumber + INSERT_AFTER_REFERENCED_LINE_OFFSET, addDrawHitCollisionLine.begin(), addDrawHitCollisionLine.end());

    return addDrawHitCollisionLine.size();
}

// 2本のラインの間にある角を取得する
std::vector<VECTOR2D> LightAreaManager::GetVertexPositions(BaseCollision* collision)
{
    std::vector<VECTOR2D> vertexPositions = {};
    switch (collision->GetCollisionType())
    {
    // case CollisionType::CollisionType_Circle2D:
    // {
    //     auto* circle = dynamic_cast<Circle2D*>(collision);
    //     if (circle != nullptr)
    //     {
    //         tryExtend(circle->GetBasePos());
    //     }
    //     break;
    // }

    case CollisionType::CollisionType_Quadrangle2D:
    {
        Quadrangle2D* quadrangle = dynamic_cast<Quadrangle2D*>(collision);
        if (quadrangle != nullptr)
        {
            // 例
            //左上: 0
            //右上: 1
            //左下: 2
            // //右下: 3
            vertexPositions.push_back(quadrangle->GetVertexPos(0));
            vertexPositions.push_back(quadrangle->GetVertexPos(1));
            vertexPositions.push_back(quadrangle->GetVertexPos(3));
            vertexPositions.push_back(quadrangle->GetVertexPos(2));
        }
        break;
    }
    }

    return vertexPositions;
}

// 	2本のラインの間にある頂点まで描画用ラインを追加する
bool LightAreaManager::AddDrawLineToVertexBetweenLines(std::vector<HIT_COLLISION_LINE>* addDrawHitCollisionLine, VECTOR2D startPos, VECTOR2D endPos, Triangle2D& tempTriangle, std::vector<VECTOR2D> vertexPositions, BaseCollision* hitCollision)
{
    // 現在のラインの方向ベクトル
    const VECTOR2D lineVec = endPos - startPos;
    // ラインの長さの2乗
    const float lineLengthSq = lineVec.MagnitudeNoSqrt();

    // ラインの長さがほぼ0なら終了
    if (lineLengthSq <= 0.0001f)
    {
        // 失敗
        return false;
    }

    // 視線方向の角度
    const float viewAngle = atan2f(lineVec.GetY(), lineVec.GetX());

    // 頂点を視線方向に対する角度で並べる
    std::sort(
        vertexPositions.begin(),
        vertexPositions.end(),
        [&startPos, viewAngle](const VECTOR2D& a, const VECTOR2D& b)
        {
            // 開始地点から各頂点への角度
            const VECTOR2D vecA = a - startPos;
            const VECTOR2D vecB = b - startPos;

            const float angleA = atan2f(vecA.GetY(), vecA.GetX()) - viewAngle;
            const float angleB = atan2f(vecB.GetY(), vecB.GetX()) - viewAngle;

            return angleA < angleB;
        });

    // 当たり判定 点
    Point2D tempPoint;
    for (VECTOR2D& vertexPosition : vertexPositions)
    {
        tempPoint.SetShapeParameter(vertexPosition);
        if (0 <= BaseCollision2DManager::CheckHitCollision2DToCollision2D(&tempPoint, &tempTriangle).mnResultParam)
        {
            addDrawHitCollisionLine->push_back({hitCollision, startPos, vertexPosition});
        }
    }

    // 成功
    return true;
}


// 当たっている辺を求める
std::vector<VECTOR2D> LightAreaManager::GetHitCollisionEdge(HIT_COLLISION_LINE hitCollisionLine)
{
    if (hitCollisionLine.HitCollision == nullptr)
    {
        return {};
    }
    std::vector<VECTOR2D> hitCollisionPositions = GetVertexPositions(hitCollisionLine.HitCollision);
    std::vector<VECTOR2D> hitCollisionEdge;

    const VECTOR2D& hitPos = hitCollisionLine.LineEndPos;

    for (size_t i = 0; i < hitCollisionPositions.size(); ++i)
    {
        const VECTOR2D& edgeStart = hitCollisionPositions[i];
        const VECTOR2D& edgeEnd = hitCollisionPositions[(i + 1) % hitCollisionPositions.size()];

        const VECTOR2D edgeDirection = edgeEnd - edgeStart;
        const VECTOR2D hitDirection = hitPos - edgeStart;

        // 外積が0に近ければ同一直線上
        const float crossProduct = edgeDirection.GetX() * hitDirection.GetY() - edgeDirection.GetY() * hitDirection.GetX();

        if (fabsf(crossProduct) > 0.0001f)
        {
            continue;
        }

        // 線分の範囲内にあるか確認
        const float dotProduct = hitDirection.GetX() * edgeDirection.GetX() + hitDirection.GetY() * edgeDirection.GetY();

        const float edgeLengthSquared = edgeDirection.GetX() * edgeDirection.GetX() + edgeDirection.GetY() * edgeDirection.GetY();

        if (dotProduct < 0.0f || dotProduct > edgeLengthSquared)
        {
            continue;
        }
        hitCollisionEdge.push_back(edgeStart);
        hitCollisionEdge.push_back(edgeEnd);
        break;
    }

    return hitCollisionEdge;
}