#include "TestScene.h"

#include "../A_GameObject/GameObject2D.h"
#include "../A_GameObject/GameObjectManager.h"
#include "../A_GameObject/PlayerObject.h"
#include "../A_GameObject/MirrorObject.h"
#include "../A_GameObject/WallObject.h"

#include "../C_Component/GimmickObjectController.h"

#include "../F_PuzzleGimmick/ButtonTrigger.h"
#include "../F_PuzzleGimmick/LightExecutor.h"

#include "../G_LightArea/LightAreaManager.h"

#include "../S_Collision/BaseCollision2DManager.h"

#include "../Y_Tool/MyFunctions.h"

#include "../Z_Except/Master.h"

TestScene::TestScene()
: mpPlayer(nullptr)
, BaseScene(SceneTag::ST_Test)
{
}

TestScene::~TestScene()
{
}

int TestScene::Create()
{
	this->mpGameObjectManager = new GameObjectManager();
	this->mpBaseCollision2DManager = new BaseCollision2DManager();

	GameObject2D *currentObject = nullptr;

	currentObject = new PlayerObject(1);
	this->mpGameObjectManager->Add(currentObject);
	currentObject = new PlayerObject(2);
	this->mpGameObjectManager->Add(currentObject);

	const VECTOR2D tempBlockSize = VECTOR2D(150.0f, 150.0f);
	const VECTOR2D tempCenterStart = tempBlockSize * 0.5f;
	VECTOR2D tempCenter;

	tempCenter = tempCenterStart + VECTOR2D(tempBlockSize.GetX() * 1.0f, tempBlockSize.GetY() * 1.0f);
	currentObject = new WallObject(false, tempCenter, tempBlockSize);
	this->mpGameObjectManager->Add(currentObject);

	tempCenter = tempCenterStart + VECTOR2D(tempBlockSize.GetX() * 2.0f, tempBlockSize.GetY() * 2.0f);
	currentObject = new MirrorObject(false, tempCenter, tempBlockSize, 2);
	this->mpGameObjectManager->Add(currentObject);

	tempCenter = tempCenterStart + VECTOR2D(tempBlockSize.GetX() * 3.0f, tempBlockSize.GetY() * 4.0f);
	currentObject = new MirrorObject(false, tempCenter, tempBlockSize, 0);
	this->mpGameObjectManager->Add(currentObject);

	tempCenter = tempCenterStart + VECTOR2D(tempBlockSize.GetX() * 4.0f, tempBlockSize.GetY() * 2.0f);
	int useLightCount = 1;
	for (int i = 0; i < useLightCount; i++)
	{
		// 
		if (Master::mpLightManager->SearchArea(i) == nullptr)
		{
			// 
			Master::mpLightManager->AddArea(new LightArea());
		}
	}

	WallObject *gimmickObject = new WallObject(true, tempCenter, tempBlockSize);
	GimmickObjectController *gimmickController = gimmickObject->GetGimmickController();
	gimmickController->AddGimmick(
		new ButtonTrigger,
		new LightExecutor(
			PuzzleGimmickActiveParam::Create(true, false),
			gimmickObject,
			0,
			300,
			MyFunctions::Deg2Rad(198.5f),
			MyFunctions::Deg2Rad(135.0f),
			10000.0f));

	this->mpGameObjectManager->Add(gimmickObject);

	this->mpGameObjectManager->Create();
	return 0;
}

int TestScene::Initialize()
{
	this->mpGameObjectManager->Initialize();
	return 0;
}

int TestScene::Finalize()
{
	this->mpGameObjectManager->Finalize();
	return 0;
}

int TestScene::Update()
{
	// ここでMoveVecを0にしておく
	this->mpGameObjectManager->ResetMoveVec();

	// 先にやりたい処理
	this->mpGameObjectManager->EarlyUpdate();

	// 通常処理
	this->mpGameObjectManager->Update();

	// 当たり判定の計算 + スライド移動 + 当たり判定のイベント通知
	this->mpBaseCollision2DManager->CheckHitAllMove();

	// ゲームオブジェクトの座標を更新
	this->mpGameObjectManager->SetPositionToMoveVec();

	// 当たり判定の座標を更新
	this->mpGameObjectManager->SetCollisionPosToCollisionMoveVec();

	// 座標更新後の処理
	this->mpGameObjectManager->LateUpdate();

	// モデルの更新処理
	this->mpGameObjectManager->UpdateModel();

	// 成功を返す
	return 0;
}

int TestScene::Draw()
{
	this->mpGameObjectManager->Draw();
	return 0;
}
