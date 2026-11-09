#pragma once

#include <algorithm>
#include <array>
#include <cmath>
#include <functional>
#include <memory>
#include <string>
#include <type_traits>
#include <vector>

#include "ImguiData.h"

// DebugVariableToImgui
// 変数の値を ImGui の表示と DX ライブラリの描画の両方に同期させるための
// 補助機構を提供する。公開 API はこの名前空間直下に置き、内部処理は
// PrivateVariable / PrivateFunction に分離して管理する。
namespace DebugVariableToImgui
{
    namespace PrivateConstFunction
    {
        // IsSupportedVariableType は、デバッグ表示に対応する変数型かどうかを判定する。
        template <typename T>
        constexpr bool IsSupportedVariableType()
        {
            return
                std::is_same<T, char>::value ||
                std::is_same<T, unsigned char>::value ||
                std::is_same<T, short>::value ||
                std::is_same<T, unsigned short>::value ||
                std::is_same<T, int>::value ||
                std::is_same<T, unsigned int>::value ||
                std::is_same<T, long>::value ||
                std::is_same<T, unsigned long>::value ||
                std::is_same<T, long long>::value ||
                std::is_same<T, unsigned long long>::value ||
                std::is_same<T, float>::value ||
                std::is_same<T, double>::value ||
                std::is_same<T, long double>::value;
        }
    }
    using namespace PrivateConstFunction;

    struct StructMemberIndexData;
    namespace PrivateEnum
    {
        // ImGui の操作設定を管理する列挙型。
        // 色、サイズ、位置などの描画設定を識別する。
    
        enum class DEBUG_VAR_DRAW_IMGUI_SETTING_TYPE
        {
            IMGUI_OPERATION_NONE = -1,

            IMGUI_OPERATION_COLOR,

            IMGUI_OPERATION_SIZE,
            IMGUI_OPERATION_WIDTH,
            IMGUI_OPERATION_HEIGHT,
            
            IMGUI_OPERATION_RADIUS,
            
            IMGUI_OPERATION_POS,
            IMGUI_OPERATION_POS_X,
            IMGUI_OPERATION_POS_Y,
            
            IMGUI_OPERATION_LEFT_POS,
            IMGUI_OPERATION_LEFT_POS_X,
            IMGUI_OPERATION_LEFT_POS_Y,

            IMGUI_OPERATION_RIGHT_POS,
            IMGUI_OPERATION_RIGHT_POS_X,
            IMGUI_OPERATION_RIGHT_POS_Y,
        };

        // 変更元の識別
        enum class VARIABLE_CHANGE_SOURCE
        {
            POINTER,       // ① 実際の変数
            DRAW_SETTING,  // ② DrawSetting
            IMGUI_VALUE,   // ③ ImGuiに渡す値

            MAX
        };
    }
    
    // DX 描画の種類を管理する列挙型。
    // 点、線、円、矩形、テキストなどの描画形式を識別する。
    enum class DEBUG_VAR_DRAW_TYPE
    {
        DRAW_TYPE_NONE = -1,
        DRAW_TYPE_POINT,
        DRAW_TYPE_LINE,
        DRAW_TYPE_CIRCLE,
        DRAW_TYPE_RECTANGLE,
        DRAW_TYPE_TEXT,
        DRAW_TYPE_FILL_CIRCLE,
        DRAW_TYPE_FILL_RECTANGLE
    };

    using namespace PrivateEnum;
    namespace PrivateStruct
    {
        struct DrawSetting
        {
            DEBUG_VAR_DRAW_TYPE type;
            int color;
            float radius;
            float width;
            float height;
            float PosX;
            float PosY;
            float leftX;
            float leftY;
            float rightX;
            float rightY;
            bool fill;
            std::string label;
            std::string text;
            bool enabled;
            bool basicEnabled;
            bool typeEnabled;
            bool elementEnabled;

            DrawSetting()
            : type(DEBUG_VAR_DRAW_TYPE::DRAW_TYPE_NONE)
            , color(0xffffff)
            , radius(8.0f)
            , width(16.0f)
            , height(16.0f)
            , PosX(0.0f)
            , PosY(0.0f)
            , leftX(0.0f)
            , leftY(0.0f)
            , rightX(0.0f)
            , rightY(0.0f)
            , fill(false)
            , label()
            , text()
            , enabled(true)
            , basicEnabled(true)
            , typeEnabled(true)
            , elementEnabled(true)
            {
            }

            DrawSetting(DEBUG_VAR_DRAW_TYPE typeValue, int colorValue, float radiusValue, float widthValue, float heightValue, float xValue, float yValue, bool fillValue, const std::string& labelValue, const std::string& textValue, bool enabledValue)
            : type(typeValue)
            , color(colorValue)
            , radius(radiusValue)
            , width(widthValue)
            , height(heightValue)
            , PosX(xValue)
            , PosY(yValue)
            , leftX(xValue)
            , leftY(yValue)
            , rightX(xValue + widthValue)
            , rightY(yValue + heightValue)
            , fill(fillValue)
            , label(labelValue)
            , text(textValue)
            , enabled(enabledValue)
            , basicEnabled(true)
            , typeEnabled(true)
            , elementEnabled(true)
            {
            }

