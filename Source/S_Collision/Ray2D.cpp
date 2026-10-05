#include "Ray2D.h"

#include "../A_GameObject/GameObject2D.h"

#include "BaseCollisionList.h"
#include "Circle2D.h"

Ray2D::Ray2D() :
    mvStartPos(VECTOR2D::GetZero()),
    mvEndPos(VECTOR2D::GetZero()),
    BaseCollision2D(nullptr, CollisionType::CollisionType_Ray2D, CollisionTag_Checker, CollisionNorm_Out, true, false, 0.0f)
{

}

Ray2D::Ray2D(
    const VECTOR2D &startPos, const VECTOR2D &endPos,
    GameObject *myObject, CollisionTag tag,
    bool penetrate, bool hitMove, float moveLate) :
    mvStartPos(startPos),
    mvEndPos(endPos),
    BaseCollision2D(myObject, CollisionType::CollisionType_Ray2D, tag, CollisionNorm_Out, penetrate, hitMove, moveLate)
{

}

Ray2D::~Ray2D()
{

}

int Ray2D::Draw(const Material2D &color)
{
    return 0;
}

int Ray2D::SetPosToMoveVec()
{
    VECTOR2D moveVec = this->GetMoveVec();
    if (moveVec != VECTOR2D::GetZero())
    {
        this->mvStartPos = this->mvStartPos + moveVec;
        this->mvEndPos = this->mvEndPos + moveVec;
        this->SetBasePosUpdateFlag(true);

        this->SetMoveVec(VECTOR2D::GetZero());
    }

    return 0;
}

int Ray2D::SlideMove(const CollisionCheckResult2D &result, float moveLate)
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
                VECTOR2D targetMoveVec = static_cast<Circle2D *>(result.mpCollisionB)->GetMoveVec();

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
                VECTOR2D targetMoveVec = static_cast<Circle2D *>(result.mpCollisionA)->GetMoveVec();

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

    return 0;
}

int Ray2D::SetBaseParamMySelf()
{
    // 円の中心座標を更新する必要がある場合のみ処理を行う
    if (this->GetBasePosUpdateFlag())
    {
        // Rayの中心座標を取得する
        VECTOR2D centerPos = VECTOR2D::GetLerpPos(this->mvStartPos, this->mvEndPos, 0.5f);
        this->SetBasePos(centerPos);

        // フラグを整える
        this->SetBasePosUpdateFlag(false);
    }

    // 円の半径を更新する必要がある場合のみ処理を行う
    if (this->GetBaseRadiusUpdateFlag())
    {
        // Rayの長さの半分を取得する
        float radiusNoSqrt = (this->mvEndPos - this->mvStartPos).MagnitudeNoSqrt() * 0.5f;
        this->SetBaseRadiusNoSqrt(radiusNoSqrt);

        // フラグを整える
        this->SetBaseRadiusUpdateFlag(false);
    }

    return 0;
}

int Ray2D::GetAABB(AABB2D &out)
{
    if (this->mvStartPos.GetX() < this->mvEndPos.GetX())
    {
        out.mvMinPos.SetX(this->mvStartPos.GetX());
        out.mvMaxPos.SetX(this->mvEndPos.GetX());
    }
    else
    {
        out.mvMinPos.SetX(this->mvEndPos.GetX());
        out.mvMaxPos.SetX(this->mvStartPos.GetX());
    }
    if (this->mvStartPos.GetY() < this->mvEndPos.GetY())
    {
        out.mvMinPos.SetY(this->mvStartPos.GetY());
        out.mvMaxPos.SetY(this->mvEndPos.GetY());
    }
    else
    {
        out.mvMinPos.SetY(this->mvEndPos.GetY());
        out.mvMaxPos.SetY(this->mvStartPos.GetY());
    }
    out.mvMoveVec = this->GetMoveVec();
    return 0;
}

void Ray2D::SetShapeParameter(const VECTOR2D &startPos, const VECTOR2D &endPos)
{
    this->mvStartPos = startPos;
    this->mvEndPos = endPos;

    // 値の変更があったことを記憶しておく
    this->SetBasePosUpdateFlag(true);
}