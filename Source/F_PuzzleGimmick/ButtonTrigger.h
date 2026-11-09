#pragma once

#include "PuzzleGimmickData.h"

// 
class ButtonObject;

// 
enum ButtonTriggerMode : uint8_t
{
    ButtonTriggerMode_OneLayer = 0,         // 
    ButtonTriggerMode_TrueCount,            // 
};

// ボタンの状態を確認し、シミュレーションを行うかを判断するクラス
class ButtonTrigger : public BaseGimmickTrigger
{
private:
    // 
    struct Node
    {
        uint32_t mnLayer;

        // 
        ButtonObject *mpButton;
    };

public:
    // コンストラクタ
    ButtonTrigger(ButtonTriggerMode activeLayerMode);

    // デストラクタ
    ~ButtonTrigger() override;

    // シミュレーションしてきたギミックを実行に移すかを判断する関数
    // ※GameObject::Update()のタイミングで呼ばれ、自身と紐づけられてるExecutor::Update()の直前で呼ばれます
    bool GetSignal() override;

    // 当たり判定によるギミックの変化に対応させる関数
    int HitOnCollision(BaseCollision *myCollision, BaseCollision *hitCollision) override;

    // 
    bool AddButton(ButtonObject *button, uint32_t layer);

private:
    // これらのやつが全てFlagとなるので
    std::vector<Node> mlNodeBox;

    // 0だったら1つでも条件がOKならOK。
    // 1だったらtrueのLayerが奇数個ならOK
    ButtonTriggerMode mnMode;
};
