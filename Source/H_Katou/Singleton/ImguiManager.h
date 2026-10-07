#pragma once
#include <string>
#include <vector>

#include "ImguiData.h"

// TODO:_ 最終的にはプロジェクトから外す

// TODO:_ 一時追加用をグループ作成する

class ImguiManager
{
private:
    // 登録中グループ関連の情報
    struct CURRENT_GROUP_TYPE_DATA
    {
        // 参照しているグループ種類
        IMGUI_GROUP_TYPE CurrentGroupType = IMGUI_GROUP_TYPE::NONE;

        // 参照しているグループまでの添え字
        std::vector<int> CurrentGroupTypeIndexs;
    };
private:
    // IMGUIデータ float
    std::vector<IMGUI_FLOAT_DATA> mstImguiFloatDatas;

    // IMGUIデータ int
    std::vector<IMGUI_INT_DATA> mstImguiIntDatas;

    // IMGUIグループデータ
    std::vector<IMGUI_GROUP_DATA> mstImguiGroupDatas;
    
    // 現在登録中のグループ関連情報
    CURRENT_GROUP_TYPE_DATA mstCurrentGroupTypeData;

    // 追加Imguiナンバー
    int mnAddNumber;

    // imgui実行フラグ
    bool mbIsImguiExecute;
public:

    ImguiManager(bool isImguiExecute);
    ~ImguiManager();

    /// <summary>初期化</summary>
    void Initilize();
    /// <summary>終了</summary>
    void Finalize();

    /// <summary>更新</summary>
    void Update();
    /// <summary>描画</summary>
    void Draw();

    /// <summary>Imgui追加描画</summary>
    void AddDrawImgui(IMGUI_FLOAT_DATA imguiFloatData);
    /// <summary>Imgui追加描画</summary>
    void AddDrawImgui(IMGUI_INT_DATA imguiIntData);

    /// <summary>Imguiグループ追加描画(全部)</summary>
    void AddDrawImguiGroup(IMGUI_GROUP_DATA imguiGroupData);
    /// <summary>Imguiグループ追加描画(float)</summary>
    void AddDrawImguiGroup(IMGUI_FLOAT_DATA imguiFloatData, IMGUI_GROUP_TYPE groupType, std::string groupName = "NEW_GROUP");
    /// <summary>Imguiグループ追加描画(int)</summary>
    void AddDrawImguiGroup(IMGUI_INT_DATA imguiIntData, IMGUI_GROUP_TYPE groupType, std::string groupName = "NEW_GROUP");
    /// <summary>Imguiグループ追加描画(参照int情報) ※StartGroupを読んでから使用してください</summary>
    void AddDrawImguiGroup(IMGUI_FLOAT_DATA imguiFloatData);
    /// <summary>Imguiグループ追加描画(参照float情報)</summary>
    void AddDrawImguiGroup(IMGUI_INT_DATA imguiIntData);

    /// <summary>Imguiグループ参照先設定開始 ※設定が終わったらEndGroupを読んでください</summary>
    void StartGroup(IMGUI_GROUP_TYPE groupType, std::string groupName = "NEW_GROUP");
    /// <summary>Imguiグループ参照先設定終了</summary>
    void EndGroup();

    /// <summary>Imguiグループを新しく作成</summary>
    /// <param name="parentGroupType">NONEなら最上位に、違うなら探して子供として作成</param>
    void CreateImguiGroup(IMGUI_GROUP_TYPE groupType, std::string groupName, IMGUI_GROUP_TYPE parentGroupType = IMGUI_GROUP_TYPE::NONE);

    /// <summary>Imguiグループを移動</summary>
    /// <param name="parentGroupType">NONEなら最上位に、違うなら探して子供として移動</param>
    void MoveImguiGroup(IMGUI_GROUP_TYPE groupType, IMGUI_GROUP_TYPE parentGroupType);

    /// <summary>Imguiグループを削除</summary>
    void DeleteImguiGroup(IMGUI_GROUP_TYPE groupType);

    /// <summary>WndProcでやるImguiの処理</summary>
    void ImguiWndProcProcess(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

private:
    /*floatのImguui描画*/
    void DrawFloatImgui(IMGUI_FLOAT_DATA imguiFloatData);

    /*intのImguui描画*/
    void DrawIntImgui(IMGUI_INT_DATA imguiIntData);

    /*Imguiグループ描画*/
    void DrawGroupImgui(IMGUI_GROUP_DATA imguiGroupData);

    /*グループ種類からグループを検索*/
    CURRENT_GROUP_TYPE_DATA SearchImguiGroupData(IMGUI_GROUP_TYPE groupType, IMGUI_GROUP_DATA** imguiGroupData);

    /*現在参照しているグループを取得*/
    IMGUI_GROUP_DATA* GetCurrentGroupData();
};
/*
構造体作成
const char* label, float* v, float v_min, float v_max, const char* format, ImGuiSliderFlags flags
const char* label, float v[2], float v_min, float v_max, const char* format, ImGuiSliderFlags flags
const char* label, float v[3], float v_min, float v_max, const char* format, ImGuiSliderFlags flags
const char* label, float v[4], float v_min, float v_max, const char* format, ImGuiSliderFlags flags
const char* label, float* v_rad, float v_degrees_min, float v_degrees_max, const char* format, ImGuiSliderFlags flags
const char* label, float* v, float v_speed, float v_min, float v_max, const char* format, ImGuiSliderFlags flags
*/

/*使用例 1(float)
    Master::mpImguiManager->AddDrawImgui(IMGUI_FLOAT_DATA::GetImguiData(
        { &testSize },
        0.1f,
        0.1f,
        0.1f,
        0.0f,
        250.0f,
        "TEST_SIZE_BACK_",
        "%f",
        0,
        IMGUI_TYPE::SLIDER1
    )
    );
*/
/*使用例 2(int)
    Master::mpImguiManager->AddDrawImgui(IMGUI_INT_DATA::GetImguiData(
                                                                     { &mstMiniMapDrawGraphData[0].pos.x, &mstMiniMapDrawGraphData[0].pos.y, &mstMiniMapDrawGraphData[0].size.x, &mstMiniMapDrawGraphData[0].size.y },
                                                                     1.0f,
                                                                     1.0f,
                                                                     1.0f,
                                                                     0,
                                                                     1000,
                                                                     "NONE_",
                                                                     "%d",
                                                                     0,
                                                                     IMGUI_TYPE::SLIDER4
                                                                    )
                                        );

*/