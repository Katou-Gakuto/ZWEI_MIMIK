#pragma once

#include "BaseScene.h"

#include "../Z_Except/CursorMoveSupporter.h"

#include <cstdint>

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

    // 
    enum ResultMenu
    {
        ResultMenu_NextStage,
        ResultMenu_StageSelect,

        ResultMenu_Max,
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
        VECTOR2D &goalShadowPos) const = 0;

    // 
    virtual uint32_t GetUseLightAreaCount() const = 0;

    // 
    static SceneTag StageNum2SceneTag(unsigned long stageNum);

    // 
    static unsigned long SceneTag2StageNum(SceneTag sceneTag);

    // 
    Player *GetPlayer(int playerNumber)const;


    // 
    GoalObjectController *GetGoal(bool lightSide)const;

    // ポーズ状態を取得する
    bool GetmbPouse() { return mbPouse; }


private:
    // 
    Player *mpPlayerLight;

    // 
    Player *mpPlayerShadow;

    // 
    GoalObjectController *mpGoalLight;

    // 
    GoalObjectController *mpGoalShadow;

	// ポーズ状態かどうか
    bool mbPouse;

    // 
    bool mbGoal;

    // 
    bool mbFailed;

    // 
    int mnPouseCursorPos;

    // 
    int mnResultCursorPos;

    // 
    static CursorMoveData smdMoveData;

    // 
    void CreateAndAddMastObject();

    // 
    void AddMasterObjects();

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
};