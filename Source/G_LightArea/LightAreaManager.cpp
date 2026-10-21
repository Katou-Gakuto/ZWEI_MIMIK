#include "DxLib.h"

#include "LightAreaManager.h"

#include "LightArea.h"

#include "LightLineNode.h"

#include "Master.h"

#include "DxLibDataManager.h"

#include "ResourceManager.h"

#include "../S_Collision/Point2D.h"

// 
LightAreaManager::LightAreaManager() :
    mlNode(),
    mnDeactivateStartIndex(0),
    mnLightScreenHandle(),
    mnAllLightScreenHandle(-1),
    mstMaskData(),
    mnLightAreaGraphHandle(-1)
{
}

// 
LightAreaManager::~LightAreaManager()
{
    // 
    for (auto node : this->mlNode)
    {
        // 
        if (node == nullptr)
        {
            continue;
        }

        // 
        delete node;

        // 
        node = nullptr;
    }

    // 
    this->mlNode.clear();

    // 
    this->mnDeactivateStartIndex = 0;


    // スクリーン終了
    for (int i = 0; i < mnLightScreenHandle.size(); ++i)
    {
        if (mnLightScreenHandle[i].SceneObjectScreenHandle != -1)
        {
            DeleteGraph(mnLightScreenHandle[i].SceneObjectScreenHandle);
            mnLightScreenHandle[i].SceneObjectScreenHandle = -1;
        }
        if (mnLightScreenHandle[i].FilpScreenHandle != -1)
        {
            DeleteGraph(mnLightScreenHandle[i].FilpScreenHandle);
            mnLightScreenHandle[i].FilpScreenHandle = -1;
        }
        if (mnLightScreenHandle[i].ScreenHandle != -1)
        {
            DeleteGraph(mnLightScreenHandle[i].ScreenHandle);
            mnLightScreenHandle[i].ScreenHandle = -1;
        }
    }
    mnLightScreenHandle.clear();
    if (mnAllLightScreenHandle != -1)
    {
        DeleteGraph(mnAllLightScreenHandle);
        mnAllLightScreenHandle = -1;
    }

    // マスクデータ削除
    if (mstMaskData.maskData != nullptr)
    {
        free(mstMaskData.maskData);
    }
}

// 初期化
void LightAreaManager::Initilize()
{
    mnLightAreaGraphHandle = Master::mpResourceManager->LoadGraphics(ResourceManager::msResourceFile + "LightArea/LightColor.png");
    ScreenSizeChange();
}

// 描画
void LightAreaManager::Draw()
{    
    // ライト描画処理
    { 
        // 開始
        StartLightDraw();
        // 描画
        LightDraw();
        // 終了
        EndLightDraw();
    }
}


// 
LightArea *LightAreaManager::SearchArea(int areaIndex)
{
    // 
    if (areaIndex < 0 ||
        this->mnDeactivateStartIndex <= areaIndex)
    {
        // 
        return nullptr;
    }

    // 
    return this->mlNode[areaIndex];
}

// 
bool LightAreaManager::ResizeArea(uint32_t useAreaCount)
{
    // 
    if (useAreaCount < this->mnDeactivateStartIndex)
    {
        // 
        this->mnDeactivateStartIndex = useAreaCount;

        // 
        return true;
    }

    // 
    if (this->mlNode.size() < useAreaCount)
    {
        this->mlNode.resize(useAreaCount);
    }

    for (uint32_t i = 0; i < useAreaCount; i++)
    {
        // 
        if (this->mlNode[i] == nullptr)
        {
            // 
            this->mlNode[i] = new LightArea();
        }
    }

    // 
    this->mnDeactivateStartIndex = useAreaCount;

    // 
    return true;
}

// どの光域に入っているかを確認する関数
// 返り値のintは0で処理の成功の可否、引数のoutは自身が入っているAreaIndexを返す関数
int LightAreaManager::CheckInLightArea(const VECTOR2D &pos, std::vector<int> &out)
{
    // 
    Point2D tempPoint;

    // 
    tempPoint.SetShapeParameter(pos);

    // 
    for (uint16_t i = 0; i < this->mnDeactivateStartIndex; i++)
    {
        // 
        if (this->mlNode[i]->GetOffLight())
        {
            // 
            continue;
        }

        // 
        if (this->mlNode[i]->CheckInArea(tempPoint))
        {
            // 
            out.push_back(i);
        }
    }

    // 
    return 0;
}

