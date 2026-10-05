#pragma once

#include <algorithm>
#include <cfloat>
#include <cmath>

#include "DxLib.h"
#include "Vector2.h"

class MyMath
{
public:
    static float GetClockwiseAngleFromLeft(float angle, float baseLeft);
    static float GetSignedAngleFromLeft(float angle, float baseLeft);
    static float GetAngleToPoint(const Vector2& from, const Vector2& to);
    static float Cross(const Vector2& src, const Vector2& dst);
    static bool GetIntersection(const Vector2 srcA, const Vector2 srcB, const Vector2 dstC, const Vector2 dstD, Vector2& intersection);
    static bool GetLineIntersection(const Vector2& srcA, const Vector2& srcB, const Vector2& dstC, const Vector2& dstD, Vector2& intersection);
    static bool IsRayIntersectRect(const Vector2& rayOrigin, const Vector2& rayDirection, float left, float right, float top, float bottom);
};
