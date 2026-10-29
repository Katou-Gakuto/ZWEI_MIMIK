#include "BaseCollision2DManager.h"

#include "../A_GameObject/GameObject2D.h"

#include "BaseCollisionList.h"
#include "Point2D.h"
#include "Circle2D.h"
#include "Capsule2D.h"
#include "Triangle2D.h"
#include "Quadrangle2D.h"
#include "Ray2D.h"

#include "../Y_Tool/MyFunctions.h"

// BaseCollision3DManagerの変数定義
AABB2D BaseCollision2DManager::aabbA;
AABB2D BaseCollision2DManager::aabbB;

// 凸四角形内に点 P があるか判定する
bool PointInConvexQuad(const VECTOR2D &p, const Quadrangle2D *q)
{
    bool hasPositive = false;
    bool hasNegative = false;

    // 
    int vertexIndexBox[4][2] =
    {
        {0, 1},
        {1, 3},
        {3, 2},
        {2, 1},
    };

    for (int i = 0; i < 4; ++i)
    {
        const VECTOR2D &a = q->GetVertexPos(vertexIndexBox[i][0]);
        const VECTOR2D &b = q->GetVertexPos(vertexIndexBox[i][1]);

        VECTOR2D ab = b - a;
        VECTOR2D ap = p - a;

        double cross = ab.GetX() * ap.GetY() - ab.GetY() * ap.GetX();

        if (cross > FLT_EPSILON)
        {
            hasPositive = true;
        }
        if (cross < -FLT_EPSILON)
        {
            hasNegative = true;
        }

        if (hasPositive && hasNegative)
        {
            return false;
        }
    }

    return true;
}

// 頂点の順序に依存せず、最も近い辺上の点を取得する
VECTOR2D ClosestPointOnQuad(
    const VECTOR2D &p,
    const Quadrangle2D *q)
{
    VECTOR2D closest{};
    double minDistSq = INFINITY;

    // 
    int vertexIndexBox[4][2] =
    {
        {0, 1},
        {1, 3},
        {3, 2},
        {2, 1},
    };

    for (int i = 0; i < 4; ++i)
    {
        const VECTOR2D &a = q->GetVertexPos(vertexIndexBox[i][0]);
        const VECTOR2D &b = q->GetVertexPos(vertexIndexBox[i][1]);

        VECTOR2D candidate = VECTOR2D::GetNearestPosOnLineSegment(p, a, b);
        double distSq = (p - candidate).Magnitude();

        if (distSq < minDistSq)
        {
            minDistSq = distSq;
            closest = candidate;
        }
    }

    return closest;
}

// 凸四角形の外向き法線を取得する
// 頂点は時計回り・反時計回りのどちらでもよい
VECTOR2D GetQuadNormal(const Quadrangle2D *q, int edgeIndex)
{
    double area2 = 0.0;

    // 
    int vertexIndexBox[4][2] =
    {
        {0, 1},
        {1, 3},
        {3, 2},
        {2, 1},
    };

    for (int i = 0; i < 4; ++i)
    {
        const VECTOR2D &a = q->GetVertexPos(vertexIndexBox[i][0]);
        const VECTOR2D &b = q->GetVertexPos(vertexIndexBox[i][1]);

        area2 += a.GetX() * b.GetY() - a.GetY() * b.GetX();
    }

    VECTOR2D edge = q->GetVertexPos(vertexIndexBox[edgeIndex][1]) - q->GetVertexPos(vertexIndexBox[edgeIndex][0]);

    // 反時計回りなら右側、時計回りなら左側が外側
    return { -edge.GetY(), edge.GetX() };
}

// この二つの当たり判定が互いの処理対象なのかを確認する関数
bool BaseCollision2DManager::CheckProcessing(BaseCollision2D *collision2DA, BaseCollision2D *collision2DB)
{
    // 互いに処理をする当たり判定かを調べ、計算対象ならtrueを返す
    if (collision2DA->GetCollisionTag() == CollisionTag::CollisionTag_Checker ||
        collision2DB->GetCollisionTag() == CollisionTag::CollisionTag_Checker)
    {
        return true;
    }
    if (collision2DA->CheckProcessingFlag(collision2DB->GetCollisionTag()) &&
        collision2DB->CheckProcessingFlag(collision2DA->GetCollisionTag()))
    {
        return true;
    }
    return false;
}

// 当たり判定と指定の当たり判定の移動のカリング処理を行う関数
bool BaseCollision2DManager::CheckHitMoveVecToCollision2D(BaseCollision2D *collision2DA, BaseCollision2D *collision2DB)
{
    // どれか一つでも無効な値が入っていた場合はfalseを返す
    if (collision2DA == nullptr ||
        collision2DB == nullptr)
    {
        return false;
    }

    // 当たり判定の片方だけでも貫通を許すのなら、移動の進行ベクトルによるカリングをスキップする
    if (collision2DA->GetPenetrate() == true ||
        collision2DB->GetPenetrate() == true)
    {
        return true;
    }

    VECTOR2D moveVecA = collision2DA->GetMoveVec();
    VECTOR2D moveVecB = collision2DB->GetMoveVec();

    // 当たり判定Aの移動ベクトル(以下Aベクトルと呼ぶ)
    bool aMoveFlag = moveVecA != VECTOR2D::GetZero();

    // 当たり判定Bの移動ベクトル(以下Bベクトルと呼ぶ)
    bool bMoveFlag = moveVecB != VECTOR2D::GetZero();

    // どちらか片方でも移動している場合は処理を行う
    if (aMoveFlag || bMoveFlag)
    {
        return true;
    }

    // ※どちらも移動していない場合は以降の衝突・内外判定の処理を行わない

    // 二つの当たり判定のことはないのでfalseを返す
    return false;
}

// 当たり判定と指定の当たり判定の円を使ったカリング処理を行う関数
bool BaseCollision2DManager::CheckHitBaseCollision2DToBaseCollision2D(BaseCollision2D *collision2DA, BaseCollision2D *collision2DB)
{
    // 二つの当たり判定の基準円を取得する
    collision2DA->SetBaseParamMySelf();
    collision2DB->SetBaseParamMySelf();

    // 1の中心点→2の中心点の進行ベクトルを取得
    VECTOR2D distanceVec = 
        collision2DB->GetMovedPos(collision2DB->GetBasePos()) -
        collision2DA->GetMovedPos(collision2DA->GetBasePos());

    // 二つの円の半径を取得
    float baseRadius = collision2DA->GetBaseRadius() + collision2DB->GetBaseRadius();

    // 進行ベクトルと二つの円の半径を比較し、進行ベクトルの方が小さかったらfalseを返す
    if (distanceVec.MagnitudeNoSqrt() <= baseRadius * baseRadius)
    {
        return true;
    }

    // falseを返す
    return false;
}

// AABBを使ったカリング処理を行う関数
bool BaseCollision2DManager::CheckHitAABBAABB(BaseCollision2D *collision2DA, BaseCollision2D *collision2DB)
{
    if (collision2DA->GetAABB(aabbA) != 0 || collision2DB->GetAABB(aabbB) != 0)
    {
        return false;
    }
    VECTOR2D aabb1min = aabbA.mvMinPos + aabbA.mvMoveVec;
    VECTOR2D aabb1max = aabbA.mvMaxPos + aabbA.mvMoveVec;
    VECTOR2D aabb2min = aabbB.mvMinPos + aabbB.mvMoveVec;
    VECTOR2D aabb2max = aabbB.mvMaxPos + aabbB.mvMoveVec;
    if (aabb1max.GetX() < aabb2min.GetX() || aabb2max.GetX() < aabb1min.GetX())
    {
        return false;
    }
    if (aabb1max.GetY() < aabb2min.GetY() || aabb2max.GetY() < aabb1min.GetY())
    {
        return false;
    }
    return true;
}

// カリング処理をまとめて行い、当たり判定の計算を飛ばすべきかを確認する関数
bool BaseCollision2DManager::CheckCulling(BaseCollision2D *collision2DA, BaseCollision2D *collision2DB)
{
    // 二つの当たり判定が互いの処理対象かを確認する
    if (BaseCollision2DManager::CheckProcessing(collision2DA, collision2DB) == false)
    {
        return true;
    }
    // 移動ベクトルを使ったカリング処理を行う
    if (BaseCollision2DManager::CheckHitMoveVecToCollision2D(collision2DA, collision2DB) == false)
    {
        return true;
    }
    // AABBを使ったカリング処理を行う
    if (BaseCollision2DManager::CheckHitAABBAABB(collision2DA, collision2DB) == false)
    {
        return true;
    }
    // 円を使ったカリング処理を行う
    if (BaseCollision2DManager::CheckHitBaseCollision2DToBaseCollision2D(collision2DA, collision2DB) == false)
    {
        return true;
    }

    // 飛ばすべきでないことを返す
    return false;
}

// 二つの当たり判定のスライド移動を行う関数
int BaseCollision2DManager::CollisionSlide(const CollisionCheckResult2D &hitResult, BaseCollision2D *collision2DA, BaseCollision2D *collision2DB)
{
    // どちらも貫通を許さない場合はスライド移動の処理を行う
    if (collision2DA->GetPenetrate() == false && collision2DB->GetPenetrate() == false)
    {
        float aMoveLate = 0.0f;
        float bMoveLate = 0.0f;

        // 
        if (BaseCollision2DManager::GetCollisionMoveLate(collision2DA, collision2DB, aMoveLate, bMoveLate))
        {
            // collision2DAのスライド移動を行う
            if (!MyFunctions::EqualInRangeF(aMoveLate, 0, 0.00001f))
            {
                // あとは当たり判定側に任せる
                collision2DA->SlideMove(hitResult, aMoveLate);
            }

            // collision2DBのスライド移動を行う
            if (!MyFunctions::EqualInRangeF(bMoveLate, 0, 0.00001f))
            {
                // あとは当たり判定側に任せる
                collision2DB->SlideMove(hitResult, bMoveLate);
            }
        }
    }

    // 関数が正常終了したことを返す
    return 0;
}

// 二つの当たり判定のスライド移動を行う関数
bool BaseCollision2DManager::GetCollisionMoveLate(
    BaseCollision2D *collision2DA,
    BaseCollision2D *collision2DB,
    float &aMoveLate,
    float &bMoveLate)
{
    aMoveLate = 0.0f;
    bMoveLate = 0.0f;

    // 
    if (collision2DA->mbHitMoveLose &&
        !collision2DB->mbHitMoveLose)
    {
        // 
        aMoveLate = 2.0f;
        bMoveLate = 0.0f;

        // 
        return true;
    }

    // 
    if (!collision2DA->mbHitMoveLose &&
        collision2DB->mbHitMoveLose)
    {
        // 
        aMoveLate = 0.0f;
        bMoveLate = 2.0f;

        // 
        return true;
    }

    // 
    if (collision2DA->mbHitMoveLose &&
        collision2DB->mbHitMoveLose)
    {
        // 
        if (collision2DA->GetMoveVec() == VECTOR2D::GetZero() && collision2DB->GetMoveVec() != VECTOR2D::GetZero())
        {
            // 
            aMoveLate = 0.0f;
            bMoveLate = 2.0f;

            // 
            return true;
        }
        else if (collision2DA->GetMoveVec() != VECTOR2D::GetZero() && collision2DB->GetMoveVec() == VECTOR2D::GetZero())
        {
            // 
            aMoveLate = 2.0f;
            bMoveLate = 0.0f;

            // 
            return true;
        }
    }

    // 
    if (!collision2DA->GetHitMove() &&
        !collision2DB->GetHitMove())
    {
        // 
        bool aMoveFlag = collision2DA->GetMoveVec() != VECTOR2D::GetZero();
        bool bMoveFlag = collision2DB->GetMoveVec() != VECTOR2D::GetZero();

        // 
        if (aMoveFlag && bMoveFlag)
        {
            aMoveLate = 1.0f;
            bMoveLate = 1.0f;
        }
        else if (!aMoveFlag && bMoveFlag)
        {
            aMoveLate = 0.0f;
            bMoveLate = 2.0f;
        }
        else if (aMoveFlag && !bMoveFlag)
        {
            aMoveLate = 2.0f;
            bMoveLate = 0.0f;
        }
        return true;
    }
    
    // collision2DAのスライド移動を行う
    if (collision2DA->GetHitMove())
    {
        // collision2DAの移動の係数を設定する
        if (collision2DB->GetHitMove() == false)
        {
            aMoveLate = 2.0f;
        }
        else
        {
            aMoveLate = MyFunctions::GetRatio(
                collision2DA->GetMoveLate() + collision2DB->GetMoveLate(),
                collision2DA->GetMoveLate(),
                2.0f);
        }
    }

    // collision2DBのスライド移動を行う
    if (collision2DB->GetHitMove())
    {
        // collision2DBの移動の係数を設定する
        if (collision2DA->GetHitMove() == false)
        {
            bMoveLate = 2.0f;
        }
        else
        {
            bMoveLate = MyFunctions::GetRatio(
                collision2DB->GetMoveLate() + collision2DA->GetMoveLate(),
                collision2DB->GetMoveLate(),
                2.0f);
        }
    }

    // 
    return true;
}

