#include "Quadrangle2D.h"

#include "CollisionCheckResult.h"
#include "BaseCollisionList.h"
#include "../A_GameObject/GameObject2D.h"
#include "../Y_Tool/MyFunctions.h"

Quadrangle2D::Quadrangle2D() : 
    mvVertexPos(),
    BaseCollision2D(nullptr, CollisionType::CollisionType_Quadrangle2D, CollisionTag_Checker, CollisionNorm_Out, true, false, 0.0f)
{

}

Quadrangle2D::Quadrangle2D(
    const VECTOR2D &pos0, const VECTOR2D &pos1, const VECTOR2D &pos2, const VECTOR2D &pos3,
    GameObject *myObject, CollisionTag tag, CollisionNorm normNum,
    bool penetrate, bool hitMove, float moveLate) :
    mvVertexPos(),
    BaseCollision2D(myObject, CollisionType::CollisionType_Quadrangle2D, tag, normNum, penetrate, hitMove, moveLate)
{
    // 頂点の座標を設定する
    this->mvVertexPos[0] = pos0;
    this->mvVertexPos[1] = pos1;
    this->mvVertexPos[2] = pos2;
    this->mvVertexPos[3] = pos3;
}

Quadrangle2D::~Quadrangle2D()
{

}

int Quadrangle2D::Draw(const Material2D &color)
{
    return 0;
}

int Quadrangle2D::SetPosToMoveVec()
{
    VECTOR2D moveVec = this->GetMoveVec();
    if (moveVec != VECTOR2D::GetZero())
    {
        this->mvVertexPos[0] += moveVec;
        this->mvVertexPos[1] += moveVec;
        this->mvVertexPos[2] += moveVec;
        this->mvVertexPos[3] += moveVec;
        this->SetBasePosUpdateFlag(true);

        this->SetMoveVec(VECTOR2D::GetZero());
    }

    return 0;
}

