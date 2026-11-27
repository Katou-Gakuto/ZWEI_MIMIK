#pragma once
#include "BaseModel.h"
#include <string>
#include "VECTOR.h"
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
	int SetObjModel(string pathName, VECTOR2D zoom);
	void SetZoom(VECTOR2D zoom) { Zoom = zoom; }
	void SetRotaAngle(double angle) { RotaAngle = angle; }
	
	// ŒJ‚è•Ô‚µ•`‰æ‚·‚é”ÍˆÍ‚Ì‘å‚«‚³‚ğİ’è
	inline void SetGraphLoopSize(VECTOR2D oneGraphSize) { mvGraphLoopSize = oneGraphSize; }

private:

	int GraphHandle;
	VECTOR2D Zoom; // Šg‘å—¦
	double RotaAngle; // ƒ‰ƒWƒAƒ“Šp

	// ŒJ‚è•Ô‚µ•`‰æ‚·‚é”ÍˆÍ‚Ì‘å‚«‚³
	VECTOR2D mvGraphLoopSize;
};