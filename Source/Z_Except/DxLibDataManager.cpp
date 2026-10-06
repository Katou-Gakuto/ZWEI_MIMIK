#include "VECTOR.h"

#include "DxLib.h"

#include "DxLibDataManager.h"

#include "Master.h"

#include "LightAreaManager.h"
#include "KeyState.h"
#include "TimeManager.h"

#ifdef _DEBUG
#include "ImguiManager.h""
#endif

LRESULT WINAPI DxLibDataManagerWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

DxLibDataManager::DxLibDataManager()
: mstDisplaySize()
, mbIsInitialized(false)
{
}

DxLibDataManager::~DxLibDataManager()
{
}

// DXInit前初期化
void DxLibDataManager::DxInitPreInitialize()
{
    SetHookWinProc(DxLibDataManagerWndProc);
    DxLib::SetAlwaysRunFlag(TRUE);
    DxLib::SetAlwaysRunFlag(FALSE);

    int screenW, screenH;
    GetScreenState(&screenW, &screenH, NULL);
    mstDisplaySize.SetXY(static_cast<float>(screenW), static_cast<float>(screenH));
}

// 初期化
void DxLibDataManager::Initialize()
{
    mbIsInitialized = true;
}

// 終了
void DxLibDataManager::Finalize()
{
    SetHookWinProc(NULL);
}

// 新しく描画するディスプレイのサイズを設定
void DxLibDataManager::SettingNewDisplaySize(VECTOR2D newDisplaySize)
{
    SetDrawArea(0, 0, newDisplaySize.GetX(), newDisplaySize.GetY());
    mstDisplaySize = newDisplaySize;
}

// 別アプリ移動
void DxLibDataManager::OnDeactivate()
{
    // 時間
    Master::mpTimeManager->OnEnterBackground();
}

// 別アプリからこのアプリに移動
void DxLibDataManager::OnActivate()
{
    // 時間
    Master::mpTimeManager->OnReturnForeground();
}


// ウィンドウプロシージャの定義
LRESULT WINAPI DxLibDataManagerWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (!Master::mpDxLibDataManager->GetInitializedFlag())
    {
        return 0;
    }

#ifdef _DEBUG
    Master::mpImguiManager->ImguiWndProcProcess(hWnd, msg, wParam, lParam);
    //DEBUG::SaveText("GAME MAnager WndProc\n", DEBUG::DEBUG_MAP_TYPE::DEBUG_GAME_MANAGER_WND_PROC);
#endif
    Master::mpKeyState->KeyStateWndProcProcess(hWnd, msg, wParam, lParam);

    switch (msg)
    {
    case WM_ACTIVATEAPP:
    {
        if (wParam == FALSE)
        {
            // =========================
            // 別アプリへ切り替わった
            // Alt+Tab など
            // =========================
            Master::mpDxLibDataManager->OnDeactivate();
#ifdef _DEBUG
            //DEBUG::SaveText("別アプリへ切り替わった\n", DEBUG::DEBUG_MAP_TYPE::DEBUG_GAME_MANAGER_WND_PROC);
#endif
        }
        else
        {
            // =========================
            // アプリへ戻ってきた
            // =========================
            Master::mpDxLibDataManager->OnActivate();
#ifdef _DEBUG
            //DEBUG::SaveText("アプリへ戻ってきた\n", DEBUG::DEBUG_MAP_TYPE::DEBUG_GAME_MANAGER_WND_PROC);
#endif
        }
    }
    break;

    case WM_ACTIVATE:
    {
        if (LOWORD(wParam) == WA_INACTIVE)
        {
            // 非アクティブ
#ifdef _DEBUG
            //DEBUG::SaveText("非アクティブ\n", DEBUG::DEBUG_MAP_TYPE::DEBUG_GAME_MANAGER_WND_PROC);
#endif
        }
        else
        {
            // アクティブ
#ifdef _DEBUG
            //::SaveText("アクティブ\n", DEBUG::DEBUG_MAP_TYPE::DEBUG_GAME_MANAGER_WND_PROC);
#endif
        }
    }
    break;

    case WM_KILLFOCUS:
    {
        // フォーカス失った
#ifdef _DEBUG
            //DEBUG::SaveText("フォーカス失った\n", DEBUG::DEBUG_MAP_TYPE::DEBUG_GAME_MANAGER_WND_PROC);
#endif
    }
    break;

    case WM_SETFOCUS:
    {
        // フォーカス取得
#ifdef _DEBUG
            //DEBUG::SaveText("フォーカス取得\n", DEBUG::DEBUG_MAP_TYPE::DEBUG_GAME_MANAGER_WND_PROC);
#endif
    }
    break;

    case WM_DESTROY:
    {
        PostQuitMessage(0);
        return 0;
    }
    }

    return 0;
}