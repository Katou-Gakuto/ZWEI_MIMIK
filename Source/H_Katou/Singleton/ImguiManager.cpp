#include <Windows.h>
#include <d3d11.h>
#include <tchar.h>
#include <vector>

#include "ImguiEnum.h"
#include "ImguiData.h"

#include "DxLib.h"
#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"

#include "ImguiManager.h"

#ifdef _DEBUG
#include "DebugLogs/DebugLog.h"

#endif


ImguiManager::ImguiManager(bool isImguiExecute)
: mnAddNumber(0)
, mbIsImguiExecute(isImguiExecute)
, mstCurrentGroupTypeData()
{
    mstImguiGroupDatas.clear();
}

ImguiManager::~ImguiManager()
{
}
// 初期化
void ImguiManager::Initilize()
{
#ifdef _DEBUG
    if (!mbIsImguiExecute)
    {
        return;
    }
    
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    io.Fonts->AddFontFromFileTTF("Resource/imgui/BIZ_UDGothic/BIZUDGothic-Regular.ttf", 16.0f);

    ImGui::StyleColorsDark();

    ImGui_ImplWin32_Init(DxLib::GetMainWindowHandle());
    ImGui_ImplDX11_Init((ID3D11Device*)DxLib::GetUseDirect3D11Device(), (ID3D11DeviceContext*)DxLib::GetUseDirect3D11DeviceContext());
#endif
}

// 終了
void ImguiManager::Finalize()
{
#ifdef _DEBUG
    if (!mbIsImguiExecute)
    {
        return;
    }
    
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
#endif
}

// 更新
void ImguiManager::Update()
{
#ifdef _DEBUG
    if (!mbIsImguiExecute)
    {
        return;
    }
    
    // ImGui フレーム開始
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
    ImGui::ShowDemoWindow();
    
    mnAddNumber = 0;
    // グループ
    for (int i = 0; i < mstImguiGroupDatas.size(); i++)
    {
        DrawGroupImgui(mstImguiGroupDatas[i]);
    }
    
    mstImguiGroupDatas.clear();
ImGui::TextLinkOpenURL("TEST", "https://github.com/Katou-Gakuto/ZWEI_MIMIK");
    DEBUG::SaveText("CLICK");
    if (ImGui::Button("Test Button"))
    {
        DEBUG::SaveText("CLICK\n\n");
    }
#endif
}

// 描画
void ImguiManager::Draw()
{
#ifdef _DEBUG
    if (!mbIsImguiExecute)
    {
        return;
    }
    
    // ImGui フレーム終了と描画
    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    // DXLib Direct3D設定を復元
    RefreshDxLibDirect3DSetting();
#endif
}


// Imgui追加描画
void ImguiManager::AddDrawImgui(IMGUI_CONTROL_VARIABLE imguiControlVariableData)
{
#ifdef _DEBUG
    if (!mbIsImguiExecute)
    {
        return;
    }
    
    if (imguiControlVariableData.AddNumberDrawFlag == true)
    {
        imguiControlVariableData.Label = imguiControlVariableData.Label + "_" + std::to_string(mnAddNumber);
    }
    ++mnAddNumber;
    DrawControlVariableImgui(imguiControlVariableData);
#endif
}

// Imguiグループ追加描画(全部)
void ImguiManager::AddDrawImguiGroup(IMGUI_GROUP_DATA imguiGroupData)
{
#ifdef _DEBUG
    if (!mbIsImguiExecute)
    {
        return;
    }
    
    mstImguiGroupDatas.push_back(imguiGroupData);
#endif
}

// Imguiグループ追加描画(引数参照)
void ImguiManager::AddDrawImguiGroup(IMGUI_CONTROL_VARIABLE imguiControlVariableData, IMGUI_GROUP_TYPE groupType, std::string groupName)
{
#ifdef _DEBUG
    if (!mbIsImguiExecute)
    {
        return;
    }
    IMGUI_GROUP_DATA* imguiGroupData = nullptr;

    CURRENT_GROUP_TYPE_DATA currentGroupTypeData = SearchImguiGroupData(groupType, &imguiGroupData);

    // 既存グループがある場合
    if (imguiGroupData != nullptr)
    {
        imguiGroupData->AddImguiControlVariableData(imguiControlVariableData);
        return;
    }

    // グループが存在しない場合は新規作成
    IMGUI_GROUP_DATA newGroupData = IMGUI_GROUP_DATA::GetImguiGroupData(groupName, groupType);

    newGroupData.AddImguiControlVariableData(imguiControlVariableData);

    mstImguiGroupDatas.push_back(newGroupData);
#endif
}

// Imguiグループ追加描画(参照) ※StartGroupを読んでから使用してください
void ImguiManager::AddDrawImguiGroup(IMGUI_CONTROL_VARIABLE imguiControlVariableData)
{
#ifdef _DEBUG
    if (!mbIsImguiExecute)
    {
        return;
    }

    IMGUI_GROUP_DATA* imguiGroupData = GetCurrentGroupData();

    if (imguiGroupData == nullptr)
    {
        MessageBoxA(nullptr, "ImguiManager::AddDrawImguiGroup(float)\nStartGroup()が呼ばれていないため、追加できません。", "StartGroup()が呼ばれていません。",MB_OK | MB_ICONERROR);
        __debugbreak();
        return;
    }

    imguiGroupData->AddImguiControlVariableData(imguiControlVariableData);
#endif    
}

