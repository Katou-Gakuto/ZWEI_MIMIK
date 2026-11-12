#include <algorithm>

#include "LightArea.h"

#include "LightLineNode.h"

#include "../S_Collision/BaseCollision2DManager.h"
#include "../S_Collision/Point2D.h"
#include "../S_Collision/Triangle2D.h"
#include "../S_Collision/Quadrangle2D.h"

#include "../Y_Tool/MyFunctions.h"

#include "BitFlag.h"

#include "Master.h"
#include "DxLibDataManager.h"
#include "LightAreaManager.h"
#include "DrawSystem.h"

// 
LightArea::LightArea() :
    mlLightFirstNode(),
    mlLineAngleBox(),
    mpParentObject(nullptr),
    mnLightLineCount(0),
    mbOffLight(false),
    mbFinal2Start(false),
    mnLightColor(0xffffff),
    // mstLightLine(),
    mstLightAreaTriangleVertex(nullptr),
    munLightAreaTriangleSize(0),
    mnPreLightAreaTriangleVertexIndexCount(0),
    mbIsLightFlag(true)
{
}

// 
LightArea::~LightArea()
{
}

// 
void LightArea::SetParam(void *parentObject, uint32_t lineCount, float stockMagnitude, float baseAngle, float lightAngle, bool final2start)
{
    // 
    this->mpParentObject = parentObject;

    // 
    this->mbFinal2Start = final2start;

    // 
    this->SetLightLineCount(lineCount);

    // 
    if (lineCount == 0)
    {
        // 
        return;
    }

    // 
    float oneAngle = lightAngle / static_cast<float>(lineCount);

    // 
    float startAngle = baseAngle - (lightAngle * 0.5f);

    // 
    for (uint32_t i = 0; i < lineCount; i++)
    {
        // 
        if (this->mlLightFirstNode[i] == nullptr)
        {
            // 
            this->mlLightFirstNode[i] = new LightLineNode(parentObject);
        }
        else
        {
            this->mlLightFirstNode[i]->SetParent(parentObject);
        }

        // 
        this->mlLineAngleBox[i] = MyFunctions::GetArrangeRad(startAngle + (oneAngle * static_cast<float>(i)));
    }

    // 
    this->mfStockMagnitude = stockMagnitude;
}

// 自身の光の終了地点を計算し、設定する関数
// 次のノードにつながる場合はtrueを返す
bool LightArea::CalculateNode(
    const std::vector<BaseCollision2D *> &objectCollBox,
    const std::vector<BaseCollision2D *> &mirrorCollBox,
    Ray2D &tempRay,
    CollisionCheckResult2D &tempResultCurrent,
    CollisionCheckResult2D &tempResultNewr)
{
    // 
    LightLineNode *currentNode = nullptr;
    LightLineNode *nextNode = nullptr;

    // 
    float tempMagnitude = 0.0f;

    VECTOR2D tempStartPos;

    // 
    VECTOR2D toEndNorm;

    // 
    for (uint32_t i = 0; i < this->mnLightLineCount; i++)
    {
        // 
        tempStartPos = this->mlLightFirstNode[i]->GetListStartPos();

        // 
        toEndNorm = VECTOR2D::GetOnUnitCirclePos('x', 'y', this->mlLineAngleBox[i]);

        // 
        currentNode = this->mlLightFirstNode[i];

        // 
        tempMagnitude = this->mfStockMagnitude;

        // 計算を行い、次のノードに移る場合は処理を行う
        while (currentNode->CalculateEndPos(
            tempStartPos,
            toEndNorm,
            objectCollBox,
            mirrorCollBox,
            tempMagnitude,
            tempRay,
            tempResultCurrent,
            tempResultNewr))
        {
            // 
            tempStartPos = currentNode->GetMyEndPos();

            // 
            toEndNorm = VECTOR2D::Reflect(toEndNorm, tempResultNewr.mvRepulsionVecB.Normalize());

            // 
            if (!currentNode->AccessNext(&nextNode))
            {
                // 
                break;
            }

            // 
            currentNode = nextNode;
        }
    }

    // 
    return true;
}

// 
LightLineNode **LightArea::GetFirstNodeBox()
{
    // 
    return this->mlLightFirstNode.data();
}

// 
LightLineNode *const *LightArea::GetFirstNodeBox() const
{
    // 
    return this->mlLightFirstNode.data();
}

// 
uint32_t LightArea::GetLightLineCount() const
{
    // 
    return this->mnLightLineCount;
}

// 
VECTOR2D LightArea::GetStartPosition() const
{
    // 
    VECTOR2D temp;

    // 
    if (!this->mlLightFirstNode.empty() &&
        this->mlLightFirstNode[0] != nullptr)
    {
        // 
        temp = this->mlLightFirstNode[0]->GetListStartPos();
    }

    // 
    return temp;
}

// 
void LightArea::SetLightLineCount(uint32_t count)
{
    // 
    if (this->mnLightLineCount < count)
    {
        // 
        this->mlLightFirstNode.resize(count);

        // 
        this->mlLineAngleBox.resize(count);
    }

    // 
    this->mnLightLineCount = count;
}

