#pragma once
#include <Windows.h>

#include "VECTOR.h"

#include "DxLib.h"

class DxLibDataManager
{
private:
	const VECTOR2D START_DISPLAY_SIZE;

	// 描画画面サイズ
	VECTOR2D mstDisplaySize;

	// 世界サイズ
	VECTOR2D mstWorldSize;

	// ゲームディスプレイ画面割合のアスペクト比
	const VECTOR2D GAME_DISPLAY_ASPECT_RATIO;

	// 初期化フラグ
	bool mbIsInitialized;
public:
	DxLibDataManager(VECTOR2D startDisplaySize);
	~DxLibDataManager();

	// DXInit前初期化
	void DxInitPreInitialize();

	// 初期化
	void Initialize();

	// 終了
	void Finalize();

	// 新しく描画するディスプレイのサイズを設定
	void SettingNewDisplaySize(VECTOR2D newDisplaySize);

	// ディスプレイのサイズ取得
	inline VECTOR2D GetDisplaySize() const { return START_DISPLAY_SIZE/*mstDisplaySize*/; }
	// 開始時ディスプレイのサイズ取得
	inline VECTOR2D GetStartDisplaySize() const { return START_DISPLAY_SIZE; }
	// 世界のサイズ取得
	inline VECTOR2D GetWorldSize() const { return mstWorldSize; }

	/*----------------------------------*/
	/*【ウィンドウプロシージャ使用関数】*/
	/*----------------------------------*/

	/// <summary>別アプリ移動</summary>
	void OnDeactivate();
	/// <summary>別アプリからこのアプリに移動</summary>
	void OnActivate();
	/// <summary>初期化済みフラグ</summary>
	/// <returns>初期化しているなら「true」を返す</returns>
	inline bool GetInitializedFlag() const { return mbIsInitialized; }

private:
	// 描画サイズ情報設定
	void SettingDrawSizeData();
};