// Imguiグループ参照先設定開始 ※設定が終わったらEndGroupを読んでください
void ImguiManager::StartGroup(IMGUI_GROUP_TYPE groupType, std::string groupName)
{
#ifdef _DEBUG
    if (!mbIsImguiExecute)
    {
        return;
    }

    IMGUI_GROUP_DATA* imguiGroupData = nullptr;

    mstCurrentGroupTypeData = SearchImguiGroupData(groupType, &imguiGroupData);

    // グループが見つからなかった場合は新しく作成してそれを参照にする
    if (imguiGroupData == nullptr)
    {
        IMGUI_GROUP_DATA newGroupData = IMGUI_GROUP_DATA::GetImguiGroupData(groupName, groupType);

        mstImguiGroupDatas.push_back(newGroupData);

        // 追加したグループを参照
        int newGroupIndex = (int)mstImguiGroupDatas.size() - 1;

        mstCurrentGroupTypeData.CurrentGroupType = groupType;
        mstCurrentGroupTypeData.CurrentGroupTypeIndexs.clear();
        mstCurrentGroupTypeData.CurrentGroupTypeIndexs.push_back(newGroupIndex);
    }
#endif
}
// Imguiグループ参照先設定終了
void ImguiManager::EndGroup()
{
#ifdef _DEBUG
    if (!mbIsImguiExecute)
    {
        return;
    }

    mstCurrentGroupTypeData = CURRENT_GROUP_TYPE_DATA();
#endif
}

// Imguiグループを新しく作成
void ImguiManager::CreateImguiGroup(IMGUI_GROUP_TYPE groupType, std::string groupName, IMGUI_GROUP_TYPE parentGroupType)
{
#ifdef _DEBUG
    if (!mbIsImguiExecute)
    {
        return;
    }

    if (groupType == IMGUI_GROUP_TYPE::NONE)
    {
        return;
    }

    IMGUI_GROUP_DATA newGroupData =
        IMGUI_GROUP_DATA::GetImguiGroupData(
            groupName,
            groupType
        );

    // 親なしなら最上位に追加
    if (parentGroupType == IMGUI_GROUP_TYPE::NONE)
    {
        mstImguiGroupDatas.push_back(newGroupData);
        return;
    }

    // 親グループを検索
    IMGUI_GROUP_DATA* parentGroupData = nullptr;

    SearchImguiGroupData(parentGroupType, &parentGroupData);

    if (parentGroupData == nullptr)
    {
        return;
    }

    parentGroupData->AddChildData(newGroupData);
#endif
}

// Imguiグループを移動
void ImguiManager::MoveImguiGroup(IMGUI_GROUP_TYPE groupType, IMGUI_GROUP_TYPE parentGroupType)
{
#ifdef _DEBUG
    if (!mbIsImguiExecute)
    {
        return;
    }

    if (groupType == IMGUI_GROUP_TYPE::NONE)
    {
        return;
    }

    // 移動対象を検索
    IMGUI_GROUP_DATA* moveGroupData = nullptr;

    CURRENT_GROUP_TYPE_DATA currentGroupTypeData =
        SearchImguiGroupData(groupType, &moveGroupData);

    if (moveGroupData == nullptr)
    {
        return;
    }

    // 自分自身を親にはできない
    if (groupType == parentGroupType)
    {
        return;
    }

    // 移動対象をコピー
    IMGUI_GROUP_DATA moveData = *moveGroupData;

    // 元のグループを削除
    DeleteImguiGroup(groupType);

    // 最上位へ移動
    if (parentGroupType == IMGUI_GROUP_TYPE::NONE)
    {
        mstImguiGroupDatas.push_back(moveData);
        return;
    }

    // 移動先の親を検索
    IMGUI_GROUP_DATA* parentGroupData = nullptr;

    SearchImguiGroupData(parentGroupType, &parentGroupData);

    if (parentGroupData == nullptr)
    {
        // 親が存在しなかった場合は最上位へ戻す
        mstImguiGroupDatas.push_back(moveData);
        return;
    }

    parentGroupData->AddChildData(moveData);
#endif
}

