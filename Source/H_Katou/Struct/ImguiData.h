#pragma once
#include <string>
#include <vector>

#include "BitFlag.h"

#include "ImguiEnum.h"

#include "imgui.h"

struct IMGUI_VARIABLE_POITER_DATA;
struct IMGUI_VARIABLE_DATA;
struct IMGUI_LAYOUT_CONTROL;

/* 変数データ(ポインタ) */
struct IMGUI_VARIABLE_POITER_DATA
{
public:
    // コンストラクタ
    IMGUI_VARIABLE_POITER_DATA();
    IMGUI_VARIABLE_POITER_DATA(char* value, IMGUI_VARIABLE_TYPE variableType = IMGUI_VARIABLE_TYPE::CHAR);
    IMGUI_VARIABLE_POITER_DATA(unsigned char* value, IMGUI_VARIABLE_TYPE variableType = IMGUI_VARIABLE_TYPE::UNSIGNED_CHAR);
    IMGUI_VARIABLE_POITER_DATA(short* value, IMGUI_VARIABLE_TYPE variableType = IMGUI_VARIABLE_TYPE::SHORT);
    IMGUI_VARIABLE_POITER_DATA(unsigned short* value, IMGUI_VARIABLE_TYPE variableType = IMGUI_VARIABLE_TYPE::UNSIGNED_SHORT);
    IMGUI_VARIABLE_POITER_DATA(int* value, IMGUI_VARIABLE_TYPE variableType = IMGUI_VARIABLE_TYPE::INT);
    IMGUI_VARIABLE_POITER_DATA(unsigned int* value, IMGUI_VARIABLE_TYPE variableType = IMGUI_VARIABLE_TYPE::UNSIGNED_INT);
    IMGUI_VARIABLE_POITER_DATA(long* value, IMGUI_VARIABLE_TYPE variableType = IMGUI_VARIABLE_TYPE::LONG);
    IMGUI_VARIABLE_POITER_DATA(unsigned long* value, IMGUI_VARIABLE_TYPE variableType = IMGUI_VARIABLE_TYPE::UNSIGNED_LONG);
    IMGUI_VARIABLE_POITER_DATA(long long* value, IMGUI_VARIABLE_TYPE variableType = IMGUI_VARIABLE_TYPE::LONG_LONG);
    IMGUI_VARIABLE_POITER_DATA(unsigned long long* value, IMGUI_VARIABLE_TYPE variableType = IMGUI_VARIABLE_TYPE::UNSIGNED_LONG_LONG);
    IMGUI_VARIABLE_POITER_DATA(float* value, IMGUI_VARIABLE_TYPE variableType = IMGUI_VARIABLE_TYPE::FLOAT);
    IMGUI_VARIABLE_POITER_DATA(double* value, IMGUI_VARIABLE_TYPE variableType = IMGUI_VARIABLE_TYPE::DOUBLE);
    IMGUI_VARIABLE_POITER_DATA(long double* value, IMGUI_VARIABLE_TYPE variableType = IMGUI_VARIABLE_TYPE::LONG_DOUBLE);

    // コピー・ムーブ
    IMGUI_VARIABLE_POITER_DATA(const IMGUI_VARIABLE_POITER_DATA& other);
    IMGUI_VARIABLE_POITER_DATA(IMGUI_VARIABLE_POITER_DATA&& other);
    IMGUI_VARIABLE_POITER_DATA& operator=(const IMGUI_VARIABLE_POITER_DATA& other);
    IMGUI_VARIABLE_POITER_DATA& operator=(IMGUI_VARIABLE_POITER_DATA&& other);

    // デストラクタ
    ~IMGUI_VARIABLE_POITER_DATA();

    // 値の代入
    IMGUI_VARIABLE_POITER_DATA& operator=(char value);
    IMGUI_VARIABLE_POITER_DATA& operator=(short value);
    IMGUI_VARIABLE_POITER_DATA& operator=(int value);
    IMGUI_VARIABLE_POITER_DATA& operator=(long value);
    IMGUI_VARIABLE_POITER_DATA& operator=(long long value);
    IMGUI_VARIABLE_POITER_DATA& operator=(float value);
    IMGUI_VARIABLE_POITER_DATA& operator=(double value);
    IMGUI_VARIABLE_POITER_DATA& operator=(const IMGUI_VARIABLE_DATA& valueData);

    // 値の取得
    void GetValueToChar(char& charValue) const;
    void GetValueToUnsignedChar(unsigned char& unsignedCharValue) const;
    void GetValueToShort(short& shortValue) const;
    void GetValueToUnsignedShort(unsigned short& unsignedShortValue) const;
    void GetValueToInt(int& intValue) const;
    void GetValueToUnsignedInt(unsigned int& unsignedIntValue) const;
    void GetValueToLong(long& longValue) const;
    void GetValueToUnsignedLong(unsigned long& unsignedLongValue) const;
    void GetValueToLongLong(long long& longlongValue) const;
    void GetValueToUnsignedLongLong(unsigned long long& unsignedLongLongValue) const;
    void GetValueToFloat(float& floatValue) const;
    void GetValueToDouble(double& doubleValue) const;
    void GetValueToLongDouble(long double& longDoubleValue) const;

    // インクリメント・デクリメント
    IMGUI_VARIABLE_POITER_DATA& operator++();
    IMGUI_VARIABLE_POITER_DATA& operator--();

    const void* GetPointer() const;

