#pragma comment(lib, "winmm.lib")

#include "DxLib.h"

#include "Master.h"

#include "DrawManager.h"
#include "EndManager.h"
#include "GameManager.h"
#include "ImguiManager.h"
#include "KeyState.h"
#include "LoadingManager.h"
#include "ResourceManager.h"
#include "StopManager.h"
#include "ThreadManager.h"
#include "TimeManager.h"
#include "ShineManager.h"

#ifdef _DEBUG
#include "DebugLogs/DebugLog.h"
#endif

// マスター静的メンバ変数初期化
DrawManager* Master::mpDrawManager = new DrawManager();
EndManager* Master::mpEndManager = new EndManager();
GameManager* Master::mpGameManager = new GameManager();
ImguiManager* Master::mpImguiManager = new ImguiManager();
KeyState* Master::mpKeyState = new KeyState();
LoadingManager* Master::mpLoadingManager = new LoadingManager();
ResourceManager* Master::mpResourceManager = new ResourceManager();
StopManager* Master::mpStopManager = new StopManager();
ThreadManager* Master::mpThreadManager = new ThreadManager();
TimeManager* Master::mpTimeManager = new TimeManager(/**/1/*/17/**/);
ShineManager* Master::mpShineManager = new ShineManager();

/// <summary>
/// メイン
/// </summary>
/// <param name="hInstance">HINSTANCE</param>
/// <param name="hPrevInstance">HINSTANCE</param>
/// <param name="lpCmdLine">LPSTR</param>
/// <param name="nCmdShow">int</param>
/// <returns>int</returns>
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
#ifdef _DEBUG
	
	// デバッグ初期化
	DEBUG::DebugInitialization(/**/true/*/false/**/);
	
	// デバッグテキストの出力先を新しいファイルにする
	{
		DEBUG::DebugCreateLogFileName();
		DEBUG::DebugLogAddData(DEBUG::DEBUG_PROCESS_TYPE::FUNCTION_CALL);
		DEBUG::DebugLogAddData(DEBUG::DEBUG_PROCESS_TYPE::TIME);

		DEBUG::DebugCreateLogFileName(DEBUG::DEBUG_MAP_TYPE::DEBUG_UNDISCOVERED, {"_graph"});

		DEBUG::DebugCreateLogFileName(DEBUG::DEBUG_MAP_TYPE::DEBUG_SCENE_TITLE, {"_title"});
		DEBUG::DebugLogAddData(DEBUG::DEBUG_PROCESS_TYPE::ALL_FILE_OUTPUT, DEBUG::DEBUG_MAP_TYPE::DEBUG_SCENE_TITLE);
/**/
		DEBUG::DebugCreateLogFileName(DEBUG::DEBUG_MAP_TYPE::DEBUG_EFFECT, {"_effect"});
		DEBUG::DebugLogAddData(DEBUG::DEBUG_PROCESS_TYPE::FUNCTION_CALL, DEBUG::DEBUG_MAP_TYPE::DEBUG_EFFECT);
		DEBUG::DebugLogAddData(DEBUG::DEBUG_PROCESS_TYPE::TIME, DEBUG::DEBUG_MAP_TYPE::DEBUG_EFFECT);//*/
/**/
		DEBUG::DebugCreateLogFileName(DEBUG::DEBUG_MAP_TYPE::DEBUG_GRAPH, {"_graph"});
		DEBUG::DebugLogAddData(DEBUG::DEBUG_PROCESS_TYPE::FUNCTION_CALL, DEBUG::DEBUG_MAP_TYPE::DEBUG_GRAPH);
		DEBUG::DebugLogAddData(DEBUG::DEBUG_PROCESS_TYPE::TIME, DEBUG::DEBUG_MAP_TYPE::DEBUG_GRAPH);//*/
/**/
		DEBUG::DebugCreateLogFileName(DEBUG::DEBUG_MAP_TYPE::DEBUG_3D_MODEL, {"_3d_model"});
		DEBUG::DebugLogAddData(DEBUG::DEBUG_PROCESS_TYPE::FUNCTION_CALL, DEBUG::DEBUG_MAP_TYPE::DEBUG_3D_MODEL);
		DEBUG::DebugLogAddData(DEBUG::DEBUG_PROCESS_TYPE::TIME, DEBUG::DEBUG_MAP_TYPE::DEBUG_3D_MODEL);//*/
		/**/
		DEBUG::DebugCreateLogFileName(DEBUG::DEBUG_MAP_TYPE::DEBUG_FADE, {"_fade"});
		DEBUG::DebugLogAddData(DEBUG::DEBUG_PROCESS_TYPE::FUNCTION_CALL, DEBUG::DEBUG_MAP_TYPE::DEBUG_FADE);
		DEBUG::DebugLogAddData(DEBUG::DEBUG_PROCESS_TYPE::TIME, DEBUG::DEBUG_MAP_TYPE::DEBUG_FADE);//*/
		/**/
		DEBUG::DebugCreateLogFileName(DEBUG::DEBUG_MAP_TYPE::DEBUG_FAILURE_LOG, {"_failureLog"});
		DEBUG::DebugLogAddData(DEBUG::DEBUG_PROCESS_TYPE::FUNCTION_CALL, DEBUG::DEBUG_MAP_TYPE::DEBUG_FAILURE_LOG);
		DEBUG::DebugLogAddData(DEBUG::DEBUG_PROCESS_TYPE::TIME, DEBUG::DEBUG_MAP_TYPE::DEBUG_FAILURE_LOG);//*/

		/**/
		DEBUG::DebugCreateLogFileName(DEBUG::DEBUG_MAP_TYPE::DEBUG_TIME, { "_Time" });
		DEBUG::DebugLogAddData(DEBUG::DEBUG_PROCESS_TYPE::TIME, DEBUG::DEBUG_MAP_TYPE::DEBUG_TIME);//*/

		/**/
		DEBUG::DebugCreateLogFileName(DEBUG::DEBUG_MAP_TYPE::DEBUG_SHINE_POS, { "_ShinePos" });
		DEBUG::DebugLogAddData(DEBUG::DEBUG_PROCESS_TYPE::TIME, DEBUG::DEBUG_MAP_TYPE::DEBUG_SHINE_POS);//*/

/*/
		DEBUG::DebugCreateLogFileName(DEBUG::DEBUG_MAP_TYPE::DEBUG_GAME_MANAGER_WND_PROC, "_GameManager");//*/
	}
