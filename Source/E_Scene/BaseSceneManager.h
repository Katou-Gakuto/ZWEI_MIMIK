#pragma once

#include "BaseScene.h"
#include "../Y_Tool/CreateFlag.h"
#include "../Y_Tool/VoidList.h"

typedef enum CrossSceneDataNumber : unsigned long
{
    CSDN_SceneTag_BattleMode = 0,
    CSDN_bool_PlayerWin,
    CSDN_TimeParam_GameStartTime,
    CSDN_unsignedLong_OtherPlayerNum,

} CSDN;

class BaseSceneManager
{
private:
    BaseScene *mpSceneBox[SceneTag::ST_Max];
    SceneTag mnSceneOld;
    SceneTag mnSceneNow;
    SceneTag mnChangeScene;
    SceneTag mnResreveScene;
    CreateFlag mbFlag;
    VoidList mlUniqueDataList;
    bool mbNowFinalize;

    BaseScene *SearchSceneTag(SceneTag tag);

public:
    BaseSceneManager();
    ~BaseSceneManager();

    int Create();
    int Initialize();
    int Finalize();
    int Update();
    int Draw();

    BaseScene *SearchSceneAuto()const;
    BaseScene *SearchSceneNow()const;
    BaseScene *SearchSceneOld()const;

    BaseScene *SearchScene(int sceneTag)const;

    SceneTag GetSneceOld() const { return this->mnSceneOld; }

    void ChangeScene(SceneTag nextSceneTag) { this->mnChangeScene = nextSceneTag; }
    void ChangeSceneMySelf() { this->mnChangeScene = this->mnResreveScene; }
    void SetResreveScene(SceneTag tag) { this->mnResreveScene = tag; }
	bool CheckNowScene(SceneTag thisScene) { return mnSceneNow == thisScene; } // 指定したシーンが現在のシーンか確認する

    void *GetCSD(CSDN number);
};