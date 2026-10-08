#include "LightArea.h"

#include "LightLineNode.h"

#include "../S_Collision/BaseCollision2DManager.h"
#include "../S_Collision/Point2D.h"
#include "../S_Collision/Triangle2D.h"
#include "../S_Collision/Quadrangle2D.h"

#include "../Y_Tool/MyFunctions.h"

#include "Master.h"
#include "DxLibDataManager.h"
#include "LightAreaManager.h"

// 
LightArea::LightArea() :
    mlLightFirstNode(),
    mlLineAngleBox(),
    mpParentObject(nullptr),
    mnLightLineCount(0),
    mbOffLight(false),
    mbFinal2Start(false),
    mnLightColor(0xffffff),
    mstLightLine(),
    mstLightAreaTriangleVertex(nullptr),
    mnPreLightAreaTriangleVertexIndexCount(0)
{
}

// 
LightArea::~LightArea()
{
}

// 
void LightArea::SetParam(void *parentObject, uint32_t lineCount, float baseAngle, float lightAngle, bool final2start)
{
    // 
    this->mpParentObject = parentObject;

    // 
    this->mbFinal2Start = final2start;

    // 
    this->SetLightLineCount(lineCount);

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

        // 
        this->mlLineAngleBox[i] = MyFunctions::GetArrangeRad(startAngle + (oneAngle * static_cast<float>(i)));
    }
}