// スクリーンサイズ変更
void LightAreaManager::ScreenSizeChange()
{
    VECTOR2D displaySize = Master::mpDxLibDataManager->GetDisplaySize();
    for (int i = 0; i < mnLightScreenHandle.size(); ++i)
    {
        if (mnLightScreenHandle[i].SceneObjectScreenHandle != -1)
        {
            DeleteGraph(mnLightScreenHandle[i].SceneObjectScreenHandle);
            mnLightScreenHandle[i].SceneObjectScreenHandle = -1;
        }
        if (mnLightScreenHandle[i].FilpScreenHandle != -1)
        {
            DeleteGraph(mnLightScreenHandle[i].FilpScreenHandle);
            mnLightScreenHandle[i].FilpScreenHandle = -1;
        }
        if (mnLightScreenHandle[i].ScreenHandle != -1)
        {
            DeleteGraph(mnLightScreenHandle[i].ScreenHandle);
            mnLightScreenHandle[i].ScreenHandle = -1;
        }
        mnLightScreenHandle[i].SceneObjectScreenHandle = MakeScreen(displaySize.GetX(), displaySize.GetY(), TRUE);
        mnLightScreenHandle[i].FilpScreenHandle = MakeScreen(displaySize.GetX(), displaySize.GetY(), TRUE);
        mnLightScreenHandle[i].ScreenHandle = MakeScreen(displaySize.GetX(), displaySize.GetY(), TRUE);
    }
    if (mnAllLightScreenHandle != -1)
    {
        DeleteGraph(mnAllLightScreenHandle);
        mnAllLightScreenHandle = -1;
    }
    mnAllLightScreenHandle = MakeScreen(displaySize.GetX(), displaySize.GetY(), TRUE);

    if (mstMaskData.maskData != nullptr)
    {
        free(mstMaskData.maskData);
    }
    mstMaskData.maskData = static_cast<unsigned char*>(malloc(sizeof(unsigned char) * displaySize.GetX() * displaySize.GetY()));
    mstMaskData.maskSize = displaySize;

    if (mstMaskData.maskData == nullptr)
    {
        return;
    }
    // マスクを1ピクセルずつ記入
    for (int y = 0; y < mstMaskData.maskSize.GetY(); ++y)
    {
        for (int x = 0; x < mstMaskData.maskSize.GetX(); ++x)
        {
            mstMaskData.maskData[(y * static_cast<int>(mstMaskData.maskSize.GetX())) + x] = 0xff;
        }
    }
}

// 描画毎初期化
void LightAreaManager::StartLightDraw()
{
    {
        // 描画先を変更
        SetDrawScreen(mnAllLightScreenHandle);
        ClearDrawScreen();

        // マスク画面を作成します
        CreateMaskScreen();

        DrawMaskToDirectData(0, 0, mstMaskData.maskSize.GetX(), mstMaskData.maskSize.GetY(), mstMaskData.maskData, DX_MASKTRANS_NONE);

        // マスク画面を削除します
        DeleteMaskScreen();
    }
    
    for (int i = 0; i < mnLightScreenHandle.size(); ++i)
    {
        {
            // 描画先を変更
            SetDrawScreen(mnLightScreenHandle[i].SceneObjectScreenHandle);
            ClearDrawScreen();

            // マスク画面を作成します
            CreateMaskScreen();

            DrawMaskToDirectData(0, 0, mstMaskData.maskSize.GetX(), mstMaskData.maskSize.GetY(), mstMaskData.maskData, DX_MASKTRANS_NONE);

            // マスク画面を削除します
            DeleteMaskScreen();
        }

        {
            // 描画先を変更
            SetDrawScreen(mnLightScreenHandle[i].FilpScreenHandle);
            ClearDrawScreen();

            // マスク画面を作成します
            CreateMaskScreen();

            DrawMaskToDirectData(0, 0, mstMaskData.maskSize.GetX(), mstMaskData.maskSize.GetY(), mstMaskData.maskData, DX_MASKTRANS_NONE);

            // マスク画面を削除します
            DeleteMaskScreen();
        }
        
        {
            // 描画先を変更
            SetDrawScreen(mnLightScreenHandle[i].ScreenHandle);
            ClearDrawScreen();

            // マスク画面を作成します
            CreateMaskScreen();

            DrawMaskToDirectData(0, 0, mstMaskData.maskSize.GetX(), mstMaskData.maskSize.GetY(), mstMaskData.maskData, DX_MASKTRANS_NONE);

            // マスク画面を削除します
            DeleteMaskScreen();
        }
    }
}