    union
    {
        char* CharValue;                            //                 char型変数へのポインタ
        unsigned char* UnsignedCharValue;           // unsigned        char型変数へのポインタ
        short* ShortValue;                          //                short型変数へのポインタ
        unsigned short* UnsignedShortValue;         // unsigned       short型変数へのポインタ
        int* IntValue;                              //                  int型変数へのポインタ
        unsigned int* UnsignedIntValue;             // unsigned         int型変数へのポインタ
        long* LongValue;                            //                 long型変数へのポインタ
        unsigned long* UnsignedLongValue;           // unsigned        long型変数へのポインタ
        long long* LongLongValue;                   //          long   long型変数へのポインタ
        unsigned long long* UnsignedLongLongValue;  // unsigned long   long型変数へのポインタ
        float* FloatValue;                          //                float型変数へのポインタ
        double* DoubleValue;                        //               double型変数へのポインタ
        long double* LongDoubleValue;               //          long double型変数へのポインタ
    };

    IMGUI_VARIABLE_TYPE VariableType; // 変数の型
};
/*変数データ(値)*/
struct IMGUI_VARIABLE_DATA
{
public:
    // コンストラクタ
    IMGUI_VARIABLE_DATA();
    IMGUI_VARIABLE_DATA(char value, IMGUI_VARIABLE_TYPE variableType = IMGUI_VARIABLE_TYPE::CHAR);
    IMGUI_VARIABLE_DATA(unsigned char value, IMGUI_VARIABLE_TYPE variableType = IMGUI_VARIABLE_TYPE::UNSIGNED_CHAR);
    IMGUI_VARIABLE_DATA(short value, IMGUI_VARIABLE_TYPE variableType = IMGUI_VARIABLE_TYPE::SHORT);
    IMGUI_VARIABLE_DATA(unsigned short value, IMGUI_VARIABLE_TYPE variableType = IMGUI_VARIABLE_TYPE::UNSIGNED_SHORT);
    IMGUI_VARIABLE_DATA(int value, IMGUI_VARIABLE_TYPE variableType = IMGUI_VARIABLE_TYPE::INT);
    IMGUI_VARIABLE_DATA(unsigned int value, IMGUI_VARIABLE_TYPE variableType = IMGUI_VARIABLE_TYPE::UNSIGNED_INT);
    IMGUI_VARIABLE_DATA(long value, IMGUI_VARIABLE_TYPE variableType = IMGUI_VARIABLE_TYPE::LONG);
    IMGUI_VARIABLE_DATA(unsigned long value, IMGUI_VARIABLE_TYPE variableType = IMGUI_VARIABLE_TYPE::UNSIGNED_LONG);
    IMGUI_VARIABLE_DATA(long long value, IMGUI_VARIABLE_TYPE variableType = IMGUI_VARIABLE_TYPE::LONG_LONG);
    IMGUI_VARIABLE_DATA(unsigned long long value, IMGUI_VARIABLE_TYPE variableType = IMGUI_VARIABLE_TYPE::UNSIGNED_LONG_LONG);
    IMGUI_VARIABLE_DATA(float value, IMGUI_VARIABLE_TYPE variableType = IMGUI_VARIABLE_TYPE::FLOAT);
    IMGUI_VARIABLE_DATA(double value, IMGUI_VARIABLE_TYPE variableType = IMGUI_VARIABLE_TYPE::DOUBLE);
    IMGUI_VARIABLE_DATA(long double value, IMGUI_VARIABLE_TYPE variableType = IMGUI_VARIABLE_TYPE::LONG_DOUBLE);

    // コピー・ムーブ
    IMGUI_VARIABLE_DATA(const IMGUI_VARIABLE_DATA& other);
    IMGUI_VARIABLE_DATA(IMGUI_VARIABLE_DATA&& other);
    IMGUI_VARIABLE_DATA& operator=(const IMGUI_VARIABLE_DATA& other);
    IMGUI_VARIABLE_DATA& operator=(IMGUI_VARIABLE_DATA&& other);

    // デストラクタ
    ~IMGUI_VARIABLE_DATA();

    // 値の代入
    IMGUI_VARIABLE_DATA& operator=(char value);
    IMGUI_VARIABLE_DATA& operator=(short value);
    IMGUI_VARIABLE_DATA& operator=(int value);
    IMGUI_VARIABLE_DATA& operator=(long value);
    IMGUI_VARIABLE_DATA& operator=(long long value);
    IMGUI_VARIABLE_DATA& operator=(float value);
    IMGUI_VARIABLE_DATA& operator=(double value);
    IMGUI_VARIABLE_DATA& operator=(const IMGUI_VARIABLE_POITER_DATA& poiterData);

    // 値の取得
    void GetValueToChar(char& charValue) const;
    void GetValueToUnsignedChar(unsigned char& unsignedCharValue) const;
    void GetValueToShort(short& shortValue) const;
    void GetValueToUnsignedShort(unsigned short& unsignedShortValue) const;
    void GetValueToInt(int& intValue) const;
    void GetValueToUnsignedInt(unsigned int& unsignedIntValue) const;
    void GetValueToLong(long& longValue) const;
    void GetValueToUnsignedLong(unsigned long& unsignedLongValue) const;
    void GetValueToLongLong(long long& longlongValue) const;
    void GetValueToUnsignedLongLong(unsigned long long& unsignedLongLongValue) const;
    void GetValueToFloat(float& floatValue) const;
    void GetValueToDouble(double& doubleValue) const;
    void GetValueToLongDouble(long double& longDoubleValue) const;

