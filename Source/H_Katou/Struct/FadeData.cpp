#include "FadeData.h"

#include "BaseSceneManager.h"

FadeData::FadeData()
: CURTAIN_END_TIME(0.0f)
, IsFade(false)
, elapsedTime(0.0f)
, endTime(0.0f)
{
}

FadeData::FadeData(const float curtainMoveEndtime)
: CURTAIN_END_TIME(curtainMoveEndtime)
, IsFade(false)
, elapsedTime(0.0f)
, endTime(0.0f)
{
}

void FadeData::Init(SceneCloseAnimNumber closeAnim)
{
	switch (closeAnim)
	{
	case SceneCloseAnimNumber::SCAN_None:
		IsFade = false;
		break;

	case SceneCloseAnimNumber::SCAN_CurtainDown:
		IsFade = true;
		elapsedTime = 0.0f;
		endTime = CURTAIN_END_TIME;
		break;
	}
}

void FadeData::Init(SceneOpenAnimNumber openAnim)
{
	switch (openAnim)
	{
	case SceneOpenAnimNumber::SOAN_None:
		IsFade = false;
		break;

	case SceneOpenAnimNumber::SOAN_CurtainUp:
		IsFade = true;
		elapsedTime = 0.0f;
		endTime = CURTAIN_END_TIME;
		break;
	}
}