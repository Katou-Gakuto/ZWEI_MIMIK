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
    mstImguiFloatDatas.clear();
    mstImguiIntDatas.clear();
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

    DEBUG::SaveText("CLICK");
    if (ImGui::Button("Test Button"))
    {
        DEBUG::SaveText("CLICK\n\n");
    }

    for (int i = 0; i < mstImguiFloatDatas.size(); i++)
    {
        DrawFloatImgui(mstImguiFloatDatas[i]);
    }

    for (int i = 0; i < mstImguiIntDatas.size(); i++)
    {
        DrawIntImgui(mstImguiIntDatas[i]);
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
void ImguiManager::AddDrawImgui(IMGUI_FLOAT_DATA imguiFloatData)
{
#ifdef _DEBUG
    if (!mbIsImguiExecute)
    {
        return;
    }
    
    if (imguiFloatData.AddNumberDrawFlag == true)
    {
        imguiFloatData.Label = imguiFloatData.Label + "_" + std::to_string(mnAddNumber);
    }
    ++mnAddNumber;
    DrawFloatImgui(imguiFloatData);
#endif
}
// Imgui追加描画
void ImguiManager::AddDrawImgui(IMGUI_INT_DATA imguiIntData)
{
#ifdef _DEBUG
    if (!mbIsImguiExecute)
    {
        return;
    }
    
    if (imguiIntData.AddNumberDrawFlag == true)
    {
        imguiIntData.Label = imguiIntData.Label + "_" + std::to_string(mnAddNumber);
    }
    ++mnAddNumber;
    DrawIntImgui(imguiIntData);
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
// Imguiグループ追加描画(float)
void ImguiManager::AddDrawImguiGroup(IMGUI_FLOAT_DATA imguiFloatData, IMGUI_GROUP_TYPE groupType, std::string groupName)
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
        imguiGroupData->AddFloatData(imguiFloatData);
        return;
    }

    // グループが存在しない場合は新規作成
    IMGUI_GROUP_DATA newGroupData = IMGUI_GROUP_DATA::GetImguiGroupData(groupName, groupType);

    newGroupData.AddFloatData(imguiFloatData);

    mstImguiGroupDatas.push_back(newGroupData);
#endif
}
// Imguiグループ追加描画(int)
void ImguiManager::AddDrawImguiGroup(IMGUI_INT_DATA imguiIntData, IMGUI_GROUP_TYPE groupType, std::string groupName)
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
        imguiGroupData->AddIntData(imguiIntData);
        return;
    }

    // グループが存在しない場合は新規作成
    IMGUI_GROUP_DATA newGroupData = IMGUI_GROUP_DATA::GetImguiGroupData(groupName, groupType);

    newGroupData.AddIntData(imguiIntData);

    mstImguiGroupDatas.push_back(newGroupData);
#endif
}

// Imguiグループ追加描画(参照int情報) ※StartGroupを読んでから使用してください
void ImguiManager::AddDrawImguiGroup(IMGUI_FLOAT_DATA imguiFloatData)
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

    imguiGroupData->AddFloatData(imguiFloatData);
#endif    
}
// Imguiグループ追加描画(参照float情報)
void ImguiManager::AddDrawImguiGroup(IMGUI_INT_DATA imguiIntData)
{
#ifdef _DEBUG
    if (!mbIsImguiExecute)
    {
        return;
    }

    IMGUI_GROUP_DATA* imguiGroupData = GetCurrentGroupData();

    if (imguiGroupData == nullptr)
    {
        MessageBoxA(nullptr, "ImguiManager::AddDrawImguiGroup(int)\nStartGroup()が呼ばれていないため、追加できません。", "StartGroup()が呼ばれていません。",MB_OK | MB_ICONERROR);
        __debugbreak();
    }

    imguiGroupData->AddIntData(imguiIntData);
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
                TemporarySaveImguiGroupDatas.pop_back();
                currentGroupTypeIndexs.pop_back();

                if (currentGroupTypeIndexs.size() == 0)
                {
                    break;
                }

                nextCheckDatas = TemporarySaveImguiGroupDatas[TemporarySaveImguiGroupDatas.size() - 1];
                continue;
            }

            // 参照ナンバーを増やす
            currentGroupTypeIndexs[currentGroupTypeIndexs.size() - 1] += 1;
        }
    }
#endif
}

