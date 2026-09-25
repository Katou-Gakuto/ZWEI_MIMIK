#pragma once

#include "BaseScene.h"

#include "../Z_Except/CursorMoveSupporter.h"

class Player;
class LightAreaManager;

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
    virtual int MapCreate() = 0;

private:
    // 
    bool mbPouse;

    // 
    int mnCursorPos;

    // 
    static CursorMoveData smdMoveData;
};