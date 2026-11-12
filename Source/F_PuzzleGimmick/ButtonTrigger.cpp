#include "ButtonTrigger.h"

#include "../A_GameObject/ButtonObject.h"

#include "../C_Component/ButtonObjectController.h"

// 
ButtonTrigger::ButtonTrigger(ButtonTriggerMode mode) :
    mlNodeBox(),
    mnMode(mode),
    BaseGimmickTrigger()
{
}

// 
ButtonTrigger::~ButtonTrigger()
{
    // 
    for (auto &currentButton : this->mlNodeBox)
    {
        // 
        currentButton.mpButton = nullptr;
    }

    // 
    this->mlNodeBox.clear();
}

// 
bool ButtonTrigger::GetSignal()
{
    // 
    if (this->mlNodeBox.empty())
    {
        // 
        return false;
    }

    // 
    ButtonObjectController *controller = nullptr;
    if (this->mlNodeBox[0].mpButton == nullptr)
    {
        // 
        return false;
    }

    // 
    uint32_t falseLayer = this->mlNodeBox[0].mnLayer;
    controller = this->mlNodeBox[0].mpButton->GetButtonController();
    if (controller == nullptr)
    {
        // 
        return false;
    }

    // 
    bool result = controller->GetNowState();
    if (this->mlNodeBox.size() == 1)
    {
        // 
        return result;
    }

    // 
    bool trueCount = false;
    for (uint32_t i = 1; i < this->mlNodeBox.size(); i++)
    {
        // 現状、着目レイヤーがtrueのみの場合かで処理を変える
        if (result)
        {
            // レイヤーが変わった場合は処理を行う
            if (this->mlNodeBox[i - 1].mnLayer != this->mlNodeBox[i].mnLayer)
            {
                // 
                if (this->mnMode == ButtonTriggerMode::ButtonTriggerMode_OneLayer)
                {
                    // trueのレイヤーが1つ見つかったので
                    return true;
                }
                else
                {
                    // 直近のレイヤーがtrueだったのでフラグを逆転させる
                    trueCount = !trueCount;
                }
            }
        }
        else
        {
            // 既にfalseになったレイヤーと同じレイヤーの場合は処理を行う
            if (falseLayer == this->mlNodeBox[i].mnLayer)
            {
                // このループをスキップする
                continue;
            }
            else
            {
                // レイヤーが変わったので再度trueを前提に処理を進める
                result = true;
            }
        }

        // 
        controller = this->mlNodeBox[i].mpButton->GetButtonController();
        if (controller == nullptr)
        {
            // 
            return false;
        }

        // 
        if (!controller->GetNowState())
        {
            // 
            falseLayer = this->mlNodeBox[i].mnLayer;

            // 
            result = false;
        }
    }

    // 
    if (this->mnMode == ButtonTriggerMode::ButtonTriggerMode_OneLayer)
    {
        // 
        return result;
    }

    // 
    if (this->mnMode == ButtonTriggerMode::ButtonTriggerMode_TrueCount)
    {
        // 
        if (result)
        {
            // 
            trueCount = !trueCount;

            // 
            return trueCount;
        }
    }

    // 
    return result;
}

// 当たり判定によるギミックの変化に対応させる関数
int ButtonTrigger::HitOnCollision(BaseCollision *myCollision, BaseCollision *hitCollision)
{
    // 
    return 0;
}

// 
bool ButtonTrigger::AddButton(ButtonObject *button, uint32_t layer)
{
    Node tempNode;
    tempNode.mnLayer = layer;
    tempNode.mpButton = button;

    // 
    this->mlNodeBox.push_back(tempNode);

    // 
    for (uint32_t i = this->mlNodeBox.size() - 1; 0 < i; i--)
    {
        // 
        if (layer <= this->mlNodeBox[i - 1].mnLayer)
        {
            // 
            break;
        }

        // 
        tempNode.mnLayer = this->mlNodeBox[i].mnLayer;

        // 
        tempNode.mpButton = this->mlNodeBox[i].mpButton;

        // 
        this->mlNodeBox[i].mnLayer = this->mlNodeBox[i - 1].mnLayer;

        // 
        this->mlNodeBox[i].mpButton = this->mlNodeBox[i - 1].mpButton;

        // 
        this->mlNodeBox[i - 1].mnLayer = tempNode.mnLayer;

        // 
        this->mlNodeBox[i - 1].mpButton = tempNode.mpButton;
    }


    // 
    return true;
}
