#pragma once

#include <cstdint>
#include <vector>

#include "DxLib.h"

#include "../Y_Tool/VECTOR.h"

struct HIT_COLLISION_LINE;

class BaseCollision;

// 
class LightArea;

// 
class LightAreaManager
{
private:

    struct MASK_DATA
    {
        VECTOR2D maskSize;
        unsigned char* maskData = nullptr;
    };

    struct LIGHT_SCREEN_HANDLE
    {
        int SceneObjectScreenHandle;
        int FilpScreenHandle;
        int ScreenHandle;
    };


public:
    // 
    LightAreaManager();

    // 
    ~LightAreaManager();

    // 初期化
    void Initilize();

    // 描画
    void Draw();


    // 
    LightArea *SearchArea(int areaIndex);

    // 
    bool ResizeArea(uint32_t useAreaCount);

    // どの光域に入っているかを確認する関数
    // 返り値のintは0で処理の成功の可否、引数のoutは自身が入っているAreaIndexを返す関数
    int CheckInLightArea(const VECTOR2D &pos, std::vector<int> &out);

    // スクリーンサイズ変更
    void ScreenSizeChange();

    // ライトエリア用画像ハンドル取得
    inline int GetLightAreaGraphHandle() const { return mnLightAreaGraphHandle; }

private:
    // ライト描画開始時処理
    void StartLightDraw();

    // ライト描画処理
    void LightDraw();

    // ライト描画終了時処理
    void EndLightDraw();

    // 光領域内の描画済み画面を反転
    void FlipLightAreaScreen();

    // 光領域を描画用に調整する
    int SetupLightAreaForDrawing(const std::vector<HIT_COLLISION_LINE>& hitCollisionLine, std::vector<HIT_COLLISION_LINE>& drawHitCollisionLine, size_t lineIndex, int drawHitCollisionLineIteratorPlusNumber);

    // 角を取得する
    std::vector<VECTOR2D> GetVertexPositions(BaseCollision* collision);

private:
    // 
    std::vector<LightArea *> mlNode;

    // 
    uint16_t mnDeactivateStartIndex;

    // ライトスクリーンハンドル
    std::vector<LIGHT_SCREEN_HANDLE> mnLightScreenHandle;

    // 全ライトまとめ用スクリーンハンドル
    int mnAllLightScreenHandle;

    // マスクデータ
    MASK_DATA mstMaskData;

    // ライトエリア画像ハンドル
    int mnLightAreaGraphHandle;
};