// floatのImguui描画
void ImguiManager::DrawFloatImgui(IMGUI_FLOAT_DATA imguiFloatData)
{
#ifdef _DEBUG
    if (!mbIsImguiExecute)
    {
        return;
    }

    for (int i = 0; i < imguiFloatData.VariableDatas.size(); i++)
    {
        if (i >= 4)
        {
            break;
        }
        if ((std::fabs(*(imguiFloatData.VariableDatas[i])) - imguiFloatData.PreVariable[i]) < 0.00000001f/*float誤差*/)
        {
            continue;
        }

        imguiFloatData.ChangeVariable[i] += *(imguiFloatData.VariableDatas[i]) - imguiFloatData.PreVariable[i];
    }
    switch (imguiFloatData.ImguiType)
    {
    case IMGUI_TYPE::SLIDER1:
        ImGui::SliderFloat(imguiFloatData.Label.c_str(), imguiFloatData.ChangeVariable, imguiFloatData.Min, imguiFloatData.Max, imguiFloatData.Format.c_str(), imguiFloatData.Flag);
        break;

    case IMGUI_TYPE::SLIDER2:
        ImGui::SliderFloat2(imguiFloatData.Label.c_str(), imguiFloatData.ChangeVariable, imguiFloatData.Min, imguiFloatData.Max, imguiFloatData.Format.c_str(), imguiFloatData.Flag);
        break;

    case IMGUI_TYPE::SLIDER3:
        ImGui::SliderFloat3(imguiFloatData.Label.c_str(), imguiFloatData.ChangeVariable, imguiFloatData.Min, imguiFloatData.Max, imguiFloatData.Format.c_str(), imguiFloatData.Flag);
        break;

    case IMGUI_TYPE::SLIDER4:
        ImGui::SliderFloat4(imguiFloatData.Label.c_str(), imguiFloatData.ChangeVariable, imguiFloatData.Min, imguiFloatData.Max, imguiFloatData.Format.c_str(), imguiFloatData.Flag);
        break;

    case IMGUI_TYPE::DRAG1:
        ImGui::DragFloat(imguiFloatData.Label.c_str(), imguiFloatData.ChangeVariable, imguiFloatData.Speed, imguiFloatData.Min, imguiFloatData.Max, imguiFloatData.Format.c_str(), imguiFloatData.Flag);
        break;

    case IMGUI_TYPE::DRAG2:
        ImGui::DragFloat2(imguiFloatData.Label.c_str(), imguiFloatData.ChangeVariable, imguiFloatData.Speed, imguiFloatData.Min, imguiFloatData.Max, imguiFloatData.Format.c_str(), imguiFloatData.Flag);
        break;

    case IMGUI_TYPE::DRAG3:
        ImGui::DragFloat3(imguiFloatData.Label.c_str(), imguiFloatData.ChangeVariable, imguiFloatData.Speed, imguiFloatData.Min, imguiFloatData.Max, imguiFloatData.Format.c_str(), imguiFloatData.Flag);
        break;

    case IMGUI_TYPE::DRAG4:
        ImGui::DragFloat4(imguiFloatData.Label.c_str(), imguiFloatData.ChangeVariable, imguiFloatData.Speed, imguiFloatData.Min, imguiFloatData.Max, imguiFloatData.Format.c_str(), imguiFloatData.Flag);
        break;

    case IMGUI_TYPE::INPUT1:
        ImGui::InputFloat(imguiFloatData.Label.c_str(), imguiFloatData.ChangeVariable, imguiFloatData.Step, imguiFloatData.StepFast, imguiFloatData.Format.c_str(), imguiFloatData.Flag);
        break;

    case IMGUI_TYPE::INPUT2:
        ImGui::InputFloat2(imguiFloatData.Label.c_str(), imguiFloatData.ChangeVariable, imguiFloatData.Format.c_str(), imguiFloatData.Flag);
        break;

    case IMGUI_TYPE::INPUT3:
        ImGui::InputFloat3(imguiFloatData.Label.c_str(), imguiFloatData.ChangeVariable, imguiFloatData.Format.c_str(), imguiFloatData.Flag);
        break;

    case IMGUI_TYPE::INPUT4:
        ImGui::InputFloat4(imguiFloatData.Label.c_str(), imguiFloatData.ChangeVariable, imguiFloatData.Format.c_str(), imguiFloatData.Flag);
        break;

    case IMGUI_TYPE::ANGLE:
        ImGui::SliderAngle(imguiFloatData.Label.c_str(), imguiFloatData.ChangeVariable, imguiFloatData.Min, imguiFloatData.Max, imguiFloatData.Format.c_str(), imguiFloatData.Flag);
        break;
    }

    for (int i = 0; i < imguiFloatData.VariableDatas.size(); i++)
    {
        if (i >= 4)
        {
            break;
        }

        *(imguiFloatData.VariableDatas[i]) = imguiFloatData.ChangeVariable[i];
        imguiFloatData.PreVariable[i] = *(imguiFloatData.VariableDatas[i]);
    }
#endif
}


