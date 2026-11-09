#pragma once

enum SceneCloseAnimNumber : unsigned short;
enum SceneOpenAnimNumber : unsigned short;

struct FadeData
{
	// フェードフラグ
	bool IsFade;

	// 経過時間
	float elapsedTime;

	// 終了時間
	float endTime;

	// 幕の終了時間
	const float CURTAIN_END_TIME;

	FadeData();
	FadeData(const float curtainEndTime);

	void Init(SceneCloseAnimNumber closeAnim);
	void Init(SceneOpenAnimNumber openAnim);
};