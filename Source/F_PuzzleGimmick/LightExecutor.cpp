#include "LightExecutor.h"

#include "DxLib.h"

#include "../A_GameObject/GameObject2D.h"

#include "../E_Scene/BaseScene.h"
#include "../E_Scene/BaseSceneManager.h"

#include "../G_LightArea/LightLineNode.h"
#include "../G_LightArea/LightArea.h"
#include "../G_LightArea/LightAreaManager.h"

#include "../S_Collision/BaseCollision2D.h"
#include "../S_Collision/Ray2D.h"
#include "../S_Collision/BaseCollision2DManager.h"

#include "../Y_Tool/MyFunctions.h"

#include "../Z_Except/Master.h"

int gnDebugTest = 0;

#include "ImguiManager.h"
//==================================================
// ImguiManager ボタンテスト用変数
//==================================================
IMGUI_BUTTON_CONTROL_VARIABLE testButton1;
IMGUI_BUTTON_CONTROL_VARIABLE testButton2;
IMGUI_BUTTON_CONTROL_VARIABLE testButton3;
IMGUI_BUTTON_CONTROL_VARIABLE testButton4;
IMGUI_BUTTON_CONTROL_VARIABLE testButton5;
IMGUI_BUTTON_CONTROL_VARIABLE testButton6;
IMGUI_BUTTON_CONTROL_VARIABLE testButton7;
IMGUI_BUTTON_CONTROL_VARIABLE testButton8;
IMGUI_BUTTON_CONTROL_VARIABLE testButton9;
IMGUI_BUTTON_CONTROL_VARIABLE testButton10;
IMGUI_BUTTON_CONTROL_VARIABLE testButton11;
IMGUI_BUTTON_CONTROL_VARIABLE testButton12;
IMGUI_BUTTON_CONTROL_VARIABLE testButton13;
//==================================================
// ImguiManager ボタンテスト用変数の初期化
//==================================================
void InitializeTestAllButtonImgui()
{
    //==================================================
    // 1. 標準ボタン
    //==================================================
    testButton1.ButtonType = IMGUI_BUTTON_TYPE::BUTTON;
    testButton1.Label = "Normal Button";
    testButton1.Size = ImVec2(150.0f, 30.0f);

    //==================================================
    // 2. 小型ボタン
    //==================================================
    testButton2.ButtonType = IMGUI_BUTTON_TYPE::SMALL_BUTTON;
    testButton2.Label = "Small Button";

    //==================================================
    // 3. 矢印ボタン
    //==================================================
    testButton3.ButtonType = IMGUI_BUTTON_TYPE::ARROW_BUTTON;
    testButton3.Label = "Arrow";
    testButton3.ImGuiEnumFlags = ImGuiDir_Right;

    //==================================================
    // 4. 透明ボタン
    //==================================================
    testButton4.ButtonType = IMGUI_BUTTON_TYPE::INVISIBLE_BUTTON;
    testButton4.Label = "Invisible";
    testButton4.Size = ImVec2(150.0f, 30.0f);
    testButton4.ImGuiEnumFlags = ImGuiButtonFlags_None;

    //==================================================
    // 5. チェックボックス
    //==================================================
    testButton5.ButtonType = IMGUI_BUTTON_TYPE::CHECK_BOX;
    testButton5.Label = "Check Box";
    testButton5.ButtonFlag = false;

    //==================================================
    // 6. ビットフラグ用チェックボックス
    //==================================================
    testButton6.ButtonType = IMGUI_BUTTON_TYPE::CHECK_BOX_FLAGS;
    testButton6.Label = "Flag Bit";
    testButton6.ButtonBitFlag.flags = 0;
    testButton6.ButtonBitFlagValue = 1u;

    //==================================================
    // 7. ラジオボタン
    //==================================================
    testButton7.ButtonType = IMGUI_BUTTON_TYPE::RADIO_BUTTON;
    testButton7.Label = "Radio Button";
    testButton7.ButtonFlag = false;

    //==================================================
    // 8. 色ボタン
    //==================================================
    testButton8.ButtonType = IMGUI_BUTTON_TYPE::COLOR_BUTTON;
    testButton8.Label = "Color Button";
    testButton8.Color = ImVec4(1.0f, 0.2f, 0.2f, 1.0f);
    testButton8.Size = ImVec2(100.0f, 30.0f);
    testButton8.ImGuiEnumFlags = ImGuiColorEditFlags_None;

    //==================================================
    // 9. 選択可能項目
    //==================================================
    testButton9.ButtonType = IMGUI_BUTTON_TYPE::SELECTABLE;
    testButton9.Label = "Selectable Item";
    testButton9.ButtonFlag = false;
    testButton9.ImGuiEnumFlags = ImGuiSelectableFlags_None;

    //==================================================
    // 10. メニュー項目
    //==================================================
    testButton10.ButtonType = IMGUI_BUTTON_TYPE::MENU_ITEM;
    testButton10.Label = "Menu Item";
    testButton10.PressKeyString = "Ctrl+T";
    testButton10.DrawFlag = true;

    //==================================================
    // 11. タブバー内のボタン
    //==================================================
    testButton11.ButtonType = IMGUI_BUTTON_TYPE::TABITEM_BUTTON;
    testButton11.Label = "Tab Action";
    testButton11.ImGuiEnumFlags = ImGuiTabItemFlags_None;

    //==================================================
    // 12. テキストリンク
    //==================================================
    testButton12.ButtonType = IMGUI_BUTTON_TYPE::TEXT_LINK;
    testButton12.Label = "Text Link";

    //==================================================
    // 13. URLを開くテキストリンク
    //==================================================
    testButton13.ButtonType = IMGUI_BUTTON_TYPE::TEXT_LINK_OPEN_URL;
    testButton13.Label = "Open OpenAI Website";
    testButton13.Url = "https://openai.com/";
}
//==================================================
// ImguiManager ボタンテスト
//==================================================
void TestAllButtonImgui()
{
    //==================================================
    // 1. 標準ボタン
    //==================================================
    ImGui::Text(u8"1. BUTTON試し");
    Master::mpImguiManager->DrawButtonImgui(testButton1);
    ImGui::SameLine();
    ImGui::Text("Pressed: %s",
        testButton1.ArgumentButtonFlag ? "true" : "false");

    //==================================================
    // 2. 小型ボタン
    //==================================================
    ImGui::Text("2. SMALL_BUTTON");
    Master::mpImguiManager->DrawButtonImgui(testButton2);
    ImGui::SameLine();
    ImGui::Text("Pressed: %s",
        testButton2.ArgumentButtonFlag ? "true" : "false");

    //==================================================
    // 3. 矢印ボタン
    //==================================================
    ImGui::Text("3. ARROW_BUTTON");
    Master::mpImguiManager->DrawButtonImgui(testButton3);
    ImGui::SameLine();
    ImGui::Text("Pressed: %s",
        testButton3.ArgumentButtonFlag ? "true" : "false");

    //==================================================
    // 4. 透明ボタン
    //==================================================
    ImGui::Text("4. INVISIBLE_BUTTON");
    Master::mpImguiManager->DrawButtonImgui(testButton4);
    ImGui::SameLine();
    ImGui::Text("Pressed: %s",
        testButton4.ArgumentButtonFlag ? "true" : "false");

    //==================================================
    // 5. チェックボックス
    //==================================================
    ImGui::Text("5. CHECK_BOX");
    Master::mpImguiManager->DrawButtonImgui(testButton5);
    ImGui::SameLine();
    ImGui::Text("Changed: %s",
        testButton5.ArgumentButtonFlag ? "true" : "false");
    ImGui::SameLine();
    ImGui::Text("State: %s",
        testButton5.ButtonFlag ? "ON" : "OFF");

    //==================================================
    // 6. ビットフラグ用チェックボックス
    //==================================================
    ImGui::Text("6. CHECK_BOX_FLAGS");
    Master::mpImguiManager->DrawButtonImgui(testButton6);
    ImGui::SameLine();
    ImGui::Text("Flags: %u",
        testButton6.ButtonBitFlag.flags);

    //==================================================
    // 7. ラジオボタン
    //==================================================
    ImGui::Text("7. RADIO_BUTTON");
    Master::mpImguiManager->DrawButtonImgui(testButton7);
    ImGui::SameLine();
    ImGui::Text("Changed: %s",
        testButton7.ArgumentButtonFlag ? "true" : "false");

    //==================================================
    // 8. 色ボタン
    //==================================================
    ImGui::Text("8. COLOR_BUTTON");
    Master::mpImguiManager->DrawButtonImgui(testButton8);
    ImGui::SameLine();
    ImGui::Text("Pressed: %s",
        testButton8.ArgumentButtonFlag ? "true" : "false");

    //==================================================
    // 9. 選択可能項目
    //==================================================
    ImGui::Text("9. SELECTABLE");
    Master::mpImguiManager->DrawButtonImgui(testButton9);
    ImGui::SameLine();
    ImGui::Text("Selected: %s",
        testButton9.ButtonFlag ? "true" : "false");

    //==================================================
    // 10. メニュー項目
    //==================================================
    ImGui::Text("10. MENU_ITEM");
    if (ImGui::BeginMenu("Test Menu"))
    {
        Master::mpImguiManager->DrawButtonImgui(testButton10);
        ImGui::EndMenu();
    }
    ImGui::Text("Selected: %s",
        testButton10.ButtonFlag ? "true" : "false");

    //==================================================
    // 11. タブバー内のボタン
    //==================================================
    ImGui::Text("11. TABITEM_BUTTON");
    if (ImGui::BeginTabBar("TestTabBar"))
    {
        Master::mpImguiManager->DrawButtonImgui(testButton11);
        ImGui::SameLine();
        ImGui::Text("Pressed: %s",
            testButton11.ArgumentButtonFlag ? "true" : "false");

        ImGui::EndTabBar();
    }

    //==================================================
    // 12. テキストリンク
    //==================================================
    ImGui::Text("12. TEXT_LINK");
    Master::mpImguiManager->DrawButtonImgui(testButton12);
    ImGui::SameLine();
    ImGui::Text("Pressed: %s",
        testButton12.ArgumentButtonFlag ? "true" : "false");

    //==================================================
    // 13. URLを開くテキストリンク
    //==================================================
    ImGui::Text("13. TEXT_LINK_OPEN_URL");
    Master::mpImguiManager->DrawButtonImgui(testButton13);
}

