#pragma once

#include "BaseScene.h"

// 
class OptionScene : public BaseScene
{
public:
    // 
    OptionScene();

    // 
    ~OptionScene();

    int Create() override;
    int Initialize() override;
    int Finalize() override;
    int Update() override;
    int Draw() override;

private:
    // 0Å`255
    int mnVolumeBGM;

    // 0Å`255
    int mnVolumeSE;

};