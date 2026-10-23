#include "MyEasing.h"

#include "MyFunctions.h"

// イージングの引数として渡すframeParamを取得する関数
bool MyEasing::GetFrameParam(uint32_t targetFrame, uint32_t nowFrame, float &out)
{
    // 
    if (targetFrame == 0)
    {
        // 
        return false;
    }

    // 
    out = 0.0f;

    // 整数同士の除算にならないようfloatへ変換
    float t = 0.0f;
    if (nowFrame != 0)
    {
        t = static_cast<float>(nowFrame) / static_cast<float>(targetFrame);
    }
    
    // 
    out = MyEasing::Clamp01(t);

    // 
    return true;
}

// イージングとして一般的な動き方
float MyEasing::GetDefault(EasingProcessNumber easingNumber, float frameParam)
{
    // 
    return MyEasing::ApplyProcess(easingNumber, frameParam, MyEasing::GetDefaultCore);
}

// 累乗を使用して加速や減速を極端にした動き方(Quad系の動き方)
float MyEasing::GetSquare(EasingProcessNumber easingNumber, float frameParam, int32_t squareParam)
{
    // 
    MyEasing::smnWorkSquareParam = squareParam;

    // 
    return MyEasing::ApplyProcess(easingNumber, frameParam, MyEasing::GetSquareCore);
}

// 目標まで行き過ぎてから、少し戻る動き方
float MyEasing::GetBack(EasingProcessNumber easingNumber, float frameParam)
{
    // 
    return MyEasing::ApplyProcess(easingNumber, frameParam, MyEasing::GetBackCore);
}

// ボールなどが跳ねながら進む際のY軸の動き方
float MyEasing::GetBounce(EasingProcessNumber easingNumber, float frameParam)
{
    // 
    return MyEasing::ApplyProcess(easingNumber, frameParam, MyEasing::GetBounceCore);
}

// バネのように振動して落ち着いていく動き方
float MyEasing::GetElastic(EasingProcessNumber easingNumber, float frameParam)
{
    // 
    return MyEasing::ApplyProcess(easingNumber, frameParam, MyEasing::GetElasticCore);
}

// サインカーブを使った滑らかな動き方
float MyEasing::GetSine(EasingProcessNumber easingNumber, float frameParam)
{
    // 
    return MyEasing::ApplyProcess(easingNumber, frameParam, MyEasing::GetSineCore);
}

// 円の一部を使った滑らかな動き方
float MyEasing::GetCircular(EasingProcessNumber easingNumber, float frameParam)
{
    // 
    return MyEasing::ApplyProcess(easingNumber, frameParam, MyEasing::GetCircularCore);
}

// 指数関数を使った加速・減速を急激にした動き方
float MyEasing::GetExponential(EasingProcessNumber easingNumber, float frameParam)
{
    // 
    return MyEasing::ApplyProcess(easingNumber, frameParam, MyEasing::GetExponentialCore);
}

// 
int MyEasing::smnWorkSquareParam = 1;

float MyEasing::ApplyProcess(EasingProcessNumber easingNumber, float easingParam, EasingCore core)
{
    const float t = MyEasing::Clamp01(easingParam);

    float outParam = t;

    switch (easingNumber)
    {
    case EasingProcessNumber_In:
        // Ease-In = 1 - Ease-Out(1 - t)
        outParam = 1.0f - core(1.0f - t);
        break;
    case EasingProcessNumber_Out:
        // Ease-Out
        outParam = core(t);
        break;
    case EasingProcessNumber_InOut:
        // 前半はIn、後半はOut
        if (t < 0.5f)
        {
            outParam = (1.0f - core(1.0f - 2.0f * t)) * 0.5f;
        }
        else
        {
            outParam = 0.5f + core(2.0f * t - 1.0f) * 0.5f;
        }
        break;
    case EasingProcessNumber_OutIn:
        // 前半はOut、後半はIn
        if (t < 0.5f)
        {
            outParam = core(2.0f * t) * 0.5f;
        }
        else
        {
            outParam = 0.5f + (1.0f - core(2.0f - 2.0f * t)) * 0.5f;
        }
        break;
    default:
        // 不正な値の場合はLinear
        break;
    }
    return outParam;
}

float MyEasing::Clamp01(float value)
{
    if (value < 0.0f)
    {
        return 0.0f;
    }
    if (1.0f < value)
    {
        return 1.0f;
    }
    return value;
}

float MyEasing::GetDefaultCore(float frameParam)
{
    // 標準のイージング：Ease-Out Cubic
    float u = 1.0f - frameParam;
    return 1.0f - u * u * u;
}

float MyEasing::GetSquareCore(float frameParam)
{
    // Ease-Out Power
    const int32_t power = MyEasing::smnWorkSquareParam < 1 ? 1 : MyEasing::smnWorkSquareParam;

    return 1.0f - powf(1.0f - frameParam, static_cast<float>(power));
}

float MyEasing::GetBackCore(float frameParam)
{
    // Ease-Out Back
    constexpr float s = 1.70158f;
    float u = frameParam - 1.0f;

    return 1.0f + (s + 1.0f) * u * u * u + s * u * u;
}

float MyEasing::GetBounceCore(float frameParam)
{
    // Ease-Out Bounce
    constexpr float n = 7.5625f;
    constexpr float d = 2.75f;

    if (frameParam < 1.0f / d)
    {
        return n * frameParam * frameParam;
    }
    else if (frameParam < 2.0f / d)
    {
        frameParam -= 1.5f / d;
        return n * frameParam * frameParam + 0.75f;
    }
    else if (frameParam < 2.5f / d)
    {
        frameParam -= 2.25f / d;
        return n * frameParam * frameParam + 0.9375f;
    }
    else
    {
        frameParam -= 2.625f / d;
        return n * frameParam * frameParam + 0.984375f;
    }

    // 
    return 0.0f;
}

float MyEasing::GetElasticCore(float frameParam)
{
    // Ease-Out Elastic
    if (frameParam <= 0.0f) return 0.0f;
    if (frameParam >= 1.0f) return 1.0f;

    return powf(2.0f, -10.0f * frameParam) * sinf((frameParam * 10.0f - 0.75f) * (2.0f * MyFunctions::GetPI() / 3.0f)) + 1.0f;
}

float MyEasing::GetSineCore(float frameParam)
{
    // Ease-Out Sine
    return sinf(frameParam * MyFunctions::GetPI() * 0.5f);
}

float MyEasing::GetCircularCore(float frameParam)
{
    // Ease-Out Circular
    float u = frameParam - 1.0f;

    return sqrtf(1.0f - u * u);
}

float MyEasing::GetExponentialCore(float frameParam)
{
    // Ease-Out Exponential
    if (frameParam >= 1.0f) return 1.0f;

    return 1.0f - powf(2.0f, -10.0f * frameParam);
}