#endif

#ifdef _DEBUG
	Master::mpImguiManager->DxInit();
#endif

	// DxLib_Init前初期化
	Master::mpGameManager->DxLib_PreInit();

	// DXライブラリ初期化処理
	if(DxLib_Init() == -1)
	{
		return -1;		// エラーが起きたら直ちに終了
	}

#ifdef _DEBUG
	Master::mpImguiManager->Initilize();
#endif

	// 初期化
	Master::mpGameManager->Initilize();

	// ループ
	while (!Master::mpEndManager->EndFlag()) {

		// ローディング処理
		if (Master::mpLoadingManager->GetLoadingFlag())
		{
			// 読み込み
			Master::mpLoadingManager->Loading();
		}

		
		// メイン処理
		if (Master::mpTimeManager->GetNextUpdateFlag())
		{

#ifdef _DEBUG
			Master::mpImguiManager->Update();
#endif
			// 更新
			Master::mpGameManager->Update();

			// 必要であれば削除する
			Master::mpGameManager->DeleteAllIfNeeded();

			// 描画
			Master::mpGameManager->Draw();
		}
	}

	// 削除
	Master::AllDelete();

	// DXライブラリ使用の終了処理
	DxLib_End();

	// ソフトの終了
	return 0;
}
/*
#include "DxLib.h"
#include <chrono>
#include <cstdio>

using Clock = std::chrono::steady_clock;

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	ChangeWindowMode(TRUE);

	if (DxLib_Init() == -1)
		return -1;

	SetDrawScreen(DX_SCREEN_BACK);

	// 計測用のメモリ画面
	int screen = MakeScreen(640, 480, TRUE);

	if (screen == -1)
	{
		DxLib_End();
		return -1;
	}

	constexpr int COUNT = 100000;

	double switchMs = 0.0;
	double loopMs = 0.0;

	// ウォームアップ
	for (int i = 0; i < 1000; ++i)
	{
		SetDrawScreen(screen);
		SetDrawScreen(DX_SCREEN_BACK);
	}

	// 1. SetDrawScreenの切り替え時間
	{
		auto start = Clock::now();

		for (int i = 0; i < COUNT; ++i)
		{
			SetDrawScreen(screen);
			SetDrawScreen(DX_SCREEN_BACK);
		}

		auto end = Clock::now();

		switchMs =
			std::chrono::duration<double, std::milli>(
				end - start).count();
	}

	// 2. ループと色判定に相当する処理の比較用
	volatile int color = 0;
	{
		auto start = Clock::now();

		for (int i = 0; i < COUNT; ++i)
		{
			if (color == 0)
				color = 1;
			else
				color = 0;
		}

		auto end = Clock::now();

		loopMs =
			std::chrono::duration<double, std::milli>(
				end - start).count();
	}

	// 計測結果をゲーム画面に表示
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		SetDrawScreen(DX_SCREEN_BACK);
		ClearDrawScreen();

		DrawFormatString(20, 20, GetColor(255, 255, 255),
			"SetDrawScreen benchmark");

		DrawFormatString(20, 60, GetColor(255, 255, 0),
			"Switch count: %d", COUNT * 2);

		DrawFormatString(20, 90, GetColor(255, 255, 255),
			"Switch time: %.3f ms", switchMs);

		DrawFormatString(20, 120, GetColor(255, 255, 255),
			"Average per call: %.3f us",
			switchMs * 1000.0 / (COUNT * 2));

		DrawFormatString(20, 160, GetColor(255, 255, 255),
			"Loop test: %.3f ms", loopMs);

		DrawFormatString(20, 210, GetColor(180, 180, 180),
			"Press ESC to exit");

		ScreenFlip();
	}

	DeleteGraph(screen);
	DxLib_End();

	return 0;
}
*/

