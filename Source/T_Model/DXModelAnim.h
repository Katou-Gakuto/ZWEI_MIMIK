#pragma once
#include "BaseModel.h"
#include "VECTOR.h"
#include <string>
using namespace std;

class DXAnimModel : public BaseModel
{
public:
	DXAnimModel(GameObject *myObject);
	~DXAnimModel();

	int Initialize();
	int Update();
	int Draw();
	int Finalize();

	int SetAnimModel(string pathName, int maxPage, int maxPageFrame, float uvdown, float uvright);

	void SetNowPage(int nowpage) { NowPage = nowpage; }
	void SetMaxPage(int maxpage) { MaxPage = maxpage; }
	void SteMaxPageFrame(int maxpageframe) { MaxPageFrame = maxpageframe; }

private:

	VECTOR2D uvLeftUp;
	VECTOR2D uvRightDown;

	int NowPage; // 現在のフレーム
	int MaxPage; // 最大フレーム数
	int NowPageFrame;
	int MaxPageFrame; // ページをめくるまでのフレーム数
	float UVWidth;

	int GraphHandle;
};