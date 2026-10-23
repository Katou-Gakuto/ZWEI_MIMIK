#include "DXModelAnim.h"

#include "../A_GameObject/GameObject2D.h"
#include "../Z_Except/Master.h"
#include "../Z_Except/ResourceManager.h"

class BaseSceneManager; // 前方宣言

DXAnimModel::DXAnimModel(GameObject *myObject) : BaseModel(myObject, ModelType_Model2D, static_cast<ScreenNumber>(0))
{
	NowPage = 0;
	NowPageFrame = 0;
	UVWidth = 0.0f;
}

DXAnimModel::~DXAnimModel()
{
}

int DXAnimModel::Initialize()
{
	NowPageFrame = 0;
	NowPage = 0;
	uvLeftUp.SetX(0.0f);
	uvRightDown.SetX(UVWidth);
	return 0;
}

int DXAnimModel::Update()
{
	NowPageFrame++;

    if (NowPageFrame > MaxPageFrame[AnimNum])
    {
        NowPageFrame = 0;
        NowPage++;

        // ずらす
        uvLeftUp.SetX(uvLeftUp.GetX() + UVWidth);

        if (NowPage >= MaxPage[AnimNum])
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
    auto model = static_cast<GameObject2D *>(this->GetUp());
    VECTOR2D pos = model->GetPosition();

	// 描画
	Master::DrawGraphAnim(
		VECTOR2D(pos.GetX() - (Master::PlayerSizeXY / 2), pos.GetY() - (Master::PlayerSizeXY / 2)),
		VECTOR2D(pos.GetX() + (Master::PlayerSizeXY / 2), pos.GetY() + (Master::PlayerSizeXY / 2)),
		uvLeftUp,
		uvRightDown,
		GraphHandle[AnimNum]);//this->GetModelNumber());
	return 0;
}

int DXAnimModel::Finalize()
{
	return 0;
}

// 色々設定(画像パス アニメーションの枚数 ページをめくるまでのフレーム数 1枚目の右下のUV値 アニメーションの番号)
int DXAnimModel::SetAnimModel(std::string pathName, int maxPage, int maxPageFrame, float uvdown, float uvright, int animnum)
{
	// モデルの読み込み
	int modelHandle = Master::mpResourceManager->LoadGraphics(pathName);
	if (modelHandle == -1)
	{
		return -1;
	}

	// アニメーション番号とグラフハンドルをセット
	this->ChangeAnimNum(animnum);
	GraphHandle[animnum] = modelHandle;
	
	// UV座標の初期化
	uvLeftUp.SetX(0.0f);
	uvLeftUp.SetY(0.0f);
	uvRightDown.SetX(uvright);
	uvRightDown.SetY(uvdown);

	// フレーム数の設定
	this->SetNowPage(0);
	this->SetMaxPage(maxPage, animnum);
	this->SetMaxPageFrame(maxPageFrame, animnum);

	// UV幅を保存
	UVWidth = uvRightDown.GetX() - uvLeftUp.GetX();
	return 0; 
}

void DXAnimModel::ChangeAnimNum(int animnum)
{
	AnimNum = animnum;
	NowPage = 0;
	NowPageFrame = 0;
	uvLeftUp.SetX(0.0f);
	uvRightDown.SetX(UVWidth);
}