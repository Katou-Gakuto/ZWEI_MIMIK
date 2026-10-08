#pragma once

#include <cstdint>
#include <vector>

#include "DxLib.h"

#include "../Y_Tool/VECTOR.h"

// 
class LightArea;

// 
class LightAreaManager
{
public:
    // DELETE:_ 消す
    struct LIGHT_DATA
    {
        VECTOR2D lineOne;
        VECTOR2D lineTwo;

        uint32_t lightColor;
    };
private:

    struct MASK_DATA
    {
        VECTOR2D maskSize;
        unsigned char* maskData = nullptr;
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

private:
    // 
    std::vector<LightArea *> mlNode;

    // 
    uint16_t mnDeactivateStartIndex;

    // ライトスクリーンハンドル
    std::vector<int> mnLightScreenHandle;

    // マスクデータ
    MASK_DATA mstMaskData;

    // ライトエリア画像ハンドル
    int mnLightAreaGraphHandle;
};
