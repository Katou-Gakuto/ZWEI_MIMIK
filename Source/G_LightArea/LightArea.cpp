#include "LightArea.h"

#include "LightLineNode.h"

#include "../S_Collision/BaseCollision2DManager.h"
#include "../S_Collision/Point2D.h"
#include "../S_Collision/Triangle2D.h"
#include "../S_Collision/Quadrangle2D.h"

#include "../Y_Tool/MyFunctions.h"

// 
LightArea::LightArea() :
    mlLightFirstNode(),
    mlLineAngleBox(),
    mpParentObject(nullptr),
    mnLightLineCount(0),
    mbOffLight(false),
    mbFinal2Start(false)
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
