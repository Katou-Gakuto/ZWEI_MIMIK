#include "DXModelRotaObj.h"
#include "../A_GameObject/GameObject2D.h"
#include "../Z_Except/Master.h"
#include "../Z_Except/ResourceManager.h"
#include "DrawSystem.h"

DXModelRotaObj::DXModelRotaObj(GameObject *myObject) : BaseModel(myObject, ModelType_Model2D, static_cast<ScreenNumber>(0)), mvGraphLoopSize(VECTOR2D::GetZero())
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

	// ŒJ‚è•Ô‚µ•`‰æ‚·‚é”ÍˆÍ‚Ì‘å‚«‚³‚ªÝ’è‚³‚ê‚Ä‚¢‚È‚¢‚È‚çƒTƒCƒY‚ÅÝ’è‚·‚é
	if (mvGraphLoopSize == VECTOR2D::GetZero())
	{
		mvGraphLoopSize = Zoom;
	}

	// ‰ñ“]•`‰æ

	DRAW_SYSTEM::DrawImage(pos,
		Zoom,
		mvGraphLoopSize,
		RotaAngle,
		GraphHandle,true); 
	
	return 0;
}

int DXModelRotaObj::Finalize()
{
	return 0;
}

// FXÝ’è(‰æ‘œƒpƒX ‰æ‘œ‚ÌŠg‘å—¦)
int DXModelRotaObj::SetObjModel(std::string pathName, VECTOR2D zoom)
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