// ライト描画処理
void LightAreaManager::LightDraw()
{
    // 光の種類数を調べる
    int colorCount = 0;
    std::vector<uint32_t> colorNumbers;
    for (LightArea* lightArea : mlNode)
    {
        bool newColorFlag = true;
        for (int i = 0; i < colorNumbers.size(); ++i)
        {
            if (lightArea->GetLightColor() == colorNumbers[i])
            {
                newColorFlag = false;
                break;
            }
        }

        if (newColorFlag)
        {
            ++colorCount;
            colorNumbers.push_back(lightArea->GetLightColor());
        }
    }

    // 光描画用スクリーンの数が合わないなら変更
    if (mnLightScreenHandle.size() != colorCount)
    {
        if (mnLightScreenHandle.size() < colorCount)
        {
            while (mnLightScreenHandle.size() < colorCount)
            {
                mnLightScreenHandle.push_back({ MakeScreen(Master::mpDxLibDataManager->GetDisplaySize().GetX(), Master::mpDxLibDataManager->GetDisplaySize().GetY(), TRUE), MakeScreen(Master::mpDxLibDataManager->GetDisplaySize().GetX(), Master::mpDxLibDataManager->GetDisplaySize().GetY(), TRUE), MakeScreen(Master::mpDxLibDataManager->GetDisplaySize().GetX(), Master::mpDxLibDataManager->GetDisplaySize().GetY(), TRUE) });
            }
        }
        else
        {
            while (mnLightScreenHandle.size() > colorCount)
            {
                if (mnLightScreenHandle[mnLightScreenHandle.size() - 1].SceneObjectScreenHandle != -1)
                {
                    DeleteGraph(mnLightScreenHandle[mnLightScreenHandle.size() - 1].SceneObjectScreenHandle);
                }
                if (mnLightScreenHandle[mnLightScreenHandle.size() - 1].FilpScreenHandle != -1)
                {
                    DeleteGraph(mnLightScreenHandle[mnLightScreenHandle.size() - 1].FilpScreenHandle);
                }
                if (mnLightScreenHandle[mnLightScreenHandle.size() - 1].ScreenHandle != -1)
                {
                    DeleteGraph(mnLightScreenHandle[mnLightScreenHandle.size() - 1].ScreenHandle);
                }
                mnLightScreenHandle.pop_back();
            }
        }
    }

    // 光描画
    for (int i = 0; i < mnLightScreenHandle.size(); ++i)
    {
        SetDrawScreen(mnLightScreenHandle[i].FilpScreenHandle);
        for (LightArea* lightArea : mlNode)
        {
            if (lightArea->GetLightColor() == colorNumbers[i])
            {
                lightArea->DrawLightArea();
            }
        }
    }
    for (int i = 0; i < mnLightScreenHandle.size(); ++i)
    {
        SetDrawScreen(mnLightScreenHandle[i].ScreenHandle);
        for (LightArea* lightArea : mlNode)
        {
            if (lightArea->GetLightColor() == colorNumbers[i])
            {
                lightArea->ReDrawLightArea();
            }
        }
    }

    // 当たっているオブジェクトに沿った描画を行う
    for (int i = 0; i < mnLightScreenHandle.size(); ++i)
    {
        SetDrawScreen(mnLightScreenHandle[i].ScreenHandle);
        for (LightArea* lightArea : mlNode)
        {
            if (lightArea->GetLightColor() == colorNumbers[i])
            {
                std::vector<std::vector<HIT_COLLISION_LINE>> hitCollisionLine = lightArea->DrawLingAreaHitCollisionsGetProcess();

                if (hitCollisionLine.size() == 0)
                {
                    continue;
                }

                // 一本ずつ調べて必要なら補正する
                // TODO:_ 補正処理作成する
                // INPROGRESS:_ 加藤次の作業個所
            }
        }
    }
}