int Quadrangle2D::SlideMove(const CollisionCheckResult2D &result, float moveLate)
{
        if (this == result.mpCollisionA)
        {
            VECTOR2D myMoveVec = this->GetMoveVec();
            if (result.mpCollisionB->GetCollisionType() == CollisionType::CollisionType_Circle2D)
            {
                VECTOR2D sideNormVec = (result.mvRepulsionVecA).Normalize();
                if (1.0f < moveLate)
                {
                    // 自分じゃない方の当たり判定の移動ベクトルを取得する
                    VECTOR2D targetMoveVec = static_cast<Quadrangle2D *>(result.mpCollisionB)->GetMoveVec();

                    // スライドの進行ベクトルを取得
                    VECTOR2D slideVec = VECTOR2D::GetSlide(myMoveVec, sideNormVec);

                    // 現在の移動の進行ベクトルにスライドに進行ベクトルと、相手の移動ベクトルを加えて、新しい移動の進行ベクトルを取得する
                    VECTOR2D newMoveVec = myMoveVec + slideVec + (targetMoveVec * (moveLate - 1.0f));

                    // 自身の移動ベクトルを更新する
                    this->SetMoveVec(newMoveVec);
                    if (this->GetMyObject2D() != nullptr)
                    {
                        // オブジェクトの移動ベクトルを更新する
                        this->GetMyObject2D()->SetMoveVec(newMoveVec);

                        // オブジェクトの当たり判定全ての移動ベクトルを更新する
                        this->GetMyObject2D()->GetBaseCollisionList()->SetCollisionMoveVec(CollisionDimension_2D, &newMoveVec);
                    }
                }
                else
                {
                    // 壁ずり移動の進行ベクトル保持する変数
                    VECTOR2D slideVec = VECTOR2D::GetSlide(myMoveVec, sideNormVec);

                    // 現在の移動の進行ベクトルから壁の法線成分を抜いた新しい進行ベクトルを取得する
                    VECTOR2D newMoveVec = myMoveVec + (slideVec * moveLate);

                    // 自身の移動ベクトルを更新する
                    this->SetMoveVec(newMoveVec);
                    if (this->GetMyObject2D() != nullptr)
                    {
                        // オブジェクトの移動ベクトルを更新する
                        this->GetMyObject2D()->SetMoveVec(newMoveVec);

                        // オブジェクトの当たり判定全ての移動ベクトルを更新する
                        this->GetMyObject2D()->GetBaseCollisionList()->SetCollisionMoveVec(CollisionDimension_2D, &newMoveVec);
                    }
                }
            }
            else if (result.mpCollisionB->GetCollisionType() == CollisionType::CollisionType_Quadrangle2D)
            {
                VECTOR2D sideNormVec = (result.mvRepulsionVecA).Normalize();
                if (1.0f < moveLate)
                {
                    // 自分じゃない方の当たり判定の移動ベクトルを取得する
                    VECTOR2D targetMoveVec = static_cast<Quadrangle2D *>(result.mpCollisionB)->GetMoveVec();

                    // スライドの進行ベクトルを取得
                    VECTOR2D slideVec = VECTOR2D::GetSlide(myMoveVec, sideNormVec);

                    // 現在の移動の進行ベクトルにスライドに進行ベクトルと、相手の移動ベクトルを加えて、新しい移動の進行ベクトルを取得する
                    VECTOR2D newMoveVec = myMoveVec + slideVec + (targetMoveVec * (moveLate - 1.0f));

                    // 自身の移動ベクトルを更新する
                    this->SetMoveVec(newMoveVec);
                    if (this->GetMyObject2D() != nullptr)
                    {
                        // オブジェクトの移動ベクトルを更新する
                        this->GetMyObject2D()->SetMoveVec(newMoveVec);

                        // オブジェクトの当たり判定全ての移動ベクトルを更新する
                        this->GetMyObject2D()->GetBaseCollisionList()->SetCollisionMoveVec(CollisionDimension_2D, &newMoveVec);
                    }
                }
                else
                {
                    // 壁ずり移動の進行ベクトル保持する変数
                    VECTOR2D slideVec = VECTOR2D::GetSlide(myMoveVec, sideNormVec);

                    // 現在の移動の進行ベクトルから壁の法線成分を抜いた新しい進行ベクトルを取得する
                    VECTOR2D newMoveVec = myMoveVec + (slideVec * moveLate);

                    // 自身の移動ベクトルを更新する
                    this->SetMoveVec(newMoveVec);
                    if (this->GetMyObject2D() != nullptr)
                    {
                        // オブジェクトの移動ベクトルを更新する
                        this->GetMyObject2D()->SetMoveVec(newMoveVec);

                        // オブジェクトの当たり判定全ての移動ベクトルを更新する
                        this->GetMyObject2D()->GetBaseCollisionList()->SetCollisionMoveVec(CollisionDimension_2D, &newMoveVec);
                    }
                }
            }
        }
        else if (this == result.mpCollisionB)
        {
            VECTOR2D myMoveVec = this->GetMoveVec();
            if (result.mpCollisionA->GetCollisionType() == CollisionType::CollisionType_Circle2D)
            {
                VECTOR2D sideNormVec = result.mvRepulsionVecB.Normalize();

                if (1.0f < moveLate)
                {
                    // 自分じゃない方の当たり判定の移動ベクトルを取得する
                    VECTOR2D targetMoveVec = static_cast<Quadrangle2D *>(result.mpCollisionA)->GetMoveVec();

                    // スライドの進行ベクトルを取得
                    VECTOR2D slideVec = VECTOR2D::GetSlide(myMoveVec, sideNormVec);

                    // 現在の移動の進行ベクトルにスライドに進行ベクトルと、相手の移動ベクトルを加えて、新しい移動の進行ベクトルを取得する
                    VECTOR2D newMoveVec = myMoveVec + slideVec + (targetMoveVec * (moveLate - 1.0f));

                    // 自身の移動ベクトルを更新する
                    this->SetMoveVec(newMoveVec);
                    if (this->GetMyObject2D() != nullptr)
                    {
                        // オブジェクトの移動ベクトルを更新する
                        this->GetMyObject2D()->SetMoveVec(newMoveVec);

                        // オブジェクトの当たり判定全ての移動ベクトルを更新する
                        this->GetMyObject2D()->GetBaseCollisionList()->SetCollisionMoveVec(CollisionDimension_2D, &newMoveVec);
                    }
                }
                else
                {
                    // 壁ずり移動の進行ベクトル保持する変数
                    VECTOR2D slideVec = VECTOR2D::GetSlide(myMoveVec, sideNormVec);

                    // 現在の移動の進行ベクトルから壁の法線成分を抜いた新しい進行ベクトルを取得する
                    VECTOR2D newMoveVec = myMoveVec + (slideVec * moveLate);

                    // 自身の移動ベクトルを更新する
                    this->SetMoveVec(newMoveVec);
                    if (this->GetMyObject2D() != nullptr)
                    {
                        // オブジェクトの移動ベクトルを更新する
                        this->GetMyObject2D()->SetMoveVec(newMoveVec);

                        // オブジェクトの当たり判定全ての移動ベクトルを更新する
                        this->GetMyObject2D()->GetBaseCollisionList()->SetCollisionMoveVec(CollisionDimension_2D, &newMoveVec);
                    }
                }
            }
            if (result.mpCollisionA->GetCollisionType() == CollisionType::CollisionType_Quadrangle2D)
            {
                VECTOR2D slideNormVec = result.mvRepulsionVecB.Normalize();

                if (1.0f < moveLate)
                {
                    // 自分じゃない方の当たり判定の移動ベクトルを取得する
                    VECTOR2D targetMoveVec = static_cast<Quadrangle2D *>(result.mpCollisionA)->GetMoveVec();

                    // スライドの進行ベクトルを取得
                    VECTOR2D slideVec = VECTOR2D::GetSlide(myMoveVec, slideNormVec);

                    // 現在の移動の進行ベクトルにスライドに進行ベクトルと、相手の移動ベクトルを加えて、新しい移動の進行ベクトルを取得する
                    VECTOR2D newMoveVec = myMoveVec + slideVec +(targetMoveVec * (moveLate - 1.0f));

                    // 自身の移動ベクトルを更新する
                    this->SetMoveVec(newMoveVec);
                    if (this->GetMyObject2D() != nullptr)
                    {
                        // オブジェクトの移動ベクトルを更新する
                        this->GetMyObject2D()->SetMoveVec(newMoveVec);

                        // オブジェクトの当たり判定全ての移動ベクトルを更新する
                        this->GetMyObject2D()->GetBaseCollisionList()->SetCollisionMoveVec(CollisionDimension_2D, &newMoveVec);
                    }
                }
                else
                {
                    // 壁ずり移動の進行ベクトル保持する変数
                    VECTOR2D slideVec = VECTOR2D::GetSlide(myMoveVec, slideNormVec);

                    // 現在の移動の進行ベクトルから壁の法線成分を抜いた新しい進行ベクトルを取得する
                    VECTOR2D newMoveVec = myMoveVec + (slideVec * moveLate);

                    // 自身の移動ベクトルを更新する
                    this->SetMoveVec(newMoveVec);
                    if (this->GetMyObject2D() != nullptr)
                    {
                        // オブジェクトの移動ベクトルを更新する
                        this->GetMyObject2D()->SetMoveVec(newMoveVec);

                        // オブジェクトの当たり判定全ての移動ベクトルを更新する
                        this->GetMyObject2D()->GetBaseCollisionList()->SetCollisionMoveVec(CollisionDimension_2D, &newMoveVec);
                    }
                }
            }
        }

    return 0;
}