// Imguiグループを削除
void ImguiManager::DeleteImguiGroup(IMGUI_GROUP_TYPE groupType)
{
#ifdef _DEBUG
    if (!mbIsImguiExecute)
    {
        return;
    }

    if (groupType == IMGUI_GROUP_TYPE::NONE)
    {
        return;
    }

    if (mstImguiGroupDatas.size() == 0)
    {
        return;
    }
    std::vector<IMGUI_GROUP_DATA>* nextCheckDatas = &mstImguiGroupDatas;
    std::vector<std::vector<IMGUI_GROUP_DATA>*> TemporarySaveImguiGroupDatas;

    TemporarySaveImguiGroupDatas.push_back(nextCheckDatas);

    std::vector<int> currentGroupTypeIndexs;
    currentGroupTypeIndexs.push_back(0);

    while (true)
    {
        // 取得し判定
        IMGUI_GROUP_DATA* setImguiGroupData = &(*nextCheckDatas)[currentGroupTypeIndexs[currentGroupTypeIndexs.size() - 1]];

        if (setImguiGroupData->GetGroupType() == groupType)
        {
            // 現在参照している配列から削除
            nextCheckDatas->erase(nextCheckDatas->begin() + currentGroupTypeIndexs[currentGroupTypeIndexs.size() - 1]);

            // 現在参照しているグループが削除対象だった場合
            if (mstCurrentGroupTypeData.CurrentGroupType == groupType)
            {
                mstCurrentGroupTypeData = CURRENT_GROUP_TYPE_DATA();
            }

            return;
        }

        // 子情報があるならそちらを調べる
        if (setImguiGroupData->GetChildDatas()->size() > 0)
        {
            nextCheckDatas = setImguiGroupData->GetChildDatas();

            TemporarySaveImguiGroupDatas.push_back(nextCheckDatas);
            currentGroupTypeIndexs.push_back(0);

            continue;
        }
        // 子情報がないなら参照ナンバーを増やす
        else
        {
            // 配列の最後を現在指しているなら親を調べる対象に変更
            if (nextCheckDatas->size() <= (currentGroupTypeIndexs[currentGroupTypeIndexs.size() - 1] + 1))
            {
                while (true)
                {
                    TemporarySaveImguiGroupDatas.pop_back();
                    currentGroupTypeIndexs.pop_back();
                    if (currentGroupTypeIndexs.size() == 0)
                    {
                        return;
                    }
                    nextCheckDatas = TemporarySaveImguiGroupDatas[TemporarySaveImguiGroupDatas.size() - 1];

                    if (nextCheckDatas->size() <= (currentGroupTypeIndexs[currentGroupTypeIndexs.size() - 1] + 1))
                    {
                        continue;
                    }

                    break;
                }
            }

            // 参照ナンバーを増やす
            currentGroupTypeIndexs[currentGroupTypeIndexs.size() - 1] += 1;
        }
    }
#endif
}

