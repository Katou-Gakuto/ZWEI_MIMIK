#pragma once

#include "PuzzleGimmickData.h"

// オブジェクトを回転させるクラス
class RotateExecutor : public BaseGimmickExecutor
{
public:
    // 
    RotateExecutor(PuzzleGimmickActiveParam param);

    // 
    ~RotateExecutor();

    // ギミックの内容を実行する関数
    // ※GameObject::EarlyUpdate()のタイミングで呼ばれます
    int EarlyUpdate(bool triggerSignal) override;

    // ギミックの内容を実行する関数
    // ※GameObject::Update()のタイミングで呼ばれます
    int Update(bool triggerSignal) override;

    // ギミックの内容を実行する関数
    // ※GameObject::LateUpdate()のタイミングで呼ばれます
    int LateUpdate(bool triggerSignal) override;

    // 当たり判定によるギミックの変化に対応させる関数
    int HitOnCollision(BaseCollision *myCollision, BaseCollision *hitCollision) override;

    // 
    float GetNowRotate() const;

    // 
    void SetNowRotate(float radian);

    // 
    void AddNowRotate(float radian);

private:
    // 
    float mfNowRotate;
};