// コンストラクタ
LightExecutor::LightExecutor(
    PuzzleGimmickActiveParam param,
    GameObject2D *parentObject,
    int lightAreaIndex,
    uint32_t lineCount,
    float baseAngle,
    float lightAngle,
    float lightLength,
    bool final2start) :
    mpParentObject(parentObject),
    mbLightOn(true),
    mbParamUpdate(false),
    mbFinal2Start(false),
    mnAreaIndex(lightAreaIndex),
    mnLineCount(lineCount),
    mfBaseAngle(baseAngle),
    mfLightAngle(lightAngle),
    mfLength(lightLength),
    BaseGimmickExecutor(param)
{
    InitializeTestAllButtonImgui();
    // 
    this->SetLightLineCount(lineCount);

    // 
    this->SetLength(this->mfLength);

    // 
    this->SetBaseAngle(this->mfBaseAngle);

    // 
    this->SetLightAngle(lightAngle);

    // 
    this->SetFinal2Start(final2start);

    // 
    this->UpdateLightParam();
}

// デストラクタ
LightExecutor::~LightExecutor()
{
}

// ギミックの内容を実行する関数
// ※GameObject::EarlyUpdate()のタイミングで呼ばれます
int LightExecutor::EarlyUpdate(bool triggerSignal)
{
    // 
    if (this->GetActiveParam().GetSignalNot())
    {
        // 
        triggerSignal = !triggerSignal;
    }

    // 
    if (!triggerSignal)
    {
        // 
        return 0;
    }

    // 
    return 0;
}
bool flag = false;
// ギミックの内容を実行する関数
// ※GameObject::Update()のタイミングで呼ばれます
int LightExecutor::Update(bool triggerSignal)
{
    if (!flag)
    {
        TestAllButtonImgui();
        flag = true;
    }
    // 
    if (this->GetActiveParam().GetSignalNot())
    {
        // 
        triggerSignal = !triggerSignal;
    }

    // 
    this->mbLightOn = triggerSignal;

    // 
    return 0;
}