    // インクリメント・デクリメント
    IMGUI_VARIABLE_DATA& operator++();
    IMGUI_VARIABLE_DATA& operator--();

    const void* GetPointer() const;

    union
    {
        char CharValue;                            //                 char型変数へのポインタ
        unsigned char UnsignedCharValue;           // unsigned        char型変数へのポインタ
        short ShortValue;                          //                short型変数へのポインタ
        unsigned short UnsignedShortValue;         // unsigned       short型変数へのポインタ
        int IntValue;                              //                  int型変数へのポインタ
        unsigned int UnsignedIntValue;             // unsigned         int型変数へのポインタ
        long LongValue;                            //                 long型変数へのポインタ
        unsigned long UnsignedLongValue;           // unsigned        long型変数へのポインタ
        long long LongLongValue;                   //          long   long型変数へのポインタ
        unsigned long long UnsignedLongLongValue;  // unsigned long   long型変数へのポインタ
        float FloatValue;                          //                float型変数へのポインタ
        double DoubleValue;                        //               double型変数へのポインタ
        long double LongDoubleValue;               //          long double型変数へのポインタ
    };

    IMGUI_VARIABLE_TYPE VariableType; // 変数の型
};



// Imguiの変数描画用構造体
struct IMGUI_VARIABLE_CONTROL
{
public:
#ifdef _DEBUG
    static constexpr int IMGUI_VARIABLE_MAX = 4;

    std::vector<IMGUI_VARIABLE_POITER_DATA> VariableDatas = {};

    IMGUI_VARIABLE_DATA PreVariable[IMGUI_VARIABLE_MAX];
    IMGUI_VARIABLE_DATA ChangeVariable[IMGUI_VARIABLE_MAX];

    float Speed = 1.0f;
    float Step = 0.0f;
    float StepFast = 0.0f;

    IMGUI_VARIABLE_DATA VariableMin;
    IMGUI_VARIABLE_DATA VariableMax;

    std::string VariableLabel = "NONE";
    std::string Format = "%.6f";

    ImGuiSliderFlags VariableFlag = 0;
    IMGUI_TYPE VariableImguiType = IMGUI_TYPE::SLIDER1;
    bool AddNumberDrawFlag = true;

    // 描画前にやるレイアウト描画
    std::vector<IMGUI_LAYOUT_CONTROL> VariableBeforeImguiLayoutControl;
    // 描画後にやるレイアウト描画
    std::vector<IMGUI_LAYOUT_CONTROL> VariableAfterImguiLayoutControl;
#endif

    // コンストラクタ
    IMGUI_VARIABLE_CONTROL()
#ifdef _DEBUG
        : Speed(1.0f)
        , Step(0.0f)
        , StepFast(0.0f)
        , VariableMin(IMGUI_VARIABLE_DATA())
        , VariableMax(IMGUI_VARIABLE_DATA())
        , VariableLabel("NONE")
        , Format("%.6f")
        , VariableFlag(0)
        , VariableImguiType(IMGUI_TYPE::SLIDER1)
        , PreVariable()
        , ChangeVariable()
        , AddNumberDrawFlag(true)
#endif
    {
#ifdef _DEBUG
        VariableDatas.clear();
#endif
    }

    // コピーコンストラクタ
    IMGUI_VARIABLE_CONTROL(const IMGUI_VARIABLE_CONTROL& other)
#ifdef _DEBUG
        : VariableDatas(other.VariableDatas)
        , Speed(other.Speed)
        , Step(other.Step)
        , StepFast(other.StepFast)
        , VariableMin(other.VariableMin)
        , VariableMax(other.VariableMax)
        , VariableLabel(other.VariableLabel)
        , Format(other.Format)
        , VariableFlag(other.VariableFlag)
        , VariableImguiType(other.VariableImguiType)
        , AddNumberDrawFlag(other.AddNumberDrawFlag)
        , VariableBeforeImguiLayoutControl(other.VariableBeforeImguiLayoutControl)
        , VariableAfterImguiLayoutControl(other.VariableAfterImguiLayoutControl)
#endif
    {
        for (int i = 0; i < IMGUI_VARIABLE_MAX; ++i)
        {
            PreVariable[i] = other.PreVariable[i];
            ChangeVariable[i] = other.ChangeVariable[i];
        }
    }

