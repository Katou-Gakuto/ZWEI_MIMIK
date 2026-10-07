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

    Player(GameObject* myObject, int playerNumber);
    ~Player();

    int Create() override;
    int Initialize() override;
    int Finalize() override;
    int EarlyUpdate() override;
    int Update() override;
    int HitOnCollision(BaseCollision* myCollision, BaseCollision* hitCollision) override;
    int LateUpdate() override;
    int Draw() override;

    // HitOnCollision()が呼ばれたら行う関数で、オブジェクトが掴める際に掴む関数
    int Hold(BaseCollision *hitCollision);

    // オブジェクトをつかんでいる状態でHitOnCollision()が呼ばれたら行う関数
    int HoldMove();

    // 
    bool CheckHoldObject(const HoldObjectController *hold) const;

    // 
    bool SyncPlayerMoveVec(const VECTOR2D &vec);

	VECTOR2D GetPos() const { return Pos; }
	int GetPlayerNum() const { return PlayerNum; } // 1Pか2Pかを返す

    // 
    bool InitPosition(const VECTOR2D &pos);

    // 
    bool ChangeLightSide();

    // 自身のゴールにたどり着いたか
    bool CheckGoal() const;

private:

    VECTOR2D Pos;
    VECTOR2D OldPos;
    VECTOR2D moveVec;
    int PlayerNum; //P1かP2か

	int PlayerGraphHandle; // プレイヤーのグラフィックハンドル

    
    HoldObjectController *mpHold; // 自身がつかんでいるオブジェクト

    // このプレイヤーの当たり判定
    CollisionHandle mdBodyCollision;

    // このプレイヤーのDXAnimModelをBaseModelListから取得するためのハンドル
    BaseModelHandle mdModelHandle;

    // 
    bool mbHoldFlag;

    // 
    bool mbLightSide;

    // 
    bool CheckHoldNow() const;

    // 
    DXAnimModel *GetPlayerModel()const;

    // 
    Circle2D *GetBodyCollision() const;
};