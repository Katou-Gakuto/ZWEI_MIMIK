#include "BaseScene.h"

#include "../A_GameObject/GameObjectManager.h"

BaseScene::BaseScene(SceneTag tag) :
    mnST(tag),
    mbCreateFlag(true),
    mbResetFlag(true),
    mpGameObjectManager(nullptr),
    mpBaseCollision2DManager(nullptr),
    mpBaseCollision3DManager(nullptr)
{
}

BaseScene::~BaseScene()
{
    if (this->mpGameObjectManager != nullptr)
    {
        delete this->mpGameObjectManager;
        this->mpGameObjectManager = nullptr;
    }
}

int BaseScene::BaseInitialize()
{
    // 
    if (this->mbCreateFlag)
    {
        // 
        this->mpGameObjectManager = new GameObjectManager;

        // 
        this->Create();

        // 
        this->mbCreateFlag = false;
    }

    // 
    if (this->mbResetFlag)
    {
        // 
        this->Initialize();

        // 
        this->mbResetFlag = false;
    }

    return 0;
}

int BaseScene::BaseFinalize()
{
    // 
    if (this->mbResetFlag)
    {
        // 
        this->Finalize();
    }

    // 
    return 0;
}
