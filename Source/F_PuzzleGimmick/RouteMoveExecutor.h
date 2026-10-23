#pragma once

#include "PuzzleGimmickData.h"

#include <cstdint>
#include <vector>

#include "../Y_Tool/VECTOR.h"

// 自身の移動状態がOFFの際に、どのような挙動を取るのか
enum RouteOffMode
{
    // 自身の状態がOFFになった瞬間にその場で止まる
    RouteOffMode_Stop,

    // 自身の状態がOFFになった瞬間にその場から移動の逆再生を始める
    RouteOffMode_Return,
};

// キーフレームの設定
struct RouteKeyFrame
{
    // 何フレーム目のものか
    uint32_t mnFrameCount;

    // このフレームでの回転量
    float mfRadian;

    // このフレームでの座標
    VECTOR2D mvPos;
};

// 0フレーム時点の情報も記録しておいてください
// また、LoopをONにする場合は0フレーム目と同じ座標まで戻るように設定してください
// (反復を繰り返すのか、一周を繰り返すのか設定するのはKeyFrame側)
// ※RouteOffMode_StopはloopがONの時以外許されないので気を付けてください
class RouteData
{
public:
    // デフォルトコンストラクタは削除
    RouteData() = delete;

    // コンストラクタ
    RouteData(RouteOffMode offMode, bool loop);

    // コピーコンストラクタ
    RouteData(const RouteData &src);

    // デストラクタ
    ~RouteData();

    // キーフレームを登録する関数
    int Add(const RouteKeyFrame keyFrame);

    // フレームに合わせた値を取得する関数
    bool GetTargetFrameData(uint32_t frameCount, float &outRad, VECTOR2D &outPos) const;

    // ループを行うのか
    bool GetLoopFlag();

    // OFF時の挙動を取得する関数
    RouteOffMode GetOffMode() const;

    // OFFになった際に最後まで行くのか
    bool GetReturnFlag();

    // この移動ルートの最後のフレーム(LoopがOnなら時計でいうなら0:00で、0フレームと同じ扱いができそうなところ)
    uint32_t GetFinalFrame() const;

private:
    // 登録されたキーフレームを記憶する動的配列
    // キーフレームからキーフレームまではLeapで補間
    // 最初に動いた際に処理に使用するフレーム数は1です
    std::vector<RouteKeyFrame> mlKeyFrameBox;

    // OFFの状態でどのような移動を行うのかの設定
    RouteOffMode mnOffMode;

    // ON時に最後のキーフレームまで到達した場合、そのまま0フレームから再生を行うかどうか
    bool mbLoop;

    // 
    bool GetCurrentKeyNumber(uint32_t frameCount, uint32_t &outCurrent, uint32_t &outEnd) const;

    // 
    bool GetTargetTimming(uint32_t frameCount, uint32_t currentIndex, uint32_t currentEndIndex, float &out) const;
};

// 
class GameObject2D;

// 
class RouteMoveExecutor : public BaseGimmickExecutor
{
public:
    // コンストラクタ
    RouteMoveExecutor(PuzzleGimmickActiveParam param, GameObject2D *myObject, const RouteData &routeData);

    // デストラクタ
    ~RouteMoveExecutor() override;

    // ギミックの内容を初期化する関数
    // ※GameObject::Initialize()のタイミングで呼ばれます
    int Initilize() override;

    // ギミックの内容を実行する関数
    // ※GameObject::EarlyUpdate()のタイミングで呼ばれます
    int EarlyUpdate(bool triggerSignal) override;

    // ギミックの内容を実行する関数
    // ※GameObject::Update()のタイミングで呼ばれます
    int Update(bool triggerSignal) override;

    // ギミックの内容を実行する関数
    // ※GameObject::LateUpdate()のタイミングで呼ばれます
    int LateUpdate(bool triggerSignal) override;

    // 当たり判定によるギミックの変化に対応させる関数
    int HitOnCollision(BaseCollision *myCollision, BaseCollision *hitCollision) override;

    // 
    void SetFrameCount(uint32_t frameCount);

private:
    // 
    RouteData mdMoveData;

    // 
    uint32_t mnFrameCount;

    // 
    GameObject2D *mpMyObject;

    // 
    bool MoveRouteOnTargetFrame(bool triggerSignal);
};