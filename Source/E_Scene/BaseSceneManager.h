#pragma once

#include "BaseScene.h"
#include "../Y_Tool/CreateFlag.h"
#include "../Y_Tool/VoidList.h"
#include "DXLib.h"

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


    VERTEX2DSHADER g_Vertex[4]; //頂点配列
    unsigned short g_Index[6];  //インデックス
    int g_Offscreen = -1;       //オフスクリーンバッファ用ハンドル
    int g_PixelShader = -1;     //ピクセルシェーダー用ハンドル
    int g_PostPixelShader = -1; //ポストエフェクト用ピクセルシェーダー用ハンドル

    //ライトの座標
    //構造隊を作るときの注意点（16バイト単位にしなくてはならない）
    struct LightPos
    {
        VECTOR pos;
		float temp;// 16バイト単位にするための空の変数
    };

    LightPos g_lightpos;
    int g_lightconstbuff;


    VERTEX2DSHADER SetVertex2D(float x, float y, float u, float v)
    {
        VERTEX2DSHADER vt;

        vt.pos = VGet(x, y, 0.0f);
        vt.u = u;
        vt.v = v;
        vt.su = u;
        vt.sv = v;
        vt.rhw = 1.0f;
        vt.dif = GetColorU8(255, 255, 255, 255);
        vt.spc = GetColorU8(0, 0, 0, 0);

        return vt;
    }
    // 2Dポリゴンを描画する関数
    void DrawPS(float x, float y, float width, float height, int graphhandle)
    {
        SetUseTextureToShader(0, graphhandle);

        g_Vertex[0] = SetVertex2D(x, y, 0.0f, 0.0f);
        g_Vertex[1] = SetVertex2D(x + width, y, 1.0f, 0.0f);
        g_Vertex[2] = SetVertex2D(x, y + height, 0.0f, 1.0f);
        g_Vertex[3] = SetVertex2D(x + width, y + height, 1.0f, 1.0f);

        DrawPolygonIndexed2DToShader(g_Vertex, 4, g_Index, 2);
    }


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

    // シーン遷移(開ける時)のアニメーションが終わったかを確認する関数
    bool CheckSceneOpenEnd() const;

    // シーン遷移(閉じる時)のアニメーションが終わったかを確認する関数
    bool CheckSceneCloseEnd() const;

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