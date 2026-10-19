#include "BaseSceneManager.h"

#include "BaseScene.h"
#include "TitleScene.h"
#include "OptionScene.h"
#include "StageSelectScene.h"
#include "PuzzleScene.h"
#include "TestScene.h"

#include "../Y_Tool/MyTimer.h"

BaseScene *BaseSceneManager::SearchSceneTag(SceneTag tag)
{
    BaseScene *temp = nullptr;
    for (unsigned char i = 0; i < SceneTag::ST_Max; i++)
    {
        if (this->mpSceneBox[i] != nullptr &&
            this->mpSceneBox[i]->GetTag() == tag)
        {
            temp = this->mpSceneBox[i];
            break;
        }
    }
    return temp;
}

BaseSceneManager::BaseSceneManager() :
    mpSceneBox(),
    mnSceneOld(SceneTag::ST_Max),
    mnSceneNow(SceneTag::ST_Max),
    mnChangeScene(SceneTag::ST_Title),
    mnResreveScene(SceneTag::ST_Max),
    mbFlag(),
    mbNowFinalize(false)
{
    for (unsigned char i = 0; i < SceneTag::ST_Max; i++)
    {
        this->mpSceneBox[i] = nullptr;
    }
}

BaseSceneManager::~BaseSceneManager()
{
    for (unsigned char i = 0; i < SceneTag::ST_Max; i++)
    {
        if (this->mpSceneBox[i] != nullptr)
        {
            this->mpSceneBox[i]->BaseFinalize();
        }
    }
    for (unsigned char i = 0; i < SceneTag::ST_Max; i++)
    {
        if (this->mpSceneBox[i] != nullptr)
        {
            delete this->mpSceneBox[i];
            this->mpSceneBox[i] = nullptr;
        }
    }

    // CSDの削除
    delete (SceneTag *)this->mlUniqueDataList.GetIsolateToNum(CSDN::CSDN_SceneTag_BattleMode);
    delete (bool *)this->mlUniqueDataList.GetIsolateToNum(CSDN::CSDN_bool_PlayerWin);
    delete (TimeParam *)this->mlUniqueDataList.GetIsolateToNum(CSDN::CSDN_TimeParam_GameStartTime);
    delete (unsigned long *)this->mlUniqueDataList.GetIsolateToNum(CSDN::CSDN_unsignedLong_OtherPlayerNum);
}

int BaseSceneManager::Create()
{
    if (this->mbFlag.GetFlag())
    {
        this->mpSceneBox[SceneTag::ST_Title] = new TitleScene();
        this->mpSceneBox[SceneTag::ST_StageSelect] = new StageSelectScene();
        this->mpSceneBox[SceneTag::ST_Option] = new OptionScene();

        this->mpSceneBox[SceneTag::ST_Puzzle1_1] = new PuzzleScene1_1();
        this->mpSceneBox[SceneTag::ST_Puzzle1_2] = new PuzzleScene1_2();
        this->mpSceneBox[SceneTag::ST_Puzzle1_3] = new PuzzleScene1_3();
        this->mpSceneBox[SceneTag::ST_Puzzle1_4] = new PuzzleScene1_4();
        this->mpSceneBox[SceneTag::ST_Puzzle1_5] = new PuzzleScene1_5();
        this->mpSceneBox[SceneTag::ST_Puzzle1_6] = new PuzzleScene1_6();
        this->mpSceneBox[SceneTag::ST_Puzzle1_7] = new PuzzleScene1_7();
        this->mpSceneBox[SceneTag::ST_Puzzle1_8] = new PuzzleScene1_8();
        this->mpSceneBox[SceneTag::ST_Puzzle1_9] = new PuzzleScene1_9();

        this->mpSceneBox[SceneTag::ST_Test] = new TestScene();

        // シーンで共有するデータ
        this->mlUniqueDataList.Add(new SceneTag, CSDN::CSDN_SceneTag_BattleMode);
        this->mlUniqueDataList.Add(new bool, CSDN::CSDN_bool_PlayerWin);
        this->mlUniqueDataList.Add(new TimeParam, CSDN::CSDN_TimeParam_GameStartTime);
        this->mlUniqueDataList.Add(new unsigned long, CSDN::CSDN_unsignedLong_OtherPlayerNum);

        this->mbFlag.CreateComplate();
    }

    return 0;
}

int BaseSceneManager::Initialize()
{
    this->Create();
    return 0;
}

int BaseSceneManager::Finalize()
{
    // 
    for (auto &currentScene : this->mpSceneBox)
    {
        // 
        if (currentScene != nullptr)
        {
            // 
            currentScene->Finalize();
        }
    }
    return 0;
}