// Imguui描画
void ImguiManager::DrawControlVariableImgui(IMGUI_CONTROL_VARIABLE imguiControlVariableData)
{
#ifdef _DEBUG
    if (!mbIsImguiExecute ||
        imguiControlVariableData.VariableDatas.empty())
    {
        return;
    }

    for (int i = 0; i < imguiControlVariableData.VariableDatas.size(); i++)
    {
        if (i >= IMGUI_CONTROL_VARIABLE::IMGUI_VARIABLE_MAX)
        {
            break;
        }

        int variableIntegerType = static_cast<int>(ChangeVariableTypeToVariableIntegerType(imguiControlVariableData.VariableDatas[i].VariableType));
        if (variableIntegerType == IMGUI_VARIABLE_INTEGER)
        {
            int currentValue = 0;
            int previousValue = 0;
            int changeValue = 0;
            IMGUI_CONTROL_VARIABLE::GetVariableValue(imguiControlVariableData.VariableDatas[i]).GetValueToInt(currentValue);

            imguiControlVariableData.PreVariable[i].GetValueToInt(previousValue);
            imguiControlVariableData.ChangeVariable[i].GetValueToInt(changeValue);

            if (currentValue == previousValue)
            {
                continue;
            }

            imguiControlVariableData.ChangeVariable[i] = changeValue + (currentValue - previousValue);
        }
        else if (variableIntegerType == IMGUI_VARIABLE_MINORITY)
        {
            float currentValue = 0.0f;
            float previousValue = 0.0f;
            float changeValue = 0.0f;

            IMGUI_CONTROL_VARIABLE::GetVariableValue(imguiControlVariableData.VariableDatas[i]).GetValueToFloat(currentValue);

            imguiControlVariableData.PreVariable[i].GetValueToFloat(previousValue);
            imguiControlVariableData.ChangeVariable[i].GetValueToFloat(changeValue);

            if (std::fabs(currentValue - previousValue) < 0.00000001f)
            {
                continue;
            }

            imguiControlVariableData.ChangeVariable[i] = changeValue + (currentValue - previousValue);
        }
    }

    // ImGuiに渡す連続した描画用配列
    int changeInt[IMGUI_CONTROL_VARIABLE::IMGUI_VARIABLE_MAX] = {};
    float changeFloat[IMGUI_CONTROL_VARIABLE::IMGUI_VARIABLE_MAX] = {};

    int minInt[IMGUI_CONTROL_VARIABLE::IMGUI_VARIABLE_MAX] = {};
    int maxInt[IMGUI_CONTROL_VARIABLE::IMGUI_VARIABLE_MAX] = {};

    float minFloat[IMGUI_CONTROL_VARIABLE::IMGUI_VARIABLE_MAX] = {};
    float maxFloat[IMGUI_CONTROL_VARIABLE::IMGUI_VARIABLE_MAX] = {};

    for (int i = 0; i < imguiControlVariableData.VariableDatas.size(); i++)
    {
        if (i >= IMGUI_CONTROL_VARIABLE::IMGUI_VARIABLE_MAX)
        {
            break;
        }

        imguiControlVariableData.ChangeVariable[i].GetValueToInt(changeInt[i]);
        imguiControlVariableData.ChangeVariable[i].GetValueToFloat(changeFloat[i]);

        imguiControlVariableData.Min[i].GetValueToInt(minInt[i]);
        imguiControlVariableData.Max[i].GetValueToInt(maxInt[i]);

        imguiControlVariableData.Min[i].GetValueToFloat(minFloat[i]);
        imguiControlVariableData.Max[i].GetValueToFloat(maxFloat[i]);
    }

    const int drawVariableType = static_cast<int>(ChangeVariableTypeToVariableIntegerType(imguiControlVariableData.VariableDatas[0].VariableType));

    const char* label = imguiControlVariableData.Label.c_str();
    const char* format = imguiControlVariableData.Format.c_str();
    const ImGuiSliderFlags flag = imguiControlVariableData.Flag;

    switch (drawVariableType)
    {
    case IMGUI_VARIABLE_INTEGER:
        switch (imguiControlVariableData.ImguiType)
        {
        case IMGUI_TYPE::SLIDER1:
            ImGui::SliderInt(label, changeInt, minInt[0], maxInt[0], format, flag);
            break;

        case IMGUI_TYPE::SLIDER2:
            ImGui::SliderInt2(label, changeInt, minInt[0], maxInt[0], format, flag);
            break;

        case IMGUI_TYPE::SLIDER3:
            ImGui::SliderInt3(label, changeInt, minInt[0], maxInt[0], format, flag);
            break;

        case IMGUI_TYPE::SLIDER4:
            ImGui::SliderInt4(label, changeInt, minInt[0], maxInt[0], format, flag);
            break;

        case IMGUI_TYPE::DRAG1:
            ImGui::DragInt(label, changeInt, imguiControlVariableData.Speed, minInt[0], maxInt[0], format, flag);
            break;

        case IMGUI_TYPE::DRAG2:
            ImGui::DragInt2(label, changeInt, imguiControlVariableData.Speed, minInt[0], maxInt[0], format, flag);
            break;

        case IMGUI_TYPE::DRAG3:
            ImGui::DragInt3(label, changeInt, imguiControlVariableData.Speed, minInt[0], maxInt[0], format, flag);
            break;

        case IMGUI_TYPE::DRAG4:
            ImGui::DragInt4(label, changeInt, imguiControlVariableData.Speed, minInt[0], maxInt[0], format, flag);
            break;

        case IMGUI_TYPE::INPUT1:
            ImGui::InputInt(label, changeInt, static_cast<int>(imguiControlVariableData.Step), static_cast<int>(imguiControlVariableData.StepFast), flag);
            break;

        case IMGUI_TYPE::INPUT2:
            ImGui::InputInt2(label, changeInt, flag);
            break;

        case IMGUI_TYPE::INPUT3:
            ImGui::InputInt3(label, changeInt, flag);
            break;

        case IMGUI_TYPE::INPUT4:
            ImGui::InputInt4(label, changeInt, flag);
            break;

        default:
            break;
        }
        break;

    case IMGUI_VARIABLE_MINORITY:
        switch (imguiControlVariableData.ImguiType)
        {
        case IMGUI_TYPE::SLIDER1:
            ImGui::SliderFloat(label, changeFloat, minFloat[0], maxFloat[0], format, flag);
            break;

        case IMGUI_TYPE::SLIDER2:
            ImGui::SliderFloat2(label, changeFloat, minFloat[0], maxFloat[0], format, flag);
            break;

        case IMGUI_TYPE::SLIDER3:
            ImGui::SliderFloat3(label, changeFloat, minFloat[0], maxFloat[0], format, flag);
            break;

        case IMGUI_TYPE::SLIDER4:
            ImGui::SliderFloat4(label, changeFloat, minFloat[0], maxFloat[0], format, flag);
            break;

        case IMGUI_TYPE::DRAG1:
            ImGui::DragFloat(label, changeFloat, imguiControlVariableData.Speed, minFloat[0], maxFloat[0], format, flag);
            break;

        case IMGUI_TYPE::DRAG2:
            ImGui::DragFloat2(label, changeFloat, imguiControlVariableData.Speed, minFloat[0], maxFloat[0], format, flag);
            break;

        case IMGUI_TYPE::DRAG3:
            ImGui::DragFloat3(label, changeFloat, imguiControlVariableData.Speed, minFloat[0], maxFloat[0], format, flag);
            break;

        case IMGUI_TYPE::DRAG4:
            ImGui::DragFloat4(label, changeFloat, imguiControlVariableData.Speed, minFloat[0], maxFloat[0], format, flag);
            break;

        case IMGUI_TYPE::INPUT1:
            ImGui::InputFloat(label, changeFloat, imguiControlVariableData.Step, imguiControlVariableData.StepFast, format, flag);
            break;

        case IMGUI_TYPE::INPUT2:
            ImGui::InputFloat2(label, changeFloat, format, flag);
            break;

        case IMGUI_TYPE::INPUT3:
            ImGui::InputFloat3(label, changeFloat, format, flag);
            break;

        case IMGUI_TYPE::INPUT4:
            ImGui::InputFloat4(label, changeFloat, format, flag);
            break;

        case IMGUI_TYPE::ANGLE:
            ImGui::SliderAngle(label, changeFloat, minFloat[0], maxFloat[0], format, flag);
            break;

        default:
            break;
        }
        break;
    }

    // 描画結果を構造体へ戻す
    for (int i = 0; i < imguiControlVariableData.VariableDatas.size(); i++)
    {
        if (i >= IMGUI_CONTROL_VARIABLE::IMGUI_VARIABLE_MAX)
        {
            break;
        }

        if (drawVariableType == IMGUI_VARIABLE_INTEGER)
        {
            imguiControlVariableData.ChangeVariable[i] = changeInt[i];
        }
        else if (drawVariableType == IMGUI_VARIABLE_MINORITY)
        {
            imguiControlVariableData.ChangeVariable[i] = changeFloat[i];
        }

        imguiControlVariableData.VariableDatas[i] = imguiControlVariableData.ChangeVariable[i];

        imguiControlVariableData.PreVariable[i] = IMGUI_CONTROL_VARIABLE::GetVariableValue(imguiControlVariableData.VariableDatas[i]);
    }
#endif
}