// 点と謎の当たり判定の内外判定と衝突判定を行う関数
CollisionCheckResult2D BaseCollision2DManager::CheckHitPoint2DToCollision2D(Point2D *point2D, BaseCollision2D *collision)
{
    // 返り値を保持する変数
    CollisionCheckResult2D temp = GetCollisionCheckResult2DZero();

    // 点じゃない方の当たり判定のタイプに合わせた関数に飛ぶ
    switch (collision->GetCollisionType())
    {
    case CollisionType::CollisionType_Point2D:
        temp = BaseCollision2DManager::CheckHitPoint2DToCollision2D(point2D, static_cast<Point2D *>(collision));
        break;
    case CollisionType::CollisionType_Circle2D:
        temp = BaseCollision2DManager::CheckHitPoint2DToCircle2D(point2D, static_cast<Circle2D *>(collision));
        break;
    case CollisionType::CollisionType_Capsule2D:
        temp = BaseCollision2DManager::CheckHitPoint2DToCapsule2D(point2D, static_cast<Capsule2D *>(collision));
        break;
    case CollisionType::CollisionType_Triangle2D:
        temp = BaseCollision2DManager::CheckHitPoint2DToTriangle2D(point2D, static_cast<Triangle2D *>(collision));
        break;
    case CollisionType::CollisionType_Quadrangle2D:
        temp = BaseCollision2DManager::CheckHitPoint2DToQuadrangle2D(point2D, static_cast<Quadrangle2D *>(collision));
        break;
    default:

        break;
    }
    return temp;
}

// 円と謎の当たり判定の内外判定と衝突判定を行う関数
CollisionCheckResult2D BaseCollision2DManager::CheckHitCircle2DToCollision2D(Circle2D *circle2D, BaseCollision2D *collision)
{
    CollisionCheckResult2D temp = GetCollisionCheckResult2DZero();
    
    // 円じゃない方の当たり判定のタイプに合わせた関数に飛ぶ
    switch (collision->GetCollisionType())
    {
    case CollisionType::CollisionType_Point2D:
        temp = BaseCollision2DManager::CheckHitPoint2DToCircle2D(static_cast<Point2D *>(collision), circle2D);
        break;
    case CollisionType::CollisionType_Circle2D:
        temp = BaseCollision2DManager::CheckHitCircle2DToCircle2D(circle2D, static_cast<Circle2D *>(collision));
        break;
    case CollisionType::CollisionType_Capsule2D:
        temp = BaseCollision2DManager::CheckHitCircle2DToCapsule2D(circle2D, static_cast<Capsule2D *>(collision));
        break;
    case CollisionType::CollisionType_Triangle2D:
        temp = BaseCollision2DManager::CheckHitCircle2DToTriangle2D(circle2D, static_cast<Triangle2D *>(collision));
        break;
    case CollisionType::CollisionType_Quadrangle2D:
        temp = BaseCollision2DManager::CheckHitCircle2DToQuadrangle2D(circle2D, static_cast<Quadrangle2D *>(collision));
        break;
    case CollisionType::CollisionType_Ray2D:
        temp = BaseCollision2DManager::CheckHitCircle2DToRay2D(circle2D, static_cast<Ray2D *>(collision));
        break;
    default:

        break;
    }
    return temp;
}

// カプセルと謎の当たり判定の内外判定と衝突判定を行う関数
CollisionCheckResult2D BaseCollision2DManager::CheckHitCapsule2DToCollision2D(Capsule2D *capsule2D, BaseCollision2D *collision)
{
    CollisionCheckResult2D temp = GetCollisionCheckResult2DZero();
    
    // カプセルじゃない方の当たり判定のタイプに合わせた関数に飛ぶ
    switch (collision->GetCollisionType())
    {
    case CollisionType::CollisionType_Point2D:
        temp = BaseCollision2DManager::CheckHitPoint2DToCapsule2D(static_cast<Point2D *>(collision), capsule2D);
        break;
    case CollisionType::CollisionType_Circle2D:
        temp = BaseCollision2DManager::CheckHitCircle2DToCapsule2D(static_cast<Circle2D *>(collision), capsule2D);
        break;
    case CollisionType::CollisionType_Capsule2D:
        temp = BaseCollision2DManager::CheckHitCapsule2DToCapsule2D(capsule2D, static_cast<Capsule2D *>(collision));
        break;
    case CollisionType::CollisionType_Triangle2D:
        temp = BaseCollision2DManager::CheckHitCapsule2DToTriangle2D(capsule2D, static_cast<Triangle2D *>(collision));
        break;
    case CollisionType::CollisionType_Quadrangle2D:
        temp = BaseCollision2DManager::CheckHitCapsule2DToQuadrangle2D(capsule2D, static_cast<Quadrangle2D *>(collision));
        break;
    default:

        break;
    }
    return temp;
}

// 三角形と謎の当たり判定の内外判定と衝突判定を行う関数
CollisionCheckResult2D BaseCollision2DManager::CheckHitTriangle2DToCollision2D(Triangle2D *triangle2D, BaseCollision2D *collision)
{
    CollisionCheckResult2D temp = GetCollisionCheckResult2DZero();
    
    // 三角形じゃない方の当たり判定のタイプに合わせた関数に飛ぶ
    switch (collision->GetCollisionType())
    {
    case CollisionType::CollisionType_Point2D:
        temp = BaseCollision2DManager::CheckHitPoint2DToTriangle2D(static_cast<Point2D *>(collision), triangle2D);
        break;
    case CollisionType::CollisionType_Circle2D:
        temp = BaseCollision2DManager::CheckHitCircle2DToTriangle2D(static_cast<Circle2D *>(collision), triangle2D);
        break;
    case CollisionType::CollisionType_Capsule2D:
        temp = BaseCollision2DManager::CheckHitCapsule2DToTriangle2D(static_cast<Capsule2D *>(collision), triangle2D);
        break;
    case CollisionType::CollisionType_Triangle2D:
        temp = BaseCollision2DManager::CheckHitTriangle2DToTriangle2D(triangle2D, static_cast<Triangle2D *>(collision));
        break;
    case CollisionType::CollisionType_Quadrangle2D:
        temp = BaseCollision2DManager::CheckHitTriangle2DToQuadrangle2D(triangle2D, static_cast<Quadrangle2D *>(collision));
        break;
    default:

        break;
    }
    return temp;
}

// 四角形と謎の当たり判定の内外判定と衝突判定を行う関数
CollisionCheckResult2D BaseCollision2DManager::CheckHitQuadrangle2DToCollision2D(Quadrangle2D *quadrangle2D, BaseCollision2D *collision)
{
    CollisionCheckResult2D temp = GetCollisionCheckResult2DZero();
    
    // 四角形じゃない方の当たり判定のタイプに合わせた関数に飛ぶ
    switch (collision->GetCollisionType())
    {
    case CollisionType::CollisionType_Point2D:
        temp = BaseCollision2DManager::CheckHitPoint2DToQuadrangle2D(static_cast<Point2D *>(collision), quadrangle2D);
        break;
    case CollisionType::CollisionType_Circle2D:
        temp = BaseCollision2DManager::CheckHitCircle2DToQuadrangle2D(static_cast<Circle2D *>(collision), quadrangle2D);
        break;
    case CollisionType::CollisionType_Capsule2D:
        temp = BaseCollision2DManager::CheckHitCapsule2DToQuadrangle2D(static_cast<Capsule2D *>(collision), quadrangle2D);
        break;
    case CollisionType::CollisionType_Triangle2D:
        temp = BaseCollision2DManager::CheckHitTriangle2DToQuadrangle2D(static_cast<Triangle2D *>(collision), quadrangle2D);
        break;
    case CollisionType::CollisionType_Quadrangle2D:
        temp = BaseCollision2DManager::CheckHitQuadrangle2DToQuadrangle2D(quadrangle2D, static_cast<Quadrangle2D *>(collision));
        break;
    case CollisionType::CollisionType_Ray2D:
        temp = BaseCollision2DManager::CheckHitQuadrangle2DToRay2D(quadrangle2D, static_cast<Ray2D *>(collision));
        break;
    default:
        break;
    }
    return temp;
}

// レイと謎の当たり判定の衝突確認を行う関数
CollisionCheckResult2D BaseCollision2DManager::CheckHitRay2DToCollision2D(Ray2D *ray2D, BaseCollision2D *collision)
{
    // 返り値
    CollisionCheckResult2D temp = GetCollisionCheckResult2DZero();

    switch (collision->GetCollisionType())
    {
    case CollisionType::CollisionType_Point2D:
        temp = BaseCollision2DManager::CheckHitPoint2DToRay2D(static_cast<Point2D *>(collision), ray2D);
        break;
    case CollisionType::CollisionType_Circle2D:
        temp = BaseCollision2DManager::CheckHitCircle2DToRay2D(static_cast<Circle2D *>(collision), ray2D);
        break;
    case CollisionType::CollisionType_Capsule2D:
        temp = BaseCollision2DManager::CheckHitCapsule2DToRay2D(static_cast<Capsule2D *>(collision), ray2D);
        break;
    case CollisionType::CollisionType_Triangle2D:
        temp = BaseCollision2DManager::CheckHitTriangle2DToRay2D(static_cast<Triangle2D *>(collision), ray2D);
        break;
    case CollisionType::CollisionType_Quadrangle2D:
        temp = BaseCollision2DManager::CheckHitQuadrangle2DToRay2D(static_cast<Quadrangle2D *>(collision), ray2D);
        break;
    case CollisionType::CollisionType_Ray2D:
        temp = BaseCollision2DManager::CheckHitRay2DToRay2D(ray2D, static_cast<Ray2D *>(collision));
        break;

    default:
        break;
    }

    return temp;

    // 衝突地点の計算はこのサイトを参考にしました
    // http://marupeke296.com/COL_2D_No11_CircleVsRay.html
}

// 点と点の内外判定と衝突判定を行う関数
CollisionCheckResult2D BaseCollision2DManager::CheckHitPoint2DToPoint2D(Point2D *point2Da, Point2D *point2Db)
{
    // 
    if (point2Da->GetMovedPos(point2Da->GetBasePos()) == point2Db->GetMovedPos(point2Db->GetBasePos()))
    {
        return GetCollisionCheckResult2D(
            point2Da,
            point2Db,
            0,
            point2Da->GetBasePos() - point2Db->GetBasePos(),
            point2Db->GetBasePos() - point2Da->GetBasePos(),
            VECTOR2D::GetZero(),
            VECTOR2D::GetZero());
    }

    // 
    return GetCollisionCheckResult2DZero();
}

// 点と円の内外判定と衝突判定を行う関数
CollisionCheckResult2D BaseCollision2DManager::CheckHitPoint2DToCircle2D(Point2D *point2D, Circle2D *circle2D)
{
    VECTOR2D point2circle = circle2D->GetMovedPos(circle2D->GetBasePos()) - point2D->GetMovedPos(point2D->GetBasePos());

    // 
    if (circle2D->GetBaseRadius() * circle2D->GetBaseRadius() < point2circle.MagnitudeNoSqrt())
    {
        // 
        return GetCollisionCheckResult2DZero();
    }

    // 
    return GetCollisionCheckResult2D(
        point2D,
        circle2D,
        0,
        point2D->GetBasePos() - circle2D->GetBasePos(),
        circle2D->GetBasePos() - point2D->GetBasePos(),
        point2D->GetBasePos(),
        VECTOR2D::GetZero());
}