    // 引数付きコンストラクタ
    IMGUI_VARIABLE_CONTROL(
        const std::vector<IMGUI_VARIABLE_POITER_DATA>& variableDatas,
        const IMGUI_VARIABLE_DATA* preVariable,
        const IMGUI_VARIABLE_DATA* changeVariable,
        float speed = 1.0f,
        float step = 0.0f,
        float stepFast = 0.0f,
        IMGUI_VARIABLE_DATA min = IMGUI_VARIABLE_DATA(),
        IMGUI_VARIABLE_DATA max = IMGUI_VARIABLE_DATA(),
        const std::string& label = "NONE",
        const std::string& format = "%.6f",
        ImGuiSliderFlags flag = 0,
        IMGUI_TYPE imguiType = IMGUI_TYPE::SLIDER1,
        bool addNumberFlag = true,
        std::vector<IMGUI_LAYOUT_CONTROL> variableBeforeImguiLayoutControl = {},
        std::vector<IMGUI_LAYOUT_CONTROL> variableAfterImguiLayoutControl = {}
    )
#ifdef _DEBUG
        : VariableDatas(variableDatas)
        , Speed(speed)
        , Step(step)
        , StepFast(stepFast)
        , VariableMin()
        , VariableMax()
        , VariableLabel(label)
        , Format(format)
        , VariableFlag(flag)
        , VariableImguiType(imguiType)
        , AddNumberDrawFlag(addNumberFlag)
        , VariableBeforeImguiLayoutControl(variableBeforeImguiLayoutControl)
        , VariableAfterImguiLayoutControl(variableAfterImguiLayoutControl)
#endif
    {
#ifdef _DEBUG
        for (int i = 0; i < IMGUI_VARIABLE_MAX; i++)
        {
            PreVariable[i] =
                (preVariable != nullptr)
                ? preVariable[i]
                : IMGUI_VARIABLE_DATA();

            ChangeVariable[i] =
                (changeVariable != nullptr)
                ? changeVariable[i]
                : IMGUI_VARIABLE_DATA();

        }
        
        // 引数の範囲を各変数の型に合わせる
        if (0 < static_cast<int>(VariableDatas.size()))
        {
            IMGUI_VARIABLE_DATA minData(min);
            IMGUI_VARIABLE_DATA maxData(max);

            switch (VariableDatas[0].VariableType)
            {
            case IMGUI_VARIABLE_TYPE::CHAR:
            {
                char minValue;
                char maxValue;
                minData.GetValueToChar(minValue);
                maxData.GetValueToChar(maxValue);
                VariableMin = IMGUI_VARIABLE_DATA(minValue);
                VariableMax = IMGUI_VARIABLE_DATA(maxValue);
                break;
            }
            case IMGUI_VARIABLE_TYPE::UNSIGNED_CHAR:
            {
                unsigned char minValue;
                unsigned char maxValue;
                minData.GetValueToUnsignedChar(minValue);
                maxData.GetValueToUnsignedChar(maxValue);
                VariableMin = IMGUI_VARIABLE_DATA(minValue);
                VariableMax = IMGUI_VARIABLE_DATA(maxValue);
                break;
            }
            case IMGUI_VARIABLE_TYPE::SHORT:
            {
                short minValue;
                short maxValue;
                minData.GetValueToShort(minValue);
                maxData.GetValueToShort(maxValue);
                VariableMin = IMGUI_VARIABLE_DATA(minValue);
                VariableMax = IMGUI_VARIABLE_DATA(maxValue);
                break;
            }
            case IMGUI_VARIABLE_TYPE::UNSIGNED_SHORT:
            {
                unsigned short minValue;
                unsigned short maxValue;
                minData.GetValueToUnsignedShort(minValue);
                maxData.GetValueToUnsignedShort(maxValue);
                VariableMin = IMGUI_VARIABLE_DATA(minValue);
                VariableMax = IMGUI_VARIABLE_DATA(maxValue);
                break;
            }
            case IMGUI_VARIABLE_TYPE::INT:
            {
                int minValue;
                int maxValue;
                minData.GetValueToInt(minValue);
                maxData.GetValueToInt(maxValue);
                VariableMin = IMGUI_VARIABLE_DATA(minValue);
                VariableMax = IMGUI_VARIABLE_DATA(maxValue);
                break;
            }
            case IMGUI_VARIABLE_TYPE::UNSIGNED_INT:
            {
                unsigned int minValue;
                unsigned int maxValue;
                minData.GetValueToUnsignedInt(minValue);
                maxData.GetValueToUnsignedInt(maxValue);
                VariableMin = IMGUI_VARIABLE_DATA(minValue);
                VariableMax = IMGUI_VARIABLE_DATA(maxValue);
                break;
            }
            case IMGUI_VARIABLE_TYPE::LONG:
            {
                long minValue;
                long maxValue;
                minData.GetValueToLong(minValue);
                maxData.GetValueToLong(maxValue);
                VariableMin = IMGUI_VARIABLE_DATA(minValue);
                VariableMax = IMGUI_VARIABLE_DATA(maxValue);
                break;
            }
            case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG:
            {
                unsigned long minValue;
                unsigned long maxValue;
                minData.GetValueToUnsignedLong(minValue);
                maxData.GetValueToUnsignedLong(maxValue);
                VariableMin = IMGUI_VARIABLE_DATA(minValue);
                VariableMax = IMGUI_VARIABLE_DATA(maxValue);
                break;
            }
            case IMGUI_VARIABLE_TYPE::LONG_LONG:
            {
                long long minValue;
                long long maxValue;
                minData.GetValueToLongLong(minValue);
                maxData.GetValueToLongLong(maxValue);
                VariableMin = IMGUI_VARIABLE_DATA(minValue);
                VariableMax = IMGUI_VARIABLE_DATA(maxValue);
                break;
            }
            case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG_LONG:
            {
                unsigned long long minValue;
                unsigned long long maxValue;
                minData.GetValueToUnsignedLongLong(minValue);
                maxData.GetValueToUnsignedLongLong(maxValue);
                VariableMin = IMGUI_VARIABLE_DATA(minValue);
                VariableMax = IMGUI_VARIABLE_DATA(maxValue);
                break;
            }
            case IMGUI_VARIABLE_TYPE::FLOAT:
            {
                float minValue;
                float maxValue;
                minData.GetValueToFloat(minValue);
                maxData.GetValueToFloat(maxValue);
                VariableMin = IMGUI_VARIABLE_DATA(minValue);
                VariableMax = IMGUI_VARIABLE_DATA(maxValue);
                break;
            }
            case IMGUI_VARIABLE_TYPE::DOUBLE:
            {
                double minValue;
                double maxValue;
                minData.GetValueToDouble(minValue);
                maxData.GetValueToDouble(maxValue);
                VariableMin = IMGUI_VARIABLE_DATA(minValue);
                VariableMax = IMGUI_VARIABLE_DATA(maxValue);
                break;
            }
            case IMGUI_VARIABLE_TYPE::LONG_DOUBLE:
            {
                long double minValue;
                long double maxValue;
                minData.GetValueToLongDouble(minValue);
                maxData.GetValueToLongDouble(maxValue);
                VariableMin = IMGUI_VARIABLE_DATA(minValue);
                VariableMax = IMGUI_VARIABLE_DATA(maxValue);
                break;
            }
            }
        }
        else
        {
            VariableMin = min;
            VariableMax = max;
        }
#endif
    }