// ギミックの内容を実行する関数
// ※GameObject::LateUpdate()のタイミングで呼ばれます
int LightExecutor::LateUpdate(bool triggerSignal)
{
    flag = false;
    // 
    if (this->mbLightOn)
    {
        // 
        this->GetMyLightArea()->OnLight();

        // 
        this->UpdateLightParam();

        // 
        this->CalculateLineEndPos();
    }
    else
    {
        // 
        this->GetMyLightArea()->OffLight();
    }

    // 
    return 0;
}

// シミュレーション内容を描画する関数
// ※既に実行段階である場合は引数がtrueになります。実行段階では描画しない、あるいはその逆の場合はこの引数を使ってください。
int LightExecutor::Draw(bool triggerSignal)
{
    // 
    if (!this->mbLightOn)
    {
        // 光域のシミュレーターは描画はしません
        return 0;
    }

    // 
    size_t firstIndex = 0;
    size_t secondIndex = 0;

    // 
    LightArea *lightArea = Master::mpLightManager->SearchArea(this->mnAreaIndex);
    LightLineNode *currentNode;
    LightLineNode *nextNode;

    // 
    auto nodeBox = lightArea->GetFirstNodeBox();

    // 
    int drawResult = 0;

    // 
    VECTOR2D baseStartPos = lightArea->GetStartPosition();

    // 
    int drawMode = 0;

    if (drawMode == 0)
    {
        // 
        for (uint32_t i = 0; i < lightArea->GetLightLineCount(); i++)
        {
            // 
            currentNode = lightArea->GetFirstNodeBox()[i];

            // 
            if (currentNode == nullptr)
            {
                // 
                continue;
            }

            // 
            while (true)
            {
                // 
                if (currentNode == lightArea->GetFirstNodeBox()[i] &&
                    !currentNode->CheckNext())
                {
                    // 
                    // break;
                }

                // デバッグ用レイの可視化
                //drawResult = DxLib::DrawLine(
                //    currentNode->GetMyStartPos().GetX(),
                //    currentNode->GetMyStartPos().GetY(),
                //    currentNode->GetMyEndPos().GetX(),
                //    currentNode->GetMyEndPos().GetY(),
                //    0x00ffff);

                // 
                if (!currentNode->AccessNext(&nextNode))
                {
                    // 
                    break;
                }

                // 
                currentNode = nextNode;
            }
        }
    }
    else if (drawMode == 1)
    {

        // 
        for (uint32_t i = 0; i < lightArea->GetLightLineCount() - 1; i++)
        {
            // 
            drawResult = DxLib::DrawTriangle(
                baseStartPos.GetX(),
                baseStartPos.GetY(),
                nodeBox[i]->GetMyEndPos().GetX(),
                nodeBox[i]->GetMyEndPos().GetY(),
                nodeBox[i + 1]->GetMyEndPos().GetX(),
                nodeBox[i + 1]->GetMyEndPos().GetY(),
                0x00ffff,
                false);

            // 
            if (drawResult != 0)
            {
                // 
                break;
            }
        }

        // 
        if (drawResult != 0)
        {
            // 
            return drawResult;
        }

        // 
        firstIndex = 0;

        // 
        bool loopFlag = true;

        // 
        LightLineNode *firstNode = nullptr;
        LightLineNode *firstNodeNext = nullptr;
        LightLineNode *secondNode = nullptr;
        LightLineNode *secondNodeNext = nullptr;

        // 
        for (size_t i = 0; i < lightArea->GetLightLineCount() - 1; i++)
        {
            // 
            firstNode = nodeBox[i];
            secondNode = nodeBox[i + 1];

            // 
            loopFlag = true;

            // 
            while (loopFlag)
            {
                // 
                firstNode->AccessNext(&firstNodeNext);
                secondNode->AccessNext(&secondNodeNext);

                // 
                if (firstNodeNext != nullptr && secondNodeNext != nullptr)
                {
                    // 
                    drawResult = DxLib::DrawQuadrangle(
                        firstNode->GetMyEndPos().GetX(),
                        firstNode->GetMyEndPos().GetY(),
                        secondNode->GetMyEndPos().GetX(),
                        secondNode->GetMyEndPos().GetY(),
                        firstNodeNext->GetMyEndPos().GetX(),
                        firstNodeNext->GetMyEndPos().GetY(),
                        secondNodeNext->GetMyEndPos().GetX(),
                        secondNodeNext->GetMyEndPos().GetY(),
                        0x00ffff,
                        true);

                    // 
                    firstNode = firstNodeNext;
                    secondNode = secondNodeNext;
                }
                else if (firstNodeNext != nullptr && secondNodeNext == nullptr)
                {
                    // 
                    drawResult = DxLib::DrawTriangle(
                        firstNode->GetMyEndPos().GetX(),
                        firstNode->GetMyEndPos().GetY(),
                        secondNode->GetMyEndPos().GetX(),
                        secondNode->GetMyEndPos().GetY(),
                        firstNodeNext->GetMyEndPos().GetX(),
                        firstNodeNext->GetMyEndPos().GetY(),
                        0x00ffff,
                        true);

                    // 
                    loopFlag = false;
                }
                else if (firstNodeNext == nullptr && secondNodeNext != nullptr)
                {
                    // 
                    drawResult = DxLib::DrawTriangle(
                        firstNode->GetMyEndPos().GetX(),
                        firstNode->GetMyEndPos().GetY(),
                        secondNode->GetMyEndPos().GetX(),
                        secondNode->GetMyEndPos().GetY(),
                        secondNodeNext->GetMyEndPos().GetX(),
                        secondNodeNext->GetMyEndPos().GetY(),
                        0x00ffff,
                        true);

                    // 
                    loopFlag = false;
                }
                else
                {
                    // 
                    loopFlag = false;
                }
            }

            // 
            if (drawResult != 0)
            {
                // 
                break;
            }
        }
    }
    else if (drawMode == 2)
    {
        // 
        currentNode = nodeBox[gnDebugTest];

        // 
        while (true)
        {
            // 
            drawResult = DxLib::DrawLine(
                currentNode->GetMyStartPos().GetX(),
                currentNode->GetMyStartPos().GetY(),
                currentNode->GetMyEndPos().GetX(),
                currentNode->GetMyEndPos().GetY(),
                0x00ffff);

            // 
            if (currentNode->AccessNext(&nextNode))
            {
                // 
                currentNode = nextNode;
            }
            else
            {
                // 
                break;
            }
        }

        // 
        gnDebugTest++;

        // 
        gnDebugTest %= lightArea->GetLightLineCount();
    }

    // 
    return 0;
}

