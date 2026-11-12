#include "FadeData.h"

#include "BaseSceneManager.h"

FadeData::FadeData()
: CURTAIN_END_FRAME(0)
, IsFade(false)
, elapsedFrame(0.0f)
, endFrame(0.0f)
{
}

FadeData::FadeData(const int curtainMoveEndtime)
: CURTAIN_END_FRAME(curtainMoveEndtime)
, IsFade(false)
, elapsedFrame(0.0f)
, endFrame(0.0f)
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
		elapsedFrame = 0.0f;
		endFrame = (float)CURTAIN_END_FRAME;
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
		elapsedFrame = 0.0f;
		endFrame = (float)CURTAIN_END_FRAME;
		break;
	}
}