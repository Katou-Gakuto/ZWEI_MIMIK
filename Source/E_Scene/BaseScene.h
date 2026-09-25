#pragma once

class GameObjectManager;
class BaseCollision2DManager;
class BaseCollision3DManager;

enum SceneTag : unsigned char
{
    ST_Title = 0,
    ST_StageSelect,
    ST_Option,

    ST_Test,
    ST_Puzzle1_1,

    ST_Max,
};

class BaseScene
{
private:
    SceneTag mnST;
    bool mbCreateFlag;
    bool mbResetFlag;

protected:
    GameObjectManager *mpGameObjectManager;
    BaseCollision2DManager *mpBaseCollision2DManager;
    BaseCollision3DManager *mpBaseCollision3DManager;

public:
    BaseScene(SceneTag tag);
    virtual ~BaseScene();

    virtual int Create() = 0;
    virtual int Initialize() = 0;
    virtual int Finalize() = 0;
    virtual int Update() = 0;
    virtual int Draw() = 0;

    int BaseInitialize();
    int BaseFinalize();

    SceneTag GetTag() const { return this->mnST; }
    GameObjectManager *GetGameObjectManager() const { return this->mpGameObjectManager; }
    BaseCollision2DManager *GetBaseCollision2DManager() const { return this->mpBaseCollision2DManager; }
    BaseCollision3DManager *GetBaseCollision3DManager() const { return this->mpBaseCollision3DManager; }

    // 
    void OnResetFlag() { this->mbResetFlag = true; }
};