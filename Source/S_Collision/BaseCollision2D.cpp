#include "BaseCollision2D.h"

#include "BaseCollision2DManager.h"

#include "../E_Scene/BaseScene.h"
#include "../E_Scene/BaseSceneManager.h"
#include "../Z_Except/Master.h"

BaseCollision2D::BaseCollision2D(
    GameObject *object, CollisionType type, CollisionTag tag, CollisionNorm normNum,
    bool penetrate, bool hitMove, float moveLate) :
    mvBasePos(VECTOR2D::GetZero()),
    mfBaseRadius(0.0f),
    mbBasePosUpdateFlag(true),
    mbBaseRadiusUpdateFlag(true),
    mvMoveVec(VECTOR2D::GetZero()),
    mpPrevWorld(nullptr),
    mpNextWorld(nullptr),
    mbHitMoveLose(false),
    BaseCollision(object, type, tag, normNum, penetrate, hitMove, moveLate)
{

}

BaseCollision2D::~BaseCollision2D()
{

}

int BaseCollision2D::Draw(const Material2D &color)
{
    return 0;
}

int BaseCollision2D::SetPosToMoveVec()
{
    return 0;
}

int BaseCollision2D::SetMoveVec(const void *moveData)
{
    if (moveData != nullptr)
    {
        VECTOR2D *moveVec = (VECTOR2D *)(moveData);
        this->mvMoveVec = *moveVec;
    }
    return 0;
}

int BaseCollision2D::SetNextPos(const void *posData)
{
    if (posData != nullptr)
    {
        VECTOR2D moveVec = *((VECTOR2D *)(posData)) - this->mvBasePos;
        this->mvMoveVec = moveVec;
    }
    return 0;
}

int BaseCollision2D::WorldConnectMySelf()
{
    auto nowScene = Master::mpBaseSceneManager->SearchSceneAuto();

    return nowScene->GetBaseCollision2DManager()->Add(this);
}

int BaseCollision2D::WorldIsolateMySelf()
{
    int resultNum = -1;
    BaseScene *nowScene;
    BaseCollision2DManager *manager = nullptr;
    for (int i = 0; i < SceneTag::ST_Max; i++)
    {
        // 
        nowScene = Master::mpBaseSceneManager->SearchScene(i);
        if (nowScene != nullptr)
        {
            // 
            manager = nowScene->GetBaseCollision2DManager();

            // 
            if (manager != nullptr)
            {
                resultNum = manager->IsolateTarget(this);
                if (resultNum == 0)
                {
                    // 
                    break;
                }
            }
        }

    }

    return resultNum;
}

int BaseCollision2D::SetBaseParamMySelf()
{
    return 0;
}