#pragma once

#include "BaseScene.h"
#include "../Y_Tool/CreateFlag.h"
#include "../Y_Tool/VoidList.h"

#include "FadeData.h"

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

// 
typedef enum SceneChangeAnimPhase : unsigned char
{
    SCAP_ToClose = 0,
    SCAP_Closing,
    SCAP_ToOpen,
    SCAP_Opening,
    SCAP_OpenedWait,
    SCAP_End,
} SCAP;

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
    bool mbToClosingUpdate;
    bool mbClosingUpdate;
    bool mbToOpeningUpdate;
    bool mbOpeningUpdate;
    SceneOpenAnimNumber mnOpeningNumber;
    SceneCloseAnimNumber mnClosingNumber;
    SceneChangeAnimPhase mnSceneChangeAnimPhase;
    uint32_t mnToOpeningFrame;
    uint32_t mnToClosingFrame;
    uint32_t mnOpeningFrame;
    uint32_t mnClosingFrame;
    uint32_t mnOpendWaitFrame;
    VoidList mlUniqueDataList;

    // フェード用画像ハンドル
    int mnBlackFadeHandle;

    // フェードを開けるときの情報
    FadeData mstFadeOpenData;
    // フェードを閉じるときの情報
    FadeData mstFadeCloseData;

    BaseScene *SearchSceneTag(SceneTag tag);

    // シーン遷移(開ける時)のアニメーションを行う関数
    int SceneOpen();

    // シーン遷移(閉じる時)のアニメーションを行う関数
    int SceneClose();

    // シーン遷移(開ける時)のアニメーションが何フレームかかるのかを取得する関数
    uint32_t GetSceneOpenAnimFrame() const;

    // シーン遷移(閉じる時)のアニメーションが何フレームかかるのかを取得する関数
    uint32_t GetSceneCloseAnimFrame() const;

    // シーン遷移アニメーション初期化
    void SceneTransitionInit();

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
        uint32_t toCloseStartFlame,
        bool toCloseUpdate,
        SceneCloseAnimNumber closeAnim,
        bool closingUpdate,
        uint32_t toOpenStartFlame,
        bool toOpenUpdate,
        SceneOpenAnimNumber openAnim,
        bool openingUpdate,
        uint32_t opendWaitFlame);

    void ChangeSceneMySelf();

    void SetResreveScene(
        SceneTag nextSceneTag,
        uint32_t toCloseStartFlame,
        bool toCloseUpdate,
        SceneCloseAnimNumber closeAnim,
        bool closingUpdate,
        uint32_t toOpenStartFlame,
        bool toOpenUpdate,
        SceneOpenAnimNumber openAnim,
        bool openingUpdate,
        uint32_t opendWaitFlame);

    // 指定したシーンが現在のシーンか確認する
    bool CheckNowScene(SceneTag thisScene);

    // 返り値は着目シーンのUpdate()を行うかどうか
    bool UpdateChanging();

    // 
    bool CheckChanging() const;

    // 
    bool CheckToClose() const;

    // 
    bool CheckClosing() const;

    // 
    bool CheckToOpen() const;

    // 
    bool CheckOpening() const;

    // 
    bool CheckOpendWait() const;


    void *GetCSD(CSDN number);
};