#include "DXModelRotaObj.h"
#include "../A_GameObject/GameObject2D.h"
#include "../Z_Except/Master.h"
#include "../Z_Except/ResourceManager.h"

DXModelRotaObj::DXModelRotaObj(GameObject *myObject) : BaseModel(myObject, ModelType_Model2D, static_cast<ScreenNumber>(0))
{
	GraphHandle = -1;
}

DXModelRotaObj::~DXModelRotaObj()
{
}

int DXModelRotaObj::Initialize()
{
	return 0;
}

int DXModelRotaObj::Update()
{
	return 0;
}

int DXModelRotaObj::Draw()
{
	auto model = static_cast<GameObject2D *>(this->GetUp());
	VECTOR2D pos = model->GetPosition();
	float rota = model->GetRotation();
	RotaAngle = rota;

	// ‰ñ“]•`‰æ
	DrawRotaGraph(
		pos.GetX(), pos.GetY(),
		Zoom,
		RotaAngle,
		GraphHandle,true,false); 
	
	return 0;
}

int DXModelRotaObj::Finalize()
{
	return 0;
}

// FXÝ’è(‰æ‘œƒpƒX ‰æ‘œ‚ÌŠg‘å—¦)
int DXModelRotaObj::SetObjModel(std::string pathName, float zoom)
{
	// ƒ‚ƒfƒ‹‚Ì“Ç‚Ýž‚Ý
	int modelHandle = Master::mpResourceManager->LoadGraphics(pathName);
	if (modelHandle == -1)
	{
		return -1;
	}

	GraphHandle = modelHandle;
	this->SetZoom(zoom);

	return 0;
}