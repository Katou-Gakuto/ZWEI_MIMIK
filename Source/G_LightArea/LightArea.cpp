#include <algorithm>

#include "LightArea.h"

#include "LightLineNode.h"

#include "../S_Collision/BaseCollision2DManager.h"
#include "../S_Collision/Point2D.h"
#include "../S_Collision/Triangle2D.h"
#include "../S_Collision/Quadrangle2D.h"

#include "../Y_Tool/MyFunctions.h"

#include "BitFlag.h"

#include "GameObject2D.h"

#include "Master.h"
#include "DxLibDataManager.h"
#include "LightAreaManager.h"
#include "DrawSystem.h"

#include "ImguiManager.h"
static int DrawSelectNumber = 1;
static int DrawSelectNumber1 = -1;
static int DrawSelectNumber2 = -1;
static int DrawSelectNumber3 = -1;

// 
LightArea::LightArea() :
    mlLightFirstNode(),
    mlLineAngleBox(),
    mpParentObject(nullptr),
    mnLightLineCount(0),
    mbOffLight(false),
    mbFinal2Start(false),
    mnLightColor(0xffffff),
    mnNodeMaxCount(-1),
    mstLightAreaTriangleVertex(nullptr),
    munLightAreaTriangleSize(0),
    mnPreLightAreaTriangleVertexIndexCount(0),
    LIGHT_POWER(3000.0f),
    mstAddDrawHitCollisionLine(),
    mlAddLightFirstNode(),
    mlAddLineAngleBox(),
    munAddLightLineCount(0u),
    mbIdLightNodeUpdate(false)
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

    // 描画用情報を設定
    if (SettingDrawLightAreaData(objectCollBox, mirrorCollBox))
    {
        // 当たり判定処理
        for (unsigned int addLightLineIterator = 0u; addLightLineIterator < this->munAddLightLineCount; ++addLightLineIterator)
        {
            tempStartPos = this->mlAddLightFirstNode[addLightLineIterator]->GetListStartPos();

            // 
            toEndNorm = VECTOR2D::GetOnUnitCirclePos('x', 'y', this->mlAddLineAngleBox[addLightLineIterator]);

            // 
            currentNode = this->mlAddLightFirstNode[addLightLineIterator];

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
    }

    mbIdLightNodeUpdate = true;

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
    // TODO:_ ここで追加したやつも含めて判定

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

// ライトエリア再描画
void LightArea::DrawLightArea()
{
    if (this->mbOffLight)
    {
        return;
    }

    Master::mpImguiManager->AddDrawImgui(
        IMGUI_VARIABLE_CONTROL::GetImguiData(
            {
                &DrawSelectNumber
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
                &DrawSelectNumber1
            },
            1.0f,
            1.0f,
            1.0f,
            -1,
            100,
            "NONE_",
            "%d",
            0,
            IMGUI_TYPE::SLIDER1
        )
    );
    if (DrawSelectNumber == 2)
    {
        Master::mpImguiManager->AddDrawImgui(
            IMGUI_VARIABLE_CONTROL::GetImguiData(
                {
                    &DrawSelectNumber2
                },
                1.0f,
                1.0f,
                1.0f,
                -1,
                100,
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
                -1,
                100,
                "NONE_",
                "%d",
                0,
                IMGUI_TYPE::SLIDER1
            )
        );
    }

    if (mbIdLightNodeUpdate)
    {
        // 最大ノード数取得
        int setNodeMaxCount = mnNodeMaxCount;
        LightLineNode* currentNode;
        LightLineNode* nextNode;
        for (uint32_t i = 0; i < munAddLightLineCount; ++i)
        {
            currentNode = this->mlAddLightFirstNode[i];

            if (currentNode == nullptr)
            {
                continue;
            }
            int nodeCount = 0;
            while (true)
            {
                // ノード数インクリメント
                ++nodeCount;
                // 次のノードがあるか確認
                if (!currentNode->AccessNext(&nextNode))
                {
                    break;
                }
                // 次のノード設定
                currentNode = nextNode;
            }
            setNodeMaxCount = max(setNodeMaxCount, nodeCount);
        }
        mnNodeMaxCount = setNodeMaxCount;

        // 光の線取得
        std::vector<std::vector<std::vector<HIT_COLLISION_LINE>>> hitCollisionLine = DrawLingAreaHitCollisionsGetProcess();
        std::vector<std::vector<std::vector<HIT_COLLISION_LINE>>> drawHitCollisionLine = hitCollisionLine;
        if (hitCollisionLine.size() == 0)
        {
            return;
        }

        // 光の中に入る影の線をすべて描画用データとして追加する
        mstAddDrawHitCollisionLine.clear();
        for (int hitCollisionLinesIterator = 0; hitCollisionLinesIterator < hitCollisionLine.size(); ++hitCollisionLinesIterator)
        {
            for (int lightAreaIterator = 0; lightAreaIterator < hitCollisionLine[hitCollisionLinesIterator].size(); ++lightAreaIterator)
            {
                int drawHitCollisionLineIteratorPlusNumber = 0;
                for (int hitLineIndex = 0; (hitLineIndex + 1) < hitCollisionLine[hitCollisionLinesIterator][lightAreaIterator].size(); ++hitLineIndex)
                {
                    if (hitCollisionLine[hitCollisionLinesIterator][lightAreaIterator][hitLineIndex].IsSetup)
                    {
                        //drawHitCollisionLineIteratorPlusNumber += SetupLightAreaForDrawing(hitCollisionLine[hitCollisionLinesIterator][lightAreaIterator], &drawHitCollisionLine[hitCollisionLinesIterator][lightAreaIterator], hitLineIndex, drawHitCollisionLineIteratorPlusNumber);
                    }
                }
            }
        }

        // 描画内容をポリゴン用に設定
        SettingDrawHitCollisionLineData(drawHitCollisionLine);

        switch (DrawSelectNumber)
        {
        case 0:
        {
            // 設定した3角を全部描画
            DRAW_SYSTEM::DrawPolygon(mstLightAreaTriangleVertex, munLightAreaTriangleSize / 3, Master::mpLightManager->GetLightAreaGraphHandle(), TRUE, true); 
        }
            break;
        case 1:
        {
            for (uint32_t i = 0; i < this->munAddLightLineCount; ++i)
            {
                if ((DrawSelectNumber1 != -1) && (DrawSelectNumber1 != i))
                {
                    continue;
                }
                currentNode = this->mlAddLightFirstNode[i];

                if (currentNode == nullptr)
                {
                    continue;
                }
                while (true)
                {
                    DRAW_SYSTEM::DrawLine(currentNode->GetMyStartPos(), currentNode->GetMyEndPos(), 0xff0000 + (i * 5));

                    // 次のノードがあるか確認
                    if (!currentNode->AccessNext(&nextNode))
                    {
                        break;
                    }

                    // 次のノード設定
                    currentNode = nextNode;
                }
            }
        }
            break;
        case 2:
        {
            for (int i = 0; i < drawHitCollisionLine.size(); ++i)
            {
                if ((DrawSelectNumber1 != -1) && (DrawSelectNumber1 != i))
                {
                    continue;
                }
                for (int l = 0; l < drawHitCollisionLine[i].size(); ++l)
                {
                    if ((DrawSelectNumber2 != -1) && (DrawSelectNumber2 != l))
                    {
                        continue;
                    }
                    for (int iterator = 0; iterator < drawHitCollisionLine[i][l].size(); ++iterator)
                    {
                        auto& hitCollisionLineIterator = drawHitCollisionLine[i][l][iterator];
                        if ((DrawSelectNumber3 != -1) && (DrawSelectNumber3 != iterator))
                        {
                            continue;
                        }
                        DRAW_SYSTEM::DrawLine(hitCollisionLineIterator.LineStartPos, hitCollisionLineIterator.LineEndPos, 0x00f0ff);
                    }
                }
            }
        }
            break;
        }
    }
    
    // 設定した3角を全部描画
    //DRAW_SYSTEM::DrawPolygon(mstLightAreaTriangleVertex, munLightAreaTriangleSize / 3, Master::mpLightManager->GetLightAreaGraphHandle(), TRUE, true); 

    mbIdLightNodeUpdate = false;
}

// ライトエリア描画時当たっている
std::vector<std::vector<std::vector<HIT_COLLISION_LINE>>> LightArea::DrawLingAreaHitCollisionsGetProcess()
{
    std::vector<std::vector<std::vector<HIT_COLLISION_LINE>>> hitCollisionLineData;
    std::vector<std::vector<std::vector<AREA_ROUTE_JUDGE_DATA>>> areaRuteJudgeDatas;

    if (this->mbOffLight)
    {
        return hitCollisionLineData;
    }

    // 最大ノード数に合わせてメモリを確保しておく
    if (mnNodeMaxCount == -1)
    {
        return hitCollisionLineData;
    }
    hitCollisionLineData.reserve(mnNodeMaxCount);
    areaRuteJudgeDatas.reserve(mnNodeMaxCount);
    HIT_COLLISION_LINE hitCollisionLine;
    AREA_ROUTE_JUDGE_DATA areaRouteJudge;

    // 追加ノード用変数
    unsigned int addLightLineCount = 0;
    LightLineNode* addCurrentNode;
    LightLineNode* addNextNode;
    HIT_COLLISION_LINE addHitCollisionLine;
    const float ADD_LIGHT_INTENSITY = std::abs(0.1f / (float)mnLightLineCount);

    LightLineNode* currentNode;
    LightLineNode* nextNode;
    int preLoopCount = -1;
    unsigned int setNodeId = 0u;
    for (uint32_t i = 0; i < mnLightLineCount; ++i)
    {
        currentNode = this->GetFirstNodeBox()[i];

        if (currentNode == nullptr)
        {
            continue;
        }

        // ループ数
        int loopCount = 0;
        
        // ルートのID初期化
        areaRouteJudge.LightAreaRouteID = 0;
        areaRouteJudge.PlusLightAreaRouteID = 0;
        areaRouteJudge.IsAddSet = false;

        hitCollisionLine.LightIntensity = (std::abs(((float)i / (float)mnLightLineCount) - 0.5f)) * 2.0f;
        // if (hitCollisionLine.LightIntensity < 0.1f)
        // {
        //     hitCollisionLine.LightIntensity = 0.0f;
        // }
        // else
        // {
        //     hitCollisionLine.LightIntensity = ((hitCollisionLine.LightIntensity - 0.1f) / 0.4f);
        // }

        // ノードのポジション開始位置を取得
        VECTOR2D preNodeStartPos = currentNode->GetMyStartPos();
        VECTOR2D preNodeEndPos = currentNode->GetMyStartPos();

        // アルファ値初期化
        {
            hitCollisionLine.LightStartAlphaRange = 0.0f;
            hitCollisionLine.LightEndAlphaRange = 0.0f;
        }

        // 前の当たり判定
        BaseCollision* preHitCollision = nullptr;
        while (true)
        {
            setNodeId++;
            currentNode->SetNodeId(setNodeId);

            // 情報保存
            hitCollisionLine.HitCollision = currentNode->GetHitCollision();
            hitCollisionLine.LineStartPos = currentNode->GetMyStartPos();
            hitCollisionLine.LineEndPos = currentNode->GetMyEndPos();
            hitCollisionLine.PreHitCollision = preHitCollision;
            hitCollisionLine.OtherCollision = nullptr;
            hitCollisionLine.IsSetup = true;
            hitCollisionLine.LightNodeId = currentNode->GetNodeId();

            while (this->munAddLightLineCount > addLightLineCount)
            {
                addCurrentNode = this->mlAddLightFirstNode[addLightLineCount];
                if (addCurrentNode->GetNodeId() == currentNode->GetNodeId())
                {
                    int addLoopCount = 0;
                    VECTOR2D preAddNodeStartPos = preNodeStartPos;
                    VECTOR2D preAddNodeEndPos = preNodeEndPos;
                    addHitCollisionLine = hitCollisionLine;
                    while (true)
                    {
                        // INPROGRESS:_ 加藤 なぜか描画用に追加されていない(1ループ目は上手くいくけどその次がだめ)
                        // 処理
                        {
                            addHitCollisionLine.HitCollision = addCurrentNode->GetHitCollision();
                            addHitCollisionLine.LineStartPos = addCurrentNode->GetMyStartPos();
                            addHitCollisionLine.LineEndPos = addCurrentNode->GetMyEndPos();
                            addHitCollisionLine.LightStartAlphaRange += ((preAddNodeStartPos - addCurrentNode->GetMyStartPos()).Magnitude() / LIGHT_POWER);
                            addHitCollisionLine.LightEndAlphaRange += ((preAddNodeEndPos - addCurrentNode->GetMyEndPos()).Magnitude() / LIGHT_POWER);
                            areaRouteJudge.IsAddSet = true;
                            const int loopIndex = loopCount + addLoopCount;

                            // このループ数最初の判定なら追加だけして次へ
                            if (hitCollisionLineData.size() <= loopIndex)
                            {
                                // 情報を追加
                                hitCollisionLineData.push_back({{addHitCollisionLine}});

                                areaRouteJudge.LightAreaRouteID += areaRouteJudge.PlusLightAreaRouteID;
                                // 追加IDナンバーがないから0を代入
                                areaRouteJudge.PlusLightAreaRouteID = 0;
                                areaRuteJudgeDatas.push_back({{areaRouteJudge}});
                            }
                            else
                            {

                                const int lightAreaIndex = static_cast<int>(hitCollisionLineData[loopIndex].size()) - 1;

                                // 当たり判定線を追加
                                hitCollisionLineData[loopIndex][lightAreaIndex].push_back(addHitCollisionLine);

                                // 対応するルート判定情報を追加
                                areaRuteJudgeDatas[loopIndex][lightAreaIndex].push_back(areaRouteJudge);
                            }
                        }
                        // 次のノードがあるか確認
                        if (!addCurrentNode->AccessNext(&addNextNode))
                        {
                            break;
                        }

                        // 前回の追加ノードのポジションとして取得
                        preAddNodeStartPos = addCurrentNode->GetMyStartPos();
                        preAddNodeEndPos = addCurrentNode->GetMyEndPos();

                        // 次のノード設定
                        addCurrentNode = addNextNode;

                        ++addLoopCount;
                    }
                    ++addLightLineCount;
                }
                else
                {
                    break;
                }
            }

            // アルファ値更新
            {
                hitCollisionLine.LightStartAlphaRange += ((preNodeStartPos - currentNode->GetMyStartPos()).Magnitude() / LIGHT_POWER);
                hitCollisionLine.LightEndAlphaRange += ((preNodeEndPos - currentNode->GetMyEndPos()).Magnitude() / LIGHT_POWER);
            }

            preHitCollision = currentNode->GetHitCollision();

            // このループ数最初の判定なら追加だけして次へ
            if (hitCollisionLineData.size() <= loopCount)
            {
                // 情報を追加
                hitCollisionLineData.push_back({{hitCollisionLine}});

                areaRouteJudge.LightAreaRouteID += areaRouteJudge.PlusLightAreaRouteID;
                // 追加IDナンバーがないから0を代入
                areaRouteJudge.PlusLightAreaRouteID = 0;
                areaRouteJudge.IsAddSet = false;
                areaRuteJudgeDatas.push_back({{areaRouteJudge}});
            }
            // 前に設定したことがあるから調べる
            else
            {
                areaRouteJudge.LightAreaRouteID += areaRouteJudge.PlusLightAreaRouteID;
                // 隣のはずの線からエリアルート判定情報取得
                AREA_ROUTE_JUDGE_DATA& nowAreaRuteJudgeData = areaRuteJudgeDatas[loopCount].back().back();
                areaRouteJudge.PlusLightAreaRouteID = nowAreaRuteJudgeData.PlusLightAreaRouteID;
                areaRouteJudge.IsAddSet = false;

                const int lineDataIndexs[3] =
                {
                    loopCount,
                    hitCollisionLineData[loopCount].size() - 1,
                    hitCollisionLineData[loopCount][hitCollisionLineData[loopCount].size() - 1].size() - 1
                };
                constexpr int LOOP_COUNT = 0;
                constexpr int LIGHT_AREA_COUNT = 1;
                constexpr int COLLISION_COUNT = 2;

                /*ルートが違う*/
                if (areaRouteJudge.LightAreaRouteID != nowAreaRuteJudgeData.LightAreaRouteID)
                {
                    // 新しいライトエリアとして登録
                    hitCollisionLineData[lineDataIndexs[LOOP_COUNT]].push_back({hitCollisionLine});
                    areaRuteJudgeDatas[lineDataIndexs[LOOP_COUNT]].push_back({areaRouteJudge});
                }
                /*前回のノード数が少ない今のループより少ない
                  出だしが違うオブジェクト*/
                else if (
                    (!areaRuteJudgeDatas[lineDataIndexs[LOOP_COUNT]][lineDataIndexs[LIGHT_AREA_COUNT]][lineDataIndexs[COLLISION_COUNT]].IsAddSet) &&
                    (
                        ((preLoopCount != -1) && (preLoopCount <  loopCount)) ||
                        (hitCollisionLineData[lineDataIndexs[LOOP_COUNT]][lineDataIndexs[LIGHT_AREA_COUNT]][lineDataIndexs[COLLISION_COUNT]].PreHitCollision != hitCollisionLine.PreHitCollision)
                    ))
                {
                    // 新しいライトエリアとして登録IDを増やす)
                    hitCollisionLineData[lineDataIndexs[LOOP_COUNT]].push_back({hitCollisionLine});
                    areaRouteJudge.PlusLightAreaRouteID += 1;
                    areaRuteJudgeDatas[lineDataIndexs[LOOP_COUNT]].push_back({areaRouteJudge});
                }
                /*このif判定順番厳守、配列の参照でエラー出る*/
                else if (/*二つのラインで四角分がこれまでに作成されているか判定*/
                    (hitCollisionLineData[lineDataIndexs[LOOP_COUNT]][lineDataIndexs[LIGHT_AREA_COUNT]].size() >= 2) &&
                    /*前の二つのラインを見て今のラインの頂点が両点座標が直線上にあるか判定*/
                    (IsPointOnLine(hitCollisionLineData[lineDataIndexs[LOOP_COUNT]][lineDataIndexs[LIGHT_AREA_COUNT]][lineDataIndexs[COLLISION_COUNT]].LineStartPos, hitCollisionLineData[lineDataIndexs[LOOP_COUNT]][lineDataIndexs[LIGHT_AREA_COUNT]][lineDataIndexs[COLLISION_COUNT] - 1/*後ろから2番目の配列参照*/].LineStartPos, hitCollisionLine.LineStartPos) &&
                        IsPointOnLine(hitCollisionLineData[lineDataIndexs[LOOP_COUNT]][lineDataIndexs[LIGHT_AREA_COUNT]][lineDataIndexs[COLLISION_COUNT]].LineEndPos, hitCollisionLineData[lineDataIndexs[LOOP_COUNT]][lineDataIndexs[LIGHT_AREA_COUNT]][lineDataIndexs[COLLISION_COUNT] - 1/*後ろから2番目の配列参照*/].LineEndPos, hitCollisionLine.LineEndPos)))
                {
                    // 前回登録した情報を補正外に設定
                    hitCollisionLineData[lineDataIndexs[LOOP_COUNT]][lineDataIndexs[LIGHT_AREA_COUNT]][lineDataIndexs[COLLISION_COUNT]].IsSetup = false;
                    // 情報を追加
                    hitCollisionLineData[lineDataIndexs[LOOP_COUNT]][lineDataIndexs[LIGHT_AREA_COUNT]].push_back(hitCollisionLine);
                    areaRuteJudgeDatas[lineDataIndexs[LOOP_COUNT]][lineDataIndexs[LIGHT_AREA_COUNT]].push_back(areaRouteJudge);
                }
                else
                {
                    // 情報を追加
                    hitCollisionLineData[lineDataIndexs[LOOP_COUNT]][lineDataIndexs[LIGHT_AREA_COUNT]].push_back(hitCollisionLine);
                    areaRuteJudgeDatas[lineDataIndexs[LOOP_COUNT]][lineDataIndexs[LIGHT_AREA_COUNT]].push_back(areaRouteJudge);
                }
            }

            // 次のノードがあるか確認
            if (!currentNode->AccessNext(&nextNode))
            {
                break;
            }

            // 前回のノードのポジションとして取得
            preNodeStartPos = currentNode->GetMyStartPos();
            preNodeEndPos = currentNode->GetMyEndPos();

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
                
            // ルートのID初期化
            areaRouteJudge.LightAreaRouteID = 0;
            areaRouteJudge.PlusLightAreaRouteID = 0;

            // ノードのポジション開始位置を取得
            VECTOR2D preNodeStartPos = currentNode->GetMyStartPos();
            VECTOR2D preNodeEndPos = currentNode->GetMyStartPos();

            // アルファ値保存
            {
                hitCollisionLine.LightStartAlphaRange = ((preNodeStartPos - currentNode->GetMyStartPos()).Magnitude() / LIGHT_POWER);
                hitCollisionLine.LightEndAlphaRange = ((preNodeEndPos - currentNode->GetMyEndPos()).Magnitude() / LIGHT_POWER);
            }

            // 前の当たり判定
            BaseCollision* preHitCollision = nullptr;

            while (this->munAddLightLineCount > addLightLineCount)
            {
                int addLoopCount = 0;
                addCurrentNode = this->mlAddLightFirstNode[addLightLineCount];
                if (addCurrentNode->GetNodeId() == currentNode->GetNodeId())
                {
                    while (true)
                    {
                        // 処理
                        {
                            addHitCollisionLine = hitCollisionLine;
                            addHitCollisionLine.HitCollision = addCurrentNode->GetHitCollision();
                            addHitCollisionLine.LineStartPos = addCurrentNode->GetMyStartPos();
                            addHitCollisionLine.LineEndPos = addCurrentNode->GetMyEndPos();
                            addHitCollisionLine.LightStartAlphaRange;
                            addHitCollisionLine.LightEndAlphaRange;
                            addHitCollisionLine.LightIntensity + hitCollisionLine.LightIntensity;

                            // このループ数最初の判定なら追加だけして次へ
                            if (hitCollisionLineData.size() <= (loopCount + addLoopCount))
                            {
                                // 情報を追加
                                hitCollisionLineData.push_back({{addHitCollisionLine}});

                                areaRouteJudge.LightAreaRouteID += areaRouteJudge.PlusLightAreaRouteID;
                                // 追加IDナンバーがないから0を代入
                                areaRouteJudge.PlusLightAreaRouteID = 0;
                                areaRuteJudgeDatas.push_back({{areaRouteJudge}});
                            }
                            else
                            {
                                hitCollisionLineData[loopCount + addLoopCount][hitCollisionLineData[loopCount].size() - 1].push_back(addHitCollisionLine);
                            }
                        }
                        // 次のノードがあるか確認
                        if (!addCurrentNode->AccessNext(&addNextNode))
                        {
                            break;
                        }

                        // 次のノード設定
                        addCurrentNode = addNextNode;

                        ++addLoopCount;
                    }
                    ++addLightLineCount;
                }
                else
                {
                    break;
                }
            }

            while (true)
            {
                // 情報保存
                hitCollisionLine.HitCollision = currentNode->GetHitCollision();
                hitCollisionLine.LineStartPos = currentNode->GetMyStartPos();
                hitCollisionLine.LineEndPos = currentNode->GetMyEndPos();
                hitCollisionLine.PreHitCollision = preHitCollision;
                hitCollisionLine.OtherCollision = nullptr;
                hitCollisionLine.LightNodeId = currentNode->GetNodeId(); 

                // アルファ値更新
                {
                    hitCollisionLine.LightStartAlphaRange += ((preNodeStartPos - currentNode->GetMyStartPos()).Magnitude() / LIGHT_POWER);
                    hitCollisionLine.LightEndAlphaRange += ((preNodeEndPos - currentNode->GetMyEndPos()).Magnitude() / LIGHT_POWER);
                }

                preHitCollision = currentNode->GetHitCollision();

                // このループ数最初の判定なら追加だけして次へ
                if (hitCollisionLineData.size() <= loopCount)
                {
                    // 情報を追加
                    hitCollisionLineData.push_back({{hitCollisionLine}});

                    areaRouteJudge.LightAreaRouteID += areaRouteJudge.PlusLightAreaRouteID;
                    // 追加IDナンバーがないから0を代入
                    areaRouteJudge.PlusLightAreaRouteID = 0;
                    areaRuteJudgeDatas.push_back({{areaRouteJudge}});
                }
                // 前に設定したことがあるから調べる
                else
                {
                    areaRouteJudge.LightAreaRouteID += areaRouteJudge.PlusLightAreaRouteID;
                    // 隣のはずの線からエリアルート判定情報取得
                    AREA_ROUTE_JUDGE_DATA& nowAreaRuteJudgeData = areaRuteJudgeDatas[loopCount].back().back();
                    areaRouteJudge.PlusLightAreaRouteID = nowAreaRuteJudgeData.PlusLightAreaRouteID;

                    const int lineDataIndexs[3] =
                    {
                        loopCount,
                        hitCollisionLineData[loopCount].size() - 1,
                        hitCollisionLineData[loopCount][hitCollisionLineData[loopCount].size() - 1].size() - 1
                    };
                    constexpr int LOOP_COUNT = 0;
                    constexpr int LIGHT_AREA_COUNT = 1;
                    constexpr int COLLISION_COUNT = 2;


                    /*ルートが違う*/
                    if (areaRouteJudge.LightAreaRouteID != nowAreaRuteJudgeData.LightAreaRouteID)
                    {
                        // 新しいライトエリアとして登録
                        hitCollisionLineData[lineDataIndexs[LOOP_COUNT]].push_back({hitCollisionLine});
                        areaRuteJudgeDatas[lineDataIndexs[LOOP_COUNT]].push_back({areaRouteJudge});
                    }
                    /*前回のノード数が少ない今のループより少ない
                      出だしが違うオブジェクト*/
                    else if (
                        ((preLoopCount != -1) && (preLoopCount <  loopCount)) ||
                        (hitCollisionLineData[lineDataIndexs[LOOP_COUNT]][lineDataIndexs[LIGHT_AREA_COUNT]][lineDataIndexs[COLLISION_COUNT]].PreHitCollision != hitCollisionLine.PreHitCollision))
                    {
                        // 新しいライトエリアとして登録IDを増やす)
                        hitCollisionLineData[lineDataIndexs[LOOP_COUNT]].push_back({hitCollisionLine});
                        areaRouteJudge.PlusLightAreaRouteID += 1;
                        areaRuteJudgeDatas[lineDataIndexs[LOOP_COUNT]].push_back({areaRouteJudge});
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
                        areaRuteJudgeDatas[lineDataIndexs[LOOP_COUNT]][lineDataIndexs[LIGHT_AREA_COUNT]][lineDataIndexs[COLLISION_COUNT]] = areaRouteJudge;
                    }
                    else
                    {
                        // 情報を追加
                        hitCollisionLineData[lineDataIndexs[LOOP_COUNT]][lineDataIndexs[LIGHT_AREA_COUNT]].push_back(hitCollisionLine);
                        areaRuteJudgeDatas[lineDataIndexs[LOOP_COUNT]][lineDataIndexs[LIGHT_AREA_COUNT]].push_back(areaRouteJudge);
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

// ライトエリアの描画
bool LightArea::SettingDrawLightAreaData(const std::vector<BaseCollision2D *> &objectCollBox, const std::vector<BaseCollision2D *> &mirrorCollBox)
{
    if (mbOffLight)
    {
        return false;
    }

    // 最大ノード数取得
    int setNodeMaxCount = -1;
    LightLineNode* currentNode;
    LightLineNode* nextNode;
    for (uint32_t i = 0; i < mnLightLineCount; ++i)
    {
        currentNode = this->GetFirstNodeBox()[i];

        if (currentNode == nullptr)
        {
            continue;
        }
        int nodeCount = 0;
        while (true)
        {
            // ノード数インクリメント
            ++nodeCount;
            // 次のノードがあるか確認
            if (!currentNode->AccessNext(&nextNode))
            {
                break;
            }
            // 次のノード設定
            currentNode = nextNode;
        }
        setNodeMaxCount = max(setNodeMaxCount, nodeCount);
    }
    mnNodeMaxCount = setNodeMaxCount;


    // 光の線取得
    this->munAddLightLineCount = 0;
    std::vector<std::vector<std::vector<HIT_COLLISION_LINE>>> hitCollisionLine = DrawLingAreaHitCollisionsGetProcess();
    std::vector<std::vector<std::vector<HIT_COLLISION_LINE>>> drawHitCollisionLine = hitCollisionLine;
    if (hitCollisionLine.size() == 0)
    {
        return false;
    }

    // 光の中に入る影の線をすべて描画用データとして追加する
    mstAddDrawHitCollisionLine.clear();
    for (int hitCollisionLinesIterator = 0; hitCollisionLinesIterator < hitCollisionLine.size(); ++hitCollisionLinesIterator)
    {
        for (int lightAreaIterator = 0; lightAreaIterator < hitCollisionLine[hitCollisionLinesIterator].size(); ++lightAreaIterator)
        {
            int drawHitCollisionLineIteratorPlusNumber = 0;
            for (int hitLineIndex = 0; (hitLineIndex + 1) < hitCollisionLine[hitCollisionLinesIterator][lightAreaIterator].size(); ++hitLineIndex)
            {
                if (hitCollisionLine[hitCollisionLinesIterator][lightAreaIterator][hitLineIndex].IsSetup)
                {
                    drawHitCollisionLineIteratorPlusNumber += SetupLightAreaForDrawing(hitCollisionLine[hitCollisionLinesIterator][lightAreaIterator], &drawHitCollisionLine[hitCollisionLinesIterator][lightAreaIterator], hitLineIndex, drawHitCollisionLineIteratorPlusNumber, &objectCollBox, &mirrorCollBox);
                }
            }
        }
    }

    // 追加した光ラインをノードにする
    {
        this->munAddLightLineCount = mstAddDrawHitCollisionLine.size();
        
        if (this->mlAddLightFirstNode.capacity() < this->munAddLightLineCount)
        {
            this->mlAddLightFirstNode.reserve(this->munAddLightLineCount);
        }
        
        void *setLightLineNodeObject = nullptr;
        for (uint32_t i = 0; i < this->munAddLightLineCount; i++)
        {
            HIT_COLLISION_LINE& addHitCollisionLine = mstAddDrawHitCollisionLine[i];
            if (addHitCollisionLine.PreHitCollision != nullptr)
            {
                setLightLineNodeObject = addHitCollisionLine.PreHitCollision->GetMyObject();
            }
            else
            {
                // コリジョンがnullのためライトオブジェクト設定
                setLightLineNodeObject = this->mpParentObject;
            }

            // 設定
            if (this->mlAddLightFirstNode.size() <= i)
            {
                // オブジェクトと開始ポジション
                this->mlAddLightFirstNode.push_back(new LightLineNode(setLightLineNodeObject, &addHitCollisionLine.LineStartPos));
                // 光線のアングル設定
                this->mlAddLineAngleBox.push_back(MyFunctions::GetArrangeRad((addHitCollisionLine.LineEndPos - addHitCollisionLine.LineStartPos).GetAngle()));
            }
            else
            {
                // オブジェクトと開始ポジション
                this->mlAddLightFirstNode[i]->SetParent(setLightLineNodeObject, &addHitCollisionLine.LineStartPos);
                // 光線のアングル設定
                this->mlAddLineAngleBox[i] = MyFunctions::GetArrangeRad((addHitCollisionLine.LineEndPos - addHitCollisionLine.LineStartPos).GetAngle());
            }
            // 追加の共通設定
            this->mlAddLightFirstNode[i]->SetNodeId(addHitCollisionLine.LightNodeId);
        }
    }

    if (this->munAddLightLineCount == 0)
    {
        return false;
    }
    return true;
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
int LightArea::SetupLightAreaForDrawing(const std::vector<HIT_COLLISION_LINE>& hitCollisionLine, std::vector<HIT_COLLISION_LINE>* drawHitCollisionLine, const size_t& lineIndex, const int& drawHitCollisionLineIteratorPlusNumber, const std::vector<BaseCollision2D *> *objectCollBox, const std::vector<BaseCollision2D *> *mirrorCollBox)
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

    // 角に当たらないようにずらす量
    VECTOR2D nowInnerPerpendicular;
    VECTOR2D nextInnerPerpendicular;
    // NowのEndから見たNextのEndの左右判定
    {
        VECTOR2D nowDirection = nowCheckHitLine.LineEndPos - nowCheckHitLine.LineStartPos;

        VECTOR2D toNext = nextCheckHitLine.LineEndPos - nowCheckHitLine.LineEndPos;

        VECTOR2D nowPerpendicular1 = VECTOR2D(-nowDirection.GetY(), nowDirection.GetX());

        VECTOR2D nowPerpendicular2 = VECTOR2D(nowDirection.GetY(), -nowDirection.GetX());

        float dot1 =
            nowPerpendicular1.GetX() * toNext.GetX() +
            nowPerpendicular1.GetY() * toNext.GetY();

        float dot2 =
            nowPerpendicular2.GetX() * toNext.GetX() +
            nowPerpendicular2.GetY() * toNext.GetY();

        // NextのEnd側を向いている垂直ベクトルを選択
        nowInnerPerpendicular = (dot1 > dot2) ? nowPerpendicular1 : nowPerpendicular2;
    }
    // NextのEndから見たNowのEndの左右判定
    {
        VECTOR2D nextDirection = nextCheckHitLine.LineEndPos - nextCheckHitLine.LineStartPos;

        VECTOR2D toNow = nowCheckHitLine.LineEndPos - nextCheckHitLine.LineEndPos;

        VECTOR2D nextPerpendicular1 = VECTOR2D(-nextDirection.GetY(), nextDirection.GetX());

        VECTOR2D nextPerpendicular2 = VECTOR2D(nextDirection.GetY(), -nextDirection.GetX());

        float dot1 =
            nextPerpendicular1.GetX() * toNow.GetX() +
            nextPerpendicular1.GetY() * toNow.GetY();

        float dot2 =
            nextPerpendicular2.GetX() * toNow.GetX() +
            nextPerpendicular2.GetY() * toNow.GetY();

        // NowのEnd側を向いている垂直ベクトルを選択
        nextInnerPerpendicular = (dot1 > dot2) ? nextPerpendicular1 : nextPerpendicular2;
    }
    // 正規化してなるべく小さくする
    nowInnerPerpendicular.Normalize();
    nowInnerPerpendicular *= 0.0001f;
    nextInnerPerpendicular.Normalize();
    nextInnerPerpendicular *= 0.0001f;

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
                AddDrawLineToVertexBetweenLines(&addDrawHitCollisionLine, nowCheckHitLine.LineStartPos, nowCheckHitLine.LineEndPos, tempQuadrangle, vertexPositions, nowCheckHitLine.HitCollision, nowCheckHitLine.PreHitCollision, nextCheckHitLine.HitCollision, true, nowCheckHitLine.LightStartAlphaRange, nowCheckHitLine.LightIntensity);
                break;
            }
            // 次のラインが当たっている当たり判定の角が参照ラインと次のラインの間か調べる
            else if (nowCheckHitLine.HitCollision == nullptr)
            {
                std::vector<VECTOR2D> vertexPositions = GetVertexPositions(nextCheckHitLine.HitCollision, nextCheckHitLine.LineStartPos);
                AddDrawLineToVertexBetweenLines(&addDrawHitCollisionLine, nowCheckHitLine.LineStartPos, nowCheckHitLine.LineEndPos, tempQuadrangle, vertexPositions, nextCheckHitLine.HitCollision, nextCheckHitLine.PreHitCollision, nowCheckHitLine.HitCollision, false, nowCheckHitLine.LightStartAlphaRange, nowCheckHitLine.LightIntensity);
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
                        addDrawHitCollisionLine.push_back(HIT_COLLISION_LINE(nowCheckHitLine.HitCollision, nowCheckHitLine.PreHitCollision, nextCheckHitLine.HitCollision, nowCheckHitLine.LineStartPos, intersectionPos[intersectionPosIndex], nowCheckHitLine.LightStartAlphaRange, nowCheckHitLine.LightStartAlphaRange, nowCheckHitLine.LightIntensity + (0.5f / (float)mnLightLineCount)));
                        if (nowCheckHitLine.LineStartPos != nextCheckHitLine.LineStartPos)
                        {
                            addDrawHitCollisionLine.push_back(HIT_COLLISION_LINE(nextCheckHitLine.HitCollision, nextCheckHitLine.PreHitCollision, nowCheckHitLine.HitCollision, nextCheckHitLine.LineStartPos, intersectionPos[intersectionPosIndex], nextCheckHitLine.LightStartAlphaRange, nextCheckHitLine.LightStartAlphaRange, nowCheckHitLine.LightIntensity + (0.5f / (float)mnLightLineCount)));
                        }
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
                std::vector<VECTOR2D> excludeVertexPositions;

                // 現在の光ラインが当たっているコリジョン
                {
                    vertexPositions = GetVertexPositions(nowCheckHitLine.HitCollision, nowCheckHitLine.LineStartPos, &nextCheckHitLine.LineStartPos);
                    setAddDrawHitCollisionLine.clear();
                    excludeVertexPositions.clear();
                    AddDrawLineToVertexBetweenLines(&setAddDrawHitCollisionLine, nextCheckHitLine.LineStartPos, nowCheckHitLine.LineEndPos, tempQuadrangle, vertexPositions, nowCheckHitLine.HitCollision, nowCheckHitLine.PreHitCollision, nextCheckHitLine.HitCollision, true, nextCheckHitLine.LightStartAlphaRange, nowCheckHitLine.LightIntensity, &excludeVertexPositions);
                    if (0 < setAddDrawHitCollisionLine.size())
                    {
                        HIT_COLLISION_LINE setExtendedLight = setAddDrawHitCollisionLine[setAddDrawHitCollisionLine.size() - 1];
                        if (GettingExtendedLight(setExtendedLight, nextCheckHitLine, &setExtendedLight, nowInnerPerpendicular))
                        {
                            // 当たり判定 点
                            Point2D tempPoint;
                            tempPoint.SetShapeParameter(setExtendedLight.LineEndPos);
                            // オブジェクトへの埋まり確認
                            BaseCollision2D* nowHitCollision = dynamic_cast<BaseCollision2D*>(nowCheckHitLine.HitCollision);
                            if ((nowHitCollision != nullptr) && !(0 <= BaseCollision2DManager::CheckHitCollision2DToCollision2D(&tempPoint, nowHitCollision).mnResultParam))
                            {
                                bool isSetExtendedLight = true;
                                Quadrangle2D extendedLightCollision;
                                extendedLightCollision.SetShapeParameter(nextCheckHitLine.LineStartPos, setExtendedLight.LineStartPos, setExtendedLight.LineEndPos, nextCheckHitLine.LineEndPos);
                                
                                LIGHT_EDGE_DATA nextCollisionPositions = GettingHitCollisionEdge(nextCheckHitLine);
                                for (int xcludeVertexIterator = 0; xcludeVertexIterator < excludeVertexPositions.size(); ++xcludeVertexIterator)
                                {
                                    tempPoint.SetShapeParameter(excludeVertexPositions[xcludeVertexIterator]);
                                    if (0 <= BaseCollision2DManager::CheckHitCollision2DToCollision2D(&extendedLightCollision, &tempPoint).mnResultParam)
                                    {
                                        setExtendedLight.LineEndPos = excludeVertexPositions[xcludeVertexIterator];
                                        setAddDrawHitCollisionLine.push_back(setExtendedLight);
                                        if (GettingExtendedLight(setExtendedLight, nextCheckHitLine, &setExtendedLight, nowInnerPerpendicular))
                                        {
                                            isSetExtendedLight = true;
                                        }
                                        else
                                        {
                                            isSetExtendedLight = false;
                                        }
                                        extendedLightCollision.SetShapeParameter(nextCheckHitLine.LineStartPos, setExtendedLight.LineStartPos, setExtendedLight.LineEndPos, nextCheckHitLine.LineEndPos);
                                    }
                                    else
                                    {
                                        if (!nextCollisionPositions.IsExist)
                                        {
                                            continue;
                                        }

                                        VECTOR2D intersectionPos;

                                        // 関係辺
                                        std::vector<LIGHT_EDGE_DATA> connectedEdges = GetVisibleEdges(nowCheckHitLine.HitCollision, nowCheckHitLine.LineStartPos, &nextCheckHitLine.LineStartPos);

                                        for (const LIGHT_EDGE_DATA& connectedEdgesIterator : connectedEdges)
                                        {
                                            if ((connectedEdgesIterator.LineOne != excludeVertexPositions[xcludeVertexIterator]) &&
                                                (connectedEdgesIterator.LineTwo != excludeVertexPositions[xcludeVertexIterator]))
                                            {
                                                continue;
                                            }

                                            if (GetIntersectionPosition(
                                                nextCollisionPositions.LineOne,
                                                nextCollisionPositions.LineTwo,
                                                connectedEdgesIterator.LineOne,
                                                connectedEdgesIterator.LineTwo,
                                                &intersectionPos))
                                            {
                                                tempPoint.SetShapeParameter(intersectionPos);
                                                if (0 <= BaseCollision2DManager::CheckHitCollision2DToCollision2D(&extendedLightCollision, &tempPoint).mnResultParam)
                                                {
                                                    isSetExtendedLight = false;
                                                    setExtendedLight.LineEndPos = intersectionPos;
                                                    setAddDrawHitCollisionLine.push_back(setExtendedLight);
                                                    extendedLightCollision.SetShapeParameter(nextCheckHitLine.LineStartPos, setExtendedLight.LineStartPos, setExtendedLight.LineEndPos, nextCheckHitLine.LineEndPos);
                                                }
                                            }
                                        }
                                    }
                                }

                                if (isSetExtendedLight)
                                {
                                    setAddDrawHitCollisionLine.push_back(setExtendedLight);
                                }
                            }
                        }
                        isAddDrawHitCollisionLine = true;
                        addDrawHitCollisionLine.insert(addDrawHitCollisionLine.end(), setAddDrawHitCollisionLine.begin(), setAddDrawHitCollisionLine.end());
                    }
                }

                // 次の光ラインが当たっているコリジョン
                {
                    vertexPositions = GetVertexPositions(nextCheckHitLine.HitCollision, nowCheckHitLine.LineStartPos, &nextCheckHitLine.LineStartPos);
                    setAddDrawHitCollisionLine.clear();
                    excludeVertexPositions.clear();
                    AddDrawLineToVertexBetweenLines(&setAddDrawHitCollisionLine, nowCheckHitLine.LineStartPos, nowCheckHitLine.LineEndPos, tempQuadrangle, vertexPositions, nextCheckHitLine.HitCollision, nextCheckHitLine.PreHitCollision, nowCheckHitLine.HitCollision, false, nowCheckHitLine.LightStartAlphaRange, nowCheckHitLine.LightIntensity, &excludeVertexPositions);
                    if (0 < setAddDrawHitCollisionLine.size())
                    {
                        HIT_COLLISION_LINE setExtendedLight = setAddDrawHitCollisionLine[0];
                        if (GettingExtendedLight(setExtendedLight, nowCheckHitLine, &setExtendedLight, nextInnerPerpendicular))
                        {
                            // 当たり判定 点
                            Point2D tempPoint;
                            tempPoint.SetShapeParameter(setExtendedLight.LineEndPos);
                            // オブジェクトへの埋まり確認
                            BaseCollision2D* nextHitCollision = dynamic_cast<BaseCollision2D*>(nextCheckHitLine.HitCollision);
                            if ((nextHitCollision != nullptr) && !(0 <= BaseCollision2DManager::CheckHitCollision2DToCollision2D(&tempPoint, nextHitCollision).mnResultParam))
                            {
                                bool isSetExtendedLight = true;
                                Quadrangle2D extendedLightCollision;
                                extendedLightCollision.SetShapeParameter(nowCheckHitLine.LineStartPos, setExtendedLight.LineStartPos, setExtendedLight.LineEndPos, nowCheckHitLine.LineEndPos);
                                
                                LIGHT_EDGE_DATA nowCollisionPositions = GettingHitCollisionEdge(nowCheckHitLine);
                                for (int xcludeVertexIterator = 0; xcludeVertexIterator < excludeVertexPositions.size(); ++xcludeVertexIterator)
                                {
                                    tempPoint.SetShapeParameter(excludeVertexPositions[xcludeVertexIterator]);
                                    if (0 <= BaseCollision2DManager::CheckHitCollision2DToCollision2D(&extendedLightCollision, &tempPoint).mnResultParam)
                                    {
                                        setExtendedLight.LineEndPos = excludeVertexPositions[xcludeVertexIterator];
                                        setAddDrawHitCollisionLine.insert(setAddDrawHitCollisionLine.begin(), setExtendedLight);
                                        if (GettingExtendedLight(setExtendedLight, nowCheckHitLine, &setExtendedLight, nextInnerPerpendicular))
                                        {
                                            isSetExtendedLight = true;
                                        }
                                        else
                                        {
                                            isSetExtendedLight = false;
                                        }
                                        extendedLightCollision.SetShapeParameter(nowCheckHitLine.LineStartPos, setExtendedLight.LineStartPos, setExtendedLight.LineEndPos, nowCheckHitLine.LineEndPos);
                                    }
                                    else
                                    {
                                        if (!nowCollisionPositions.IsExist)
                                        {
                                            continue;
                                        }

                                        VECTOR2D intersectionPos;

                                        // 関係辺
                                        std::vector<LIGHT_EDGE_DATA> connectedEdges = GetVisibleEdges(nextCheckHitLine.HitCollision, nowCheckHitLine.LineStartPos);

                                        for (const LIGHT_EDGE_DATA& connectedEdgesIterator : connectedEdges)
                                        {
                                            if ((connectedEdgesIterator.LineOne != excludeVertexPositions[xcludeVertexIterator]) &&
                                                (connectedEdgesIterator.LineTwo != excludeVertexPositions[xcludeVertexIterator]))
                                            {
                                                continue;
                                            }

                                            if (GetIntersectionPosition(
                                                nowCollisionPositions.LineOne,
                                                nowCollisionPositions.LineTwo,
                                                connectedEdgesIterator.LineOne,
                                                connectedEdgesIterator.LineTwo,
                                                &intersectionPos))
                                            {
                                                tempPoint.SetShapeParameter(intersectionPos);
                                                if (0 <= BaseCollision2DManager::CheckHitCollision2DToCollision2D(&extendedLightCollision, &tempPoint).mnResultParam)
                                                {
                                                    isSetExtendedLight = false;
                                                    setExtendedLight.LineEndPos = intersectionPos;
                                                    setAddDrawHitCollisionLine.insert(setAddDrawHitCollisionLine.begin(), setExtendedLight);
                                                    extendedLightCollision.SetShapeParameter(nowCheckHitLine.LineStartPos, setExtendedLight.LineStartPos, setExtendedLight.LineEndPos, nowCheckHitLine.LineEndPos);
                                                }
                                            }
                                        }
                                    }
                                }

                                if (isSetExtendedLight)
                                {
                                    setAddDrawHitCollisionLine.insert(setAddDrawHitCollisionLine.begin(), setExtendedLight);
                                }
                            }
                        }
                        isAddDrawHitCollisionLine = true;
                        addDrawHitCollisionLine.insert(addDrawHitCollisionLine.end(), setAddDrawHitCollisionLine.begin(), setAddDrawHitCollisionLine.end());
                    }
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
                extendedQuadrangle.SetShapeParameter(extendedNowLight.LineStartPos, extendedNextLight.LineStartPos, extendedNextLight.LineEndPos, extendedNowLight.LineEndPos);

                // 延長後の範囲内にある角を取得
                {
                    std::vector<HIT_COLLISION_LINE> setAddDrawHitCollisionLine;
                    std::vector<VECTOR2D> vertexPositions;

                    // 現在のオブジェクト
                    vertexPositions = GetVertexPositions(nowCheckHitLine.HitCollision, nextCheckHitLine.LineStartPos);

                    AddDrawLineToVertexBetweenLines(&setAddDrawHitCollisionLine, nextCheckHitLine.LineStartPos, extendedNowLight.LineEndPos, extendedQuadrangle, vertexPositions, nowCheckHitLine.HitCollision, nowCheckHitLine.PreHitCollision, nextCheckHitLine.HitCollision, true, nextCheckHitLine.LightStartAlphaRange, nowCheckHitLine.LightIntensity);

                    if (!setAddDrawHitCollisionLine.empty())
                    {
                        // 追加した角から次のオブジェクトまで光を伸ばす
                        HIT_COLLISION_LINE setExtendedLight = setAddDrawHitCollisionLine.back();

                        if (GettingExtendedLight(setExtendedLight, nextCheckHitLine, &setExtendedLight, nowInnerPerpendicular))
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
                    vertexPositions = GetVertexPositions(nextCheckHitLine.HitCollision, nowCheckHitLine.LineStartPos);

                    AddDrawLineToVertexBetweenLines(&setAddDrawHitCollisionLine, nowCheckHitLine.LineStartPos, extendedNextLight.LineEndPos, extendedQuadrangle, vertexPositions, nextCheckHitLine.HitCollision, nextCheckHitLine.PreHitCollision, nowCheckHitLine.HitCollision, false, nowCheckHitLine.LightStartAlphaRange, nowCheckHitLine.LightIntensity);

                    if (!setAddDrawHitCollisionLine.empty())
                    {
                        // 追加した角から現在のオブジェクトまで光を伸ばす
                        HIT_COLLISION_LINE setExtendedLight = setAddDrawHitCollisionLine[0];

                        if (GettingExtendedLight(setExtendedLight, nowCheckHitLine, &setExtendedLight, nextInnerPerpendicular))
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
            AddDrawLineToVertexBetweenLines(&addDrawHitCollisionLine, nowCheckHitLine.LineStartPos, nowCheckHitLine.LineEndPos, tempQuadrangle, vertexPositions, nowCheckHitLine.HitCollision, nowCheckHitLine.PreHitCollision, nextCheckHitLine.HitCollision, true, nowCheckHitLine.LightStartAlphaRange, nowCheckHitLine.LightIntensity);
        }
    } while (false);

    constexpr int INSERT_AFTER_REFERENCED_LINE_OFFSET = 1;

    VECTOR2D start2current;
    float s2cMagNoSqrt = 0.0f;
    Ray2D tempRay;
    CollisionCheckResult2D tempResultCurrent;
    // 追加ラインが対象コリジョン以外にも当たっている場合縮めて反映
    for (auto addDrawLineIterator = addDrawHitCollisionLine.begin(); addDrawLineIterator != addDrawHitCollisionLine.end();)
    {
        // 既存の光ラインと完全に重複している場合は削除
        if (((addDrawLineIterator->LineStartPos == nowCheckHitLine.LineStartPos) && (addDrawLineIterator->LineEndPos == nowCheckHitLine.LineEndPos)) ||
            ((addDrawLineIterator->LineStartPos == nextCheckHitLine.LineStartPos) && (addDrawLineIterator->LineEndPos == nextCheckHitLine.LineEndPos)))
        {
            addDrawLineIterator = addDrawHitCollisionLine.erase(addDrawLineIterator);
            continue;
        }

        addDrawLineIterator->LightNodeId = nextCheckHitLine.LightNodeId;

        addDrawLineIterator->LightEndAlphaRange = addDrawLineIterator->LightStartAlphaRange + ((addDrawLineIterator->LineStartPos - addDrawLineIterator->LineEndPos).Magnitude() / LIGHT_POWER);

        if ((objectCollBox == nullptr) || (mirrorCollBox == nullptr))
        {
            ++addDrawLineIterator;
            continue;
        }

        tempRay.SetShapeParameter(addDrawLineIterator->LineStartPos, addDrawLineIterator->LineEndPos);
        for (BaseCollision2D* objectCollIterator : *objectCollBox)
        {
            // 対象値判定が自信か当たっている当たり判定なら次へ
            if ((objectCollIterator->GetMyObject2D() == this->mpParentObject) ||
                ((addDrawLineIterator->HitCollision != nullptr) &&
                (objectCollIterator->GetMyObject2D() == addDrawLineIterator->HitCollision->GetMyObject2D())) ||
                ((addDrawLineIterator->PreHitCollision != nullptr) &&
                (objectCollIterator->GetMyObject2D() == addDrawLineIterator->PreHitCollision->GetMyObject2D())) ||
                ((addDrawLineIterator->OtherCollision != nullptr) &&
                (objectCollIterator->GetMyObject2D() == addDrawLineIterator->OtherCollision->GetMyObject2D())))
            {
                continue;
            }

            // 当たっているか取得
            tempResultCurrent = BaseCollision2DManager::CheckHitCollision2DToCollision2D(objectCollIterator, &tempRay);
            
            // 当たっていなかった場合は次へ
            if (tempResultCurrent.mnResultParam < 0)
            {
                continue;
            }
            

            // 今回のレイの開始地点から、当たった場所までの距離を取得する
            start2current = tempResultCurrent.mvHitPos - tempRay.GetStartPos();
            s2cMagNoSqrt = start2current.MagnitudeNoSqrt();

            // スタート地点からあまりにも近すぎたら次へ
            if (MyFunctions::EqualInRangeF(s2cMagNoSqrt, 0.0f, 0.01f))
            {
                continue;
            }

            // 当たっているため線を縮める
            {
                addDrawLineIterator->LineEndPos = tempResultCurrent.mvHitPos;
                tempRay.SetShapeParameter(addDrawLineIterator->LineStartPos, addDrawLineIterator->LineEndPos);
            }
        }

        for (BaseCollision2D*  mirrorCollIterator : *mirrorCollBox)
        {
            // 対象値判定が自信か当たっている当たり判定なら次へ
            if ((mirrorCollIterator->GetMyObject2D() == this->mpParentObject) ||
                ((addDrawLineIterator->HitCollision != nullptr) &&
                (mirrorCollIterator->GetMyObject2D() == addDrawLineIterator->HitCollision->GetMyObject2D())) ||
                ((addDrawLineIterator->PreHitCollision != nullptr) &&
                (mirrorCollIterator->GetMyObject2D() == addDrawLineIterator->PreHitCollision->GetMyObject2D())) ||
                ((addDrawLineIterator->OtherCollision != nullptr) &&
                (mirrorCollIterator->GetMyObject2D() == addDrawLineIterator->OtherCollision->GetMyObject2D())))
            {
                continue;
            }

            // 当たっているか取得
            tempResultCurrent = BaseCollision2DManager::CheckHitCollision2DToCollision2D(mirrorCollIterator, &tempRay);
            
            // 当たっていなかった場合は次へ
            if (tempResultCurrent.mnResultParam < 0)
            {
                continue;
            }
            

            // 今回のレイの開始地点から、当たった場所までの距離を取得する
            start2current = tempResultCurrent.mvHitPos - tempRay.GetStartPos();
            s2cMagNoSqrt = start2current.MagnitudeNoSqrt();

            // スタート地点からあまりにも近すぎたら次へ
            if (MyFunctions::EqualInRangeF(s2cMagNoSqrt, 0.0f, 0.01f))
            {
                continue;
            }

            // 当たっているため線を縮める
            {
                addDrawLineIterator->LineEndPos = tempResultCurrent.mvHitPos;
                tempRay.SetShapeParameter(addDrawLineIterator->LineStartPos, addDrawLineIterator->LineEndPos);
            }
        }
        ++addDrawLineIterator;
    }

    // 追加されたラインを反映
    drawHitCollisionLine->insert(drawHitCollisionLine->begin() + lineIndex + drawHitCollisionLineIteratorPlusNumber + INSERT_AFTER_REFERENCED_LINE_OFFSET, addDrawHitCollisionLine.begin(), addDrawHitCollisionLine.end());
    mstAddDrawHitCollisionLine.insert(mstAddDrawHitCollisionLine.end(), addDrawHitCollisionLine.begin(), addDrawHitCollisionLine.end());

    return addDrawHitCollisionLine.size();
}

// 角を取得する
std::vector<VECTOR2D> LightArea::GetVertexPositions(BaseCollision* collision, const VECTOR2D& viewPos1, const VECTOR2D* viewPos2)
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
            const float viewX1 = viewPos1.GetX() - edgeStart.GetX();
            const float viewY1 = viewPos1.GetY() - edgeStart.GetY();

            // 外積による可視判定
            const float cross1 = edgeX * viewY1 - edgeY * viewX1;

            // 視点側を向いていない辺があれば除外
            if (cross1 < 0.0f)
            {
                // 調べている頂点がこの辺の始点または終点なら除外
                if (&vertexPos == &edgeStart || &vertexPos == &edgeEnd)
                {
                    isVisible = true;
                    break;
                }
            }

            if (viewPos2 != nullptr)
            {
                // 辺の始点から視点へのベクトル
                const float viewX2 = viewPos2->GetX() - edgeStart.GetX();
                const float viewY2 = viewPos2->GetY() - edgeStart.GetY();
                // 外積による可視判定
                const float cross2 = edgeX * viewY2 - edgeY * viewX2;

                if (cross2 < 0.0f)
                {
                    // 調べている頂点がこの辺の始点または終点なら除外
                    if (&vertexPos == &edgeStart || &vertexPos == &edgeEnd)
                    {
                        isVisible = true;
                        break;
                    }
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
std::vector<LIGHT_EDGE_DATA> LightArea::GetVisibleEdges(BaseCollision* collision, const VECTOR2D& viewPos1, const VECTOR2D* viewPos2)
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
            const float viewX1 = viewPos1.GetX() - edgeStart.GetX();
            const float viewY1 = viewPos1.GetY() - edgeStart.GetY();

            // 外積による可視判定
            const float cross1 = edgeX * viewY1 - edgeY * viewX1;

            // 視点側を向いていない辺があれば除外
            if (cross1 < 0.0f)
            {
                // 調べている頂点がこの辺の始点または終点なら除外
                if (&vertexPos == &edgeStart || &vertexPos == &edgeEnd)
                {
                    isVisible = true;
                    break;
                }
            }

            if (viewPos2 != nullptr)
            {
                // 辺の始点から視点へのベクトル
                const float viewX2 = viewPos2->GetX() - edgeStart.GetX();
                const float viewY2 = viewPos2->GetY() - edgeStart.GetY();
                // 外積による可視判定
                const float cross2 = edgeX * viewY2 - edgeY * viewX2;

                if (cross2 < 0.0f)
                {
                    // 調べている頂点がこの辺の始点または終点なら除外
                    if (&vertexPos == &edgeStart || &vertexPos == &edgeEnd)
                    {
                        isVisible = true;
                        break;
                    }
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
bool LightArea::AddDrawLineToVertexBetweenLines(std::vector<HIT_COLLISION_LINE>* addDrawHitCollisionLine, const VECTOR2D& startPos, const VECTOR2D& endPos, Quadrangle2D& tempQuadrangle, std::vector<VECTOR2D>& vertexPositions, BaseCollision* hitCollision, BaseCollision* preHitCollision, BaseCollision* otherHitCollision, bool isEqualAngleFrontSet, float startAlphaRange, float lightIntensity, std::vector<VECTOR2D>* excludeVertexPositions)
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
            addDrawHitCollisionLine->push_back(HIT_COLLISION_LINE(hitCollision, preHitCollision, otherHitCollision, startPos, vertexPosition, startAlphaRange, startAlphaRange, lightIntensity + (0.5f / (float)mnLightLineCount)));
        }
        else if (excludeVertexPositions != nullptr)
        {
            excludeVertexPositions->push_back(vertexPosition);
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
bool LightArea::GettingExtendedLight(const HIT_COLLISION_LINE& extendedLightLine, const HIT_COLLISION_LINE& hitCollisionLine, HIT_COLLISION_LINE* setExtendedLight, const VECTOR2D& shiftVec)
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

    // 交点が光の延長方向にあり、衝突辺の線分内にあるか確認
    if (t < 0.0f || u < 0.0f || u > 1.0f)
    {
        return false;
    }

    // 交点を保存
    VECTOR2D lightEndPos = VECTOR2D(lightStart.GetX() + lightX * t, lightStart.GetY() + lightY * t);
    // 1単位ずらす
    lightEndPos += shiftVec;

    // 光の終点を変更
    setExtendedLight->LineEndPos = lightEndPos;

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

// 2つの線分の交差点を取得
bool LightArea::GetIntersectionPosition(const VECTOR2D& lineOneStart, const VECTOR2D& lineOneEnd, const VECTOR2D& lineTwoStart, const VECTOR2D& lineTwoEnd, VECTOR2D* intersectionPos)
{
    const VECTOR2D lineOneDirection = lineOneEnd - lineOneStart;
    const VECTOR2D lineTwoDirection = lineTwoEnd - lineTwoStart;

    const float denominator =
        lineOneDirection.GetX() * lineTwoDirection.GetY() -
        lineOneDirection.GetY() * lineTwoDirection.GetX();

    // 平行または同一直線上なら交差点なし
    if (fabsf(denominator) <= 0.0001f)
    {
        return false;
    }

    const VECTOR2D diff = lineTwoStart - lineOneStart;

    const float lineOneRatio = (diff.GetX() * lineTwoDirection.GetY() - diff.GetY() * lineTwoDirection.GetX()) / denominator;
    const float lineTwoRatio = (diff.GetX() * lineOneDirection.GetY() - diff.GetY() * lineOneDirection.GetX()) / denominator;

    // 両方の線分の範囲内で交差しているか確認
    if (lineOneRatio < 0.0f || lineOneRatio > 1.0f ||
        lineTwoRatio < 0.0f || lineTwoRatio > 1.0f)
    {
        return false;
    }

    *intersectionPos = lineOneStart + (lineOneDirection * lineOneRatio);

    return true;
}

// 3角情報にして描画
void LightArea::SettingDrawHitCollisionLineData(const std::vector<std::vector<std::vector<HIT_COLLISION_LINE>>> &hitCollisionLineData)
{
    // 四角設定用変数設定
    constexpr unsigned int boxIndexMax = 4;
    VERTEX2D setBoxPosDatas[boxIndexMax];
    {
        VERTEX2D startBoxPosData;
        startBoxPosData.rhw = 1.0f;
        startBoxPosData.dif = GetColorU8(((mnLightColor & 0xff0000) >> 16), ((mnLightColor & 0x00ff00) >> 8), (mnLightColor & 0x0000ff), 255);//GetColorU8(((/*mnLightColor*/0xffffff & 0xff0000) >> 16), ((/*mnLightColor*/0xffffff & 0x00ff00) >> 8), (/*mnLightColor*/0xffffff & 0x0000ff), 255);
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
                    // ポジション
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

                    // アルファ値
                    {
                        static constexpr float LIGHT_ALPHA_MIN = 255.0f * 0.55f;
                        static constexpr float LIGHT_ALPHA_RANGE = 255.0f - LIGHT_ALPHA_MIN;

                        static constexpr float LIGHT_INTENSITY_MIN = 0.5f;
                        static constexpr float LIGHT_INTENSITY_RANGE = 1.0f - LIGHT_INTENSITY_MIN;

                        float lightLeftDataStartAlpha = min(1.0f, SetupLightAlphaRange(hitCollisionLineData[lightAreaIterator][i][l].LightStartAlphaRange)) * (LIGHT_INTENSITY_MIN + (LIGHT_INTENSITY_RANGE * (hitCollisionLineData[lightAreaIterator][i][l].LightIntensity)));
                        float lightLeftDataEndAlpha = min(1.0f, SetupLightAlphaRange(hitCollisionLineData[lightAreaIterator][i][l].LightEndAlphaRange)) * (LIGHT_INTENSITY_MIN + (LIGHT_INTENSITY_RANGE * (hitCollisionLineData[lightAreaIterator][i][l].LightIntensity)));
                        float lightRightDataStartAlpha = min(1.0f, SetupLightAlphaRange(hitCollisionLineData[lightAreaIterator][i][l + 1].LightStartAlphaRange)) * (LIGHT_INTENSITY_MIN + (LIGHT_INTENSITY_RANGE * (hitCollisionLineData[lightAreaIterator][i][l + 1].LightIntensity)));
                        float lightRightDataEndAlpha = min(1.0f, SetupLightAlphaRange(hitCollisionLineData[lightAreaIterator][i][l + 1].LightEndAlphaRange)) * (LIGHT_INTENSITY_MIN + (LIGHT_INTENSITY_RANGE * (hitCollisionLineData[lightAreaIterator][i][l + 1].LightIntensity)));

                        setBoxPosDatas[0].dif = GetColorU8(setBoxPosDatas[0].dif.r, setBoxPosDatas[0].dif.g, setBoxPosDatas[0].dif.b, LIGHT_ALPHA_MIN + (LIGHT_ALPHA_RANGE * (1.0f - lightLeftDataStartAlpha)));
                        setBoxPosDatas[1].dif = GetColorU8(setBoxPosDatas[1].dif.r, setBoxPosDatas[1].dif.g, setBoxPosDatas[1].dif.b, LIGHT_ALPHA_MIN + (LIGHT_ALPHA_RANGE * (1.0f - lightLeftDataEndAlpha)));
                        setBoxPosDatas[2].dif = GetColorU8(setBoxPosDatas[2].dif.r, setBoxPosDatas[2].dif.g, setBoxPosDatas[2].dif.b, LIGHT_ALPHA_MIN + (LIGHT_ALPHA_RANGE * (1.0f - lightRightDataStartAlpha)));
                        setBoxPosDatas[3].dif = GetColorU8(setBoxPosDatas[3].dif.r, setBoxPosDatas[3].dif.g, setBoxPosDatas[3].dif.b, LIGHT_ALPHA_MIN + (LIGHT_ALPHA_RANGE * (1.0f - lightRightDataEndAlpha)));
                    }
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
    //// 設定した3角を全部描画
    //DRAW_SYSTEM::DrawPolygon(mstLightAreaTriangleVertex, munLightAreaTriangleSize / 3, Master::mpLightManager->GetLightAreaGraphHandle(), TRUE, false); 
}

// ライトアルファ値補正
float LightArea::SetupLightAlphaRange(float lightAlphaRange)
{
    static constexpr float LIGHT_POWER_RANGE = 0.00f;
    if (lightAlphaRange < LIGHT_POWER_RANGE)
    {
        lightAlphaRange = 0.0f;
    }
    else if (lightAlphaRange > 1.5f)
    {
        lightAlphaRange -= LIGHT_POWER_RANGE;
    }
    return lightAlphaRange;
}