#pragma once
#include <string>

#include "VECTOR.h"

#include "DxLib.h"


namespace DRAW_SYSTEM
{
    enum STAGE_SIZE_TYPE
    {
        STAGE_SIZE_TYPE_WORLD_SIZE = 0,
        STAGE_SIZE_TYPE_DISPLAY_SIZE,
        STAGE_SIZE_TYPE_LEFT_UP_INTERVAL,
        STAGE_SIZE_TYPE_MAX
    };

    static VECTOR2D StageSize[STAGE_SIZE_TYPE::STAGE_SIZE_TYPE_MAX];

    static VECTOR2D ScaleFactor;

    // ステージの大きさ設定
    void SetStazeSize(VECTOR2D* stageSize);

    // 画像描画
    void DrawImage(VECTOR2D pos, VECTOR2D size, int handle);
    void DrawImage(VECTOR2D pos, VECTOR2D size, double angle, int handle, int TransFlag);
    void DrawImage(VECTOR2D pos1, VECTOR2D pos2, VECTOR2D pos3, VECTOR2D pos4, int handle, int flag = TRUE);

    // 現状光領域描画用
    void DrawPolygon(VERTEX2D* triangleVertex, int polygonNumber, int graphHandle, int flag = TRUE, bool redrawFlag = false);

    // プレイヤー描画用
    void DrawRectExtendGraph(VECTOR2D drawLeftUp, VECTOR2D drawRightDown, VECTOR2D graphLeftUpUV, VECTOR2D graphRightDown, int graphHandle, int flag = TRUE);

    // TODO:_ 画像に変換するため後でいらなくなる予定
    int DrawBox(VECTOR2D pos, VECTOR2D size, int color, int flag = FALSE);
    int DrawCircle(VECTOR2D pos, int radius, int color, int flag = FALSE);
    int DrawLine(VECTOR2D pos1, VECTOR2D pos2, int color);
    int DrawString(VECTOR2D pos, std::string String, int color);
    int DrawTriangle(VECTOR2D pos1, VECTOR2D pos2, VECTOR2D pos3, int color, int flag = FALSE);
    int DrawQuadrangle(VECTOR2D pos1, VECTOR2D pos2, VECTOR2D pos3, VECTOR2D pos4, int color, int flag = TRUE);

    // オブジェクトサイズをディスプレイサイズに変換
    VECTOR2D WorldSizeToDisplaySize(const VECTOR2D& objectSize);
    // オブジェクトの半径をディスプレイの半径に変換
    int WorldRadiusToDisplayRadius(int objectRadius);
}