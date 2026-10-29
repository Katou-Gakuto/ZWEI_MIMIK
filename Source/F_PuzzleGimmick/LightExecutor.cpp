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
#include "DrawSystem.h"

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
    mnLineCountInit(lineCount),
    mnLineCount(lineCount),
    mfBaseAngleInit(baseAngle), 
    mfBaseAngle(baseAngle),
    mfLightAngle(lightAngle),
    mfLength(lightLength),
    BaseGimmickExecutor(param)
{
    // 
    this->mnLineCount = this->mnLineCountInit;

    // 
    this->SetLength(this->mfLength);

    // 
    this->SetBaseAngle(this->mfBaseAngleInit);

    // 
    this->SetLightAngle(this->mfLightAngle);

    // 
    this->SetFinal2Start(this->mbFinal2Start);

    // 
    this->UpdateLightParam();
}

// デストラクタ
LightExecutor::~LightExecutor()
{
}

// 初期化
int LightExecutor::Initilize()
{
    // 
    this->mnLineCount = this->mnLineCountInit;

    // 
    this->SetBaseAngle(this->mfBaseAngleInit);

    // 
    this->UpdateLightParam();

    // 
    return 0;
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
    this->GetMyLightArea()->SetLightFlag(this->mbLightOn);


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

// 当たり判定によるギミックの変化に対応させる関数
int LightExecutor::HitOnCollision(BaseCollision *myCollision, BaseCollision *hitCollision)
{
    // 
    return 0;
}

// このライトの光域を計算する関数
bool LightExecutor::CalculateLineEndPos()
{
    // 
    std::vector<BaseCollision2D *> objectCollisionBox;

    // 
    BaseScene *nowScene = Master::mpBaseSceneManager->SearchSceneAuto();
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
            this->mbFinal2Start);

        // 
        this->mbParamUpdate = false;
    }

    // 
    return true;
}
