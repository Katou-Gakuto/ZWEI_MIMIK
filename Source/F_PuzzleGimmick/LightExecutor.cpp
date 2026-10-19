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

    testLayoutButtonB.ButtonType = IMGUI_BUTTON_TYPE::BUTTON;
    testLayoutButtonB.ButtonLabel = "Button B";

    testLayoutButtonC.ButtonType = IMGUI_BUTTON_TYPE::BUTTON;
    testLayoutButtonC.ButtonLabel = "Aligned Button";

    testLayoutButtonD.ButtonType = IMGUI_BUTTON_TYPE::BUTTON;
    testLayoutButtonD.ButtonLabel = "Group Button A";

    testLayoutButtonE.ButtonType = IMGUI_BUTTON_TYPE::BUTTON;
    testLayoutButtonE.ButtonLabel = "Group Button B";

    testLayoutButtonF.ButtonType = IMGUI_BUTTON_TYPE::BUTTON;
    testLayoutButtonF.ButtonLabel = "Child Button";

    testLayoutButtonG.ButtonType = IMGUI_BUTTON_TYPE::BUTTON;
    testLayoutButtonG.ButtonLabel = "Style Spacing Test A";

    testLayoutButtonH.ButtonType = IMGUI_BUTTON_TYPE::BUTTON;
    testLayoutButtonH.ButtonLabel = "Style Spacing Test B";

    //==================================================
    // レイアウトテスト用ボタン
    //==================================================
    testLayoutButton.ButtonType = IMGUI_BUTTON_TYPE::BUTTON;
    testLayoutButton.ButtonLabel = "Button";
    //testLayoutButton.ButtonImGuiEnumFlags = 0;
    testLayoutButton.ButtonSize = ImVec2(0.0f, 0.0f);
    testLayoutButton.ButtonDrawFlag = true;
    testLayoutButton.ButtonFlag = false;
    testLayoutButton.ArgumentButtonFlag = false;

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
    Master::mpImguiManager->DrawLayoutImgui(testLayoutText);

    //==================================================
    // 2. フォーマット付きテキスト
    //==================================================
    Master::mpImguiManager->DrawLayoutImgui(testLayoutTextFormat);

    //==================================================
    // 3. 同じ行に配置
    //==================================================
    testLayoutButton.ButtonLabel = "Button A";
    Master::mpImguiManager->DrawButtonImgui(testLayoutButton);

    Master::mpImguiManager->DrawLayoutImgui(testLayoutSameLine);

    testLayoutButton.ButtonLabel = "Button B";
    Master::mpImguiManager->DrawButtonImgui(testLayoutButton);

    //==================================================
    // 4. 水平線
    //==================================================
    Master::mpImguiManager->DrawLayoutImgui(testLayoutSeparator);

    //==================================================
    // 5. 項目間の空白
    //==================================================
    Master::mpImguiManager->DrawLayoutImgui(testLayoutSpacing);

    //==================================================
    // 6. 改行
    //==================================================
    testText.LayoutText = "NewLine Test A";
    Master::mpImguiManager->DrawLayoutImgui(testText);

    Master::mpImguiManager->DrawLayoutImgui(testLayoutNewLine);

    testText.LayoutText = "NewLine Test B";
    Master::mpImguiManager->DrawLayoutImgui(testText);

    //==================================================
    // 7～8. 描画位置の調整
    //==================================================
    testText.LayoutText = "Indent Test";
    Master::mpImguiManager->DrawLayoutImgui(testText);

    Master::mpImguiManager->DrawLayoutImgui(testLayoutIndent);

    testText.LayoutText = "Indented Text";
    Master::mpImguiManager->DrawLayoutImgui(testText);

    Master::mpImguiManager->DrawLayoutImgui(testLayoutUnindent);

    testText.LayoutText = "Normal Position";
    Master::mpImguiManager->DrawLayoutImgui(testText);

    //==================================================
    // 9. 空白領域
    //==================================================
    testText.LayoutText = "Dummy Before";
    Master::mpImguiManager->DrawLayoutImgui(testText);

    Master::mpImguiManager->DrawLayoutImgui(testLayoutDummy);

    testText.LayoutText = "Dummy After";
    Master::mpImguiManager->DrawLayoutImgui(testText);

    //==================================================
    // 10. 次の項目の幅を指定
    //==================================================
    Master::mpImguiManager->DrawLayoutImgui(testLayoutSetNextItemWidth);

    testLayoutInput.VariableLabel = "SetNextItemWidth Test";
    Master::mpImguiManager->AddDrawImgui(testLayoutInput);

    //==================================================
    // 11～12. 項目の幅を設定・復元
    //==================================================
    Master::mpImguiManager->DrawLayoutImgui(testLayoutPushItemWidth);

    testLayoutInput.VariableLabel = "PushItemWidth Test";
    Master::mpImguiManager->AddDrawImgui(testLayoutInput);

    Master::mpImguiManager->DrawLayoutImgui(testLayoutPopItemWidth);

    //==================================================
    // 13. テキストの高さを合わせる
    //==================================================
    Master::mpImguiManager->DrawLayoutImgui(
        testLayoutAlignTextToFramePadding
    );

    testText.LayoutText = "Aligned Text";
    Master::mpImguiManager->DrawLayoutImgui(testText);

    testLayoutButton.ButtonLabel = "Aligned Button";
    Master::mpImguiManager->DrawButtonImgui(testLayoutButton);

    //==================================================
    // 14. ツリーの初期開閉状態
    //==================================================
    Master::mpImguiManager->DrawLayoutImgui(testLayoutSetNextItemOpen);

    testLayoutTreeNode1.LayoutText = "SetNextItemOpen Test";
    Master::mpImguiManager->DrawLayoutImgui(testLayoutTreeNode1);

    testText.LayoutText = "Initially Open";
    Master::mpImguiManager->DrawLayoutImgui(testText);

    Master::mpImguiManager->DrawLayoutImgui(testLayoutTreePop);

    //==================================================
    // 15～16. グループ
    //==================================================
    Master::mpImguiManager->DrawLayoutImgui(testLayoutBeginGroup);

    testLayoutButton.ButtonLabel = "Group Button A";
    Master::mpImguiManager->DrawButtonImgui(testLayoutButton);

    testLayoutButton.ButtonLabel = "Group Button B";
    Master::mpImguiManager->DrawButtonImgui(testLayoutButton);

    Master::mpImguiManager->DrawLayoutImgui(testLayoutEndGroup);

    //==================================================
    // 17～18. 子領域
    //==================================================
    Master::mpImguiManager->DrawLayoutImgui(testLayoutBeginChild);

    testText.LayoutText = "Child Region Test";
    Master::mpImguiManager->DrawLayoutImgui(testText);

    testLayoutButton.ButtonLabel = "Child Button";
    Master::mpImguiManager->DrawButtonImgui(testLayoutButton);

    Master::mpImguiManager->DrawLayoutImgui(testLayoutEndChild);

    //==================================================
    // 19. 折りたたみ見出し
    //==================================================
    Master::mpImguiManager->DrawLayoutImgui(testLayoutCollapsingHeader);

    testText.LayoutText = "Header Content";
    Master::mpImguiManager->DrawLayoutImgui(testText);
    Master::mpImguiManager->DrawLayoutImgui(testLayoutEndCollapsingHeader);

    //==================================================
    // 20～21. ツリー
    //==================================================
    testLayoutTreeNode2.LayoutText = "SetNextItemOpen Test 2";
    Master::mpImguiManager->DrawLayoutImgui(testLayoutTreeNode2);

    testText.LayoutText = "Tree Content";
    Master::mpImguiManager->DrawLayoutImgui(testText);

    Master::mpImguiManager->DrawLayoutImgui(testLayoutTreePop);

    //==================================================
    // 22～29. テーブル
    //==================================================
    Master::mpImguiManager->DrawLayoutImgui(testLayoutBeginTable);

    Master::mpImguiManager->DrawLayoutImgui(
        testLayoutTableSetupColumn1
    );

    Master::mpImguiManager->DrawLayoutImgui(
        testLayoutTableSetupColumn2
    );

    Master::mpImguiManager->DrawLayoutImgui(
        testLayoutTableHeadersRow
    );

    // 1行目
    Master::mpImguiManager->DrawLayoutImgui(testLayoutTableNextRow);

    Master::mpImguiManager->DrawLayoutImgui(
        testLayoutTableSetColumnIndex
    );

    testText.LayoutText = "Player";
    Master::mpImguiManager->DrawLayoutImgui(testText);

    Master::mpImguiManager->DrawLayoutImgui(
        testLayoutTableNextColumn
    );

    testText.LayoutText = "100";
    Master::mpImguiManager->DrawLayoutImgui(testText);

    // 2行目
    Master::mpImguiManager->DrawLayoutImgui(testLayoutTableNextRow);

    Master::mpImguiManager->DrawLayoutImgui(
        testLayoutTableSetColumnIndex
    );

    testText.LayoutText = "Enemy";
    Master::mpImguiManager->DrawLayoutImgui(testText);

    Master::mpImguiManager->DrawLayoutImgui(
        testLayoutTableNextColumn
    );

    testText.LayoutText = "80";
    Master::mpImguiManager->DrawLayoutImgui(testText);

    Master::mpImguiManager->DrawLayoutImgui(testLayoutEndTable);

    //==================================================
    // 30～31. スタイル値の変更・復元
    //==================================================
    Master::mpImguiManager->DrawLayoutImgui(testLayoutPushStyleVar);

    testLayoutButton.ButtonLabel = "Style Spacing Test A";
    Master::mpImguiManager->DrawButtonImgui(testLayoutButton);

    testLayoutButton.ButtonLabel = "Style Spacing Test B";
    Master::mpImguiManager->DrawButtonImgui(testLayoutButton);

    Master::mpImguiManager->DrawLayoutImgui(testLayoutPopStyleVar);

    //==================================================
    // 32～33. 文字色の変更・復元
    //==================================================
    Master::mpImguiManager->DrawLayoutImgui(testLayoutPushStyleColor);

    testText.LayoutText = "Red Text Test";
    Master::mpImguiManager->DrawLayoutImgui(testText);

    Master::mpImguiManager->DrawLayoutImgui(testLayoutPopStyleColor);

    //==================================================
    // ツリーの入れ子・描画制御テスト
    //==================================================
    testLayoutTreeNode1.LayoutText = "Parent Tree";
    Master::mpImguiManager->DrawLayoutImgui(testLayoutTreeNode1);

    testText.LayoutText = "Parent Content";
    Master::mpImguiManager->DrawLayoutImgui(testText);

    testLayoutTreeNode2.LayoutText = "Child Tree";
    Master::mpImguiManager->DrawLayoutImgui(testLayoutTreeNode2);

    testText.LayoutText = "Child Content";
    Master::mpImguiManager->DrawLayoutImgui(testText);

    Master::mpImguiManager->DrawLayoutImgui(testLayoutTreePop);
    Master::mpImguiManager->DrawLayoutImgui(testLayoutTreePop);

    testText.LayoutText = "Outside Tree";
    Master::mpImguiManager->DrawLayoutImgui(testText);

    //==================================================
    // 折りたたみ見出し・入れ子テスト
    //==================================================
    testLayoutCollapsingHeader.LayoutText = "Parent Header";
    Master::mpImguiManager->DrawLayoutImgui(testLayoutCollapsingHeader);

    testText.LayoutText = "Parent Header Content";
    Master::mpImguiManager->DrawLayoutImgui(testText);

    testLayoutCollapsingHeader.LayoutText = "Child Header";
    Master::mpImguiManager->DrawLayoutImgui(testLayoutCollapsingHeader);

    testText.LayoutText = "Child Header Content";
    Master::mpImguiManager->DrawLayoutImgui(testText);

    Master::mpImguiManager->DrawLayoutImgui(testLayoutEndCollapsingHeader);
    Master::mpImguiManager->DrawLayoutImgui(testLayoutEndCollapsingHeader);

    testText.LayoutText = "Outside Header";
    Master::mpImguiManager->DrawLayoutImgui(testText);

    //==================================================
    // テーブル・描画制御テスト
    //==================================================
    testLayoutBeginTable.LayoutText = "TestTable";
    Master::mpImguiManager->DrawLayoutImgui(testLayoutBeginTable);

    Master::mpImguiManager->DrawLayoutImgui(testLayoutTableSetupColumn1);
    Master::mpImguiManager->DrawLayoutImgui(testLayoutTableSetupColumn2);
    Master::mpImguiManager->DrawLayoutImgui(testLayoutTableHeadersRow);

    Master::mpImguiManager->DrawLayoutImgui(testLayoutTableNextRow);
    Master::mpImguiManager->DrawLayoutImgui(testLayoutTableNextColumn);

    testText.LayoutText = "Table Content";
    Master::mpImguiManager->DrawLayoutImgui(testText);

    Master::mpImguiManager->DrawLayoutImgui(testLayoutEndTable);

    testText.LayoutText = "Outside Table";
    Master::mpImguiManager->DrawLayoutImgui(testText);

    //==================================================
    // 複合レイアウト・描画制御テスト
    //==================================================
    testLayoutTreeNode1.LayoutText = "Parent Tree";
    Master::mpImguiManager->DrawLayoutImgui(testLayoutTreeNode1);

    testText.LayoutText = "Parent Content";
    Master::mpImguiManager->DrawLayoutImgui(testText);

    // ツリー内の折りたたみ見出し
    testLayoutCollapsingHeader.LayoutText = "Nested Header";
    Master::mpImguiManager->DrawLayoutImgui(testLayoutCollapsingHeader);

    testText.LayoutText = "Nested Header Content";
    Master::mpImguiManager->DrawLayoutImgui(testText);

    Master::mpImguiManager->DrawLayoutImgui(testLayoutEndCollapsingHeader);

    // ツリー内の子ツリー
    testLayoutTreeNode2.LayoutText = "Nested Tree";
    Master::mpImguiManager->DrawLayoutImgui(testLayoutTreeNode2);

    testText.LayoutText = "Nested Tree Content";
    Master::mpImguiManager->DrawLayoutImgui(testText);

    Master::mpImguiManager->DrawLayoutImgui(testLayoutTreePop);

    // 親ツリーを終了
    Master::mpImguiManager->DrawLayoutImgui(testLayoutTreePop);

    // すべてのレイアウト終了後
    testText.LayoutText = "Outside All Layouts";
    Master::mpImguiManager->DrawLayoutImgui(testText);
}