    // ポインタが保持している値を取得
    static IMGUI_VARIABLE_DATA GetVariableValue(const IMGUI_VARIABLE_POITER_DATA& data)
    {
#ifdef _DEBUG
        switch (data.VariableType)
        {
        case IMGUI_VARIABLE_TYPE::CHAR:
            return IMGUI_VARIABLE_DATA(*data.CharValue);

        case IMGUI_VARIABLE_TYPE::UNSIGNED_CHAR:
            return IMGUI_VARIABLE_DATA(*data.UnsignedCharValue);

        case IMGUI_VARIABLE_TYPE::SHORT:
            return IMGUI_VARIABLE_DATA(*data.ShortValue);

        case IMGUI_VARIABLE_TYPE::UNSIGNED_SHORT:
            return IMGUI_VARIABLE_DATA(*data.UnsignedShortValue);

        case IMGUI_VARIABLE_TYPE::INT:
            return IMGUI_VARIABLE_DATA(*data.IntValue);

        case IMGUI_VARIABLE_TYPE::UNSIGNED_INT:
            return IMGUI_VARIABLE_DATA(*data.UnsignedIntValue);

        case IMGUI_VARIABLE_TYPE::LONG:
            return IMGUI_VARIABLE_DATA(*data.LongValue);

        case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG:
            return IMGUI_VARIABLE_DATA(*data.UnsignedLongValue);

        case IMGUI_VARIABLE_TYPE::LONG_LONG:
            return IMGUI_VARIABLE_DATA(*data.LongLongValue);

        case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG_LONG:
            return IMGUI_VARIABLE_DATA(*data.UnsignedLongLongValue);

        case IMGUI_VARIABLE_TYPE::FLOAT:
            return IMGUI_VARIABLE_DATA(*data.FloatValue);

        case IMGUI_VARIABLE_TYPE::DOUBLE:
            return IMGUI_VARIABLE_DATA(*data.DoubleValue);

        case IMGUI_VARIABLE_TYPE::LONG_DOUBLE:
            return IMGUI_VARIABLE_DATA(*data.LongDoubleValue);
        }
#endif
        return IMGUI_VARIABLE_DATA();
    }

    // 変数を追加
    template<typename T>
    void AddVariable(T* src)
    {
#ifdef _DEBUG
        if (src == nullptr ||
            VariableDatas.size() >= IMGUI_VARIABLE_MAX)
        {
            return;
        }

        VariableDatas.emplace_back(src);

        const int index =
            static_cast<int>(VariableDatas.size() - 1);

        PreVariable[index] =
            GetVariableValue(VariableDatas[index]);

        ChangeVariable[index] = PreVariable[index];
#endif
    }

    // 変数リセット
    void ReSetVariable()
    {
#ifdef _DEBUG
        VariableDatas.clear();

        for (int i = 0; i < IMGUI_VARIABLE_MAX; i++)
        {
            PreVariable[i] = IMGUI_VARIABLE_DATA();
            ChangeVariable[i] = IMGUI_VARIABLE_DATA();
        }
#endif
    }

    // 速度設定
    void SetSpeed(float speed)
    {
#ifdef _DEBUG
        Speed = speed;
#endif
    }

    // 刻み幅設定
    void SetStep(float step)
    {
#ifdef _DEBUG
        Step = step;
#endif
    }

    // Ctrl押下時の刻み幅設定
    void SetStepFast(float stepFast)
    {
#ifdef _DEBUG
        StepFast = stepFast;
#endif
    }

    // 最小値を一括設定
    template<typename T>
    void SetMin(T min)
    {
#ifdef _DEBUG
        if (0 < VariableDatas.size())
        {
            VariableMin = IMGUI_VARIABLE_DATA(min, VariableDatas[0].VariableType);
        }
#endif
    }

    // 最大値を一括設定
    template<typename T>
    void SetMax(T max)
    {
#ifdef _DEBUG
        if (0 < VariableDatas.size())
        {
            VariableMax = IMGUI_VARIABLE_DATA(max, VariableDatas[0].VariableType);
        }
#endif
    }

    // ラベル設定
    void SetLabel(const std::string& label)
    {
#ifdef _DEBUG
        VariableLabel = label;
#endif
    }

    // フォーマット設定
    void SetFormat(const std::string& format)
    {
#ifdef _DEBUG
        Format = format;
#endif
    }

    // オプションフラグ設定
    void SetFlag(ImGuiSliderFlags flag)
    {
#ifdef _DEBUG
        VariableFlag = flag;
#endif
    }

