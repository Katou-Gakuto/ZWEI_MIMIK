#include <map>
#include <string>

#include "DebugVariableToImgui.h"
#include "Master.h"
#include "Singleton/ImguiManager.h"

// DebugVariableToImgui の内部処理を定義します。
// ImGui の設定編集や DX 描画の実体をここに配置しています。
namespace DebugVariableToImgui
{


    namespace PrivateFunction
    {
        struct Player2
        {
            int Hp;
            float Speed;
        };
        struct Player
        {
            Player2 Hp;
            float Speed;
        };
        
        void Update()
        {
                        
            std::vector<StructMemberIndexData> MemberData;

            MemberData.push_back(MakeMemberData<Player>("Hp", &Player::Hp, &Player2::Hp));

            MemberData.push_back(MakeMemberData("Speed", &Player::Speed));

            Player player;
            player.Hp.Hp = 100;
            player.Speed = 5.0f;

            int hp = *MemberData[0].GetMemberPointer<int>(&player);
            float speed = *(MemberData[1].GetMemberPointer<float>(&player));

            // auto& entries = PrivateVariable::GetEntries();
            // for (auto& entry : entries)
            // {
            //     if (entry.updateImgui)
            //     {
            //         entry.updateImgui();
            //     }
            // }
        }

        void Draw()
        {
            // auto& entries = PrivateVariable::GetEntries();
            // for (auto& entry : entries)
            // {
            //     if (entry.drawDx)
            //     {
            //         entry.drawDx();
            //     }
            // }
        }
    }
}