/*ボタンimgui描画*/
void ImguiManager::DrawButtonImgui(IMGUI_BUTTON_CONTROL_VARIABLE& imguiButtonControlVariableData)
{
#ifdef _DEBUG
    if (!mbIsImguiExecute)
    {
        return;
    }
    bool buttonFlag = false;
    switch (imguiButtonControlVariableData.ButtonType)
    {    
    case IMGUI_BUTTON_TYPE::BUTTON:
        buttonFlag = ImGui::Button(imguiButtonControlVariableData.Label.c_str(), imguiButtonControlVariableData.Size);//	標準的な四角いボタン。サイズを指定できる
        break;

    case IMGUI_BUTTON_TYPE::SMALL_BUTTON:
        buttonFlag = ImGui::SmallButton(imguiButtonControlVariableData.Label.c_str());//	小さいボタン。文字列の横などに置きやすい
        break;

    case IMGUI_BUTTON_TYPE::ARROW_BUTTON:
        buttonFlag = ImGui::ArrowButton(imguiButtonControlVariableData.Label.c_str(), (ImGuiDir)imguiButtonControlVariableData.ImGuiEnumFlags);//	矢印を表示する四角いボタン。上下左右などの方向を指定
        break;

    case IMGUI_BUTTON_TYPE::INVISIBLE_BUTTON:
        buttonFlag = ImGui::InvisibleButton(imguiButtonControlVariableData.Label.c_str(), imguiButtonControlVariableData.Size, imguiButtonControlVariableData.ImGuiEnumFlags);//	見た目を描画しないボタン。独自の見た目やクリック判定を作る土台
        break;

    case IMGUI_BUTTON_TYPE::CHECK_BOX:
        buttonFlag = ImGui::Checkbox(imguiButtonControlVariableData.Label.c_str(), &imguiButtonControlVariableData.ButtonFlag);//	チェックボックス。クリックで bool の ON/OFF を切り替える
        break;

    case IMGUI_BUTTON_TYPE::CHECK_BOX_FLAGS:
        buttonFlag = ImGui::CheckboxFlags(imguiButtonControlVariableData.Label.c_str(), &imguiButtonControlVariableData.ButtonBitFlag.flags, imguiButtonControlVariableData.ButtonBitFlagValue);//	ビットフラグ用チェックボックス。チェック状態に応じて指定したビットを設定・解除する
        break;

    case IMGUI_BUTTON_TYPE::RADIO_BUTTON:
        buttonFlag = ImGui::RadioButton(imguiButtonControlVariableData.Label.c_str(), &imguiButtonControlVariableData.ButtonFlag);//	ラジオボタン。複数候補から一つを選択する用途
        break;

    case IMGUI_BUTTON_TYPE::COLOR_BUTTON:
        buttonFlag = ImGui::ColorButton(imguiButtonControlVariableData.Label.c_str(), imguiButtonControlVariableData.Color, imguiButtonControlVariableData.ImGuiEnumFlags, imguiButtonControlVariableData.Size);//	色見本をボタンとして表示
        break;

    case IMGUI_BUTTON_TYPE::SELECTABLE:
        buttonFlag = ImGui::Selectable(imguiButtonControlVariableData.Label.c_str(), &imguiButtonControlVariableData.ButtonFlag, imguiButtonControlVariableData.ImGuiEnumFlags, imguiButtonControlVariableData.Size);//	選択可能な項目。選択状態に応じて背景が変わり、リスト項目などに使える
        break;

    case IMGUI_BUTTON_TYPE::MENU_ITEM:
        buttonFlag = ImGui::MenuItem(imguiButtonControlVariableData.Label.c_str(), imguiButtonControlVariableData.PressKeyString.c_str(), &imguiButtonControlVariableData.ButtonFlag, imguiButtonControlVariableData.DrawFlag);//	メニュー内の項目。選択やチェック付き項目に使う
        break;

    case IMGUI_BUTTON_TYPE::TABITEM_BUTTON:
        buttonFlag = ImGui::TabItemButton(imguiButtonControlVariableData.Label.c_str(), imguiButtonControlVariableData.ImGuiEnumFlags);//	タブバー内に配置するボタン。タブ選択とは異なる用途にも使える
        break;

    case IMGUI_BUTTON_TYPE::TEXT_LINK:
        buttonFlag = ImGui::TextLink(imguiButtonControlVariableData.Label.c_str());//	リンク風の文字列ボタン。クリックされたかを取得する
        break;

    case IMGUI_BUTTON_TYPE::TEXT_LINK_OPEN_URL:
        buttonFlag = ImGui::TextLinkOpenURL(imguiButtonControlVariableData.Label.c_str(), imguiButtonControlVariableData.Url.c_str());//	URLを開くリンク風ボタン
        break;

    default:
        return;
    }

    imguiButtonControlVariableData.ArgumentButtonFlag = buttonFlag;
#endif
}

