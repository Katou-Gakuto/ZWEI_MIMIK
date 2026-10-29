#include "DxLib.h"
#include "KeyState.h"
#include "BaseComponent.h"

#include "../S_Collision/CollisionHandle.h"
#include "../T_Model/BaseModelHandle.h"

#include "VECTOR.h"

class HoldObjectController;
class DXAnimModel;
class Circle2D;

class Player : public BaseComponent
{
public:

    Player(GameObject *myObject, int playerNumber);
    ~Player();

    int Create() override;
    int Initialize() override;
    int Finalize() override;
    int EarlyUpdate() override;
    int Update() override;
    int HitOnCollision(BaseCollision *myCollision, BaseCollision *hitCollision) override;
    int LateUpdate() override;
    int Draw() override;

    // オブジェクトが掴める際に掴む関数
    int TryHold();

    // オブジェクトをつかんでいる状態で「自身を中心として振り回す」ことを試してみる関数
    int TryHoldSwing();

    // オブジェクトをつかんでいる状態で「自身と同じようにオブジェクトを動かす」ことを試してみる関数
    int TryHoldMove(const VECTOR2D &moveVec);

    // オブジェクトをつかんでいる状態でHitOnCollision()が呼ばれたら行う関数
    bool SyncPlayerMoveVec(const VECTOR2D &vec);

    // ホールド関係を完全に0にし、何も持っていない状態にする関数
    bool ClearHold();

    // 
    VECTOR2D GetMoveVecNowFrame()const;

    int GetPlayerNum() const { return mnPlayerNum; } // 1Pか2Pかを返す

    // 
    bool InitPosition(const VECTOR2D &pos);

    // 
    bool ChangeLightSide();

    // 
    bool GetInLightArea() const;

private:

    int mnPlayerNum;        //P1かP2か

    int PlayerGraphHandle;  // プレイヤーのグラフィックハンドル

    float mfSwingDegree;    // 

    float mfNowSwingRadian;       // 

    float mfMoveMagnitude;

    HoldObjectController *mpHold; // 自身がつかんでいるオブジェクト

    // このプレイヤーの当たり判定
    CollisionHandle mdBodyCollision;

    // このプレイヤーのDXAnimModelをBaseModelListから取得するためのハンドル
    BaseModelHandle mdModelHandle;

    // 
    bool mbHoldFlag;

    // 
    bool mbSwingFlag;

    // 
    bool mbLightSide;

    // 
    bool mbInLightArea;

    // 
    bool CheckHoldNow() const;

    // 
    DXAnimModel *GetPlayerModel()const;

    // 
    Circle2D *GetBodyCollision() const;

    // 
    bool SetHoldRadian();

    // 
    int UpdateInLightArea();
};