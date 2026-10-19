#include "ButtonTrigger.h"

#include "../A_GameObject/ButtonObject.h"

#include "../C_Component/ButtonObjectController.h"

// 
ButtonTrigger::ButtonTrigger() :
    mlNodeBox(),
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
    for (uint32_t i = 1; i < this->mlNodeBox.size(); i++)
    {
        // 
        if (result)
        {
            // 
            if (this->mlNodeBox[i - 1].mnLayer != this->mlNodeBox[i].mnLayer)
            {
                // 
                break;
            }
        }
        else
        {
            // 
            if (falseLayer == this->mlNodeBox[i].mnLayer)
            {
                // 
                continue;
            }
            else
            {
                // 
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
    return result;
}

// “–‚½‚è”»’è‚É‚æ‚éƒMƒ~ƒbƒN‚Ì•Ï‰»‚É‘Î‰ž‚³‚¹‚éŠÖ”
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
