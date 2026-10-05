#include "MyMath.h"

float MyMath::GetClockwiseAngleFromLeft(float angle, float baseLeft)
{
    float diff = std::fmod(angle - baseLeft, DX_TWO_PI_F);
    if (diff < 0.0f)
    {
        diff += DX_TWO_PI_F;
    }
    return diff;
}

float MyMath::GetSignedAngleFromLeft(float angle, float baseLeft)
{
    float diff = std::fmod(angle - baseLeft, DX_TWO_PI_F);

    if (diff > DX_PI_F)
    {
        diff -= DX_TWO_PI_F;
    }
    else if (diff < -DX_PI_F)
    {
        diff += DX_TWO_PI_F;
    }

    return diff;
}

float MyMath::GetAngleToPoint(const Vector2& from, const Vector2& to)
{
    const float dx = to.x - from.x;
    const float dy = to.y - from.y;

    float angle = std::atan2(dy, dx);

    if (angle < 0.0f)
    {
        angle += DX_TWO_PI;
    }

    return angle;
}

float MyMath::Cross(const Vector2& src, const Vector2& dst)
{
    return src.x * dst.y - src.y * dst.x;
}

bool MyMath::GetIntersection(const Vector2 srcA, const Vector2 srcB, const Vector2 dstC, const Vector2 dstD, Vector2& intersection)
{
    Vector2 srcAB = { srcB.x - srcA.x, srcB.y - srcA.y };
    Vector2 dstCD = { dstD.x - dstC.x, dstD.y - dstC.y };

    float denominator = Cross(srcAB, dstCD);
    if (std::fabs(denominator) < 0.000001f)
    {
        return false;
    }

    Vector2 srcAdstC = { dstC.x - srcA.x, dstC.y - srcA.y };
    float t = Cross(srcAdstC, dstCD) / denominator;
    float u = Cross(srcAdstC, srcAB) / denominator;

    if (t < 0.0f || t > 1.0f ||
        u < 0.0f || u > 1.0f)
    {
        return false;
    }

    intersection =
    {
        srcA.x + srcAB.x * t,
        srcA.y + srcAB.y * t
    };

    return true;
}

bool MyMath::GetLineIntersection(const Vector2& srcA, const Vector2& srcB, const Vector2& dstC, const Vector2& dstD, Vector2& intersection)
{
    Vector2 srcAB = { srcB.x - srcA.x, srcB.y - srcA.y };
    Vector2 dstCD = { dstD.x - dstC.x, dstD.y - dstC.y };

    float denominator = Cross(srcAB, dstCD);
    if (denominator == 0.0f)
    {
        return false;
    }

    Vector2 srcAdstC = { dstC.x - srcA.x, dstC.y - srcA.y };
    float t = Cross(srcAdstC, dstCD) / denominator;
    float u = Cross(srcAdstC, srcAB) / denominator;

    intersection =
    {
        srcA.x + srcAB.x * t,
        srcA.y + srcAB.y * t
    };

    return true;
}

bool MyMath::IsRayIntersectRect(const Vector2& rayOrigin, const Vector2& rayDirection, float left, float right, float top, float bottom)
{
    float tMin = 0.0f;
    float tMax = FLT_MAX;

    if (rayDirection.x == 0.0f)
    {
        if (rayOrigin.x < left || rayOrigin.x > right)
            return false;
    }
    else
    {
        float t1 = (left - rayOrigin.x) / rayDirection.x;
        float t2 = (right - rayOrigin.x) / rayDirection.x;

        if (t1 > t2)
            std::swap(t1, t2);

        tMin = max(tMin, t1);
        tMax = min(tMax, t2);

        if (tMin > tMax)
            return false;
    }

    if (rayDirection.y == 0.0f)
    {
        if (rayOrigin.y < top || rayOrigin.y > bottom)
            return false;
    }
    else
    {
        float t1 = (top - rayOrigin.y) / rayDirection.y;
        float t2 = (bottom - rayOrigin.y) / rayDirection.y;

        if (t1 > t2)
            std::swap(t1, t2);

        tMin = max(tMin, t1);
        tMax = min(tMax, t2);

        if (tMin > tMax)
            return false;
    }

    return tMax >= 0.0f;
}