// 点とカプセルの内外判定と衝突判定を行う関数
CollisionCheckResult2D BaseCollision2DManager::CheckHitPoint2DToCapsule2D(Point2D *point2D, Capsule2D *capsule2D)
{
    // 返り値
    CollisionCheckResult2D temp = GetCollisionCheckResult2DZero();

    // 球体とカプセルの線上最近点を求める(世界座標 無限延長線編)
    VECTOR2D newrPos = VECTOR2D::GetNewrPosOnLine(
        point2D->GetMovedPos(point2D->GetBasePos()),
        capsule2D->GetMovedPos(capsule2D->GetStartPos()),
        capsule2D->GetMovedPos(capsule2D->GetEndPos()));

    // ベクトル二つを改めて作る
    VECTOR2D startToNewr = newrPos - capsule2D->GetMovedPos(capsule2D->GetStartPos());
    VECTOR2D startToEnd = capsule2D->GetMovedPos(capsule2D->GetEndPos()) - capsule2D->GetMovedPos(capsule2D->GetStartPos());

    // 線上最近点を中心としたカプセルのスフィアを作る
    Circle2D capsuleCircle2D;

    // 線上最近点が、どっちのセンターベクトルを軸とした+方向にあるか、-方向にあるかが確定していないため、それを判断するswitch文
    switch (VECTOR2D::CheckAxisVecPlusOrMinus(startToNewr, startToEnd))
    {
    case 1:
        // startNewrがプラス方向にあるため、線上最近点が確定していない
        if (startToNewr.MagnitudeNoSqrt() <= startToEnd.MagnitudeNoSqrt())
        {
            // カプセルのセンターベクトル内に線上最近点があったということで、作業用のスフィアの値を設定する
            capsuleCircle2D.SetShapeParameter(newrPos, capsule2D->GetBaseRadius());
            temp = BaseCollision2DManager::CheckHitPoint2DToCircle2D(point2D, &capsuleCircle2D);
            if (0 <= temp.mnResultParam)
            {
                temp = GetCollisionCheckResult2D(
                    point2D,
                    capsule2D,
                    0,
                    point2D->GetBasePos() - capsule2D->GetBasePos(),
                    capsule2D->GetBasePos() - point2D->GetBasePos(),
                    point2D->GetBasePos(),
                    newrPos);
            }
        }
        else
        {
            // カプセルのセンターベクトル内に線上最近点はなかったということで、+方向の端点とスフィアで当たり判定を計算する
            capsuleCircle2D.SetShapeParameter(capsule2D->GetMovedPos(capsule2D->GetEndPos()), capsule2D->GetBaseRadius());
            temp = BaseCollision2DManager::CheckHitPoint2DToCircle2D(point2D, &capsuleCircle2D);
            if (0 <= temp.mnResultParam)
            {
                temp = GetCollisionCheckResult2D(
                    point2D,
                    capsule2D,
                    0,
                    point2D->GetBasePos() - capsule2D->GetBasePos(),
                    capsule2D->GetBasePos() - point2D->GetBasePos(),
                    point2D->GetBasePos(),
                    newrPos);
            }
        }

        break;
    case -1:
        // 線上最近点がマイナス方向にあるため、-方向の端点とスフィアで当たり判定を計算する
        capsuleCircle2D.SetShapeParameter(capsule2D->GetMovedPos(capsule2D->GetBasePos()), capsule2D->GetBaseRadius());
        temp = BaseCollision2DManager::CheckHitPoint2DToCircle2D(point2D, &capsuleCircle2D);
        if (0 <= temp.mnResultParam)
        {
            temp = GetCollisionCheckResult2D(
                point2D,
                capsule2D,
                0,
                point2D->GetBasePos() -  capsule2D->GetBasePos(),
                capsule2D->GetBasePos() - point2D->GetBasePos(),
                point2D->GetBasePos(),
                newrPos);
        }
        break;
    case 0:
        // anewrがプラス方向にもマイナス方向にもないため、何もできない。

        break;
    default:
        // 謎エラー。

        break;
    }

    // 計算結果を返す
    return temp;
}

// 点と三角形の内外判定と衝突判定を行う関数
CollisionCheckResult2D BaseCollision2DManager::CheckHitPoint2DToTriangle2D(Point2D *point2D, Triangle2D *triangle2D)
{
    // 返り値
    CollisionCheckResult2D temp = GetCollisionCheckResult2DZero();

    // 計算に使うベクトルを取得する
    VECTOR2D pos0_pos1Vec = (triangle2D->GetMovedPos(triangle2D->GetVertexPos(1)) - triangle2D->GetMovedPos(triangle2D->GetVertexPos(0)));
    VECTOR2D posP_pos1Vec = (point2D->GetMovedPos(point2D->GetBasePos()) - triangle2D->GetMovedPos(triangle2D->GetVertexPos(1)));
    VECTOR2D pos1_pos2Vec = (triangle2D->GetMovedPos(triangle2D->GetVertexPos(2)) - triangle2D->GetMovedPos(triangle2D->GetVertexPos(1)));
    VECTOR2D posP_pos2Vec = (point2D->GetMovedPos(point2D->GetBasePos()) - triangle2D->GetMovedPos(triangle2D->GetVertexPos(2)));
    VECTOR2D pos2_pos0Vec = (triangle2D->GetMovedPos(triangle2D->GetVertexPos(0)) - triangle2D->GetMovedPos(triangle2D->GetVertexPos(2)));
    VECTOR2D posP_pos0Vec = (point2D->GetMovedPos(point2D->GetBasePos()) - triangle2D->GetMovedPos(triangle2D->GetVertexPos(0)));

    // 三角形の頂点からマウスの座標へのベクトルと、三角形の辺ベクトルの外積を求め、架空のz成分を取得する
    float cross1 = VECTOR2D::Cross(pos0_pos1Vec, posP_pos1Vec);
    float cross2 = VECTOR2D::Cross(pos1_pos2Vec, posP_pos2Vec);
    float cross0 = VECTOR2D::Cross(pos2_pos0Vec, posP_pos0Vec);

    // 外積の符号を確認（境界上の点も許容）
    constexpr float EPS = 1e-5f;

    const bool allPositive =
        -EPS <= cross1 &&
        -EPS <= cross2 &&
        -EPS <= cross0;

    const bool allNegative =
        cross1 <= EPS &&
        cross2 <= EPS &&
        cross0 <= EPS;

    // 
    if (triangle2D->CheckCollisionNormIn())
    {
        // 外積で求めた架空のz成分の向きが揃っているかを調べる
        if (!allPositive && !allNegative)
        {
            // 点が三角形の外にあるということなのでtrueを返す
            temp = GetCollisionCheckResult2D(
                point2D,
                triangle2D,
                0,
                point2D->GetBasePos() - triangle2D->GetBasePos(),
                triangle2D->GetBasePos() - point2D->GetBasePos(),
                point2D->GetBasePos(),
                VECTOR2D::GetZero());
        }
    }
    else
    {
        // 外積で求めた架空のz成分の向きが揃っているかを調べる
        if (allPositive || allNegative)
        {
            // 点が三角形の中に入っているということなのでtrueを返す
            temp = GetCollisionCheckResult2D(
                point2D,
                triangle2D,
                0,
                triangle2D->GetBasePos() - point2D->GetBasePos(),
                point2D->GetBasePos() - triangle2D->GetBasePos(),
                point2D->GetBasePos(),
                VECTOR2D::GetZero());
        }
    }

    // 計算結果を返す
    return temp;
}

// 点と四角形の内外判定と衝突判定を行う関数
CollisionCheckResult2D BaseCollision2DManager::CheckHitPoint2DToQuadrangle2D(Point2D *point2D, Quadrangle2D *quadrangle2D)
{
    // 返り値
    CollisionCheckResult2D temp = GetCollisionCheckResult2DZero();

    // 
    Triangle2D tempTriangle2D(
        quadrangle2D->GetMovedPos(quadrangle2D->GetVertexPos(0)),
        quadrangle2D->GetMovedPos(quadrangle2D->GetVertexPos(1)),
        quadrangle2D->GetMovedPos(quadrangle2D->GetVertexPos(2)),
        nullptr,
        CollisionTag::CollisionTag_Checker,
        quadrangle2D->GetCollisionNorm(),
        true, 
        false,
        0.0f);

    // 
    temp = BaseCollision2DManager::CheckHitPoint2DToTriangle2D(point2D, &tempTriangle2D);

    // 
    if (quadrangle2D->CheckCollisionNormIn())
    {
        // 
        if (temp.mnResultParam < 0)
        {
            // 
            return GetCollisionCheckResult2DZero();
        }

        // 
        tempTriangle2D.SetShapeParameter(
            quadrangle2D->GetMovedPos(quadrangle2D->GetVertexPos(3)),
            quadrangle2D->GetMovedPos(quadrangle2D->GetVertexPos(2)),
            quadrangle2D->GetMovedPos(quadrangle2D->GetVertexPos(1)));

        // 
        if (temp.mnResultParam < 0)
        {
            // 
            return GetCollisionCheckResult2DZero();
        }

        // 
        temp = GetCollisionCheckResult2D(
            point2D,
            quadrangle2D,
            1,
            point2D->GetBasePos() - quadrangle2D->GetBasePos(),
            quadrangle2D->GetBasePos() - point2D->GetBasePos(),
            point2D->GetBasePos(),
            VECTOR2D::GetZero());
    }
    else
    {
        // 
        bool firstHit = 0 <= temp.mnResultParam;

        // 当たっていない場合はさらに処理を行う
        if (!firstHit)
        {
            // 
            tempTriangle2D.SetShapeParameter(
                quadrangle2D->GetMovedPos(quadrangle2D->GetVertexPos(3)),
                quadrangle2D->GetMovedPos(quadrangle2D->GetVertexPos(2)),
                quadrangle2D->GetMovedPos(quadrangle2D->GetVertexPos(1)));

            // 
            temp = BaseCollision2DManager::CheckHitPoint2DToTriangle2D(point2D, &tempTriangle2D);
        }

        // 
        if (0 <= temp.mnResultParam)
        {
            // 
            int resultParam = firstHit ? 1 : 2;

            // 
            temp = GetCollisionCheckResult2D(
                point2D,
                quadrangle2D,
                resultParam,
                point2D->GetBasePos() - quadrangle2D->GetBasePos(),
                quadrangle2D->GetBasePos() - point2D->GetBasePos(),
                point2D->GetBasePos(),
                VECTOR2D::GetZero());
        }
    }

    // 
    return temp;
}

// 点とレイの内外判定と衝突判定を行う関数
CollisionCheckResult2D BaseCollision2DManager::CheckHitPoint2DToRay2D(Point2D *point2D, Ray2D *ray2D)
{
    // 返り値
    CollisionCheckResult2D temp = GetCollisionCheckResult2DZero();

    do
    {
        VECTOR2D start2point = point2D->GetBasePos() - ray2D->GetStartPos();
        VECTOR2D start2end = ray2D->GetLineVec();
        float dot = VECTOR2D::Dot(start2point, start2end);
        if (MyFunctions::EqualInRangeF((float)fabs((double)(dot)), 1.0f, 0.0001f) == false)
        {
            // 別ベクトルの場所にいました
            break;
        }
        if (start2end.MagnitudeNoSqrt() < start2point.MagnitudeNoSqrt())
        {
            // Rayの延長線上にはいるけど、Rayの上にはいないので
            break;
        }

        temp = GetCollisionCheckResult2D(
            point2D,
            ray2D,
            0,
            point2D->GetBasePos() - ray2D->GetBasePos(),
            ray2D->GetBasePos() - point2D->GetBasePos(),
            point2D->GetBasePos(),
            VECTOR2D::GetZero());
    } while (false);
    return temp;
}

// 円と円の内外判定と衝突判定を行う関数
CollisionCheckResult2D BaseCollision2DManager::CheckHitCircle2DToCircle2D(Circle2D *circle2Da, Circle2D *circle2Db)
{
    // 返り値
    CollisionCheckResult2D temp = GetCollisionCheckResult2DZero();

    // 1の中心点→2の中心点の進行ベクトルを取得
    VECTOR2D distanceVec =
        circle2Db->GetMovedPos(circle2Db->GetBasePos()) -
        circle2Da->GetMovedPos(circle2Da->GetBasePos());

    // 二つの円の半径を取得
    float baseRadius = circle2Da->GetBaseRadius() + circle2Db->GetBaseRadius();

    // 進行ベクトルと二つの円の半径を比較し、進行ベクトルの方が小さかったらfalseを返す
    if (distanceVec.MagnitudeNoSqrt() <= baseRadius * baseRadius)
    {
        temp = GetCollisionCheckResult2D(
            circle2Da,
            circle2Db,
            0,
            circle2Da->GetBasePos() - circle2Db->GetBasePos(),
            circle2Db->GetBasePos() - circle2Da->GetBasePos(),
            VECTOR2D::GetZero(),           // HitPosの計算がめんどくさい。
            VECTOR2D::GetZero());
    }

    // trueを返す
    return temp;
}

