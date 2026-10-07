#pragma once

// シーンマネージャー
class BaseSceneManager;
// 終了マネージャー
class EndManager;
// 時間マネージャー
class TimeManager;
// リソースマネージャー
class ResourceManager;
class DXAnimModel;
// キー情報
class KeyState;
// 光域の管理をするクラス
class LightAreaManager;

// DXライブラリの情報を持ち管理するクラス(複数に影響するDXライブラリの設定を行うのを主に想定して作成)
class DxLibDataManager;

#ifdef _DEBUG
// デバッグ用imguiを管理するクラス
class ImguiManager;
#endif

// 
class Player;

// 
class GoalObjectController;

// 
class VECTOR2D;

// 
class CursorMoveSupporter;

// 
class Master
{
public:
    // シーンのManager
    static BaseSceneManager *mpBaseSceneManager;

    // 終了の管理
    static EndManager* mpEndManager;
    // 時間の管理
    static TimeManager* mpTimeManager;
    // リソースの管理
	static ResourceManager *mpResourceManager;

    // キーの情報管理
    static KeyState* mpKeyState;

#ifdef _DEBUG
    // デバッグ用imgui管理
    static ImguiManager* mpImguiManager;
#endif

    // DXライブラリの情報管理
    static DxLibDataManager* mpDxLibDataManager;

    // 
    static Player *mpPlayerLight;

    // 
    static Player *mpPlayerShadow;

    // 
    static GoalObjectController *mpGoalLight;

    // 
    static GoalObjectController *mpGoalShadow;

    // Manager
    static LightAreaManager *mpLightManager;

    // 
    static CursorMoveSupporter *mpCursorMoveSupporter;

    // DxLibの前の初期化
    static int DxInitPreInitialize();

    // Masterの各メンバをnewする関数
    static int Initialize();

    // Masterの各メンバをdeleteする関数
    static int Finalize();

    // プレイヤーの大きさ
    static int PlayerSizeXY;

    // 画像を拡大/縮小し、UV座標を指定して描画する関数
    static int DrawGraphAnim(
        const VECTOR2D &posLeftUp, const VECTOR2D &posRightDown,
        const VECTOR2D &uvLeftUp, const VECTOR2D &uvRightDown,
        int graphHandle);
};