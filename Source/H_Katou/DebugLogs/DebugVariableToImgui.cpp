// #include "DebugVariableToImgui.h"

// #include <map>
// #include <string>

// #include "Master.h"
// #include "Singleton/ImguiManager.h"

// // DebugVariableToImgui の内部処理を定義します。
// // ImGui の設定編集や DX 描画の実体をここに配置しています。
// namespace DebugVariableToImgui
// {
//     namespace PrivateVariable
//     {
//         std::vector<Entry>& GetEntries()
//         {
//             static std::vector<Entry> entries;
//             return entries;
//         }

//         void AddEntry(Entry entry)
//         {
//             GetEntries().push_back(std::move(entry));
//         }

//         void RemoveEntry(const std::string& key)
//         {
//             auto& entries = GetEntries();
//             entries.erase(std::remove_if(entries.begin(), entries.end(), [&key](const Entry& entry)
//             {
//                 return entry.key == key;
//             }), entries.end());
//         }

//         bool HasEntry(const std::string& key)
//         {
//             const auto& entries = GetEntries();
//             return std::any_of(entries.begin(), entries.end(), [&key](const Entry& entry)
//             {
//                 return entry.key == key;
//             });
//         }
//     }

//     namespace PrivateDetail
//     {
//         // DrawType を文字列に変換するための補助関数です。
//         // ImGui のツリーノードやデバッグ表示に使います。
//         const char* GetDrawTypeName(DrawType type)
//         {
//             switch (type)
//             {
//             case DrawType_Point: return "Point";
//             case DrawType_Line: return "Line";
//             case DrawType_Circle: return "Circle";
//             case DrawType_Rectangle: return "Rectangle";
//             case DrawType_Text: return "Text";
//             case DrawType_FillCircle: return "FillCircle";
//             case DrawType_FillRectangle: return "FillRectangle";
//             default: return "Unknown";
//             }
//         }

//         // 32bit の RGB 値を ImGui の ColorEdit4 の float[4] 形式に変換します。
//         // 0.0f ～ 1.0f に正規化した値にして、UI と DX 描画の両方で扱いやすくします。
//         inline void ColorIntToFloatArray(int color, float out[4])
//         {
//             const int r = (color >> 16) & 0xff;
//             const int g = (color >> 8) & 0xff;
//             const int b = color & 0xff;
//             out[0] = static_cast<float>(r) / 255.0f;
//             out[1] = static_cast<float>(g) / 255.0f;
//             out[2] = static_cast<float>(b) / 255.0f;
//             out[3] = 1.0f;
//         }

//         // ImGui 側の float[4] 色データを DXLib の描画用色に変換します。
//         // 各値は 0.0 ～ 1.0 の範囲で扱い、ARRGGBB の形式に変換します。
//         inline int ColorFloatArrayToInt(const float value[4])
//         {
//             const int r = static_cast<int>(value[0] * 255.0f + 0.5f);
//             const int g = static_cast<int>(value[1] * 255.0f + 0.5f);
//             const int b = static_cast<int>(value[2] * 255.0f + 0.5f);
//             return (r << 16) | (g << 8) | b;
//         }

//         // Entry の設定を ImGui で編集可能な形に変換して表示します。
//         // Visible / Basic Enable / Type Enable / Element Enable をまとめて編集します。
//         void DrawEntrySettingEditor(PrivateVariable::Entry& entry)
//         {
//             if (!entry.drawState || entry.drawState->settings.empty())
//             {
//                 return;
//             }

//             if (!ImGui::CollapsingHeader(entry.label.c_str(), nullptr, ImGuiTreeNodeFlags_None))
//             {
//                 return;
//             }

//             DrawSetting& activeSetting = entry.drawState->settings.front();
//             bool visible = activeSetting.enabled;
//             if (ImGui::Checkbox("Visible", &visible))
//             {
//                 activeSetting.enabled = visible;
//                 for (auto& setting : entry.drawState->settings)
//                 {
//                     setting.enabled = visible;
//                 }
//             }

//             ImGui::Checkbox("Basic Enable", &activeSetting.basicEnabled);
//             ImGui::Checkbox("Type Enable", &activeSetting.typeEnabled);
//             ImGui::Checkbox("Element Enable", &activeSetting.elementEnabled);

//             for (size_t i = 0; i < entry.drawState->settings.size(); ++i)
//             {
//                 DrawSetting& setting = entry.drawState->settings[i];
//                 const std::string id = entry.label + "_" + std::to_string(i);
//                 if (ImGui::TreeNode((id + " / " + GetDrawTypeName(setting.type)).c_str()))
//                 {
//                     float colorValue[4] = {};
//                     ColorIntToFloatArray(setting.color, colorValue);
//                     if (ImGui::ColorEdit4("Color", colorValue, ImGuiColorEditFlags_AlphaPreviewHalf))
//                     {
//                         setting.color = ColorFloatArrayToInt(colorValue);
//                     }