// レイアウトimgui描画
void ImguiManager::DrawLayoutImgui(IMGUI_LAYOUT_CONTROL imguiLayoutControlData)
{
#ifdef _DEBUG
    if (!mbIsImguiExecute)
    {
        return;
    }

    switch (imguiLayoutControlData.LayoutType)
    {
    case IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_TEXT:
        ImGui::Text(u8"");// 指定したテキストを表示
        break;

    case IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_TEXT_FORMAT:
        ImGui::Text(u8"%d", 0);// 指定したテキストを表示(フォーマット付き)
        break;

    
    case IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_SAME_LINE:
        ImGui::SameLine(0.0f, -1.0f);// 次のUI要素を同じ行に配置
        break;

    
    case IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_SEPARATOR:
        ImGui::Separator();// 水平線を描画して区切る
        break;

    
    case IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_SPACING:
        ImGui::Spacing();// UI要素間に空白を追加
        break;
    //==================================================
    // レイアウト・配置関連
    //==================================================

    case IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_NEW_LINE:
        ImGui::NewLine();// 改行する
        break;

    case IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_INDENT:
        ImGui::Indent(0.0f);// 描画位置を右にずらす
        break;

    case IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_UNINDENT:
        ImGui::Unindent(0.0f);// Indent() でずらした描画位置を戻す
        break;

    case IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_DUMMY:
        ImGui::Dummy(ImVec2(10.0f, 10.0f));// 指定したサイズの空白領域を作る
        break;

    case IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_SET_NEXT_ITEM_WIDTH:
        ImGui::SetNextItemWidth(200.0f);// 次に描画する入力項目などの幅を指定する
        break;

    case IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_PUSH_ITEM_WIDTH:
        ImGui::PushItemWidth(200.0f);// 入力項目の幅を設定する（複数項目に適用）
        break;

    case IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_POP_ITEM_WIDTH:
        ImGui::PopItemWidth();// PushItemWidth() で設定した幅を元に戻す
        break;

    case IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_ALIGN_TEXT_TO_FRAME_PADDING:
        ImGui::AlignTextToFramePadding();// 文字をフレーム付き UI の高さに合わせる
        break;

    case IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_SET_NEXT_ITEM_OPEN:
        ImGui::SetNextItemOpen(true, 0);// 次のツリー項目などを開いた状態に設定する
        break;

    //==================================================
    // グループ関連
    //==================================================

    case IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_BEGIN_GROUP:
        ImGui::BeginGroup();// 複数の UI 項目をひとつのグループとして扱う
        break;

    case IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_END_GROUP:
        ImGui::EndGroup();// BeginGroup() で開始したグループを終了する
        break;

    //==================================================
    // 子領域関連
    //==================================================

    case IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_BEGIN_CHILD:
        ImGui::BeginChild("Child", ImVec2(200.0f, 100.0f), 0, 0);// 独立した子領域を作る。サイズやスクロール領域を指定できる
        break;

    case IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_END_CHILD:
        ImGui::EndChild();// BeginChild() で開始した子領域を終了する
        break;

    //==================================================
    // 折りたたみ・ツリー関連
    //==================================================

    case IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_COLLAPSING_HEADER:
        ImGui::CollapsingHeader("Header", 0);// クリックで開閉できる見出しを表示する
        break;

    case IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_TREE_NODE:
        ImGui::TreeNode("Node");// ツリー項目を表示する。開いている間だけ子項目を描画できる
        break;

    case IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_TREE_POP:
        ImGui::TreePop();// TreeNode() で開始したツリー階層を終了する
        break;

    //==================================================
    // 表関連
    //==================================================

    case IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_BEGIN_TABLE:
        ImGui::BeginTable("Table", 2, 0, ImVec2(0, 0), 0.0f);// 表を開始する。列数を指定する
        break;

    case IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_TABLE_SETUP_COLUMN:
        ImGui::TableSetupColumn("Column", 0, 0.0f, 0u);// 列の名前や幅などを設定する
        break;

    case IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_TABLE_HEADERS_ROW:
        ImGui::TableHeadersRow();// 列の見出し行を表示する
        break;

    case IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_TABLE_NEXT_ROW:
        ImGui::TableNextRow(0, 0.0f);// 表の次の行へ移動する
        break;

    case IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_TABLE_NEXT_COLUMN:
        ImGui::TableNextColumn();// 表の次の列へ移動する
        break;

    case IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_TABLE_SET_COLUMN_INDEX:
        ImGui::TableSetColumnIndex(0);// 指定した列へ移動する
        break;

    case IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_END_TABLE:
        ImGui::EndTable();// BeginTable() で開始した表を終了する
        break;

    //==================================================
    // 表示制御・レイアウト補助
    //==================================================

    case IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_PUSH_STYLE_VAR:
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4.0f, 4.0f));// UI 項目間の余白など、指定したスタイル値を一時的に変更する
        break;

    case IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_POP_STYLE_VAR:
        ImGui::PopStyleVar();// PushStyleVar() で変更したスタイル値を元に戻す
        break;

    case IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_PUSH_STYLE_COLOR:
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1, 0, 0, 1));// 指定した色を一時的に変更する
            break;

    case IMGUI_LAYOUT_TYPE::IMGUI_LAYOUT_POP_STYLE_COLOR:
            ImGui::PopStyleColor();// PushStyleColor() で変更した色を元に戻す
            break;
    }
