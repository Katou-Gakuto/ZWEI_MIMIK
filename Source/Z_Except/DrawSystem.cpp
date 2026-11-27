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
    ScaleFactor = VECTOR2D(StageSize[STAGE_SIZE_TYPE::STAGE_SIZE_TYPE_WORLD_SIZE].GetX() / StageSize[STAGE_SIZE_TYPE::STAGE_SIZE_TYPE_DISPLAY_SIZE].GetX(),
                           StageSize[STAGE_SIZE_TYPE::STAGE_SIZE_TYPE_WORLD_SIZE].GetY() / StageSize[STAGE_SIZE_TYPE::STAGE_SIZE_TYPE_DISPLAY_SIZE].GetY());

}

// 画像描画
void DRAW_SYSTEM::DrawImage(VECTOR2D pos, VECTOR2D size, int handle)
{
    pos = WorldSizeToDisplaySize(pos);
    size = WorldSizeToDisplaySize(size);
    DxLib::DrawExtendGraph(pos.GetX() - (size.GetX() * 0.5f), pos.GetY() - (size.GetY() * 0.5f), pos.GetX() + (size.GetX() * 0.5f), pos.GetY() + (size.GetY() * 0.5f), handle, FALSE);
}

// 画像描画
void DRAW_SYSTEM::DrawImage(VECTOR2D pos, VECTOR2D size, float graphSizeRate, double angle, int handle, int TransFlag)
{
    // 画像中心をワールド座標として扱う
    float cx = pos.GetX();
    float cy = pos.GetY();

    // サイズから幅・高さを取得
    float halfW = size.GetX();
    float halfH = size.GetY();

    // 回転角度（ラジアン）
    float cosA = cos(angle);
    float sinA = sin(angle);

    // 各頂点のローカル座標
    float localX[] = { -halfW, halfW, halfW, -halfW };
    float localY[] = { -halfH, -halfH, halfH, halfH };

    // ワールド座標の頂点
    VECTOR2D worldVertex[4];

    for (int i = 0; i < 4; i++)
    {
        worldVertex[i] = VECTOR2D(
            cx + localX[i] * cosA - localY[i] * sinA,
            cy + localX[i] * sinA + localY[i] * cosA
        );
    }

    // ワールド座標から画面座標へ変換
    for (int i = 0; i < 4; i++)
    {
        worldVertex[i] = WorldSizeToDisplaySize(worldVertex[i]);
    }

    
    // polygonに設定
    {
        // 共通設定
        for (int i = 0; i < 6; ++i)
        {
            BoxVertex[i].rhw = 1.0f;
            BoxVertex[i].dif = GetColorU8(0xff, 0xff, 0xff, 0xff);
        }

        static constexpr int WORLD_LEFT_UP = 0;
        static constexpr int WORLD_RIGHT_UP = 1;
        static constexpr int WORLD_RIGHT_DOWN = 2;
        static constexpr int WORLD_LEFT_DOWN = 3;

        
        static constexpr int BOX_LEFT_UP_ONE = 0;
        static constexpr int BOX_RIGHT_UP = 1;
        static constexpr int BOX_RIGHT_DOWN_ONE = 2;
        static constexpr int BOX_LEFT_UP_TWO = 3;
        static constexpr int BOX_RIGHT_DOWN_TWO = 4;
        static constexpr int BOX_LEFT_DOWN = 5;
        
        BoxVertex[BOX_LEFT_UP_ONE].pos       = VGet(worldVertex[WORLD_LEFT_UP].GetX(),    worldVertex[WORLD_LEFT_UP].GetY(), 0.0f);
        BoxVertex[BOX_RIGHT_UP].pos          = VGet(worldVertex[WORLD_RIGHT_UP].GetX(),   worldVertex[WORLD_RIGHT_UP].GetY(), 0.0f);
        BoxVertex[BOX_RIGHT_DOWN_ONE].pos    = VGet(worldVertex[WORLD_RIGHT_DOWN].GetX(), worldVertex[WORLD_RIGHT_DOWN].GetY(), 0.0f);

        BoxVertex[BOX_LEFT_UP_TWO].pos       = VGet(worldVertex[WORLD_LEFT_UP].GetX(),    worldVertex[WORLD_LEFT_UP].GetY(), 0.0f);
        BoxVertex[BOX_RIGHT_DOWN_TWO].pos    = VGet(worldVertex[WORLD_RIGHT_DOWN].GetX(), worldVertex[WORLD_RIGHT_DOWN].GetY(), 0.0f);
        BoxVertex[BOX_LEFT_DOWN].pos         = VGet(worldVertex[WORLD_LEFT_DOWN].GetX(),  worldVertex[WORLD_LEFT_DOWN].GetY(), 0.0f);

        int graphSizeX;
        int graphSizeY;
        if (GetGraphSize(handle, &graphSizeX, &graphSizeY) == -1)
        {
            return;
        }

        const VECTOR2D boxUV = VECTOR2D(size.GetX() / ((float)graphSizeX * graphSizeRate), size.GetY() / ((float)graphSizeY * graphSizeRate));

        BoxVertex[BOX_LEFT_UP_ONE].u    = BoxVertex[BOX_LEFT_UP_TWO].u      = 0.0f;
        BoxVertex[BOX_LEFT_UP_ONE].v    = BoxVertex[BOX_LEFT_UP_TWO].v      = 0.0f;
        BoxVertex[BOX_RIGHT_UP].u                                           = boxUV.GetX();
        BoxVertex[BOX_RIGHT_UP].v                                           = 0.0f;
        BoxVertex[BOX_RIGHT_DOWN_ONE].u = BoxVertex[BOX_RIGHT_DOWN_TWO].u   = boxUV.GetX();
        BoxVertex[BOX_RIGHT_DOWN_ONE].v = BoxVertex[BOX_RIGHT_DOWN_TWO].v   = boxUV.GetY();
        BoxVertex[BOX_LEFT_DOWN].u                                          = 0.0f;
        BoxVertex[BOX_LEFT_DOWN].v                                          = boxUV.GetY();
    }
    
    // 自由変形描画
    SetTextureAddressMode(DX_TEXADDRESS_WRAP);
    DxLib::DrawPolygon2D(BoxVertex, 2, handle, TransFlag);
    SetTextureAddressMode(DX_TEXADDRESS_CLAMP);
}