    // ImGui種類設定
    void SetImguiType(IMGUI_TYPE imguiType)
    {
#ifdef _DEBUG
        VariableImguiType = imguiType;
#endif
    }

    // 追加ナンバー描画フラグ設定
    void SetAddNumberFlag(bool addNumberDrawFlag)
    {
#ifdef _DEBUG
        AddNumberDrawFlag = addNumberDrawFlag;
#endif
    }

    // 描画前レイアウト設定
    void SetVariableBeforeImguiLayoutControl(std::vector<IMGUI_LAYOUT_CONTROL> variableBeforeImguiLayoutControl)
    {
#ifdef _DEBUG
        this->VariableBeforeImguiLayoutControl = variableBeforeImguiLayoutControl;
#endif
    }

    // 描画後レイアウト設定
    void SetVariableAfterImguiLayoutControl(std::vector<IMGUI_LAYOUT_CONTROL> variableAfterImguiLayoutControl)
    {
#ifdef _DEBUG
        this->VariableAfterImguiLayoutControl = variableAfterImguiLayoutControl;
#endif
    }

    // float用データ生成
    static IMGUI_VARIABLE_CONTROL GetImguiData(
        const std::vector<float*>& variableDatas,
        float speed = 1.0f,
        float step = 0.0f,
        float stepFast = 0.0f,
        float min = -1.0f,
        float max = 1.0f,
        const std::string& label = "NONE",
        const std::string& format = "%.6f",
        ImGuiSliderFlags flag = 0,
        IMGUI_TYPE imguiType = IMGUI_TYPE::SLIDER1,
        bool addNumberDrawFlag = true,
        std::vector<IMGUI_LAYOUT_CONTROL> variableBeforeImguiLayoutControl = {},
        std::vector<IMGUI_LAYOUT_CONTROL> variableAfterImguiLayoutControl = {}
    )
    {
        IMGUI_VARIABLE_CONTROL imguiData;

#ifdef _DEBUG
        imguiData.Speed = speed;
        imguiData.Step = step;
        imguiData.StepFast = stepFast;
        imguiData.VariableLabel = label;
        imguiData.Format = format;
        imguiData.VariableFlag = flag;
        imguiData.VariableImguiType = imguiType;
        imguiData.AddNumberDrawFlag = addNumberDrawFlag;
        imguiData.VariableBeforeImguiLayoutControl = variableBeforeImguiLayoutControl;
        imguiData.VariableAfterImguiLayoutControl = variableAfterImguiLayoutControl;

        for (float* variable : variableDatas)
        {
            imguiData.AddVariable(variable);
        }
        imguiData.SetMin(min);
        imguiData.SetMax(max);
#endif

        return imguiData;
    }

    // int用データ生成
    static IMGUI_VARIABLE_CONTROL GetImguiData(
        const std::vector<int*>& variableDatas,
        float speed = 1.0f,
        float step = 1.0f,
        float stepFast = 1.0f,
        int min = -1,
        int max = 1,
        const std::string& label = "NONE",
        const std::string& format = "%d",
        ImGuiSliderFlags flag = 0,
        IMGUI_TYPE imguiType = IMGUI_TYPE::SLIDER1,
        bool addNumberDrawFlag = true,
        std::vector<IMGUI_LAYOUT_CONTROL> variableBeforeImguiLayoutControl = {},
        std::vector<IMGUI_LAYOUT_CONTROL> variableAfterImguiLayoutControl = {}
    )
    {
        IMGUI_VARIABLE_CONTROL imguiData;

#ifdef _DEBUG
        imguiData.Speed = speed;
        imguiData.Step = step;
        imguiData.StepFast = stepFast;
        imguiData.VariableLabel = label;
        imguiData.Format = format;
        imguiData.VariableFlag = flag;
        imguiData.VariableImguiType = imguiType;
        imguiData.AddNumberDrawFlag = addNumberDrawFlag;
        imguiData.VariableBeforeImguiLayoutControl = variableBeforeImguiLayoutControl;
        imguiData.VariableAfterImguiLayoutControl = variableAfterImguiLayoutControl;

        for (int* variable : variableDatas)
        {
            imguiData.AddVariable(variable);
        }

        imguiData.SetMin(min);
        imguiData.SetMax(max);
#endif

        return imguiData;
    }

    // 汎用データ生成
    static IMGUI_VARIABLE_CONTROL GetImguiData(
        const std::vector<IMGUI_VARIABLE_POITER_DATA>& variableDatas,
        float speed = 1.0f,
        float step = 1.0f,
        float stepFast = 1.0f,
        const std::string& label = "NONE",
        const std::string& format = "%d",
        ImGuiSliderFlags flag = 0,
        IMGUI_TYPE imguiType = IMGUI_TYPE::SLIDER1,
        bool addNumberDrawFlag = true,
        std::vector<IMGUI_LAYOUT_CONTROL> variableBeforeImguiLayoutControl = {},
        std::vector<IMGUI_LAYOUT_CONTROL> variableAfterImguiLayoutControl = {}
    )
    {
        IMGUI_VARIABLE_CONTROL imguiData;

#ifdef _DEBUG
        imguiData.Speed = speed;
        imguiData.Step = step;
        imguiData.StepFast = stepFast;
        imguiData.VariableLabel = label;
        imguiData.Format = format;
        imguiData.VariableFlag = flag;
        imguiData.VariableImguiType = imguiType;
        imguiData.AddNumberDrawFlag = addNumberDrawFlag;
        imguiData.VariableBeforeImguiLayoutControl = variableBeforeImguiLayoutControl;
        imguiData.VariableAfterImguiLayoutControl = variableAfterImguiLayoutControl;

        imguiData.VariableDatas = variableDatas;
#endif

        return imguiData;
    }
};



