#include <string>

#include "VECTOR.h"

#include "DxLib.h"

#include "DrawSystem.h"

// ステージの大きさ設定
void DRAW_SYSTEM::SetStazeSize(VECTOR2D* stageSize)
{
    for (int stageSizeIndex = 0; stageSizeIndex < STAGE_SIZE_TYPE::STAGE_SIZE_TYPE_MAX; ++stageSizeIndex)
    {
        StageSize[stageSizeIndex] = stageSize[stageSizeIndex];
    }
    ScaleFactor = VECTOR2D(StageSize[STAGE_SIZE_TYPE::STAGE_SIZE_TYPE_DISPLAY_SIZE].GetX() / StageSize[STAGE_SIZE_TYPE::STAGE_SIZE_TYPE_WORLD_SIZE].GetX(),
                           StageSize[STAGE_SIZE_TYPE::STAGE_SIZE_TYPE_DISPLAY_SIZE].GetY() / StageSize[STAGE_SIZE_TYPE::STAGE_SIZE_TYPE_WORLD_SIZE].GetY());

}

// 画像描画
void DRAW_SYSTEM::DrawImage(VECTOR2D pos, VECTOR2D size, int handle)
{
    pos = WorldSizeToDisplaySize(pos);
    size = WorldSizeToDisplaySize(size);
    DxLib::DrawExtendGraph(pos.GetX() - (size.GetX() * 0.5f), pos.GetY() - (size.GetY() * 0.5f), pos.GetX() + (size.GetX() * 0.5f), pos.GetY() + (size.GetY() * 0.5f), handle, FALSE);
}

// 画像描画
void DRAW_SYSTEM::DrawImage(VECTOR2D pos, VECTOR2D size, double angle, int handle, int TransFlag)
{
    // 画像中心をワールド座標として扱う
    double cx = pos.GetX();
    double cy = pos.GetY();

    // サイズから幅・高さを取得
    double halfW = size.GetX();
    double halfH = size.GetY();

    // 回転角度（ラジアン）
    double cosA = cos(angle);
    double sinA = sin(angle);

    // 各頂点のローカル座標
    double localX[] = { -halfW, halfW, halfW, -halfW };
    double localY[] = { -halfH, -halfH, halfH, halfH };

    // ワールド座標の頂点
    VECTOR2D worldVertex[4];

    for (int i = 0; i < 4; i++)
    {
        worldVertex[i] = VECTOR2D(
            cx + localX[i] * cosA - localY[i] * sinA,
            cy + localX[i] * sinA + localY[i] * cosA
        );
    }

    // 最後にワールド座標から画面座標へ変換
    for (int i = 0; i < 4; i++)
    {
        worldVertex[i] = WorldSizeToDisplaySize(worldVertex[i]);
    }
    
    // 自由変形描画
    DxLib::DrawModiGraph(worldVertex[0].GetX(), worldVertex[0].GetY(), worldVertex[1].GetX(), worldVertex[1].GetY(), worldVertex[2].GetX(), worldVertex[2].GetY(), worldVertex[3].GetX(), worldVertex[3].GetY(), handle, TransFlag);

    //// ワールド座標から画面座標へ変換
    //pos = WorldSizeToDisplaySize(pos);

    //// 画像サイズ取得
    //int width, height;
    //DxLib::GetGraphSize(handle, &width, &height);

    //// 拡大後の半サイズ
    //double halfW = width * exRate.GetX() * 0.5;
    //double halfH = height * exRate.GetY() * 0.5;

    //// 回転角度
    //double cosA = cos(angle);
    //double sinA = sin(angle);

    //// 画像中心を pos とする
    //double cx = pos.GetX();
    //double cy = pos.GetY();

    //// 各頂点のローカル座標
    //double localX[] = { -halfW, halfW, halfW, -halfW };
    //double localY[] = { -halfH, -halfH, halfH, halfH };

    //int x[4], y[4];

    //// 回転・拡大縮小して各頂点の座標を計算
    //for (int i = 0; i < 4; i++)
    //{
    //    x[i] = static_cast<int>(
    //        cx + localX[i] * cosA - localY[i] * sinA);

    //    y[i] = static_cast<int>(
    //        cy + localX[i] * sinA + localY[i] * cosA);
    //}

    //// 自由変形描画
    //DxLib::DrawModiGraph(x[0], y[0], x[1], y[1], x[2], y[2], x[3], y[3], handle, TransFlag);
}

// 画像描画
void DRAW_SYSTEM::DrawImage(VECTOR2D pos1, VECTOR2D pos2, VECTOR2D pos3, VECTOR2D pos4, int handle, int flag)
{
    pos1 = WorldSizeToDisplaySize(pos1);
    pos2 = WorldSizeToDisplaySize(pos2);
    pos3 = WorldSizeToDisplaySize(pos3);
    pos4 = WorldSizeToDisplaySize(pos4);
    DxLib::DrawModiGraph(pos1.GetX(), pos1.GetY(), pos2.GetX(), pos2.GetY(), pos3.GetX(), pos3.GetY(), pos4.GetX(), pos4.GetY(), handle, flag);
}