            bool IsVisible() const
            {
                return basicEnabled && typeEnabled && elementEnabled && enabled;
            }
        };

        // imgui の操作設定を管理する構造体。
        struct ImguiOperationSetting
        {
            DEBUG_VAR_DRAW_IMGUI_SETTING_TYPE type;
            std::vector<StructMemberIndexData> memberData;
            DrawSetting drawSetting;
        };


        struct DebugOneVariableData
        {
            std::string TabName;
            void* Variable;

            std::vector<ImguiOperationSetting> MemberData;
        };

        struct DebugVariableData
        {
            std::string TabName;
            std::vector<void>* Variable;

            std::vector<ImguiOperationSetting> MemberData;
        };
    }
        
    
    // StructMemberIndexData は構造体のメンバ変数をデバッグ表示用に束ねる情報を持つ。
    // 例: position.x のような階層メンバも、名前とポインタの組み合わせで1つのデバッグ項目として扱える。
    struct StructMemberIndexData
    {
        std::string Name;
        std::function<void*(void*)> GetPointer;

        
        template <typename MemberType>
        MemberType* GetMemberPointer(void* objectPtr) const
        {
            return static_cast<MemberType*>(GetPointer(objectPtr));
        }
    };

    using namespace PrivateStruct;

    namespace PrivateVariable
    {
        // デバッグ変数の情報を保持する変数(一時的に保持)
        // デバッグ変数の情報を保持する変数(削除指示があるまで保持)

        // 描画のみ情報を持つ
    }
    namespace PrivateFunction
    {
        // 更新
        void Update();
        // 描画
        void Draw();

        // MakeDefaultDrawSetting は標準の描画設定をまとめて生成するヘルパー。
        // DX 描画と ImGui の両方で共通の初期値として使うための関数。
        inline DrawSetting MakeDrawSetting(
            DEBUG_VAR_DRAW_TYPE typeValue = DEBUG_VAR_DRAW_TYPE::DRAW_TYPE_NONE,
            int colorValue = 0xffffff,
            int thicknessValue = 1,
            float radiusValue = 8.0f,
            float widthValue = 16.0f,
            float heightValue = 16.0f,
            float xValue = 0.0f,
            float yValue = 0.0f,
            bool fillValue = false,
            const std::string& labelValue = std::string(),
            const std::string& textValue = std::string(),
            bool enabledValue = true);
    }
    using namespace PrivateFunction;

    template <typename T, typename MemberType>
    StructMemberIndexData MakeMemberData(const std::string& nameValue, MemberType T::* member)
    {
        static_assert(
            IsSupportedVariableType<MemberType>(),
            "登録されたメンバ変数は正常に稼働できない型です。"
        );

        return
        {
            nameValue,
            [member](void* objectPtr) -> void*
            {
                T* object = static_cast<T*>(objectPtr);
                return &(object->*member);
            }
        };
    }

    // 最後のメンバーへのアクセス
    template <typename T, typename MemberType>
    MemberType* GetMemberPointer(T* object, MemberType T::* member)
    {
        static_assert(
            IsSupportedVariableType<MemberType>(),
            "登録されたメンバ変数は正常に稼働できない型です。"
        );

        return &(object->*member);
    }

    // 階層メンバーへのアクセス
    template <typename T, typename ParentType, typename MemberType, typename... Rest>
    auto GetMemberPointer(T* object, ParentType T::* parentMember, MemberType ParentType::* member, Rest... rest)-> decltype(GetMemberPointer(&(object->*parentMember), member, rest...))
    {
        return GetMemberPointer(&(object->*parentMember), member, rest...);
    }

    // メンバー情報作成
    template <typename T, typename... Members>
    StructMemberIndexData MakeMemberData(const std::string& nameValue, Members... members)
    {
        // 最終メンバーの型を取得する処理は別途必要
        return
        {
            nameValue,
            [members...](void* objectPtr) -> void*
            {
                T* object = static_cast<T*>(objectPtr);
                return GetMemberPointer(object, members...);
            }
        };
    }

    // 単品設定
    template <typename T>
    void SettingDrawDebugVariable(std::string TabName, T* variable, std::vector<StructMemberIndexData> memberData = {}, std::vector<DEBUG_VAR_DRAW_TYPE> drawType = {})
    {
        if (variable == nullptr)
        {
            return;
        }
        
        if (memberData.size() <= 0)
        {
            static_assert(
                IsSupportedVariableType<T>(),
                "登録されたメンバ変数は正常に稼働できない型です。"
            );
        }
        else
        {
        }
    }

    // 複数設定
    template <typename T>
    void SettingDrawDebugVariable(std::string TabName, std::vector<T>* variables, std::vector<StructMemberIndexData> memberData = {}, std::vector<DEBUG_VAR_DRAW_TYPE> drawType = {})
    {
        if (variables == nullptr)
        {
            return;
        }

        if (memberData.size() <= 0)
        {
            static_assert(
                IsSupportedVariableType<T>(),
                "登録されたメンバ変数は正常に稼働できない型です。"
            );
        }
        else
        {
        }
    }
}

namespace debugVar = DebugVariableToImgui;