// 
bool LightArea::CheckInArea(Point2D &targetPoint) const
{
    // 
    if (this->mlLightFirstNode.empty())
    {
        // 
        return false;
    }

    // 
    Triangle2D tempTriangle;

    // 
    bool result = false;

    // 
    auto nodeBox = this->GetFirstNodeBox();
    uint32_t count = this->GetLightLineCount();

    // 
    VECTOR2D lightStartPos = this->GetFirstNodeBox()[0]->GetListStartPos();

    // 
    CollisionCheckResult2D checkResult = GetCollisionCheckResult2DZero();

    // 
    for (size_t i = 0; i < count - 1; i++)
    {
        // 
        tempTriangle.SetShapeParameter(
            lightStartPos,
            nodeBox[i]->GetMyEndPos(),
            nodeBox[i + 1]->GetMyEndPos());

        // 
        checkResult = BaseCollision2DManager::CheckHitCollision2DToCollision2D(&targetPoint, &tempTriangle);
        if (0 <= checkResult.mnResultParam)
        {
            // 
            result = true;

            // 
            break;
        }
    }

    // 
    if (result)
    {
        // 
        return true;
    }

    if (this->mbFinal2Start)
    {
        // 
        tempTriangle.SetShapeParameter(
            lightStartPos,
            nodeBox[count - 1]->GetMyEndPos(),
            nodeBox[0]->GetMyEndPos());

        // 
        checkResult = BaseCollision2DManager::CheckHitCollision2DToCollision2D(&targetPoint, &tempTriangle);
        if (0 <= checkResult.mnResultParam)
        {
            // 
            result = true;
        }
    }

    // 
    if (result)
    {
        // 
        return true;
    }

    // 
    Quadrangle2D tempQuad;

    // 
    LightLineNode *firstNode = nullptr;
    LightLineNode *firstNodeNext = nullptr;
    LightLineNode *secondNode = nullptr;
    LightLineNode *secondNodeNext = nullptr;

    // 
    bool checkTri = false;

    // 
    bool loopFlag = true;

    // 
    for (size_t i = 0; i < count; i++)
    {
        // 
        if (this->mbFinal2Start)
        {
            firstNode = nodeBox[i];
            secondNode = nodeBox[(i + 1) % count];
        }
        else
        {
            if (count - 1 < (i + 1))
            {
                // 
                break;
            }

            // 
            firstNode = nodeBox[i];
            secondNode = nodeBox[i + 1];
        }

        // 
        loopFlag = true;

        // 
        while (loopFlag)
        {
            // 
            checkTri = false;

            // 
            firstNode->AccessNext(&firstNodeNext);
            secondNode->AccessNext(&secondNodeNext);

            // 
            if (firstNodeNext != nullptr && secondNodeNext != nullptr)
            {
                // 
                firstNode = firstNodeNext;
                secondNode = secondNodeNext;

                // 
                tempQuad.SetShapeParameter(
                    firstNode->GetMyStartPos(),
                    secondNode->GetMyStartPos(),
                    firstNode->GetMyEndPos(),
                    secondNode->GetMyEndPos());
            }
            else if (firstNodeNext != nullptr && secondNodeNext == nullptr)
            {
                // 
                tempTriangle.SetShapeParameter(
                    firstNode->GetMyEndPos(),
                    secondNode->GetMyEndPos(),
                    firstNodeNext->GetMyEndPos());

                // 
                checkTri = true;

                // 
                loopFlag = false;
            }
            else if (firstNodeNext == nullptr && secondNodeNext != nullptr)
            {
                // 
                tempTriangle.SetShapeParameter(
                    firstNode->GetMyEndPos(),
                    secondNode->GetMyEndPos(),
                    secondNodeNext->GetMyEndPos());

                // 
                checkTri = true;

                // 
                loopFlag = false;
            }
            else
            {
                // 
                break;
            }

            // 
            if (checkTri)
            {
                // この三角形があほほど大きくなることが多々ありそうだったので、ひとまずコメントアウト
                // checkResult = BaseCollision2DManager::CheckHitCollision2DToCollision2D(&targetPoint, &tempTriangle);
            }
            else
            {
                checkResult = BaseCollision2DManager::CheckHitCollision2DToCollision2D(&targetPoint, &tempQuad);
            }

            // 
            if (0 <= checkResult.mnResultParam)
            {
                // 
                result = true;

                // 
                break;
            }
        }

        // 
        if (result)
        {
            // 
            break;
        }
    }

    // 
    return result;
}

// 
bool LightArea::GetOffLight() const
{
    // 
    return this->mbOffLight;
}

// 
bool LightArea::OnLight()
{
    // 
    this->mbOffLight = false;

    // 
    return true;
}

// 
bool LightArea::OffLight()
{
    // 
    this->mbOffLight = true;

    // 
    return true;
}

std::vector<std::vector<std::vector<HIT_COLLISION_LINE>>> drawHitCollisionLine;
// ライトエリアの描画
void LightArea::DrawLightArea()
{
    if (!mbIsLightFlag)
    {
        return;
    }


    // 光の線取得
    std::vector<std::vector<std::vector<HIT_COLLISION_LINE>>> hitCollisionLine = DrawLingAreaHitCollisionsGetProcess();
    //std::vector<std::vector<std::vector<HIT_COLLISION_LINE>>> drawHitCollisionLine = hitCollisionLine;
    drawHitCollisionLine = hitCollisionLine;
    if (hitCollisionLine.size() == 0)
    {
        return;
    }

    // 光の中に入る影の線をすべて描画用データとして追加する
    for (int hitCollisionLinesIterator = 0; hitCollisionLinesIterator < hitCollisionLine.size(); ++hitCollisionLinesIterator)
    {
        for (int lightAreaIterator = 0; lightAreaIterator < hitCollisionLine[hitCollisionLinesIterator].size(); ++lightAreaIterator)
        {
            int drawHitCollisionLineIteratorPlusNumber = 0;
            for (int hitLineIndex = 0; (hitLineIndex + 1) < hitCollisionLine[hitCollisionLinesIterator][lightAreaIterator].size(); ++hitLineIndex)
            {
                drawHitCollisionLineIteratorPlusNumber += SetupLightAreaForDrawing(hitCollisionLine[hitCollisionLinesIterator][lightAreaIterator], drawHitCollisionLine[hitCollisionLinesIterator][lightAreaIterator], hitLineIndex, drawHitCollisionLineIteratorPlusNumber);
            }
        }
    }

    // 描画
    DrawHitCollisionLineData(drawHitCollisionLine);
}

// ライトエリア再描画
void LightArea::ReDrawLightArea()
{
    if (!mbIsLightFlag)
    {
        return;
    }
    
    for (int i = 0; i < munLightAreaTriangleSize; ++i)
    {
        mstLightAreaTriangleVertex[i].dif = GetColorU8(((mnLightColor & 0xff0000) >> 16), ((mnLightColor & 0x00ff00) >> 8), (mnLightColor & 0x0000ff), 255);
    }
    // 設定した3角を全部描画
    DRAW_SYSTEM::DrawPolygon(mstLightAreaTriangleVertex, munLightAreaTriangleSize / 3, Master::mpLightManager->GetLightAreaGraphHandle(), TRUE, true); 
}