// 円とカプセルの内外判定と衝突判定を行う関数
CollisionCheckResult2D BaseCollision2DManager::CheckHitCircle2DToCapsule2D(Circle2D *circle2D, Capsule2D *capsule2D)
{
    // 返り値
    CollisionCheckResult2D temp = GetCollisionCheckResult2DZero();

    // 球体とカプセルの線上最近点を求める(世界座標 無限延長線編)
    VECTOR2D newrPos = VECTOR2D::GetNewrPosOnLine(circle2D->GetMovedPos(
        circle2D->GetBasePos()), 
        capsule2D->GetMovedPos(capsule2D->GetStartPos()), 
        capsule2D->GetMovedPos(capsule2D->GetEndPos()));

    // ベクトル二つを改めて作る
    VECTOR2D startToNewr = newrPos - capsule2D->GetMovedPos(capsule2D->GetStartPos());
    VECTOR2D startToEnd = capsule2D->GetMovedPos(capsule2D->GetEndPos()) - capsule2D->GetMovedPos(capsule2D->GetStartPos());

    // 線上最近点を中心としたカプセルのスフィアを作る
    Circle2D capsuleCircle2D;

    // 線上最近点が、どっちのセンターベクトルを軸とした+方向にあるか、-方向にあるかが確定していないため、それを判断するswitch文
    switch (VECTOR2D::CheckAxisVecPlusOrMinus(startToNewr, startToEnd))
    {
    case 1:
        // startNewrがプラス方向にあるため、線上最近点が確定していない
        if (startToNewr.MagnitudeNoSqrt() <= startToEnd.MagnitudeNoSqrt())
        {
            // カプセルのセンターベクトル内に線上最近点があったということで、作業用のスフィアの値を設定する
            capsuleCircle2D.SetShapeParameter(newrPos, capsule2D->GetBaseRadius());
            temp = BaseCollision2DManager::CheckHitCircle2DToCircle2D(circle2D, &capsuleCircle2D);
            if (0 <= temp.mnResultParam)
            {
                // カプセルの法線ベクトルを取得する
                VECTOR3D capsuleCrossVec3D = VECTOR3D::Cross(capsule2D->GetLineVec().To3D(0.0f), VECTOR3D(0.0f, 0.0f, 1.0f));
                VECTOR2D capsuleCrossVec2D = capsuleCrossVec3D.To2D('x', 'y');
                VECTOR2D capsule2circle = circle2D->GetBasePos() - newrPos;
                capsuleCrossVec2D = VECTOR2D::GetTargetDirectionNewrVec(capsule2circle, capsuleCrossVec2D, -capsuleCrossVec2D);

                temp = GetCollisionCheckResult2D(
                    circle2D,
                    capsule2D,
                    1,
                    capsuleCrossVec2D,
                    capsule2D->GetBasePos() - circle2D->GetBasePos(),
                    VECTOR2D::GetZero(),
                    newrPos);
            }
        }
        else
        {
            // カプセルのセンターベクトル内に線上最近点はなかったということで、+方向の端点とスフィアで当たり判定を計算する
            capsuleCircle2D.SetShapeParameter(capsule2D->GetMovedPos(capsule2D->GetEndPos()), capsule2D->GetBaseRadius());
            temp = BaseCollision2DManager::CheckHitCircle2DToCircle2D(circle2D, &capsuleCircle2D);
            if (0 <= temp.mnResultParam)
            {
                temp = GetCollisionCheckResult2D(
                    circle2D,
                    capsule2D,
                    2,
                    circle2D->GetBasePos() - newrPos,
                    newrPos - circle2D->GetBasePos(),
                    VECTOR2D::GetZero(),
                    newrPos);
            }
        }

        break;
    case -1:
        // 線上最近点がマイナス方向にあるため、-方向の端点とスフィアで当たり判定を計算する
        capsuleCircle2D.SetShapeParameter(capsule2D->GetMovedPos(capsule2D->GetStartPos()), capsule2D->GetBaseRadius());
        temp = BaseCollision2DManager::CheckHitCircle2DToCircle2D(circle2D, &capsuleCircle2D);
        if (0 <= temp.mnResultParam)
        {
            temp = GetCollisionCheckResult2D(
                circle2D,
                capsule2D,
                3,
                circle2D->GetBasePos() - newrPos,
                newrPos - circle2D->GetBasePos(),
                VECTOR2D::GetZero(),
                newrPos);
        }
        break;
    case 0:
        // anewrがプラス方向にもマイナス方向にもないため、何もできない。

        break;
    default:
        // 謎エラー。

        break;
    }

    // 値を返す
    return temp;
}

// 円と三角形の内外判定と衝突判定を行う関数
CollisionCheckResult2D BaseCollision2DManager::CheckHitCircle2DToTriangle2D(Circle2D *circle2D, Triangle2D *triangle2D)
{
    // 返り値
    CollisionCheckResult2D returnValue = GetCollisionCheckResult2DZero();

    // 円の中心点を点に変換する
    Point2D circlePoint;
    circlePoint.SetBasePos(circle2D->GetMovedPos(circle2D->GetBasePos()));

    Ray2D triangleRay;
    triangleRay.SetMoveVec(triangle2D->GetMoveVec());

    bool hitFlag = false;
    int minNum;

    // 三角形の中に円の中心点が入っていたらtrueを返す
    returnValue = BaseCollision2DManager::CheckHitPoint2DToTriangle2D(&circlePoint, triangle2D);
    if (0 <= returnValue.mnResultParam)
    {
        returnValue = GetCollisionCheckResult2D(
            circle2D,
            triangle2D,
            1,
            circle2D->GetBasePos() - triangle2D->GetBasePos(),
            triangle2D->GetBasePos() - circle2D->GetBasePos(),
            circle2D->GetBasePos(),
            VECTOR2D::GetZero());
    }
    else
    {
        // 関数の返り値を保持するための変数
        CollisionCheckResult2D temp = GetCollisionCheckResult2DZero();
        for (int i = 0; i < 3; i++)
        {
            int j = i + 1;
            if (3 <= j)
            {
                j -= 3;
            }

            // 三角形の辺の一つをRayに変換する
            triangleRay.SetShapeParameter(triangle2D->GetVertexPos(i), triangle2D->GetVertexPos(j));
            temp = BaseCollision2DManager::CheckHitCircle2DToRay2D(circle2D, &triangleRay);

            // 辺の一つでも円に当たっていたら処理を行う
            if (0 <= temp.mnResultParam)
            {
                if (returnValue.mnResultParam == -1)
                {
                    returnValue = GetCollisionCheckResult2D(
                        circle2D,
                        triangle2D,
                        (signed long)(i + 1),
                        temp.mvRepulsionVecA, 
                        temp.mvRepulsionVecB,
                        temp.mvHitPos,
                        temp.mvFloatBox);
                }
                else
                {
                    VECTOR2D currentPos = VECTOR2D::GetNewrPosOnLine(circle2D->GetBasePos(), triangleRay.GetStartPos(), triangleRay.GetEndPos());
                    if ((currentPos - circle2D->GetBasePos()).MagnitudeNoSqrt() < (returnValue.mvHitPos - circle2D->GetBasePos()).MagnitudeNoSqrt())
                    {
                        returnValue = GetCollisionCheckResult2D(
                            circle2D,
                            triangle2D,
                            (signed long)(i + 1),
                            temp.mvRepulsionVecA,
                            temp.mvRepulsionVecB,
                            temp.mvHitPos,
                            temp.mvFloatBox);
                    }
                }
            }
        }
    }

    // どのへんにも当たっていなかったのでfalseを返す
    return returnValue;
}

// 円と四角形の内外判定と衝突判定を行う関数

CollisionCheckResult2D BaseCollision2DManager::CheckHitCircle2DToQuadrangle2D(
    Circle2D *circle2D,
    Quadrangle2D *quadrangle2D)
{
    // 
    if (circle2D == nullptr || quadrangle2D == nullptr)
    {
        return GetCollisionCheckResult2DZero();
    }

    const float radius = circle2D->GetBaseRadius();
    if (radius <= 0.0f)
    {
        return GetCollisionCheckResult2DZero();
    }

    // 
    CollisionCheckResult2D returnValue = GetCollisionCheckResult2DZero();

    // 
    Point2D tempPoint;
    tempPoint.SetShapeParameter(circle2D->GetMovedPos(circle2D->GetBasePos()));

    // 
    returnValue = BaseCollision2DManager::CheckHitPoint2DToQuadrangle2D(&tempPoint, quadrangle2D);
    if (0 <= returnValue.mnResultParam)
    {
        // 
        if (quadrangle2D->CheckCollisionNormIn())
        {
            // 
            returnValue = GetCollisionCheckResult2D(
                circle2D,
                quadrangle2D,
                1,
                circle2D->GetMovedPos(circle2D->GetBasePos()) - quadrangle2D->GetMovedPos(quadrangle2D->GetBasePos()),
                quadrangle2D->GetMovedPos(quadrangle2D->GetBasePos()) - circle2D->GetMovedPos(circle2D->GetBasePos()),
                tempPoint.GetMovedPos(tempPoint.GetBasePos()),
                VECTOR2D::GetZero());
        }
        else
        {
            // 
            returnValue = GetCollisionCheckResult2D(
                circle2D,
                quadrangle2D,
                1,
                quadrangle2D->GetMovedPos(quadrangle2D->GetBasePos()) - circle2D->GetMovedPos(circle2D->GetBasePos()),
                circle2D->GetMovedPos(circle2D->GetBasePos()) - quadrangle2D->GetMovedPos(quadrangle2D->GetBasePos()),
                tempPoint.GetMovedPos(tempPoint.GetBasePos()),
                VECTOR2D::GetZero());
        }

        // 
        return returnValue;
    }

    // 
    CollisionCheckResult2D tempValue;

    // 
    tempPoint.SetMoveVec(quadrangle2D->GetMoveVec());

    // 四角の角に当たったかを判定するループ文
    bool minHit = false;
    VECTOR2D minVec;
    for (int i = 0; i < 4; i++)
    {
        // 
        tempPoint.SetShapeParameter(quadrangle2D->GetVertexPos(i));

        // 
        tempValue = BaseCollision2DManager::CheckHitPoint2DToCircle2D(&tempPoint, circle2D);
        if (0 <= tempValue.mnResultParam)
        {
            // 
            minHit = false;

            // 
            if (returnValue.mnResultParam < 0)
            {
                // 
                minHit = true;
            }
            else
            {
                if ((tempValue.mvHitPos - circle2D->GetBasePos()).MagnitudeNoSqrt() < minVec.MagnitudeNoSqrt())
                {
                    // 
                    minHit = true;
                }
            }

            // 
            if (minHit)
            {
                // 
                returnValue = GetCollisionCheckResult2D(
                    circle2D,
                    quadrangle2D,
                    10 + i,
                    tempValue.mvRepulsionVecA,
                    tempValue.mvRepulsionVecB,
                    tempValue.mvHitPos,
                    tempValue.mvFloatBox);

                // 
                minVec = tempValue.mvHitPos - circle2D->GetBasePos();
            }
        }
    }

    // 
    VECTOR2D newMoveVecCircle = circle2D->GetMoveVec();
    VECTOR2D newMoveVecQuad = quadrangle2D->GetMoveVec();

    // 四角の角のいずれかに当たっていた場合は新しい移動ベクトルを取得する
    if (0 <= returnValue.mnResultParam)
    {
        // 
        float moveLateCircle = 0.0f;
        float moveLateQuad = 0.0f;
        if (BaseCollision2DManager::GetCollisionMoveLate(circle2D, quadrangle2D, moveLateCircle, moveLateQuad))
        {
            // 
            if (1.0f < moveLateCircle)
            {
                // 自分じゃない方の当たり判定の移動ベクトルを取得する
                VECTOR2D targetMoveVec = quadrangle2D->GetMoveVec();

                // スライドの進行ベクトルを取得する
                VECTOR2D slideVec = VECTOR2D::GetSlide(circle2D->GetMoveVec(), returnValue.mvRepulsionVecA.Normalize());

                // 新しい移動の進行ベクトルを取得する
                newMoveVecCircle = circle2D->GetMoveVec() + slideVec + (targetMoveVec * (moveLateCircle - 1.0f));
            }
            else
            {
                // 壁ずり移動の進行ベクトルを取得する
                VECTOR2D slideVec = VECTOR2D::GetSlide(circle2D->GetMoveVec(), returnValue.mvRepulsionVecA.Normalize());

                // 壁の法線成分を抜いた新しい進行ベクトルを取得する
                newMoveVecCircle = circle2D->GetMoveVec() + (slideVec * moveLateCircle);
            }

            // 
            if (1.0f < moveLateQuad)
            {
                // 自分じゃない方の当たり判定の移動ベクトルを取得する
                VECTOR2D targetMoveVec = circle2D->GetMoveVec();

                // スライドの進行ベクトルを取得する
                VECTOR2D slideVec = VECTOR2D::GetSlide(quadrangle2D->GetMoveVec(), returnValue.mvRepulsionVecB.Normalize());

                // 新しい移動の進行ベクトルを取得する
                newMoveVecQuad = quadrangle2D->GetMoveVec() + slideVec + (targetMoveVec * (moveLateQuad - 1.0f));
            }
            else
            {
                // 壁ずり移動の進行ベクトルを取得する
                VECTOR2D slideVec = VECTOR2D::GetSlide(quadrangle2D->GetMoveVec(), returnValue.mvRepulsionVecB.Normalize());

                // 壁の法線成分を抜いた新しい進行ベクトルを取得する
                newMoveVecQuad = quadrangle2D->GetMoveVec() + (slideVec * moveLateQuad);
            }
        }

        // めんどくさいので、手っ取り早い方法にします。
        circle2D->SetMoveVec(newMoveVecCircle);
        quadrangle2D->SetMoveVec(newMoveVecQuad);
    }

    // 四角形の各辺を構成する頂点のインデックス
    const int edgeVertex[4][2] =
    {
        { 0, 1 },
        { 1, 3 },
        { 3, 2 },
        { 2, 0 }
    };

    // 
    Circle2D tempCircle(
        circle2D->GetBasePos(),
        circle2D->GetBaseRadius(),
        nullptr,
        CollisionTag::CollisionTag_Checker,
        circle2D->GetCollisionNorm(),
        true,
        false,
        0.0f);

    // 
    tempCircle.SetMoveVec(newMoveVecCircle);

    // 
    Ray2D tempRay;
    tempRay.SetMoveVec(newMoveVecQuad);

    // 
    for (int i = 0; i < 4; i++)
    {
        // 
        if (quadrangle2D->CheckCollisionNormIn())
        {
            tempRay.SetShapeParameter(
                quadrangle2D->GetVertexPos(edgeVertex[i][1]),
                quadrangle2D->GetVertexPos(edgeVertex[i][0]));
        }
        else
        {
            tempRay.SetShapeParameter(
                quadrangle2D->GetVertexPos(edgeVertex[i][0]),
                quadrangle2D->GetVertexPos(edgeVertex[i][1]));
        }

        // 
        tempValue = BaseCollision2DManager::CheckHitCircle2DToRay2D(&tempCircle, &tempRay);
        if (0 <= tempValue.mnResultParam)
        {
            // 
            minHit = false;

            // 
            if (returnValue.mnResultParam < 0)
            {
                // 
                minHit = true;
            }
            else
            {
                // 
                if ((tempValue.mvHitPos - circle2D->GetBasePos()).MagnitudeNoSqrt() < minVec.MagnitudeNoSqrt())
                {
                    // 
                    minHit = true;
                }
            }

            // 
            if (minHit)
            {
                // 
                returnValue = GetCollisionCheckResult2D(
                    circle2D,
                    quadrangle2D,
                    20 + i,
                    tempValue.mvRepulsionVecA,
                    tempValue.mvRepulsionVecB,
                    tempValue.mvHitPos,
                    tempValue.mvFloatBox);

                // 
                minVec = tempValue.mvHitPos - circle2D->GetBasePos();
            }
        }
    }

    // 
    return returnValue;
}

