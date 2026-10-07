#include "DxLib.h"

#include "LightAreaManager.h"

#include "LightArea.h"

#include "LightLineNode.h"

#include "Master.h"

#include "ResourceManager.h"

#include "../S_Collision/Point2D.h"

// 
LightAreaManager::LightAreaManager() :
    mlNode(),
    mnDeactivateStartIndex(0),
    LightScreenHandle(-1),
    mstMaskData(),
    mstLightLine(),
    mstLightAreaTriangleVertex(nullptr),
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
            mstMaskData.maskData[(y * static_cast<int>(mstMaskData.maskSize.GetX())) + x] = 0xff;
        }
    }
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

// ライト描画処理
void LightAreaManager::LightDraw()
{
    mstLightLine.clear();
    std::vector<std::vector<LIGHT_LINE_DATA>> lightLine;
    for (int lightAreaIndex = 0; lightAreaIndex < this->mnDeactivateStartIndex; ++lightAreaIndex)
    {
        LightArea *lightArea = this->mlNode[lightAreaIndex];
        LightLineNode* currentNode;
        LightLineNode* nextNode;

        for (uint32_t i = 0; i < lightArea->GetLightLineCount(); ++i)
        {
            currentNode = lightArea->GetFirstNodeBox()[i];

            if (currentNode == nullptr)
            {
                continue;
            }

            // ループ数
            int loopCount = 0;
            while (true)
            {

                // 情報保存
                LIGHT_LINE_DATA linePosData;
                linePosData.lineOne = currentNode->GetMyStartPos();
                linePosData.lineTwo = currentNode->GetMyEndPos();
                linePosData = GetScreenInsideLine(linePosData);

                // このループ数最初の判定なら追加だけして次へ
                if (mstLightLine.size() <= loopCount)
                {
                    // 情報を追加
                    mstLightLine.push_back({linePosData});
                    lightLine.push_back({linePosData});
                }
                // 前に設定したことがあるから調べる
                else
                {
                    /*このif判定順番厳守、配列の参照でエラー出る*/
                    if (/*二つのラインで四角分がこれまでに作成されているか判定*/
                        (mstLightLine[loopCount].size() >= 2) &&
                        /*前の二つのラインを見て今のラインの頂点が両点座標が直線上にあるか判定*/
                        (IsPointOnLine(mstLightLine[loopCount][mstLightLine[loopCount].size() - 1/*後ろから1番目の配列参照*/].lineOne, mstLightLine[loopCount][mstLightLine[loopCount].size() - 2/*後ろから2番目の配列参照*/].lineOne, linePosData.lineOne) &&
                         IsPointOnLine(mstLightLine[loopCount][mstLightLine[loopCount].size() - 1/*後ろから1番目の配列参照*/].lineTwo, mstLightLine[loopCount][mstLightLine[loopCount].size() - 2/*後ろから2番目の配列参照*/].lineTwo, linePosData.lineTwo)))
                    {
                        // 前回登録した情報を書き換える
                        mstLightLine[loopCount][mstLightLine[loopCount].size() - 1/*後ろから1番目の配列参照*/] = linePosData;
                        lightLine[loopCount].push_back(linePosData);
                    }
                    else
                    {
                        // 情報を追加
                        mstLightLine[loopCount].push_back(linePosData);
                        lightLine[loopCount].push_back(linePosData);
                    }
                }

                // 次のノードがあるか確認
                if (!currentNode->AccessNext(&nextNode))
                {
                    break;
                }

                // 次のノード設定
                currentNode = nextNode;

                // ループ数インクリメント
                ++loopCount;
            }
        }
    }

    // 何も登録されていないなら何もしない
    if (mstLightLine.size() <= 0)
    {
        return;
    }

    
    // 四角設定用変数設定
    constexpr unsigned int boxIndexMax = 4;
    VERTEX2D setBoxPosDatas[boxIndexMax];
    {
        VERTEX2D startBoxPosData;
        startBoxPosData.rhw = 1.0f;
        startBoxPosData.dif = GetColorU8(255, 255, 255, 255 * 1.0f);
        startBoxPosData.u = 0.0f;
        startBoxPosData.v = 0.0f;
        for (int i = 0; i < boxIndexMax; ++i)
        {
            setBoxPosDatas[i] = startBoxPosData;
        }
    }
    
    // 三角形を入力する情報の数を測定
    unsigned int lightAreaTriangleSize = 0;
    for (size_t i = 0; i < mstLightLine.size(); ++i)
    {
        // 四角ができるか判定
        if (mstLightLine[i].size() < 2)
        {
            continue;
        }
        lightAreaTriangleSize += mstLightLine[i].size() - 1/*一番後ろは計測しない*/;
    }
    lightAreaTriangleSize *= 6;/*一つの4角で6個頂点を登録する*/

    // 中に何か入っているなら消して新しくメモリを用意する
    if (mstLightAreaTriangleVertex != nullptr)
    {
        free(mstLightAreaTriangleVertex);
    }
    mstLightAreaTriangleVertex = static_cast<VERTEX2D*>(malloc(sizeof(VERTEX2D) * lightAreaTriangleSize));

    // 四角を三角で設定
    unsigned int lightAreaIndex = 0;
    for (size_t i = 0; i < mstLightLine.size(); ++i)
    {
        // 四角ができるか判定
        if (mstLightLine[i].size() < 2)
        {
            continue;
        }
        for (size_t l = 0; l < (mstLightLine[i].size() - 1)/*四角にするために最後を除いて処理*/; ++l)
        {
            // 4頂点入力
            {
                setBoxPosDatas[0].dif = GetColorU8(255 * (static_cast<float>((i * mstLightLine.size()) + l) / static_cast<float>(mstLightLine.size() + mstLightLine[i].size() - 1)), 255 * (static_cast<float>((i * mstLightLine.size()) + l) / static_cast<float>(mstLightLine.size() + mstLightLine[i].size() - 1)), 255 * (static_cast<float>((i * mstLightLine.size()) + l) / static_cast<float>(mstLightLine.size() + mstLightLine[i].size() - 1)), 255 * 1.0f);
                setBoxPosDatas[2].dif = GetColorU8(255 * (static_cast<float>((i * mstLightLine.size()) + l) / static_cast<float>(mstLightLine.size() + mstLightLine[i].size() - 1)), 255 * (static_cast<float>((i * mstLightLine.size()) + l) / static_cast<float>(mstLightLine.size() + mstLightLine[i].size() - 1)), 255 * (static_cast<float>((i * mstLightLine.size()) + l) / static_cast<float>(mstLightLine.size() + mstLightLine[i].size() - 1)), 255 * 1.0f);

                setBoxPosDatas[0].pos = VGet(mstLightLine[i][l].lineOne.GetX(), mstLightLine[i][l].lineOne.GetY(), 0.0f);
                setBoxPosDatas[1].pos = VGet(mstLightLine[i][l].lineTwo.GetX(), mstLightLine[i][l].lineTwo.GetY(), 0.0f);
                setBoxPosDatas[2].pos = VGet(mstLightLine[i][l + 1].lineOne.GetX(), mstLightLine[i][l + 1].lineOne.GetY(), 0.0f);
                setBoxPosDatas[3].pos = VGet(mstLightLine[i][l + 1].lineTwo.GetX(), mstLightLine[i][l + 1].lineTwo.GetY(), 0.0f);
            }
            mstLightAreaTriangleVertex[lightAreaIndex++] = setBoxPosDatas[0];
            mstLightAreaTriangleVertex[lightAreaIndex++] = setBoxPosDatas[1];
            mstLightAreaTriangleVertex[lightAreaIndex++] = setBoxPosDatas[2];

            mstLightAreaTriangleVertex[lightAreaIndex++] = setBoxPosDatas[1];
            mstLightAreaTriangleVertex[lightAreaIndex++] = setBoxPosDatas[2];
            mstLightAreaTriangleVertex[lightAreaIndex++] = setBoxPosDatas[3];
        }
    }

    // 設定した3角を全部描画
    DrawPolygon2D(mstLightAreaTriangleVertex, lightAreaTriangleSize / 3, mnLightAreaGraphHandle, TRUE); 

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
    // for (size_t i = 0; i < mstLightLine.size(); ++i)
    // {
    //     for (size_t l = 0; l < mstLightLine[i].size(); ++l)
    //     {
    //         DrawLine(mstLightLine[i][l].lineOne.GetX(), mstLightLine[i][l].lineOne.GetY(),
    //                  mstLightLine[i][l].lineTwo.GetX(), mstLightLine[i][l].lineTwo.GetY(),
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
    // 描画対象画像を画面いっぱいに拡大して描画する
    DrawExtendGraph(0, 0, mstMaskData.maskSize.GetX(), mstMaskData.maskSize.GetY(), LightScreenHandle, TRUE);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

// 指定した2点を通る直線上に点があるかを判定
bool LightAreaManager::IsPointOnLine(const VECTOR2D& linePos1, const VECTOR2D& linePos2, const VECTOR2D& checkPos)
{
    // 直線の方向ベクトル
    const VECTOR2D lineVec = linePos2 - linePos1;
    // 始点から判定対象までのベクトル
    const VECTOR2D checkVec = checkPos - linePos1;

    // 外積が0なら、3点は同一直線上にある
    return std::fabs(VECTOR2D::Cross(lineVec, checkVec)) < 0.001f;
}

// 片方の点が画面外の場合、画面内に収まる位置まで線分を縮める
LightAreaManager::LIGHT_LINE_DATA LightAreaManager::GetScreenInsideLine(const LIGHT_LINE_DATA& linePos)
{
    LIGHT_LINE_DATA result = linePos;

    const float screenWidth = mstMaskData.maskSize.GetX();
    const float screenHeight = mstMaskData.maskSize.GetY();

    const VECTOR2D& pos1 = linePos.lineOne;
    const VECTOR2D& pos2 = linePos.lineTwo;

    // 両方とも画面内ならそのまま返す
    const bool pos1Inside = pos1.GetX() >= 0.0f && pos1.GetX() <= screenWidth &&
                            pos1.GetY() >= 0.0f && pos1.GetY() <= screenHeight;

    const bool pos2Inside = pos2.GetX() >= 0.0f && pos2.GetX() <= screenWidth &&
                            pos2.GetY() >= 0.0f && pos2.GetY() <= screenHeight;

    if (pos1Inside == pos2Inside)
    {
        return result;
    }

    // 画面内の点
    const VECTOR2D insidePos = pos1Inside ? pos1 : pos2;

    // 画面外の点
    const VECTOR2D outsidePos = pos1Inside ? pos2 : pos1;

    const VECTOR2D direction = outsidePos - insidePos;

    float nearestT = 1.0f;
    bool hasIntersection = false;

    // 左端
    if (direction.GetX() != 0.0f)
    {
        const float t = (0.0f - insidePos.GetX()) / direction.GetX();

        if (t >= 0.0f && t <= 1.0f)
        {
            const float y = insidePos.GetY() + direction.GetY() * t;

            if (y >= 0.0f && y <= screenHeight && t < nearestT)
            {
                nearestT = t;
                hasIntersection = true;
            }
        }
    }

    // 右端
    if (direction.GetX() != 0.0f)
    {
        const float t = (screenWidth - insidePos.GetX()) / direction.GetX();

        if (t >= 0.0f && t <= 1.0f)
        {
            const float y = insidePos.GetY() + direction.GetY() * t;

            if (y >= 0.0f && y <= screenHeight && t < nearestT)
            {
                nearestT = t;
                hasIntersection = true;
            }
        }
    }

    // 上端
    if (direction.GetY() != 0.0f)
    {
        const float t = (0.0f - insidePos.GetY()) / direction.GetY();

        if (t >= 0.0f && t <= 1.0f)
        {
            const float x = insidePos.GetX() + direction.GetX() * t;

            if (x >= 0.0f && x <= screenWidth && t < nearestT)
            {
                nearestT = t;
                hasIntersection = true;
            }
        }
    }

    // 下端
    if (direction.GetY() != 0.0f)
    {
        const float t = (screenHeight - insidePos.GetY()) / direction.GetY();

        if (t >= 0.0f && t <= 1.0f)
        {
            const float x = insidePos.GetX() + direction.GetX() * t;

            if (x >= 0.0f && x <= screenWidth && t < nearestT)
            {
                nearestT = t;
                hasIntersection = true;
            }
        }
    }

    if (hasIntersection)
    {
        const VECTOR2D newPos = insidePos + direction * nearestT;

        if (pos1Inside)
        {
            result.lineTwo = newPos;
        }
        else
        {
            result.lineOne = newPos;
        }
    }

    return result;
}