//==================================================
// ImguiManager ボタンテスト用変数
//==================================================
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
    testButton1.ButtonSize = ImVec2(150.0f, 30.0f);

    //==================================================
    // 2. 小型ボタン
    //==================================================
    testButton2.ButtonType = IMGUI_BUTTON_TYPE::SMALL_BUTTON;
    testButton2.ButtonLabel = "Small Button";

    //==================================================
    // 3. 矢印ボタン
    //==================================================
    testButton3.ButtonType = IMGUI_BUTTON_TYPE::ARROW_BUTTON;
    testButton3.ButtonLabel = "Arrow";
    testButton3.ButtonDir = ImGuiDir_Right;

    //==================================================
    // 4. 透明ボタン
    //==================================================
    testButton4.ButtonType = IMGUI_BUTTON_TYPE::INVISIBLE_BUTTON;
    testButton4.ButtonLabel = "Invisible";
    testButton4.ButtonSize = ImVec2(150.0f, 30.0f);
    testButton4.ButtonFlags = ImGuiButtonFlags_None;

    //==================================================
    // 5. チェックボックス
    //==================================================
    testButton5.ButtonType = IMGUI_BUTTON_TYPE::CHECK_BOX;
    testButton5.ButtonLabel = "Check Box";
    testButton5.ButtonFlag = false;

    //==================================================
    // 6. ビットフラグ用チェックボックス
    //==================================================
    testButton6.ButtonType = IMGUI_BUTTON_TYPE::CHECK_BOX_FLAGS;
    testButton6.ButtonLabel = "Flag Bit";
    testButton6.ButtonBitFlag.flags = 0;
    testButton6.ButtonBitFlagValue = 1u;

    //==================================================
    // 7. ラジオボタン
    //==================================================
    testButton7.ButtonType = IMGUI_BUTTON_TYPE::RADIO_BUTTON;
    testButton7.ButtonLabel = "Radio Button";
    testButton7.ButtonFlag = false;

    //==================================================
    // 8. 色ボタン
    //==================================================
    testButton8.ButtonType = IMGUI_BUTTON_TYPE::COLOR_BUTTON;
    testButton8.ButtonLabel = "Color Button";
    testButton8.ButtonColor = ImVec4(1.0f, 0.2f, 0.2f, 1.0f);
    testButton8.ButtonSize = ImVec2(100.0f, 30.0f);
    testButton8.ButtonColorEditFlags = ImGuiColorEditFlags_None;

    //==================================================
    // 9. 選択可能項目
    //==================================================
    testButton9.ButtonType = IMGUI_BUTTON_TYPE::SELECTABLE;
    testButton9.ButtonLabel = "Selectable Item";
    testButton9.ButtonFlag = false;
    testButton9.ButtonSelectableFlags = ImGuiSelectableFlags_None;

    //==================================================
    // 10. メニュー項目
    //==================================================
    testButton10.ButtonType = IMGUI_BUTTON_TYPE::MENU_ITEM;
    testButton10.ButtonLabel = "Menu Item";
    testButton10.PressKeyString = "Ctrl+T";
    testButton10.ButtonDrawFlag = true;

    //==================================================
    // 11. タブバー内のボタン
    //==================================================
    testButton11.ButtonType = IMGUI_BUTTON_TYPE::TABITEM_BUTTON;
    testButton11.ButtonLabel = "Tab Action";
    testButton11.ButtonTabItemFlags = ImGuiTabItemFlags_None;

    //==================================================
    // 12. テキストリンク
    //==================================================
    testButton12.ButtonType = IMGUI_BUTTON_TYPE::TEXT_LINK;
    testButton12.ButtonLabel = "Text Link";

    //==================================================
    // 13. URLを開くテキストリンク
    //==================================================
    testButton13.ButtonType = IMGUI_BUTTON_TYPE::TEXT_LINK_OPEN_URL;
    testButton13.ButtonLabel = "Open OpenAI Website";
    testButton13.Url = "https://openai.com/";
}
//==================================================
// ImguiManager ボタンテスト
//==================================================
void TestAllButtonImgui()
{
    //==================================================
    // 1. 標準ボタン
    //==================================================
    ImGui::Text(u8"1. BUTTON試し");
    Master::mpImguiManager->DrawButtonImgui(testButton1);
    ImGui::SameLine();
    ImGui::Text("Pressed: %s",
        testButton1.ArgumentButtonFlag ? "true" : "false");

    //==================================================
    // 2. 小型ボタン
    //==================================================
    ImGui::Text("2. SMALL_BUTTON");
    Master::mpImguiManager->DrawButtonImgui(testButton2);
    ImGui::SameLine();
    ImGui::Text("Pressed: %s",
        testButton2.ArgumentButtonFlag ? "true" : "false");

    //==================================================
    // 3. 矢印ボタン
    //==================================================
    ImGui::Text("3. ARROW_BUTTON");
    Master::mpImguiManager->DrawButtonImgui(testButton3);
    ImGui::SameLine();
    ImGui::Text("Pressed: %s",
        testButton3.ArgumentButtonFlag ? "true" : "false");

    //==================================================
    // 4. 透明ボタン
    //==================================================
    ImGui::Text("4. INVISIBLE_BUTTON");
    Master::mpImguiManager->DrawButtonImgui(testButton4);
    ImGui::SameLine();
    ImGui::Text("Pressed: %s",
        testButton4.ArgumentButtonFlag ? "true" : "false");

    //==================================================
    // 5. チェックボックス
    //==================================================
    ImGui::Text("5. CHECK_BOX");
    Master::mpImguiManager->DrawButtonImgui(testButton5);
    ImGui::SameLine();
    ImGui::Text("Changed: %s",
        testButton5.ArgumentButtonFlag ? "true" : "false");
    ImGui::SameLine();
    ImGui::Text("State: %s",
        testButton5.ButtonFlag ? "ON" : "OFF");

    //==================================================
    // 6. ビットフラグ用チェックボックス
    //==================================================
    ImGui::Text("6. CHECK_BOX_FLAGS");
    Master::mpImguiManager->DrawButtonImgui(testButton6);
    ImGui::SameLine();
    ImGui::Text("Flags: %u",
        testButton6.ButtonBitFlag.flags);

    //==================================================
    // 7. ラジオボタン
    //==================================================
    ImGui::Text("7. RADIO_BUTTON");
    Master::mpImguiManager->DrawButtonImgui(testButton7);
    ImGui::SameLine();
    ImGui::Text("Changed: %s",
        testButton7.ArgumentButtonFlag ? "true" : "false");

    //==================================================
    // 8. 色ボタン
    //==================================================
    ImGui::Text("8. COLOR_BUTTON");
    Master::mpImguiManager->DrawButtonImgui(testButton8);
    ImGui::SameLine();
    ImGui::Text("Pressed: %s",
        testButton8.ArgumentButtonFlag ? "true" : "false");

    //==================================================
    // 9. 選択可能項目
    //==================================================
    ImGui::Text("9. SELECTABLE");
    Master::mpImguiManager->DrawButtonImgui(testButton9);
    ImGui::SameLine();
    ImGui::Text("Selected: %s",
        testButton9.ButtonFlag ? "true" : "false");

    //==================================================
    // 10. メニュー項目
    //==================================================
    ImGui::Text("10. MENU_ITEM");
    if (ImGui::BeginMenu("Test Menu"))
    {
        Master::mpImguiManager->DrawButtonImgui(testButton10);
        ImGui::EndMenu();
    }
    ImGui::Text("Selected: %s",
        testButton10.ButtonFlag ? "true" : "false");

    //==================================================
    // 11. タブバー内のボタン
    //==================================================
    ImGui::Text("11. TABITEM_BUTTON");
    if (ImGui::BeginTabBar("TestTabBar"))
    {
        Master::mpImguiManager->DrawButtonImgui(testButton11);
        ImGui::SameLine();
        ImGui::Text("Pressed: %s",
            testButton11.ArgumentButtonFlag ? "true" : "false");

        ImGui::EndTabBar();
    }

    //==================================================
    // 12. テキストリンク
    //==================================================
    ImGui::Text("12. TEXT_LINK");
    Master::mpImguiManager->DrawButtonImgui(testButton12);
    ImGui::SameLine();
    ImGui::Text("Pressed: %s",
        testButton12.ArgumentButtonFlag ? "true" : "false");

    //==================================================
    // 13. URLを開くテキストリンク
    //==================================================
    ImGui::Text("13. TEXT_LINK_OPEN_URL");
    Master::mpImguiManager->DrawButtonImgui(testButton13);
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
    //ImGui::Begin("Test", nullptr);
    //    TestAllLayoutImgui();
    //    ImGui::End();
    //ImGui::Begin("DEbug", nullptr);
        //TestAllButtonImgui();
        //ImGui::End();
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

// シミュレーション内容を描画する関数
// ※既に実行段階である場合は引数がtrueになります。実行段階では描画しない、あるいはその逆の場合はこの引数を使ってください。
int LightExecutor::Draw(bool triggerSignal)
{
    // 
    if (!this->mbLightOn)
    {
        // 光域のシミュレーターは描画はしません
        return 0;
    }

    // 
    size_t firstIndex = 0;
    size_t secondIndex = 0;

    // 
    LightArea *lightArea = Master::mpLightManager->SearchArea(this->mnAreaIndex);
    LightLineNode *currentNode;
    LightLineNode *nextNode;

    // 
    auto nodeBox = lightArea->GetFirstNodeBox();

    // 
    int drawResult = 0;

    // 
    VECTOR2D baseStartPos = lightArea->GetStartPosition();

    // 
    int drawMode = 0;

    if (drawMode == 0)
    {
        // 
        for (uint32_t i = 0; i < lightArea->GetLightLineCount(); i++)
        {
            // 
            currentNode = lightArea->GetFirstNodeBox()[i];

            // 
            if (currentNode == nullptr)
            {
                // 
                continue;
            }

            // 
            while (true)
            {
                // 
                if (currentNode == lightArea->GetFirstNodeBox()[i] &&
                    !currentNode->CheckNext())
                {
                    // 
                    // break;
                }
                
                // デバッグ用レイの可視化
                drawResult = DxLib::DrawLine(
                    currentNode->GetMyStartPos().GetX(),
                    currentNode->GetMyStartPos().GetY(),
                    currentNode->GetMyEndPos().GetX(),
                    currentNode->GetMyEndPos().GetY(),
                    0x00ffff);
                // 
                if (!currentNode->AccessNext(&nextNode))
                {
                    // 
                    break;
                }

                // 
                currentNode = nextNode;
            }
        }
                   // Master::mpImguiManager->DrawGameDisplayToImgui("Draw");
    }
    else if (drawMode == 1)
    {

        // 
        for (uint32_t i = 0; i < lightArea->GetLightLineCount() - 1; i++)
        {
            // 
            drawResult = DxLib::DrawTriangle(
                baseStartPos.GetX(),
                baseStartPos.GetY(),
                nodeBox[i]->GetMyEndPos().GetX(),
                nodeBox[i]->GetMyEndPos().GetY(),
                nodeBox[i + 1]->GetMyEndPos().GetX(),
                nodeBox[i + 1]->GetMyEndPos().GetY(),
                0x00ffff,
                false);

            // 
            if (drawResult != 0)
            {
                // 
                break;
            }
        }

        // 
        if (drawResult != 0)
        {
            // 
            return drawResult;
        }

        // 
        firstIndex = 0;

        // 
        bool loopFlag = true;

        // 
        LightLineNode *firstNode = nullptr;
        LightLineNode *firstNodeNext = nullptr;
        LightLineNode *secondNode = nullptr;
        LightLineNode *secondNodeNext = nullptr;

        // 
        for (size_t i = 0; i < lightArea->GetLightLineCount() - 1; i++)
        {
            // 
            firstNode = nodeBox[i];
            secondNode = nodeBox[i + 1];

            // 
            loopFlag = true;

            // 
            while (loopFlag)
            {
                // 
                firstNode->AccessNext(&firstNodeNext);
                secondNode->AccessNext(&secondNodeNext);

                // 
                if (firstNodeNext != nullptr && secondNodeNext != nullptr)
                {
                    // 
                    drawResult = DxLib::DrawQuadrangle(
                        firstNode->GetMyEndPos().GetX(),
                        firstNode->GetMyEndPos().GetY(),
                        secondNode->GetMyEndPos().GetX(),
                        secondNode->GetMyEndPos().GetY(),
                        firstNodeNext->GetMyEndPos().GetX(),
                        firstNodeNext->GetMyEndPos().GetY(),
                        secondNodeNext->GetMyEndPos().GetX(),
                        secondNodeNext->GetMyEndPos().GetY(),
                        0x00ffff,
                        true);

                    // 
                    firstNode = firstNodeNext;
                    secondNode = secondNodeNext;
                }
                else if (firstNodeNext != nullptr && secondNodeNext == nullptr)
                {
                    // 
                    drawResult = DxLib::DrawTriangle(
                        firstNode->GetMyEndPos().GetX(),
                        firstNode->GetMyEndPos().GetY(),
                        secondNode->GetMyEndPos().GetX(),
                        secondNode->GetMyEndPos().GetY(),
                        firstNodeNext->GetMyEndPos().GetX(),
                        firstNodeNext->GetMyEndPos().GetY(),
                        0x00ffff,
                        true);

                    // 
                    loopFlag = false;
                }
                else if (firstNodeNext == nullptr && secondNodeNext != nullptr)
                {
                    // 
                    drawResult = DxLib::DrawTriangle(
                        firstNode->GetMyEndPos().GetX(),
                        firstNode->GetMyEndPos().GetY(),
                        secondNode->GetMyEndPos().GetX(),
                        secondNode->GetMyEndPos().GetY(),
                        secondNodeNext->GetMyEndPos().GetX(),
                        secondNodeNext->GetMyEndPos().GetY(),
                        0x00ffff,
                        true);

                    // 
                    loopFlag = false;
                }
                else
                {
                    // 
                    loopFlag = false;
                }
            }

            // 
            if (drawResult != 0)
            {
                // 
                break;
            }
        }
    }
    else if (drawMode == 2)
    {
        // 
        currentNode = nodeBox[gnDebugTest];

        // 
        while (true)
        {
            // 
            drawResult = DxLib::DrawLine(
                currentNode->GetMyStartPos().GetX(),
                currentNode->GetMyStartPos().GetY(),
                currentNode->GetMyEndPos().GetX(),
                currentNode->GetMyEndPos().GetY(),
                0x00ffff);

            // 
            if (currentNode->AccessNext(&nextNode))
            {
                // 
                currentNode = nextNode;
            }
            else
            {
                // 
                break;
            }
        }

        // 
        gnDebugTest++;

        // 
        gnDebugTest %= lightArea->GetLightLineCount();
    }

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
