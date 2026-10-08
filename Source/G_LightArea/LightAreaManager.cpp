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
        if (mnLightScreenHandle[i] != -1)
        {
            DeleteGraph(mnLightScreenHandle[i]);
            mnLightScreenHandle[i] = -1;
        }
    }
    mnLightScreenHandle.clear();

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
    for (int i = 0; i < mnLightScreenHandle.size(); ++i)
    {
        if (mnLightScreenHandle[i] != -1)
        {
            DeleteGraph(mnLightScreenHandle[i]);
            mnLightScreenHandle[i] = -1;
        }
        mnLightScreenHandle[i] = MakeScreen(Master::mpDxLibDataManager->GetDisplaySize().GetX(), Master::mpDxLibDataManager->GetDisplaySize().GetY(), TRUE);
    }

    if (mstMaskData.maskData != nullptr)
    {
        free(mstMaskData.maskData);
    }
    mstMaskData.maskData = static_cast<unsigned char*>(malloc(sizeof(unsigned char) * Master::mpDxLibDataManager->GetDisplaySize().GetX() * Master::mpDxLibDataManager->GetDisplaySize().GetY()));
    mstMaskData.maskSize = Master::mpDxLibDataManager->GetDisplaySize();

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
    for (int i = 0; i < mnLightScreenHandle.size(); ++i)
    {
        // 描画先を変更
        SetDrawScreen(mnLightScreenHandle[i]);
        ClearDrawScreen();

        // マスク画面を作成します
        CreateMaskScreen();

        DrawMaskToDirectData(0, 0, mstMaskData.maskSize.GetX(), mstMaskData.maskSize.GetY(), mstMaskData.maskData, DX_MASKTRANS_NONE);

        // マスク画面を削除します
        DeleteMaskScreen();
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
                mnLightScreenHandle.push_back(MakeScreen(Master::mpDxLibDataManager->GetDisplaySize().GetX(), Master::mpDxLibDataManager->GetDisplaySize().GetY(), TRUE));
            }
        }
        else
        {
            while (mnLightScreenHandle.size() > colorCount)
            {
                if (mnLightScreenHandle[mnLightScreenHandle.size() - 1] != -1)
                {
                    DeleteGraph(mnLightScreenHandle[mnLightScreenHandle.size() - 1]);
                }
                mnLightScreenHandle.pop_back();
            }
        }
    }

    // 光描画
    for (int i = 0; i < mnLightScreenHandle.size(); ++i)
    {
        SetDrawScreen(mnLightScreenHandle[i]);
        for (LightArea* lightArea : mlNode)
        {
            if (lightArea->GetLightColor() == colorNumbers[i])
            {
                lightArea->DrawLightArea();
            }
        }
    }

    // mstLightLines.clear();
    // std::vector<std::vector<LIGHT_DATA>> lightLine;
    // for (int lightAreaIndex = 0; lightAreaIndex < this->mnDeactivateStartIndex; ++lightAreaIndex)
    // {
    //     LightArea *lightArea = this->mlNode[lightAreaIndex];
    //     LightLineNode* currentNode;
    //     LightLineNode* nextNode;

    //     for (uint32_t i = 0; i < lightArea->GetLightLineCount(); ++i)
    //     {
    //         currentNode = lightArea->GetFirstNodeBox()[i];

    //         if (currentNode == nullptr)
    //         {
    //             continue;
    //         }

    //         // ループ数
    //         int loopCount = 0;
    //         while (true)
    //         {

    //             // 情報保存
    //             LIGHT_DATA linePosData;
    //             linePosData.lineOne = currentNode->GetMyStartPos();
    //             linePosData.lineTwo = currentNode->GetMyEndPos();
    //             linePosData = GetScreenInsideLine(linePosData);
    //             linePosData.lightColor = lightArea->GetLightColor();

    //             // このループ数最初の判定なら追加だけして次へ
    //             if (lightLine.size() <= loopCount)
    //             {
    //                 // 情報を追加
    //                 lightLine.push_back({linePosData});
    //             }
    //             // 前に設定したことがあるから調べる
    //             else
    //             {
    //                 /*このif判定順番厳守、配列の参照でエラー出る*/
    //                 if (/*二つのラインで四角分がこれまでに作成されているか判定*/
    //                     (lightLine[loopCount].size() >= 2) &&
    //                     /*前の二つのラインを見て今のラインの頂点が両点座標が直線上にあるか判定*/
    //                     (IsPointOnLine(lightLine[loopCount][lightLine[loopCount].size() - 1/*後ろから1番目の配列参照*/].lineOne, lightLine[loopCount][lightLine[loopCount].size() - 2/*後ろから2番目の配列参照*/].lineOne, linePosData.lineOne) &&
    //                      IsPointOnLine(lightLine[loopCount][lightLine[loopCount].size() - 1/*後ろから1番目の配列参照*/].lineTwo, lightLine[loopCount][lightLine[loopCount].size() - 2/*後ろから2番目の配列参照*/].lineTwo, linePosData.lineTwo)))
    //                 {
    //                     // 前回登録した情報を書き換える
    //                     lightLine[loopCount][lightLine[loopCount].size() - 1/*後ろから1番目の配列参照*/] = linePosData;
    //                 }
    //                 else
    //                 {
    //                     // 情報を追加
    //                     lightLine[loopCount].push_back(linePosData);
    //                 }
    //             }

    //             // 次のノードがあるか確認
    //             if (!currentNode->AccessNext(&nextNode))
    //             {
    //                 break;
    //             }

    //             // 次のノード設定
    //             currentNode = nextNode;

    //             // ループ数インクリメント
    //             ++loopCount;
    //         }
    //     }

    //     // 一周しているか
    //     if (lightArea->GetFinal2Start() && (0 < lightArea->GetLightLineCount()))
    //     {
    //         currentNode = lightArea->GetFirstNodeBox()[0];
    //         if (currentNode == nullptr)
    //         {
    //             continue;
    //         }

    //         // ループ数
    //         int loopCount = 0;
    //         while (true)
    //         {

    //             // 情報保存
    //             LIGHT_DATA linePosData;
    //             linePosData.lineOne = currentNode->GetMyStartPos();
    //             linePosData.lineTwo = currentNode->GetMyEndPos();
    //             linePosData = GetScreenInsideLine(linePosData);
    //             linePosData.lightColor = lightArea->GetLightColor();

    //             // このループ数最初の判定なら追加だけして次へ
    //             if (lightLine.size() <= loopCount)
    //             {
    //                 // 情報を追加
    //                 lightLine.push_back({ linePosData });
    //             }
    //             // 前に設定したことがあるから調べる
    //             else
    //             {
    //                 /*このif判定順番厳守、配列の参照でエラー出る*/
    //                 if (/*二つのラインで四角分がこれまでに作成されているか判定*/
    //                     (lightLine[loopCount].size() >= 2) &&
    //                     /*前の二つのラインを見て今のラインの頂点が両点座標が直線上にあるか判定*/
    //                     (IsPointOnLine(lightLine[loopCount][lightLine[loopCount].size() - 1/*後ろから1番目の配列参照*/].lineOne, lightLine[loopCount][lightLine[loopCount].size() - 2/*後ろから2番目の配列参照*/].lineOne, linePosData.lineOne) &&
    //                         IsPointOnLine(lightLine[loopCount][lightLine[loopCount].size() - 1/*後ろから1番目の配列参照*/].lineTwo, lightLine[loopCount][lightLine[loopCount].size() - 2/*後ろから2番目の配列参照*/].lineTwo, linePosData.lineTwo)))
    //                 {
    //                     // 前回登録した情報を書き換える
    //                     lightLine[loopCount][lightLine[loopCount].size() - 1/*後ろから1番目の配列参照*/] = linePosData;
    //                 }
    //                 else
    //                 {
    //                     // 情報を追加
    //                     lightLine[loopCount].push_back(linePosData);
    //                 }
    //             }

    //             // 次のノードがあるか確認
    //             if (!currentNode->AccessNext(&nextNode))
    //             {
    //                 break;
    //             }

    //             // 次のノード設定
    //             currentNode = nextNode;

    //             // ループ数インクリメント
    //             ++loopCount;
    //         }
    //     }

    //     // 1ライト分の情報設定
    //     mstLightLines.push_back(lightLine);
    //     lightLine.clear();
    // }

    // // 何も登録されていないなら何もしない
    // if (mstLightLines.size() <= 0)
    // {
    //     return;
    // }

    
    // // 四角設定用変数設定
    // constexpr unsigned int boxIndexMax = 4;
    // VERTEX2D setBoxPosDatas[boxIndexMax];
    // {
    //     VERTEX2D startBoxPosData;
    //     startBoxPosData.rhw = 1.0f;
    //     startBoxPosData.u = 0.0f;
    //     startBoxPosData.v = 0.0f;
    //     for (int i = 0; i < boxIndexMax; ++i)
    //     {
    //         setBoxPosDatas[i] = startBoxPosData;
    //     }
    // }
    
    // // 三角形を入力する情報の数を測定
    // unsigned int lightAreaTriangleSize = 0;
    // for (int lightAreaIterator = 0; lightAreaIterator < mstLightLines.size(); ++lightAreaIterator)
    // {
    //     for (int i = 0; i < mstLightLines[lightAreaIterator].size(); ++i)
    //     {
    //         // 四角ができるか判定
    //         if (mstLightLines[lightAreaIterator][i].size() < 2)
    //         {
    //             continue;
    //         }
    //         lightAreaTriangleSize += mstLightLines[lightAreaIterator][i].size() - 1/*一番後ろは計測しない*/;
    //     }
    // }
    // lightAreaTriangleSize *= 6;/*一つの4角で6個頂点を登録する*/

    // // 中に何か入っているなら消して新しくメモリを用意する
    // if (mstLightAreaTriangleVertex != nullptr)
    // {
    //     free(mstLightAreaTriangleVertex);
    // }
    // mstLightAreaTriangleVertex = static_cast<VERTEX2D*>(malloc(sizeof(VERTEX2D) * lightAreaTriangleSize));

    // // 四角を三角で設定
    // unsigned int lightAreaIndex = 0;
    // for (int lightAreaIterator = 0; lightAreaIterator < mstLightLines.size(); ++lightAreaIterator)
    // {
    //     for (size_t i = 0; i < mstLightLines[lightAreaIterator].size(); ++i)
    //     {
    //         // 四角ができるか判定
    //         if (mstLightLines[lightAreaIterator][i].size() < 2)
    //         {
    //             continue;
    //         }
    //         for (size_t l = 0; l < (mstLightLines[lightAreaIterator][i].size() - 1)/*四角にするために最後を除いて処理*/; ++l)
    //         {
    //             // 4頂点入力
    //             {
    //                 LIGHT_DATA lightLeftData = mstLightLines[lightAreaIterator][i][l];
    //                 LIGHT_DATA lightRightData = mstLightLines[lightAreaIterator][i][l + 1];
    //                 setBoxPosDatas[0].dif = GetColorU8(((lightLeftData.lightColor & 0xff0000) >> 16), ((lightLeftData.lightColor & 0x00ff00) >> 8), (lightLeftData.lightColor & 0x0000ff), 255);
    //                 setBoxPosDatas[1].dif = GetColorU8(((lightLeftData.lightColor & 0xff0000) >> 16), ((lightLeftData.lightColor & 0x00ff00) >> 8), (lightLeftData.lightColor & 0x0000ff), 255);
    //                 setBoxPosDatas[2].dif = GetColorU8(((lightRightData.lightColor & 0xff0000) >> 16), ((lightRightData.lightColor & 0x00ff00) >> 8), (lightRightData.lightColor & 0x0000ff), 255);
    //                 setBoxPosDatas[3].dif = GetColorU8(((lightRightData.lightColor & 0xff0000) >> 16), ((lightRightData.lightColor & 0x00ff00) >> 8), (lightRightData.lightColor & 0x0000ff), 255);

    //                 setBoxPosDatas[0].pos = VGet(lightLeftData.lineOne.GetX(), lightLeftData.lineOne.GetY(), 0.0f);
    //                 setBoxPosDatas[1].pos = VGet(lightLeftData.lineTwo.GetX(), lightLeftData.lineTwo.GetY(), 0.0f);
    //                 setBoxPosDatas[2].pos = VGet(lightRightData.lineOne.GetX(), lightRightData.lineOne.GetY(), 0.0f);
    //                 setBoxPosDatas[3].pos = VGet(lightRightData.lineTwo.GetX(), lightRightData.lineTwo.GetY(), 0.0f);
    //             }
    //             mstLightAreaTriangleVertex[lightAreaIndex++] = setBoxPosDatas[0];
    //             mstLightAreaTriangleVertex[lightAreaIndex++] = setBoxPosDatas[1];
    //             mstLightAreaTriangleVertex[lightAreaIndex++] = setBoxPosDatas[2];

    //             mstLightAreaTriangleVertex[lightAreaIndex++] = setBoxPosDatas[1];
    //             mstLightAreaTriangleVertex[lightAreaIndex++] = setBoxPosDatas[2];
    //             mstLightAreaTriangleVertex[lightAreaIndex++] = setBoxPosDatas[3];
    //         }
    //     }
    // }

    // // 設定した3角を全部描画
    // DxLib::DrawPolygon2D(mstLightAreaTriangleVertex, lightAreaTriangleSize / 3, mnLightAreaGraphHandle, TRUE); 

    // // テスト用描画
    // for (size_t i = 0; i < lightLine.size(); ++i)
    // {
    //     for (size_t l = 0; l < lightLine[i].size(); ++l)
    //     {
    //         DrawLine(lightLine[i][l].lineOne.GetX(), lightLine[i][l].lineOne.GetY(),
    //                  lightLine[i][l].lineTwo.GetX(), lightLine[i][l].lineTwo.GetY(),
    //                  0xff0000);
    //     }
    // }
    // for (size_t i = 0; i < mstLightLines.size(); ++i)
    // {
    //     for (size_t l = 0; l < mstLightLines[i].size(); ++l)
    //     {
    //         DrawLine(mstLightLines[i][l].lineOne.GetX(), mstLightLines[i][l].lineOne.GetY(),
    //                  mstLightLines[i][l].lineTwo.GetX(), mstLightLines[i][l].lineTwo.GetY(),
    //                  0xffffff);
    //     }
    // }
}

// ライト描画終了時処理
void LightAreaManager::EndLightDraw()
{
    // 描画先戻す
    SetDrawScreen(DX_SCREEN_BACK);

    // TODO:_ ここ上塗り出来ないように負ける設定にする
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 125);
    for (int i = 0; i < mnLightScreenHandle.size(); ++i)
    {
        // 描画対象画像を画面いっぱいに拡大して描画する
        DrawExtendGraph(0, 0, mstMaskData.maskSize.GetX(), mstMaskData.maskSize.GetY(), mnLightScreenHandle[i], TRUE);
    }
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}