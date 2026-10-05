#include "Circle2D.h"

#include "../A_GameObject/GameObject2D.h"

#include "BaseCollisionList.h"
#include "Quadrangle2D.h"
#include "Ray2D.h"

Circle2D::Circle2D() :
    BaseCollision2D(nullptr, CollisionType::CollisionType_Circle2D, CollisionTag_Checker, CollisionNorm::CollisionNorm_Out, true, false, 0.0f)
{

}

Circle2D::Circle2D(
    const VECTOR2D &pos, float radiusSqrt, GameObject *myObject, CollisionTag tag, CollisionNorm normNum,
    bool penetrate, bool hitMove, float moveLate) :
    BaseCollision2D(myObject, CollisionType::CollisionType_Circle2D, tag, normNum, penetrate, hitMove, moveLate)
{
    this->SetBasePos(pos);
    this->SetBaseRadiusSqrt(radiusSqrt);
}

Circle2D::~Circle2D()
{

}

int Circle2D::Draw(const Material2D &color)
{
    return 0;
}

int Circle2D::SetPosToMoveVec()
{
    VECTOR2D moveVec = this->GetMoveVec();
    if (moveVec!= VECTOR2D::GetZero())
    {
        this->SetBasePos(this->GetBasePos() + moveVec);

        this->SetMoveVec(VECTOR2D::GetZero());
    }

    return 0;
}

int Circle2D::SlideMove(const CollisionCheckResult2D &result, float moveLate)
{
    if (this == result.mpCollisionA)
    {
        VECTOR2D myMoveVec = this->GetMoveVec();
        if (result.mpCollisionB->GetCollisionType() == CollisionType::CollisionType_Quadrangle2D)
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
        else if (result.mpCollisionB->GetCollisionType() == CollisionType::CollisionType_Ray2D)
        {
            VECTOR2D sideNormVec = (result.mvRepulsionVecA).Normalize();
            if (1.0f < moveLate)
            {
                // 自分じゃない方の当たり判定の移動ベクトルを取得する
                VECTOR2D targetMoveVec = static_cast<Ray2D *>(result.mpCollisionB)->GetMoveVec();

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
        if (result.mpCollisionA->GetCollisionType() == CollisionType::CollisionType_Quadrangle2D)
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
        else if (result.mpCollisionA->GetCollisionType() == CollisionType::CollisionType_Ray2D)
        {
            VECTOR2D sideNormVec = result.mvRepulsionVecB.Normalize();

            if (1.0f < moveLate)
            {
                // 自分じゃない方の当たり判定の移動ベクトルを取得する
                VECTOR2D targetMoveVec = static_cast<Ray2D *>(result.mpCollisionA)->GetMoveVec();

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

int Circle2D::SetBaseParamMySelf()
{
    return 0;
}

int Circle2D::GetAABB(AABB2D &out)
{
    float radiusSqrt = this->GetBaseRadius();
    out.mvMinPos.SetXY(
        this->GetBasePos().GetX() - radiusSqrt,
        this->GetBasePos().GetY() - radiusSqrt);
    out.mvMaxPos.SetXY(
        this->GetBasePos().GetX() + radiusSqrt,
        this->GetBasePos().GetY() + radiusSqrt);
    out.mvMoveVec = this->GetMoveVec();
    return 0;
}

void Circle2D::SetShapeParameter(const VECTOR2D &pos, float radiusNoSqrt)
{
    this->SetBasePos(pos);
    this->SetBaseRadiusNoSqrt(radiusNoSqrt);
}