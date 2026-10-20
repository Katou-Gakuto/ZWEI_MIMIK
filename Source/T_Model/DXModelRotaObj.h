#pragma once
#include "BaseModel.h"
#include <string>
using namespace std;

class DXModelRotaObj : public BaseModel
{
public:
	DXModelRotaObj(GameObject *myObject);
	~DXModelRotaObj();

	int Initialize();
	int Update();
	int Draw();
	int Finalize();


	// ‰æ‘œ‚Æ‰æ‘œ‚ÌŠg‘å—¦‚ğİ’è‚·‚é
	int SetObjModel(string pathName, float zoom);
	void SetZoom(float zoom) { Zoom = zoom; }
	void SetRotaAngle(double angle) { RotaAngle = angle; }


private:

	int GraphHandle;
	float Zoom; // Šg‘å—¦
	double RotaAngle; // ƒ‰ƒWƒAƒ“Šp
};