// ライトエリア描画時当たっている
std::vector<std::vector<std::vector<HIT_COLLISION_LINE>>> LightArea::DrawLingAreaHitCollisionsGetProcess()
{
    std::vector<std::vector<std::vector<HIT_COLLISION_LINE>>> hitCollisionLineData;

    if (!mbIsLightFlag)
    {
        return hitCollisionLineData;
    }

    LightLineNode* currentNode;
    LightLineNode* nextNode;

    // // 
    // BIT_FLAG<unsigned long long> s;
    // while (s.flags >= mnLightLineCount)
    // {
    //     s = s.GetFlag_BitShift(1) | 0x1;
    // }
    // unsigned long long 

    int preLoopCount = -1;
    for (uint32_t i = 0; i < mnLightLineCount; ++i)
    {
        currentNode = this->GetFirstNodeBox()[i];

        if (currentNode == nullptr)
        {
            continue;
        }

        // ループ数
        int loopCount = 0;
        // 前の当たり判定
        BaseCollision* preHitCollision = nullptr;
        while (true)
        {
            // 情報保存
            HIT_COLLISION_LINE hitCollisionLine;
            hitCollisionLine.HitCollision = currentNode->GetHitCollision();
            hitCollisionLine.PreLineHitCollision = preHitCollision;
            hitCollisionLine.LineStartPos = currentNode->GetMyStartPos();
            hitCollisionLine.LineEndPos = currentNode->GetMyEndPos();
            preHitCollision = currentNode->GetHitCollision();

            // このループ数最初の判定なら追加だけして次へ
            if (hitCollisionLineData.size() <= loopCount)
            {
                // 情報を追加
                hitCollisionLineData.push_back({{hitCollisionLine}});
            }
            // 前に設定したことがあるから調べる
            else
            {
                const int lineDataIndexs[3] =
                {
                    loopCount,
                    hitCollisionLineData[loopCount].size() - 1,
                    hitCollisionLineData[loopCount][hitCollisionLineData[loopCount].size() - 1].size() - 1
                };
                constexpr int LOOP_COUNT = 0;
                constexpr int LIGHT_AREA_COUNT = 1;
                constexpr int COLLISION_COUNT = 2;

                // TODO:_ 入れ替え　加筆中

                /*前回のノード数が少ない今のループより少ない
                  出だしが違うオブジェクト*/
                if (((preLoopCount != -1) && (preLoopCount <  loopCount)) ||
                    (hitCollisionLineData[lineDataIndexs[LOOP_COUNT]][lineDataIndexs[LIGHT_AREA_COUNT]][lineDataIndexs[COLLISION_COUNT]].PreLineHitCollision != hitCollisionLine.PreLineHitCollision))
                {
                    // 新しいライトエリアとして登録
                    hitCollisionLineData[lineDataIndexs[LOOP_COUNT]].push_back({hitCollisionLine});
                }
                /*このif判定順番厳守、配列の参照でエラー出る*/
                else if (/*二つのラインで四角分がこれまでに作成されているか判定*/
                    (hitCollisionLineData[lineDataIndexs[LOOP_COUNT]][lineDataIndexs[LIGHT_AREA_COUNT]].size() >= 2) &&
                    /*前の二つのラインを見て今のラインの頂点が両点座標が直線上にあるか判定*/
                    (IsPointOnLine(hitCollisionLineData[lineDataIndexs[LOOP_COUNT]][lineDataIndexs[LIGHT_AREA_COUNT]][lineDataIndexs[COLLISION_COUNT]].LineStartPos, hitCollisionLineData[lineDataIndexs[LOOP_COUNT]][lineDataIndexs[LIGHT_AREA_COUNT]][lineDataIndexs[COLLISION_COUNT] - 1/*後ろから2番目の配列参照*/].LineStartPos, hitCollisionLine.LineStartPos) &&
                        IsPointOnLine(hitCollisionLineData[lineDataIndexs[LOOP_COUNT]][lineDataIndexs[LIGHT_AREA_COUNT]][lineDataIndexs[COLLISION_COUNT]].LineEndPos, hitCollisionLineData[lineDataIndexs[LOOP_COUNT]][lineDataIndexs[LIGHT_AREA_COUNT]][lineDataIndexs[COLLISION_COUNT] - 1/*後ろから2番目の配列参照*/].LineEndPos, hitCollisionLine.LineEndPos)))
                {
                    // 前回登録した情報を書き換える
                    hitCollisionLineData[lineDataIndexs[LOOP_COUNT]][lineDataIndexs[LIGHT_AREA_COUNT]][lineDataIndexs[COLLISION_COUNT]] = hitCollisionLine;
                }
                else
                {
                    // 情報を追加
                    hitCollisionLineData[lineDataIndexs[LOOP_COUNT]][lineDataIndexs[LIGHT_AREA_COUNT]].push_back(hitCollisionLine);
                }
            }

            // 次のノードがあるか確認
            if (!currentNode->AccessNext(&nextNode))
            {
                break;
            }

            // 次のノード設定
            currentNode = nextNode;

            // ループ数インクリメント
            ++loopCount;
        }
        preLoopCount = loopCount;
    }

    // 一周しているか
    if (mbFinal2Start && (0 < mnLightLineCount))
    {
        currentNode = this->GetFirstNodeBox()[0];
        if (currentNode != nullptr)
        {
            // ループ数
            int loopCount = 0;
            // 前の当たり判定
            BaseCollision* preHitCollision = nullptr;
            while (true)
            {
                // 情報保存
                HIT_COLLISION_LINE hitCollisionLine;
                hitCollisionLine.HitCollision = currentNode->GetHitCollision();
                hitCollisionLine.PreLineHitCollision = preHitCollision;
                hitCollisionLine.LineStartPos = currentNode->GetMyStartPos();
                hitCollisionLine.LineEndPos = currentNode->GetMyEndPos();
                preHitCollision = currentNode->GetHitCollision();

                // このループ数最初の判定なら追加だけして次へ
                if (hitCollisionLineData.size() <= loopCount)
                {
                    // 情報を追加
                    hitCollisionLineData.push_back({{hitCollisionLine}});
                }
                // 前に設定したことがあるから調べる
                else
                {
                    const int lineDataIndexs[3] =
                    {
                        loopCount,
                        hitCollisionLineData[loopCount].size() - 1,
                        hitCollisionLineData[loopCount][hitCollisionLineData[loopCount].size() - 1].size() - 1
                    };
                    constexpr int LOOP_COUNT = 0;
                    constexpr int LIGHT_AREA_COUNT = 1;
                    constexpr int COLLISION_COUNT = 2;

                    // TODO:_ 入れ替え　加筆中

                    /*出だしが違うオブジェクト*/
                    if (hitCollisionLineData[lineDataIndexs[LOOP_COUNT]][lineDataIndexs[LIGHT_AREA_COUNT]][lineDataIndexs[COLLISION_COUNT]].PreLineHitCollision != hitCollisionLine.PreLineHitCollision)
                    {
                        // 新しいライトエリアとして登録
                        hitCollisionLineData[lineDataIndexs[LOOP_COUNT]].push_back({hitCollisionLine});
                    }
                    /*このif判定順番厳守、配列の参照でエラー出る*/
                    else if (/*二つのラインで四角分がこれまでに作成されているか判定*/
                        (hitCollisionLineData[lineDataIndexs[LOOP_COUNT]][lineDataIndexs[LIGHT_AREA_COUNT]].size() >= 2) &&
                        /*前の二つのラインを見て今のラインの頂点が両点座標が直線上にあるか判定*/
                        (IsPointOnLine(hitCollisionLineData[lineDataIndexs[LOOP_COUNT]][lineDataIndexs[LIGHT_AREA_COUNT]][lineDataIndexs[COLLISION_COUNT]].LineStartPos, hitCollisionLineData[lineDataIndexs[LOOP_COUNT]][lineDataIndexs[LIGHT_AREA_COUNT]][lineDataIndexs[COLLISION_COUNT] - 1/*後ろから2番目の配列参照*/].LineStartPos, hitCollisionLine.LineStartPos) &&
                            IsPointOnLine(hitCollisionLineData[lineDataIndexs[LOOP_COUNT]][lineDataIndexs[LIGHT_AREA_COUNT]][lineDataIndexs[COLLISION_COUNT]].LineEndPos, hitCollisionLineData[lineDataIndexs[LOOP_COUNT]][lineDataIndexs[LIGHT_AREA_COUNT]][lineDataIndexs[COLLISION_COUNT] - 1/*後ろから2番目の配列参照*/].LineEndPos, hitCollisionLine.LineEndPos)))
                    {
                        // 前回登録した情報を書き換える
                        hitCollisionLineData[lineDataIndexs[LOOP_COUNT]][lineDataIndexs[LIGHT_AREA_COUNT]][lineDataIndexs[COLLISION_COUNT]] = hitCollisionLine;
                    }
                    else
                    {
                        // 情報を追加
                        hitCollisionLineData[lineDataIndexs[LOOP_COUNT]][lineDataIndexs[LIGHT_AREA_COUNT]].push_back(hitCollisionLine);
                    }
                }

                // 次のノードがあるか確認
                if (!currentNode->AccessNext(&nextNode))
                {
                    break;
                }

                // 次のノード設定
                currentNode = nextNode;

                // ループ数インクリメント
                ++loopCount;
            }
        }
    }

    return hitCollisionLineData;
}

