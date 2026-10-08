#pragma once
#include <string>
#include <vector>

#include "ImguiData.h"

// TODO:_ 最終的にはプロジェクトから外す
/*
    【使用方法】
    使用時の呼び出し例は、このヘッダーファイルの下部に記載。

    ・AddDrawImgui()
        Imguiを表示したい処理の中で呼び出す。
        呼び出し時に直接描画するため、初期化時に呼び出しても表示されない。

    ・AddDrawImguiGroup()
        Imguiをグループとして表示したい処理の中で呼び出す。

    ・StartGroup() / EndGroup()
        グループ内にImguiを追加する場合に使用する。
        StartGroup() → AddDrawImguiGroup() → EndGroup()の順で呼び出す。
*/

class ImguiManager
{
private:
    // 登録中グループ関連の情報
    struct CURRENT_GROUP_TYPE_DATA
    {
        // 参照しているグループ種類
        IMGUI_GROUP_TYPE CurrentGroupType = IMGUI_GROUP_TYPE::NONE;

        // 参照しているグループまでの添え字
        std::vector<int> CurrentGroupTypeIndexs;
    };
private:
    // IMGUIデータ float
    std::vector<IMGUI_FLOAT_DATA> mstImguiFloatDatas;

    // IMGUIデータ int
    std::vector<IMGUI_INT_DATA> mstImguiIntDatas;

    // IMGUIグループデータ
    std::vector<IMGUI_GROUP_DATA> mstImguiGroupDatas;
    
    // 現在登録中のグループ関連情報
    CURRENT_GROUP_TYPE_DATA mstCurrentGroupTypeData;

    // 追加Imguiナンバー
    int mnAddNumber;

    // imgui実行フラグ
    bool mbIsImguiExecute;
public:

    ImguiManager(bool isImguiExecute);
    ~ImguiManager();

    /// <summary>初期化</summary>
    void Initilize();
    /// <summary>終了</summary>
    void Finalize();

    /// <summary>更新</summary>
    void Update();
    /// <summary>描画</summary>
    void Draw();

    /// <summary>Imgui追加描画</summary>
    void AddDrawImgui(IMGUI_FLOAT_DATA imguiFloatData);
    /// <summary>Imgui追加描画</summary>
    void AddDrawImgui(IMGUI_INT_DATA imguiIntData);

    /// <summary>Imguiグループ追加描画(全部)</summary>
    void AddDrawImguiGroup(IMGUI_GROUP_DATA imguiGroupData);
    /// <summary>Imguiグループ追加描画(float)</summary>
    void AddDrawImguiGroup(IMGUI_FLOAT_DATA imguiFloatData, IMGUI_GROUP_TYPE groupType, std::string groupName = "NEW_GROUP");
    /// <summary>Imguiグループ追加描画(int)</summary>
    void AddDrawImguiGroup(IMGUI_INT_DATA imguiIntData, IMGUI_GROUP_TYPE groupType, std::string groupName = "NEW_GROUP");
    /// <summary>Imguiグループ追加描画(参照float情報) ※StartGroupを読んでから使用してください</summary>
    void AddDrawImguiGroup(IMGUI_FLOAT_DATA imguiFloatData);
    /// <summary>Imguiグループ追加描画(参照int情報) ※StartGroupを読んでから使用してください</summary>
    void AddDrawImguiGroup(IMGUI_INT_DATA imguiIntData);

    /// <summary>Imguiグループ参照先設定開始 ※設定が終わったらEndGroupを読んでください</summary>
    void StartGroup(IMGUI_GROUP_TYPE groupType, std::string groupName = "NEW_GROUP");
    /// <summary>Imguiグループ参照先設定終了</summary>
    void EndGroup();

    /// <summary>Imguiグループを新しく作成</summary>
    /// <param name="parentGroupType">NONEなら最上位に、違うなら探して子供として作成</param>
    void CreateImguiGroup(IMGUI_GROUP_TYPE groupType, std::string groupName, IMGUI_GROUP_TYPE parentGroupType = IMGUI_GROUP_TYPE::NONE);

    /// <summary>Imguiグループを移動</summary>
    /// <param name="parentGroupType">NONEなら最上位に、違うなら探して子供として移動</param>
    void MoveImguiGroup(IMGUI_GROUP_TYPE groupType, IMGUI_GROUP_TYPE parentGroupType);

