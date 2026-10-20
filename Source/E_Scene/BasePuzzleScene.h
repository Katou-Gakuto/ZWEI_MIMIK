#pragma once

#include "BaseScene.h"

#include "../Z_Except/CursorMoveSupporter.h"

class Player;
class GoalObjectController;
class VECTOR2D;

class BasePuzzleScene : public BaseScene
{
private:
    // 
    enum PouseMenu
    {
        PouseMenu_Option = 0,
        PouseMenu_Retry,
        PouseMenu_StageSelect,
        PouseMenu_Title,

        PouseMenu_Max,
    };

public:
    BasePuzzleScene(SceneTag tag);
    virtual ~BasePuzzleScene();

    int Create() override;
    int Initialize() override;
    int Finalize() override;
    int Update() override;
    int Draw() override;

    // 
    virtual int MapCreate(GameObjectManager &objectManager) = 0;

    // 
    virtual void GetMasterObjectsInitPos(
        VECTOR2D &playerLightPos,
        VECTOR2D &playerShadowPos,
        VECTOR2D &goalLightPos,
        VECTOR2D &goalShadowPos) = 0;

    // 
    static SceneTag StageNum2SceneTag(unsigned long stageNum);

    // 
    Player *GetPlayer(int playerNumber)const;


    // 
    GoalObjectController *GetGoal(bool lightSide)const;


private:
    // 
    Player *mpPlayerLight;

    // 
    Player *mpPlayerShadow;

    // 
    GoalObjectController *mpGoalLight;

    // 
    GoalObjectController *mpGoalShadow;

    // 
    bool mbPouse;

    // 
    bool mbGoal;

    // 
    bool mbFailed;

    // 
    int mnCursorPos;

    // 
    static CursorMoveData smdMoveData;

    // 
    void CreateAndAddMastObject();

    // 
    int PouseUpdate();

    // 
    int PouseDraw();

    // 
    int ResultUpdate();

    // 
    int ResultDraw();

    // 
    int FailedUpdate();

    // 
    int FailedDraw();

public:

    // É|Å[ÉYèÛë‘ÇéÊìæÇ∑ÇÈ
    bool GetmbPouse() { return mbPouse; }
};