// 指定した2点を通る直線上に点があるかを判定
bool LightArea::IsPointOnLine(const VECTOR2D& linePos1, const VECTOR2D& linePos2, const VECTOR2D& checkPos)
{
    // 直線の方向ベクトル
    const VECTOR2D lineVec = linePos2 - linePos1;
    // 始点から判定対象までのベクトル
    const VECTOR2D checkVec = checkPos - linePos1;

    // 外積が0なら、3点は同一直線上にある
    return std::fabs(VECTOR2D::Cross(lineVec, checkVec)) < 0.001f;
}




// 光領域を描画用に調整する
int LightArea::SetupLightAreaForDrawing(const std::vector<HIT_COLLISION_LINE>& hitCollisionLine, std::vector<HIT_COLLISION_LINE>& drawHitCollisionLine, size_t lineIndex, int drawHitCollisionLineIteratorPlusNumber)
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

    // 当たり判定 四角
    Quadrangle2D tempQuadrangle;
    tempQuadrangle.SetShapeParameter(nowCheckHitLine.LineStartPos, nextCheckHitLine.LineStartPos, nowCheckHitLine.LineEndPos, nextCheckHitLine.LineEndPos);

    // 当たり判定 点
    Point2D tempPoint;

    // 参照してるラインと次のラインを調べて必要なら描画用に追加する
    do {// break用
        // 参照してるラインと次のラインが違う物体に当たっている
        if (nowCheckHitLine.HitCollision != nextCheckHitLine.HitCollision)
        {
            // ×次のラインが何も当たっていないなら参照ラインが当たっている辺の次に近い方を追加する
            // 参照ラインが当たっている当たり判定の角が参照ラインと次のラインの間か調べる
            if (nextCheckHitLine.HitCollision == nullptr)
            {
                std::vector<VECTOR2D> vertexPositions = GetVertexPositions(nowCheckHitLine.HitCollision, nowCheckHitLine.LineStartPos);
                AddDrawLineToVertexBetweenLines(&addDrawHitCollisionLine, nowCheckHitLine.LineStartPos, nowCheckHitLine.LineEndPos, tempQuadrangle, vertexPositions, nowCheckHitLine.HitCollision, true);
                break;
            }
            // 次のラインが当たっている当たり判定の角が参照ラインと次のラインの間か調べる
            else if (nowCheckHitLine.HitCollision == nullptr)
            {
                std::vector<VECTOR2D> vertexPositions = GetVertexPositions(nextCheckHitLine.HitCollision, nextCheckHitLine.LineStartPos);
                AddDrawLineToVertexBetweenLines(&addDrawHitCollisionLine, nowCheckHitLine.LineStartPos, nowCheckHitLine.LineEndPos, tempQuadrangle, vertexPositions, nextCheckHitLine.HitCollision, false);
                break;
            }

            // 当たっている辺同士が交差してるなら交差点を追加
            bool IsAdd_AddDrawHitCollisionLine = false;
            do {// break用
                LIGHT_EDGE_DATA nowCollisionPositions = GettingHitCollisionEdge(nowCheckHitLine);
                LIGHT_EDGE_DATA nextCollisionPositions = GettingHitCollisionEdge(nextCheckHitLine);
                std::vector<VECTOR2D> intersectionPos;

                if (nowCollisionPositions.IsExist && nextCollisionPositions.IsExist)
                {
                    const VECTOR2D& nowStart = nowCollisionPositions.LineOne;
                    const VECTOR2D& nowEnd = nowCollisionPositions.LineTwo;

                    const VECTOR2D& nextStart = nextCollisionPositions.LineOne;
                    const VECTOR2D& nextEnd = nextCollisionPositions.LineTwo;

                    const VECTOR2D nowEdgeDirection = nowEnd - nowStart;
                    const VECTOR2D nextEdgeDirection = nextEnd - nextStart;

                    const float denominator = nowEdgeDirection.GetX() * nextEdgeDirection.GetY() - nowEdgeDirection.GetY() * nextEdgeDirection.GetX();

                    // 平行または同一直線上ならスキップ
                    if (fabsf(denominator) <= 0.0001f)
                    {
                        break;
                    }

                    const VECTOR2D diff = nextStart - nowStart;

                    const float nowEdgeIntersectionRatio = (diff.GetX() * nextEdgeDirection.GetY() - diff.GetY() * nextEdgeDirection.GetX()) / denominator;
                    const float startPositionDifference = (diff.GetX() * nowEdgeDirection.GetY() - diff.GetY() * nowEdgeDirection.GetX()) / denominator;

                    // 両方の線分の範囲内で交差しているか確認
                    if (nowEdgeIntersectionRatio < 0.0f || nowEdgeIntersectionRatio > 1.0f || startPositionDifference < 0.0f || startPositionDifference > 1.0f)
                    {
                        break;
                    }

                    intersectionPos.push_back(nowStart + nowEdgeDirection * nowEdgeIntersectionRatio);
                    for (int intersectionPosIndex = 0; intersectionPosIndex < intersectionPos.size(); ++intersectionPosIndex)
                    {
                        addDrawHitCollisionLine.push_back({nowCheckHitLine.HitCollision, nowCheckHitLine.PreLineHitCollision, nowCheckHitLine.LineStartPos, intersectionPos[intersectionPosIndex]});
                    }
                    IsAdd_AddDrawHitCollisionLine = true;
                }
            } while (false);
            if (IsAdd_AddDrawHitCollisionLine)
            {
                break;
            }

            bool isAddDrawHitCollisionLine = false;

            // 範囲内の角を追加
            {
                std::vector<HIT_COLLISION_LINE> setAddDrawHitCollisionLine;
                std::vector<VECTOR2D> vertexPositions;

                vertexPositions = GetVertexPositions(nowCheckHitLine.HitCollision, nowCheckHitLine.LineStartPos);
                setAddDrawHitCollisionLine.clear();
                AddDrawLineToVertexBetweenLines(&setAddDrawHitCollisionLine, nowCheckHitLine.LineStartPos, nowCheckHitLine.LineEndPos, tempQuadrangle, vertexPositions, nowCheckHitLine.HitCollision, true);
                if (0 < setAddDrawHitCollisionLine.size())
                {
                    HIT_COLLISION_LINE setExtendedLight = setAddDrawHitCollisionLine[setAddDrawHitCollisionLine.size() - 1];
                    if (GettingExtendedLight(setExtendedLight, nextCheckHitLine, &setExtendedLight))
                    {
                        // 当たり判定 点
                        Point2D tempPoint;
                        tempPoint.SetShapeParameter(setExtendedLight.LineEndPos);
                        // オブジェクトへの埋まり確認
                        BaseCollision2D* nowHitCollision = dynamic_cast<BaseCollision2D*>(nowCheckHitLine.HitCollision);
                        if ((nowHitCollision != nullptr) && !(0 <= BaseCollision2DManager::CheckHitCollision2DToCollision2D(&tempPoint, nowHitCollision).mnResultParam))
                        {
                            isAddDrawHitCollisionLine = true;
                            setAddDrawHitCollisionLine.push_back(setExtendedLight);
                        }
                    }
                    addDrawHitCollisionLine.insert(addDrawHitCollisionLine.end(), setAddDrawHitCollisionLine.begin(), setAddDrawHitCollisionLine.end());
                }

                vertexPositions = GetVertexPositions(nextCheckHitLine.HitCollision, nextCheckHitLine.LineStartPos);
                setAddDrawHitCollisionLine.clear();
                AddDrawLineToVertexBetweenLines(&setAddDrawHitCollisionLine, nowCheckHitLine.LineStartPos, nowCheckHitLine.LineEndPos, tempQuadrangle, vertexPositions, nextCheckHitLine.HitCollision, false);
                if (0 < setAddDrawHitCollisionLine.size())
                {
                    HIT_COLLISION_LINE setExtendedLight = setAddDrawHitCollisionLine[0];
                    if (GettingExtendedLight(setExtendedLight, nowCheckHitLine, &setExtendedLight))
                    {
                        // 当たり判定 点
                        Point2D tempPoint;
                        tempPoint.SetShapeParameter(setExtendedLight.LineEndPos);
                        // オブジェクトへの埋まり確認
                        BaseCollision2D* nextHitCollision = dynamic_cast<BaseCollision2D*>(nextCheckHitLine.HitCollision);
                        if ((nextHitCollision != nullptr) && !(0 <= BaseCollision2DManager::CheckHitCollision2DToCollision2D(&tempPoint, nextHitCollision).mnResultParam))
                        {
                            isAddDrawHitCollisionLine = true;
                            setAddDrawHitCollisionLine.insert(setAddDrawHitCollisionLine.begin(), setExtendedLight);
                        }
                    }
                    addDrawHitCollisionLine.insert(addDrawHitCollisionLine.end(), setAddDrawHitCollisionLine.begin(), setAddDrawHitCollisionLine.end());
                }
            }

            // 凹みも角もを光内にない場合延長してみて角が含まれないか調べる
            if (!isAddDrawHitCollisionLine)
            {
                // 当たっている辺同士が平行なら除外
                if (IsParallelHitCollisionEdge(nowCheckHitLine, nextCheckHitLine))
                {
                    break;
                }

                HIT_COLLISION_LINE extendedNowLight = nowCheckHitLine;
                HIT_COLLISION_LINE extendedNextLight = nextCheckHitLine;

                // それぞれのオブジェクトの別の辺まで光を延長
                const bool isExtendedNow = GettingExtendedLightToOtherEdge(nowCheckHitLine, &extendedNowLight);

                const bool isExtendedNext = GettingExtendedLightToOtherEdge(nextCheckHitLine, &extendedNextLight);

                // どちらも延長できなければ終了
                if (!isExtendedNow && !isExtendedNext)
                {
                    break;
                }

                // 延長後に当たっている辺同士が平行なら除外
                if (IsParallelHitCollisionEdge(extendedNowLight, extendedNextLight))
                {
                    break;
                }

                // 延長後の光の範囲
                Quadrangle2D extendedQuadrangle;
                extendedQuadrangle.SetShapeParameter(extendedNowLight.LineStartPos, extendedNextLight.LineStartPos, extendedNowLight.LineEndPos, extendedNextLight.LineEndPos);

                // 延長後の範囲内にある角を取得
                {
                    std::vector<HIT_COLLISION_LINE> setAddDrawHitCollisionLine;
                    std::vector<VECTOR2D> vertexPositions;

                    // 現在のオブジェクト
                    vertexPositions = GetVertexPositions(nowCheckHitLine.HitCollision, nowCheckHitLine.LineStartPos);

                    AddDrawLineToVertexBetweenLines(&setAddDrawHitCollisionLine, nowCheckHitLine.LineStartPos, extendedNowLight.LineEndPos, extendedQuadrangle, vertexPositions, nowCheckHitLine.HitCollision, true);

                    if (!setAddDrawHitCollisionLine.empty())
                    {
                        // 追加した角から次のオブジェクトまで光を伸ばす
                        HIT_COLLISION_LINE setExtendedLight = setAddDrawHitCollisionLine.back();

                        if (GettingExtendedLight(setExtendedLight, nextCheckHitLine, &setExtendedLight))
                        {
                            Point2D tempPoint;
                            tempPoint.SetShapeParameter(setExtendedLight.LineEndPos);

                            BaseCollision2D* nowHitCollision = dynamic_cast<BaseCollision2D*>(nowCheckHitLine.HitCollision);

                            // オブジェクトに埋まっていないか確認
                            if ((nowHitCollision != nullptr) && !(0 <= BaseCollision2DManager::CheckHitCollision2DToCollision2D(&tempPoint, nowHitCollision).mnResultParam))
                            {
                                isAddDrawHitCollisionLine = true;
                                setAddDrawHitCollisionLine.push_back(setExtendedLight);
                            }
                        }

                        addDrawHitCollisionLine.insert(addDrawHitCollisionLine.end(), setAddDrawHitCollisionLine.begin(), setAddDrawHitCollisionLine.end());
                    }

                    setAddDrawHitCollisionLine.clear();

                    // 次のオブジェクト
                    vertexPositions = GetVertexPositions(nextCheckHitLine.HitCollision, nextCheckHitLine.LineStartPos);

                    AddDrawLineToVertexBetweenLines(&setAddDrawHitCollisionLine, nowCheckHitLine.LineStartPos, extendedNextLight.LineEndPos, extendedQuadrangle, vertexPositions, nextCheckHitLine.HitCollision, false);

                    if (!setAddDrawHitCollisionLine.empty())
                    {
                        // 追加した角から現在のオブジェクトまで光を伸ばす
                        HIT_COLLISION_LINE setExtendedLight = setAddDrawHitCollisionLine[0];

                        if (GettingExtendedLight(setExtendedLight, nowCheckHitLine, &setExtendedLight))
                        {
                            Point2D tempPoint;
                            tempPoint.SetShapeParameter(setExtendedLight.LineEndPos);

                            BaseCollision2D* nextHitCollision = dynamic_cast<BaseCollision2D*>(nextCheckHitLine.HitCollision);

                            // オブジェクトに埋まっていないか確認
                            if ((nextHitCollision != nullptr) && !(0 <= BaseCollision2DManager::CheckHitCollision2DToCollision2D(&tempPoint, nextHitCollision).mnResultParam))
                            {
                                isAddDrawHitCollisionLine = true;
                                setAddDrawHitCollisionLine.insert(  setAddDrawHitCollisionLine.begin(), setExtendedLight);
                            }
                        }

                        addDrawHitCollisionLine.insert(addDrawHitCollisionLine.end(), setAddDrawHitCollisionLine.begin(), setAddDrawHitCollisionLine.end());
                    }
                }
            }
        }
        // nowCheckHitLine.HitCollision == nextCheckHitLine.HitCollision
        // 参照してるラインと次のラインが同じ物体に当たっている
        else
        {
            if (nowCheckHitLine.HitCollision == nullptr)
            {
                break;
            }

            std::vector<VECTOR2D> vertexPositions = GetVertexPositions(nowCheckHitLine.HitCollision, nowCheckHitLine.LineStartPos);
            AddDrawLineToVertexBetweenLines(&addDrawHitCollisionLine, nowCheckHitLine.LineStartPos, nowCheckHitLine.LineEndPos, tempQuadrangle, vertexPositions, nowCheckHitLine.HitCollision, true);
        }
    } while (false);

    constexpr int INSERT_AFTER_REFERENCED_LINE_OFFSET = 1;

    // 追加されたラインを反映
    drawHitCollisionLine.insert(drawHitCollisionLine.begin() + lineIndex + drawHitCollisionLineIteratorPlusNumber + INSERT_AFTER_REFERENCED_LINE_OFFSET, addDrawHitCollisionLine.begin(), addDrawHitCollisionLine.end());

    return addDrawHitCollisionLine.size();
}

