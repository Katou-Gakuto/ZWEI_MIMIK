#include "DxLib.h"

#include "LightAreaManager.h"

#include "LightArea.h"

#include "LightLineNode.h"

// 
LightAreaManager::LightAreaManager() :
    mlNode(),
    mnDeactivateStartIndex(0),
    LightScreenHandle(-1)
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
    if (LightScreenHandle != -1)
    {
        DeleteGraph(LightScreenHandle);
        LightScreenHandle = -1;
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
    ScreenSizeChange();
}

// 描画毎初期化
void LightAreaManager::StartLightDraw()
{
    // 描画先を変更
    SetDrawScreen(LightScreenHandle);
    ClearDrawScreen();

    // マスク画面を作成します
    CreateMaskScreen();

    DrawMaskToDirectData(0, 0, mstMaskData.maskSize.GetX(), mstMaskData.maskSize.GetY(), mstMaskData.maskData, DX_MASKTRANS_NONE);

    // マスク画面を削除します
    DeleteMaskScreen();
}

/*
// シミュレーション内容を描画する関数
// ※既に実行段階である場合は引数がtrueになります。実行段階では描画しない、あるいはその逆の場合はこの引数を使ってください。
int LightExecutor::Draw(bool triggerSignal)
{
    // 
    if (!this->mbLightOn)
    {
        // 光域のシミュレーターは描画はしません
        return 0;
    }

    // 
    LightArea *lightArea = Master::mpLightManager->SearchArea(this->mnAreaIndex);
    LightLineNode *currentNode;
    LightLineNode *nextNode;

    for (uint32_t i = 0; i < lightArea->GetLightLineCount(); i++)
    {
        // 
        currentNode = lightArea->GetFirstNodeBox()[i];

        // 
        if (currentNode == nullptr)
        {
            // 
            continue;
        }

        // 
        while (true)
        {
            // 
            int result = DxLib::DrawLine(
                currentNode->GetMyStartPos().GetX(),
                currentNode->GetMyStartPos().GetY(),
                currentNode->GetMyEndPos().GetX(),
                currentNode->GetMyEndPos().GetY(),
                0x00ffff);

            // 
            if (!currentNode->AccessNext(&nextNode))
            {
                // 
                break;
            }

            // 
            currentNode = nextNode;
        }
    }

    // 光域のシミュレーターは描画はしません
    return 0;
}
*/

// ライト描画処理
void LightAreaManager::LightDraw()
{
    mstLightLine.clear();
    LINE_POS linePosData;
    for (LightArea* lightArea : mlNode)
    {
        LightLineNode *currentNode;
        LightLineNode *nextNode;

        for (uint32_t i = 0; i < lightArea->GetLightLineCount(); i++)
        {
            currentNode = lightArea->GetFirstNodeBox()[i];

            if (currentNode == nullptr)
            {
                continue;
            }

            while (true)
            {
                if (mstLightLine.size() <= 0)
                {
                }
                else
                {
                    linePosData.lineOne = linePosData.lineTwo;
                    linePosData.lineTwo = currentNode->GetMyEndPos();
                    mstLightLine.push_back(linePosData);
                }
                //currentNode->GetMyStartPos().GetX()

                if (!currentNode->AccessNext(&nextNode))
                {
                    break;
                }

                currentNode = nextNode;
            }
        }
    }
    if (mstLightLine.size() <= 0)
    {
        return;
    }
    linePosData.lineOne = linePosData.lineTwo;
    linePosData.lineTwo = mstLightLine[0].lineOne;
    mstLightLine.push_back(linePosData);

    for (int i = 0; i < mstLightLine.size(); ++i)
    {
        DrawLine(mstLightLine[i].lineOne.GetX(), mstLightLine[i].lineOne.GetY(),
                 mstLightLine[i].lineTwo.GetX(), mstLightLine[i].lineTwo.GetY(),
                 0x00ff0f);
    }
}

// ライト描画終了時処理
void LightAreaManager::EndLightDraw()
{
    // 描画先戻す
    SetDrawScreen(DX_SCREEN_BACK);

    // TODO:_ ここ上塗り出来ないように負ける設定にする
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 127);
    // 描画対象画像を画面いっぱいに拡大して描画する
    DrawExtendGraph(0, 0, 640, 480, LightScreenHandle, FALSE);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

// TODO:_ まだおいてない
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
int LightAreaManager::AddArea(LightArea *newArea)
{
    // 
    if (newArea == nullptr)
    {
        // 
        return -1;
    }

    // 
    int addIndex = this->mnDeactivateStartIndex;

    // 
    if (this->mlNode.size() == addIndex)
    {
        // 
        this->mlNode.push_back(newArea);
    }
    else
    {
        // 
        this->mlNode[addIndex] = newArea;
    }

    // 
    this->mnDeactivateStartIndex++;

    // 
    return addIndex;
}

// 
int LightAreaManager::DeleteArea(int areaIndex)
{
    // 
    if (this->mlNode[areaIndex] == nullptr)
    {
        // 
        return 0;
    }

    // 
    delete this->mlNode[areaIndex];

    // 
    this->mlNode[areaIndex] = nullptr;

    // 
    for (uint16_t i = this->mnDeactivateStartIndex - 1; areaIndex < i; i--)
    {
        // 
        this->mlNode[i - 1] = this->mlNode[i];
    }

    // 
    this->mnDeactivateStartIndex--;

    // 
    return 0;
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

// どの光域に入っているかを確認する関数
// 返り値のintは0で処理の成功の可否、引数のoutは自身が入っているAreaIndexを返す関数
int LightAreaManager::CheckInLightArea(const VECTOR2D &pos, std::vector<int> &out)
{
    // 
    for (uint16_t i = 0; i < this->mnDeactivateStartIndex; i++)
    {
        // 
        if (this->mlNode[i]->CheckInArea(pos))
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
    if (LightScreenHandle != -1)
    {
        DeleteGraph(LightScreenHandle);
        LightScreenHandle = -1;
    }
    int screenW, screenH;
    GetScreenState(&screenW, &screenH, NULL);
    LightScreenHandle = MakeScreen(screenW, screenH, TRUE);

    if (mstMaskData.maskData != nullptr)
    {
        free(mstMaskData.maskData);
    }
    mstMaskData.maskData = static_cast<unsigned char*>(malloc(sizeof(unsigned char) * screenW * screenH));
    mstMaskData.maskSize = VECTOR2D(screenW, screenH);

    if (mstMaskData.maskData == nullptr)
    {
        return;
    }
    // マスクを1ピクセルずつ記入
    for (int y = 0; y < mstMaskData.maskSize.GetY(); ++y)
    {
        for (int x = 0; x < mstMaskData.maskSize.GetX(); ++x)
        {
            mstMaskData.maskData[(y * static_cast<int>(mstMaskData.maskSize.GetX())) + x] = 0;
        }
    }
}