// 画像描画
void DRAW_SYSTEM::DrawImage(VECTOR2D pos, VECTOR2D size, VECTOR2D graphSize, double angle, int handle, int TransFlag)
{
    // 画像中心をワールド座標として扱う
    float cx = pos.GetX();
    float cy = pos.GetY();

    // サイズから幅・高さを取得
    float halfW = size.GetX();
    float halfH = size.GetY();

    // 回転角度（ラジアン）
    float cosA = cos(angle);
    float sinA = sin(angle);

    // 各頂点のローカル座標
    float localX[] = { -halfW, halfW, halfW, -halfW };
    float localY[] = { -halfH, -halfH, halfH, halfH };

    // ワールド座標の頂点
    VECTOR2D worldVertex[4];

    for (int i = 0; i < 4; i++)
    {
        worldVertex[i] = VECTOR2D(
            cx + localX[i] * cosA - localY[i] * sinA,
            cy + localX[i] * sinA + localY[i] * cosA
        );
    }

    // ワールド座標から画面座標へ変換
    for (int i = 0; i < 4; i++)
    {
        worldVertex[i] = WorldSizeToDisplaySize(worldVertex[i]);
    }

    
    // polygonに設定
    {
        // 共通設定
        for (int i = 0; i < 6; ++i)
        {
            BoxVertex[i].rhw = 1.0f;
            BoxVertex[i].dif = GetColorU8(0xff, 0xff, 0xff, 0xff);
        }

        static constexpr int WORLD_LEFT_UP = 0;
        static constexpr int WORLD_RIGHT_UP = 1;
        static constexpr int WORLD_RIGHT_DOWN = 2;
        static constexpr int WORLD_LEFT_DOWN = 3;

        
        static constexpr int BOX_LEFT_UP_ONE = 0;
        static constexpr int BOX_RIGHT_UP = 1;
        static constexpr int BOX_RIGHT_DOWN_ONE = 2;
        static constexpr int BOX_LEFT_UP_TWO = 3;
        static constexpr int BOX_RIGHT_DOWN_TWO = 4;
        static constexpr int BOX_LEFT_DOWN = 5;

        BoxVertex[BOX_LEFT_UP_ONE].pos       = VGet(worldVertex[WORLD_LEFT_UP].GetX(),    worldVertex[WORLD_LEFT_UP].GetY(), 0.0f);
        BoxVertex[BOX_RIGHT_UP].pos          = VGet(worldVertex[WORLD_RIGHT_UP].GetX(),   worldVertex[WORLD_RIGHT_UP].GetY(), 0.0f);
        BoxVertex[BOX_RIGHT_DOWN_ONE].pos    = VGet(worldVertex[WORLD_RIGHT_DOWN].GetX(), worldVertex[WORLD_RIGHT_DOWN].GetY(), 0.0f);

        BoxVertex[BOX_LEFT_UP_TWO].pos       = VGet(worldVertex[WORLD_LEFT_UP].GetX(),    worldVertex[WORLD_LEFT_UP].GetY(), 0.0f);
        BoxVertex[BOX_RIGHT_DOWN_TWO].pos    = VGet(worldVertex[WORLD_RIGHT_DOWN].GetX(), worldVertex[WORLD_RIGHT_DOWN].GetY(), 0.0f);
        BoxVertex[BOX_LEFT_DOWN].pos         = VGet(worldVertex[WORLD_LEFT_DOWN].GetX(),  worldVertex[WORLD_LEFT_DOWN].GetY(), 0.0f);

        const VECTOR2D boxUV = VECTOR2D(size.GetX() / graphSize.GetX(), size.GetY() / graphSize.GetY());

        BoxVertex[BOX_LEFT_UP_ONE].u    = BoxVertex[BOX_LEFT_UP_TWO].u      = 0.0f;
        BoxVertex[BOX_LEFT_UP_ONE].v    = BoxVertex[BOX_LEFT_UP_TWO].v      = 0.0f;
        BoxVertex[BOX_RIGHT_UP].u                                           = boxUV.GetX();
        BoxVertex[BOX_RIGHT_UP].v                                           = 0.0f;
        BoxVertex[BOX_RIGHT_DOWN_ONE].u = BoxVertex[BOX_RIGHT_DOWN_TWO].u   = boxUV.GetX();
        BoxVertex[BOX_RIGHT_DOWN_ONE].v = BoxVertex[BOX_RIGHT_DOWN_TWO].v   = boxUV.GetY();
        BoxVertex[BOX_LEFT_DOWN].u                                          = 0.0f;
        BoxVertex[BOX_LEFT_DOWN].v                                          = boxUV.GetY();
    }
    
    // 自由変形描画
    SetTextureAddressMode(DX_TEXADDRESS_WRAP);
    DxLib::DrawPolygon2D(BoxVertex, 2, handle, TransFlag);
    SetTextureAddressMode(DX_TEXADDRESS_CLAMP);
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

// フェード用画像描画処理
void DRAW_SYSTEM::DrawFadeImage(DRAW_FADE_TYPE drawFadeType, int handle, VECTOR2D leftUpPos, VECTOR2D rightUpPos, VECTOR2D leftDownPos, VECTOR2D rightDownPos, int alpha, int transFlag)
{
    switch (drawFadeType)
    {
    case DRAW_FADE_TYPE::DRAW_FADE_TYPE_CURTAIN:
    {
        VECTOR2D displaySize = StageSize[STAGE_SIZE_TYPE::STAGE_SIZE_TYPE_DISPLAY_SIZE];
        rightUpPos.SetX(leftUpPos.GetX() + displaySize.GetX());
        rightUpPos.SetY(leftUpPos.GetY() + 0.0f);
        
        leftDownPos.SetX(leftUpPos.GetX() + 0.0f);
        leftDownPos.SetY(leftUpPos.GetY() + displaySize.GetY());
        
        rightDownPos.SetX(leftUpPos.GetX() + displaySize.GetX());
        rightDownPos.SetY(leftUpPos.GetY() + displaySize.GetY());
        
    }
        break;
    }

    DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
    DxLib::DrawModiGraph(leftUpPos.GetX(), leftUpPos.GetY(), rightUpPos.GetX(), rightUpPos.GetY(), rightDownPos.GetX(), rightDownPos.GetY(), leftDownPos.GetX(), leftDownPos.GetY(), handle, transFlag);
    DxLib::SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255/*max*/);
}
// フェード用画像描画処理
void DRAW_SYSTEM::DrawFadeImage(DRAW_FADE_TYPE drawFadeType, int handle, VECTOR2D leftUpPos, VECTOR2D rightDownPos, int alpha, int transFlag)
{
    DRAW_SYSTEM::DrawFadeImage(drawFadeType, handle, leftUpPos, VECTOR2D(rightDownPos.GetX(), leftUpPos.GetY()), VECTOR2D(leftUpPos.GetX(), rightDownPos.GetY()), rightDownPos, alpha, transFlag);
}
// フェード用画像描画処理
void DRAW_SYSTEM::DrawFadeImage(DRAW_FADE_TYPE drawFadeType, int handle, VECTOR2D leftUpPos, int alpha, int transFlag)
{
    VECTOR2D displaySize = StageSize[STAGE_SIZE_TYPE::STAGE_SIZE_TYPE_DISPLAY_SIZE];
    DRAW_SYSTEM::DrawFadeImage(drawFadeType, handle, leftUpPos, VECTOR2D(displaySize.GetX(), leftUpPos.GetY()), VECTOR2D(leftUpPos.GetX(), displaySize.GetY()), displaySize, alpha, transFlag);
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
    //return objectSize;
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