#endif
}

// Imguiグループ描画
void ImguiManager::DrawGroupImgui(IMGUI_GROUP_DATA imguiGroupData)
{
#ifdef _DEBUG
    if (!mbIsImguiExecute)
    {
        return;
    }

    // グループ描画
    if (ImGui::TreeNode(imguiGroupData.GetGroupName().c_str()))
    {
        // imguiControlVariable描画
        for (int i = 0; i < imguiGroupData.GetImguiControlVariableDatas()->size(); i++)
        {
            this->DrawControlVariableImgui((*imguiGroupData.GetImguiControlVariableDatas())[i]);
        }

        // 子グループ描画
        for (int i = 0; i < imguiGroupData.GetChildDatas()->size(); i++)
        {
            DrawGroupImgui((*imguiGroupData.GetChildDatas())[i]);
        }

        ImGui::TreePop();
    }
#endif
}

// グループ種類からグループを検索
ImguiManager::CURRENT_GROUP_TYPE_DATA ImguiManager::SearchImguiGroupData(IMGUI_GROUP_TYPE groupType, IMGUI_GROUP_DATA** imguiGroupData)
{
#ifdef _DEBUG
    if (imguiGroupData == nullptr)
    {
        return CURRENT_GROUP_TYPE_DATA();
    }

    if (!mbIsImguiExecute)
    {
        *imguiGroupData = nullptr;
        return CURRENT_GROUP_TYPE_DATA();
    }
    
    if (groupType == IMGUI_GROUP_TYPE::NONE)
    {
        *imguiGroupData = nullptr;
        return CURRENT_GROUP_TYPE_DATA();
    }
    
    if (mstImguiGroupDatas.size() == 0)
    {
        *imguiGroupData = nullptr;
        return CURRENT_GROUP_TYPE_DATA();
    }

    CURRENT_GROUP_TYPE_DATA currentGroupTypeData;
    currentGroupTypeData.CurrentGroupType = groupType;
    currentGroupTypeData.CurrentGroupTypeIndexs.clear();
    IMGUI_GROUP_DATA* setImguiGroupData = nullptr;

    std::vector<IMGUI_GROUP_DATA>* nextCheckDatas = &mstImguiGroupDatas;
    std::vector<std::vector<IMGUI_GROUP_DATA>*> TemporarySaveImguiGroupDatas;
    TemporarySaveImguiGroupDatas.push_back(nextCheckDatas);
    currentGroupTypeData.CurrentGroupTypeIndexs.push_back(0);
    while (true)
    {
        // 取得し判定
        setImguiGroupData = &(*nextCheckDatas)[currentGroupTypeData.CurrentGroupTypeIndexs[currentGroupTypeData.CurrentGroupTypeIndexs.size() - 1]];
        if (setImguiGroupData->GetGroupType() == groupType)
        {
            *imguiGroupData = setImguiGroupData;
            return currentGroupTypeData;
        }

        // 子情報があるならそちらを調べる
        if (setImguiGroupData->GetChildDatas()->size() > 0)
        {
            nextCheckDatas = setImguiGroupData->GetChildDatas();
            TemporarySaveImguiGroupDatas.push_back(nextCheckDatas);
            currentGroupTypeData.CurrentGroupTypeIndexs.push_back(0);
            continue;
        }
        // 子情報がないなら参照ナンバーを増やす
        else
        {
            // 配列の最後を現在指しているなら親を調べる対象に変更
            if (nextCheckDatas->size() <= (currentGroupTypeData.CurrentGroupTypeIndexs[currentGroupTypeData.CurrentGroupTypeIndexs.size() - 1] + 1))
            {
                while (true)
                {
                    TemporarySaveImguiGroupDatas.pop_back();
                    currentGroupTypeData.CurrentGroupTypeIndexs.pop_back();
                    if (currentGroupTypeData.CurrentGroupTypeIndexs.size() == 0)
                    {
                        *imguiGroupData = nullptr;
                        currentGroupTypeData.CurrentGroupType = IMGUI_GROUP_TYPE::NONE;
                        return CURRENT_GROUP_TYPE_DATA();
                    }
                    nextCheckDatas = TemporarySaveImguiGroupDatas[TemporarySaveImguiGroupDatas.size() - 1];

                    if (nextCheckDatas->size() <= (currentGroupTypeData.CurrentGroupTypeIndexs[currentGroupTypeData.CurrentGroupTypeIndexs.size() - 1] + 1))
                    {
                        continue;
                    }

                    break;
                }
            }

            // 参照ナンバーを増やす
            currentGroupTypeData.CurrentGroupTypeIndexs[currentGroupTypeData.CurrentGroupTypeIndexs.size() - 1] += 1;
        }
    }
#endif
    return CURRENT_GROUP_TYPE_DATA();
}

