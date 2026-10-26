#pragma once
#include <string>
#include <vector>

#include "ImguiData.h"

#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")

// TODO:_ 最終的にはプロジェクトから外す
/*
【使用方法】
使用時の呼び出し例は、このヘッダーファイルの下部に記載。

・Initilize() / Finalize()
    ImguiManagerの初期化と終了処理を行う。

・Update() / Draw()
    ImguiManagerの更新と描画を行う。

・AddDrawImgui()
    変数・ボタン・レイアウトを追加する。
    表示内容を更新するため、毎フレーム呼び出す。

・AddDrawImguiGroup()
    Imguiをグループに追加する。
    グループ全体、グループの種類と追加する内容、またはStartGroup()で
    指定したグループへの追加に対応している。

・StartGroup() / EndGroup()
    グループへの追加先を指定する。
    StartGroup()で追加先を指定し、追加が終わったらEndGroup()を呼び出す。

・CreateImguiGroup()
    新しいグループを作成する。
    親グループを指定すると、その子グループとして作成する。
    親グループを指定しない場合は、最上位に作成する。

・MoveImguiGroup()
    指定したグループを別の親グループへ移動する。
    親グループにNONEを指定すると、最上位へ移動する。

・DeleteImguiGroup()
    指定したグループを削除する。

・ImguiWndProcProcess()
    ウィンドウプロシージャ（WndProc）から呼び出し、
    Imguiに関するウィンドウメッセージを処理する。
    ※DXライブラリで使用する想定

*/
class ImguiManager
{
private:
    // 登録中グループ関連の情報
    struct CURRENT_GROUP_TYPE_DATA
    {
#ifdef _DEBUG
        // 参照しているグループ種類
        IMGUI_GROUP_TYPE CurrentGroupType = IMGUI_GROUP_TYPE::NONE;

        // 参照しているグループまでの添え字
        std::vector<int> CurrentGroupTypeIndexs;
#endif
    };
private:
#ifdef _DEBUG
    // IMGUIグループデータ
    std::vector<IMGUI_GROUP_DATA> mstImguiGroupDatas;
    
    // 現在登録中のグループ関連情報
    CURRENT_GROUP_TYPE_DATA mstCurrentGroupTypeData;

    // 追加Imguiナンバー
    int mnAddNumber;

    // imgui実行フラグ
    const bool mbIsImguiExecute;

    // ツリーの開閉状態管理
    std::vector<bool> mbLayoutDrawFlags;
    
    // Begin() / End() の描画状態管理
    std::vector<unsigned char> mucWindowDrawFlags;

    // Begin()を呼び出した
    static constexpr unsigned char WINDOW_BEGIN_CALLED = 0x01;

    // ウィンドウ内を描画できる
    static constexpr unsigned char WINDOW_DRAW_ENABLED = 0x02;

    // 初期化時に一度だけ作成
    ID3D11Texture2D* mdCopyTexture = nullptr;
    ID3D11ShaderResourceView* mbCopySRV = nullptr;

    // フレーム数
    int mnFrameCount = 0;

#endif
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

    /// <summary>Imgui変数追加描画(変数)</summary>
    void AddDrawImgui(IMGUI_VARIABLE_CONTROL imguiControlVariableData, std::string addTabName = "AddTab");
    /// <summary>Imgui追加描画（ボタン）</summary>
    void AddDrawImgui(IMGUI_BUTTON_CONTROL imguiControlButtonData, std::string addTabName = "AddTab");
    /// <summary>Imgui追加描画（レイアウト）</summary>
    void AddDrawImgui(IMGUI_LAYOUT_CONTROL imguiControlLayoutData, std::string addTabName = "AddTab");

    /// <summary>Imguiグループ追加描画(全部)</summary>
    void AddDrawImguiGroup(IMGUI_GROUP_DATA imguiGroupData);
    /// <summary>Imguiグループ追加描画(引数参照)</summary>
    void AddDrawImguiGroup(IMGUI_ALL_DRAW_ONE_DATA imguiControlVariableData, IMGUI_GROUP_TYPE groupType, std::string groupName = "NEW_GROUP");
    /// <summary>Imguiグループ追加描画(参照) ※StartGroupを読んでから使用してください</summary>
    void AddDrawImguiGroup(IMGUI_ALL_DRAW_ONE_DATA imguiControlVariableData);

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
    /*Imguui描画*/
    void DrawControlVariableImgui(IMGUI_VARIABLE_CONTROL imguiControlVariableData);

    /*ボタンimgui描画*/
    void DrawButtonImgui(IMGUI_BUTTON_CONTROL& imguiButtonControlVariableData);

    /*レイアウトimgui描画*/
    void DrawLayoutImgui(IMGUI_LAYOUT_CONTROL imguiLayoutControlData);

    /*現在のレイアウト内を描画できるか*/
    bool IsLayoutDrawEnabled() const;

    /*Imguiグループ描画*/
    void DrawGroupImgui(IMGUI_GROUP_DATA imguiGroupData);

    /*グループ種類からグループを検索*/
    CURRENT_GROUP_TYPE_DATA SearchImguiGroupData(IMGUI_GROUP_TYPE groupType, IMGUI_GROUP_DATA** imguiGroupData);

    /*現在参照しているグループを取得*/
    IMGUI_GROUP_DATA* GetCurrentGroupData();

    /*変数型を整数か浮動小数の変換*/
    IMGUI_VARIABLE_INTEGER_TYPE ChangeVariableTypeToVariableIntegerType(IMGUI_VARIABLE_TYPE variableType);

    /*ゲーム画面描画用変数初期化*/
    void InitDrawGameDisplayToImguiVariable();
    /*ゲーム画面描画*/
    void DrawGameDisplayToImgui(std::string plusName = "", float magnification = 1.0f, ImVec2 centerUV = ImVec2(0.5f, 0.5f));
};

/*
//================================================================================
// 1. 通常のfloat
//================================================================================
Master::mpImguiManager->AddDrawImgui(
    IMGUI_VARIABLE_CONTROL::GetImguiData(
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
    IMGUI_VARIABLE_CONTROL::GetImguiData(
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
    IMGUI_VARIABLE_CONTROL::GetImguiData(
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
    IMGUI_VARIABLE_CONTROL::GetImguiData(
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
//================================================================================
// 6. 通常のボタン
//================================================================================
Master::mpImguiManager->AddDrawImgui(
    IMGUI_BUTTON_CONTROL::GetImguiData(
        IMGUI_BUTTON_TYPE::BUTTON,
        "TEST_BUTTON"
    )
);
*/

/*
//================================================================================
// 7. 通常のレイアウト
//================================================================================
Master::mpImguiManager->AddDrawImgui(
    IMGUI_LAYOUT_CONTROL::GetImguiData(
        IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_TEXT,
        "TEST_LAYOUT"
    )
);
*/

/*
//================================================================================
// 8. グループにボタンを登録
//================================================================================
Master::mpImguiManager->AddDrawImguiGroup(
    IMGUI_ALL_DRAW_ONE_DATA(
        IMGUI_BUTTON_CONTROL::GetImguiData(
            IMGUI_BUTTON_TYPE::BUTTON,
            "TEST_GROUP_BUTTON"
        )
    ),
    IMGUI_GROUP_TYPE::TEST_1,
    "TEST_GROUP"
);
*/

/*
//================================================================================
// 9. グループにレイアウトを登録
//================================================================================
Master::mpImguiManager->AddDrawImguiGroup(
    IMGUI_ALL_DRAW_ONE_DATA(
        IMGUI_LAYOUT_CONTROL::GetImguiData(
            IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_TEXT,
            "TEST_GROUP_LAYOUT"
        )
    ),
    IMGUI_GROUP_TYPE::TEST_1,
    "TEST_GROUP"
);
*/

/*
//================================================================================
// 10. グループを参照してボタンを登録
//================================================================================
Master::mpImguiManager->StartGroup(
    IMGUI_GROUP_TYPE::TEST_1,
    "TEST_GROUP"
);

Master::mpImguiManager->AddDrawImguiGroup(
    IMGUI_ALL_DRAW_ONE_DATA(
        IMGUI_BUTTON_CONTROL::GetImguiData(
            IMGUI_BUTTON_TYPE::BUTTON,
            "TEST_GROUP_BUTTON"
        )
    )
);

Master::mpImguiManager->EndGroup();
*/

/*
//================================================================================
// 11. グループを参照してレイアウトを登録
//================================================================================
Master::mpImguiManager->StartGroup(
    IMGUI_GROUP_TYPE::TEST_1,
    "TEST_GROUP"
);

Master::mpImguiManager->AddDrawImguiGroup(
    IMGUI_ALL_DRAW_ONE_DATA(
        IMGUI_LAYOUT_CONTROL::GetImguiData(
            IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_TEXT,
            "TEST_GROUP_LAYOUT"
        )
    )
);

Master::mpImguiManager->EndGroup();
*/

/*
//================================================================================
// 12. グループを作成
//================================================================================

// 最上位にグループを作成
Master::mpImguiManager->CreateImguiGroup(
    IMGUI_GROUP_TYPE::TEST_2,
    "TEST_GROUP_2"
);

// TEST_1の子グループとして作成
Master::mpImguiManager->CreateImguiGroup(
    IMGUI_GROUP_TYPE::TEST_3,
    "TEST_GROUP_3",
    IMGUI_GROUP_TYPE::TEST_1
);
*/