// このライトの光域を計算する関数
bool LightExecutor::CalculateLineEndPos()
{
    // 
    std::vector<BaseCollision2D *> objectCollisionBox;

    // 
    BaseScene *nowScene = Master::mpBaseSceneManager->SearchSceneNow();
    if (nowScene->GetBaseCollision2DManager()->SearchTag(CollisionTag::CollisionTag_Wall, objectCollisionBox) != 0)
    {
        // 
        return false;
    }

    // 
    std::vector<BaseCollision2D *> mirrorCollisionBox;
    if (nowScene->GetBaseCollision2DManager()->SearchTag(CollisionTag::CollisionTag_Mirror, mirrorCollisionBox) != 0)
    {
        // 
        return false;
    }

    // 
    Ray2D tempRay;

    // 
    CollisionCheckResult2D resultCurrent = GetCollisionCheckResult2DZero();

    // 
    CollisionCheckResult2D resultNewr = GetCollisionCheckResult2DZero();

    // 
    return this->GetMyLightArea()->CalculateNode(
        this->mfBaseAngle,
        this->mfLength,
        objectCollisionBox,
        mirrorCollisionBox,
        tempRay,
        resultCurrent,
        resultNewr);
}

// このライトのレイの本数を取得する関数
uint32_t LightExecutor::GetLightLineCount() const
{
    // 
    return this->GetMyLightArea()->GetLightLineCount();
}

