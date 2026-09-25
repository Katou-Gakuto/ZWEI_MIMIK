#pragma once

#include <vector>

#include "../H_Katou/Singleton/KeyState.h"

// 
struct CursorMoveElement
{
    // 
    int mnMoveVec;

    // 
    KEY_SHADOW_GAME_TYPE mnTargetKey;
};

// 
class CursorMoveData
{
public:
    // 
    CursorMoveData() :
        mlElementBox()
    {
    }

    // 
    ~CursorMoveData()
    {
    }

    // 
    bool Add(const CursorMoveElement &newElement)
    {
        // 
        for (auto element : this->mlElementBox)
        {
            // 
            if (element.mnTargetKey == newElement.mnTargetKey)
            {
                // 
                return false;
            }
        }

        // 
        this->mlElementBox.push_back(newElement);

        // 
        return true;
    }

    // 
    size_t GetIndexCount() const { return this->mlElementBox.size(); }

    // 
    const CursorMoveElement &operator[](size_t index) const { return this->mlElementBox[index]; }

private:
    // 
    std::vector<CursorMoveElement> mlElementBox;
};

// 
class CursorMoveSupporter
{
public:
    // 
    CursorMoveSupporter();

    // 
    ~CursorMoveSupporter();

    // 
    bool Move(CursorMoveData &moveData, int &moveVec);
    
    // 
    bool CheckMove();

private:
    const int mnBaseCount;
    const int mnPushHoldFrameMax;
    int mnLastModeFrameCount;
    int mnPlayerNumber;

};