// 角を取得する
std::vector<VECTOR2D> LightArea::GetVertexPositions(BaseCollision* collision, VECTOR2D viewPos)
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
    
    case CollisionType::CollisionType_Ray2D:
    {
        Ray2D* ray = dynamic_cast<Ray2D*>(collision);
        if (ray != nullptr)
        {
            vertexPositions.push_back(ray->GetStartPos());
            vertexPositions.push_back(ray->GetEndPos());
        }
        break;
    }
    }


    // 頂点が2つ以下なら判定しない
    if (vertexPositions.size() <= 2)
    {
        return vertexPositions;
    }


    std::vector<VECTOR2D> visibleVertexPositions = {};

    // 全頂点を確認
    for (int i = 0; i < vertexPositions.size(); ++i)
    {
        const VECTOR2D& vertexPos = vertexPositions[i];

        bool isVisible = false;

        // 全辺を確認
        for (int j = 0; j < vertexPositions.size(); ++j)
        {
            // 辺の始点と終点
            const VECTOR2D& edgeStart = vertexPositions[j];
            const VECTOR2D& edgeEnd = vertexPositions[(j + 1) % vertexPositions.size()];

            // 辺の方向ベクトル
            const float edgeX = edgeEnd.GetX() - edgeStart.GetX();
            const float edgeY = edgeEnd.GetY() - edgeStart.GetY();

            // 辺の始点から視点へのベクトル
            const float viewX = viewPos.GetX() - edgeStart.GetX();
            const float viewY = viewPos.GetY() - edgeStart.GetY();

            // 外積による可視判定
            const float cross = edgeX * viewY - edgeY * viewX;

            // 視点側を向いていない辺があれば除外
            if (cross < 0.0f)
            {
                // 調べている頂点がこの辺の始点または終点なら除外
                if (&vertexPos == &edgeStart || &vertexPos == &edgeEnd)
                {
                    isVisible = true;
                    break;
                }
            }
        }

        // 見えている頂点だけ追加
        if (isVisible)
        {
            visibleVertexPositions.push_back(vertexPos);
        }
    }

    return visibleVertexPositions;
}

