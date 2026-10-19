#pragma once

#include "PuzzleGimmickData.h"

class ButtonObjectController;

// 
class TeleportExecutor : public BaseGimmickExecutor
{
public:
    // コンストラクタ
    TeleportExecutor(PuzzleGimmickActiveParam param, ButtonObjectController *buttonA, ButtonObjectController *buttonB);

    // デストラクタ
    ~TeleportExecutor() override;

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

    // ギミック内容を描画する関数
    // ※既に実行段階である場合は引数がtrueになります。実行段階では描画しない、あるいはその逆の場合はこの引数を使ってください。
    int Draw(bool triggerSignal) override;

private:
    // 
    ButtonObjectController *mpButtonA;

    // 
    ButtonObjectController *mpButtonB;
};

// 