// intのImguui描画
void ImguiManager::DrawIntImgui(IMGUI_INT_DATA imguiIntData)
{
#ifdef _DEBUG
    if (!mbIsImguiExecute)
    {
        return;
    }

    for (int i = 0; i < imguiIntData.VariableDatas.size(); i++)
    {
        if (i >= 4)
        {
            break;
        }

        if (*(imguiIntData.VariableDatas[i]) == imguiIntData.PreVariable[i])
        {
            continue;
        }

        imguiIntData.ChangeVariable[i] += *(imguiIntData.VariableDatas[i]) - imguiIntData.PreVariable[i];
    }
    switch (imguiIntData.ImguiType)
    {
    case IMGUI_TYPE::SLIDER1:
        ImGui::SliderInt(imguiIntData.Label.c_str(), imguiIntData.ChangeVariable, imguiIntData.Min, imguiIntData.Max, imguiIntData.Format.c_str(), imguiIntData.Flag);
        break;

    case IMGUI_TYPE::SLIDER2:
        ImGui::SliderInt2(imguiIntData.Label.c_str(), imguiIntData.ChangeVariable, imguiIntData.Min, imguiIntData.Max, imguiIntData.Format.c_str(), imguiIntData.Flag);
        break;

    case IMGUI_TYPE::SLIDER3:
        ImGui::SliderInt3(imguiIntData.Label.c_str(), imguiIntData.ChangeVariable, imguiIntData.Min, imguiIntData.Max, imguiIntData.Format.c_str(), imguiIntData.Flag);
        break;

    case IMGUI_TYPE::SLIDER4:
        ImGui::SliderInt4(imguiIntData.Label.c_str(), imguiIntData.ChangeVariable, imguiIntData.Min, imguiIntData.Max, imguiIntData.Format.c_str(), imguiIntData.Flag);
        break;

    case IMGUI_TYPE::DRAG1:
        ImGui::DragInt(imguiIntData.Label.c_str(), imguiIntData.ChangeVariable, imguiIntData.Speed, imguiIntData.Min, imguiIntData.Max, imguiIntData.Format.c_str(), imguiIntData.Flag);
        break;

    case IMGUI_TYPE::DRAG2:
        ImGui::DragInt2(imguiIntData.Label.c_str(), imguiIntData.ChangeVariable, imguiIntData.Speed, imguiIntData.Min, imguiIntData.Max, imguiIntData.Format.c_str(), imguiIntData.Flag);
        break;

    case IMGUI_TYPE::DRAG3:
        ImGui::DragInt3(imguiIntData.Label.c_str(), imguiIntData.ChangeVariable, imguiIntData.Speed, imguiIntData.Min, imguiIntData.Max, imguiIntData.Format.c_str(), imguiIntData.Flag);
        break;

    case IMGUI_TYPE::DRAG4:
        ImGui::DragInt4(imguiIntData.Label.c_str(), imguiIntData.ChangeVariable, imguiIntData.Speed, imguiIntData.Min, imguiIntData.Max, imguiIntData.Format.c_str(), imguiIntData.Flag);
        break;

    case IMGUI_TYPE::INPUT1:
        ImGui::InputInt(imguiIntData.Label.c_str(), imguiIntData.ChangeVariable, imguiIntData.Step, imguiIntData.StepFast, imguiIntData.Flag);
        break;

    case IMGUI_TYPE::INPUT2:
        ImGui::InputInt2(imguiIntData.Label.c_str(), imguiIntData.ChangeVariable, imguiIntData.Flag);
        break;

    case IMGUI_TYPE::INPUT3:
        ImGui::InputInt3(imguiIntData.Label.c_str(), imguiIntData.ChangeVariable, imguiIntData.Flag);
        break;

    case IMGUI_TYPE::INPUT4:
        ImGui::InputInt4(imguiIntData.Label.c_str(), imguiIntData.ChangeVariable, imguiIntData.Flag);
        break;
    }

    for (int i = 0; i < imguiIntData.VariableDatas.size(); i++)
    {
        if (i >= 4)
        {
            break;
        }

        *(imguiIntData.VariableDatas[i]) = imguiIntData.ChangeVariable[i];
        imguiIntData.PreVariable[i] = *(imguiIntData.VariableDatas[i]);
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
        // float描画
        for (int i = 0; i < imguiGroupData.GetFloatDatas()->size(); i++)
        {
            DrawFloatImgui((*imguiGroupData.GetFloatDatas())[i]);
        }

        // int描画
        for (int i = 0; i < imguiGroupData.GetIntDatas()->size(); i++)
        {
            DrawIntImgui((*imguiGroupData.GetIntDatas())[i]);
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
                TemporarySaveImguiGroupDatas.pop_back();
                currentGroupTypeData.CurrentGroupTypeIndexs.pop_back();
                if (currentGroupTypeData.CurrentGroupTypeIndexs.size() == 0)
                {
                    *imguiGroupData = nullptr;
                    currentGroupTypeData.CurrentGroupType = IMGUI_GROUP_TYPE::NONE;
                    break;
                }
                nextCheckDatas = TemporarySaveImguiGroupDatas[TemporarySaveImguiGroupDatas.size() - 1];
                continue;
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

// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// WndProcでやるImguiの処理
void ImguiManager::ImguiWndProcProcess(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
#ifdef _DEBUG
    ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam);
#endif
}