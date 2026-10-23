#include "RouteMoveExecutor.h"

#include "../A_GameObject/GameObject2D.h"
#include "../A_GameObject/LightObject.h"
#include "../A_GameObject/MirrorObject.h"
#include "../A_GameObject/WallObject.h"

#include "../C_Component/GimmickObjectController.h"
#include "../C_Component/MirrorObjectController.h"
#include "../C_Component/WallObjectController.h"

#include "../F_PuzzleGimmick/LightExecutor.h"

#include "../S_Collision/BaseCollisionList.h"

#include "../Y_Tool/MyFunctions.h"

// コンストラクタ
RouteData::RouteData(RouteOffMode offMode, bool loop) :
    mlKeyFrameBox(),
    mbLoop(loop),
    mnOffMode(offMode)
{
}

// コピーコンストラクタ
RouteData::RouteData(const RouteData &src) :
    mlKeyFrameBox(src.mlKeyFrameBox),
    mbLoop(src.mbLoop),
    mnOffMode(src.mnOffMode)
{
}

// デストラクタ
RouteData::~RouteData()
{
}

// キーフレームを登録する関数
int RouteData::Add(const RouteKeyFrame keyFrame)
{
    // 
    this->mlKeyFrameBox.push_back(keyFrame);

    // 
    return 0;
}

// フレームに合わせた値を取得する関数
bool RouteData::GetTargetFrameData(uint32_t frameCount, float &outRad, VECTOR2D &outPos) const
{
    // 
    uint32_t current;
    uint32_t currentNext;
    if (!this->GetCurrentKeyNumber(frameCount, current, currentNext))
    {
        // 
        return false;
    }

    // 
    float targetTimming = 0.0f;
    if (!this->GetTargetTimming(frameCount, current, currentNext, targetTimming))
    {
        // 
        return false;
    }

    // 
    outRad = MyFunctions::GetFloatLerp(
        this->mlKeyFrameBox[current].mfRadian,
        this->mlKeyFrameBox[currentNext].mfRadian,
        targetTimming);

    // 
    outPos = VECTOR2D::GetLerpPos(
        this->mlKeyFrameBox[current].mvPos,
        this->mlKeyFrameBox[currentNext].mvPos,
        targetTimming);

    // 
    return true;
}

// 
bool RouteData::GetLoopFlag()
{
    // 
    return this->mbLoop;
}

// OFF時の挙動を取得する関数
RouteOffMode RouteData::GetOffMode() const
{
    // 
    return this->mnOffMode;
}

// 
bool RouteData::GetReturnFlag()
{
    // 
    return this->mnOffMode == RouteOffMode::RouteOffMode_Return;
}

// 
uint32_t RouteData::GetFinalFrame() const
{
    // 
    return this->mlKeyFrameBox[this->mlKeyFrameBox.size() - 1].mnFrameCount;
}