// Imguiのボタン描画用構造体
struct IMGUI_BUTTON_CONTROL
{
#ifdef _DEBUG
    // ボタン種類
    IMGUI_BUTTON_TYPE ButtonType;
 
    // ボタンラベル
    std::string ButtonLabel;
    // 押すキーの文字列
    std::string PressKeyString = "NONE";
    // url
    std::string Url = "https://github.com/Katou-Gakuto";

    // ImGuiのenum設定値
    union
    {
        int ButtonImGuiEnumFlags;
        ImGuiDir ButtonDir;
        ImGuiButtonFlags ButtonFlags;
        ImGuiColorEditFlags ButtonColorEditFlags;
        ImGuiSelectableFlags ButtonSelectableFlags;
        ImGuiTabItemFlags ButtonTabItemFlags;
    };
    
    // 描画サイズ
    ImVec2 ButtonSize;
    // 色
    ImVec4 ButtonColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    // 描画フラグ
    bool ButtonDrawFlag;

    // ボタンフラグ
    bool *ButtonFlag = nullptr;
    // 引数ボタンフラグ
    bool *ArgumentButtonFlag = nullptr;
    // ボタンビットフラグ
    unsigned int* ButtonBitFlag = nullptr;
    // ボタンビットフラグの値
    unsigned int ButtonBitFlagValue = 0;

    // 描画前にやるレイアウト描画
    std::vector<IMGUI_LAYOUT_CONTROL> ButtonBeforeImguiLayoutControl;
    // 描画後にやるレイアウト描画
    std::vector<IMGUI_LAYOUT_CONTROL> ButtonAfterImguiLayoutControl;
#endif
};

// imguiのレイアウト描画用構造体
struct IMGUI_LAYOUT_CONTROL
{
#ifdef _DEBUG
    IMGUI_LAYOUT_TYPE LayoutType; // レイアウトの処理種別

    std::string LayoutText; // 表示文字列、フォーマット文字列、見出し名、ツリー名、列名など
    int LayoutCount = 0; // 要素数、列数、スタイル復元数など
    int LayoutIndex = 0; // 列番号など
    unsigned int LayoutUserID = 0; // ユーザー識別用ID

    ImVec2 LayoutSize = ImVec2(0.0f, 0.0f); // 領域サイズ、空白サイズ、スタイル値など
    float LayoutWidth = 0.0f; // UI項目や列の幅
    float LayoutSpacing = -1.0f; // 項目間の間隔
    float LayoutMinHeight = 0.0f; // 行の最小高さ

    // ImGuiのenum設定値
    union
    {
        int LayoutImguiEnumFlags = 0;
        ImGuiTreeNodeFlags LayoutTreeNodeFlags; // = ImGuiTreeNodeFlags_None; ツリー項目の設定
        ImGuiTableFlags LayoutTableFlags; // = ImGuiTableFlags_None; 表の設定
        ImGuiTableColumnFlags LayoutTableColumnFlags; // = ImGuiTableColumnFlags_None; 表の列設定
        ImGuiStyleVar LayoutStyleVar; // = ImGuiStyleVar_ItemSpacing; 変更するスタイル項目
        ImGuiCol LayoutStyleColor; // = ImGuiCol_Text; 変更する色の項目
        ImGuiTabBarFlags LayoutStyleTabBarFlags;    // = ImGuiTabBarFlags_; タブバーの設定
    };

    //==================================================
    // テキスト関連
    //==================================================

    IMGUI_VARIABLE_DATA LayoutVarable; // 変数の値

    //==================================================
    // 子領域関連
    //==================================================
    ImGuiChildFlags LayoutChildFlags = ImGuiChildFlags_None; // 子領域の設定
    ImGuiWindowFlags LayoutWindowFlags = ImGuiWindowFlags_None; // 子領域のウィンドウ設定

    //==================================================
    // 折りたたみ・ツリー関連
    //==================================================

    bool LayoutDefaultOpen = false; // 次のツリー項目を開いた状態にするか



    //==================================================
    // スタイル関連
    //==================================================

    ImVec4 LayoutColor = ImVec4(1.0f, 0.0f, 0.0f, 1.0f); // 変更する色（RGBA）
    #endif
};


// imgui全種類描画用1つ分情報
struct IMGUI_ALL_DRAW_ONE_DATA
{
    IMGUI_DRAW_MODE MyImguiDrawMode;

    IMGUI_VARIABLE_CONTROL ImguiVariableControl;
    IMGUI_BUTTON_CONTROL   ImguiButtonControl;
    IMGUI_LAYOUT_CONTROL   ImguiLayoutControl;

    // グループに登録した最終フレーム
    int LastRegisteredFrame = -1;

    IMGUI_ALL_DRAW_ONE_DATA();
    IMGUI_ALL_DRAW_ONE_DATA(IMGUI_VARIABLE_CONTROL value);
    IMGUI_ALL_DRAW_ONE_DATA(IMGUI_BUTTON_CONTROL value);
    IMGUI_ALL_DRAW_ONE_DATA(IMGUI_LAYOUT_CONTROL value);