// このライトの長さを取得する関数
float LightExecutor::GetLength() const
{
    // 
    return this->mfLength;
}

// このライトのレイの本数を設定する関数
void LightExecutor::SetLightLineCount(uint32_t count)
{
    // 
    this->mnLineCount = count;

    // 
    this->mbParamUpdate = true;
}

// このライトの長さを設定する関数
void LightExecutor::SetLength(float length)
{
    this->mfLength = length;

    // 
    this->mbParamUpdate = true;
}

// このライトの基本角度を設定する関数
void LightExecutor::SetBaseAngle(float radian)
{
    // 
    this->mfBaseAngle = radian;

    // 
    this->mbParamUpdate = true;
}

// このライトの全体の角度を設定する関数
void LightExecutor::SetLightAngle(float radian)
{
    this->mfLightAngle = radian;

    // 
    this->mbParamUpdate = true;
}

// 最後の線から最初の線の計算を行う関数
void LightExecutor::SetFinal2Start(bool flag)
{
    // 
    this->mbFinal2Start = flag;

    // 
    this->mbParamUpdate = true;
}

// 
LightArea *LightExecutor::GetMyLightArea() const
{
    // 
    return Master::mpLightManager->SearchArea(this->mnAreaIndex);
}

// 
bool LightExecutor::UpdateLightParam()
{
    // 
    if (this->mbParamUpdate)
    {
        // 
        this->GetMyLightArea()->SetParam(
            this->mpParentObject,
            this->mnLineCount,
            this->mfBaseAngle,
            this->mfLightAngle,
            this->mbFinal2Start);

        // 
        this->mbParamUpdate = false;
    }

    // 
    return true;
}