int Quadrangle2D::SetBaseParamMySelf()
{
    // 値が変わっている可能性がある場合のみ処理を行う
    if (this->GetBasePosUpdateFlag() || this->GetBaseRadiusUpdateFlag())
    {
        VECTOR2D basePos = VECTOR2D::GetZero();
        VECTOR2D maxDistance = this->mvVertexPos[1] - this->mvVertexPos[0];

        VECTOR2D currentDistance = VECTOR2D::GetZero();

        for (int i = 0; i < 4; i++)
        {
            for (int j = i + 1; j < 4; j++)
            {
                if (i == 0 && j == 1)
                {
                    continue;
                }

                if (i == j)
                {
                    continue;
                }

                // 現在のベクトルとそのベクトルの大きさを取得する
                currentDistance = this->mvVertexPos[j] - this->mvVertexPos[i];

                // 今回のベクトルの大きさが前回のベクトルよりも大きかったら更新処理を行う
                if (maxDistance.MagnitudeNoSqrt() < currentDistance.MagnitudeNoSqrt())
                {
                    // 
                    maxDistance = currentDistance;

                    // この図形がすっぽり埋まる円の中心点を取得する
                    basePos = VECTOR2D::GetLerpPos(this->mvVertexPos[i], this->mvVertexPos[j], 0.5f);
                }
            }
        }

        // 計算結果をBaseParamに反映する
        this->SetBasePos(basePos);
        this->SetBaseRadius(maxDistance.Magnitude());

        // フラグを整える
        this->SetBasePosUpdateFlag(false);
        this->SetBaseRadiusUpdateFlag(false);
    }

    return 0;
}