// 円とレイの内外判定と衝突判定を行う関数
CollisionCheckResult2D BaseCollision2DManager::CheckHitCircle2DToRay2D(Circle2D *circle2D, Ray2D *ray2D)
{
    // 円の半径を取得し、0.0未満だったら当たるわけないので
    const float radius = circle2D->GetBaseRadius();
    if (radius < 0.0f)
    {
        return GetCollisionCheckResult2DZero();;
    }

    // 返り値
    CollisionCheckResult2D returnValue = GetCollisionCheckResult2DZero();

    // 移動後の円の中心
    const VECTOR2D movedCirclePos = circle2D->GetMovedPos(circle2D->GetBasePos());

    // 移動後の線分の両端
    const VECTOR2D movedStartPos = ray2D->GetMovedPos(ray2D->GetStartPos());
    const VECTOR2D movedEndPos = ray2D->GetMovedPos(ray2D->GetEndPos());

    // 移動後の線分上で、移動後の円の中心に最も近い点
    const VECTOR2D movedNearestPos = VECTOR2D::GetNearestPosOnLineSegment(
            movedCirclePos,
            movedStartPos,
            movedEndPos);

    // 最近点から円の中心までのベクトル
    const VECTOR2D movedToNearest = movedNearestPos - movedCirclePos;
    const float distanceSquared = VECTOR2D::Dot(movedToNearest, movedToNearest);
    const float radiusSquared = radius * radius;

    // 円と有限線分が離れている
    if (radiusSquared < distanceSquared)
    {
        return returnValue;
    }

    // 衝突法線用のベクトル
    VECTOR2D crossVec2D(-ray2D->GetLineVec().GetY(), ray2D->GetLineVec().GetX());

    /*
        返却用の位置は移動前の座標を使用する。

        movedNearestPos は衝突判定に使った移動後の最近点。
        返却値に使う位置は、線分の移動量を取り除いた位置にする。
    */

    returnValue = GetCollisionCheckResult2D(
        circle2D,
        ray2D,
        0,
        crossVec2D,
        ray2D->GetBasePos() - circle2D->GetBasePos(),
        movedNearestPos,
        VECTOR2D(0.0f, 0.0f));

    return returnValue;
}

// カプセルとカプセルの内外判定と衝突判定を行う関数
CollisionCheckResult2D BaseCollision2DManager::CheckHitCapsule2DToCapsule2D(Capsule2D *capsule2Da, Capsule2D *capsule2Db)
{
    CollisionCheckResult2D temp = GetCollisionCheckResult2DZero();

    if (capsule2Da == nullptr ||
        capsule2Db == nullptr)
    {
        return temp;
    }

    /* 最終的にスフィアとスフィアの計算にする予定。 */
    // 計算用のスフィアの座標を記憶しておく変数
    VECTOR2D circle2DPos = VECTOR2D::GetZero();

    // スフィアとスフィアの当たり判定の計算で使う、スフィアのもとになるカプセル
    Capsule2D targetCapsule;

    // 計算用のスフィアからみた計算用のカプセルの線上最近点の世界座標を保持する変数
    VECTOR2D sphereToCapsuleNewrPointPos = VECTOR2D::GetZero();

    // 計算用のスフィアの半径
    float radius = 0.0f;

    // スフィアになってくれるカプセルの端を探している
    for (int i = 0; i < 4; i++)
    {
        VECTOR2D thisToTargetNewrPos = VECTOR2D::GetZero();
        VECTOR2D thisCapsulePos = VECTOR2D::GetZero();
        VECTOR2D targetCapsuleStartPos = VECTOR2D::GetZero();
        VECTOR2D targetCapsuleEndPos = VECTOR2D::GetZero();

        switch (i)
        {
        case 0:
            thisCapsulePos = capsule2Da->GetMovedPos(capsule2Da->GetStartPos());
            targetCapsuleStartPos = capsule2Db->GetMovedPos(capsule2Db->GetStartPos());
            targetCapsuleEndPos = capsule2Db->GetMovedPos(capsule2Db->GetEndPos());
            thisToTargetNewrPos = VECTOR2D::GetNewrPosOnLine(thisCapsulePos, targetCapsuleStartPos, targetCapsuleEndPos);
            break;
        case 1:
            thisCapsulePos = capsule2Da->GetMovedPos(capsule2Da->GetEndPos());
            targetCapsuleStartPos = capsule2Db->GetMovedPos(capsule2Db->GetStartPos());
            targetCapsuleEndPos = capsule2Db->GetMovedPos(capsule2Db->GetEndPos());
            thisToTargetNewrPos = VECTOR2D::GetNewrPosOnLine(thisCapsulePos, targetCapsuleStartPos, targetCapsuleEndPos);
            break;
        case 2:
            thisCapsulePos = capsule2Db->GetMovedPos(capsule2Db->GetStartPos());
            targetCapsuleStartPos = capsule2Da->GetMovedPos(capsule2Da->GetStartPos());
            targetCapsuleEndPos = capsule2Da->GetMovedPos(capsule2Da->GetEndPos());
            thisToTargetNewrPos = VECTOR2D::GetNewrPosOnLine(thisCapsulePos, targetCapsuleStartPos, targetCapsuleEndPos);
            break;
        case 3:
            thisCapsulePos = capsule2Db->GetMovedPos(capsule2Db->GetEndPos());
            targetCapsuleStartPos = capsule2Da->GetMovedPos(capsule2Da->GetStartPos());
            targetCapsuleEndPos = capsule2Da->GetMovedPos(capsule2Da->GetEndPos());
            thisToTargetNewrPos = VECTOR2D::GetNewrPosOnLine(thisCapsulePos, targetCapsuleStartPos, targetCapsuleEndPos);
            break;
        default:
            break;
        }

        // 直前で計算した点Pからカプセルの直線ABの線上最近点までのベクトルを持つ変数
        VECTOR2D nowThisToTargetNewrVec = VECTOR2D::GetZero();

        // これまでの計算で一番、点Pからカプセルの直線ABの線上最近点までのベクトルが小さかった時の結果を持つ変数
        VECTOR2D minThisToTargetNewrVec = sphereToCapsuleNewrPointPos - circle2DPos;

        // これまでの計算で求めた線上最近点が直線ABの中に入っているならtrue
        if (VECTOR2D::CheckPointInVector(thisToTargetNewrPos, targetCapsuleStartPos, targetCapsuleEndPos) == 1)
        {
            // 直前の計算からでた点Pから線上最近点へのベクトルをそのまま代入する。
            nowThisToTargetNewrVec = thisToTargetNewrPos - thisCapsulePos;
        }
        else
        {
            // 線上最近点をカプセルの両端のどちらかにしなければいけならず、線上最近点が-方向にある可能性も捨てきれない場合の処理
            switch (VECTOR2D::CheckAxisVecPlusOrMinus(
                thisToTargetNewrPos - targetCapsuleStartPos,
                targetCapsuleEndPos - targetCapsuleStartPos))
            {
            case 0: /* わけわからんベクトルを向いているとき */
                // 線上最近点を……

                break;
            case 1: /* +方向に向かって伸びているとき */
                // 線上最近点をendPosに設定する
                thisToTargetNewrPos = targetCapsuleEndPos;
                break;
            case -1: /* -方向に向かって伸びているとき */
                // 線上最近点をstartPosに設定する
                thisToTargetNewrPos = targetCapsuleStartPos;
                break;
            default:
                /* 謎えらー */
                break;
            }

            // 点Pから線上最近点までのベクトルを設定する
            nowThisToTargetNewrVec = thisToTargetNewrPos - thisCapsulePos;
        }

        // 二つの点pから線上最近点までのベクトル同士を比べ、現在のベクトルの方が小さかった場合、もしくはiが0の場合はtrue
        if (nowThisToTargetNewrVec.MagnitudeNoSqrt() < minThisToTargetNewrVec.MagnitudeNoSqrt() ||
            i == 0)
        {
            // 計算用のスフィアの位置を再設定する
            circle2DPos = thisCapsulePos;

            // カプセルとスフィアの当たり判定の計算で使うカプセルを再設定する
            if (i <= 1)
            {
                targetCapsule = *capsule2Db;

                // 計算用のスフィアの半径を再設定する
                radius = capsule2Da->GetBaseRadius();

            }
            else /* 2 <= i */
            {
                targetCapsule = *capsule2Da;

                // 計算用のスフィアの半径を再設定する
                radius = capsule2Db->GetBaseRadius();
            }

            // 計算用のスフィアから見た、カプセルの線上最近点の座標を記憶しておく
            sphereToCapsuleNewrPointPos = thisToTargetNewrPos;
        }
    }

    // 計算用のスフィアを作る * 2
    Circle2D circle2Da;
    circle2Da.SetBasePos(circle2DPos);
    circle2Da.SetBaseRadius(radius);
    Circle2D circle2Db;
    circle2Db.SetBasePos(sphereToCapsuleNewrPointPos);
    circle2Db.SetBaseRadius(targetCapsule.GetBaseRadius());

    // スフィアとスフィアの計算をし、結果をtempに代入する
    temp = BaseCollision2DManager::CheckHitCircle2DToCircle2D(&circle2Da, &circle2Db);
    if (0 <= temp.mnResultParam)
    {
        temp = GetCollisionCheckResult2D(
            capsule2Da,
            capsule2Db,
            0,
            capsule2Da->GetBasePos() - capsule2Db->GetBasePos(),
            capsule2Db->GetBasePos() - capsule2Da->GetBasePos(),
            circle2DPos,
            sphereToCapsuleNewrPointPos);
    }

    // 計算結果を返す
    return temp;
}

// カプセルと三角形の内外判定と衝突判定を行う関数
CollisionCheckResult2D BaseCollision2DManager::CheckHitCapsule2DToTriangle2D(Capsule2D *capsule2D, Triangle2D *triangle2D)
{
    return GetCollisionCheckResult2DZero();
}

// カプセルと四角形の内外判定と衝突判定を行う関数
CollisionCheckResult2D BaseCollision2DManager::CheckHitCapsule2DToQuadrangle2D(Capsule2D *capsule2D, Quadrangle2D *quadrangle2D)
{
    return GetCollisionCheckResult2DZero();
}

// カプセルとレイの内外判定と衝突判定を行う関数
CollisionCheckResult2D BaseCollision2DManager::CheckHitCapsule2DToRay2D(Capsule2D *capsule2D, Ray2D *ray2D)
{
    // 返り値
    CollisionCheckResult2D temp = GetCollisionCheckResult2DZero();

    return temp;
}

