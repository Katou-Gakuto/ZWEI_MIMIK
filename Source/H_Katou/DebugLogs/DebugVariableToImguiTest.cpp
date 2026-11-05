#include "DebugVariableToImguiTest.h"

#include <cmath>
#include <vector>

#include "DebugVariableToImgui.h"
#include "VECTOR.h"

namespace DebugVariableToImguiTest
{
    // struct ExampleStats
    // {
    //     int hp;
    //     float speed;
    // };

    // struct TestState
    // {
    //     int health;
    //     float moveSpeed;
    //     double scale;
    //     bool enabled;
    //     std::vector<int> sampleInts;
    //     std::vector<float> sampleFloats;
    //     ExampleStats stats;

    //     TestState()
    //         : health(120)
    //         , moveSpeed(4.0f)
    //         , scale(1.5)
    //         , enabled(true)
    //         , sampleInts{10, 20, 30}
    //         , sampleFloats{1.0f, 2.0f, 3.0f}
    //         , stats{120, 4.0f}
    //     {
    //     }
    // };

    // static TestState& GetState()
    // {
    //     static TestState state;
    //     return state;
    // }

    // static void RegisterStartupEntries()
    // {
    //     auto& state = GetState();

    //     DebugVariableToImgui::PrivateVariable::GetEntries().clear();

    //     debugVar::Register(
    //         "Health", state.health, debugVar::DrawType_Text,
    //         "MoveSpeed", state.moveSpeed, debugVar::DrawType_Line,
    //         "Scale", state.scale, debugVar::DrawType_Point,
    //         "Enabled", state.enabled, debugVar::DrawType_Text);

    //     debugVar::RegisterValue("LineSample", state.moveSpeed,
    //         debugVar::MakeLineDrawSetting(0x00ccff, 2, 100.0f, 100.0f, 220.0f, 160.0f, "LineSample", "LINE", true));

    //     debugVar::RegisterVector("SampleInts", state.sampleInts,
    //         debugVar::MakeDefaultDrawSetting(debugVar::DrawType_Point, 0xffa500, 1, 6.0f, 10.0f, 10.0f, 30.0f, 240.0f, false, "SampleInts", "INTS", true));

    //     debugVar::RegisterVector("SampleFloats", state.sampleFloats,
    //         debugVar::MakeDefaultDrawSetting(debugVar::DrawType_Line, 0x00ccff, 2, 10.0f, 180.0f, 20.0f, 50.0f, 300.0f, false, "SampleFloats", "FLOATS", true));

    //     debugVar::RegisterStructMembers(
    //         "Stats",
    //         state.stats,
    //         debugVar::StructMemberBinding<ExampleStats, int>{ "HP", &ExampleStats::hp },
    //         debugVar::StructMemberBinding<ExampleStats, float>{ "Speed", &ExampleStats::speed });
    // }

    void Initialize()
    {
        //RegisterStartupEntries();
    }

    void Update()
    {
    }
}