// ライト描画終了時処理
void LightAreaManager::EndLightDraw()
{
    // 描画先戻す
    SetDrawScreen(DX_SCREEN_BACK);

    FlipLightAreaScreen();

    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 125);
    for (int i = 0; i < mnLightScreenHandle.size(); ++i)
    {
        // 描画対象画像を画面いっぱいに拡大して描画する
        DrawExtendGraph(0, 0, mstMaskData.maskSize.GetX(), mstMaskData.maskSize.GetY(), mnLightScreenHandle[i].ScreenHandle, TRUE);
    }
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

// 光領域内の描画済み画面を反転
void LightAreaManager::FlipLightAreaScreen()
{
    // // // // // // // const int screenWidth = static_cast<int>(mstMaskData.maskSize.GetX());

    // // // // // // // const int screenHeight = static_cast<int>(mstMaskData.maskSize.GetY());

    // // // // // // // for (LIGHT_SCREEN_HANDLE& screenHandle : mnLightScreenHandle)
    // // // // // // // {
    // // // // // // //     // 画面の内容を一時スクリーンへ取得
    // // // // // // //     // 呼び出し時点では DX_SCREEN_BACK が描画先であること
    // // // // // // //     if (GetDrawScreenGraph(0, 0, screenWidth, screenHeight, screenHandle.SceneObjectScreenHandle) != 0)
    // // // // // // //     {
    // // // // // // //         return;
    // // // // // // //     }

    // // // // // // //     // 保存した画面を描画先にする
    // // // // // // //     SetDrawScreen(screenHandle.SceneObjectScreenHandle);

    // // // // // // //     // マスクの透明部分を反転対象から除外
    // // // // // // //     SetDrawAlphaTest(DX_CMP_GREATER, 0);

    // // // // // // //     // 描画先の色を反転するブレンドモード
    // // // // // // //     SetDrawBlendMode(DX_BLENDMODE_INVDESTCOLOR, 255);

    // // // // // // //     // 光領域のマスクを重ねる
    // // // // // // //     DrawGraph(0, 0, screenHandle.FilpScreenHandle, TRUE);

    // // // // // // //     // 描画設定を元に戻す
    // // // // // // //     SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
    // // // // // // //     SetDrawAlphaTest(-1, 0);

    // // // // // // //     // 元の描画先へ戻す
    // // // // // // //     SetDrawScreen(DX_SCREEN_BACK);

    // // // // // // //     // 反転済みの画面を合成
    // // // // // // //     DrawGraph(0, 0, screenHandle.SceneObjectScreenHandle, FALSE);
    // // // // // // // }


    // // // // // // // 描画先を裏画面に設定
    // // // // // // SetDrawScreen(DX_SCREEN_BACK);

    // // // // // // // 光領域外を暗くするための黒いレイヤーを重ねる
    // // // // // // SetDrawBlendMode(DX_BLENDMODE_ALPHA, 160);

    // // // // // // // 画面全体を黒くする
    // // // // // // DrawBox(0, 0, static_cast<int>(mstMaskData.maskSize.GetX()), static_cast<int>(mstMaskData.maskSize.GetY()), GetColor(0, 0, 0), TRUE);

    // // // // // // SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

    // // // // // SetDrawScreen(mnAllLightScreenHandle);
    // // // // // for (int i = 0; i < mnLightScreenHandle.size(); ++i)
    // // // // // {
    // // // // //     DrawExtendGraph(0, 0, mstMaskData.maskSize.GetX(), mstMaskData.maskSize.GetY(), mnLightScreenHandle[i].FilpScreenHandle, TRUE);
    // // // // // }

    // // // // // SetDrawScreen(DX_SCREEN_BACK);

    // // // // // // マスクを有効化
    // // // // // SetMaskScreenGraph(mnAllLightScreenHandle);
    // // // // // SetUseMaskScreenFlag(TRUE);

    // // // // // // 光領域内外の効果を反転
    // // // // // SetMaskReverseEffectFlag(TRUE);

    // // // // // // 光領域外だけを暗くする
    // // // // // SetDrawBlendMode(DX_BLENDMODE_ALPHA, 160);

    // // // // // DrawBox(0, 0, static_cast<int>(mstMaskData.maskSize.GetX()), static_cast<int>(mstMaskData.maskSize.GetY()), GetColor(0, 0, 0), TRUE);

    // // // // // // マスクと描画設定を解除
    // // // // // SetMaskReverseEffectFlag(FALSE);
    // // // // // SetUseMaskScreenFlag(FALSE);
    // // // // // SetMaskScreenGraph(-1);

    // // // // // SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

    // // // // // 光領域の統合マスクを作成
    // // // // SetDrawScreen(mnAllLightScreenHandle);
    // // // // ClearDrawScreen();

    // // // // // 各光領域を統合する
    // // // // for (const auto& screenHandle : mnLightScreenHandle)
    // // // // {
    // // // //     DrawExtendGraph(0, 0, static_cast<int>(mstMaskData.maskSize.GetX()), static_cast<int>(mstMaskData.maskSize.GetY()), screenHandle.FilpScreenHandle, TRUE);
    // // // // }

    // // // // // バックバッファに戻す
    // // // // SetDrawScreen(DX_SCREEN_BACK);

    // // // // // マスクを有効にする
    // // // // SetMaskScreenGraph(mnAllLightScreenHandle);
    // // // // SetUseMaskScreenFlag(TRUE);
    // // // // SetMaskReverseEffectFlag(TRUE);

    // // // // // 光領域外だけを暗くする
    // // // // SetDrawBlendMode(DX_BLENDMODE_ALPHA, 160);

    // // // // DrawBox(0, 0, static_cast<int>(mstMaskData.maskSize.GetX()), static_cast<int>(mstMaskData.maskSize.GetY()), GetColor(0, 0, 0), TRUE);

    // // // // // 設定を戻す
    // // // // SetUseMaskScreenFlag(FALSE);
    // // // // SetMaskReverseEffectFlag(FALSE);
    // // // // SetMaskScreenGraph(-1);

    // // // // SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

    // // // SetDrawScreen(DX_SCREEN_BACK);

    // // // // 画面全体を暗くする
    // // // SetDrawBlendMode(DX_BLENDMODE_ALPHA, 160);
    // // // DrawBox(0, 0, static_cast<int>(mstMaskData.maskSize.GetX()), static_cast<int>(mstMaskData.maskSize.GetY()), GetColor(0, 0, 0), TRUE);

    // // // // 描画設定を戻す
    // // // SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

    // // // // 光領域を再描画する
    // // // for (const auto& screenHandle : mnLightScreenHandle)
    // // // {
    // // //     DrawExtendGraph(0, 0, static_cast<int>(mstMaskData.maskSize.GetX()), static_cast<int>(mstMaskData.maskSize.GetY()), screenHandle.FilpScreenHandle, TRUE);
    // // // }

    // // // 全光領域を統合するスクリーンを初期化
    // // SetDrawScreen(mnAllLightScreenHandle);
    // // ClearDrawScreen();

    // // // 各光領域を統合
    // // for (const auto& screenHandle : mnLightScreenHandle)
    // // {
    // //     DrawExtendGraph(0, 0, static_cast<int>(mstMaskData.maskSize.GetX()), static_cast<int>(mstMaskData.maskSize.GetY()), screenHandle.FilpScreenHandle, TRUE);
    // // }

    // // // デバッグ確認：
    // // // この行を有効にすると、統合したマスクを画面に表示する
    // // SetDrawScreen(DX_SCREEN_BACK);
    // // DrawExtendGraph(0, 0, static_cast<int>(mstMaskData.maskSize.GetX()), static_cast<int>(mstMaskData.maskSize.GetY()), mnAllLightScreenHandle, TRUE);
    // // return;

    // // // マスクを使って背景を暗くする
    // // SetDrawScreen(DX_SCREEN_BACK);

    // // SetMaskScreenGraph(mnAllLightScreenHandle);
    // // SetMaskReverseEffectFlag(FALSE);
    // // SetUseMaskScreenFlag(TRUE);

    // // SetDrawBlendMode(DX_BLENDMODE_ALPHA, 160);

    // // DrawBox(0, 0, static_cast<int>(mstMaskData.maskSize.GetX()), static_cast<int>(mstMaskData.maskSize.GetY()), GetColor(0, 0, 0), TRUE);

    // // SetUseMaskScreenFlag(FALSE);
    // // SetMaskReverseEffectFlag(FALSE);
    // // SetMaskScreenGraph(-1);

    // // SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
    
    // 全光領域を統合するスクリーンを初期化
    SetDrawScreen(mnAllLightScreenHandle);

    constexpr int EXPAND_SIZE = 2;
    const int offsets[][2] =
    {
        { -EXPAND_SIZE, -EXPAND_SIZE }, // 左上
        {  EXPAND_SIZE, -EXPAND_SIZE }, // 右上
        { -EXPAND_SIZE,  EXPAND_SIZE }, // 左下
        {  EXPAND_SIZE,  EXPAND_SIZE }, // 右下
        {  0,           -EXPAND_SIZE * 2 }, // 上
        {  0,            EXPAND_SIZE * 2 }, // 下
        { -EXPAND_SIZE * 2,  0            }, // 左
        {  EXPAND_SIZE * 2,  0            }, // 右
        {  0,            0            }  // 元の位置
    };

    // 各光領域を統合
    for (const auto& screenHandle : mnLightScreenHandle)
    {
        for (const auto& offset : offsets)
        {
            DrawExtendGraph(0 + offset[0], 0 + offset[1], static_cast<int>(mstMaskData.maskSize.GetX()) + offset[0], static_cast<int>(mstMaskData.maskSize.GetY()) + offset[1], screenHandle.FilpScreenHandle, TRUE);
        }
    }

	// 描画先を裏画面にする
	SetDrawScreen(DX_SCREEN_BACK);

    CreateMaskScreen();
    SetMaskScreenGraph(mnAllLightScreenHandle);



    // マスクを有効にする
    SetUseMaskScreenFlag(TRUE);

    // SetDrawBlendMode(DX_BLENDMODE_ALPHA, 50);
    // DrawBox(0, 0, static_cast<int>(mstMaskData.maskSize.GetX()), static_cast<int>(mstMaskData.maskSize.GetY()), GetColor(0, 0, 0), TRUE);

    SetDrawBlendMode(DX_BLENDMODE_SUB, 50);
    DrawBox(0, 0, static_cast<int>(mstMaskData.maskSize.GetX()), static_cast<int>(mstMaskData.maskSize.GetY()), GetColor(255, 255, 255), TRUE);

    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

    // マスクを無効にする
    SetUseMaskScreenFlag(FALSE);
    SetMaskScreenGraph(-1);
    DeleteMaskScreen();


    // for (LIGHT_SCREEN_HANDLE& screenHandle : mnLightScreenHandle)
    // {
        
    //     // 全光領域を統合するスクリーンを初期化
    //     SetDrawScreen(screenHandle.SceneObjectScreenHandle);

    //     constexpr int EXPAND_SIZE = 5;
    //     const int offsets[][2] =
    //     {
    //         // { -EXPAND_SIZE, -EXPAND_SIZE }, // 左上
    //         // {  EXPAND_SIZE, -EXPAND_SIZE }, // 右上
    //         // { -EXPAND_SIZE,  EXPAND_SIZE }, // 左下
    //         // {  EXPAND_SIZE,  EXPAND_SIZE }, // 右下
    //         // {  0,           -EXPAND_SIZE * 2 }, // 上
    //         // {  0,            EXPAND_SIZE * 2 }, // 下
    //         // { -EXPAND_SIZE * 2,  0            }, // 左
    //         // {  EXPAND_SIZE * 2,  0            }, // 右
    //         {  0,            0            }  // 元の位置
    //     };

    //     // 各光領域を統合
    //     for (const auto& offset : offsets)
    //     {
    //         DrawExtendGraph(0 + offset[0], 0 + offset[1], static_cast<int>(mstMaskData.maskSize.GetX()) + offset[0], static_cast<int>(mstMaskData.maskSize.GetY()) + offset[1], screenHandle.FilpScreenHandle, TRUE);
    //     }

    //     // 描画先を裏画面にする
    //     SetDrawScreen(DX_SCREEN_BACK);

    //     CreateMaskScreen();
    //     SetMaskScreenGraph(screenHandle.SceneObjectScreenHandle);

    //     // マスクを有効にする
    //     SetUseMaskScreenFlag(TRUE);

    //     SetDrawBlendMode(DX_BLENDMODE_ALPHA, 20);

    //     DrawBox(0, 0, static_cast<int>(mstMaskData.maskSize.GetX()), static_cast<int>(mstMaskData.maskSize.GetY()), GetColor(0, 0, 0), TRUE);

    //     SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

    //     // マスクを無効にする
    //     SetUseMaskScreenFlag(FALSE);
    //     SetMaskScreenGraph(-1);
    //     DeleteMaskScreen();
    // }
}