// 三角形と三角形の内外判定と衝突判定を行う関数
CollisionCheckResult2D BaseCollision2DManager::CheckHitTriangle2DToTriangle2D(Triangle2D *triangle2Da, Triangle2D *triangle2Db)
{
    CollisionCheckResult2D returnValue = GetCollisionCheckResult2DZero();
    CollisionCheckResult2D temp = GetCollisionCheckResult2DZero();

    Ray2D triangleRay;
    triangleRay.SetMoveVec(triangle2Db->GetMoveVec());
    for (int i = 0; i < 3; i++)
    {
        int j = i + 1;
        if (3 <= j)
        {
            j -= 3;
        }

        // 三角形の辺の一つをRayに変換する
        triangleRay.SetShapeParameter(triangle2Db->GetVertexPos(i), triangle2Db->GetVertexPos(j));

        // 辺の一つでももう片方の三角形に当たっていたらtrueを返す
        temp = BaseCollision2DManager::CheckHitTriangle2DToRay2D(triangle2Da, &triangleRay);
        if (0 <= temp.mnResultParam)
        {
            if (returnValue.mnResultParam == -1)
            {
                returnValue = GetCollisionCheckResult2D(
                    triangle2Da,
                    triangle2Db,
                    (temp.mnResultParam * 3) + i + 1,
                    temp.mvRepulsionVecA,
                    temp.mvRepulsionVecB,
                    temp.mvHitPos,
                    temp.mvFloatBox);
            }
            else
            {
                // これまでで一番近かった衝突地点と今回の衝突地点と、どちらがより近かったかを比較する
                VECTOR2D minVec = returnValue.mvHitPos - triangleRay.GetStartPos();
                VECTOR2D tempVec = temp.mvHitPos - triangleRay.GetStartPos();
                if (tempVec.MagnitudeNoSqrt() < minVec.MagnitudeNoSqrt())
                {
                    returnValue = GetCollisionCheckResult2D(
                        triangle2Da,
                        triangle2Db,
                        (temp.mnResultParam * 3) + i + 1,
                        temp.mvRepulsionVecA,
                        temp.mvRepulsionVecB,
                        temp.mvHitPos,
                        temp.mvFloatBox);
                }
            }
        }
    }

    // どのへんにも当たっていなかったのでfalseを返す
    return returnValue;
}

// 三角形と四角形の内外判定と衝突判定を行う関数
CollisionCheckResult2D BaseCollision2DManager::CheckHitTriangle2DToQuadrangle2D(Triangle2D *triangle2D, Quadrangle2D *quadrangle2D)
{
    CollisionCheckResult2D returnValue = GetCollisionCheckResult2DZero();
    CollisionCheckResult2D temp = GetCollisionCheckResult2DZero();

    Ray2D triangleRay;
    triangleRay.SetMoveVec(triangle2D->GetMoveVec());

    for (int i = 0; i < 3; i++)
    {
        int j = i + 1;
        if (3 <= j)
        {
            j -= 3;
        }

        // 三角形の辺の一つをRayに変換する
        triangleRay.SetShapeParameter(triangle2D->GetVertexPos(i), triangle2D->GetVertexPos(j));

        // 辺の一つでももう片方の三角形に当たっていたらtrueを返す
        temp = BaseCollision2DManager::CheckHitQuadrangle2DToRay2D(quadrangle2D, &triangleRay);
        if (0 <= temp.mnResultParam)
        {
            if (returnValue.mnResultParam == -1)
            {
                returnValue = GetCollisionCheckResult2D(
                    triangle2D,
                    quadrangle2D,
                    (temp.mnResultParam * 3) + i + 1,
                    temp.mvRepulsionVecB,
                    temp.mvRepulsionVecA,
                    temp.mvHitPos,
                    temp.mvFloatBox);
            }
            else
            {
                // これまでで一番近かった衝突地点と今回の衝突地点と、どちらがより近かったかを比較する
                VECTOR2D minVec = returnValue.mvHitPos - triangleRay.GetStartPos();
                VECTOR2D tempVec = temp.mvHitPos - triangleRay.GetStartPos();
                if (tempVec.MagnitudeNoSqrt() < minVec.MagnitudeNoSqrt())
                {
                    returnValue = GetCollisionCheckResult2D(
                        triangle2D,
                        quadrangle2D,
                        (temp.mnResultParam * 3) + i + 1,
                        temp.mvRepulsionVecB,
                        temp.mvRepulsionVecA,
                        temp.mvHitPos,
                        temp.mvFloatBox);
                }
            }
        }
    }

    // どのへんにも当たっていなかったのでfalseを返す
    return returnValue;
}

CollisionCheckResult2D BaseCollision2DManager::CheckHitTriangle2DToRay2D(Triangle2D *triangle2D, Ray2D *ray2D)
{
    // 返り値
    CollisionCheckResult2D returnValue = GetCollisionCheckResult2DZero();

    // 関数の返り値を受け取る変数
    CollisionCheckResult2D temp = GetCollisionCheckResult2DZero();

    // 作業用変数
    Ray2D triangleRay;

    // 三角形の辺の一つ一つをRayに変換し、RayとRayの当たり判定の計算を行うループ
    for (int i = 0; i < 3; i++)
    {
        int j = 1 + 1;
        if (3 <= j)
        {
            j -= 3;
        }

        // 三角形の辺をRayに変換する
        triangleRay.SetShapeParameter(triangle2D->GetVertexPos(i), triangle2D->GetVertexPos(j));

        // RayとRayの当たり判定の計算を行う
        temp = BaseCollision2DManager::CheckHitRay2DToRay2D(&triangleRay, ray2D);

        // 三角形の辺と自分のRayが当たっている場合は特別な処理を行う
        if (0 <= temp.mnResultParam)
        {
            signed long resultParam = i + 1;
            if (returnValue.mnResultParam == -1)
            {
                returnValue = GetCollisionCheckResult2D(
                    triangle2D,
                    ray2D,
                    resultParam,
                    temp.mvRepulsionVecA,
                    temp.mvRepulsionVecB,
                    temp.mvHitPos,
                    temp.mvFloatBox);
            }
            else
            {
                // これまでで一番近かった衝突地点と今回の衝突地点と、どちらがより近かったかを比較する
                VECTOR2D minVec = returnValue.mvHitPos - ray2D->GetStartPos();
                VECTOR2D tempVec = temp.mvHitPos - ray2D->GetStartPos();
                if (tempVec.MagnitudeNoSqrt() < minVec.MagnitudeNoSqrt())
                {
                    // 今回の衝突地点を一番近かった衝突地点として保存しておく
                    returnValue = GetCollisionCheckResult2D(
                        triangle2D,
                        ray2D,
                        resultParam,
                        temp.mvRepulsionVecA,
                        temp.mvRepulsionVecB,
                        temp.mvHitPos,
                        temp.mvFloatBox);
                }
            }
        }
    }

    // 計算結果を返す
    return returnValue;
}

// 四角形と四角形の内外判定と衝突判定を行う関数
CollisionCheckResult2D BaseCollision2DManager::CheckHitQuadrangle2DToQuadrangle2D(Quadrangle2D *quadrangle2Da, Quadrangle2D *quadrangle2Db)
{
    CollisionCheckResult2D returnValue = GetCollisionCheckResult2DZero();

    if (quadrangle2Da == nullptr || quadrangle2Db == nullptr)
    {
        return returnValue;
    }

    /*
        四角形の頂点は現在のQuadrangle2Dの仕様に合わせる。

             0 -------- 1
              \          \
               2 -------- 3

        実際の辺の接続順は

        0 -> 1
        1 -> 3
        3 -> 2
        2 -> 0

        とする。
    */

    const int edgeVertex[4][2] =
    {
        { 0, 1 },
        { 1, 3 },
        { 3, 2 },
        { 2, 0 }
    };

    const float eps = 0.00001f;

    /*
        移動前の頂点。
        SATそのものは移動前の形状を使用し、
        AとBの相対移動によって衝突時刻を求める。
    */
    VECTOR2D aVertex[4];
    VECTOR2D bVertex[4];

    for (int i = 0; i < 4; ++i)
    {
        aVertex[i] = quadrangle2Da->GetVertexPos(i);
        bVertex[i] = quadrangle2Db->GetVertexPos(i);
    }

    /*
        AとBの移動ベクトル。

        Aを固定して考え、
        Bが

            BMove - AMove

        だけ相対的に動くものとして計算する。
    */
    VECTOR2D relativeMoveVec =
        quadrangle2Db->GetMoveVec() -
        quadrangle2Da->GetMoveVec();

    /*
        四角形の中心。

        BasePosでも計算可能だが、
        四頂点の平均を使用した方が
        「AからBへ向かう方向」を決める用途には安定する。
    */
    VECTOR2D centerA = VECTOR2D::GetZero();
    VECTOR2D centerB = VECTOR2D::GetZero();

    for (int i = 0; i < 4; ++i)
    {
        centerA += aVertex[i];
        centerB += bVertex[i];
    }

    centerA = centerA * 0.25f;
    centerB = centerB * 0.25f;

    /*
        SATで使用する軸。

        凸四角形Aの4辺の法線
        凸四角形Bの4辺の法線

        合計8軸を調べる。

        四角形同士の衝突判定では、
        この8軸だけで十分。
    */
    VECTOR2D axis[8];
    int axisCount = 0;

    for (int shape = 0; shape < 2; ++shape)
    {
        for (int edge = 0; edge < 4; ++edge)
        {
            VECTOR2D p0;
            VECTOR2D p1;

            if (shape == 0)
            {
                p0 = aVertex[edgeVertex[edge][0]];
                p1 = aVertex[edgeVertex[edge][1]];
            }
            else
            {
                p0 = bVertex[edgeVertex[edge][0]];
                p1 = bVertex[edgeVertex[edge][1]];
            }

            VECTOR2D edgeVec = p1 - p0;

            if (edgeVec.MagnitudeNoSqrt() <= eps)
            {
                continue;
            }

            /*
                2Dの辺の法線。
            */
            VECTOR2D normal(
                -edgeVec.GetY(),
                edgeVec.GetX());

            normal = normal.Normalize();

            axis[axisCount] = normal;
            ++axisCount;
        }
    }

    if (axisCount == 0)
    {
        return returnValue;
    }

    /*
        SATの時間区間。

        各軸について

            |B中心 - A中心|
                <=
            Aの半径 + Bの半径

        で重なっている。

        B-Aの軸方向距離は時間によって変化するため、
        その軸上で「いつからいつまで重なるか」を求める。

        globalEnter :
            全ての軸で重なり始める時刻

        globalExit :
            どれかの軸で分離してしまう時刻
    */
    float globalEnter = 0.0f;
    float globalExit = 1.0f;

    /*
        最初から重なっている場合に、
        最小侵入量の軸を保存する。

        この軸をスライド移動用の法線にも使用する。
    */
    float minimumPenetration = MyFunctions::GetMaxFloat();
    VECTOR2D penetrationAxis = VECTOR2D::GetZero();

    /*
        実際に衝突開始時刻を決めた軸。
    */
    VECTOR2D hitAxis = VECTOR2D::GetZero();

    bool hitAxisFound = false;

    for (int i = 0; i < axisCount; ++i)
    {
        VECTOR2D currentAxis = axis[i];

        /*
            Aの射影範囲。
        */
        float minA = VECTOR2D::Dot(aVertex[0], currentAxis);
        float maxA = minA;

        for (int j = 1; j < 4; ++j)
        {
            float projection =
                VECTOR2D::Dot(aVertex[j], currentAxis);

            if (projection < minA)
            {
                minA = projection;
            }

            if (maxA < projection)
            {
                maxA = projection;
            }
        }

        /*
            Bの射影範囲。
        */
        float minB = VECTOR2D::Dot(bVertex[0], currentAxis);
        float maxB = minB;

        for (int j = 1; j < 4; ++j)
        {
            float projection =
                VECTOR2D::Dot(bVertex[j], currentAxis);

            if (projection < minB)
            {
                minB = projection;
            }

            if (maxB < projection)
            {
                maxB = projection;
            }
        }

        /*
            射影区間を中心＋半径に変換する。
        */
        float centerProjectionA =
            (minA + maxA) * 0.5f;

        float centerProjectionB =
            (minB + maxB) * 0.5f;

        float radiusA =
            (maxA - minA) * 0.5f;

        float radiusB =
            (maxB - minB) * 0.5f;

        float radiusSum = radiusA + radiusB;

        /*
            B中心 - A中心。
        */
        float distance =
            centerProjectionB - centerProjectionA;

        /*
            相対移動量をこの軸に投影する。
        */
        float move =
            VECTOR2D::Dot(relativeMoveVec, currentAxis);

        /*
            すでに重なっているか確認する。
        */
        if (fabsf(distance) <= radiusSum + eps)
        {
            /*
                現在の侵入量。
            */
            float penetration =
                radiusSum - fabsf(distance);

            if (penetration < minimumPenetration)
            {
                minimumPenetration = penetration;

                penetrationAxis = currentAxis;

                /*
                    A -> B方向に法線を向ける。
                */
                if (distance < 0.0f)
                {
                    penetrationAxis =
                        penetrationAxis * -1.0f;
                }
            }
        }
        else
        {
            /*
                現在は分離している。

                相対移動がない場合、
                この軸で永遠に分離したままなので
                衝突しない。
            */
            if (fabsf(move) <= eps)
            {
                return returnValue;
            }
        }

        /*
            -radiusSum <= distance + move * t <= radiusSum

            を解く。
        */
        if (fabsf(move) <= eps)
        {
            /*
                移動しない軸。
            */
            if (distance < -radiusSum - eps ||
                radiusSum + eps < distance)
            {
                return returnValue;
            }

            continue;
        }

        float t0 =
            (-radiusSum - distance) / move;

        float t1 =
            (radiusSum - distance) / move;

        if (t1 < t0)
        {
            float temp = t0;
            t0 = t1;
            t1 = temp;
        }

        /*
            この軸で重なっている時間区間と、
            全軸の重なっている時間区間を
            共通部分にする。
        */
        if (globalEnter < t0)
        {
            globalEnter = t0;
        }

        if (t1 < globalExit)
        {
            globalExit = t1;
        }

        /*
            この軸によって衝突開始時刻が
            更新された場合、この軸が
            衝突法線候補になる。
        */
        if (globalEnter >= t0 - eps)
        {
            hitAxis = currentAxis;
            hitAxisFound = true;
        }

        /*
            時間区間がなくなった。
        */
        if (globalEnter > globalExit + eps)
        {
            return returnValue;
        }
    }

    /*
        0～1の移動区間内で衝突しているか確認。
    */
    if (globalExit < -eps ||
        globalEnter > 1.0f + eps)
    {
        return returnValue;
    }

    /*
        実際の衝突時刻。

        すでに重なっている場合は0。
    */
    float hitTime = globalEnter;

    if (hitTime < 0.0f)
    {
        hitTime = 0.0f;
    }

    if (hitTime > 1.0f)
    {
        hitTime = 1.0f;
    }

    /*
        衝突法線を決める。
    */
    VECTOR2D normal;

    if (hitTime <= eps)
    {
        /*
            最初から重なっていた場合。

            SATで最も侵入量の小さい軸を使用する。
        */
        normal = penetrationAxis;

        /*
            念のためA→B方向に向ける。
        */
        VECTOR2D centerDistance =
            (centerB - centerA) + relativeMoveVec * hitTime;

        if (VECTOR2D::Dot(centerDistance, normal) < 0.0f)
        {
            normal = normal * -1.0f;
        }
    }
    else
    {
        /*
            移動途中で初めて衝突した場合。
        */
        normal = hitAxis;

        /*
            衝突時点でのA→B方向を求める。
        */
        VECTOR2D centerDistance =
            (centerB - centerA) + relativeMoveVec * hitTime;

        if (VECTOR2D::Dot(centerDistance, normal) < 0.0f)
        {
            normal = normal * -1.0f;
        }
    }

    /*
        念のため正規化。
    */
    normal = normal.Normalize();

    /*
        A/Bそれぞれに対する反発方向。

        normalはA→Bなので、

            A : Bから離れる方向 = -normal
            B : Aから離れる方向 =  normal
    */
    VECTOR2D repulsionA =
        normal * -1.0f;

    VECTOR2D repulsionB =
        normal;

    /*
        衝突時点の四角形位置を計算する。
    */
    VECTOR2D aHitMove =
        quadrangle2Da->GetMoveVec() * hitTime;

    VECTOR2D bHitMove =
        quadrangle2Db->GetMoveVec() * hitTime;

    VECTOR2D hitVertexA[4];
    VECTOR2D hitVertexB[4];

    for (int i = 0; i < 4; ++i)
    {
        hitVertexA[i] = aVertex[i] + aHitMove;
        hitVertexB[i] = bVertex[i] + bHitMove;
    }

    /*
        接触座標を求める。

        SATの衝突軸上で、

            AのB側の最外点
            BのA側の最外点

        を求め、その中点を衝突位置とする。

        完全に辺同士で接触した場合は
        その接触部分の代表位置になる。
    */
    float bestAProjection =
        -MyFunctions::GetMaxFloat();

    float bestBProjection =
        MyFunctions::GetMaxFloat();

    std::vector<VECTOR2D> aHitVertices;
    std::vector<VECTOR2D> bHitVertices;

    for (int i = 0; i < 4; ++i)
    {
        aHitVertices.push_back(
            quadrangle2Da->GetVertexPos(i) +
            quadrangle2Da->GetMoveVec() * hitTime);

        bHitVertices.push_back(
            quadrangle2Db->GetVertexPos(i) +
            quadrangle2Db->GetMoveVec() * hitTime);
    }

    VECTOR2D hitPos = Quadrangle2D::GetQuadrangleContactPoint(aHitVertices, bHitVertices, normal);

    /*
        すでに重なっている場合、
        supportA / supportB の中点だけでは
        「内部にめり込んだ状態」の代表位置として
        不自然になる場合がある。

        その場合でも現在の四角形同士の
        接触軸上の位置として使用できる。
    */

    /*
        結果を生成。

        mnResultParam >= 0
            → 衝突

        mvRepulsionVecA
            → Aのスライド移動用法線

        mvRepulsionVecB
            → Bのスライド移動用法線

        mvHitPos
            → 衝突位置
    */
    returnValue = GetCollisionCheckResult2D(
        quadrangle2Da,
        quadrangle2Db,
        1,
        repulsionA,
        repulsionB,
        hitPos,
        VECTOR2D(hitTime, minimumPenetration));

    return returnValue;
}