int Quadrangle2D::GetAABB(AABB2D &out)
{
    float minX = this->mvVertexPos[0].GetX();
    float minY = this->mvVertexPos[0].GetY();
    float maxX = this->mvVertexPos[0].GetX();
    float maxY = this->mvVertexPos[0].GetY();
    for (int i = 0 + 1; i < 4; i++)
    {
        if (this->mvVertexPos[i].GetX() < minX)
        {
            minX = this->mvVertexPos[i].GetX();
        }
        else if (maxX < this->mvVertexPos[i].GetX())
        {
            maxX = this->mvVertexPos[i].GetX();
        }
        if (this->mvVertexPos[i].GetY() < minY)
        {
            minY = this->mvVertexPos[i].GetY();
        }
        else if (maxY < this->mvVertexPos[i].GetY())
        {
            maxY = this->mvVertexPos[i].GetY();
        }
    }
    out.mvMinPos.SetXY(minX, minY);
    out.mvMaxPos.SetXY(maxX, maxY);
    out.mvMoveVec = this->GetMoveVec();
    return 0;
}

void Quadrangle2D::SetShapeParameter(const VECTOR2D &pos0, const VECTOR2D &pos1, const VECTOR2D &pos2, const VECTOR2D &pos3)
{
    // 頂点の座標を設定する
    this->mvVertexPos[0] = pos0;
    this->mvVertexPos[1] = pos1;
    this->mvVertexPos[2] = pos2;
    this->mvVertexPos[3] = pos3;

    // 値の変更があったことを記憶しておく
    this->SetBasePosUpdateFlag(true);
}

const VECTOR2D &Quadrangle2D::GetVertexPos(int index) const
{
    // 
    return this->mvVertexPos[index];
}

float Quadrangle2D::GetSignedArea() const
{
    float area = 0.0f;

    for (int i = 0; i < 4; ++i)
    {
        const VECTOR2D &current = this->mvVertexPos[i];
        const VECTOR2D &next = this->mvVertexPos[(i + 1) % 4];

        area += current.GetX() * next.GetY() - current.GetY() * next.GetX();
    }

    return area;
}