// 自身の光の終了地点を計算し、設定する関数
// 次のノードにつながる場合はtrueを返す
bool LightArea::CalculateNode(
    float baseAngle,
    float stockMagunitude,
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
    float tempMagnitudeNoSqrt = 0.0f;

    VECTOR2D tempStartPos;

    // 
    VECTOR2D toEndNorm;

    // 
    for (uint32_t i = 0; i < this->mnLightLineCount; i++)
    {
        // 
        tempStartPos = this->mlLightFirstNode[i]->GetListStartPos();

        // 
        toEndNorm = VECTOR2D::GetOnUnitCirclePos('x', 'y', baseAngle + this->mlLineAngleBox[i]);

        // 
        currentNode = this->mlLightFirstNode[i];

        // 
        tempMagnitudeNoSqrt = stockMagunitude;

        // 計算を行い、次のノードに移る場合は処理を行う
        while (currentNode->CalculateEndPos(
            tempStartPos,
            toEndNorm,
            objectCollBox,
            mirrorCollBox,
            tempMagnitudeNoSqrt,
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
    VECTOR2D lightStartPos = this->GetFirstNodeBox()[0]->GetListStartPos();

    // 
    CollisionCheckResult2D checkResult = GetCollisionCheckResult2DZero();

    // 
    for (size_t i = 0; i < this->mlLightFirstNode.size() - 1; i++)
    {
        // 
        tempTriangle.SetShapeParameter(
            lightStartPos,
            this->mlLightFirstNode[i]->GetMyEndPos(),
            this->mlLightFirstNode[i + 1]->GetMyEndPos());

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

    if (this->mbFinal2Start)
    {
        // 
        tempTriangle.SetShapeParameter(
            lightStartPos,
            this->mlLightFirstNode[this->mlLightFirstNode.size() - 1]->GetMyEndPos(),
            this->mlLightFirstNode[0]->GetMyEndPos());

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
    for (size_t i = 0; i < this->mlLightFirstNode.size(); i++)
    {
        // 
        if (this->mbFinal2Start)
        {
            firstNode = this->mlLightFirstNode[i];
            secondNode = this->mlLightFirstNode[(i + 1) % this->mlLightFirstNode.size()];
        }
        else
        {
            // 
            if (this->mlLightFirstNode.size() - 1 < i)
            {
                // 
                break;
            }

            // 
            firstNode = this->mlLightFirstNode[i];
            secondNode = this->mlLightFirstNode[i + 1];
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
                checkResult = BaseCollision2DManager::CheckHitCollision2DToCollision2D(&targetPoint, &tempTriangle);
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


// ライトエリアの描画
void LightArea::DrawLightArea()
{
    mstLightLine.clear();
    LightLineNode* currentNode;
    LightLineNode* nextNode;

    for (uint32_t i = 0; i < mnLightLineCount; ++i)
    {
        currentNode = this->GetFirstNodeBox()[i];

        if (currentNode == nullptr)
        {
            continue;
        }

        // ループ数
        int loopCount = 0;
        while (true)
        {

            // 情報保存
            LIGHT_DATA linePosData;
            linePosData.lineOne = currentNode->GetMyStartPos();
            linePosData.lineTwo = currentNode->GetMyEndPos();
            linePosData = GetScreenInsideLine(linePosData);

            // このループ数最初の判定なら追加だけして次へ
            if (mstLightLine.size() <= loopCount)
            {
                // 情報を追加
                mstLightLine.push_back({linePosData});
            }
            // 前に設定したことがあるから調べる
            else
            {
                /*このif判定順番厳守、配列の参照でエラー出る*/
                if (/*二つのラインで四角分がこれまでに作成されているか判定*/
                    (mstLightLine[loopCount].size() >= 2) &&
                    /*前の二つのラインを見て今のラインの頂点が両点座標が直線上にあるか判定*/
                    (IsPointOnLine(mstLightLine[loopCount][mstLightLine[loopCount].size() - 1/*後ろから1番目の配列参照*/].lineOne, mstLightLine[loopCount][mstLightLine[loopCount].size() - 2/*後ろから2番目の配列参照*/].lineOne, linePosData.lineOne) &&
                        IsPointOnLine(mstLightLine[loopCount][mstLightLine[loopCount].size() - 1/*後ろから1番目の配列参照*/].lineTwo, mstLightLine[loopCount][mstLightLine[loopCount].size() - 2/*後ろから2番目の配列参照*/].lineTwo, linePosData.lineTwo)))
                {
                    // 前回登録した情報を書き換える
                    mstLightLine[loopCount][mstLightLine[loopCount].size() - 1/*後ろから1番目の配列参照*/] = linePosData;
                }
                else
                {
                    // 情報を追加
                    mstLightLine[loopCount].push_back(linePosData);
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

    // 一周しているか
    if (mbFinal2Start && (0 < mnLightLineCount))
    {
        currentNode = this->GetFirstNodeBox()[0];
        if (currentNode != nullptr)
        {
            // ループ数
            int loopCount = 0;
            while (true)
            {

                // 情報保存
                LIGHT_DATA linePosData;
                linePosData.lineOne = currentNode->GetMyStartPos();
                linePosData.lineTwo = currentNode->GetMyEndPos();
                linePosData = GetScreenInsideLine(linePosData);

                // このループ数最初の判定なら追加だけして次へ
                if (mstLightLine.size() <= loopCount)
                {
                    // 情報を追加
                    mstLightLine.push_back({ linePosData });
                }
                // 前に設定したことがあるから調べる
                else
                {
                    /*このif判定順番厳守、配列の参照でエラー出る*/
                    if (/*二つのラインで四角分がこれまでに作成されているか判定*/
                        (mstLightLine[loopCount].size() >= 2) &&
                        /*前の二つのラインを見て今のラインの頂点が両点座標が直線上にあるか判定*/
                        (IsPointOnLine(mstLightLine[loopCount][mstLightLine[loopCount].size() - 1/*後ろから1番目の配列参照*/].lineOne, mstLightLine[loopCount][mstLightLine[loopCount].size() - 2/*後ろから2番目の配列参照*/].lineOne, linePosData.lineOne) &&
                            IsPointOnLine(mstLightLine[loopCount][mstLightLine[loopCount].size() - 1/*後ろから1番目の配列参照*/].lineTwo, mstLightLine[loopCount][mstLightLine[loopCount].size() - 2/*後ろから2番目の配列参照*/].lineTwo, linePosData.lineTwo)))
                    {
                        // 前回登録した情報を書き換える
                        mstLightLine[loopCount][mstLightLine[loopCount].size() - 1/*後ろから1番目の配列参照*/] = linePosData;
                    }
                    else
                    {
                        // 情報を追加
                        mstLightLine[loopCount].push_back(linePosData);
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

    // 何も登録されていないなら何もしない
    if (mstLightLine.size() <= 0)
    {
        return;
    }
    // 四角設定用変数設定
    constexpr unsigned int boxIndexMax = 4;
    VERTEX2D setBoxPosDatas[boxIndexMax];
    {
        VERTEX2D startBoxPosData;
        startBoxPosData.rhw = 1.0f;
        startBoxPosData.dif = GetColorU8(((mnLightColor & 0xff0000) >> 16), ((mnLightColor & 0x00ff00) >> 8), (mnLightColor & 0x0000ff), 255);
        startBoxPosData.u = 0.0f;
        startBoxPosData.v = 0.0f;
        for (int i = 0; i < boxIndexMax; ++i)
        {
            setBoxPosDatas[i] = startBoxPosData;
        }
    }
    
    // 三角形を入力する情報の数を測定
    unsigned int lightAreaTriangleSize = 0;
    for (int i = 0; i < mstLightLine.size(); ++i)
    {
        // 四角ができるか判定
        if (mstLightLine[i].size() < 2)
        {
            continue;
        }
        lightAreaTriangleSize += mstLightLine[i].size() - 1/*一番後ろは計測しない*/;
    }

    lightAreaTriangleSize *= 6;/*一つの4角で6個頂点を登録する*/

    if (mnPreLightAreaTriangleVertexIndexCount != lightAreaTriangleSize)
    {
        // 中に何か入っているなら消して新しくメモリを用意する
        if (mstLightAreaTriangleVertex != nullptr)
        {
            free(mstLightAreaTriangleVertex);
        }
        mstLightAreaTriangleVertex = static_cast<VERTEX2D*>(malloc(sizeof(VERTEX2D) * lightAreaTriangleSize));
        mnPreLightAreaTriangleVertexIndexCount = lightAreaTriangleSize;
    }

    // 四角を三角で設定
    unsigned int lightAreaIndex = 0;
    for (size_t i = 0; i < mstLightLine.size(); ++i)
    {
        // 四角ができるか判定
        if (mstLightLine[i].size() < 2)
        {
            continue;
        }
        for (size_t l = 0; l < (mstLightLine[i].size() - 1)/*四角にするために最後を除いて処理*/; ++l)
        {
            // 4頂点入力
            {
                LIGHT_DATA lightLeftData = mstLightLine[i][l];
                LIGHT_DATA lightRightData = mstLightLine[i][l + 1];

                setBoxPosDatas[0].pos = VGet(lightLeftData.lineOne.GetX(), lightLeftData.lineOne.GetY(), 0.0f);
                setBoxPosDatas[1].pos = VGet(lightLeftData.lineTwo.GetX(), lightLeftData.lineTwo.GetY(), 0.0f);
                setBoxPosDatas[2].pos = VGet(lightRightData.lineOne.GetX(), lightRightData.lineOne.GetY(), 0.0f);
                setBoxPosDatas[3].pos = VGet(lightRightData.lineTwo.GetX(), lightRightData.lineTwo.GetY(), 0.0f);
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
    DxLib::DrawPolygon2D(mstLightAreaTriangleVertex, lightAreaTriangleSize / 3, Master::mpLightManager->GetLightAreaGraphHandle(), TRUE); 
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

// 片方の点が画面外の場合、画面内に収まる位置まで線分を縮める
LightArea::LIGHT_DATA LightArea::GetScreenInsideLine(const LIGHT_DATA& linePos)
{
    LIGHT_DATA result = linePos;

    const float screenWidth = Master::mpDxLibDataManager->GetDisplaySize().GetX();
    const float screenHeight = Master::mpDxLibDataManager->GetDisplaySize().GetY();

    const VECTOR2D& pos1 = linePos.lineOne;
    const VECTOR2D& pos2 = linePos.lineTwo;

    // 両方とも画面内ならそのまま返す
    const bool pos1Inside = pos1.GetX() >= 0.0f && pos1.GetX() <= screenWidth &&
                            pos1.GetY() >= 0.0f && pos1.GetY() <= screenHeight;

    const bool pos2Inside = pos2.GetX() >= 0.0f && pos2.GetX() <= screenWidth &&
                            pos2.GetY() >= 0.0f && pos2.GetY() <= screenHeight;

    if (pos1Inside == pos2Inside)
    {
        return result;
    }

    // 画面内の点
    const VECTOR2D insidePos = pos1Inside ? pos1 : pos2;

    // 画面外の点
    const VECTOR2D outsidePos = pos1Inside ? pos2 : pos1;

    const VECTOR2D direction = outsidePos - insidePos;

    float nearestT = 1.0f;
    bool hasIntersection = false;

    // 左端
    if (direction.GetX() != 0.0f)
    {
        const float t = (0.0f - insidePos.GetX()) / direction.GetX();

        if (t >= 0.0f && t <= 1.0f)
        {
            const float y = insidePos.GetY() + direction.GetY() * t;

            if (y >= 0.0f && y <= screenHeight && t < nearestT)
            {
                nearestT = t;
                hasIntersection = true;
            }
        }
    }

    // 右端
    if (direction.GetX() != 0.0f)
    {
        const float t = (screenWidth - insidePos.GetX()) / direction.GetX();

        if (t >= 0.0f && t <= 1.0f)
        {
            const float y = insidePos.GetY() + direction.GetY() * t;

            if (y >= 0.0f && y <= screenHeight && t < nearestT)
            {
                nearestT = t;
                hasIntersection = true;
            }
        }
    }

    // 上端
    if (direction.GetY() != 0.0f)
    {
        const float t = (0.0f - insidePos.GetY()) / direction.GetY();

        if (t >= 0.0f && t <= 1.0f)
        {
            const float x = insidePos.GetX() + direction.GetX() * t;

            if (x >= 0.0f && x <= screenWidth && t < nearestT)
            {
                nearestT = t;
                hasIntersection = true;
            }
        }
    }

    // 下端
    if (direction.GetY() != 0.0f)
    {
        const float t = (screenHeight - insidePos.GetY()) / direction.GetY();

        if (t >= 0.0f && t <= 1.0f)
        {
            const float x = insidePos.GetX() + direction.GetX() * t;

            if (x >= 0.0f && x <= screenWidth && t < nearestT)
            {
                nearestT = t;
                hasIntersection = true;
            }
        }
    }

    if (hasIntersection)
    {
        const VECTOR2D newPos = insidePos + direction * nearestT;

        if (pos1Inside)
        {
            result.lineTwo = newPos;
        }
        else
        {
            result.lineOne = newPos;
        }
    }

    return result;
}