/*
//================================================================================
// 13. グループを移動
//================================================================================

// TEST_3をTEST_2の子グループに移動
Master::mpImguiManager->MoveImguiGroup(
    IMGUI_GROUP_TYPE::TEST_3,
    IMGUI_GROUP_TYPE::TEST_2
);

// TEST_3を最上位に移動
Master::mpImguiManager->MoveImguiGroup(
    IMGUI_GROUP_TYPE::TEST_3,
    IMGUI_GROUP_TYPE::NONE
);
*/

/*
//================================================================================
// 14. グループを削除
//================================================================================
Master::mpImguiManager->DeleteImguiGroup(
    IMGUI_GROUP_TYPE::TEST_3
);
*/

/*
//================================================================================
// 15. WndProcでImguiの処理
//================================================================================

// ウィンドウプロシージャ内で呼び出す
Master::mpImguiManager->ImguiWndProcProcess(
    hWnd,
    msg,
    wParam,
    lParam
);
*/






/*
//==================================================
// ImguiManager テスト処理
//==================================================
// レイアウト・ボタン・整数型変数の各機能をテストする。
// ・レイアウトテスト：各種レイアウト設定や組み合わせ
// ・ボタンテスト：各種ボタンと状態の変更
// ・整数型変数テスト：SLIDER / DRAG / INPUT（1～4個の変数）
//
// InitializeTestAll()でテスト用データを初期化する。
// DrawTestAllImgui()で各テスト項目を登録する。
// IsTestDrawがtrueの場合に登録処理を実行し、実行後はfalseにする。
// ResetTestDrawFlag()でIsTestDrawをtrueに戻すことで、再登録できる。
*/
/*
namespace TEST_IMGUI_MANAGER
{
#ifdef _DEBUG
    //==================================================
    // ImguiManager レイアウトテスト用変数
    //==================================================
    IMGUI_LAYOUT_CONTROL testLayoutText;
    IMGUI_LAYOUT_CONTROL testLayoutTextFormat;
    IMGUI_LAYOUT_CONTROL testLayoutSameLine;
    IMGUI_LAYOUT_CONTROL testLayoutSeparator;
    IMGUI_LAYOUT_CONTROL testLayoutSpacing;
    IMGUI_LAYOUT_CONTROL testLayoutNewLine;
    IMGUI_LAYOUT_CONTROL testLayoutIndent;
    IMGUI_LAYOUT_CONTROL testLayoutUnindent;
    IMGUI_LAYOUT_CONTROL testLayoutDummy;
    IMGUI_LAYOUT_CONTROL testLayoutSetNextItemWidth;
    IMGUI_LAYOUT_CONTROL testLayoutPushItemWidth;
    IMGUI_LAYOUT_CONTROL testLayoutPopItemWidth;
    IMGUI_LAYOUT_CONTROL testLayoutAlignTextToFramePadding;
    IMGUI_LAYOUT_CONTROL testLayoutSetNextItemOpen;
    IMGUI_LAYOUT_CONTROL testLayoutBeginGroup;
    IMGUI_LAYOUT_CONTROL testLayoutEndGroup;
    IMGUI_LAYOUT_CONTROL testLayoutBeginChild;
    IMGUI_LAYOUT_CONTROL testLayoutEndChild;
    IMGUI_LAYOUT_CONTROL testLayoutCollapsingHeader;
    IMGUI_LAYOUT_CONTROL testLayoutTreeNode1;
    IMGUI_LAYOUT_CONTROL testLayoutTreeNode2;
    IMGUI_LAYOUT_CONTROL testLayoutTreePop;
    IMGUI_LAYOUT_CONTROL testLayoutBeginTable;
    IMGUI_LAYOUT_CONTROL testLayoutTableSetupColumn1;
    IMGUI_LAYOUT_CONTROL testLayoutTableSetupColumn2;
    IMGUI_LAYOUT_CONTROL testLayoutTableHeadersRow;
    IMGUI_LAYOUT_CONTROL testLayoutTableNextRow;
    IMGUI_LAYOUT_CONTROL testLayoutTableNextColumn;
    IMGUI_LAYOUT_CONTROL testLayoutTableSetColumnIndex;
    IMGUI_LAYOUT_CONTROL testLayoutEndTable;
    IMGUI_LAYOUT_CONTROL testLayoutPushStyleVar;
    IMGUI_LAYOUT_CONTROL testLayoutPopStyleVar;
    IMGUI_LAYOUT_CONTROL testLayoutPushStyleColor;
    IMGUI_LAYOUT_CONTROL testLayoutPopStyleColor;
    //==================================================
    // ImguiManager レイアウトテスト用追加変数
    //==================================================
    IMGUI_LAYOUT_CONTROL testLayoutTextA;
    IMGUI_LAYOUT_CONTROL testLayoutTextB;
    IMGUI_LAYOUT_CONTROL testLayoutTextC;
    IMGUI_LAYOUT_CONTROL testLayoutTextD;
    IMGUI_LAYOUT_CONTROL testLayoutTextE;
    IMGUI_LAYOUT_CONTROL testLayoutTextF;
    IMGUI_LAYOUT_CONTROL testLayoutTextG;
    IMGUI_LAYOUT_CONTROL testLayoutTextH;
    IMGUI_LAYOUT_CONTROL testLayoutTextI;
    IMGUI_LAYOUT_CONTROL testLayoutTextJ;
    IMGUI_LAYOUT_CONTROL testLayoutTextK;
    IMGUI_LAYOUT_CONTROL testLayoutTextL;
    IMGUI_LAYOUT_CONTROL testLayoutTextM;
    IMGUI_LAYOUT_CONTROL testLayoutTextN;
    IMGUI_LAYOUT_CONTROL testLayoutTextO;
    IMGUI_LAYOUT_CONTROL testLayoutTextP;
    IMGUI_LAYOUT_CONTROL testLayoutTextQ;
    IMGUI_LAYOUT_CONTROL testLayoutTextR;
    IMGUI_LAYOUT_CONTROL testLayoutTextS;
    IMGUI_LAYOUT_CONTROL testLayoutTextT;
    IMGUI_LAYOUT_CONTROL testLayoutTextU;
    IMGUI_LAYOUT_CONTROL testLayoutTextV;
    IMGUI_LAYOUT_CONTROL testLayoutTextW;
    IMGUI_LAYOUT_CONTROL testLayoutTextX;

    // ボタン状態保持用（IMGUI_BUTTON_CONTROL はポインタで参照する）
    bool testLayoutButtonAFlag = false;
    bool testLayoutButtonAArgumentFlag = false;
    bool testLayoutButtonBFlag = false;
    bool testLayoutButtonBArgumentFlag = false;
    bool testLayoutButtonCFlag = false;
    bool testLayoutButtonCArgumentFlag = false;
    bool testLayoutButtonDFlag = false;
    bool testLayoutButtonDArgumentFlag = false;
    bool testLayoutButtonEFlag = false;
    bool testLayoutButtonEArgumentFlag = false;
    bool testLayoutButtonFFlag = false;
    bool testLayoutButtonFArgumentFlag = false;
    bool testLayoutButtonGFlag = false;
    bool testLayoutButtonGArgumentFlag = false;
    bool testLayoutButtonHFlag = false;
    bool testLayoutButtonHArgumentFlag = false;
    bool testLayoutButtonFlag = false;
    bool testLayoutButtonArgumentFlag = false;

    // ボタンテスト用
    IMGUI_BUTTON_CONTROL testLayoutButtonA;
    IMGUI_BUTTON_CONTROL testLayoutButtonB;
    IMGUI_BUTTON_CONTROL testLayoutButtonC;
    IMGUI_BUTTON_CONTROL testLayoutButtonD;
    IMGUI_BUTTON_CONTROL testLayoutButtonE;
    IMGUI_BUTTON_CONTROL testLayoutButtonF;
    IMGUI_BUTTON_CONTROL testLayoutButtonG;
    IMGUI_BUTTON_CONTROL testLayoutButtonH;
    //==================================================
    // ImguiManager レイアウトテスト用変数
    //==================================================
    IMGUI_BUTTON_CONTROL testLayoutButton;

    int testLayoutInputValue = 123;
    IMGUI_VARIABLE_CONTROL testLayoutInput;

    IMGUI_LAYOUT_CONTROL testLayoutEndCollapsingHeader;
    //==================================================
    // ImguiManager レイアウトテスト用変数の初期化
    //==================================================
    void InitializeTestAllLayoutImgui()
    {
        //==================================================
        // 1. テキスト表示
        //==================================================
        testLayoutText.SetLayoutType(IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_TEXT);
        testLayoutText.SetLayoutText(u8"レイアウトテスト");

        //==================================================
        // 2. フォーマット付きテキスト
        //==================================================
        testLayoutTextFormat.SetLayoutType(IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_TEXT_FORMAT);
        testLayoutTextFormat.SetLayoutText(u8"整数値: %d");
        testLayoutTextFormat.SetLayoutVarable(IMGUI_VARIABLE_DATA(123)); // IMGUI_VARIABLE_DATAの実際の設定方法に合わせて変更

        //==================================================
        // 3. 同じ行に配置
        //==================================================
        testLayoutSameLine.SetLayoutType(IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_SAME_LINE);
        testLayoutSameLine.SetLayoutWidth(0.0f);
        testLayoutSameLine.SetLayoutSpacing(-1.0f);

        //==================================================
        // 4. 水平線
        //==================================================
        testLayoutSeparator.SetLayoutType(IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_SEPARATOR);

        //==================================================
        // 5. 項目間の空白
        //==================================================
        testLayoutSpacing.SetLayoutType(IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_SPACING);

        //==================================================
        // 6. 改行
        //==================================================
        testLayoutNewLine.SetLayoutType(IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_NEW_LINE);

        //==================================================
        // 7. 描画位置を右にずらす
        //==================================================
        testLayoutIndent.SetLayoutType(IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_INDENT);
        testLayoutIndent.SetLayoutWidth(30.0f);

        //==================================================
        // 8. 描画位置を戻す
        //==================================================
        testLayoutUnindent.SetLayoutType(IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_UNINDENT);
        testLayoutUnindent.SetLayoutWidth(30.0f);

        //==================================================
        // 9. 空白領域
        //==================================================
        testLayoutDummy.SetLayoutType(IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_DUMMY);
        testLayoutDummy.SetLayoutSize(ImVec2(100.0f, 20.0f));

        //==================================================
        // 10. 次の項目の幅を指定
        //==================================================
        testLayoutSetNextItemWidth.SetLayoutType(IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_SET_NEXT_ITEM_WIDTH);
        testLayoutSetNextItemWidth.SetLayoutWidth(200.0f);

        //==================================================
        // 11. 項目の幅を設定
        //==================================================
        testLayoutPushItemWidth.SetLayoutType(IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_PUSH_ITEM_WIDTH);
        testLayoutPushItemWidth.SetLayoutWidth(200.0f);

        //==================================================
        // 12. 項目の幅を元に戻す
        //==================================================
        testLayoutPopItemWidth.SetLayoutType(IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_POP_ITEM_WIDTH);

        //==================================================
        // 13. テキストの高さを合わせる
        //==================================================
        testLayoutAlignTextToFramePadding.SetLayoutType(
            IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_ALIGN_TEXT_TO_FRAME_PADDING);

        //==================================================
        // 14. 次のツリー項目の開閉状態
        //==================================================
        testLayoutSetNextItemOpen.SetLayoutType(IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_SET_NEXT_ITEM_OPEN);
        testLayoutSetNextItemOpen.SetLayoutDefaultOpen(true);
        testLayoutSetNextItemOpen.SetLayoutCount(ImGuiCond_Once);

        //==================================================
        // 15. グループ開始
        //==================================================
        testLayoutBeginGroup.SetLayoutType(IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_BEGIN_GROUP);

        //==================================================
        // 16. グループ終了
        //==================================================
        testLayoutEndGroup.SetLayoutType(IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_END_GROUP);

        //==================================================
        // 17. 子領域開始
        //==================================================
        testLayoutBeginChild.SetLayoutType(IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_BEGIN_CHILD);
        testLayoutBeginChild.SetLayoutText("TestChild");
        testLayoutBeginChild.SetLayoutSize(ImVec2(300.0f, 100.0f));
        testLayoutBeginChild.SetLayoutChildFlags(ImGuiChildFlags_None);
        testLayoutBeginChild.SetLayoutWindowFlags(ImGuiWindowFlags_None);

        //==================================================
        // 18. 子領域終了
        //==================================================
        testLayoutEndChild.SetLayoutType(IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_END_CHILD);

        //==================================================
        // 19. 折りたたみ見出し
        //==================================================
        testLayoutCollapsingHeader.SetLayoutType(
            IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_COLLAPSING_HEADER);
        testLayoutCollapsingHeader.SetLayoutText(u8"折りたたみ見出し");
        testLayoutCollapsingHeader.SetLayoutTreeNodeFlags(ImGuiTreeNodeFlags_None);

        //==================================================
        // 20. ツリー項目
        //==================================================
        testLayoutTreeNode1.SetLayoutType(IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_TREE_NODE);
        testLayoutTreeNode1.SetLayoutText(u8"ツリーテスト");
        testLayoutTreeNode2 = testLayoutTreeNode1;

        //==================================================
        // 21. ツリー階層終了
        //==================================================
        testLayoutTreePop.SetLayoutType(IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_TREE_POP);

        //==================================================
        // 22. テーブル開始
        //==================================================
        testLayoutBeginTable.SetLayoutType(IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_BEGIN_TABLE);
        testLayoutBeginTable.SetLayoutText("TestTable");
        testLayoutBeginTable.SetLayoutCount(2);
        testLayoutBeginTable.SetLayoutTableFlags(ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg);
        testLayoutBeginTable.SetLayoutSize(ImVec2(0.0f, 0.0f));
        testLayoutBeginTable.SetLayoutWidth(0.0f);

        //==================================================
        // 23. テーブルの1列目を設定
        //==================================================
        testLayoutTableSetupColumn1.SetLayoutType(
            IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_TABLE_SETUP_COLUMN);
        testLayoutTableSetupColumn1.SetLayoutText(u8"項目");
        testLayoutTableSetupColumn1.SetLayoutTableColumnFlags(ImGuiTableColumnFlags_WidthStretch);
        testLayoutTableSetupColumn1.SetLayoutWidth(0.0f);
        testLayoutTableSetupColumn1.SetLayoutUserID(1);

        //==================================================
        // 24. テーブルの2列目を設定
        //==================================================
        testLayoutTableSetupColumn2.SetLayoutType(
            IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_TABLE_SETUP_COLUMN);
        testLayoutTableSetupColumn2.SetLayoutText(u8"値");
        testLayoutTableSetupColumn2.SetLayoutTableColumnFlags(ImGuiTableColumnFlags_WidthStretch);
        testLayoutTableSetupColumn2.SetLayoutWidth(0.0f);
        testLayoutTableSetupColumn2.SetLayoutUserID(2);

        //==================================================
        // 25. テーブルの見出し行
        //==================================================
        testLayoutTableHeadersRow.SetLayoutType(
            IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_TABLE_HEADERS_ROW);

        //==================================================
        // 26. テーブルの次の行
        //==================================================
        testLayoutTableNextRow.SetLayoutType(IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_TABLE_NEXT_ROW);
        testLayoutTableNextRow.SetLayoutCount(0);
        testLayoutTableNextRow.SetLayoutMinHeight(0.0f);

        //==================================================
        // 27. テーブルの次の列
        //==================================================
        testLayoutTableNextColumn.SetLayoutType(
            IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_TABLE_NEXT_COLUMN);

        //==================================================
        // 28. 指定した列に移動
        //==================================================
        testLayoutTableSetColumnIndex.SetLayoutType(
            IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_TABLE_SET_COLUMN_INDEX);
        testLayoutTableSetColumnIndex.SetLayoutIndex(0);

        //==================================================
        // 29. テーブル終了
        //==================================================
        testLayoutEndTable.SetLayoutType(IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_END_TABLE);

        //==================================================
        // 30. スタイル値の変更
        //==================================================
        testLayoutPushStyleVar.SetLayoutType(IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_PUSH_STYLE_VAR);
        testLayoutPushStyleVar.SetLayoutStyleVar(ImGuiStyleVar_ItemSpacing);
        testLayoutPushStyleVar.SetLayoutSize(ImVec2(10.0f, 10.0f));

        //==================================================
        // 31. スタイル値を元に戻す
        //==================================================
        testLayoutPopStyleVar.SetLayoutType(IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_POP_STYLE_VAR);

        //==================================================
        // 32. 文字色の変更
        //==================================================
        testLayoutPushStyleColor.SetLayoutType(IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_PUSH_STYLE_COLOR);
        testLayoutPushStyleColor.SetLayoutStyleColor(ImGuiCol_Text);
        testLayoutPushStyleColor.SetLayoutColor(ImVec4(1.0f, 0.2f, 0.2f, 1.0f));

        //==================================================
        // 33. 文字色を元に戻す
        //==================================================
        testLayoutPopStyleColor.SetLayoutType(IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_POP_STYLE_COLOR);

        //==================================================
        // 追加テキスト表示
        //==================================================
        testLayoutTextA.SetLayoutType(IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_TEXT);
        testLayoutTextA.SetLayoutText("NewLine Test A");

        testLayoutTextB.SetLayoutType(IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_TEXT);
        testLayoutTextB.SetLayoutText("NewLine Test B");

        testLayoutTextC.SetLayoutType(IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_TEXT);
        testLayoutTextC.SetLayoutText("Indent Test");

        testLayoutTextD.SetLayoutType(IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_TEXT);
        testLayoutTextD.SetLayoutText("Indented Text");

        testLayoutTextE.SetLayoutType(IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_TEXT);
        testLayoutTextE.SetLayoutText("Normal Position");

        testLayoutTextF.SetLayoutType(IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_TEXT);
        testLayoutTextF.SetLayoutText("Dummy Before");

        testLayoutTextG.SetLayoutType(IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_TEXT);
        testLayoutTextG.SetLayoutText("Dummy After");

        testLayoutTextH.SetLayoutType(IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_TEXT);
        testLayoutTextH.SetLayoutText("SetNextItemWidth Test");

        testLayoutTextI.SetLayoutType(IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_TEXT);
        testLayoutTextI.SetLayoutText("PushItemWidth Test");

        testLayoutTextJ.SetLayoutType(IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_TEXT);
        testLayoutTextJ.SetLayoutText("Aligned Text");

        testLayoutTextK.SetLayoutType(IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_TEXT);
        testLayoutTextK.SetLayoutText("Initially Open");

        testLayoutTextL.SetLayoutType(IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_TEXT);
        testLayoutTextL.SetLayoutText("Group Content A");

        testLayoutTextM.SetLayoutType(IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_TEXT);
        testLayoutTextM.SetLayoutText("Group Content B");

        testLayoutTextN.SetLayoutType(IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_TEXT);
        testLayoutTextN.SetLayoutText("Child Region Test");

        testLayoutTextO.SetLayoutType(IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_TEXT);
        testLayoutTextO.SetLayoutText("Header Content");

        testLayoutTextP.SetLayoutType(IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_TEXT);
        testLayoutTextP.SetLayoutText("Tree Content");

        testLayoutTextQ.SetLayoutType(IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_TEXT);
        testLayoutTextQ.SetLayoutText("Player");

        testLayoutTextR.SetLayoutType(IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_TEXT);
        testLayoutTextR.SetLayoutText("100");

        testLayoutTextS.SetLayoutType(IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_TEXT);
        testLayoutTextS.SetLayoutText("Enemy");

        testLayoutTextT.SetLayoutType(IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_TEXT);
        testLayoutTextT.SetLayoutText("80");

        testLayoutTextU.SetLayoutType(IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_TEXT);
        testLayoutTextU.SetLayoutText("Style Spacing Test A");

        testLayoutTextV.SetLayoutType(IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_TEXT);
        testLayoutTextV.SetLayoutText("Style Spacing Test B");

        testLayoutTextW.SetLayoutType(IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_TEXT);
        testLayoutTextW.SetLayoutText("Red Text Test");

        testLayoutTextX.SetLayoutType(IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_TEXT);
        testLayoutTextX.SetLayoutText("Child Button Test");

        //==================================================
        // ボタンテスト用変数の初期化
        //==================================================
        testLayoutButtonA.SetButtonType(IMGUI_BUTTON_TYPE::BUTTON);
        testLayoutButtonA.SetButtonLabel("Button A");
        testLayoutButtonA.SetButtonFlag(&testLayoutButtonAFlag);
        testLayoutButtonA.SetArgumentButtonFlag(&testLayoutButtonAArgumentFlag);

        testLayoutButtonB.SetButtonType(IMGUI_BUTTON_TYPE::BUTTON);
        testLayoutButtonB.SetButtonLabel("Button B");
        testLayoutButtonB.SetButtonFlag(&testLayoutButtonBFlag);
        testLayoutButtonB.SetArgumentButtonFlag(&testLayoutButtonBArgumentFlag);

        testLayoutButtonC.SetButtonType(IMGUI_BUTTON_TYPE::BUTTON);
        testLayoutButtonC.SetButtonLabel("Aligned Button");
        testLayoutButtonC.SetButtonFlag(&testLayoutButtonCFlag);
        testLayoutButtonC.SetArgumentButtonFlag(&testLayoutButtonCArgumentFlag);

        testLayoutButtonD.SetButtonType(IMGUI_BUTTON_TYPE::BUTTON);
        testLayoutButtonD.SetButtonLabel("Group Button A");
        testLayoutButtonD.SetButtonFlag(&testLayoutButtonDFlag);
        testLayoutButtonD.SetArgumentButtonFlag(&testLayoutButtonDArgumentFlag);

        testLayoutButtonE.SetButtonType(IMGUI_BUTTON_TYPE::BUTTON);
        testLayoutButtonE.SetButtonLabel("Group Button B");
        testLayoutButtonE.SetButtonFlag(&testLayoutButtonEFlag);
        testLayoutButtonE.SetArgumentButtonFlag(&testLayoutButtonEArgumentFlag);

        testLayoutButtonF.SetButtonType(IMGUI_BUTTON_TYPE::BUTTON);
        testLayoutButtonF.SetButtonLabel("Child Button");
        testLayoutButtonF.SetButtonFlag(&testLayoutButtonFFlag);
        testLayoutButtonF.SetArgumentButtonFlag(&testLayoutButtonFArgumentFlag);

        testLayoutButtonG.SetButtonType(IMGUI_BUTTON_TYPE::BUTTON);
        testLayoutButtonG.SetButtonLabel("Style Spacing Test A");
        testLayoutButtonG.SetButtonFlag(&testLayoutButtonGFlag);
        testLayoutButtonG.SetArgumentButtonFlag(&testLayoutButtonGArgumentFlag);

        testLayoutButtonH.SetButtonType(IMGUI_BUTTON_TYPE::BUTTON);
        testLayoutButtonH.SetButtonLabel("Style Spacing Test B");
        testLayoutButtonH.SetButtonFlag(&testLayoutButtonHFlag);
        testLayoutButtonH.SetArgumentButtonFlag(&testLayoutButtonHArgumentFlag);

        //==================================================
        // レイアウトテスト用ボタン
        //==================================================
        testLayoutButton.SetButtonType(IMGUI_BUTTON_TYPE::BUTTON);
        testLayoutButton.SetButtonLabel("Button");
        //testLayoutButton.ButtonImGuiEnumFlags = 0);
        testLayoutButton.SetButtonSize(ImVec2(0.0f, 0.0f));
        testLayoutButton.SetButtonDrawFlag(true);
        testLayoutButton.SetButtonFlag(&testLayoutButtonFlag);
        testLayoutButton.SetArgumentButtonFlag(&testLayoutButtonArgumentFlag);

        //==================================================
        // レイアウトテスト用数値入力
        //==================================================
        testLayoutInput = IMGUI_VARIABLE_CONTROL::GetImguiData(
            std::vector<int*>{ &testLayoutInputValue },
            1.0f,
            1.0f,
            100.0f,
            -1000,
            1000,
            "Layout Input",
            "%d",
            0,
            IMGUI_TYPE::INPUT1,
            false
        );

        testLayoutEndCollapsingHeader.SetLayoutType(IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_END_COLLAPSING_HEADER);
    }
    //==================================================
    // ImguiManager レイアウトテスト
    //==================================================
    void TestAllLayoutImgui()
    {
        // テキスト表示用のコピー
        IMGUI_LAYOUT_CONTROL testText = testLayoutText;

        //==================================================
        // 1. テキスト表示
        //==================================================
        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testLayoutText),
            IMGUI_GROUP_TYPE::TEST_1,
            "Layout Test"
        );

        //==================================================
        // 2. フォーマット付きテキスト
        //==================================================
        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testLayoutTextFormat),
            IMGUI_GROUP_TYPE::TEST_1,
            "Layout Test"
        );

        //==================================================
        // 3. 同じ行に配置
        //==================================================
        testLayoutButton.SetButtonLabel("Button A");
        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testLayoutButton),
            IMGUI_GROUP_TYPE::TEST_2,
            "Button Test"
        );

        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testLayoutSameLine),
            IMGUI_GROUP_TYPE::TEST_1,
            "Layout Test"
        );

        testLayoutButton.SetButtonLabel("Button B");
        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testLayoutButton),
            IMGUI_GROUP_TYPE::TEST_2,
            "Button Test"
        );

        //==================================================
        // 4. 水平線
        //==================================================
        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testLayoutSeparator),
            IMGUI_GROUP_TYPE::TEST_1,
            "Layout Test"
        );

        //==================================================
        // 5. 項目間の空白
        //==================================================
        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testLayoutSpacing),
            IMGUI_GROUP_TYPE::TEST_1,
            "Layout Test"
        );

        //==================================================
        // 6. 改行
        //==================================================
        testText.SetLayoutText("NewLine Test A");
        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testText),
            IMGUI_GROUP_TYPE::TEST_1,
            "Layout Test"
        );

        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testLayoutNewLine),
            IMGUI_GROUP_TYPE::TEST_1,
            "Layout Test"
        );

        testText.SetLayoutText("NewLine Test B");
        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testText),
            IMGUI_GROUP_TYPE::TEST_1,
            "Layout Test"
        );

        //==================================================
        // 7～8. 描画位置の調整
        //==================================================
        testText.SetLayoutText("Indent Test");
        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testText),
            IMGUI_GROUP_TYPE::TEST_1,
            "Layout Test"
        );

        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testLayoutIndent),
            IMGUI_GROUP_TYPE::TEST_1,
            "Layout Test"
        );

        testText.SetLayoutText("Indented Text");
        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testText),
            IMGUI_GROUP_TYPE::TEST_1,
            "Layout Test"
        );

        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testLayoutUnindent),
            IMGUI_GROUP_TYPE::TEST_1,
            "Layout Test"
        );

        testText.SetLayoutText("Normal Position");
        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testText),
            IMGUI_GROUP_TYPE::TEST_1,
            "Layout Test"
        );

        //==================================================
        // 9. 空白領域
        //==================================================
        testText.SetLayoutText("Dummy Before");
        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testText),
            IMGUI_GROUP_TYPE::TEST_1,
            "Layout Test"
        );

        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testLayoutDummy),
            IMGUI_GROUP_TYPE::TEST_1,
            "Layout Test"
        );

        testText.SetLayoutText("Dummy After");
        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testText),
            IMGUI_GROUP_TYPE::TEST_1,
            "Layout Test"
        );

        //==================================================
        // 10. 次の項目の幅を指定
        //==================================================
        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testLayoutSetNextItemWidth),
            IMGUI_GROUP_TYPE::TEST_1,
            "Layout Test"
        );

        testLayoutInput.SetLabel("SetNextItemWidth Test");
        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testLayoutInput),
            IMGUI_GROUP_TYPE::TEST_1,
            "Layout Test"
        );

        //==================================================
        // 11～12. 項目の幅を設定・復元
        //==================================================
        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testLayoutPushItemWidth),
            IMGUI_GROUP_TYPE::TEST_1,
            "Layout Test"
        );

        testLayoutInput.SetLabel("PushItemWidth Test");
        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testLayoutInput),
            IMGUI_GROUP_TYPE::TEST_1,
            "Layout Test"
        );

        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testLayoutPopItemWidth),
            IMGUI_GROUP_TYPE::TEST_1,
            "Layout Test"
        );

        //==================================================
        // 13. テキストの高さを合わせる
        //==================================================
        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testLayoutAlignTextToFramePadding),
            IMGUI_GROUP_TYPE::TEST_1,
            "Layout Test"
        );

        testText.SetLayoutText("Aligned Text");
        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testText),
            IMGUI_GROUP_TYPE::TEST_1,
            "Layout Test"
        );

        testLayoutButton.SetButtonLabel("Aligned Button");
        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testLayoutButton),
            IMGUI_GROUP_TYPE::TEST_2,
            "Button Test"
        );

        //==================================================
        // 14. ツリーの初期開閉状態
        //==================================================
        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testLayoutSetNextItemOpen),
            IMGUI_GROUP_TYPE::TEST_1,
            "Layout Test"
        );

        testLayoutTreeNode1.SetLayoutText("SetNextItemOpen Test");
        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testLayoutTreeNode1),
            IMGUI_GROUP_TYPE::TEST_1,
            "Layout Test"
        );

        testText.SetLayoutText("Initially Open");
        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testText),
            IMGUI_GROUP_TYPE::TEST_1,
            "Layout Test"
        );

        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testLayoutTreePop),
            IMGUI_GROUP_TYPE::TEST_1,
            "Layout Test"
        );

        //==================================================
        // 15～16. グループ
        //==================================================
        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testLayoutBeginGroup),
            IMGUI_GROUP_TYPE::TEST_1,
            "Layout Test"
        );

        testLayoutButton.SetButtonLabel("Group Button A");
        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testLayoutButton),
            IMGUI_GROUP_TYPE::TEST_2,
            "Button Test"
        );

        testLayoutButton.SetButtonLabel("Group Button B");
        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testLayoutButton),
            IMGUI_GROUP_TYPE::TEST_2,
            "Button Test"
        );

        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testLayoutEndGroup),
            IMGUI_GROUP_TYPE::TEST_1,
            "Layout Test"
        );

        //==================================================
        // 17～18. 子領域
        //==================================================
        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testLayoutBeginChild),
            IMGUI_GROUP_TYPE::TEST_1,
            "Layout Test"
        );

        testText.SetLayoutText("Child Region Test");
        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testText),
            IMGUI_GROUP_TYPE::TEST_1,
            "Layout Test"
        );

        testLayoutButton.SetButtonLabel("Child Button");
        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testLayoutButton),
            IMGUI_GROUP_TYPE::TEST_2,
            "Button Test"
        );

        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testLayoutEndChild),
            IMGUI_GROUP_TYPE::TEST_1,
            "Layout Test"
        );

        //==================================================
        // 19. 折りたたみ見出し
        //==================================================
        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testLayoutCollapsingHeader),
            IMGUI_GROUP_TYPE::TEST_1,
            "Layout Test"
        );

        testText.SetLayoutText("Header Content");
        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testText),
            IMGUI_GROUP_TYPE::TEST_1,
            "Layout Test"
        );
        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testLayoutEndCollapsingHeader),
            IMGUI_GROUP_TYPE::TEST_1,
            "Layout Test"
        );

        //==================================================
        // 20～21. ツリー
        //==================================================
        testLayoutTreeNode2.SetLayoutText("SetNextItemOpen Test 2");
        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testLayoutTreeNode2),
            IMGUI_GROUP_TYPE::TEST_1,
            "Layout Test"
        );

        testText.SetLayoutText("Tree Content");
        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testText),
            IMGUI_GROUP_TYPE::TEST_1,
            "Layout Test"
        );

        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testLayoutTreePop),
            IMGUI_GROUP_TYPE::TEST_1,
            "Layout Test"
        );

        //==================================================
        // 22～29. テーブル
        //==================================================
        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testLayoutBeginTable),
            IMGUI_GROUP_TYPE::TEST_1,
            "Layout Test"
        );

        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testLayoutTableSetupColumn1),
            IMGUI_GROUP_TYPE::TEST_1,
            "Layout Test"
        );

        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testLayoutTableSetupColumn2),
            IMGUI_GROUP_TYPE::TEST_1,
            "Layout Test"
        );

        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testLayoutTableHeadersRow),
            IMGUI_GROUP_TYPE::TEST_1,
            "Layout Test"
        );

        // 1行目
        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testLayoutTableNextRow),
            IMGUI_GROUP_TYPE::TEST_1,
            "Layout Test"
        );

        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testLayoutTableSetColumnIndex),
            IMGUI_GROUP_TYPE::TEST_1,
            "Layout Test"
        );

        testText.SetLayoutText("Player");
        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testText),
            IMGUI_GROUP_TYPE::TEST_1,
            "Layout Test"
        );

        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testLayoutTableNextColumn),
            IMGUI_GROUP_TYPE::TEST_1,
            "Layout Test"
        );

        testText.SetLayoutText("100");
        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testText),
            IMGUI_GROUP_TYPE::TEST_1,
            "Layout Test"
        );

        // 2行目
        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testLayoutTableNextRow),
            IMGUI_GROUP_TYPE::TEST_1,
            "Layout Test"
        );

        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testLayoutTableSetColumnIndex),
            IMGUI_GROUP_TYPE::TEST_1,
            "Layout Test"
        );

        testText.SetLayoutText("Enemy");
        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testText),
            IMGUI_GROUP_TYPE::TEST_1,
            "Layout Test"
        );

        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testLayoutTableNextColumn),
            IMGUI_GROUP_TYPE::TEST_1,
            "Layout Test"
        );

        testText.SetLayoutText("80");
        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testText),
            IMGUI_GROUP_TYPE::TEST_1,
            "Layout Test"
        );

        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testLayoutEndTable),
            IMGUI_GROUP_TYPE::TEST_1,
            "Layout Test"
        );

        //==================================================
        // 30～31. スタイル値の変更・復元
        //==================================================
        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testLayoutPushStyleVar),
            IMGUI_GROUP_TYPE::TEST_1,
            "Layout Test"
        );

        testLayoutButton.SetButtonLabel("Style Spacing Test A");
        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testLayoutButton),
            IMGUI_GROUP_TYPE::TEST_2,
            "Button Test"
        );

        testLayoutButton.SetButtonLabel("Style Spacing Test B");
        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testLayoutButton),
            IMGUI_GROUP_TYPE::TEST_2,
            "Button Test"
        );

        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testLayoutPopStyleVar),
            IMGUI_GROUP_TYPE::TEST_1,
            "Layout Test"
        );

        //==================================================
        // 32～33. 文字色の変更・復元
        //==================================================
        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testLayoutPushStyleColor),
            IMGUI_GROUP_TYPE::TEST_1,
            "Layout Test"
        );

        testText.SetLayoutText("Red Text Test");
        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testText),
            IMGUI_GROUP_TYPE::TEST_1,
            "Layout Test"
        );

        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testLayoutPopStyleColor),
            IMGUI_GROUP_TYPE::TEST_1,
            "Layout Test"
        );

        //==================================================
        // ツリーの入れ子・描画制御テスト
        //==================================================
        testLayoutTreeNode1.SetLayoutText("Parent Tree");
        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testLayoutTreeNode1),
            IMGUI_GROUP_TYPE::TEST_1,
            "Layout Test"
        );

        testText.SetLayoutText("Parent Content");
        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testText),
            IMGUI_GROUP_TYPE::TEST_1,
            "Layout Test"
        );

        testLayoutTreeNode2.SetLayoutText("Child Tree");
        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testLayoutTreeNode2),
            IMGUI_GROUP_TYPE::TEST_1,
            "Layout Test"
        );

        testText.SetLayoutText("Child Content");
        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testText),
            IMGUI_GROUP_TYPE::TEST_1,
            "Layout Test"
        );

        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testLayoutTreePop),
            IMGUI_GROUP_TYPE::TEST_1,
            "Layout Test"
        );
        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testLayoutTreePop),
            IMGUI_GROUP_TYPE::TEST_1,
            "Layout Test"
        );

        testText.SetLayoutText("Outside Tree");
        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testText),
            IMGUI_GROUP_TYPE::TEST_1,
            "Layout Test"
        );

        //==================================================
        // 折りたたみ見出し・入れ子テスト
        //==================================================
        testLayoutCollapsingHeader.SetLayoutText("Parent Header");
        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testLayoutCollapsingHeader),
            IMGUI_GROUP_TYPE::TEST_1,
            "Layout Test"
        );

        testText.SetLayoutText("Parent Header Content");
        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testText),
            IMGUI_GROUP_TYPE::TEST_1,
            "Layout Test"
        );

        testLayoutCollapsingHeader.SetLayoutText("Child Header");
        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testLayoutCollapsingHeader),
            IMGUI_GROUP_TYPE::TEST_1,
            "Layout Test"
        );

        testText.SetLayoutText("Child Header Content");
        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testText),
            IMGUI_GROUP_TYPE::TEST_1,
            "Layout Test"
        );

        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testLayoutEndCollapsingHeader),
            IMGUI_GROUP_TYPE::TEST_1,
            "Layout Test"
        );
        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testLayoutEndCollapsingHeader),
            IMGUI_GROUP_TYPE::TEST_1,
            "Layout Test"
        );

        testText.SetLayoutText("Outside Header");
        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testText),
            IMGUI_GROUP_TYPE::TEST_1,
            "Layout Test"
        );

        //==================================================
        // テーブル・描画制御テスト
        //==================================================
        testLayoutBeginTable.SetLayoutText("TestTable");
        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testLayoutBeginTable),
            IMGUI_GROUP_TYPE::TEST_1,
            "Layout Test"
        );

        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testLayoutTableSetupColumn1),
            IMGUI_GROUP_TYPE::TEST_1,
            "Layout Test"
        );
        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testLayoutTableSetupColumn2),
            IMGUI_GROUP_TYPE::TEST_1,
            "Layout Test"
        );
        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testLayoutTableHeadersRow),
            IMGUI_GROUP_TYPE::TEST_1,
            "Layout Test"
        );

        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testLayoutTableNextRow),
            IMGUI_GROUP_TYPE::TEST_1,
            "Layout Test"
        );
        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testLayoutTableNextColumn),
            IMGUI_GROUP_TYPE::TEST_1,
            "Layout Test"
        );

        testText.SetLayoutText("Table Content");
        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testText),
            IMGUI_GROUP_TYPE::TEST_1,
            "Layout Test"
        );

        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testLayoutEndTable),
            IMGUI_GROUP_TYPE::TEST_1,
            "Layout Test"
        );

        testText.SetLayoutText("Outside Table");
        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testText),
            IMGUI_GROUP_TYPE::TEST_1,
            "Layout Test"
        );

        //==================================================
        // 複合レイアウト・描画制御テスト
        //==================================================
        testLayoutTreeNode1.SetLayoutText("Parent Tree");
        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testLayoutTreeNode1),
            IMGUI_GROUP_TYPE::TEST_1,
            "Layout Test"
        );

        testText.SetLayoutText("Parent Content");
        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testText),
            IMGUI_GROUP_TYPE::TEST_1,
            "Layout Test"
        );

        // ツリー内の折りたたみ見出し
        testLayoutCollapsingHeader.SetLayoutText("Nested Header");
        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testLayoutCollapsingHeader),
            IMGUI_GROUP_TYPE::TEST_1,
            "Layout Test"
        );

        testText.SetLayoutText("Nested Header Content");
        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testText),
            IMGUI_GROUP_TYPE::TEST_1,
            "Layout Test"
        );

        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testLayoutEndCollapsingHeader),
            IMGUI_GROUP_TYPE::TEST_1,
            "Layout Test"
        );

        // ツリー内の子ツリー
        testLayoutTreeNode2.SetLayoutText("Nested Tree");
        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testLayoutTreeNode2),
            IMGUI_GROUP_TYPE::TEST_1,
            "Layout Test"
        );

        testText.SetLayoutText("Nested Tree Content");
        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testText),
            IMGUI_GROUP_TYPE::TEST_1,
            "Layout Test"
        );

        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testLayoutTreePop),
            IMGUI_GROUP_TYPE::TEST_1,
            "Layout Test"
        );

        // 親ツリーを終了
        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testLayoutTreePop),
            IMGUI_GROUP_TYPE::TEST_1,
            "Layout Test"
        );

        // すべてのレイアウト終了後
        testText.SetLayoutText("Outside All Layouts");
        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testText),
            IMGUI_GROUP_TYPE::TEST_1,
            "Layout Test"
        );
    }

    //==================================================
    // ImguiManager ボタンテスト用変数
    //==================================================
    // ボタンの状態保持用変数。描画側に渡す構造体がコピーされても状態を共有できるようにする。
    bool testButton1Flag = false, testButton1ArgumentFlag = false;
    bool testButton2Flag = false, testButton2ArgumentFlag = false;
    bool testButton3Flag = false, testButton3ArgumentFlag = false;
    bool testButton4Flag = false, testButton4ArgumentFlag = false;
    bool testButton5Flag = false, testButton5ArgumentFlag = false;
    unsigned int testButton6BitFlag = 0;
    bool testButton6Flag = false, testButton6ArgumentFlag = false;
    bool testButton7Flag = false, testButton7ArgumentFlag = false;
    bool testButton8Flag = false, testButton8ArgumentFlag = false;
    bool testButton9Flag = false, testButton9ArgumentFlag = false;
    bool testButton10Flag = false, testButton10ArgumentFlag = false;
    bool testButton11Flag = false, testButton11ArgumentFlag = false;
    bool testButton12Flag = false, testButton12ArgumentFlag = false;
    bool testButton13Flag = false, testButton13ArgumentFlag = false;

    IMGUI_BUTTON_CONTROL testButton1;
    IMGUI_BUTTON_CONTROL testButton2;
    IMGUI_BUTTON_CONTROL testButton3;
    IMGUI_BUTTON_CONTROL testButton4;
    IMGUI_BUTTON_CONTROL testButton5;
    IMGUI_BUTTON_CONTROL testButton6;
    IMGUI_BUTTON_CONTROL testButton7;
    IMGUI_BUTTON_CONTROL testButton8;
    IMGUI_BUTTON_CONTROL testButton9;
    IMGUI_BUTTON_CONTROL testButton10;
    IMGUI_BUTTON_CONTROL testButton11;
    IMGUI_BUTTON_CONTROL testButton12;
    IMGUI_BUTTON_CONTROL testButton13;
    //==================================================
    // ImguiManager ボタンテスト用変数の初期化
    //==================================================
    void InitializeTestAllButtonImgui()
    {
        //==================================================
        // 1. 標準ボタン
        //==================================================
        testButton1.SetButtonType(IMGUI_BUTTON_TYPE::BUTTON);
        testButton1.SetButtonLabel("Normal Button");
        testButton1.SetButtonFlag(&testButton1Flag);
        testButton1.SetArgumentButtonFlag(&testButton1ArgumentFlag);
        testButton1.SetButtonSize(ImVec2(150.0f, 30.0f));

        //==================================================
        // 2. 小型ボタン
        //==================================================
        testButton2.SetButtonType(IMGUI_BUTTON_TYPE::SMALL_BUTTON);
        testButton2.SetButtonLabel("Small Button");
        testButton2.SetButtonFlag(&testButton2Flag);
        testButton2.SetArgumentButtonFlag(&testButton2ArgumentFlag);

        //==================================================
        // 3. 矢印ボタン
        //==================================================
        testButton3.SetButtonType(IMGUI_BUTTON_TYPE::ARROW_BUTTON);
        testButton3.SetButtonLabel("Arrow");
        testButton3.SetButtonFlag(&testButton3Flag);
        testButton3.SetArgumentButtonFlag(&testButton3ArgumentFlag);
        testButton3.SetButtonDir(ImGuiDir_Right);

        //==================================================
        // 4. 透明ボタン
        //==================================================
        testButton4.SetButtonType(IMGUI_BUTTON_TYPE::INVISIBLE_BUTTON);
        testButton4.SetButtonLabel("Invisible");
        testButton4.SetButtonFlag(&testButton4Flag);
        testButton4.SetArgumentButtonFlag(&testButton4ArgumentFlag);
        testButton4.SetButtonSize(ImVec2(150.0f, 30.0f));
        testButton4.SetButtonFlags(ImGuiButtonFlags_None);

        //==================================================
        // 5. チェックボックス
        //==================================================
        testButton5.SetButtonType(IMGUI_BUTTON_TYPE::CHECK_BOX);
        testButton5.SetButtonLabel("Check Box");
        testButton5.SetButtonFlag(&testButton5Flag);
        testButton5.SetArgumentButtonFlag(&testButton5ArgumentFlag);

        //==================================================
        // 6. ビットフラグ用チェックボックス
        //==================================================
        testButton6.SetButtonType(IMGUI_BUTTON_TYPE::CHECK_BOX_FLAGS);
        testButton6.SetButtonLabel("Flag Bit");
        testButton6.SetButtonFlag(&testButton6Flag);
        testButton6.SetArgumentButtonFlag(&testButton6ArgumentFlag);
        testButton6.SetButtonBitFlag(&testButton6BitFlag);
        testButton6BitFlag = 0u;
        testButton6.SetButtonBitFlagValue(1u);

        //==================================================
        // 7. ラジオボタン
        //==================================================
        testButton7.SetButtonType(IMGUI_BUTTON_TYPE::RADIO_BUTTON);
        testButton7.SetButtonLabel("Radio Button");
        testButton7.SetButtonFlag(&testButton7Flag);
        testButton7.SetArgumentButtonFlag(&testButton7ArgumentFlag);

        //==================================================
        // 8. 色ボタン
        //==================================================
        testButton8.SetButtonType(IMGUI_BUTTON_TYPE::COLOR_BUTTON);
        testButton8.SetButtonLabel("Color Button");
        testButton8.SetButtonFlag(&testButton8Flag);
        testButton8.SetArgumentButtonFlag(&testButton8ArgumentFlag);
        testButton8.SetButtonColor(ImVec4(1.0f, 0.2f, 0.2f, 1.0f));
        testButton8.SetButtonSize(ImVec2(100.0f, 30.0f));
        testButton8.SetButtonColorEditFlags(ImGuiColorEditFlags_None);

        //==================================================
        // 9. 選択可能項目
        //==================================================
        testButton9.SetButtonType(IMGUI_BUTTON_TYPE::SELECTABLE);
        testButton9.SetButtonLabel("Selectable Item");
        testButton9.SetButtonFlag(&testButton9Flag);
        testButton9.SetArgumentButtonFlag(&testButton9ArgumentFlag);
        testButton9.SetButtonSelectableFlags(ImGuiSelectableFlags_None);

        //==================================================
        // 10. メニュー項目
        //==================================================
        testButton10.SetButtonType(IMGUI_BUTTON_TYPE::MENU_ITEM);
        testButton10.SetButtonLabel("Menu Item");
        testButton10.SetButtonFlag(&testButton10Flag);
        testButton10.SetArgumentButtonFlag(&testButton10ArgumentFlag);
        testButton10.SetPressKeyString("Ctrl+T");
        testButton10.SetButtonDrawFlag(true);

        //==================================================
        // 11. タブバー内のボタン
        //==================================================
        testButton11.SetButtonType(IMGUI_BUTTON_TYPE::TABITEM_BUTTON);
        testButton11.SetButtonLabel("Tab Action");
        testButton11.SetButtonFlag(&testButton11Flag);
        testButton11.SetArgumentButtonFlag(&testButton11ArgumentFlag);
        testButton11.SetButtonTabItemFlags(ImGuiTabItemFlags_None);

        //==================================================
        // 12. テキストリンク
        //==================================================
        testButton12.SetButtonType(IMGUI_BUTTON_TYPE::TEXT_LINK);
        testButton12.SetButtonLabel("Text Link");
        testButton12.SetButtonFlag(&testButton12Flag);
        testButton12.SetArgumentButtonFlag(&testButton12ArgumentFlag);

        //==================================================
        // 13. URLを開くテキストリンク
        //==================================================
        testButton13.SetButtonType(IMGUI_BUTTON_TYPE::TEXT_LINK_OPEN_URL);
        testButton13.SetButtonLabel("Open OpenAI Website");
        testButton13.SetButtonFlag(&testButton13Flag);
        testButton13.SetArgumentButtonFlag(&testButton13ArgumentFlag);
        testButton13.SetUrl("https://openai.com/");
    }
    //==================================================
    // ImguiManager ボタンテスト
    //==================================================
    // ボタンテスト用テキストをImguiManager経由で登録
    void AddTestButtonText(const std::string& text)
    {
        IMGUI_LAYOUT_CONTROL layoutText;
        layoutText.SetLayoutType(IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_TEXT);
        layoutText.SetLayoutText(text);

        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(layoutText),
            IMGUI_GROUP_TYPE::TEST_2,
            "Button Test"
        );
    }


    void TestAllButtonImgui()
    {
        //==================================================
        // 1. 標準ボタン
        //==================================================
        AddTestButtonText(u8"1. BUTTON試し");
        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testButton1),
            IMGUI_GROUP_TYPE::TEST_2,
            "Button Test"
        );
        AddTestButtonText(testButton1ArgumentFlag ? "Pressed: true" : "Pressed: false");

        //==================================================
        // 2. 小型ボタン
        //==================================================
        AddTestButtonText(u8"2. SMALL_BUTTON");
        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testButton2),
            IMGUI_GROUP_TYPE::TEST_2,
            "Button Test"
        );
        AddTestButtonText(testButton2ArgumentFlag ? "Pressed: true" : "Pressed: false");

        //==================================================
        // 3. 矢印ボタン
        //==================================================
        AddTestButtonText(u8"3. ARROW_BUTTON");
        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testButton3),
            IMGUI_GROUP_TYPE::TEST_2,
            "Button Test"
        );
        AddTestButtonText(testButton3ArgumentFlag ? "Pressed: true" : "Pressed: false");

        //==================================================
        // 4. 透明ボタン
        //==================================================
        AddTestButtonText(u8"4. INVISIBLE_BUTTON");
        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testButton4),
            IMGUI_GROUP_TYPE::TEST_2,
            "Button Test"
        );
        AddTestButtonText(testButton4ArgumentFlag ? "Pressed: true" : "Pressed: false");

        //==================================================
        // 5. チェックボックス
        //==================================================
        AddTestButtonText(u8"5. CHECK_BOX");
        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testButton5),
            IMGUI_GROUP_TYPE::TEST_2,
            "Button Test"
        );
        AddTestButtonText(testButton5ArgumentFlag ? "Changed: true" : "Changed: false");
        AddTestButtonText(testButton5Flag ? "State: ON" : "State: OFF");

        //==================================================
        // 6. ビットフラグ用チェックボックス
        //==================================================
        AddTestButtonText(u8"6. CHECK_BOX_FLAGS");
        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testButton6),
            IMGUI_GROUP_TYPE::TEST_2,
            "Button Test"
        );
        AddTestButtonText(u8"Flags: " + std::to_string(testButton6BitFlag));

        //==================================================
        // 7. ラジオボタン
        //==================================================
        AddTestButtonText(u8"7. RADIO_BUTTON");
        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testButton7),
            IMGUI_GROUP_TYPE::TEST_2,
            "Button Test"
        );
        AddTestButtonText(testButton7ArgumentFlag ? "Changed: true" : "Changed: false");

        //==================================================
        // 8. 色ボタン
        //==================================================
        AddTestButtonText(u8"8. COLOR_BUTTON");
        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testButton8),
            IMGUI_GROUP_TYPE::TEST_2,
            "Button Test"
        );
        AddTestButtonText(testButton8ArgumentFlag ? "Pressed: true" : "Pressed: false");

        //==================================================
        // 9. 選択可能項目
        //==================================================
        AddTestButtonText(u8"9. SELECTABLE");
        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testButton9),
            IMGUI_GROUP_TYPE::TEST_2,
            "Button Test"
        );
        AddTestButtonText(testButton9Flag ? "Selected: true" : "Selected: false");

        //==================================================
        // 10. メニュー項目
        // ImguiManagerのグループAPIにメニュー開始・終了がないため、項目を直接登録
        //==================================================
        AddTestButtonText(u8"10. MENU_ITEM");
        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testButton10),
            IMGUI_GROUP_TYPE::TEST_2,
            "Button Test"
        );
        AddTestButtonText(testButton10Flag ? "Selected: true" : "Selected: false");

        //==================================================
        // 11. タブバー内のボタン
        // ImguiManagerのグループAPIにタブバー開始・終了がないため、ボタンを直接登録
        //==================================================
        AddTestButtonText(u8"11. TABITEM_BUTTON");
        // タブバー開始
        IMGUI_LAYOUT_CONTROL beginTabBar;
        beginTabBar.SetLayoutType(IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_BEGIN_TAB_BAR);
        beginTabBar.SetLayoutText("TestTabBar");
        beginTabBar.SetLayoutStyleTabBarFlags(ImGuiTabBarFlags_None);
        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(beginTabBar),
            IMGUI_GROUP_TYPE::TEST_2,
            "Button Test"
        );
        // タブバー内のボタン
        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testButton11),
            IMGUI_GROUP_TYPE::TEST_2,
            "Button Test"
        );
        AddTestButtonText(testButton11ArgumentFlag ? "Pressed: true" : "Pressed: false");
        // タブバー終了
        IMGUI_LAYOUT_CONTROL endTabBar;
        endTabBar.SetLayoutType(IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_END_TAB_BAR);
        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(endTabBar),
            IMGUI_GROUP_TYPE::TEST_2,
            "Button Test"
        );
        //==================================================
        // 12. テキストリンク
        //==================================================
        AddTestButtonText(u8"12. TEXT_LINK");
        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testButton12),
            IMGUI_GROUP_TYPE::TEST_2,
            "Button Test"
        );
        AddTestButtonText(testButton12ArgumentFlag ? "Pressed: true" : "Pressed: false");

        //==================================================
        // 13. URLを開くテキストリンク
        //==================================================
        AddTestButtonText(u8"13. TEXT_LINK_OPEN_URL");
        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testButton13),
            IMGUI_GROUP_TYPE::TEST_2,
            "Button Test"
        );
    }


    //==================================================
    // ImguiManager 整数型変数テスト用グローバル変数
    //==================================================
    // SLIDER
    int testVariableIntegerSlider1 = 10;
    int testVariableIntegerSlider2[2] = { 10, 20 };
    int testVariableIntegerSlider3[3] = { 10, 20, 30 };
    int testVariableIntegerSlider4[4] = { 10, 20, 30, 40 };

    // DRAG
    int testVariableIntegerDrag1 = 10;
    int testVariableIntegerDrag2[2] = { 10, 20 };
    int testVariableIntegerDrag3[3] = { 10, 20, 30 };
    int testVariableIntegerDrag4[4] = { 10, 20, 30, 40 };

    // INPUT
    int testVariableIntegerInput1 = 10;
    int testVariableIntegerInput2[2] = { 10, 20 };
    int testVariableIntegerInput3[3] = { 10, 20, 30 };
    int testVariableIntegerInput4[4] = { 10, 20, 30, 40 };

    // ImguiManager 整数型変数テスト用コントロール
    IMGUI_VARIABLE_CONTROL testVariableIntegerSliderControl1;
    IMGUI_VARIABLE_CONTROL testVariableIntegerSliderControl2;
    IMGUI_VARIABLE_CONTROL testVariableIntegerSliderControl3;
    IMGUI_VARIABLE_CONTROL testVariableIntegerSliderControl4;

    IMGUI_VARIABLE_CONTROL testVariableIntegerDragControl1;
    IMGUI_VARIABLE_CONTROL testVariableIntegerDragControl2;
    IMGUI_VARIABLE_CONTROL testVariableIntegerDragControl3;
    IMGUI_VARIABLE_CONTROL testVariableIntegerDragControl4;

    IMGUI_VARIABLE_CONTROL testVariableIntegerInputControl1;
    IMGUI_VARIABLE_CONTROL testVariableIntegerInputControl2;
    IMGUI_VARIABLE_CONTROL testVariableIntegerInputControl3;
    IMGUI_VARIABLE_CONTROL testVariableIntegerInputControl4;

    //==================================================
    // ImguiManager 整数型変数テスト用初期化
    //==================================================
    void InitializeTestAllVariableIntegerImgui()
    {
        //==================================================
        // SLIDER
        //==================================================
        testVariableIntegerSliderControl1 = IMGUI_VARIABLE_CONTROL::GetImguiData(
            { &testVariableIntegerSlider1 },
            1.0f, 1.0f, 10.0f,
            0, 100,
            "Integer Slider 1",
            "%d",
            0,
            IMGUI_TYPE::SLIDER1,
            false
        );

        testVariableIntegerSliderControl2 = IMGUI_VARIABLE_CONTROL::GetImguiData(
            { &testVariableIntegerSlider2[0], &testVariableIntegerSlider2[1] },
            1.0f, 1.0f, 10.0f,
            0, 100,
            "Integer Slider 2",
            "%d",
            0,
            IMGUI_TYPE::SLIDER2,
            false
        );

        testVariableIntegerSliderControl3 = IMGUI_VARIABLE_CONTROL::GetImguiData(
            { &testVariableIntegerSlider3[0], &testVariableIntegerSlider3[1], &testVariableIntegerSlider3[2] },
            1.0f, 1.0f, 10.0f,
            0, 100,
            "Integer Slider 3",
            "%d",
            0,
            IMGUI_TYPE::SLIDER3,
            false
        );

        testVariableIntegerSliderControl4 = IMGUI_VARIABLE_CONTROL::GetImguiData(
            { &testVariableIntegerSlider4[0], &testVariableIntegerSlider4[1], &testVariableIntegerSlider4[2], &testVariableIntegerSlider4[3] },
            1.0f, 1.0f, 10.0f,
            0, 100,
            "Integer Slider 4",
            "%d",
            0,
            IMGUI_TYPE::SLIDER4,
            false
        );

        //==================================================
        // DRAG
        //==================================================
        testVariableIntegerDragControl1 = IMGUI_VARIABLE_CONTROL::GetImguiData(
            { &testVariableIntegerDrag1 },
            1.0f, 1.0f, 10.0f,
            0, 100,
            "Integer Drag 1",
            "%d",
            0,
            IMGUI_TYPE::DRAG1,
            false
        );

        testVariableIntegerDragControl2 = IMGUI_VARIABLE_CONTROL::GetImguiData(
            { &testVariableIntegerDrag2[0], &testVariableIntegerDrag2[1] },
            1.0f, 1.0f, 10.0f,
            0, 100,
            "Integer Drag 2",
            "%d",
            0,
            IMGUI_TYPE::DRAG2,
            false
        );

        testVariableIntegerDragControl3 = IMGUI_VARIABLE_CONTROL::GetImguiData(
            { &testVariableIntegerDrag3[0], &testVariableIntegerDrag3[1], &testVariableIntegerDrag3[2] },
            1.0f, 1.0f, 10.0f,
            0, 100,
            "Integer Drag 3",
            "%d",
            0,
            IMGUI_TYPE::DRAG3,
            false
        );

        testVariableIntegerDragControl4 = IMGUI_VARIABLE_CONTROL::GetImguiData(
            { &testVariableIntegerDrag4[0], &testVariableIntegerDrag4[1], &testVariableIntegerDrag4[2], &testVariableIntegerDrag4[3] },
            1.0f, 1.0f, 10.0f,
            0, 100,
            "Integer Drag 4",
            "%d",
            0,
            IMGUI_TYPE::DRAG4,
            false
        );

        //==================================================
        // INPUT
        //==================================================
        testVariableIntegerInputControl1 = IMGUI_VARIABLE_CONTROL::GetImguiData(
            { &testVariableIntegerInput1 },
            1.0f, 1.0f, 10.0f,
            0, 100,
            "Integer Input 1",
            "%d",
            0,
            IMGUI_TYPE::INPUT1,
            false
        );

        testVariableIntegerInputControl2 = IMGUI_VARIABLE_CONTROL::GetImguiData(
            { &testVariableIntegerInput2[0], &testVariableIntegerInput2[1] },
            1.0f, 1.0f, 10.0f,
            0, 100,
            "Integer Input 2",
            "%d",
            0,
            IMGUI_TYPE::INPUT2,
            false
        );

        testVariableIntegerInputControl3 = IMGUI_VARIABLE_CONTROL::GetImguiData(
            { &testVariableIntegerInput3[0], &testVariableIntegerInput3[1], &testVariableIntegerInput3[2] },
            1.0f, 1.0f, 10.0f,
            0, 100,
            "Integer Input 3",
            "%d",
            0,
            IMGUI_TYPE::INPUT3,
            false
        );

        testVariableIntegerInputControl4 = IMGUI_VARIABLE_CONTROL::GetImguiData(
            { &testVariableIntegerInput4[0], &testVariableIntegerInput4[1], &testVariableIntegerInput4[2], &testVariableIntegerInput4[3] },
            1.0f, 1.0f, 10.0f,
            0, 100,
            "Integer Input 4",
            "%d",
            0,
            IMGUI_TYPE::INPUT4,
            false
        );
    }

    //==================================================
    // ImguiManager 整数型変数テスト更新
    //==================================================
    // 毎フレーム呼び出し、現在のグローバル変数を編集できる項目として登録する。
    // AddDrawImguiGroup は初期化関数では呼び出さない。
    void TestAllVariableIntegerImgui()
    {
        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testVariableIntegerSliderControl1),
            IMGUI_GROUP_TYPE::TEST_3,
            "Variable Integer Test"
        );
        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testVariableIntegerSliderControl2),
            IMGUI_GROUP_TYPE::TEST_3,
            "Variable Integer Test"
        );
        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testVariableIntegerSliderControl3),
            IMGUI_GROUP_TYPE::TEST_3,
            "Variable Integer Test"
        );
        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testVariableIntegerSliderControl4),
            IMGUI_GROUP_TYPE::TEST_3,
            "Variable Integer Test"
        );

        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testVariableIntegerDragControl1),
            IMGUI_GROUP_TYPE::TEST_3,
            "Variable Integer Test"
        );
        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testVariableIntegerDragControl2),
            IMGUI_GROUP_TYPE::TEST_3,
            "Variable Integer Test"
        );
        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testVariableIntegerDragControl3),
            IMGUI_GROUP_TYPE::TEST_3,
            "Variable Integer Test"
        );
        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testVariableIntegerDragControl4),
            IMGUI_GROUP_TYPE::TEST_3,
            "Variable Integer Test"
        );

        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testVariableIntegerInputControl1),
            IMGUI_GROUP_TYPE::TEST_3,
            "Variable Integer Test"
        );
        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testVariableIntegerInputControl2),
            IMGUI_GROUP_TYPE::TEST_3,
            "Variable Integer Test"
        );
        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testVariableIntegerInputControl3),
            IMGUI_GROUP_TYPE::TEST_3,
            "Variable Integer Test"
        );
        Master::mpImguiManager->AddDrawImguiGroup(
            IMGUI_ALL_DRAW_ONE_DATA(testVariableIntegerInputControl4),
            IMGUI_GROUP_TYPE::TEST_3,
            "Variable Integer Test"
        );
    }
#endif

    void InitializeTestAll()
    {
#ifdef _DEBUG
        InitializeTestAllLayoutImgui();
        InitializeTestAllButtonImgui();
        InitializeTestAllVariableIntegerImgui();
#endif
    }

#ifdef _DEBUG
    bool IsTestDraw = true;
#endif

    void ResetTestDrawFlag()
    {
#ifdef _DEBUG
        IsTestDraw = true;
#endif
    }

    void DrawTestAllImgui()
    {
#ifdef _DEBUG
        if (IsTestDraw)
        {
            TEST_IMGUI_MANAGER::TestAllLayoutImgui();
            TEST_IMGUI_MANAGER::TestAllButtonImgui();
            TEST_IMGUI_MANAGER::TestAllVariableIntegerImgui();
            IsTestDraw = false;
        }
#endif
    }
}
*/