VECTOR2D Quadrangle2D::GetQuadrangleContactPoint(
    const std::vector<VECTOR2D> &aVertices,
    const std::vector<VECTOR2D> &bVertices,
    const VECTOR2D &normal)
{
    const float EPSILON = 0.00001f;

    /*
        normal:
            A → B の方向

        A側は normal 方向の最大位置
        B側は normal 方向の最小位置
    */

    float aMax = -FLT_MAX;
    float bMin = FLT_MAX;

    for (size_t i = 0; i < aVertices.size(); ++i)
    {
        const float value = VECTOR2D::Dot(aVertices[i], normal);

        if (value > aMax)
        {
            aMax = value;
        }
    }

    for (size_t i = 0; i < bVertices.size(); ++i)
    {
        const float value = VECTOR2D::Dot(bVertices[i], normal);

        if (value < bMin)
        {
            bMin = value;
        }
    }

    /*
        接触面上に存在する頂点を取得する。
    */
    std::vector<VECTOR2D> aSupport;
    std::vector<VECTOR2D> bSupport;

    for (size_t i = 0; i < aVertices.size(); ++i)
    {
        const float value =
            VECTOR2D::Dot(aVertices[i], normal);

        if (std::fabs(value - aMax) <= EPSILON)
        {
            aSupport.push_back(aVertices[i]);
        }
    }

    for (size_t i = 0; i < bVertices.size(); ++i)
    {
        const float value =
            VECTOR2D::Dot(bVertices[i], normal);

        if (std::fabs(value - bMin) <= EPSILON)
        {
            bSupport.push_back(bVertices[i]);
        }
    }

    /*
        -------------------------
        角 × 角
        -------------------------
    */
    if (aSupport.size() == 1 &&
        bSupport.size() == 1)
    {
        /*
            理想的には同一点。
            数値誤差があるため2点の中間を取る。
        */
        return (aSupport[0] + bSupport[0]) * 0.5f;
    }

    /*
        接線方向。
        normal に垂直な方向。
    */
    VECTOR2D tangent(-normal.GetY(), normal.GetX());

    /*
        -------------------------
        A側の支持辺を作る
        -------------------------
    */
    float aTangentMin = FLT_MAX;
    float aTangentMax = -FLT_MAX;

    for (size_t i = 0; i < aSupport.size(); ++i)
    {
        const float value = VECTOR2D::Dot(aSupport[i], tangent);

        // 
        aTangentMin = min(aTangentMin, value);

        // 
        aTangentMax = max(aTangentMax, value);
    }

    /*
        -------------------------
        B側の支持辺を作る
        -------------------------
    */
    float bTangentMin = FLT_MAX;
    float bTangentMax = -FLT_MAX;

    for (size_t i = 0; i < bSupport.size(); ++i)
    {
        const float value =
            VECTOR2D::Dot(bSupport[i], tangent);

        bTangentMin = min(bTangentMin, value);
        bTangentMax = max(bTangentMax, value);
    }

    /*
        接触している辺同士の
        接線方向の重なり区間。
    */
    const float contactMin = max(aTangentMin, bTangentMin);

    const float contactMax = min(aTangentMax, bTangentMax);

    /*
        -------------------------
        角 × 辺
        -------------------------
        重なり区間がほぼ一点なら、
        その一点が角の正確な接触位置。
    */
    if (std::fabs(contactMax - contactMin) <= EPSILON)
    {
        const float tangentValue =
            (contactMin + contactMax) * 0.5f;

        /*
            A側の接触面上の点を
            normal方向とtangent方向から再構成する。
        */
        const float normalValue =
            (aMax + bMin) * 0.5f;

        return
            normal * normalValue +
            tangent * tangentValue;
    }

    /*
        -------------------------
        辺 × 辺
        -------------------------
        接触区間が存在するので、
        その区間の中央を接触座標とする。

        重要なのは、この点が
        実際に2つの辺の重なっている区間上に
        存在すること。
    */
    const float tangentValue =
        (contactMin + contactMax) * 0.5f;

    const float normalValue =
        (aMax + bMin) * 0.5f;

    return
        normal * normalValue +
        tangent * tangentValue;
}