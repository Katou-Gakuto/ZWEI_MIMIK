#include "BaseSceneManager.h"

#include "BaseScene.h"
#include "TitleScene.h"
#include "OptionScene.h"
#include "CreditScene.h"
#include "StageSelectScene.h"
#include "PuzzleScene1.h"
#include "TestScene.h"

#include "../A_GameObject/GameObjectManager.h"
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
    return result;
}

// シーン遷移(開ける時)のアニメーションが何フレームかかるのかを取得する関数
uint32_t BaseSceneManager::GetSceneOpenAnimFrame() const
{
    // @加藤
    return 0;
}

// シーン遷移(閉じる時)のアニメーションが何フレームかかるのかを取得する関数
uint32_t BaseSceneManager::GetSceneCloseAnimFrame() const
{
    // @加藤
    return 0;
}
/*
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
        if (30 <= this->mnOpeningFrame)
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
        if (29 <= this->mnClosingFrame)
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
*/
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
    mbToClosingUpdate(false),
    mbClosingUpdate(false),
    mbToOpeningUpdate(false),
    mbOpeningUpdate(false),
    mnOpeningNumber(SOAN::SOAN_None),
    mnClosingNumber(SCAN::SCAN_None),
    mnToOpeningFrame(0),
    mnToClosingFrame(0),
    mnOpeningFrame(0),
    mnClosingFrame(0),
    mnOpendWaitFrame(0),
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

    // ピクセルシェーダーを使うための初期化

    //インデックスの設定
    g_Index[0] = 0;
    g_Index[1] = 1;
    g_Index[2] = 2;
    g_Index[3] = 1;
    g_Index[4] = 3;
    g_Index[5] = 2;

    // ピクセルシェーダーを読み込む
    g_PixelShader = LoadPixelShader("SimplePS.cso");
    g_PostPixelShader = LoadPixelShader("PostPS.cso");

    //オフスクリーンバッファの作成
    g_Offscreen = MakeScreen(1920, 1080, FALSE);

    //定数バッファを作ってハンドルを保存する
    g_lightconstbuff = CreateShaderConstantBuffer(sizeof(LightPos));

    //定数バッファの3スロットにg_lightconstbuffをセットする
    SetShaderConstantBuffer(g_lightconstbuff, DX_SHADERTYPE_PIXEL, 3);

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

    // 
    if (this->CheckChanging())
    {
        // Update()を呼ばない場合はそのまま関数を終了する
        if (!this->UpdateChanging())
        {
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

    
    // シェーダーの光源座標更新
    g_lightpos.pos = VGet(980.0f, 540.0f, 0.0f);
    // // シェーダー用定数バッファハンドルの定数バッファのアドレスを取得する
    LightPos *pBuff = (LightPos *)GetBufferShaderConstantBuffer(g_lightconstbuff);
    pBuff->pos.x = g_lightpos.pos.x;
    pBuff->pos.y = g_lightpos.pos.y;
    pBuff->pos.z = 0.0f;
    pBuff->temp = 0.0f;

    // シェーダー用定数バッファハンドルの定数バッファへの変更を適用する
    UpdateShaderConstantBuffer(g_lightconstbuff);
    SetShaderConstantBuffer(g_lightconstbuff, DX_SHADERTYPE_PIXEL, 3);


    // 処理の結果を返す
    return 0;
}

int BaseSceneManager::Draw()
{



    // 
    BaseScene *sceneNow = this->SearchSceneTag(this->mnSceneNow);
    if (sceneNow != nullptr)
    {
        // 
        if (this->mnChangeScene != SceneTag::ST_Max)
        {
            // 応急処置でシーン遷移の間は基本的には全てのモデルをONにする
            sceneNow->GetGameObjectManager()->OnDrawFlag();
        }

        // 
        sceneNow->Draw();
    }

    // レンダリングターゲットをバックバッファに設定
    SetDrawScreen(DX_SCREEN_BACK);
    SetUsePixelShader(g_PixelShader);
    // ポストエフェクト用ピクセルシェーダーをセット
    SetUsePixelShader(g_PostPixelShader);
    // バックバッファへポリゴンを描画
    DrawPS(0.0f, 0.0f, 1000.0f, 500.0f, g_Offscreen);

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
    uint32_t toCloseStartFlame,
    bool toCloseUpdate,
    SceneCloseAnimNumber closeAnim,
    bool closingUpdate,
    uint32_t toOpenStartFlame,
    bool toOpenUpdate,
    SceneOpenAnimNumber openAnim,
    bool openingUpdate,
    uint32_t opendWaitFlame)
{
    // 
    if (!this->CheckChanging())
    {
        this->mnChangeScene = nextSceneTag;
        this->mnToClosingFrame = toCloseStartFlame;
        this->mbToClosingUpdate = toCloseUpdate;
        this->mnClosingNumber = closeAnim;
        this->mbClosingUpdate = closingUpdate;
        this->mnToOpeningFrame = toOpenStartFlame;
        this->mbToOpeningUpdate = toOpenUpdate;
        this->mnOpeningNumber = openAnim;
        this->mbOpeningUpdate = openingUpdate;
        this->mnOpendWaitFrame = opendWaitFlame;

        // 
        this->mnClosingFrame = this->GetSceneCloseAnimFrame();

        // 
        this->mnOpeningFrame = this->GetSceneOpenAnimFrame();

        // 
        this->mnSceneChangeAnimPhase = SCAP::SCAP_ToClose;

        // 
        SceneTransitionInit();
    }
}

void BaseSceneManager::ChangeSceneMySelf()
{
    // 
    if (!this->CheckChanging())
    {
        // 
        this->mnChangeScene = this->mnResreveScene;

        // 
        this->mnClosingFrame = this->GetSceneCloseAnimFrame();

        // 
        this->mnOpeningFrame = this->GetSceneOpenAnimFrame();

        // 
        this->mnSceneChangeAnimPhase = SCAP::SCAP_ToClose;

        // 
        SceneTransitionInit();
    }
}

void BaseSceneManager::SetResreveScene(
    SceneTag nextSceneTag,
    uint32_t toCloseStartFlame,
    bool toCloseUpdate,
    SceneCloseAnimNumber closeAnim,
    bool closingUpdate,
    uint32_t toOpenStartFlame,
    bool toOpenUpdate,
    SceneOpenAnimNumber openAnim,
    bool openingUpdate,
    uint32_t opendWaitFlame)
{
    this->mnResreveScene = nextSceneTag;
    this->mnToClosingFrame = toCloseStartFlame;
    this->mbToClosingUpdate = toCloseUpdate;
    this->mnClosingNumber = closeAnim;
    this->mbClosingUpdate = closingUpdate;
    this->mnToOpeningFrame = toOpenStartFlame;
    this->mbToOpeningUpdate = toOpenUpdate;
    this->mnOpeningNumber = openAnim;
    this->mbOpeningUpdate = openingUpdate;
    this->mnOpendWaitFrame = opendWaitFlame;
}

// 指定したシーンが現在のシーンか確認する
bool BaseSceneManager::CheckNowScene(SceneTag thisScene)
{
    return mnSceneNow == thisScene;
}

// 返り値は着目シーンのUpdate()を行うかどうか
bool BaseSceneManager::UpdateChanging()
{
    // 今回のシーンを取得する
    BaseScene *sceneNow = this->SearchSceneTag(this->mnChangeScene);
    BaseScene *sceneOld = this->SearchSceneTag(this->mnSceneNow);

    // 
    if (this->mnSceneChangeAnimPhase == SCAP::SCAP_ToClose)
    {
        // 
        if (this->mnToClosingFrame == 0)
        {
            // 
            this->mnSceneChangeAnimPhase = SCAP::SCAP_Closing;
        }
        else
        {
            // 
            this->mnToClosingFrame--;

            // 
            return this->mbToClosingUpdate;
        }
    }

    // 
    if (this->mnSceneChangeAnimPhase == SCAP::SCAP_Closing)
    {
        // 
        if (this->mnClosingFrame == 0)
        {
            // 
            this->mnClosingFrame = 0;
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
            this->mnClosingNumber = SCAN::SCAN_None;

            // 
            this->mnSceneChangeAnimPhase = SCAP::SCAP_ToOpen;
        }
        else
        {
            // 
            this->mnClosingFrame--;

            // 
            return this->mbClosingUpdate;
        }
    }

    // 
    if (this->mnSceneChangeAnimPhase == SCAP::SCAP_ToOpen)
    {
        // 
        if (this->mnToOpeningFrame == 0)
        {
            // 
            this->mnSceneChangeAnimPhase = SCAP::SCAP_Opening;
        }
        else
        {
            // 
            this->mnToOpeningFrame--;

            // 
            return this->mbToOpeningUpdate;
        }
    }

    // 
    if (this->mnSceneChangeAnimPhase == SCAP::SCAP_Opening)
    {
        // 
        if (this->mnOpeningFrame == 0)
        {
            // 
            this->mnSceneChangeAnimPhase = SCAP::SCAP_OpenedWait;

            // 
            this->mbOpeningUpdate = false;

            // 
            this->mnOpeningNumber = SOAN::SOAN_None;
        }
        else
        {
            // 
            this->mnOpeningFrame--;

            // 
            return this->mbOpeningUpdate;
        }
    }

    // 
    if (this->mnSceneChangeAnimPhase == SCAP::SCAP_OpenedWait)
    {
        // 
        if (this->mnOpendWaitFrame == 0)
        {
            // 
            this->mnSceneChangeAnimPhase = SCAP::SCAP_End;
        }
        else
        {
            // 
            this->mnOpendWaitFrame--;

            // 
            return false;
        }
    }

    // 
    this->mnChangeScene = SceneTag::ST_Max;

    // 
    return true;
}

// 
bool BaseSceneManager::CheckChanging() const
{
    // 
    return this->mnChangeScene != SceneTag::ST_Max;
}

// 
bool BaseSceneManager::CheckToClose() const
{
    // 
    return this->mnSceneChangeAnimPhase == SCAP::SCAP_ToClose;
}

// 
bool BaseSceneManager::CheckClosing() const
{
    // 
    return this->mnSceneChangeAnimPhase == SCAP::SCAP_Closing;
}

// 
bool BaseSceneManager::CheckToOpen() const
{
    // 
    return this->mnSceneChangeAnimPhase == SCAP::SCAP_ToOpen;
}

// 
bool BaseSceneManager::CheckOpening() const
{
    // 
    return this->mnSceneChangeAnimPhase == SCAP::SCAP_Opening;
}

// 
bool BaseSceneManager::CheckOpendWait() const
{
    // 
    return this->mnSceneChangeAnimPhase == SCAP::SCAP_OpenedWait;
}

void *BaseSceneManager::GetCSD(CSDN number)
{
    return this->mlUniqueDataList.SearchDataNum(number);
}
