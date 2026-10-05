#pragma once

#include <cstdint>
#include <vector>

#include "../Y_Tool/VECTOR.h"

// 
class LightArea;

// 
class LightAreaManager
{
public:
    struct LINE_POS
    {
        VECTOR2D lineOne;
        VECTOR2D lineTwo;
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

    // ライト描画開始時処理
    void StartLightDraw();

    // ライト描画処理
    void LightDraw();

    // ライト描画終了時処理
    void EndLightDraw();

    // 描画
    void Draw();


    // 
    int AddArea(LightArea *newArea);

    // 
    int DeleteArea(int areaIndex);

    // 
    LightArea *SearchArea(int areaIndex);

    // どの光域に入っているかを確認する関数
    // 返り値のintは0で処理の成功の可否、引数のoutは自身が入っているAreaIndexを返す関数
    int CheckInLightArea(const VECTOR2D &pos, std::vector<int> &out);

    // スクリーンサイズ変更
    void ScreenSizeChange();

private:
    // 
    std::vector<LightArea *> mlNode;

    // 
    uint16_t mnDeactivateStartIndex;

    // ライトスクリーンハンドル
    int LightScreenHandle;

    // マスクデータ
    MASK_DATA mstMaskData;

    // ライトラインポジションデータ
    std::vector<LINE_POS> mstLightLine;
};
