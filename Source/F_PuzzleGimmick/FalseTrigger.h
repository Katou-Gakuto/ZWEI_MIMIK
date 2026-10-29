#pragma once

#include "PuzzleGimmickData.h"

// 常にGetSignal()でfalseを返すトリガー
class FalseTrigger : public BaseGimmickTrigger
{
public:
    // コンストラクタ
    FalseTrigger() :
        BaseGimmickTrigger()
    {
    }

    // デストラクタ
    ~FalseTrigger() override
    {
    }

    // シミュレーションしてきたギミックを実行に移すかを判断する関数
    // ※GameObject::Update()のタイミングで呼ばれ、自身と紐づけられてるExecutor::Update()の直前で呼ばれます
    bool GetSignal() override
    {
        // 
        return false;
    }

    // 当たり判定によるギミックの変化に対応させる関数
    int HitOnCollision(BaseCollision *myCollision, BaseCollision *hitCollision) override
    {
        // 
        return 0;
    }

private:
};