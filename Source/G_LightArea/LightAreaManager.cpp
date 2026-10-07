#include "LightAreaManager.h"

#include "LightArea.h"

#include "../S_Collision/Point2D.h"

// 
LightAreaManager::LightAreaManager() :
    mlNode(),
    mnDeactivateStartIndex(0)
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
