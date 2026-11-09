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

// 
typedef enum SceneOpenAnimNumber : unsigned short
{
    SOAN_None = 0,
    SOAN_CurtainUp,
} SOAN;

// 
typedef enum SceneCloseAnimNumber : unsigned short
{
    SCAN_None = 0,
    SCAN_CurtainDown,
} SCAN;

class BaseSceneManager
{
private:
    BaseScene *mpSceneBox[SceneTag::ST_Max];
    SceneTag mnSceneOld;
    SceneTag mnSceneNow;
    SceneTag mnChangeScene;
    SceneTag mnResreveScene;
    CreateFlag mbFlag;
    bool mbNowFinalize;
    bool mbOpeningUpdate;
    bool mbClosingUpdate;
    SceneOpenAnimNumber mnOpeningNumber;
    SceneCloseAnimNumber mnClosingNumber;
    uint32_t mnOpeningFrame;
    uint32_t mnClosingFrame;
    VoidList mlUniqueDataList;

    BaseScene *SearchSceneTag(SceneTag tag);

    // シーン遷移(開ける時)のアニメーションを行う関数
    int SceneOpen();

    // シーン遷移(閉じる時)のアニメーションを行う関数
    int SceneClose();

    // シーン遷移(開ける時)のアニメーションが終わったかを確認する関数
    bool CheckSceneOpenEnd() const;

    // シーン遷移(閉じる時)のアニメーションが終わったかを確認する関数
    bool CheckSceneCloseEnd() const;

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

    SceneTag GetSneceOld() const;

    void ChangeScene(
        SceneTag nextSceneTag,
        SceneCloseAnimNumber closeAnim,
        bool closingUpdate,
        SceneOpenAnimNumber openAnim,
        bool openingUpdate);

    void ChangeSceneMySelf();

    void SetResreveScene(
        SceneTag nextSceneTag,
        SceneCloseAnimNumber closeAnim,
        bool closingUpdate,
        SceneOpenAnimNumber openAnim,
        bool openingUpdate);

    // 指定したシーンが現在のシーンか確認する
    bool CheckNowScene(SceneTag thisScene);

    void *GetCSD(CSDN number);
};