//                     bool settingVisible = setting.enabled;
//                     if (ImGui::Checkbox("Visible", &settingVisible))
//                     {
//                         setting.enabled = settingVisible;
//                     }
//                     ImGui::SameLine();
//                     ImGui::Checkbox("Fill", &setting.fill);

//                     ImGui::DragFloat("X", &setting.x, 1.0f, -2000.0f, 2000.0f);
//                     ImGui::DragFloat("Y", &setting.y, 1.0f, -2000.0f, 2000.0f);
//                     ImGui::DragFloat("Width", &setting.width, 1.0f, 0.0f, 2000.0f);
//                     ImGui::DragFloat("Height", &setting.height, 1.0f, 0.0f, 2000.0f);
//                     ImGui::DragFloat("Radius", &setting.radius, 1.0f, 0.0f, 2000.0f);
//                     ImGui::DragInt("Thickness", &setting.thickness, 0.5f, 1, 32);

//                     ImGui::TreePop();
//                 }
//             }

//             entry.drawSetting = activeSetting;
//             entry.drawSettings = entry.drawState->settings;
//         }

//         // 指定した DrawType に対応するエントリだけを画面に表示します。
//         // Basic と Type の有効 / 無効に応じて表示対象を切り替えます。
//         void DrawTypeTab(DrawType targetType)
//         {
//             auto& entries = PrivateVariable::GetEntries();
//             bool any = false;
//             for (auto& entry : entries)
//             {
//                 if (!entry.drawState || entry.drawState->settings.empty())
//                 {
//                     continue;
//                 }

//                 const bool containsType = std::any_of(entry.drawState->settings.begin(), entry.drawState->settings.end(), [targetType](const DrawSetting& s)
//                 {
//                     return s.type == targetType;
//                 });

//                 if (!containsType)
//                 {
//                     continue;
//                 }

//                 any = true;
//                 DrawEntrySettingEditor(entry);
//             }

//             if (!any)
//             {
//                 ImGui::TextUnformatted("No entries for this type.");
//             }
//         }
//     }

//     void Update()
//     {
//         auto& entries = PrivateVariable::GetEntries();
//         for (auto& entry : entries)
//         {
//             if (entry.updateImgui)
//             {
//                 entry.updateImgui();
//             }
//         }
//     }

//     void Draw()
//     {
//         auto& entries = PrivateVariable::GetEntries();
//         for (auto& entry : entries)
//         {
//             if (entry.drawDx)
//             {
//                 entry.drawDx();
//             }
//         }
//     }

//     void SetBasicEnabled(const std::string& key, bool enabled)
//     {
//         auto& entries = PrivateVariable::GetEntries();
//         const auto it = std::find_if(entries.begin(), entries.end(), [&key](const PrivateVariable::Entry& entry)
//         {
//             return entry.key == key;
//         });

//         if (it == entries.end())
//         {
//             return;
//         }

//         it->basicEnabled = enabled;
//         if (it->drawState)
//         {
//             for (auto& setting : it->drawState->settings)
//             {
//                 setting.basicEnabled = enabled;
//             }
//         }
//     }

//     void SetTypeEnabled(const std::string& key, DrawType type, bool enabled)
//     {
//         auto& entries = PrivateVariable::GetEntries();
//         const auto it = std::find_if(entries.begin(), entries.end(), [&key](const PrivateVariable::Entry& entry)
//         {
//             return entry.key == key;
//         });

//         if (it == entries.end())
//         {
//             return;
//         }

//         it->typeEnabled = enabled;
//         if (it->drawState)
//         {
//             for (auto& setting : it->drawState->settings)
//             {
//                 if (setting.type == type)
//                 {
//                     setting.typeEnabled = enabled;
//                 }
//             }
//         }
//     }

//     void SetElementEnabled(const std::string& key, bool enabled, size_t elementIndex)
//     {
//         auto& entries = PrivateVariable::GetEntries();
//         const auto it = std::find_if(entries.begin(), entries.end(), [&key](const PrivateVariable::Entry& entry)
//         {
//             return entry.key == key;
//         });

//         if (it == entries.end() || !it->drawState || elementIndex >= it->drawState->settings.size())
//         {
//             return;
//         }

//         it->drawState->settings[elementIndex].elementEnabled = enabled;
//     }