// 四角形とレイの内外判定と衝突判定を行う関数
CollisionCheckResult2D BaseCollision2DManager::CheckHitQuadrangle2DToRay2D(Quadrangle2D *quadrangle2D, Ray2D *ray2D)
{
    // 返り値
    CollisionCheckResult2D returnValue = GetCollisionCheckResult2DZero();

    // 関数の返り値を受け取る変数
    CollisionCheckResult2D temp = GetCollisionCheckResult2DZero();

    // 作業用変数
    Ray2D quadrangleRay;

    // 四角形の移動量をRayに記憶させる
    quadrangleRay.SetMoveVec(quadrangle2D->GetMoveVec());

    // 
    const int edgeStart[] = { 0, 1, 3, 2 };
    const int edgeEnd[] = { 1, 3, 2, 0 };
    for (int i = 0; i < 4; ++i)
    {
        // 四角形の辺をRayに変換する
        quadrangleRay.SetShapeParameter(quadrangle2D->GetVertexPos(edgeStart[i]), quadrangle2D->GetVertexPos(edgeEnd[i]));

        // 四角形の辺と自分のRayが当たっている場合は特別な処理を行う
        temp = BaseCollision2DManager::CheckHitRay2DToRay2D(&quadrangleRay, ray2D);
        if (0 <= temp.mnResultParam)
        {
            // これまでで一番近かった衝突地点と今回の衝突地点と、どちらがより近かったかを比較する
            VECTOR2D minVec = returnValue.mvHitPos - ray2D->GetStartPos();
            VECTOR2D tempVec = temp.mvHitPos - ray2D->GetStartPos();
            if ((returnValue.mnResultParam == -1) ||
                (tempVec.MagnitudeNoSqrt() < minVec.MagnitudeNoSqrt()))
            {
                // 今回の衝突地点を一番近かった衝突地点として保存しておく
                returnValue = GetCollisionCheckResult2D(
                    quadrangle2D,
                    ray2D,
                    i,
                    temp.mvRepulsionVecA,
                    temp.mvRepulsionVecB,
                    temp.mvHitPos,
                    temp.mvFloatBox);
            }
        }
    }

    // 計算結果を返す
    return returnValue;
}

CollisionCheckResult2D BaseCollision2DManager::CheckHitRay2DToRay2D(
    Ray2D *ray2Da,
    Ray2D *ray2Db)
{
    CollisionCheckResult2D result =
        GetCollisionCheckResult2DZero();

    const float eps = 0.00001f;

    const VECTOR2D p = ray2Da->GetStartPos();
    const VECTOR2D q = ray2Db->GetStartPos();
    const VECTOR2D r = ray2Da->GetLineVec();
    const VECTOR2D s = ray2Db->GetLineVec();

    const float rr = VECTOR2D::Dot(r, r);
    const float ss = VECTOR2D::Dot(s, s);

    const VECTOR2D qmp = q - p;

    const float rxs = VECTOR2D::Cross(r, s);
    const float qmpxr = VECTOR2D::Cross(qmp, r);

    // 内分比を計算するための補助関数
    auto clamp01 = [](float t) -> float
        {
            if (t < 0.0f) return 0.0f;
            if (t > 1.0f) return 1.0f;
            return t;
        };

    // 線分の法線を生成する
    auto getNormal = [](const VECTOR2D &line)->
        VECTOR2D
        {
            VECTOR2D normal(-line.GetY(), line.GetX());

            float len = normal.Magnitude();

            if (len > 0.0f)
                normal = normal / len;

            return normal;
        };

    // 衝突結果を生成する
    auto makeResult = [&](float t, float u, const VECTOR2D &hitPos)->
        CollisionCheckResult2D
        {
            VECTOR2D normalA = getNormal(r);
            VECTOR2D normalB = getNormal(s);

            // 既存コードと同様、法線の向きは
            // GetTargetDirectionNewrVec() で調整する。
            VECTOR2D a2b =
                ray2Db->GetBasePos() - ray2Da->GetBasePos();

            VECTOR2D b2a =
                ray2Da->GetBasePos() - ray2Db->GetBasePos();

            normalA = VECTOR2D::GetTargetDirectionNewrVec(
                a2b, normalA, -normalA);

            normalB = VECTOR2D::GetTargetDirectionNewrVec(
                b2a, normalB, -normalB);

            return GetCollisionCheckResult2D(
                ray2Da,
                ray2Db,
                0,
                normalB,
                normalA,
                hitPos,
                VECTOR2D(t, u));
        };

    // 両方が点の場合
    if (rr <= eps * eps && ss <= eps * eps)
    {
        if ((p - q).MagnitudeNoSqrt() <= eps * eps)
        {
            return makeResult(0.0f, 0.0f, p);
        }

        return result;
    }

    // Aが点の場合
    if (rr <= eps * eps)
    {
        if (ss > eps * eps)
        {
            float u = VECTOR2D::Dot(p - q, s) / ss;
            u = clamp01(u);

            VECTOR2D closest = q + s * u;

            if ((closest - p).MagnitudeNoSqrt() <= eps * eps)
            {
                return makeResult(0.0f, u, p);
            }
        }

        return result;
    }

    // Bが点の場合
    if (ss <= eps * eps)
    {
        float t = VECTOR2D::Dot(q - p, r) / rr;
        t = clamp01(t);

        VECTOR2D closest = p + r * t;

        if ((closest - q).MagnitudeNoSqrt() <= eps * eps)
        {
            return makeResult(t, 0.0f, q);
        }

        return result;
    }

    // 非平行の場合
    if (fabsf(rxs) > eps)
    {
        float t = VECTOR2D::Cross(qmp, s) / rxs;
        float u = VECTOR2D::Cross(qmp, r) / rxs;

        if (t < -eps || t > 1.0f + eps ||
            u < -eps || u > 1.0f + eps)
        {
            return result;
        }

        t = clamp01(t);
        u = clamp01(u);

        VECTOR2D hitPos = p + r * t;

        return makeResult(t, u, hitPos);
    }

    // 平行だが、同一直線上ではない
    if (fabsf(qmpxr) > eps)
    {
        return result;
    }

    // ここから同一直線上の処理
    // Bの両端をAのパラメータに変換する
    float t0 = VECTOR2D::Dot(q - p, r) / rr;
    float t1 = VECTOR2D::Dot(q + s - p, r) / rr;

    float overlapMin = fmaxf(0.0f, fminf(t0, t1));
    float overlapMax = fminf(1.0f, fmaxf(t0, t1));

    // 共通区間が存在しない
    if (overlapMin > overlapMax + eps)
    {
        return result;
    }

    // Aの始点に最も近い共通点を選択
    float t = clamp01(overlapMin);
    VECTOR2D hitPos = p + r * t;

    // 共通点をBのパラメータに変換
    float u = VECTOR2D::Dot(hitPos - q, s) / ss;
    u = clamp01(u);

    return makeResult(t, u, hitPos);
}

