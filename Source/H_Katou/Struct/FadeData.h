#pragma once

enum SceneCloseAnimNumber : unsigned short;
enum SceneOpenAnimNumber : unsigned short;

struct FadeData
{
	// フェードフラグ
	bool IsFade;

	// 経過フレーム
	float elapsedFrame;

	// 終了フレーム
	float endFrame;

	// 幕の終了フレーム
	const int CURTAIN_END_FRAME;

	FadeData();
	FadeData(const int curtainEndTime);

	void Init(SceneCloseAnimNumber closeAnim);
	void Init(SceneOpenAnimNumber openAnim);
};