// 現状光領域描画用
void DRAW_SYSTEM::DrawPolygon(VERTEX2D* triangleVertex, int polygonNumber, int graphHandle, int flag, bool redrawFlag)
{
    if (!redrawFlag)
    {
        for (int i = 0; i < polygonNumber; ++i)
        {
            VECTOR2D setPos1 = VECTOR2D(triangleVertex[(i * 3) + 0].pos.x, triangleVertex[(i * 3) + 0].pos.y);
            VECTOR2D setPos2 = VECTOR2D(triangleVertex[(i * 3) + 1].pos.x, triangleVertex[(i * 3) + 1].pos.y);
            VECTOR2D setPos3 = VECTOR2D(triangleVertex[(i * 3) + 2].pos.x, triangleVertex[(i * 3) + 2].pos.y);
            setPos1 = WorldSizeToDisplaySize(setPos1);
            setPos2 = WorldSizeToDisplaySize(setPos2);
            setPos3 = WorldSizeToDisplaySize(setPos3);
            triangleVertex[(i * 3) + 0].pos.x = setPos1.GetX();
            triangleVertex[(i * 3) + 0].pos.y = setPos1.GetY();
            triangleVertex[(i * 3) + 1].pos.x = setPos2.GetX();
            triangleVertex[(i * 3) + 1].pos.y = setPos2.GetY();
            triangleVertex[(i * 3) + 2].pos.x = setPos3.GetX();
            triangleVertex[(i * 3) + 2].pos.y = setPos3.GetY();
        }
    }
    DxLib::DrawPolygon2D(triangleVertex, polygonNumber, graphHandle, flag);
}

// プレイヤー描画用
void DRAW_SYSTEM::DrawRectExtendGraph(VECTOR2D drawLeftUp, VECTOR2D drawRightDown, VECTOR2D graphLeftUpUV, VECTOR2D graphRightDown, int graphHandle, int flag)
{
    drawLeftUp = WorldSizeToDisplaySize(drawLeftUp);
    drawRightDown = WorldSizeToDisplaySize(drawRightDown);
    DxLib::DrawRectExtendGraphF(drawLeftUp.GetX(), drawLeftUp.GetY(), drawRightDown.GetX(), drawRightDown.GetY(), graphLeftUpUV.GetX(), graphLeftUpUV.GetY(), graphRightDown.GetX(), graphRightDown.GetY(), graphHandle, flag);
}

// TODO:_ 後でいらなくする
int DRAW_SYSTEM::DrawBox(VECTOR2D pos, VECTOR2D size, int color, int flag)
{
    pos = WorldSizeToDisplaySize(pos);
    size = WorldSizeToDisplaySize(size);
    return DxLib::DrawBox(pos.GetX(), pos.GetY(), size.GetX(), size.GetY(), color, flag);
}
int DRAW_SYSTEM::DrawCircle(VECTOR2D pos, int radius, int color, int flag)
{
    pos = WorldSizeToDisplaySize(pos);
    radius = WorldRadiusToDisplayRadius(radius);
    return DxLib::DrawCircle(pos.GetX(), pos.GetY(), radius, color, flag);
}
int DRAW_SYSTEM::DrawLine(VECTOR2D pos1, VECTOR2D pos2, int color)
{
    pos1 = WorldSizeToDisplaySize(pos1);
    pos2 = WorldSizeToDisplaySize(pos2);
    return DxLib::DrawLine(pos1.GetX(), pos1.GetY(), pos2.GetX(), pos2.GetY(), color);
}
int DRAW_SYSTEM::DrawString(VECTOR2D pos, std::string String, int color)
{
    //pos = WorldSizeToDisplaySize(pos);
    return DxLib::DrawString(pos.GetX(), pos.GetY(), String.c_str(), color);
}
int DRAW_SYSTEM::DrawTriangle(VECTOR2D pos1, VECTOR2D pos2, VECTOR2D pos3, int color, int flag)
{
    pos1 = WorldSizeToDisplaySize(pos1);
    pos2 = WorldSizeToDisplaySize(pos2);
    pos3 = WorldSizeToDisplaySize(pos3);
    return DxLib::DrawTriangle(pos1.GetX(), pos1.GetY(), pos2.GetX(), pos2.GetY(), pos3.GetX(), pos3.GetY(), color, flag);
}
int DRAW_SYSTEM::DrawQuadrangle(VECTOR2D pos1, VECTOR2D pos2, VECTOR2D pos3, VECTOR2D pos4, int color, int flag)
{
    pos1 = WorldSizeToDisplaySize(pos1);
    pos2 = WorldSizeToDisplaySize(pos2);
    pos3 = WorldSizeToDisplaySize(pos3);
    pos4 = WorldSizeToDisplaySize(pos4);
    return DxLib::DrawQuadrangle(pos1.GetX(), pos1.GetY(), pos2.GetX(), pos2.GetY(), pos3.GetX(), pos3.GetY(), pos4.GetX(), pos4.GetY(), color, flag);
}

// オブジェクトサイズをディスプレイサイズに変換
VECTOR2D DRAW_SYSTEM::WorldSizeToDisplaySize(const VECTOR2D& objectSize)
{
    VECTOR2D displaySize = VECTOR2D(ScaleFactor.GetX() * objectSize.GetX(), ScaleFactor.GetY() * objectSize.GetY());

    // displaySize = VECTOR2D((objectSize.GetX() / StageSize[STAGE_SIZE_TYPE::STAGE_SIZE_TYPE_OBJECT_SIZE].GetX()) * StageSize[STAGE_SIZE_TYPE::STAGE_SIZE_TYPE_DISPLAY_SIZE].GetX(),
    //                         (objectSize.GetY() / StageSize[STAGE_SIZE_TYPE::STAGE_SIZE_TYPE_OBJECT_SIZE].GetY()) * StageSize[STAGE_SIZE_TYPE::STAGE_SIZE_TYPE_DISPLAY_SIZE].GetY());

    displaySize += StageSize[STAGE_SIZE_TYPE::STAGE_SIZE_TYPE_LEFT_UP_INTERVAL];

    return displaySize;
}

// オブジェクトの半径をディスプレイの半径に変換
int DRAW_SYSTEM::WorldRadiusToDisplayRadius(int objectRadius)
{
    return objectRadius * ((ScaleFactor.GetX() + ScaleFactor.GetY()) * 0.5f);
}