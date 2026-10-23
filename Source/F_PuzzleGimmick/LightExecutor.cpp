#include "LightExecutor.h"

#include "DxLib.h"

#include "../A_GameObject/GameObject2D.h"

#include "../E_Scene/BaseScene.h"
#include "../E_Scene/BaseSceneManager.h"

#include "../G_LightArea/LightLineNode.h"
#include "../G_LightArea/LightArea.h"
#include "../G_LightArea/LightAreaManager.h"

#include "../S_Collision/BaseCollision2D.h"
#include "../S_Collision/Ray2D.h"
#include "../S_Collision/BaseCollision2DManager.h"

#include "../Y_Tool/MyFunctions.h"

#include "../Z_Except/Master.h"
#include "DrawSystem.h"

int gnDebugTest = 0;

#include "ImguiManager.h"

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
    testLayoutText.LayoutType = IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_TEXT;
    testLayoutText.LayoutText = u8"レイアウトテスト";

    //==================================================
    // 2. フォーマット付きテキスト
    //==================================================
    testLayoutTextFormat.LayoutType = IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_TEXT_FORMAT;
    testLayoutTextFormat.LayoutText = u8"整数値: %d";
    testLayoutTextFormat.LayoutVarable = IMGUI_VARIABLE_DATA(123); // IMGUI_VARIABLE_DATAの実際の設定方法に合わせて変更

    //==================================================
    // 3. 同じ行に配置
    //==================================================
    testLayoutSameLine.LayoutType = IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_SAME_LINE;
    testLayoutSameLine.LayoutWidth = 0.0f;
    testLayoutSameLine.LayoutSpacing = -1.0f;

    //==================================================
    // 4. 水平線
    //==================================================
    testLayoutSeparator.LayoutType = IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_SEPARATOR;

    //==================================================
    // 5. 項目間の空白
    //==================================================
    testLayoutSpacing.LayoutType = IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_SPACING;

    //==================================================
    // 6. 改行
    //==================================================
    testLayoutNewLine.LayoutType = IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_NEW_LINE;

    //==================================================
    // 7. 描画位置を右にずらす
    //==================================================
    testLayoutIndent.LayoutType = IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_INDENT;
    testLayoutIndent.LayoutWidth = 30.0f;

    //==================================================
    // 8. 描画位置を戻す
    //==================================================
    testLayoutUnindent.LayoutType = IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_UNINDENT;
    testLayoutUnindent.LayoutWidth = 30.0f;

    //==================================================
    // 9. 空白領域
    //==================================================
    testLayoutDummy.LayoutType = IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_DUMMY;
    testLayoutDummy.LayoutSize = ImVec2(100.0f, 20.0f);

    //==================================================
    // 10. 次の項目の幅を指定
    //==================================================
    testLayoutSetNextItemWidth.LayoutType = IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_SET_NEXT_ITEM_WIDTH;
    testLayoutSetNextItemWidth.LayoutWidth = 200.0f;

    //==================================================
    // 11. 項目の幅を設定
    //==================================================
    testLayoutPushItemWidth.LayoutType = IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_PUSH_ITEM_WIDTH;
    testLayoutPushItemWidth.LayoutWidth = 200.0f;

    //==================================================
    // 12. 項目の幅を元に戻す
    //==================================================
    testLayoutPopItemWidth.LayoutType = IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_POP_ITEM_WIDTH;

    //==================================================
    // 13. テキストの高さを合わせる
    //==================================================
    testLayoutAlignTextToFramePadding.LayoutType =
        IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_ALIGN_TEXT_TO_FRAME_PADDING;

    //==================================================
    // 14. 次のツリー項目の開閉状態
    //==================================================
    testLayoutSetNextItemOpen.LayoutType = IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_SET_NEXT_ITEM_OPEN;
    testLayoutSetNextItemOpen.LayoutDefaultOpen = true;
    testLayoutSetNextItemOpen.LayoutCount = ImGuiCond_Once;

    //==================================================
    // 15. グループ開始
    //==================================================
    testLayoutBeginGroup.LayoutType = IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_BEGIN_GROUP;

    //==================================================
    // 16. グループ終了
    //==================================================
    testLayoutEndGroup.LayoutType = IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_END_GROUP;

    //==================================================
    // 17. 子領域開始
    //==================================================
    testLayoutBeginChild.LayoutType = IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_BEGIN_CHILD;
    testLayoutBeginChild.LayoutText = "TestChild";
    testLayoutBeginChild.LayoutSize = ImVec2(300.0f, 100.0f);
    testLayoutBeginChild.LayoutChildFlags = ImGuiChildFlags_None;
    testLayoutBeginChild.LayoutWindowFlags = ImGuiWindowFlags_None;

    //==================================================
    // 18. 子領域終了
    //==================================================
    testLayoutEndChild.LayoutType = IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_END_CHILD;

    //==================================================
    // 19. 折りたたみ見出し
    //==================================================
    testLayoutCollapsingHeader.LayoutType =
        IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_COLLAPSING_HEADER;
    testLayoutCollapsingHeader.LayoutText = u8"折りたたみ見出し";
    testLayoutCollapsingHeader.LayoutTreeNodeFlags = ImGuiTreeNodeFlags_None;

    //==================================================
    // 20. ツリー項目
    //==================================================
    testLayoutTreeNode1.LayoutType = IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_TREE_NODE;
    testLayoutTreeNode1.LayoutText = u8"ツリーテスト";
    testLayoutTreeNode2 = testLayoutTreeNode1;

    //==================================================
    // 21. ツリー階層終了
    //==================================================
    testLayoutTreePop.LayoutType = IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_TREE_POP;

    //==================================================
    // 22. テーブル開始
    //==================================================
    testLayoutBeginTable.LayoutType = IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_BEGIN_TABLE;
    testLayoutBeginTable.LayoutText = "TestTable";
    testLayoutBeginTable.LayoutCount = 2;
    testLayoutBeginTable.LayoutTableFlags = ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg;
    testLayoutBeginTable.LayoutSize = ImVec2(0.0f, 0.0f);
    testLayoutBeginTable.LayoutWidth = 0.0f;

    //==================================================
    // 23. テーブルの1列目を設定
    //==================================================
    testLayoutTableSetupColumn1.LayoutType =
        IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_TABLE_SETUP_COLUMN;
    testLayoutTableSetupColumn1.LayoutText = u8"項目";
    testLayoutTableSetupColumn1.LayoutTableColumnFlags = ImGuiTableColumnFlags_WidthStretch;
    testLayoutTableSetupColumn1.LayoutWidth = 0.0f;
    testLayoutTableSetupColumn1.LayoutUserID = 1;

    //==================================================
    // 24. テーブルの2列目を設定
    //==================================================
    testLayoutTableSetupColumn2.LayoutType =
        IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_TABLE_SETUP_COLUMN;
    testLayoutTableSetupColumn2.LayoutText = u8"値";
    testLayoutTableSetupColumn2.LayoutTableColumnFlags = ImGuiTableColumnFlags_WidthStretch;
    testLayoutTableSetupColumn2.LayoutWidth = 0.0f;
    testLayoutTableSetupColumn2.LayoutUserID = 2;

    //==================================================
    // 25. テーブルの見出し行
    //==================================================
    testLayoutTableHeadersRow.LayoutType =
        IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_TABLE_HEADERS_ROW;

    //==================================================
    // 26. テーブルの次の行
    //==================================================
    testLayoutTableNextRow.LayoutType = IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_TABLE_NEXT_ROW;
    testLayoutTableNextRow.LayoutCount = 0;
    testLayoutTableNextRow.LayoutMinHeight = 0.0f;

    //==================================================
    // 27. テーブルの次の列
    //==================================================
    testLayoutTableNextColumn.LayoutType =
        IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_TABLE_NEXT_COLUMN;

    //==================================================
    // 28. 指定した列に移動
    //==================================================
    testLayoutTableSetColumnIndex.LayoutType =
        IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_TABLE_SET_COLUMN_INDEX;
    testLayoutTableSetColumnIndex.LayoutIndex = 0;

    //==================================================
    // 29. テーブル終了
    //==================================================
    testLayoutEndTable.LayoutType = IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_END_TABLE;

    //==================================================
    // 30. スタイル値の変更
    //==================================================
    testLayoutPushStyleVar.LayoutType = IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_PUSH_STYLE_VAR;
    testLayoutPushStyleVar.LayoutStyleVar = ImGuiStyleVar_ItemSpacing;
    testLayoutPushStyleVar.LayoutSize = ImVec2(10.0f, 10.0f);

    //==================================================
    // 31. スタイル値を元に戻す
    //==================================================
    testLayoutPopStyleVar.LayoutType = IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_POP_STYLE_VAR;

    //==================================================
    // 32. 文字色の変更
    //==================================================
    testLayoutPushStyleColor.LayoutType = IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_PUSH_STYLE_COLOR;
    testLayoutPushStyleColor.LayoutStyleColor = ImGuiCol_Text;
    testLayoutPushStyleColor.LayoutColor = ImVec4(1.0f, 0.2f, 0.2f, 1.0f);

    //==================================================
    // 33. 文字色を元に戻す
    //==================================================
    testLayoutPopStyleColor.LayoutType = IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_POP_STYLE_COLOR;

    //==================================================
    // 追加テキスト表示
    //==================================================
    testLayoutTextA.LayoutType = IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_TEXT;
    testLayoutTextA.LayoutText = "NewLine Test A";

    testLayoutTextB.LayoutType = IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_TEXT;
    testLayoutTextB.LayoutText = "NewLine Test B";

    testLayoutTextC.LayoutType = IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_TEXT;
    testLayoutTextC.LayoutText = "Indent Test";

    testLayoutTextD.LayoutType = IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_TEXT;
    testLayoutTextD.LayoutText = "Indented Text";

    testLayoutTextE.LayoutType = IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_TEXT;
    testLayoutTextE.LayoutText = "Normal Position";

    testLayoutTextF.LayoutType = IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_TEXT;
    testLayoutTextF.LayoutText = "Dummy Before";

    testLayoutTextG.LayoutType = IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_TEXT;
    testLayoutTextG.LayoutText = "Dummy After";

    testLayoutTextH.LayoutType = IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_TEXT;
    testLayoutTextH.LayoutText = "SetNextItemWidth Test";

    testLayoutTextI.LayoutType = IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_TEXT;
    testLayoutTextI.LayoutText = "PushItemWidth Test";

    testLayoutTextJ.LayoutType = IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_TEXT;
    testLayoutTextJ.LayoutText = "Aligned Text";

    testLayoutTextK.LayoutType = IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_TEXT;
    testLayoutTextK.LayoutText = "Initially Open";

    testLayoutTextL.LayoutType = IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_TEXT;
    testLayoutTextL.LayoutText = "Group Content A";

    testLayoutTextM.LayoutType = IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_TEXT;
    testLayoutTextM.LayoutText = "Group Content B";

    testLayoutTextN.LayoutType = IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_TEXT;
    testLayoutTextN.LayoutText = "Child Region Test";

    testLayoutTextO.LayoutType = IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_TEXT;
    testLayoutTextO.LayoutText = "Header Content";

    testLayoutTextP.LayoutType = IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_TEXT;
    testLayoutTextP.LayoutText = "Tree Content";

    testLayoutTextQ.LayoutType = IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_TEXT;
    testLayoutTextQ.LayoutText = "Player";

    testLayoutTextR.LayoutType = IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_TEXT;
    testLayoutTextR.LayoutText = "100";

    testLayoutTextS.LayoutType = IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_TEXT;
    testLayoutTextS.LayoutText = "Enemy";

    testLayoutTextT.LayoutType = IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_TEXT;
    testLayoutTextT.LayoutText = "80";

    testLayoutTextU.LayoutType = IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_TEXT;
    testLayoutTextU.LayoutText = "Style Spacing Test A";

    testLayoutTextV.LayoutType = IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_TEXT;
    testLayoutTextV.LayoutText = "Style Spacing Test B";

    testLayoutTextW.LayoutType = IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_TEXT;
    testLayoutTextW.LayoutText = "Red Text Test";

    testLayoutTextX.LayoutType = IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_TEXT;
    testLayoutTextX.LayoutText = "Child Button Test";

    //==================================================
    // ボタンテスト用変数の初期化
    //==================================================
    testLayoutButtonA.ButtonType = IMGUI_BUTTON_TYPE::BUTTON;
    testLayoutButtonA.ButtonLabel = "Button A";
    testLayoutButtonA.ButtonFlag = &testLayoutButtonAFlag;
    testLayoutButtonA.ArgumentButtonFlag = &testLayoutButtonAArgumentFlag;

    testLayoutButtonB.ButtonType = IMGUI_BUTTON_TYPE::BUTTON;
    testLayoutButtonB.ButtonLabel = "Button B";
    testLayoutButtonB.ButtonFlag = &testLayoutButtonBFlag;
    testLayoutButtonB.ArgumentButtonFlag = &testLayoutButtonBArgumentFlag;

    testLayoutButtonC.ButtonType = IMGUI_BUTTON_TYPE::BUTTON;
    testLayoutButtonC.ButtonLabel = "Aligned Button";
    testLayoutButtonC.ButtonFlag = &testLayoutButtonCFlag;
    testLayoutButtonC.ArgumentButtonFlag = &testLayoutButtonCArgumentFlag;

    testLayoutButtonD.ButtonType = IMGUI_BUTTON_TYPE::BUTTON;
    testLayoutButtonD.ButtonLabel = "Group Button A";
    testLayoutButtonD.ButtonFlag = &testLayoutButtonDFlag;
    testLayoutButtonD.ArgumentButtonFlag = &testLayoutButtonDArgumentFlag;

    testLayoutButtonE.ButtonType = IMGUI_BUTTON_TYPE::BUTTON;
    testLayoutButtonE.ButtonLabel = "Group Button B";
    testLayoutButtonE.ButtonFlag = &testLayoutButtonEFlag;
    testLayoutButtonE.ArgumentButtonFlag = &testLayoutButtonEArgumentFlag;

    testLayoutButtonF.ButtonType = IMGUI_BUTTON_TYPE::BUTTON;
    testLayoutButtonF.ButtonLabel = "Child Button";
    testLayoutButtonF.ButtonFlag = &testLayoutButtonFFlag;
    testLayoutButtonF.ArgumentButtonFlag = &testLayoutButtonFArgumentFlag;

    testLayoutButtonG.ButtonType = IMGUI_BUTTON_TYPE::BUTTON;
    testLayoutButtonG.ButtonLabel = "Style Spacing Test A";
    testLayoutButtonG.ButtonFlag = &testLayoutButtonGFlag;
    testLayoutButtonG.ArgumentButtonFlag = &testLayoutButtonGArgumentFlag;

    testLayoutButtonH.ButtonType = IMGUI_BUTTON_TYPE::BUTTON;
    testLayoutButtonH.ButtonLabel = "Style Spacing Test B";
    testLayoutButtonH.ButtonFlag = &testLayoutButtonHFlag;
    testLayoutButtonH.ArgumentButtonFlag = &testLayoutButtonHArgumentFlag;

    //==================================================
    // レイアウトテスト用ボタン
    //==================================================
    testLayoutButton.ButtonType = IMGUI_BUTTON_TYPE::BUTTON;
    testLayoutButton.ButtonLabel = "Button";
    //testLayoutButton.ButtonImGuiEnumFlags = 0;
    testLayoutButton.ButtonSize = ImVec2(0.0f, 0.0f);
    testLayoutButton.ButtonDrawFlag = true;
    testLayoutButton.ButtonFlag = &testLayoutButtonFlag;
    testLayoutButton.ArgumentButtonFlag = &testLayoutButtonArgumentFlag;

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

    testLayoutEndCollapsingHeader.LayoutType = IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_END_COLLAPSING_HEADER;
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
    testLayoutButton.ButtonLabel = "Button A";
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

    testLayoutButton.ButtonLabel = "Button B";
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
    testText.LayoutText = "NewLine Test A";
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

    testText.LayoutText = "NewLine Test B";
    Master::mpImguiManager->AddDrawImguiGroup(
        IMGUI_ALL_DRAW_ONE_DATA(testText),
        IMGUI_GROUP_TYPE::TEST_1,
        "Layout Test"
    );

    //==================================================
    // 7～8. 描画位置の調整
    //==================================================
    testText.LayoutText = "Indent Test";
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

    testText.LayoutText = "Indented Text";
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

    testText.LayoutText = "Normal Position";
    Master::mpImguiManager->AddDrawImguiGroup(
        IMGUI_ALL_DRAW_ONE_DATA(testText),
        IMGUI_GROUP_TYPE::TEST_1,
        "Layout Test"
    );

    //==================================================
    // 9. 空白領域
    //==================================================
    testText.LayoutText = "Dummy Before";
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

    testText.LayoutText = "Dummy After";
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

    testLayoutInput.VariableLabel = "SetNextItemWidth Test";
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

    testLayoutInput.VariableLabel = "PushItemWidth Test";
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

    testText.LayoutText = "Aligned Text";
    Master::mpImguiManager->AddDrawImguiGroup(
        IMGUI_ALL_DRAW_ONE_DATA(testText),
        IMGUI_GROUP_TYPE::TEST_1,
        "Layout Test"
    );

    testLayoutButton.ButtonLabel = "Aligned Button";
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

    testLayoutTreeNode1.LayoutText = "SetNextItemOpen Test";
    Master::mpImguiManager->AddDrawImguiGroup(
        IMGUI_ALL_DRAW_ONE_DATA(testLayoutTreeNode1),
        IMGUI_GROUP_TYPE::TEST_1,
        "Layout Test"
    );

    testText.LayoutText = "Initially Open";
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

    testLayoutButton.ButtonLabel = "Group Button A";
    Master::mpImguiManager->AddDrawImguiGroup(
        IMGUI_ALL_DRAW_ONE_DATA(testLayoutButton),
        IMGUI_GROUP_TYPE::TEST_2,
        "Button Test"
    );

    testLayoutButton.ButtonLabel = "Group Button B";
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

    testText.LayoutText = "Child Region Test";
    Master::mpImguiManager->AddDrawImguiGroup(
        IMGUI_ALL_DRAW_ONE_DATA(testText),
        IMGUI_GROUP_TYPE::TEST_1,
        "Layout Test"
    );

    testLayoutButton.ButtonLabel = "Child Button";
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

    testText.LayoutText = "Header Content";
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
    testLayoutTreeNode2.LayoutText = "SetNextItemOpen Test 2";
    Master::mpImguiManager->AddDrawImguiGroup(
        IMGUI_ALL_DRAW_ONE_DATA(testLayoutTreeNode2),
        IMGUI_GROUP_TYPE::TEST_1,
        "Layout Test"
    );

    testText.LayoutText = "Tree Content";
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

    testText.LayoutText = "Player";
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

    testText.LayoutText = "100";
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

    testText.LayoutText = "Enemy";
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

    testText.LayoutText = "80";
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

    testLayoutButton.ButtonLabel = "Style Spacing Test A";
    Master::mpImguiManager->AddDrawImguiGroup(
        IMGUI_ALL_DRAW_ONE_DATA(testLayoutButton),
        IMGUI_GROUP_TYPE::TEST_2,
        "Button Test"
    );

    testLayoutButton.ButtonLabel = "Style Spacing Test B";
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

    testText.LayoutText = "Red Text Test";
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
    testLayoutTreeNode1.LayoutText = "Parent Tree";
    Master::mpImguiManager->AddDrawImguiGroup(
        IMGUI_ALL_DRAW_ONE_DATA(testLayoutTreeNode1),
        IMGUI_GROUP_TYPE::TEST_1,
        "Layout Test"
    );

    testText.LayoutText = "Parent Content";
    Master::mpImguiManager->AddDrawImguiGroup(
        IMGUI_ALL_DRAW_ONE_DATA(testText),
        IMGUI_GROUP_TYPE::TEST_1,
        "Layout Test"
    );

    testLayoutTreeNode2.LayoutText = "Child Tree";
    Master::mpImguiManager->AddDrawImguiGroup(
        IMGUI_ALL_DRAW_ONE_DATA(testLayoutTreeNode2),
        IMGUI_GROUP_TYPE::TEST_1,
        "Layout Test"
    );

    testText.LayoutText = "Child Content";
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

    testText.LayoutText = "Outside Tree";
    Master::mpImguiManager->AddDrawImguiGroup(
        IMGUI_ALL_DRAW_ONE_DATA(testText),
        IMGUI_GROUP_TYPE::TEST_1,
        "Layout Test"
    );

    //==================================================
    // 折りたたみ見出し・入れ子テスト
    //==================================================
    testLayoutCollapsingHeader.LayoutText = "Parent Header";
    Master::mpImguiManager->AddDrawImguiGroup(
        IMGUI_ALL_DRAW_ONE_DATA(testLayoutCollapsingHeader),
        IMGUI_GROUP_TYPE::TEST_1,
        "Layout Test"
    );

    testText.LayoutText = "Parent Header Content";
    Master::mpImguiManager->AddDrawImguiGroup(
        IMGUI_ALL_DRAW_ONE_DATA(testText),
        IMGUI_GROUP_TYPE::TEST_1,
        "Layout Test"
    );

    testLayoutCollapsingHeader.LayoutText = "Child Header";
    Master::mpImguiManager->AddDrawImguiGroup(
        IMGUI_ALL_DRAW_ONE_DATA(testLayoutCollapsingHeader),
        IMGUI_GROUP_TYPE::TEST_1,
        "Layout Test"
    );

    testText.LayoutText = "Child Header Content";
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

    testText.LayoutText = "Outside Header";
    Master::mpImguiManager->AddDrawImguiGroup(
        IMGUI_ALL_DRAW_ONE_DATA(testText),
        IMGUI_GROUP_TYPE::TEST_1,
        "Layout Test"
    );

    //==================================================
    // テーブル・描画制御テスト
    //==================================================
    testLayoutBeginTable.LayoutText = "TestTable";
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

    testText.LayoutText = "Table Content";
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

    testText.LayoutText = "Outside Table";
    Master::mpImguiManager->AddDrawImguiGroup(
        IMGUI_ALL_DRAW_ONE_DATA(testText),
        IMGUI_GROUP_TYPE::TEST_1,
        "Layout Test"
    );

    //==================================================
    // 複合レイアウト・描画制御テスト
    //==================================================
    testLayoutTreeNode1.LayoutText = "Parent Tree";
    Master::mpImguiManager->AddDrawImguiGroup(
        IMGUI_ALL_DRAW_ONE_DATA(testLayoutTreeNode1),
        IMGUI_GROUP_TYPE::TEST_1,
        "Layout Test"
    );

    testText.LayoutText = "Parent Content";
    Master::mpImguiManager->AddDrawImguiGroup(
        IMGUI_ALL_DRAW_ONE_DATA(testText),
        IMGUI_GROUP_TYPE::TEST_1,
        "Layout Test"
    );

    // ツリー内の折りたたみ見出し
    testLayoutCollapsingHeader.LayoutText = "Nested Header";
    Master::mpImguiManager->AddDrawImguiGroup(
        IMGUI_ALL_DRAW_ONE_DATA(testLayoutCollapsingHeader),
        IMGUI_GROUP_TYPE::TEST_1,
        "Layout Test"
    );

    testText.LayoutText = "Nested Header Content";
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
    testLayoutTreeNode2.LayoutText = "Nested Tree";
    Master::mpImguiManager->AddDrawImguiGroup(
        IMGUI_ALL_DRAW_ONE_DATA(testLayoutTreeNode2),
        IMGUI_GROUP_TYPE::TEST_1,
        "Layout Test"
    );

    testText.LayoutText = "Nested Tree Content";
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
    testText.LayoutText = "Outside All Layouts";
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
    testButton1.ButtonType = IMGUI_BUTTON_TYPE::BUTTON;
    testButton1.ButtonLabel = "Normal Button";
    testButton1.ButtonFlag = &testButton1Flag;
    testButton1.ArgumentButtonFlag = &testButton1ArgumentFlag;
    testButton1.ButtonSize = ImVec2(150.0f, 30.0f);

    //==================================================
    // 2. 小型ボタン
    //==================================================
    testButton2.ButtonType = IMGUI_BUTTON_TYPE::SMALL_BUTTON;
    testButton2.ButtonLabel = "Small Button";
    testButton2.ButtonFlag = &testButton2Flag;
    testButton2.ArgumentButtonFlag = &testButton2ArgumentFlag;

    //==================================================
    // 3. 矢印ボタン
    //==================================================
    testButton3.ButtonType = IMGUI_BUTTON_TYPE::ARROW_BUTTON;
    testButton3.ButtonLabel = "Arrow";
    testButton3.ButtonFlag = &testButton3Flag;
    testButton3.ArgumentButtonFlag = &testButton3ArgumentFlag;
    testButton3.ButtonDir = ImGuiDir_Right;

    //==================================================
    // 4. 透明ボタン
    //==================================================
    testButton4.ButtonType = IMGUI_BUTTON_TYPE::INVISIBLE_BUTTON;
    testButton4.ButtonLabel = "Invisible";
    testButton4.ButtonFlag = &testButton4Flag;
    testButton4.ArgumentButtonFlag = &testButton4ArgumentFlag;
    testButton4.ButtonSize = ImVec2(150.0f, 30.0f);
    testButton4.ButtonFlags = ImGuiButtonFlags_None;

    //==================================================
    // 5. チェックボックス
    //==================================================
    testButton5.ButtonType = IMGUI_BUTTON_TYPE::CHECK_BOX;
    testButton5.ButtonLabel = "Check Box";
    testButton5.ButtonFlag = &testButton5Flag;
    testButton5.ArgumentButtonFlag = &testButton5ArgumentFlag;

    //==================================================
    // 6. ビットフラグ用チェックボックス
    //==================================================
    testButton6.ButtonType = IMGUI_BUTTON_TYPE::CHECK_BOX_FLAGS;
    testButton6.ButtonLabel = "Flag Bit";
    testButton6.ButtonFlag = &testButton6Flag;
    testButton6.ArgumentButtonFlag = &testButton6ArgumentFlag;
    testButton6.ButtonBitFlag = &testButton6BitFlag;
    testButton6BitFlag = 0u;
    testButton6.ButtonBitFlagValue = 1u;

    //==================================================
    // 7. ラジオボタン
    //==================================================
    testButton7.ButtonType = IMGUI_BUTTON_TYPE::RADIO_BUTTON;
    testButton7.ButtonLabel = "Radio Button";
    testButton7.ButtonFlag = &testButton7Flag;
    testButton7.ArgumentButtonFlag = &testButton7ArgumentFlag;

    //==================================================
    // 8. 色ボタン
    //==================================================
    testButton8.ButtonType = IMGUI_BUTTON_TYPE::COLOR_BUTTON;
    testButton8.ButtonLabel = "Color Button";
    testButton8.ButtonFlag = &testButton8Flag;
    testButton8.ArgumentButtonFlag = &testButton8ArgumentFlag;
    testButton8.ButtonColor = ImVec4(1.0f, 0.2f, 0.2f, 1.0f);
    testButton8.ButtonSize = ImVec2(100.0f, 30.0f);
    testButton8.ButtonColorEditFlags = ImGuiColorEditFlags_None;

    //==================================================
    // 9. 選択可能項目
    //==================================================
    testButton9.ButtonType = IMGUI_BUTTON_TYPE::SELECTABLE;
    testButton9.ButtonLabel = "Selectable Item";
    testButton9.ButtonFlag = &testButton9Flag;
    testButton9.ArgumentButtonFlag = &testButton9ArgumentFlag;
    testButton9.ButtonSelectableFlags = ImGuiSelectableFlags_None;

    //==================================================
    // 10. メニュー項目
    //==================================================
    testButton10.ButtonType = IMGUI_BUTTON_TYPE::MENU_ITEM;
    testButton10.ButtonLabel = "Menu Item";
    testButton10.ButtonFlag = &testButton10Flag;
    testButton10.ArgumentButtonFlag = &testButton10ArgumentFlag;
    testButton10.PressKeyString = "Ctrl+T";
    testButton10.ButtonDrawFlag = true;

    //==================================================
    // 11. タブバー内のボタン
    //==================================================
    testButton11.ButtonType = IMGUI_BUTTON_TYPE::TABITEM_BUTTON;
    testButton11.ButtonLabel = "Tab Action";
    testButton11.ButtonFlag = &testButton11Flag;
    testButton11.ArgumentButtonFlag = &testButton11ArgumentFlag;
    testButton11.ButtonTabItemFlags = ImGuiTabItemFlags_None;

    //==================================================
    // 12. テキストリンク
    //==================================================
    testButton12.ButtonType = IMGUI_BUTTON_TYPE::TEXT_LINK;
    testButton12.ButtonLabel = "Text Link";
    testButton12.ButtonFlag = &testButton12Flag;
    testButton12.ArgumentButtonFlag = &testButton12ArgumentFlag;

    //==================================================
    // 13. URLを開くテキストリンク
    //==================================================
    testButton13.ButtonType = IMGUI_BUTTON_TYPE::TEXT_LINK_OPEN_URL;
    testButton13.ButtonLabel = "Open OpenAI Website";
    testButton13.ButtonFlag = &testButton13Flag;
    testButton13.ArgumentButtonFlag = &testButton13ArgumentFlag;
    testButton13.Url = "https://openai.com/";
}
//==================================================
// ImguiManager ボタンテスト
//==================================================
// ボタンテスト用テキストをImguiManager経由で登録
void AddTestButtonText(const std::string& text)
{
    IMGUI_LAYOUT_CONTROL layoutText;
    layoutText.LayoutType = IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_TEXT;
    layoutText.LayoutText = text;

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
    AddTestButtonText(*testButton1.ArgumentButtonFlag ? "Pressed: true" : "Pressed: false");

    //==================================================
    // 2. 小型ボタン
    //==================================================
    AddTestButtonText(u8"2. SMALL_BUTTON");
    Master::mpImguiManager->AddDrawImguiGroup(
        IMGUI_ALL_DRAW_ONE_DATA(testButton2),
        IMGUI_GROUP_TYPE::TEST_2,
        "Button Test"
    );
    AddTestButtonText(*testButton2.ArgumentButtonFlag ? "Pressed: true" : "Pressed: false");

    //==================================================
    // 3. 矢印ボタン
    //==================================================
    AddTestButtonText(u8"3. ARROW_BUTTON");
    Master::mpImguiManager->AddDrawImguiGroup(
        IMGUI_ALL_DRAW_ONE_DATA(testButton3),
        IMGUI_GROUP_TYPE::TEST_2,
        "Button Test"
    );
    AddTestButtonText(*testButton3.ArgumentButtonFlag ? "Pressed: true" : "Pressed: false");

    //==================================================
    // 4. 透明ボタン
    //==================================================
    AddTestButtonText(u8"4. INVISIBLE_BUTTON");
    Master::mpImguiManager->AddDrawImguiGroup(
        IMGUI_ALL_DRAW_ONE_DATA(testButton4),
        IMGUI_GROUP_TYPE::TEST_2,
        "Button Test"
    );
    AddTestButtonText(*testButton4.ArgumentButtonFlag ? "Pressed: true" : "Pressed: false");

    //==================================================
    // 5. チェックボックス
    //==================================================
    AddTestButtonText(u8"5. CHECK_BOX");
    Master::mpImguiManager->AddDrawImguiGroup(
        IMGUI_ALL_DRAW_ONE_DATA(testButton5),
        IMGUI_GROUP_TYPE::TEST_2,
        "Button Test"
    );
    AddTestButtonText(*testButton5.ArgumentButtonFlag ? "Changed: true" : "Changed: false");
    AddTestButtonText(*testButton5.ButtonFlag ? "State: ON" : "State: OFF");

    //==================================================
    // 6. ビットフラグ用チェックボックス
    //==================================================
    AddTestButtonText(u8"6. CHECK_BOX_FLAGS");
    Master::mpImguiManager->AddDrawImguiGroup(
        IMGUI_ALL_DRAW_ONE_DATA(testButton6),
        IMGUI_GROUP_TYPE::TEST_2,
        "Button Test"
    );
    AddTestButtonText(u8"Flags: " + std::to_string(*testButton6.ButtonBitFlag));

    //==================================================
    // 7. ラジオボタン
    //==================================================
    AddTestButtonText(u8"7. RADIO_BUTTON");
    Master::mpImguiManager->AddDrawImguiGroup(
        IMGUI_ALL_DRAW_ONE_DATA(testButton7),
        IMGUI_GROUP_TYPE::TEST_2,
        "Button Test"
    );
    AddTestButtonText(*testButton7.ArgumentButtonFlag ? "Changed: true" : "Changed: false");

    //==================================================
    // 8. 色ボタン
    //==================================================
    AddTestButtonText(u8"8. COLOR_BUTTON");
    Master::mpImguiManager->AddDrawImguiGroup(
        IMGUI_ALL_DRAW_ONE_DATA(testButton8),
        IMGUI_GROUP_TYPE::TEST_2,
        "Button Test"
    );
    AddTestButtonText(*testButton8.ArgumentButtonFlag ? "Pressed: true" : "Pressed: false");

    //==================================================
    // 9. 選択可能項目
    //==================================================
    AddTestButtonText(u8"9. SELECTABLE");
    Master::mpImguiManager->AddDrawImguiGroup(
        IMGUI_ALL_DRAW_ONE_DATA(testButton9),
        IMGUI_GROUP_TYPE::TEST_2,
        "Button Test"
    );
    AddTestButtonText(*testButton9.ButtonFlag ? "Selected: true" : "Selected: false");

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
    AddTestButtonText(*testButton10.ButtonFlag ? "Selected: true" : "Selected: false");

    //==================================================
    // 11. タブバー内のボタン
    // ImguiManagerのグループAPIにタブバー開始・終了がないため、ボタンを直接登録
    //==================================================
    AddTestButtonText(u8"11. TABITEM_BUTTON");
    // タブバー開始
    IMGUI_LAYOUT_CONTROL beginTabBar;
    beginTabBar.LayoutType = IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_BEGIN_TAB_BAR;
    beginTabBar.LayoutText = "TestTabBar";
    beginTabBar.LayoutStyleTabBarFlags = ImGuiTabBarFlags_None;
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
    AddTestButtonText(*testButton11.ArgumentButtonFlag ? "Pressed: true" : "Pressed: false");
    // タブバー終了
    IMGUI_LAYOUT_CONTROL endTabBar;
    endTabBar.LayoutType = IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_END_TAB_BAR;
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
    AddTestButtonText(*testButton12.ArgumentButtonFlag ? "Pressed: true" : "Pressed: false");

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


// コンストラクタ
LightExecutor::LightExecutor(
    PuzzleGimmickActiveParam param,
    GameObject2D *parentObject,
    int lightAreaIndex,
    uint32_t lineCount,
    float baseAngle,
    float lightAngle,
    float lightLength,
    bool final2start) :
    mpParentObject(parentObject),
    mbLightOn(true),
    mbParamUpdate(false),
    mbFinal2Start(false),
    mnAreaIndex(lightAreaIndex),
    mnLineCount(lineCount),
    mfBaseAngle(baseAngle),
    mfLightAngle(lightAngle),
    mfLength(lightLength),
    BaseGimmickExecutor(param)
{
    InitializeTestAllLayoutImgui();
    // 
    this->SetLightLineCount(this->mnLineCount);

    // 
    this->SetLength(this->mfLength);

    // 
    this->SetBaseAngle(this->mfBaseAngle);

    // 
    this->SetLightAngle(this->mfLightAngle);

    // 
    this->SetFinal2Start(this->mbFinal2Start);

    // 
    this->UpdateLightParam();
}

// デストラクタ
LightExecutor::~LightExecutor()
{
}

// 初期化
int LightExecutor::Initilize()
{
    this->mbParamUpdate = true;

    InitializeTestAllLayoutImgui();
    InitializeTestAllButtonImgui();
    InitializeTestAllVariableIntegerImgui();

    return 0;
}

// ギミックの内容を実行する関数
// ※GameObject::EarlyUpdate()のタイミングで呼ばれます
int LightExecutor::EarlyUpdate(bool triggerSignal)
{
    // 
    if (this->GetActiveParam().GetSignalNot())
    {
        // 
        triggerSignal = !triggerSignal;
    }

    // 
    if (!triggerSignal)
    {
        // 
        return 0;
    }

    // 
    return 0;
}
bool flag = false;
// ギミックの内容を実行する関数
// ※GameObject::Update()のタイミングで呼ばれます
int LightExecutor::Update(bool triggerSignal)
{
    if (!flag)
    {
#ifdef _DEBUG
        TestAllLayoutImgui();
        TestAllButtonImgui();
        TestAllVariableIntegerImgui();
        flag = true;
#endif
    }
    // 
    if (this->GetActiveParam().GetSignalNot())
    {
        // 
        triggerSignal = !triggerSignal;
    }

    // 
    this->mbLightOn = triggerSignal;
    this->GetMyLightArea()->SetLightFlag(this->mbLightOn);


    // 
    return 0;
}

// ギミックの内容を実行する関数
// ※GameObject::LateUpdate()のタイミングで呼ばれます
int LightExecutor::LateUpdate(bool triggerSignal)
{
    flag = false;
    // 
    if (this->mbLightOn)
    {
        // 
        this->GetMyLightArea()->OnLight();

        // 
        this->UpdateLightParam();

        // 
        this->CalculateLineEndPos();
    }
    else
    {
        // 
        this->GetMyLightArea()->OffLight();
    }

    // 
    return 0;
}

// 当たり判定によるギミックの変化に対応させる関数
int LightExecutor::HitOnCollision(BaseCollision *myCollision, BaseCollision *hitCollision)
{
    // 
    return 0;
}

// このライトの光域を計算する関数
bool LightExecutor::CalculateLineEndPos()
{
    // 
    std::vector<BaseCollision2D *> objectCollisionBox;

    // 
    BaseScene *nowScene = Master::mpBaseSceneManager->SearchSceneAuto();
    if (nowScene->GetBaseCollision2DManager()->SearchTag(CollisionTag::CollisionTag_Wall, objectCollisionBox) != 0)
    {
        // 
        return false;
    }

    // 
    std::vector<BaseCollision2D *> mirrorCollisionBox;
    if (nowScene->GetBaseCollision2DManager()->SearchTag(CollisionTag::CollisionTag_Mirror, mirrorCollisionBox) != 0)
    {
        // 
        return false;
    }

    // 
    Ray2D tempRay;

    // 
    CollisionCheckResult2D resultCurrent = GetCollisionCheckResult2DZero();

    // 
    CollisionCheckResult2D resultNewr = GetCollisionCheckResult2DZero();

    // 
    return this->GetMyLightArea()->CalculateNode(
        this->mfBaseAngle,
        this->mfLength,
        objectCollisionBox,
        mirrorCollisionBox,
        tempRay,
        resultCurrent,
        resultNewr);
}

// このライトのレイの本数を取得する関数
uint32_t LightExecutor::GetLightLineCount() const
{
    // 
    return this->GetMyLightArea()->GetLightLineCount();
}

// このライトの長さを取得する関数
float LightExecutor::GetLength() const
{
    // 
    return this->mfLength;
}

// このライトのレイの本数を設定する関数
void LightExecutor::SetLightLineCount(uint32_t count)
{
    // 
    this->mnLineCount = count;

    // 
    this->mbParamUpdate = true;
}

// このライトの長さを設定する関数
void LightExecutor::SetLength(float length)
{
    this->mfLength = length;

    // 
    this->mbParamUpdate = true;
}

// このライトの基本角度を設定する関数
void LightExecutor::SetBaseAngle(float radian)
{
    // 
    this->mfBaseAngle = radian;

    // 
    this->mbParamUpdate = true;
}

// このライトの全体の角度を設定する関数
void LightExecutor::SetLightAngle(float radian)
{
    this->mfLightAngle = radian;

    // 
    this->mbParamUpdate = true;
}

// 最後の線から最初の線の計算を行う関数
void LightExecutor::SetFinal2Start(bool flag)
{
    // 
    this->mbFinal2Start = flag;

    // 
    this->mbParamUpdate = true;
}

// 
LightArea *LightExecutor::GetMyLightArea() const
{
    // 
    return Master::mpLightManager->SearchArea(this->mnAreaIndex);
}

// 
bool LightExecutor::UpdateLightParam()
{
    // 
    if (this->mbParamUpdate)
    {
        // 
        this->GetMyLightArea()->SetParam(
            this->mpParentObject,
            this->mnLineCount,
            this->mfBaseAngle,
            this->mfLightAngle,
            this->mbFinal2Start);

        // 
        this->mbParamUpdate = false;
    }

    // 
    return true;
}
