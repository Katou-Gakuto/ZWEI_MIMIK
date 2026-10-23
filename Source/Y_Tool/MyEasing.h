#pragma once

#include <cstdint>

// イージングでどのような動き方をしてほしいかを設定する値
enum EasingProcessNumber
{
    EasingProcessNumber_In = 0,     // ゆっくり始まり、加速していくイージング
    EasingProcessNumber_Out,        // 早く始まり、減速していくイージング
    EasingProcessNumber_InOut,      // ゆっくり始まり、途中で早くなり、最終的には減速していくイージング
    EasingProcessNumber_OutIn,      // 早く始まり、途中で遅くなり、最終的には加速していくイージング
};

// イージング関数をまとめて持っているクラス
class MyEasing
{
public:
    // イージングの引数として渡すframeParamを取得する関数
    static bool GetFrameParam(uint32_t targetFrame, uint32_t nowFrame, float &out);

    // イージングとして一般的な動き方
    static float GetDefault(EasingProcessNumber easingNumber, float frameParam);

    // 累乗を使用して加速や減速を極端にした動き方(Quad系の動き方)
    static float GetSquare(EasingProcessNumber easingNumber, float frameParam, int32_t squareParam);

    // 目標まで行き過ぎてから、少し戻る動き方
    static float GetBack(EasingProcessNumber easingNumber, float frameParam);

    // ボールなどが跳ねながら進む際のY軸の動き方
    static float GetBounce(EasingProcessNumber easingNumber, float frameParam);

    // バネのように振動して落ち着いていく動き方
    static float GetElastic(EasingProcessNumber easingNumber, float frameParam);

    // サインカーブを使った滑らかな動き方
    static float GetSine(EasingProcessNumber easingNumber, float frameParam);

    // 円の一部を使った滑らかな動き方
    static float GetCircular(EasingProcessNumber easingNumber, float frameParam);

    // 指数関数を使った加速・減速を急激にした動き方
    static float GetExponential(EasingProcessNumber easingNumber, float frameParam);

private:
    // Get○○()で使用する01曲線部分を取得する関数
    // 出力の値はEasing-Outでの値
    using EasingCore = float (*)(float);

    // GetSquare()で使用する作業用の値
    static int smnWorkSquareParam;

    // 各イージングのIn/Out/InOut/OutInを共通化
    static float ApplyProcess(EasingProcessNumber easingNumber, float frameParam, EasingCore core);

    // 共通処理用の補助関数
    static float Clamp01(float value);

    // 各曲線のCore（Ease-Out側の基本曲線）
    static float GetDefaultCore(float frameParam);
    static float GetSquareCore(float frameParam);
    static float GetBackCore(float frameParam);
    static float GetBounceCore(float frameParam);
    static float GetElasticCore(float frameParam);
    static float GetSineCore(float frameParam);
    static float GetCircularCore(float frameParam);
    static float GetExponentialCore(float frameParam);
};