#include "CreditScene.h"
#include "DxLib.h"
#include "BaseSceneManager.h"

#include "../H_Katou/Singleton/KeyState.h"

#include "../Z_Except/Master.h"

CreditScene::CreditScene() :
	BaseScene(SceneTag::ST_Credit)
{
}

CreditScene::~CreditScene()
{
}

int CreditScene::Create()
{
	return 0;
}

int CreditScene::Initialize()
{
	return 0;
}

int CreditScene::Finalize()
{
	return 0;
}

int CreditScene::Update()
{
	bool Back =
		Master::mpKeyState->GetShadowGameKeyDown(KEY_SHADOW_GAME_TYPE::B, 0) ||
		Master::mpKeyState->GetShadowGameKeyDown(KEY_SHADOW_GAME_TYPE::B, 1);

	// Bが押された処理
	if (Back)
	{
		// タイトルに戻る
		Master::mpBaseSceneManager->ChangeScene(SceneTag::ST_Title);
		// 
		this->OnResetFlag();
	}
	return 0;
}	

int CreditScene::Draw()
{
	// 
	DxLib::DrawString(
		0.0f,
		0.0f,
		"CREDIT SCENE",
		GetColor(255, 255, 255));

	DxLib::DrawString(
		500,
		400,
		"制作　Team 藤田さん\n\n\nTHANK YOU FOR PLAYING\n\n\n\n\n\nRPESS B BUTTON",
		GetColor(255, 255, 255));
	return 0;
}

// ここら辺に使った素材のサイト名とURLをメモしといてくれるとありがたい
//
//
//
//
//
//
//
//
//
//
//
//
//