    // コピー・ムーブ
    IMGUI_ALL_DRAW_ONE_DATA(const IMGUI_ALL_DRAW_ONE_DATA& other);
    IMGUI_ALL_DRAW_ONE_DATA(IMGUI_ALL_DRAW_ONE_DATA&& other);
    IMGUI_ALL_DRAW_ONE_DATA& operator=(const IMGUI_ALL_DRAW_ONE_DATA& other);
    IMGUI_ALL_DRAW_ONE_DATA& operator=(IMGUI_ALL_DRAW_ONE_DATA&& other);

    // デストラクタ
    ~IMGUI_ALL_DRAW_ONE_DATA();

    IMGUI_ALL_DRAW_ONE_DATA& operator=(const IMGUI_VARIABLE_CONTROL& other);
    IMGUI_ALL_DRAW_ONE_DATA& operator=(IMGUI_VARIABLE_CONTROL&& other);
    IMGUI_ALL_DRAW_ONE_DATA& operator=(const IMGUI_BUTTON_CONTROL& other);
    IMGUI_ALL_DRAW_ONE_DATA& operator=(IMGUI_BUTTON_CONTROL&& other);
    IMGUI_ALL_DRAW_ONE_DATA& operator=(const IMGUI_LAYOUT_CONTROL& other);
    IMGUI_ALL_DRAW_ONE_DATA& operator=(IMGUI_LAYOUT_CONTROL&& other);
};

// 1グループのimgui描画情報
struct IMGUI_GROUP_DATA
{
private:
#ifdef _DEBUG
    // グループ参照用
    IMGUI_GROUP_TYPE GroupType = IMGUI_GROUP_TYPE::NONE;

    // グループ名
    std::string GroupName = "NONE";

    // Imgui管理変数情報
    std::vector<IMGUI_ALL_DRAW_ONE_DATA> ImguiControlVariableDatas = {};
    // 子の情報
    std::vector<IMGUI_GROUP_DATA> ChildDatas = {};
#endif

public:
    /*------------*/
    /*  【生成】  */
    /*------------*/
    static IMGUI_GROUP_DATA GetImguiGroupData(
        std::string groupName = "NEW GROUP",
        IMGUI_GROUP_TYPE groupType = IMGUI_GROUP_TYPE::NONE,
        std::vector<IMGUI_ALL_DRAW_ONE_DATA> imguiControlVariableDatas = {},
        std::vector<IMGUI_GROUP_DATA> childDatas = {}
    )
    {
        IMGUI_GROUP_DATA imguiGroupData;
#ifdef _DEBUG
        imguiGroupData.GroupType = groupType;
        imguiGroupData.GroupName = groupName;
        imguiGroupData.ImguiControlVariableDatas.clear();
        imguiGroupData.ImguiControlVariableDatas.resize(imguiControlVariableDatas.size());
        for (int i = 0; i < imguiControlVariableDatas.size(); ++i)
        {
            imguiGroupData.ImguiControlVariableDatas[i] = imguiControlVariableDatas[i];
        }
        imguiGroupData.ChildDatas = childDatas;
#endif
        return imguiGroupData;
    }

    /*------------*/
    /*【リセット】*/
    /*------------*/
    /// <summary>情報リセット</summary>
    void ReSetDatas()
    {
#ifdef _DEBUG
        ImguiControlVariableDatas.clear();
#endif
    }

    
    /*------------*/
    /*  【追加】  */
    /*------------*/

    /// <summary>Imgui管理描画情報追加</summary>
    void AddImguiControlDrawData(IMGUI_ALL_DRAW_ONE_DATA imguiControlVariableData)
    {
#ifdef _DEBUG
        ImguiControlVariableDatas.push_back(imguiControlVariableData);
#endif
    }

    /// <summary>子グループ追加</summary>
    void AddChildData(IMGUI_GROUP_DATA childData)
    {
#ifdef _DEBUG
        ChildDatas.push_back(childData);
#endif
    }

    /*------------*/
    /*  【設定】  */
    /*------------*/
    /// <summary>グループ種類設定</summary>
    void SetGroupType(IMGUI_GROUP_TYPE groupType)
    {
#ifdef _DEBUG
        GroupType = groupType;
#endif
    }

    /// <summary>グループ名設定</summary>
    void SetGroupName(std::string groupName)
    {
#ifdef _DEBUG
        GroupName = groupName;
#endif
    }

    /*------------*/
    /*  【取得】  */
    /*------------*/
    /// <summary>グループ種類取得</summary>
    IMGUI_GROUP_TYPE GetGroupType() const
    {
#ifdef _DEBUG
        return GroupType;
#else
        return IMGUI_GROUP_TYPE::NONE;
#endif
    }

    /// <summary>グループ名取得</summary>
    const std::string& GetGroupName() const
    {
#ifdef _DEBUG
        return GroupName;
#else
        static const std::string empty = "";
        return empty;
#endif
    }

    /// <summary>imgui管理変数情報取得</summary>
    std::vector<IMGUI_ALL_DRAW_ONE_DATA>* GetImguiControlVariableDatas()
    {
#ifdef _DEBUG
        return &ImguiControlVariableDatas;
#else
        return nullptr;
#endif
    }

    /// <summary>子グループ取得</summary>
    std::vector<IMGUI_GROUP_DATA>* GetChildDatas()
    {
#ifdef _DEBUG
        return &ChildDatas;
#else
        return nullptr;
#endif
    }
};