int BaseSceneManager::Update()
{
    // シーンを変えるかを記憶しておくフラグ
    bool sceneChangeFlag = this->mnChangeScene != SceneTag::ST_Max;

    // 変更先のシーンが現在のシーンと同じかを記憶しておく
    bool equalChange = this->mnSceneNow == this->mnChangeScene;

    // シーンを変えるなら前回のシーンと現在のシーンを更新する
    if (sceneChangeFlag && !equalChange)
    {
        this->mnSceneOld = this->mnSceneNow;
        this->mnSceneNow = this->mnChangeScene;
    }

    // 今回のシーンを取得する
    BaseScene *sceneNow = this->SearchSceneTag(this->mnSceneNow);

    // 前回のシーンを取得する
    BaseScene *sceneOld = this->SearchSceneTag(this->mnSceneOld);
    
    // 
    if (equalChange)
    {
        // 
        if (sceneNow == nullptr)
        {
            // 
            return -1;
        }

        // 
        this->mbNowFinalize = true;

        // 
        sceneNow->BaseFinalize();

        // 
        this->mbNowFinalize = false;

        // 
        sceneNow->BaseInitialize();

        // 
        sceneNow->Update();

        // 
        this->mnChangeScene = SceneTag::ST_Max;
    }
    else
    {
        // 今回のシーンがnullptrでないなら処理をおコアぬ
        if (sceneNow != nullptr)
        {
            // シーンが変わったタイミングなら今回のシーンにInitializeをかける
            if (sceneChangeFlag)
            {
                sceneNow->BaseInitialize();
            }

            // 今回のシーンに更新をかける
            sceneNow->Update();
        }

        // シーンが変わったタイミングかつ、前回のシーンがnullptrでないなら前回のシーンにFinalizeをかける
        if (sceneChangeFlag && sceneOld != nullptr)
        {
            // シーンを変えたことを書いておく
            this->mnChangeScene = SceneTag::ST_Max;

            // 現在のシーンもnullptrではなく、さらにsceneOldとも違っていた場合
            if (sceneNow != nullptr && sceneNow != sceneOld)
            {
                // 
                this->mbNowFinalize = true;

                // 
                sceneOld->BaseFinalize();

                // 
                this->mbNowFinalize = false;
            }
        }
    }

    // 処理の結果を返す
    return 0;
}

int BaseSceneManager::Draw()
{
    BaseScene *sceneNow = this->SearchSceneTag(this->mnSceneNow);
    if (sceneNow != nullptr)
    {
        sceneNow->Draw();
    }

    return 0;
}

BaseScene *BaseSceneManager::SearchSceneAuto() const
{
    BaseScene *temp = nullptr;
    for (unsigned char i = 0; i < SceneTag::ST_Max; i++)
    {
        if (this->mpSceneBox[i] != nullptr)
        {
            if (this->mbNowFinalize)
            {
                if (this->mpSceneBox[i]->GetTag() == this->mnSceneOld)
                {
                    temp = this->mpSceneBox[i];
                    break;
                }
            }
            else
            {
                if (this->mpSceneBox[i]->GetTag() == this->mnSceneNow)
                {
                    temp = this->mpSceneBox[i];
                    break;
                }
            }

        }
    }
    return temp;
}

BaseScene *BaseSceneManager::SearchSceneNow() const
{
    BaseScene *temp = nullptr;
    for (unsigned char i = 0; i < SceneTag::ST_Max; i++)
    {
        if (this->mpSceneBox[i] != nullptr)
        {
            if (this->mpSceneBox[i]->GetTag() == this->mnSceneNow)
            {
                temp = this->mpSceneBox[i];
                break;
            }
        }
    }
    return temp;
}

BaseScene *BaseSceneManager::SearchSceneOld() const
{
    BaseScene *temp = nullptr;
    for (unsigned char i = 0; i < SceneTag::ST_Max; i++)
    {
        if (this->mpSceneBox[i] != nullptr)
        {
            if (this->mpSceneBox[i]->GetTag() == this->mnSceneOld)
            {
                temp = this->mpSceneBox[i];
                break;
            }
        }
    }
    return temp;
}

BaseScene *BaseSceneManager::SearchScene(int sceneTag)const
{
    // 
    if (sceneTag < 0 ||
        SceneTag::ST_Max <= sceneTag)
    {
        // 
        return nullptr;
    }

    // 
    return this->mpSceneBox[sceneTag];
}


void *BaseSceneManager::GetCSD(CSDN number)
{
    return this->mlUniqueDataList.SearchDataNum(number);
}
