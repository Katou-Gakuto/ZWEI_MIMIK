#pragma once

#include <vector>

// TODO:_ 色々な描画のしかたを設定できるデバッグを作成する

namespace DebugVariableToImgui
{
    namespace PrivateVariable
    {
        //inline std::vector<>
    }

    namespace PrivateFunction
    {
        void Update();

        void Draw();
    }
}



namespace debugVar = DebugVariableToImgui;