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
{
    mstImguiFloatDatas.clear();
    mstImguiIntDatas.clear();
}

ImguiManager::~ImguiManager()
{
}
// èâä˙âª
void ImguiManager::Initilize()
{
#ifdef _DEBUG
    if (mbIsImguiExecute)
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

        ImGui::StyleColorsDark();

        ImGui_ImplWin32_Init(DxLib::GetMainWindowHandle());
        ImGui_ImplDX11_Init((ID3D11Device*)DxLib::GetUseDirect3D11Device(), (ID3D11DeviceContext*)DxLib::GetUseDirect3D11DeviceContext());
    }
#endif
}

// èIóπ
void ImguiManager::Finalize()
{
#ifdef _DEBUG
    if (mbIsImguiExecute)
    {
        ImGui_ImplDX11_Shutdown();
        ImGui_ImplWin32_Shutdown();
        ImGui::DestroyContext();
    }
#endif
}

// çXêV
void ImguiManager::Update()
{
#ifdef _DEBUG
    if (mbIsImguiExecute)
    {
        // ImGui ÉtÉåÅ[ÉÄäJén
        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();
        ImGui::ShowDemoWindow();
        mnAddNumber = 0;

        //DEBUG::SaveText("CLICK");
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
    }
#endif
}

// ï`âÊ
void ImguiManager::Draw()
{
#ifdef _DEBUG
    if (mbIsImguiExecute)
    {
        // ImGui ÉtÉåÅ[ÉÄèIóπÇ∆ï`âÊ
        ImGui::Render();
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

        // DXLib Direct3Dê›íËÇïúå≥
        RefreshDxLibDirect3DSetting();
    }
#endif
}


// Imguií«â¡ï`âÊ
void ImguiManager::AddDrawImgui(IMGUI_FLOAT_DATA imguiFloatData)
{
#ifdef _DEBUG
    if (mbIsImguiExecute)
    {
        if (imguiFloatData.AddNumberDrawFlag == true)
        {
            imguiFloatData.Label = imguiFloatData.Label + "_" + std::to_string(mnAddNumber);
        }
        ++mnAddNumber;
        DrawFloatImgui(imguiFloatData);
    }
#endif
}
// Imguií«â¡ï`âÊ
void ImguiManager::AddDrawImgui(IMGUI_INT_DATA imguiIntData)
{
#ifdef _DEBUG
    if (mbIsImguiExecute)
    {
        if (imguiIntData.AddNumberDrawFlag == true)
        {
            imguiIntData.Label = imguiIntData.Label + "_" + std::to_string(mnAddNumber);
        }
        ++mnAddNumber;
        DrawIntImgui(imguiIntData);
    }
#endif
}

// floatÇÃImguuiï`âÊ
void ImguiManager::DrawFloatImgui(IMGUI_FLOAT_DATA imguiFloatData)
{
#ifdef _DEBUG
    if (mbIsImguiExecute)
    {
        for (int i = 0; i < imguiFloatData.VariableDatas.size(); i++)
        {
            if (i >= 4)
            {
                break;
            }
            if ((std::fabs(*(imguiFloatData.VariableDatas[i])) - imguiFloatData.PreVariable[i]) < 0.00000001f/*floatåÎç∑*/)
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
    }
#endif
}


// intÇÃImguuiï`âÊ
void ImguiManager::DrawIntImgui(IMGUI_INT_DATA imguiIntData)
{
#ifdef _DEBUG
    if (mbIsImguiExecute)
    {
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
    }
#endif
}


// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

/// <summary>WndProcÇ≈Ç‚ÇÈImguiÇÃèàóù</summary>
void ImguiManager::ImguiWndProcProcess(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam);
}