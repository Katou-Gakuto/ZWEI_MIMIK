#include "VECTOR.h"

#include "DxLib.h"

#include "DxLibDataManager.h"

#include "Master.h"

#include "LightAreaManager.h"
#include "KeyState.h"
#include "TimeManager.h"
#include "DrawSystem.h"

#ifdef _DEBUG
#include "ImguiManager.h""
#endif

LRESULT WINAPI DxLibDataManagerWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

DxLibDataManager::DxLibDataManager(VECTOR2D startDisplaySize)
: START_DISPLAY_SIZE(startDisplaySize)
, mstDisplaySize(startDisplaySize)
, mstWorldSize(VECTOR2D(1920, 1080))
, GAME_DISPLAY_ASPECT_RATIO(VECTOR2D(16, 9))
, mbIsInitialized(false)
{
}

DxLibDataManager::~DxLibDataManager()
{
}

// DXInit前初期化
void DxLibDataManager::DxInitPreInitialize()
{
    SetGraphMode(mstDisplaySize.GetX(), mstDisplaySize.GetY(), 32);
    SetWindowSizeChangeEnableFlag(FALSE, TRUE); //ウィンドウの端をつかんでサイズ変更可能にするかどうか
    SetMainWindowText("ZWEI MIMK");            //ウィンドウのタイトルを設定

    SetHookWinProc(DxLibDataManagerWndProc);
    DxLib::SetAlwaysRunFlag(TRUE);
    DxLib::SetAlwaysRunFlag(FALSE);

    // 描画情報設定
    SettingDrawSizeData();
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
void DxLibDataManager::SettingNewDisplaySize(VECTOR2D newDisplaySize, bool windowmode)
{
    //ChangeWindowMode(windowmode); // ウィンドウモードで描画するか
    float Win_Size_Rat_X = newDisplaySize.GetX() / START_DISPLAY_SIZE.GetX();
    float Win_Size_Rat_Y = newDisplaySize.GetY() / START_DISPLAY_SIZE.GetY();
    SetWindowSizeExtendRate(Win_Size_Rat_X, Win_Size_Rat_Y); // ウィンドウのサイズを変更
    mstDisplaySize = newDisplaySize;

    // 描画情報設定
    //SettingDrawSizeData();
}

// 描画サイズ情報設定
void DxLibDataManager::SettingDrawSizeData()
{
    VECTOR2D displayMargin = VECTOR2D(0.0f, 0.0f);

    int gameSizeRatioValueX = static_cast<int>(mstDisplaySize.GetX() / GAME_DISPLAY_ASPECT_RATIO.GetX());
    int gameSizeRatioValueY = static_cast<int>(mstDisplaySize.GetY() / GAME_DISPLAY_ASPECT_RATIO.GetY());

    if (gameSizeRatioValueX < gameSizeRatioValueY)
    {
        displayMargin.SetX(mstDisplaySize.GetX() - (gameSizeRatioValueX * GAME_DISPLAY_ASPECT_RATIO.GetX()));
        displayMargin.SetY(mstDisplaySize.GetY() - (gameSizeRatioValueX * GAME_DISPLAY_ASPECT_RATIO.GetY()));
    }
    else if (gameSizeRatioValueX > gameSizeRatioValueY)
    {
        displayMargin.SetX(mstDisplaySize.GetX() - (gameSizeRatioValueY * GAME_DISPLAY_ASPECT_RATIO.GetX()));
        displayMargin.SetY(mstDisplaySize.GetY() - (gameSizeRatioValueY * GAME_DISPLAY_ASPECT_RATIO.GetY()));
    }
    else
    {
        displayMargin.SetX(mstDisplaySize.GetX() - (gameSizeRatioValueX * GAME_DISPLAY_ASPECT_RATIO.GetX()));
        displayMargin.SetY(mstDisplaySize.GetY() - (gameSizeRatioValueY * GAME_DISPLAY_ASPECT_RATIO.GetY()));
    }

    displayMargin *= 0;
    // 
    VECTOR2D setStageSize[DRAW_SYSTEM::STAGE_SIZE_TYPE::STAGE_SIZE_TYPE_MAX] = {
        START_DISPLAY_SIZE - displayMargin,//mstDisplaySize/* - displayMargin*/,         // ディスプレイ座標
        mstWorldSize,           // ワールド座標
        displayMargin * 0.5f    // 左上からのずれ
    };

    DRAW_SYSTEM::SetStazeSize(setStageSize);
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