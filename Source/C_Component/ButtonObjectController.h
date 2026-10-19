#pragma once

#include "BaseComponent.h"

#include <cstdint>

#include "../S_Collision/CollisionHandle.h"

#include "../Y_Tool/VECTOR.h"

class Quadrangle2D;

// 
class ButtonObjectController : public BaseComponent
{
public:
    // 
    ButtonObjectController(
        GameObject *myObject,
        bool onePush,
        uint32_t onFrameCount,
        const VECTOR2D &center,
        const VECTOR2D &blockSize);

    // 
    ~ButtonObjectController() override;

    virtual int Create() override;
    virtual int Initialize() override;
    virtual int Finalize() override;
    virtual int EarlyUpdate() override;
    virtual int Update() override;
    virtual int HitOnCollision(BaseCollision *myCollision, BaseCollision *hitCollision) override;
    virtual int LateUpdate() override;
    virtual int Draw() override;

    // 現在このボタンはONの状態なのか
    bool GetNowState() const;

    // 現在このボタンは光域プレイヤー用なのか
    bool GetLightSide() const;

protected:
    // 
    ButtonObjectController(
        ComponentTagAndOrder ctao,
        GameObject *myObject,
        const VECTOR2D &center,
        const VECTOR2D &blockSize);

    // 
    int CreateBody();

    // 
    int BaseEarlyUpdate();

    // 
    int BaseLateUpdate();

private:
    // 現在スイッチがONになっているか
    bool mbNowOn;

    // この値がtrueの時は毎フレーム押し込み判定が必要なのかを確認する
    bool mbHitButton;

    // 前回のフレームでもボタンを踏んでいるか
    bool mbPushLastFrame;

    // 現在スイッチは光域に位置しているのか
    bool mbLightSide;

    // 
    bool mbOnPlayer;

    // ここが0以外の値になっていたらこのフレーム分だけONになり、後は自動でOFFになるという設定
    uint32_t mnOnFrameCount;

    // 現在の状態になってから何フレーム経ったかを記憶する変数
    uint32_t mnNowFrameCount;

    // 
    VECTOR2D mvCenterPos;

    // 
    VECTOR2D mvBlockSize;

    // 
    CollisionHandle mdBody;

    // 現在このボタンの上にプレイヤーがいるのか
    bool CheckOnPlayer() const;

    // 
    void UpdateNowState();

    // 
    void UpdateLightSide();

    // 
    Quadrangle2D *GetBody() const;
};