//     void SetDefaultDrawSetting(const std::string& key, const DrawSetting& setting)
//     {
//         auto& entries = PrivateVariable::GetEntries();
//         const auto it = std::find_if(entries.begin(), entries.end(), [&key](const PrivateVariable::Entry& entry)
//         {
//             return entry.key == key;
//         });

//         if (it == entries.end() || !it->drawState)
//         {
//             return;
//         }

//         it->drawState->mainSetting = setting;
//         it->drawState->settings.assign(1, setting);
//         it->drawSetting = setting;
//         it->drawSettings = it->drawState->settings;
//     }

//     void SetDrawColor(const std::string& key, int color)
//     {
//         auto& entries = PrivateVariable::GetEntries();
//         const auto it = std::find_if(entries.begin(), entries.end(), [&key](const PrivateVariable::Entry& entry)
//         {
//             return entry.key == key;
//         });

//         if (it == entries.end() || !it->drawState)
//         {
//             return;
//         }

//         for (auto& setting : it->drawState->settings)
//         {
//             setting.color = color;
//         }
//     }

//     void SetDrawType(const std::string& key, DrawType type)
//     {
//         auto& entries = PrivateVariable::GetEntries();
//         const auto it = std::find_if(entries.begin(), entries.end(), [&key](const PrivateVariable::Entry& entry)
//         {
//             return entry.key == key;
//         });

//         if (it == entries.end() || !it->drawState)
//         {
//             return;
//         }

//         for (auto& setting : it->drawState->settings)
//         {
//             setting.type = type;
//         }
//     }

//     namespace PrivateFunction
//     {
//         template <typename T>
//         struct VariableControlFactory
//         {
//             static IMGUI_VARIABLE_CONTROL Create(const std::string& label, T& value, float step, float stepFast, T min, T max, const char* format, IMGUI_TYPE type)
//             {
//                 std::vector<T*> variableDatas;
//                 variableDatas.push_back(&value);

//                 return IMGUI_VARIABLE_CONTROL::GetImguiData(
//                     variableDatas,
//                     1.0f,
//                     step,
//                     stepFast,
//                     min,
//                     max,
//                     label,
//                     format,
//                     0,
//                     type,
//                     false);
//             }
//         };

//         template <>
//         struct VariableControlFactory<double>
//         {
//             static IMGUI_VARIABLE_CONTROL Create(const std::string& label, double& value, float step, float stepFast, double min, double max, const char* format, IMGUI_TYPE type)
//             {
//                 std::vector<IMGUI_VARIABLE_POITER_DATA> variableDatas;
//                 variableDatas.emplace_back(&value, IMGUI_VARIABLE_TYPE::DOUBLE);

//                 return IMGUI_VARIABLE_CONTROL::GetImguiData(
//                     variableDatas,
//                     1.0f,
//                     step,
//                     stepFast,
//                     label,
//                     format,
//                     0,
//                     type,
//                     false);
//             }
//         };

//         // ImGui の値を Master::mpImguiManager に登録して、
//         // そのまま画面上でスライダーや入力欄として編集できるようにします。
//         template <typename T>
//         void RegisterManagerVariable(const std::string& label, T& value, float step, float stepFast, T min, T max, const char* format, IMGUI_TYPE type)
//         {
// #ifdef _DEBUG
//             if (Master::mpImguiManager == nullptr)
//             {
//                 return;
//             }

//             const IMGUI_VARIABLE_CONTROL ctrl = VariableControlFactory<T>::Create(label, value, step, stepFast, min, max, format, type);
//             Master::mpImguiManager->AddDrawImgui(ctrl, "DebugVariableToImgui");
// #endif
//         }

//         // int 型の変数を ImGui のスライダー形式で登録します。
//         void RegisterImguiInt(const std::string& label, int& value, int min, int max)
//         {
// #ifdef _DEBUG
//             RegisterManagerVariable<int>(label, value, 1.0f, 1.0f, min, max, "%d", IMGUI_TYPE::SLIDER1);
// #endif
//         }

//         // float 型の変数を ImGui のスライダー形式で登録します。
//         void RegisterImguiFloat(const std::string& label, float& value, float min, float max)
//         {
// #ifdef _DEBUG
//             RegisterManagerVariable<float>(label, value, 0.1f, 0.1f, min, max, "%.2f", IMGUI_TYPE::SLIDER1);
// #endif
//         }

//         // double 型の変数を ImGui のスライダー形式で登録します。
//         void RegisterImguiDouble(const std::string& label, double& value, double min, double max)
//         {
// #ifdef _DEBUG
//             RegisterManagerVariable<double>(label, value, 0.1f, 0.1f, min, max, "%.2f", IMGUI_TYPE::SLIDER1);
// #endif
//         }
//     }
// }