#pragma once
#include <Windows.h>

#include "VECTOR.h"

#include "DxLib.h"

class DxLibDataManager
{
private:
	// 描画画面サイズ
	VECTOR2D mstDisplaySize;

	// 初期化フラグ
	bool mbIsInitialized;
public:
	DxLibDataManager();
	~DxLibDataManager();

	// DXInit前初期化
	void DxInitPreInitialize();

	// 初期化
	void Initialize();

	// 終了
	void Finalize();

	// 新しく描画するディスプレイのサイズを設定
	void SettingNewDisplaySize(VECTOR2D newDisplaySize);

	/*----------------------------------*/
	/*【ウィンドウプロシージャ使用関数】*/
	/*----------------------------------*/

	/// <summary>別アプリ移動</summary>
	void OnDeactivate();
	/// <summary>別アプリからこのアプリに移動</summary>
	void OnActivate();
	/// <summary>初期化済みフラグ</summary>
	/// <returns>初期化しているなら「true」を返す</returns>
	inline bool GetInitializedFlag() { return mbIsInitialized; }
};