// 
bool RouteData::GetCurrentKeyNumber(uint32_t frameCount, uint32_t &outCurrent, uint32_t &outEnd) const
{
    // 
    if (this->mlKeyFrameBox.empty())
    {
        // 
        return false;
    }

    // 
    bool result = false;

    // 
    uint32_t current = 0;

    // 
    for (uint32_t i = 0; i < this->mlKeyFrameBox.size() - 1; i++)
    {
        // 
        if (this->mlKeyFrameBox[i].mnFrameCount <= frameCount &&
            frameCount < this->mlKeyFrameBox[i + 1].mnFrameCount)
        {
            // 
            current = i;

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
        outCurrent = current;

        // 
        outEnd = current + 1;
    }

    // 
    return result;
}

// 
bool RouteData::GetTargetTimming(uint32_t frameCount, uint32_t currentIndex, uint32_t currentEndIndex, float &out) const
{
    // 
    if (this->mlKeyFrameBox.empty() ||
        this->mlKeyFrameBox.size() <= currentIndex ||
        this->mlKeyFrameBox.size() <= currentEndIndex ||
        currentEndIndex <= currentIndex )
    {
        // 
        return false;
    }

    // 
    uint32_t inCurrnetFrame = frameCount - this->mlKeyFrameBox[currentIndex].mnFrameCount;

    // 
    uint32_t currentMax = this->mlKeyFrameBox[currentEndIndex].mnFrameCount - this->mlKeyFrameBox[currentIndex].mnFrameCount;

    // 
    if (inCurrnetFrame == 0)
    {
        // 
        out = 0.0f;
    }
    else
    {
        // 
        out = static_cast<float>(inCurrnetFrame) / static_cast<float>(currentMax);
    }

    // 
    return true;
}

// コンストラクタ
RouteMoveExecutor::RouteMoveExecutor(PuzzleGimmickActiveParam param, GameObject2D *myObject, const RouteData &routeData) :
    mdMoveData(routeData),
    mnFrameCount(0),
    mpMyObject(myObject),
    BaseGimmickExecutor(param)
{
}

// デストラクタ
RouteMoveExecutor::~RouteMoveExecutor()
{
}

// ギミックの内容を初期化する関数
// ※GameObject::Initialize()のタイミングで呼ばれます
int RouteMoveExecutor::Initilize()
{
    // 
    this->mnFrameCount = 0;

    // 
    return 0;
}

// ギミックの内容を実行する関数
// ※GameObject::EarlyUpdate()のタイミングで呼ばれます
int RouteMoveExecutor::EarlyUpdate(bool triggerSignal)
{
    // 
    return 0;
}

// ギミックの内容を実行する関数
// ※GameObject::Update()のタイミングで呼ばれます
int RouteMoveExecutor::Update(bool triggerSignal)
{
    // 
    if (this->mpMyObject == nullptr)
    {
        // 
        return -1;
    }

    // 
    if (this->GetActiveParam().GetSignalNot())
    {
        triggerSignal = !triggerSignal;
    }

    // 
    if (!this->MoveRouteOnTargetFrame(triggerSignal))
    {
        // 
        return -1;
    }

    // 
    return 0;
}

// ギミックの内容を実行する関数
// ※GameObject::LateUpdate()のタイミングで呼ばれます
int RouteMoveExecutor::LateUpdate(bool triggerSignal)
{
    // 
    return 0;
}

// 当たり判定によるギミックの変化に対応させる関数
int RouteMoveExecutor::HitOnCollision(BaseCollision *myCollision, BaseCollision *hitCollision)
{
    // 
    return 0;
}

// 
void RouteMoveExecutor::SetFrameCount(uint32_t frameCount)
{
    // 
    this->mnFrameCount = frameCount;
}

// 
bool RouteMoveExecutor::MoveRouteOnTargetFrame(bool triggerSignal)
{
    // 
    bool move = true;

    // 
    bool framePlus = true;

    // 
    if (triggerSignal)
    {
        // ループしない場合は処理を行う
        if (!this->mdMoveData.GetLoopFlag())
        {
            // 最後のフレーム以降になっていたら処理を行う
            if (this->mdMoveData.GetFinalFrame() <= this->mnFrameCount)
            {
                // 
                move = false;
            }
        }
    }
    else
    {
        // 動かない前提でいきます
        move = false;

        // 
        if (this->GetActiveParam().GetOnePushActive())
        {
            // 既に動き始めている場合は処理を行う
            if (0 < this->mnFrameCount)
            {
                // 
                move = true;
            }
        }
        else
        {
            // 戻る場合かで処理を分ける
            if (this->mdMoveData.GetReturnFlag())
            {
                // 戻り切っていない場合場合は処理を行う
                if (0 < this->mnFrameCount)
                {
                    // 
                    move = true;

                    // 
                    framePlus = false;
                }
            }
        }
    }

    // 
    if (!move)
    {
        // 
        return true;
    }

    // 
    if (framePlus)
    {
        // 
        if (this->mdMoveData.GetLoopFlag())
        {
            // 
            this->mnFrameCount++;

            // 
            this->mnFrameCount %= this->mdMoveData.GetFinalFrame();
        }
        else
        {
            // 
            if (this->mnFrameCount < this->mdMoveData.GetFinalFrame())
            {
                // 
                this->mnFrameCount++;
            }
        }
    }
    else
    {
        // Returnの場合しか-方向には進まないので
        this->mnFrameCount--;
    }

    // 
    float nextRadian = 0.0f;
    VECTOR2D nextPos;
    if (!this->mdMoveData.GetTargetFrameData(this->mnFrameCount, nextRadian, nextPos))
    {
        // 
        return false;
    }

    // 
    VECTOR2D moveVec = nextPos - this->mpMyObject->GetPosition();

    // 
    if (this->mpMyObject->GetObjectTag() == GameObjectTag::GOT_Light)
    {
        // 
        LightObject *lightObject = static_cast<LightObject *>(this->mpMyObject);
        this->mpMyObject->SetMoveVec(moveVec);

        // 
        BaseCollisionList *list = this->mpMyObject->GetBaseCollisionList();
        if (list == nullptr)
        {
            // 
            return true;
        }

        list->SetCollisionMoveVec(CollisionDimension::CollisionDimension_2D, &moveVec);

        // 
        auto gimmick = lightObject->GetGimmickController();
        if (gimmick == nullptr)
        {
            return false;
        }

        // 
        auto box = gimmick->GetGimmickBox();
        auto count = gimmick->GetGimmickCount();
        for (size_t i = 0; i < count; i++)
        {
            // 
            LightExecutor *lightExecutor = dynamic_cast<LightExecutor *>(box[i].mpExecutor);
            if (lightExecutor == nullptr)
            {
                // 
                continue;
            }

            // 
            lightExecutor->SetBaseAngle(nextRadian);
        }
    }
    else if (this->mpMyObject->GetObjectTag() == GameObjectTag::GOT_Mirror)
    {
        // 
        MirrorObject *mirrorObject = static_cast<MirrorObject *>(this->mpMyObject);
        auto mirrorController = mirrorObject->GetMirrorController();
        if (mirrorController == nullptr)
        {
            // 
            return false;
        }

        // 
        mirrorController->SetMoveVecObjAndBody(moveVec);
        mirrorController->SetMoveVecMirrorFace(moveVec);
        mirrorController->SetBodyCollisionRotateAtNowPos(nextRadian);

    }
    else if (this->mpMyObject->GetObjectTag() == GameObjectTag::GOT_Wall)
    {
        // 
        WallObject *wallObject = static_cast<WallObject *>(this->mpMyObject);
        auto wallController = wallObject->GetWallController();
        if (wallController == nullptr)
        {
            // 
            return false;
        }

        // 
        wallController->SetMoveVecObjAndBody(moveVec);
        wallController->SetBodyCollisionRotateAtNowPos(nextRadian);
    }

    // 
    return true;
}