// 辺を取得する
std::vector<LIGHT_EDGE_DATA> LightArea::GetVisibleEdges(BaseCollision* collision, const VECTOR2D& viewPos)
{
    std::vector<VECTOR2D> vertexPositions = {};
    switch (collision->GetCollisionType())
    {
    case CollisionType::CollisionType_Quadrangle2D:
    {
        Quadrangle2D* quadrangle = dynamic_cast<Quadrangle2D*>(collision);
        if (quadrangle != nullptr)
        {
            // 例
            //左上: 0
            //右上: 1
            //左下: 2
            //右下: 3
            vertexPositions.push_back(quadrangle->GetVertexPos(0));
            vertexPositions.push_back(quadrangle->GetVertexPos(1));
            vertexPositions.push_back(quadrangle->GetVertexPos(3));
            vertexPositions.push_back(quadrangle->GetVertexPos(2));
        }
        break;
    }
    
    case CollisionType::CollisionType_Ray2D:
    {
        Ray2D* ray = dynamic_cast<Ray2D*>(collision);
        if (ray != nullptr)
        {
            vertexPositions.push_back(ray->GetStartPos());
            vertexPositions.push_back(ray->GetEndPos());
        }
        break;
    }
    }

    // 頂点がが2つ以下なら判定しない
    if (vertexPositions.size() < 2)
    {
        return {};
    }
    else if (vertexPositions.size() == 2)
    {
        return { LIGHT_EDGE_DATA(vertexPositions[0], vertexPositions[1], true)};
    }

    std::vector<int> vertexPositionsIndexs = {};
    // 全頂点を確認
    for (int i = 0; i < vertexPositions.size(); ++i)
    {
        const VECTOR2D& vertexPos = vertexPositions[i];

        bool isVisible = false;

        // 全辺を確認
        for (int j = 0; j < vertexPositions.size(); ++j)
        {
            // 辺の始点と終点
            const VECTOR2D& edgeStart = vertexPositions[j];
            const VECTOR2D& edgeEnd = vertexPositions[(j + 1) % vertexPositions.size()];

            // 辺の方向ベクトル
            const float edgeX = edgeEnd.GetX() - edgeStart.GetX();
            const float edgeY = edgeEnd.GetY() - edgeStart.GetY();

            // 辺の始点から視点へのベクトル
            const float viewX = viewPos.GetX() - edgeStart.GetX();
            const float viewY = viewPos.GetY() - edgeStart.GetY();

            // 外積による可視判定
            const float cross = edgeX * viewY - edgeY * viewX;

            // 視点側を向いていない辺があれば除外
            if (cross < 0.0f)
            {
                // 調べている頂点がこの辺の始点または終点なら除外
                if (&vertexPos == &edgeStart || &vertexPos == &edgeEnd)
                {
                    isVisible = true;
                    break;
                }
            }
        }

        // 見えている頂点だけ追加
        if (isVisible)
        {
            vertexPositionsIndexs.push_back(i);
        }
    }

    // 頂点がが2つ以下なら判定しない
    if (vertexPositionsIndexs.size() < 2)
    {
        return {};
    }

    std::vector<LIGHT_EDGE_DATA> visibleEdges = {};
    for (size_t i = 0; i < vertexPositionsIndexs.size(); ++i)
    {
        const int nextVertexNumber = ((vertexPositionsIndexs[i] + 1) % vertexPositions.size());
        const int nextIndexNumber = vertexPositionsIndexs[(i + 1) % vertexPositionsIndexs.size()];
        if (nextVertexNumber == nextIndexNumber)
        {
            visibleEdges.push_back(LIGHT_EDGE_DATA(vertexPositions[vertexPositionsIndexs[i]], vertexPositions[vertexPositionsIndexs[(i + 1) % vertexPositionsIndexs.size()]], true));
        }
    }

    return visibleEdges;
}

