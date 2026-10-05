#include "LightArea.h"

#include "LightLineNode.h"

#include "../Y_Tool/MyFunctions.h"

// 
LightArea::LightArea() :
    mlLightFirstNode(),
    mlLineEndPosBox(),
    mlLineAngleBox(),
    mpParentObject(nullptr),
    mnLightLineCount(0),
    mbOffLight(false)
{
}

// 
LightArea::~LightArea()
{
}

// 
void LightArea::SetParam(void *parentObject, uint32_t lineCount, float baseAngle, float lightAngle)
{
    // 
    this->mpParentObject = parentObject;

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
            toEndNorm = VECTOR2D::Reflect(toEndNorm, tempResultNewr.mvRepulsionVecA.Normalize());

            // 
            if (!currentNode->AccessNext(&nextNode))
            {
                // 
                break;
            }

            // 
            currentNode = nextNode;
        }

        // 
        this->mlLineEndPosBox[i] = currentNode->GetMyEndPos();
    }

    // 
    return true;
}

// 
uint32_t LightArea::GetAllNodeCount() const
{
    // 
    uint32_t counter = 0;

    // 
    LightLineNode *current = nullptr;

    // 
    LightLineNode *next = nullptr;

    // 
    for (size_t i = 0; i < this->mlLightFirstNode.size(); i++)
    {
        // 
        current = this->mlLightFirstNode[i];

        // 
        while (current != nullptr)
        {
            // 
            if (current->AccessNext(&next))
            {
                // 
                counter++;

                // 
                current = next;
            }
            else
            {
                // 
                break;
            }
        }
    }

    // 
    return counter;
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
VECTOR2D *LightArea::GetLineEndPosBox()
{
    // 
    return this->mlLineEndPosBox.data();
}

// 
const VECTOR2D *LightArea::GetLineEndPosBox() const
{
    // 
    return this->mlLineEndPosBox.data();
}

// 
uint32_t LightArea::GetLightLineCount() const
{
    // 
    return this->mnLightLineCount;
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
        this->mlLineEndPosBox.resize(count);

        // 
        this->mlLineAngleBox.resize(count);
    }

    // 
    this->mnLightLineCount = count;
}

// 
bool LightArea::CheckInArea(const VECTOR2D &pos) const
{
    // 
    return false;
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