    /// <summary>Imguiグループを削除</summary>
    void DeleteImguiGroup(IMGUI_GROUP_TYPE groupType);

    /// <summary>WndProcでやるImguiの処理</summary>
    void ImguiWndProcProcess(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

private:
    /*floatのImguui描画*/
    void DrawFloatImgui(IMGUI_FLOAT_DATA imguiFloatData);

    /*intのImguui描画*/
    void DrawIntImgui(IMGUI_INT_DATA imguiIntData);

    /*Imguiグループ描画*/
    void DrawGroupImgui(IMGUI_GROUP_DATA imguiGroupData);

    /*グループ種類からグループを検索*/
    CURRENT_GROUP_TYPE_DATA SearchImguiGroupData(IMGUI_GROUP_TYPE groupType, IMGUI_GROUP_DATA** imguiGroupData);

    /*現在参照しているグループを取得*/
    IMGUI_GROUP_DATA* GetCurrentGroupData();
};
/*
構造体作成
const char* label, float* v, float v_min, float v_max, const char* format, ImGuiSliderFlags flags
const char* label, float v[2], float v_min, float v_max, const char* format, ImGuiSliderFlags flags
const char* label, float v[3], float v_min, float v_max, const char* format, ImGuiSliderFlags flags
const char* label, float v[4], float v_min, float v_max, const char* format, ImGuiSliderFlags flags
const char* label, float* v_rad, float v_degrees_min, float v_degrees_max, const char* format, ImGuiSliderFlags flags
const char* label, float* v, float v_speed, float v_min, float v_max, const char* format, ImGuiSliderFlags flags
*/

/*
//================================================================================
// 1. 通常のfloat
//================================================================================
Master::mpImguiManager->AddDrawImgui(
    IMGUI_FLOAT_DATA::GetImguiData(
        { &testSize },
        0.1f,
        0.1f,
        0.1f,
        0.0f,
        250.0f,
        "TEST_SIZE_BACK_",
        "%f",
        0,
        IMGUI_TYPE::SLIDER1
    )
);
*/

/*
//================================================================================
// 2. 通常のint
//================================================================================
Master::mpImguiManager->AddDrawImgui(
    IMGUI_INT_DATA::GetImguiData(
        {
            &mstMiniMapDrawGraphData[0].pos.x,
            &mstMiniMapDrawGraphData[0].pos.y,
            &mstMiniMapDrawGraphData[0].size.x,
            &mstMiniMapDrawGraphData[0].size.y
        },
        1.0f,
        1.0f,
        1.0f,
        0,
        1000,
        "NONE_",
        "%d",
        0,
        IMGUI_TYPE::SLIDER4
    )
);
*/

/*
//================================================================================
// 3. グループに全部登録
//================================================================================
Master::mpImguiManager->AddDrawImguiGroup(
    IMGUI_GROUP_DATA::GetImguiGroupData(
        "TEST_GROUP",
        IMGUI_GROUP_TYPE::TEST_1
    )
);
*/

/*
//================================================================================
// 4. グループにfloatを登録
//================================================================================
Master::mpImguiManager->AddDrawImguiGroup(
    IMGUI_FLOAT_DATA::GetImguiData(
        { &testSize },
        0.1f,
        0.1f,
        0.1f,
        0.0f,
        250.0f,
        "TEST_SIZE",
        "%f",
        0,
        IMGUI_TYPE::SLIDER1
    ),
    IMGUI_GROUP_TYPE::TEST_1,
    "TEST_GROUP"
);
*/

/*
//================================================================================
// 5. グループを参照してfloatを登録
//================================================================================
Master::mpImguiManager->StartGroup(
    IMGUI_GROUP_TYPE::TEST_1,
    "TEST_GROUP"
);

Master::mpImguiManager->AddDrawImguiGroup(
    IMGUI_FLOAT_DATA::GetImguiData(
        { &testSize },
        0.1f,
        0.1f,
        0.1f,
        0.0f,
        250.0f,
        "TEST_SIZE",
        "%f",
        0,
        IMGUI_TYPE::SLIDER1
    )
);

Master::mpImguiManager->EndGroup();
*/













/*
    【TestImgui】
    ImguiManagerの各機能を確認するためのテスト処理。

    ・通常のImgui登録
    ・グループを作成してImguiを登録
    ・StartGroup / EndGroupを使用した登録
    ・StartGroupによるグループの自動作成
    ・グループ階層の作成と登録
    ・IMGUI_GROUP_DATAを直接作成して登録
    ・グループを指定したImgui登録時の自動作成

    ※AddDrawImgui() / AddDrawImguiGroup()は毎フレーム登録する必要があるため、
      TestImgui()も毎フレーム呼び出す。
*/
/*
//==================================================
// ImguiManager テスト用変数
//==================================================
float testFloat1 = 10.0f;
int testInt1 = 10;

float testFloat2 = 20.0f;
int testInt2 = 20;

float testFloat3 = 30.0f;
int testInt3 = 30;

float testFloat4 = 40.0f;
int testInt4 = 40;

float testFloat5_1 = 51.0f;
int testInt5_1 = 51;

float testFloat5_2 = 52.0f;
int testInt5_2 = 52;

float testFloat5_3 = 53.0f;
int testInt5_3 = 53;

float testFloat6 = 60.0f;
int testInt6 = 60;

float testFloat10 = 100.0f;
int testInt10 = 100;


//==================================================
// ImguiManager テスト
//==================================================
void TestImgui()
{
    //==================================================
    // 1. 通常のImGui登録
    //==================================================
    Master::mpImguiManager->AddDrawImgui(
        IMGUI_FLOAT_DATA::GetImguiData(
            { &testFloat1 },
            1.0f,
            0.1f,
            1.0f,
            0.0f,
            100.0f,
            "TestFloat1"));

    Master::mpImguiManager->AddDrawImgui(
        IMGUI_INT_DATA::GetImguiData(
            { &testInt1 },
            1.0f,
            1.0f,
            10.0f,
            0,
            100,
            "TestInt1"));


    //==================================================
    // 2. グループを作成して登録
    //==================================================
    Master::mpImguiManager->CreateImguiGroup(
        IMGUI_GROUP_TYPE::TEST_1,
        "CreateGroup");

    Master::mpImguiManager->AddDrawImguiGroup(
        IMGUI_FLOAT_DATA::GetImguiData(
            { &testFloat2 },
            1.0f,
            0.1f,
            1.0f,
            0.0f,
            100.0f,
            "TestFloat2"),
        IMGUI_GROUP_TYPE::TEST_1);

    Master::mpImguiManager->AddDrawImguiGroup(
        IMGUI_INT_DATA::GetImguiData(
            { &testInt2 },
            1.0f,
            1.0f,
            10.0f,
            0,
            100,
            "TestInt2"),
        IMGUI_GROUP_TYPE::TEST_1);


    //==================================================
    // 3. StartGroup / EndGroup
    //==================================================
    Master::mpImguiManager->StartGroup(
        IMGUI_GROUP_TYPE::TEST_2,
        "StartGroup");

    Master::mpImguiManager->AddDrawImguiGroup(
        IMGUI_FLOAT_DATA::GetImguiData(
            { &testFloat3 },
            1.0f,
            0.1f,
            1.0f,
            0.0f,
            100.0f,
            "TestFloat3"));

    Master::mpImguiManager->AddDrawImguiGroup(
        IMGUI_INT_DATA::GetImguiData(
            { &testInt3 },
            1.0f,
            1.0f,
            10.0f,
            0,
            100,
            "TestInt3"));

    Master::mpImguiManager->EndGroup();


    //==================================================
    // 4. StartGroupによるグループ自動作成
    //==================================================
    Master::mpImguiManager->StartGroup(
        IMGUI_GROUP_TYPE::TEST_3,
        "AutoCreateGroup");

    Master::mpImguiManager->AddDrawImguiGroup(
        IMGUI_FLOAT_DATA::GetImguiData(
            { &testFloat4 },
            1.0f,
            0.1f,
            1.0f,
            0.0f,
            100.0f,
            "TestFloat4"));

    Master::mpImguiManager->AddDrawImguiGroup(
        IMGUI_INT_DATA::GetImguiData(
            { &testInt4 },
            1.0f,
            1.0f,
            10.0f,
            0,
            100,
            "TestInt4"));

    Master::mpImguiManager->EndGroup();


    //==================================================
    // 5. グループ階層を作成
    //==================================================
    Master::mpImguiManager->CreateImguiGroup(
        IMGUI_GROUP_TYPE::TEST_4,
        "ParentGroup");

    Master::mpImguiManager->CreateImguiGroup(
        IMGUI_GROUP_TYPE::TEST_5,
        "ChildGroup",
        IMGUI_GROUP_TYPE::TEST_4);

    Master::mpImguiManager->CreateImguiGroup(
        IMGUI_GROUP_TYPE::TEST_6,
        "GrandChildGroup",
        IMGUI_GROUP_TYPE::TEST_5);

    Master::mpImguiManager->AddDrawImguiGroup(
        IMGUI_FLOAT_DATA::GetImguiData(
            { &testFloat5_1 },
            1.0f,
            0.1f,
            1.0f,
            0.0f,
            100.0f,
            "TestFloat5_1"),
        IMGUI_GROUP_TYPE::TEST_4);

    Master::mpImguiManager->AddDrawImguiGroup(
        IMGUI_INT_DATA::GetImguiData(
            { &testInt5_1 },
            1.0f,
            1.0f,
            10.0f,
            0,
            100,
            "TestInt5_1"),
        IMGUI_GROUP_TYPE::TEST_4);

    Master::mpImguiManager->AddDrawImguiGroup(
        IMGUI_FLOAT_DATA::GetImguiData(
            { &testFloat5_2 },
            1.0f,
            0.1f,
            1.0f,
            0.0f,
            100.0f,
            "TestFloat5_2"),
        IMGUI_GROUP_TYPE::TEST_5);

    Master::mpImguiManager->AddDrawImguiGroup(
        IMGUI_INT_DATA::GetImguiData(
            { &testInt5_2 },
            1.0f,
            1.0f,
            10.0f,
            0,
            100,
            "TestInt5_2"),
        IMGUI_GROUP_TYPE::TEST_5);

    Master::mpImguiManager->AddDrawImguiGroup(
        IMGUI_FLOAT_DATA::GetImguiData(
            { &testFloat5_3 },
            1.0f,
            0.1f,
            1.0f,
            0.0f,
            100.0f,
            "TestFloat5_3"),
        IMGUI_GROUP_TYPE::TEST_6);

    Master::mpImguiManager->AddDrawImguiGroup(
        IMGUI_INT_DATA::GetImguiData(
            { &testInt5_3 },
            1.0f,
            1.0f,
            10.0f,
            0,
            100,
            "TestInt5_3"),
        IMGUI_GROUP_TYPE::TEST_6);


    //==================================================
    // 6. IMGUI_GROUP_DATAを直接作成して登録
    //==================================================
    IMGUI_GROUP_DATA testGroupData =
        IMGUI_GROUP_DATA::GetImguiGroupData(
            "GroupData",
            IMGUI_GROUP_TYPE::TEST_7);

    testGroupData.AddFloatData(
        IMGUI_FLOAT_DATA::GetImguiData(
            { &testFloat6 },
            1.0f,
            0.1f,
            1.0f,
            0.0f,
            100.0f,
            "TestFloat6"));

    testGroupData.AddIntData(
        IMGUI_INT_DATA::GetImguiData(
            { &testInt6 },
            1.0f,
            1.0f,
            10.0f,
            0,
            100,
            "TestInt6"));

    Master::mpImguiManager->AddDrawImguiGroup(testGroupData);


    //==================================================
    // 7. グループを指定して自動作成
    //==================================================
    Master::mpImguiManager->AddDrawImguiGroup(
        IMGUI_FLOAT_DATA::GetImguiData(
            { &testFloat10 },
            1.0f,
            0.1f,
            1.0f,
            0.0f,
            100.0f,
            "TestFloat10"),
        IMGUI_GROUP_TYPE::TEST_8,
        "AutoCreateByAdd");

    Master::mpImguiManager->AddDrawImguiGroup(
        IMGUI_INT_DATA::GetImguiData(
            { &testInt10 },
            1.0f,
            1.0f,
            10.0f,
            0,
            100,
            "TestInt10"),
        IMGUI_GROUP_TYPE::TEST_8,
        "AutoCreateByAdd");
}*/