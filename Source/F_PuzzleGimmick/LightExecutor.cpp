#include "LightExecutor.h"

#include "DxLib.h"

#include "../A_GameObject/GameObject2D.h"

#include "../E_Scene/BaseScene.h"
#include "../E_Scene/BaseSceneManager.h"

#include "../G_LightArea/LightLineNode.h"
#include "../G_LightArea/LightArea.h"
#include "../G_LightArea/LightAreaManager.h"

#include "../S_Collision/BaseCollision2D.h"
#include "../S_Collision/Ray2D.h"
#include "../S_Collision/BaseCollision2DManager.h"

#include "../Y_Tool/MyFunctions.h"

#include "../Z_Except/Master.h"

int gnDebugTest = 0;

// コンストラクタ
LightExecutor::LightExecutor(
    PuzzleGimmickActiveParam param,
    GameObject2D *parentObject,
    int lightAreaIndex,
    uint32_t lineCount,
    float baseAngle,
    float lightAngle,
    float lightLength,
    bool final2start) :
    mpParentObject(parentObject),
    mbLightOn(true),
    mbParamUpdate(false),
    mbFinal2Start(false),
    mnAreaIndex(lightAreaIndex),
    mnLineCount(lineCount),
    mfBaseAngle(baseAngle),
    mfLightAngle(lightAngle),
    mfLength(lightLength),
    BaseGimmickExecutor(param)
{
    // 
    this->SetLightLineCount(lineCount);

    // 
    this->SetLength(this->mfLength);

    // 
    this->SetBaseAngle(this->mfBaseAngle);

    // 
    this->SetLightAngle(lightAngle);

    // 
    this->SetFinal2Start(final2start);

    // 
    this->UpdateLightParam();
}

// デストラクタ
LightExecutor::~LightExecutor()
{
}

// ギミックの内容を実行する関数
// ※GameObject::EarlyUpdate()のタイミングで呼ばれます
int LightExecutor::EarlyUpdate(bool triggerSignal)
{
    // 
    if (this->GetActiveParam().GetSignalNot())
    {
        // 
        triggerSignal = !triggerSignal;
    }

    // 
    if (!triggerSignal)
    {
        // 
        return 0;
    }

    // 
    return 0;
}

// ギミックの内容を実行する関数
// ※GameObject::Update()のタイミングで呼ばれます
int LightExecutor::Update(bool triggerSignal)
{
    // 
    if (this->GetActiveParam().GetSignalNot())
    {
        // 
        triggerSignal = !triggerSignal;
    }

    // 
    this->mbLightOn = triggerSignal;

    // 
    return 0;
}

// ギミックの内容を実行する関数
// ※GameObject::LateUpdate()のタイミングで呼ばれます
int LightExecutor::LateUpdate(bool triggerSignal)
{
    // 
    if (this->mbLightOn)
    {
        // 
        this->GetMyLightArea()->OnLight();

        // 
        this->UpdateLightParam();

        // 
        this->CalculateLineEndPos();
    }
    else
    {
        // 
        this->GetMyLightArea()->OffLight();
    }

    // 
    return 0;
}

