#include "BaseSceneManager.h"

#include "BaseScene.h"
#include "TitleScene.h"
#include "OptionScene.h"
#include "CreditScene.h"
#include "StageSelectScene.h"
#include "PuzzleScene1.h"
#include "TestScene.h"

#include "../Y_Tool/MyTimer.h"

#include "Master.h"
#include "ResourceManager.h"
#include "TimeManager.h"

#include "DrawSystem.h"
#include "DxLibDataManager.h"


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

// シーン遷移(開ける時)のアニメーションを行う関数
int BaseSceneManager::SceneOpen()
{
    // 
    int result = 0;

    // 
    switch (this->mnOpeningNumber)
    {
    case SOAN::SOAN_None:
        break;
    case SOAN::SOAN_CurtainUp:
    {
        // 幕が下がっていくがっていく処理
        mstFadeOpenData.elapsedFrame += 1;
        VECTOR2D displaySize =  Master::mpDxLibDataManager->GetStartDisplaySize();
        DRAW_SYSTEM::DrawFadeImage(DRAW_SYSTEM::DRAW_FADE_TYPE_CURTAIN, mnBlackFadeHandle, VECTOR2D(0, -displaySize.GetY() * (mstFadeOpenData.elapsedFrame / mstFadeOpenData.endFrame)));

        if (mstFadeOpenData.elapsedFrame >= mstFadeOpenData.endFrame)
        {
            mstFadeOpenData.IsFade = false;
        }
    }
        break;
    default:
        result = -1;
        break;
    }

    // 
    this->mnOpeningFrame++;

    // 
    return result;
}

// シーン遷移(閉じる時)のアニメーションを行う関数
int BaseSceneManager::SceneClose()
{
    // 
    int result = 0;

    // 
    switch (this->mnClosingNumber)
    {
    case SCAN::SCAN_None:
        break;
    case SCAN::SCAN_CurtainDown:
    {
        // 幕が上がっていく処理
        mstFadeCloseData.elapsedFrame += 1;
        VECTOR2D displaySize =  Master::mpDxLibDataManager->GetStartDisplaySize();
        DRAW_SYSTEM::DrawFadeImage(DRAW_SYSTEM::DRAW_FADE_TYPE_CURTAIN, mnBlackFadeHandle, VECTOR2D(0, -displaySize.GetY()* (1.0f - (mstFadeCloseData.elapsedFrame / mstFadeCloseData.endFrame))));

        if (mstFadeCloseData.elapsedFrame >= mstFadeCloseData.endFrame)
        {
            mstFadeCloseData.IsFade = false;
        }
    }
        break;
    default:
        result = -1;
        break;
    }

    // 
    this->mnClosingFrame++;

    // 
    return result;
}

// シーン遷移(開ける時)のアニメーションが終わったかを確認する関数
bool BaseSceneManager::CheckSceneOpenEnd() const
{
    // 
    bool result = false;

    // 
    switch (this->mnOpeningNumber)
    {
    case SOAN::SOAN_None:
        result = true;
        break;
    case SOAN::SOAN_CurtainUp:
        // 幕が上がり終わったかを確認する
        if (!mstFadeOpenData.IsFade)
        {
            result = true;
        }
        break;
    default:
        result = false;
        break;
    }

    // 
    return result;
}

// シーン遷移(閉じる時)のアニメーションが終わったかを確認する関数
bool BaseSceneManager::CheckSceneCloseEnd() const
{
    // 
    bool result = false;

    // 
    switch (this->mnClosingNumber)
    {
    case SCAN::SCAN_None:
        result = true;
        break;
    case SCAN::SCAN_CurtainDown:
        // 幕が下がり終わったかを確認する
        if (!mstFadeCloseData.IsFade)
        {
            result = true;
        }
        break;
    default:
        result = false;
        break;
    }

    // 
    return result;
}

// シーン遷移アニメーション初期化
void BaseSceneManager::SceneTransitionInit()
{
    mstFadeOpenData.Init(this->mnOpeningNumber);
    mstFadeCloseData.Init(this->mnClosingNumber);
}

BaseSceneManager::BaseSceneManager() :
    mpSceneBox(),
    mnSceneOld(SceneTag::ST_Max),
    mnSceneNow(SceneTag::ST_Title),
    mnChangeScene(SceneTag::ST_Max),
    mnResreveScene(SceneTag::ST_Max),
    mbFlag(),
    mbNowFinalize(false),
    mbOpeningUpdate(false),
    mbClosingUpdate(false),
    mnOpeningNumber(SOAN::SOAN_None),
    mnClosingNumber(SCAN::SCAN_None),
    mnOpeningFrame(0),
    mnClosingFrame(0),
    mlUniqueDataList(),
    mnBlackFadeHandle(-1),
    mstFadeCloseData(30),
    mstFadeOpenData(30)
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
        this->mpSceneBox[SceneTag::ST_Credit] = new CreditScene();

        this->mpSceneBox[SceneTag::ST_Puzzle1_1] = new PuzzleScene1_1();
        this->mpSceneBox[SceneTag::ST_Puzzle1_2] = new PuzzleScene1_2();
        this->mpSceneBox[SceneTag::ST_Puzzle1_3] = new PuzzleScene1_3();
        this->mpSceneBox[SceneTag::ST_Puzzle1_4] = new PuzzleScene1_4();
        this->mpSceneBox[SceneTag::ST_Puzzle1_5] = new PuzzleScene1_5();
        this->mpSceneBox[SceneTag::ST_Puzzle1_6] = new PuzzleScene1_6();
        this->mpSceneBox[SceneTag::ST_Puzzle1_7] = new PuzzleScene1_7();
        this->mpSceneBox[SceneTag::ST_Puzzle1_8] = new PuzzleScene1_8();
        this->mpSceneBox[SceneTag::ST_Puzzle1_9] = new PuzzleScene1_9();
        this->mpSceneBox[SceneTag::ST_Puzzle1_10] = new PuzzleScene1_10();

        this->mpSceneBox[SceneTag::ST_Test] = new TestScene();

        // シーンで共有するデータ
        this->mlUniqueDataList.Add(new SceneTag, CSDN::CSDN_SceneTag_BattleMode);
        this->mlUniqueDataList.Add(new bool, CSDN::CSDN_bool_PlayerWin);
        this->mlUniqueDataList.Add(new TimeParam, CSDN::CSDN_TimeParam_GameStartTime);
        this->mlUniqueDataList.Add(new unsigned long, CSDN::CSDN_unsignedLong_OtherPlayerNum);

        this->mbFlag.CreateComplate();

        // 画像ハンドル取得
        mnBlackFadeHandle = Master::mpResourceManager->LoadGraphics(ResourceManager::msResourceFile + "Fade/BlackCurtain.png");
    }

    return 0;
}