// 	2本のラインの間にある頂点まで描画用ラインを追加する
bool LightArea::AddDrawLineToVertexBetweenLines(std::vector<HIT_COLLISION_LINE>* addDrawHitCollisionLine, VECTOR2D startPos, VECTOR2D endPos, Quadrangle2D& tempQuadrangle, std::vector<VECTOR2D> vertexPositions, BaseCollision* hitCollision, bool isEqualAngleFrontSet)
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
        [&startPos, viewAngle, isEqualAngleFrontSet](const VECTOR2D& a, const VECTOR2D& b)
        {
            // 開始地点から各頂点への角度
            const VECTOR2D vecA = a - startPos;
            const VECTOR2D vecB = b - startPos;

            const float angleA = atan2f(vecA.GetY(), vecA.GetX()) - viewAngle;
            const float angleB = atan2f(vecB.GetY(), vecB.GetX()) - viewAngle;

            constexpr float FLOAT_EPSILON = 0.00001f;
            if (std::abs(angleA - angleB) < FLOAT_EPSILON)
            {
                // 各頂点までの距離の二乗
                const float distanceA = vecA.GetX() * vecA.GetX() + vecA.GetY() * vecA.GetY();
                const float distanceB = vecB.GetX() * vecB.GetX() + vecB.GetY() * vecB.GetY();

                // trueなら近い順、falseなら遠い順
                if (isEqualAngleFrontSet)
                {
                    return distanceA < distanceB;
                }
                else
                {
                    return distanceA > distanceB;
                }
            }

            return angleA < angleB;
        });

    // 当たり判定 点
    Point2D tempPoint;
    for (VECTOR2D& vertexPosition : vertexPositions)
    {
        tempPoint.SetShapeParameter(vertexPosition);
        if (0 <= BaseCollision2DManager::CheckHitCollision2DToCollision2D(&tempPoint, &tempQuadrangle).mnResultParam)
        {
            addDrawHitCollisionLine->push_back({hitCollision, nullptr, startPos, vertexPosition});
        }
    }

    // 成功
    return true;
}


// 当たっている辺を求める
LIGHT_EDGE_DATA LightArea::GettingHitCollisionEdge(const HIT_COLLISION_LINE& hitCollisionLine)
{
    if (hitCollisionLine.HitCollision == nullptr)
    {
        return LIGHT_EDGE_DATA(false);
    }
    std::vector<LIGHT_EDGE_DATA> hitCollisionPositions = GetVisibleEdges(hitCollisionLine.HitCollision, hitCollisionLine.LineStartPos);
    LIGHT_EDGE_DATA hitCollisionEdge;

    const VECTOR2D& hitPos = hitCollisionLine.LineEndPos;

    for (size_t i = 0; i < hitCollisionPositions.size(); ++i)
    {
        // 点が辺上にあるか確認
        if (!IsPointOnLineSegment(hitPos, hitCollisionPositions[i].LineOne, hitCollisionPositions[i].LineTwo))
        {
            continue;
        }

        hitCollisionEdge = hitCollisionPositions[i];
        break;
    }

    return hitCollisionEdge;
}

// 延長した光を取得する
bool LightArea::GettingExtendedLight(HIT_COLLISION_LINE extendedLightLine, const HIT_COLLISION_LINE& hitCollisionLine, HIT_COLLISION_LINE* setExtendedLight)
{
    LIGHT_EDGE_DATA collisionEdge = GettingHitCollisionEdge(hitCollisionLine);

    if (!collisionEdge.IsExist)
    {
        return false;
    }
    const VECTOR2D& lightStart = extendedLightLine.LineStartPos;
    const VECTOR2D& lightEnd   = extendedLightLine.LineEndPos;

    const VECTOR2D& edgeStart = collisionEdge.LineOne;
    const VECTOR2D& edgeEnd   = collisionEdge.LineTwo;

    // 光の方向ベクトル
    const float lightX = lightEnd.GetX() - lightStart.GetX();
    const float lightY = lightEnd.GetY() - lightStart.GetY();

    // 衝突辺の方向ベクトル
    const float edgeX = edgeEnd.GetX() - edgeStart.GetX();
    const float edgeY = edgeEnd.GetY() - edgeStart.GetY();

    // 光と辺が平行な場合
    const float denominator = lightX * edgeY - lightY * edgeX;

    constexpr float FLOAT_EPSILON = 0.00001f;
    if (std::abs(denominator) < FLOAT_EPSILON)
    {
        return false;
    }

    // 光の始点から辺の始点までのベクトル
    const float diffX = edgeStart.GetX() - lightStart.GetX();
    const float diffY = edgeStart.GetY() - lightStart.GetY();

    // 光の直線と辺の交点を求める
    const float t = (diffX * edgeY - diffY * edgeX) / denominator;
    const float u = (diffX * lightY - diffY * lightX) / denominator;

    // 光の終点を交点に変更
    setExtendedLight->LineEndPos.SetX(lightStart.GetX() + lightX * t);
    setExtendedLight->LineEndPos.SetY(lightStart.GetY() + lightY * t);
    return true;
}