// 現在参照しているグループを取得
IMGUI_GROUP_DATA* ImguiManager::GetCurrentGroupData()
{
#ifdef _DEBUG
    if (!mbIsImguiExecute)
    {
        return nullptr;
    }

    IMGUI_GROUP_DATA* currentGroupData = nullptr;

    std::vector<IMGUI_GROUP_DATA>* currentGroupDatas = &mstImguiGroupDatas;

    for (int index : mstCurrentGroupTypeData.CurrentGroupTypeIndexs)
    {
        if (index < 0 || index >= currentGroupDatas->size())
        {
            return nullptr;
        }

        currentGroupData = &(*currentGroupDatas)[index];

        currentGroupDatas = currentGroupData->GetChildDatas();
    }

    return currentGroupData;
#else
    return nullptr;
#endif
}

// 変数型を整数か浮動小数の変換
IMGUI_VARIABLE_INTEGER_TYPE ImguiManager::ChangeVariableTypeToVariableIntegerType(IMGUI_VARIABLE_TYPE variableType)
{
    switch (variableType)
    {
        case IMGUI_VARIABLE_TYPE::CHAR:
            return IMGUI_VARIABLE_INTEGER_TYPE::CHAR;
            
        case IMGUI_VARIABLE_TYPE::UNSIGNED_CHAR:
            return IMGUI_VARIABLE_INTEGER_TYPE::UNSIGNED_CHAR;
            
        case IMGUI_VARIABLE_TYPE::SHORT:
            return IMGUI_VARIABLE_INTEGER_TYPE::SHORT;
            
        case IMGUI_VARIABLE_TYPE::UNSIGNED_SHORT:
            return IMGUI_VARIABLE_INTEGER_TYPE::UNSIGNED_SHORT;
            
        case IMGUI_VARIABLE_TYPE::INT:
            return IMGUI_VARIABLE_INTEGER_TYPE::INT;
            
        case IMGUI_VARIABLE_TYPE::UNSIGNED_INT:
            return IMGUI_VARIABLE_INTEGER_TYPE::UNSIGNED_INT;
            
        case IMGUI_VARIABLE_TYPE::LONG:
            return IMGUI_VARIABLE_INTEGER_TYPE::LONG;
            
        case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG:
            return IMGUI_VARIABLE_INTEGER_TYPE::UNSIGNED_LONG;
            
        case IMGUI_VARIABLE_TYPE::LONG_LONG:
            return IMGUI_VARIABLE_INTEGER_TYPE::LONG_LONG;
            
        case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG_LONG:
            return IMGUI_VARIABLE_INTEGER_TYPE::UNSIGNED_LONG_LONG;
            
        case IMGUI_VARIABLE_TYPE::FLOAT:
            return IMGUI_VARIABLE_INTEGER_TYPE::FLOAT;
            
        case IMGUI_VARIABLE_TYPE::DOUBLE:
            return IMGUI_VARIABLE_INTEGER_TYPE::DOUBLE;
            
        case IMGUI_VARIABLE_TYPE::LONG_DOUBLE:
            return IMGUI_VARIABLE_INTEGER_TYPE::LONG_DOUBLE;
            
        default:
            return IMGUI_VARIABLE_INTEGER_TYPE::NONE;
    }
}

// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// WndProcでやるImguiの処理
void ImguiManager::ImguiWndProcProcess(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
#ifdef _DEBUG
    ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam);
#endif
}