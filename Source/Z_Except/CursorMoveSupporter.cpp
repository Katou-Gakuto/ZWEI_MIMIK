#include "CursorMoveSupporter.h"

// 
#include "Master.h"

// 
CursorMoveSupporter::CursorMoveSupporter() :
    mnBaseCount(100),
    mnPushHoldFrameMax(3),
    mnLastModeFrameCount(-100),
    mnPlayerNumber(0)
{
}

// 
CursorMoveSupporter::~CursorMoveSupporter()
{
}

// 
bool CursorMoveSupporter::Move(CursorMoveData &moveData, int &moveVec)
{
    // 
    bool push = false;

    // 
    int stageMove = 0;

    // 
    bool canMove = (this->mnLastModeFrameCount <= 0 || this->mnLastModeFrameCount == this->mnBaseCount);

    // 
    bool playerConst = !(this->mnLastModeFrameCount <= -this->mnBaseCount);

    // 
    int playerNumber = this->mnPlayerNumber;

    // 操作プレイヤーの変更にも対応しながら
    // プレイヤーの入力 + ステージ選択の移動量を取得するループ文
    do
    {
        // 
        for (size_t i = 0; i < moveData.GetIndexCount(); i++)
        {
            // 
            if (Master::mpKeyState->GetShadowGameKey(moveData[i].mnTargetKey, playerNumber))
            {
                // 
                push = true;

                // 
                if (canMove)
                {
                    // 
                    moveVec += moveData[i].mnMoveVec;
                }
            }
        }

        // 
        if (push ||
            playerConst ||
            playerNumber != this->mnPlayerNumber)
        {
            // 
            break;
        }

        // 
        playerNumber = (this->mnPlayerNumber == 0) ? (1) : (0);

    } while (true);

    // 
    if (push)
    {
        // 
        if (!playerConst)
        {
            // 
            this->mnPlayerNumber = playerNumber;
        }

        // 
        if (this->mnLastModeFrameCount <= 0)
        {
            // 
            this->mnLastModeFrameCount = 0;
        }
        else
        {
            // 
            if (this->mnLastModeFrameCount < this->mnBaseCount)
            {
                // 
                this->mnLastModeFrameCount++;
            }
            else
            {
                // 
                this->mnLastModeFrameCount++;

                // 
                unsigned long holdCount = this->mnLastModeFrameCount - this->mnBaseCount;

                // 
                this->mnLastModeFrameCount = this->mnBaseCount + (holdCount % this->mnPushHoldFrameMax);
            }
        }
    }
    else
    {
        // 
        if (0 < this->mnLastModeFrameCount)
        {
            // 
            this->mnLastModeFrameCount = 0;
        }
        else
        {
            // 
            if (-this->mnBaseCount < this->mnLastModeFrameCount)
            {
                this->mnLastModeFrameCount--;
            }
        }
    }

    // 
    return true;
}

// 
bool CursorMoveSupporter::CheckMove()
{
    // 
    return true;
}