// 当たり判定の寿命に関する更新処理を行う関数
int BaseCollision2DManager::UpdateCollisionLife()
{
    // 今回のループで確認する当たり判定
    BaseCollision2D *current = this->mpFirstBaseCollision2D;

    // 次のループで確認する当たり判定
    BaseCollision2D *next = nullptr;

    // 作業用変数
    BaseCollision *listPrev = nullptr;
    BaseCollision *listNext = nullptr;
    BaseCollision2D *worldPrev = nullptr;
    BaseCollision2D *worldNext = nullptr;

    // ワールドに登録されている全ての当たり判定を確認するif文
    while (current != nullptr)
    {
        // 次のループで使用する当たり判定を取得しておく
        next = current->GetNextWorld();

        // 今回のループで使用する当たり判定の寿命の処理を進める
        current->UpdateLife();

        // 寿命が来たら処理をする
        if (current->GetDeleteFlag())
        {
            // リストの孤立処理をしておく
            listPrev = current->GetPrevList();
            listNext = current->GetNextList();
            worldPrev = current->GetPrevWorld();
            worldNext = current->GetNextWorld();
            if (listPrev != nullptr)
            {
                listPrev->SetNextList(listNext);
            }
            if (listNext != nullptr)
            {
                listNext->SetPrevList(listPrev);
            }
            if (worldPrev != nullptr)
            {
                worldPrev->SetNextWorld(worldNext);
            }
            if (worldNext != nullptr)
            {
                worldNext->SetPrevWorld(worldPrev);
            }
            current->SetPrevList(nullptr);
            current->SetNextList(nullptr);
            current->SetPrevWorld(nullptr);
            current->SetNextWorld(nullptr);

            // 当たり判定を削除する
            delete current;
        }

        // 次の当たり判定に移る
        current = next;
    }

    // 関数が正常終了したことを返す
    return 0;
}

// 
int BaseCollision2DManager::SelectCornerEdge(
    const CollisionCheckResult2D &edgeResult0,
    const CollisionCheckResult2D &edgeResult1,
    const VECTOR2D &relativeMoveVec)
{
    VECTOR2D normal0 = edgeResult0.mvRepulsionVecA;
    VECTOR2D normal1 = edgeResult1.mvRepulsionVecA;

    normal0.Normalize();
    normal1.Normalize();

    // 移動方向と法線の内積。
    // 負の値が大きいほど、移動方向に対して正面から受け止める辺。
    const float dot0 = VECTOR2D::Dot(relativeMoveVec, normal0);
    const float dot1 = VECTOR2D::Dot(relativeMoveVec, normal1);

    if (dot0 < dot1)
    {
        return 0;
    }

    if (dot1 < dot0)
    {
        return 1;
    }

    // 同じ場合は辺番号が小さい方を選択するなど、
    // 常に同じ結果になるようにする。
    return 0;
}

BaseCollision2DManager::BaseCollision2DManager() :
    mpFirstBaseCollision2D(nullptr)
{

}

BaseCollision2DManager::~BaseCollision2DManager()
{
    this->IsolateAll();
}

int BaseCollision2DManager::Initialize()
{
    BaseCollision2D *current = mpFirstBaseCollision2D;
    while (current != nullptr)
    {
        current = current->GetNextWorld();
    }

    return 0;
}

int BaseCollision2DManager::Finalize()
{
    BaseCollision2D *current = mpFirstBaseCollision2D;
    while (current != nullptr)
    {
        current = current->GetNextWorld();
    }

    return 0;
}

// ワールドに登録されている当たり判定とワールドに登録されている当たり判定を移動込みの総当たりで計算し、スライド移動も行う関数(カリング処理 : 移動ベクトル、基準円)
int BaseCollision2DManager::CheckHitAllMove()
{
    if (this->mpFirstBaseCollision2D == nullptr ||
        this->mpFirstBaseCollision2D->GetNextWorld() == nullptr)
    {
        return 0;
    }
    // 前者の当たり判定を取得する
    for (BaseCollision2D *current = this->mpFirstBaseCollision2D; current != nullptr; current = current->GetNextWorld())
    {
        // 
        current->mnHitCount = 0;
    }

    // 関数の返り値を保持するための変数
    CollisionCheckResult2D temp;

    // 前者の当たり判定を取得する
    for (int i = 0; i < 2; i++)
    {
        for (BaseCollision2D *current = this->mpFirstBaseCollision2D; current != nullptr; current = current->GetNextWorld())
        {
            // 後者の当たり判定を取得する
            for (BaseCollision2D *target = current->GetNextWorld(); target != nullptr; target = target->GetNextWorld())
            {
                // 二つの当たり判定の削除フラグと有効フラグを確認し、問題があった場合は処理を飛ばす
                if (current->GetDeleteFlag() ||
                    target->GetDeleteFlag() ||
                    current->GetActiveFlag() == false ||
                    target->GetActiveFlag() == false)
                {
                    continue;
                }

                // 円のカリングを含めた当たり細かい判定の計算を行う
                temp = BaseCollision2DManager::CheckHitCollision2DToCollision2D(current, target);

                // 当たっている場合は処理を行う
                if (0 <= temp.mnResultParam)
                {
                    // 二つの当たり判定のスライド移動を行う
                    BaseCollision2DManager::CollisionSlide(temp, current, target);

                    // 
                    current->mnHitCount++;

                    // 
                    target->mnHitCount++;

                    // 
                    VECTOR2D zeroVec;

                    // 
                    if (current->mnHitCount == 2)
                    {
                        // 
                        current->GetMyObject2D()->SetMoveVec(zeroVec);

                        // 
                        current->GetMyObject()->GetBaseCollisionList()->SetCollisionMoveVec(CollisionDimension_2D, &zeroVec);
                    }
                    // 
                    if (target->mnHitCount == 2)
                    {
                        // 
                        target->GetMyObject2D()->SetMoveVec(zeroVec);

                        // 
                        target->GetMyObject()->GetBaseCollisionList()->SetCollisionMoveVec(CollisionDimension_2D, &zeroVec);
                    }

                    // 二つの当たり判定に、衝突したことを知らせる
                    current->HitOnCollision(target);
                    target->HitOnCollision(current);
                }
            }
        }
    }

    // 当たり判定の寿命に関する処理を行う
    this->UpdateCollisionLife();

    // 関数が正常終了したことを知らせる
    return 0;
}

// 
int BaseCollision2DManager::SearchTag(CollisionTag tag, std::vector<BaseCollision2D *> &out)
{
    // 
    uint32_t count = 0;

    // 
    BaseCollision2D *current = this->mpFirstBaseCollision2D;
    while (current != nullptr)
    {
        // 
        if (current->GetCollisionTag() == tag)
        {
            // 
            count++;
        }

        // 
        current = current->GetNextWorld();
    }
    
    // 
    out.resize(count, nullptr);

    // 
    count = 0;

    // 
    current = this->mpFirstBaseCollision2D;

    // 
    while (current != nullptr)
    {
        // 
        if (out.size() <= count)
        {
            // 
            break;
        }

        // 
        if (current->GetCollisionTag() == tag)
        {
            // 
            out[count] = current;

            // 
            count++;
        }

        // 
        current = current->GetNextWorld();
    }

    // 
    out;

    // 
    return 0;
}

// 謎の当たり判定と謎の当たり判定の内外判定と衝突判定を行う関数
CollisionCheckResult2D BaseCollision2DManager::CheckHitCollision2DToCollision2D(BaseCollision2D *collision2DA, BaseCollision2D *collision2DB)
{
    // 返り値を保持する変数
    CollisionCheckResult2D temp = GetCollisionCheckResult2DZero();

    // 片方でもnullptrだった場合は計算ができないので
    if (collision2DA == nullptr || collision2DB == nullptr)
    {
        return temp;
    }

    // CollisionTypeの数値が低い方の当たり判定
    BaseCollision2D *checkCollisionA = nullptr;

    // CollisionTypeの数値が高い方の当たり判定
    BaseCollision2D *checkCollisionB = nullptr;

    // AとBを入れ替えて計算しているか
    bool swapFlag = false;

    // 緻密な当たり判定の計算に使用する場合は、ColiisionTypeの数値の順番通りに二つの当たり判定を渡してください
    // (floatで処理するため、浮動小数点数特有の『誤差』の影響を受けやすく、内部のfloat同士の計算結果がブレることがあるため)
    if (collision2DB->GetCollisionType() < collision2DA->GetCollisionType())
    {
        checkCollisionA = collision2DB;
        checkCollisionB = collision2DA;
        swapFlag = true;
    }
    else
    {
        checkCollisionA = collision2DA;
        checkCollisionB = collision2DB;
        swapFlag = false;
    }

    // カリング処理をまとめて行い、飛ばすべきでない場合のみ詳しい計算を行う
    if (BaseCollision2DManager::CheckCulling(checkCollisionA, checkCollisionB) == false)
    {
        // まず片方のコリジョンタイプにあった関数に飛ぶ
        switch (checkCollisionA->GetCollisionType())
        {
        case CollisionType::CollisionType_Point2D:
            temp = BaseCollision2DManager::CheckHitPoint2DToCollision2D(static_cast<Point2D *>(checkCollisionA), checkCollisionB);
            break;
        case CollisionType::CollisionType_Circle2D:
            temp = BaseCollision2DManager::CheckHitCircle2DToCollision2D(static_cast<Circle2D *>(checkCollisionA), checkCollisionB);
            break;
        case CollisionType::CollisionType_Capsule2D:
            temp = BaseCollision2DManager::CheckHitCapsule2DToCollision2D(static_cast<Capsule2D *>(checkCollisionA), checkCollisionB);
            break;
        case CollisionType::CollisionType_Triangle2D:
            temp = BaseCollision2DManager::CheckHitTriangle2DToCollision2D(static_cast<Triangle2D *>(checkCollisionA), checkCollisionB);
            break;
        case CollisionType::CollisionType_Quadrangle2D:
            temp = BaseCollision2DManager::CheckHitQuadrangle2DToCollision2D(static_cast<Quadrangle2D *>(checkCollisionA), checkCollisionB);
            break;
        case CollisionType::CollisionType_Ray2D:
            temp = BaseCollision2DManager::CheckHitRay2DToCollision2D(static_cast<Ray2D *>(checkCollisionA), checkCollisionB);
            break;
        default:
            break;
        }
    }

    // 
    if (0 <= temp.mnResultParam && swapFlag)
    {
        // 
        temp = GetCollisionCheckResult2D(
            temp.mpCollisionB,
            temp.mpCollisionA,
            temp.mnResultParam,
            temp.mvRepulsionVecB,
            temp.mvRepulsionVecA,
            temp.mvHitPos,
            temp.mvFloatBox);
    }

    // 計算結果を返す
    return temp;
}

/* 線形リスト関連の関数 */
int BaseCollision2DManager::Add(BaseCollision2D *target)
{
    // そもそもtargetがnullの場合
    if (target == nullptr)
    {
        return -1;
    }
    // mpCollisionすらない場合
    if (mpFirstBaseCollision2D == nullptr)
    {
        mpFirstBaseCollision2D = target;
        return 0;
    }

    BaseCollision2D *current = mpFirstBaseCollision2D;
    // 最後尾を見つける
    while (current->GetNextWorld() != nullptr)
    {
        current = current->GetNextWorld();
    }

    return ConnectTarget(current, target, nullptr);
}

int BaseCollision2DManager::ConnectTarget(BaseCollision2D *prev, BaseCollision2D *target, BaseCollision2D *next)
{
    if (prev != nullptr)
    {
        prev->SetNextWorld(target);
    }
    if (next != nullptr)
    {
        next->SetPrevWorld(target);
    }
    if (next == mpFirstBaseCollision2D)
    {
        mpFirstBaseCollision2D = target;
    }

    target->SetPrevWorld(prev);
    target->SetNextWorld(next);

    return 0;
}

int BaseCollision2DManager::IsolateTarget(BaseCollision2D *target)
{
    // 
    bool hit = false;
    for (BaseCollision2D *current = this->mpFirstBaseCollision2D; current != nullptr; current = current->GetNextWorld())
    {
        // 
        if (current == target)
        {
            // 
            hit = true;
        }
    }

    // 
    if (!hit)
    {
        // 
        return -1;
    }

    // 作業用変数を用意
    BaseCollision2D *prev = target->GetPrevWorld();
    BaseCollision2D *next = target->GetNextWorld();

    if (prev != nullptr)
    {
        // prevがnullでなかったら、nextがnullだろうとセットする。(targetが最後尾のコリジョンの場合など)
        prev->SetNextWorld(next);
    }
    if (next != nullptr)
    {
        // nextがnullでなかったら、prevがnullだろうとセットする。(target == mpCollisionの場合など)
        next->SetPrevWorld(prev);
    }

    if (target == mpFirstBaseCollision2D)
    {
        // 自分が最初のコリジョンだった場合は一つ後のコリジョンを最初のコリジョンとする
        mpFirstBaseCollision2D = next;
    }

    target->SetPrevWorld(nullptr);
    target->SetNextWorld(nullptr);

    return 0;
}

int BaseCollision2DManager::IsolateAll()
{
    if (this->mpFirstBaseCollision2D == nullptr)
    {
        return 0;
    }

    BaseCollision2D *target = mpFirstBaseCollision2D;
    BaseCollision2D *next = target->GetNextWorld();

    while (true)
    {
        IsolateTarget(target);
        target = next;
        if (target == nullptr)
        {
            break;
        }
        else
        {
            next = target->GetNextWorld();
        }
    }

    return 0;
}