int BaseSceneManager::Initialize()
{
    this->Create();

    // 
    this->SearchSceneNow()->BaseInitialize();

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
    // 今回のシーンを取得する
    BaseScene *sceneNow = nullptr;

    // シーンを変えるかを記憶しておくフラグ
    if (this->mnChangeScene != SceneTag::ST_Max)
    {
        // 
        sceneNow = this->SearchSceneTag(this->mnChangeScene);
        BaseScene *sceneOld = this->SearchSceneTag(this->mnSceneNow);

        // 
        if (this->CheckSceneCloseEnd())
        {
            // 
            this->mnClosingFrame = 0;
            this->mnClosingNumber = SCAN::SCAN_None;
            this->mbClosingUpdate = false;

            // 
            this->mnSceneOld = this->mnSceneNow;
            this->mnSceneNow = this->mnChangeScene;

            // 
            if (sceneOld != nullptr)
            {
                this->mbNowFinalize = true;
                sceneOld->BaseFinalize();
                this->mbNowFinalize = false;
            }

            // 
            sceneNow->BaseInitialize();

            // 
            if (!this->CheckSceneOpenEnd())
            {
                // 
                if (this->mbOpeningUpdate)
                {
                    // 
                    sceneNow->Update();
                }

                // 
                this->mnOpeningFrame++;

                // 
                return 0;
            }
        }

        // シーン遷移が完了したかで処理を変える
        if (this->CheckSceneOpenEnd())
        {
            // 
            this->mnOpeningFrame = 0;
            this->mnOpeningNumber = SOAN::SOAN_None;
            this->mbOpeningUpdate = false;

            // 
            this->mnChangeScene = SceneTag::ST_Max;
        }
        else
        {
            // 
            if (this->mnOpeningFrame == 0)
            {
                // 
                if (this->mbClosingUpdate)
                {
                    // 
                    sceneOld->Update();
                }

                // 
                this->mnClosingFrame++;
            }
            else
            {
                // 
                if (this->mbOpeningUpdate)
                {
                    // 
                    sceneNow->Update();
                }

                // 
                this->mnOpeningFrame++;
            }

            // 
            return 0;
        }
    }

    // 今回のシーンを取得する
    sceneNow = this->SearchSceneTag(this->mnSceneNow);
    if (sceneNow != nullptr)
    {
        // 今回のシーンに更新をかける
        sceneNow->Update();
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

    // 
    if (this->mnChangeScene != SceneTag::ST_Max)
    {
        // 
        if (this->mnOpeningFrame == 0)
        {
            // 
            this->SceneClose();
        }
        else
        {
            // 
            this->SceneOpen();
        }
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

SceneTag BaseSceneManager::GetSneceOld() const
{
    return this->mnSceneOld;
}

void BaseSceneManager::ChangeScene(
    SceneTag nextSceneTag,
    SceneCloseAnimNumber closeAnim,
    bool closingUpdate,
    SceneOpenAnimNumber openAnim,
    bool openingUpdate)
{
    // 
    if (this->mnClosingFrame == 0 &&
        this->mnOpeningFrame == 0)
    {
        this->mnChangeScene = nextSceneTag;
        this->mnClosingNumber = closeAnim;
        this->mbClosingUpdate = closingUpdate;
        this->mnOpeningNumber = openAnim;
        this->mbOpeningUpdate = openingUpdate;
    }

    SceneTransitionInit();
}

void BaseSceneManager::ChangeSceneMySelf()
{
    // 
    if (this->mnClosingFrame == 0 &&
        this->mnOpeningFrame == 0)
    {
        this->mnChangeScene = this->mnResreveScene;

        SceneTransitionInit();
    }
}

void BaseSceneManager::SetResreveScene(
    SceneTag nextSceneTag,
    SceneCloseAnimNumber closeAnim,
    bool closingUpdate,
    SceneOpenAnimNumber openAnim,
    bool openingUpdate)
{
    this->mnResreveScene = nextSceneTag;
    this->mnClosingNumber = closeAnim;
    this->mbClosingUpdate = closingUpdate;
    this->mnOpeningNumber = openAnim;
    this->mbOpeningUpdate = openingUpdate;
}

// 指定したシーンが現在のシーンか確認する
bool BaseSceneManager::CheckNowScene(SceneTag thisScene)
{
    return mnSceneNow == thisScene;
}

void *BaseSceneManager::GetCSD(CSDN number)
{
    return this->mlUniqueDataList.SearchDataNum(number);
}