// シミュレーション内容を描画する関数
// ※既に実行段階である場合は引数がtrueになります。実行段階では描画しない、あるいはその逆の場合はこの引数を使ってください。
int LightExecutor::Draw(bool triggerSignal)
{
    // 
    if (!this->mbLightOn)
    {
        // 光域のシミュレーターは描画はしません
        return 0;
    }

    // 
    size_t firstIndex = 0;
    size_t secondIndex = 0;

    // 
    LightArea *lightArea = Master::mpLightManager->SearchArea(this->mnAreaIndex);
    LightLineNode *currentNode;
    LightLineNode *nextNode;

    // 
    auto nodeBox = lightArea->GetFirstNodeBox();

    // 
    int drawResult = 0;

    // 
    VECTOR2D baseStartPos = lightArea->GetStartPosition();

    // 
    int drawMode = 0;

    if (drawMode == 0)
    {
        // 
        for (uint32_t i = 0; i < lightArea->GetLightLineCount(); i++)
        {
            // 
            currentNode = lightArea->GetFirstNodeBox()[i];

            // 
            if (currentNode == nullptr)
            {
                // 
                continue;
            }

            // 
            while (true)
            {
                // 
                if (currentNode == lightArea->GetFirstNodeBox()[i] &&
                    !currentNode->CheckNext())
                {
                    // 
                    // break;
                }

                // デバッグ用レイの可視化
                //drawResult = DxLib::DrawLine(
                //    currentNode->GetMyStartPos().GetX(),
                //    currentNode->GetMyStartPos().GetY(),
                //    currentNode->GetMyEndPos().GetX(),
                //    currentNode->GetMyEndPos().GetY(),
                //    0x00ffff);

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
    else if (drawMode == 1)
    {

        // 
        for (uint32_t i = 0; i < lightArea->GetLightLineCount() - 1; i++)
        {
            // 
            drawResult = DxLib::DrawTriangle(
                baseStartPos.GetX(),
                baseStartPos.GetY(),
                nodeBox[i]->GetMyEndPos().GetX(),
                nodeBox[i]->GetMyEndPos().GetY(),
                nodeBox[i + 1]->GetMyEndPos().GetX(),
                nodeBox[i + 1]->GetMyEndPos().GetY(),
                0x00ffff,
                false);

            // 
            if (drawResult != 0)
            {
                // 
                break;
            }
        }

        // 
        if (drawResult != 0)
        {
            // 
            return drawResult;
        }

        // 
        firstIndex = 0;

        // 
        bool loopFlag = true;

        // 
        LightLineNode *firstNode = nullptr;
        LightLineNode *firstNodeNext = nullptr;
        LightLineNode *secondNode = nullptr;
        LightLineNode *secondNodeNext = nullptr;

        // 
        for (size_t i = 0; i < lightArea->GetLightLineCount() - 1; i++)
        {
            // 
            firstNode = nodeBox[i];
            secondNode = nodeBox[i + 1];

            // 
            loopFlag = true;

            // 
            while (loopFlag)
            {
                // 
                firstNode->AccessNext(&firstNodeNext);
                secondNode->AccessNext(&secondNodeNext);

                // 
                if (firstNodeNext != nullptr && secondNodeNext != nullptr)
                {
                    // 
                    drawResult = DxLib::DrawQuadrangle(
                        firstNode->GetMyEndPos().GetX(),
                        firstNode->GetMyEndPos().GetY(),
                        secondNode->GetMyEndPos().GetX(),
                        secondNode->GetMyEndPos().GetY(),
                        firstNodeNext->GetMyEndPos().GetX(),
                        firstNodeNext->GetMyEndPos().GetY(),
                        secondNodeNext->GetMyEndPos().GetX(),
                        secondNodeNext->GetMyEndPos().GetY(),
                        0x00ffff,
                        true);

                    // 
                    firstNode = firstNodeNext;
                    secondNode = secondNodeNext;
                }
                else if (firstNodeNext != nullptr && secondNodeNext == nullptr)
                {
                    // 
                    drawResult = DxLib::DrawTriangle(
                        firstNode->GetMyEndPos().GetX(),
                        firstNode->GetMyEndPos().GetY(),
                        secondNode->GetMyEndPos().GetX(),
                        secondNode->GetMyEndPos().GetY(),
                        firstNodeNext->GetMyEndPos().GetX(),
                        firstNodeNext->GetMyEndPos().GetY(),
                        0x00ffff,
                        true);

                    // 
                    loopFlag = false;
                }
                else if (firstNodeNext == nullptr && secondNodeNext != nullptr)
                {
                    // 
                    drawResult = DxLib::DrawTriangle(
                        firstNode->GetMyEndPos().GetX(),
                        firstNode->GetMyEndPos().GetY(),
                        secondNode->GetMyEndPos().GetX(),
                        secondNode->GetMyEndPos().GetY(),
                        secondNodeNext->GetMyEndPos().GetX(),
                        secondNodeNext->GetMyEndPos().GetY(),
                        0x00ffff,
                        true);

                    // 
                    loopFlag = false;
                }
                else
                {
                    // 
                    loopFlag = false;
                }
            }

            // 
            if (drawResult != 0)
            {
                // 
                break;
            }
        }
    }
    else if (drawMode == 2)
    {
        // 
        currentNode = nodeBox[gnDebugTest];

        // 
        while (true)
        {
            // 
            drawResult = DxLib::DrawLine(
                currentNode->GetMyStartPos().GetX(),
                currentNode->GetMyStartPos().GetY(),
                currentNode->GetMyEndPos().GetX(),
                currentNode->GetMyEndPos().GetY(),
                0x00ffff);

            // 
            if (currentNode->AccessNext(&nextNode))
            {
                // 
                currentNode = nextNode;
            }
            else
            {
                // 
                break;
            }
        }

        // 
        gnDebugTest++;

        // 
        gnDebugTest %= lightArea->GetLightLineCount();
    }

    // 
    return 0;
}

// このライトの光域を計算する関数
bool LightExecutor::CalculateLineEndPos()
{
    // 
    std::vector<BaseCollision2D *> objectCollisionBox;

    // 
    BaseScene *nowScene = Master::mpBaseSceneManager->SearchSceneNow();
    if (nowScene->GetBaseCollision2DManager()->SearchTag(CollisionTag::CollisionTag_Wall, objectCollisionBox) != 0)
    {
        // 
        return false;
    }

    // 
    std::vector<BaseCollision2D *> mirrorCollisionBox;
    if (nowScene->GetBaseCollision2DManager()->SearchTag(CollisionTag::CollisionTag_Mirror, mirrorCollisionBox) != 0)
    {
        // 
        return false;
    }

    // 
    Ray2D tempRay;

    // 
    CollisionCheckResult2D resultCurrent = GetCollisionCheckResult2DZero();

    // 
    CollisionCheckResult2D resultNewr = GetCollisionCheckResult2DZero();

    // 
    return this->GetMyLightArea()->CalculateNode(
        this->mfBaseAngle,
        this->mfLength,
        objectCollisionBox,
        mirrorCollisionBox,
        tempRay,
        resultCurrent,
        resultNewr);
}

// このライトのレイの本数を取得する関数
uint32_t LightExecutor::GetLightLineCount() const
{
    // 
    return this->GetMyLightArea()->GetLightLineCount();
}

// このライトの長さを取得する関数
float LightExecutor::GetLength() const
{
    // 
    return this->mfLength;
}

// このライトのレイの本数を設定する関数
void LightExecutor::SetLightLineCount(uint32_t count)
{
    // 
    this->mnLineCount = count;

    // 
    this->mbParamUpdate = true;
}

// このライトの長さを設定する関数
void LightExecutor::SetLength(float length)
{
    this->mfLength = length;

    // 
    this->mbParamUpdate = true;
}

// このライトの基本角度を設定する関数
void LightExecutor::SetBaseAngle(float radian)
{
    // 
    this->mfBaseAngle = radian;

    // 
    this->mbParamUpdate = true;
}

// このライトの全体の角度を設定する関数
void LightExecutor::SetLightAngle(float radian)
{
    this->mfLightAngle = radian;

    // 
    this->mbParamUpdate = true;
}

// 最後の線から最初の線の計算を行う関数
void LightExecutor::SetFinal2Start(bool flag)
{
    // 
    this->mbFinal2Start = flag;

    // 
    this->mbParamUpdate = true;
}

// 
LightArea *LightExecutor::GetMyLightArea() const
{
    // 
    return Master::mpLightManager->SearchArea(this->mnAreaIndex);
}

// 
bool LightExecutor::UpdateLightParam()
{
    // 
    if (this->mbParamUpdate)
    {
        // 
        this->GetMyLightArea()->SetParam(
            this->mpParentObject,
            this->mnLineCount,
            this->mfBaseAngle,
            this->mfLightAngle,
            this->mbFinal2Start);// HACK:_ ここmbParamUpdateだったけど変えた、川田に確認

        // 
        this->mbParamUpdate = false;
    }

    // 
    return true;
}