// 当たっている辺以外の辺まで光を延長する
bool LightArea::GettingExtendedLightToOtherEdge(const HIT_COLLISION_LINE& hitCollisionLine, HIT_COLLISION_LINE* setExtendedLight)
{
    if (hitCollisionLine.HitCollision == nullptr || setExtendedLight == nullptr)
    {
        return false;
    }

    if (hitCollisionLine.HitCollision->GetCollisionType() != CollisionType::CollisionType_Quadrangle2D)
    {
        return false;
    }

    Quadrangle2D* quadrangle = dynamic_cast<Quadrangle2D*>(hitCollisionLine.HitCollision);

    if (quadrangle == nullptr)
    {
        return false;
    }

    // 四角形の頂点
    std::vector<VECTOR2D> vertexPositions =
    {
        quadrangle->GetVertexPos(0),
        quadrangle->GetVertexPos(1),
        quadrangle->GetVertexPos(3),
        quadrangle->GetVertexPos(2)
    };

    const VECTOR2D& lightStart = hitCollisionLine.LineStartPos;
    const VECTOR2D& lightEnd = hitCollisionLine.LineEndPos;

    const VECTOR2D lightDirection = lightEnd - lightStart;

    const float lightX = lightDirection.GetX();
    const float lightY = lightDirection.GetY();

    if (lightX * lightX + lightY * lightY <= 0.0001f)
    {
        return false;
    }

    // 現在当たっている辺を特定
    int hitEdgeIndex = -1;

    for (size_t i = 0; i < vertexPositions.size(); ++i)
    {
        const VECTOR2D& edgeStart = vertexPositions[i];
        const VECTOR2D& edgeEnd = vertexPositions[(i + 1) % vertexPositions.size()];

        // 光の終点が辺上にあるか確認
        if (!IsPointOnLineSegment(lightEnd, edgeStart, edgeEnd))
        {
            continue;
        }

        hitEdgeIndex = static_cast<int>(i);
        break;
    }

    if (hitEdgeIndex < 0)
    {
        return false;
    }

    float nearestRatio = 1.0f;
    VECTOR2D nearestPosition;
    bool isHit = false;

    // 現在当たっている辺以外を調べる
    for (size_t i = 0; i < vertexPositions.size(); ++i)
    {
        if (static_cast<int>(i) == hitEdgeIndex)
        {
            continue;
        }

        const VECTOR2D& edgeStart = vertexPositions[i];
        const VECTOR2D& edgeEnd = vertexPositions[(i + 1) % vertexPositions.size()];

        const VECTOR2D edgeDirection = edgeEnd - edgeStart;

        const float edgeX = edgeDirection.GetX();
        const float edgeY = edgeDirection.GetY();
    
        const float denominator = lightX * edgeY - lightY * edgeX;
        const float edgeLengthSquared = edgeX * edgeX + edgeY * edgeY;
        const float lightLengthSquared = lightX * lightX + lightY * lightY;
        // ほぼ平行なら除外
        constexpr float PARALLEL_EPSILON = 0.0001f;
        if (denominator * denominator <=
            PARALLEL_EPSILON * PARALLEL_EPSILON *
            lightLengthSquared * edgeLengthSquared)
        {
            continue;
        }

        const VECTOR2D diff = edgeStart - lightStart;

        const float t = (diff.GetX() * edgeY - diff.GetY() * edgeX) / denominator;

        const float u = (diff.GetX() * lightY - diff.GetY() * lightX) / denominator;

        // 現在の光線終点より先にある交点だけを対象にする
        if (t <= 1.0001f || u < 0.0f || u > 1.0f)
        {
            continue;
        }

        if (!isHit || t < nearestRatio)
        {
            nearestRatio = t;
            nearestPosition = lightStart + lightDirection * t;
            isHit = true;
        }
    }

    if (!isHit)
    {
        return false;
    }

    *setExtendedLight = hitCollisionLine;
    setExtendedLight->LineEndPos = nearestPosition;

    return true;
}

// 2本の衝突辺が平行か判定
bool LightArea::IsParallelHitCollisionEdge(const HIT_COLLISION_LINE& firstLine, const HIT_COLLISION_LINE& secondLine)
{
    const LIGHT_EDGE_DATA firstEdge = GettingHitCollisionEdge(firstLine);
    const LIGHT_EDGE_DATA secondEdge = GettingHitCollisionEdge(secondLine);

    if (!(firstEdge.IsExist && secondEdge.IsExist))
    {
        return false;
    }

    const VECTOR2D firstDirection = firstEdge.LineTwo - firstEdge.LineOne;
    const VECTOR2D secondDirection = secondEdge.LineTwo - secondEdge.LineOne;

    const float cross = VECTOR2D::Cross(firstDirection, secondDirection);

    return fabsf(cross) <= 0.0001f;
}

// 点が線分上にあるか確認
bool LightArea::IsPointOnLineSegment(const VECTOR2D& point, const VECTOR2D& lineStart, const VECTOR2D& lineEnd)
{
    const VECTOR2D edgeDirection = lineEnd - lineStart;
    const VECTOR2D hitDirection = point - lineStart;

    const float edgeLengthSquared = edgeDirection.MagnitudeNoSqrt();

    // 線分の長さがほぼ0なら除外
    if (edgeLengthSquared <= 0.0001f)
    {
        return false;
    }

    // 線分の範囲内にあるか確認
    const float dot =
        hitDirection.GetX() * edgeDirection.GetX() +
        hitDirection.GetY() * edgeDirection.GetY();

    if (dot < 0.0f || dot > edgeLengthSquared)
    {
        return false;
    }

    // 線分からの垂直距離を確認
    const float cross =
        edgeDirection.GetX() * hitDirection.GetY() -
        edgeDirection.GetY() * hitDirection.GetX();

    constexpr float DISTANCE_EPSILON = 0.1f;

    if (cross * cross > DISTANCE_EPSILON * DISTANCE_EPSILON * edgeLengthSquared)
    {
        return false;
    }

    return true;
}

// 3角情報にして描画
void LightArea::DrawHitCollisionLineData(const std::vector<std::vector<std::vector<HIT_COLLISION_LINE>>> &hitCollisionLineData)
{
    // 四角設定用変数設定
    constexpr unsigned int boxIndexMax = 4;
    VERTEX2D setBoxPosDatas[boxIndexMax];
    {
        VERTEX2D startBoxPosData;
        startBoxPosData.rhw = 1.0f;
        startBoxPosData.dif = GetColorU8(((/*mnLightColor*/0xffffff & 0xff0000) >> 16), ((/*mnLightColor*/0xffffff & 0x00ff00) >> 8), (/*mnLightColor*/0xffffff & 0x0000ff), 255);
        startBoxPosData.u = 0.0f;
        startBoxPosData.v = 0.0f;
        for (int i = 0; i < boxIndexMax; ++i)
        {
            setBoxPosDatas[i] = startBoxPosData;
        }
    }
    
    // 三角形を入力する情報の数を測定
    munLightAreaTriangleSize = 0;
    for (int i = 0; i < hitCollisionLineData.size(); ++i)
    {
        for (int l = 0; l < hitCollisionLineData[i].size(); ++l)
        {
            // 四角ができるか判定
            if (hitCollisionLineData[i][l].size() < 2)
            {
                continue;
            }
            munLightAreaTriangleSize += hitCollisionLineData[i][l].size() - 1/*一番後ろは計測しない*/;
        }
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
    for (size_t lightAreaIterator = 0; lightAreaIterator < hitCollisionLineData.size(); ++lightAreaIterator)
    {
        for (int i = 0; i < hitCollisionLineData[lightAreaIterator].size(); ++i)
        {
            // 四角ができるか判定
            if (hitCollisionLineData[lightAreaIterator][i].size() < 2)
            {
                continue;
            }
            for (size_t l = 0; l < (hitCollisionLineData[lightAreaIterator][i].size() - 1)/*四角にするために最後を除いて処理*/; ++l)
            {
                // 4頂点入力
                {
                    VECTOR2D lightLeftDataStart = hitCollisionLineData[lightAreaIterator][i][l].LineStartPos;
                    VECTOR2D lightLeftDataEnd = hitCollisionLineData[lightAreaIterator][i][l].LineEndPos;
                    VECTOR2D lightRightDataStart = hitCollisionLineData[lightAreaIterator][i][l + 1].LineStartPos;
                    VECTOR2D lightRightDataEnd = hitCollisionLineData[lightAreaIterator][i][l + 1].LineEndPos;

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
    }
    // 設定した3角を全部描画
    DRAW_SYSTEM::DrawPolygon(mstLightAreaTriangleVertex, munLightAreaTriangleSize / 3, Master::mpLightManager->GetLightAreaGraphHandle(), TRUE, false); 
}