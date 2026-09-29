#include "DXModelAnim.h"
#include "../A_GameObject/GameObject2D.h"
#include "../Z_Except/Master.h"
#include "../Z_Except/ResourceManager.h"

DXAnimModel::DXAnimModel(GameObject *myObject) : BaseModel(myObject, ModelType_Model2D, static_cast<ScreenNumber>(0))
{
	GraphHandle= -1;
}

DXAnimModel::~DXAnimModel()
{
}

int DXAnimModel::Initialize()
{
	NowPageFrame = 0;
	NowPage = 0;
	return 0;
}

int DXAnimModel::Update()
{
	NowPageFrame++;
	if (NowPageFrame > MaxPageFrame)
	{
		NowPageFrame = 0;
		NowPage++;

		// ずらす
		uvLeftUp.SetX(uvLeftUp.GetX() + UVWidth);

		if (NowPage >= MaxPage)
		{
			NowPage = 0;
			uvLeftUp.SetX(0.0f);
			uvRightDown.SetX(UVWidth);
		}
	}
	return 0;
}

int DXAnimModel::Draw()
{
	Update();
    auto model = static_cast<GameObject2D *>(this->GetUp());
    VECTOR2D pos = model->GetPosition();

	// 描画
	Master::DrawGraphAnim(
		VECTOR2D(pos.GetX() - (Master::PlayerSizeXY / 2), pos.GetY() - (Master::PlayerSizeXY / 2)),
		VECTOR2D(pos.GetX() + (Master::PlayerSizeXY / 2), pos.GetY() + (Master::PlayerSizeXY / 2)),
		uvLeftUp,
		uvRightDown,
		GraphHandle);//this->GetModelNumber());
	return 0;
}

int DXAnimModel::Finalize()
{
	return 0;
}

// 色々設定(画像パス アニメーションの枚数 ページをめくるまでのフレーム数 1枚目の右下のUV値)
int DXAnimModel::SetAnimModel(std::string pathName, int maxPage, int maxPageFrame, float uvdown, float uvright)
{
	// モデルの読み込み
	int modelHandle = Master::mpResourceManager->LoadMadel(pathName);
	if (modelHandle == -1)
	{
		return -1;
	}

		GraphHandle = modelHandle;

	
	// ↓このBaseModel::ModelNuberはList内での識別番号であり、モデルのハンドルではない
	// this->SetModelNumber(modelHandle);
	
	// UV座標の初期化
	uvLeftUp.SetX(0.0f);
	uvLeftUp.SetY(0.0f);
	uvRightDown.SetX(uvright);
	uvRightDown.SetY(uvdown);

	// フレーム数の設定
	this->SetNowPage(0);
	this->SetMaxPage(maxPage);
	this->SteMaxPageFrame(maxPageFrame);

	// UV幅を保存
	UVWidth = uvRightDown.GetX() - uvLeftUp.GetX();
	return 0; 
}