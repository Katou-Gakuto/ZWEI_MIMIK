#pragma once
#include <string>
#include <vector>

#include "ImguiEnum.h"

#include "imgui.h"

struct IMGUI_VARIABLE_POITER_DATA;
struct IMGUI_VARIABLE_DATA;

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
    void GetValueToShort(short& shortValue) const;
    void GetValueToInt(int& intValue) const;
    void GetValueToLong(long& longValue) const;
    void GetValueToLongLong(long long& longlongValue) const;
    void GetValueToFloat(float& floatValue) const;
    void GetValueToDouble(double& doubleValue) const;

    // インクリメント・デクリメント
    IMGUI_VARIABLE_POITER_DATA& operator++();
    IMGUI_VARIABLE_POITER_DATA& operator--();

    const void* GetPointer() const;

    IMGUI_VARIABLE_TYPE VariableType; // 変数の型

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
    void GetValueToShort(short& shortValue) const;
    void GetValueToInt(int& intValue) const;
    void GetValueToLong(long& longValue) const;
    void GetValueToLongLong(long long& longlongValue) const;
    void GetValueToFloat(float& floatValue) const;
    void GetValueToDouble(double& doubleValue) const;

    // インクリメント・デクリメント
    IMGUI_VARIABLE_DATA& operator++();
    IMGUI_VARIABLE_DATA& operator--();

    const void* GetPointer() const;

    IMGUI_VARIABLE_TYPE VariableType; // 変数の型

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
};



// Imguiの変数描画用構造体
struct IMGUI_CONTROL_VARIABLE
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

    IMGUI_VARIABLE_DATA Min[IMGUI_VARIABLE_MAX];
    IMGUI_VARIABLE_DATA Max[IMGUI_VARIABLE_MAX];

    std::string Label = "NONE";
    std::string Format = "%.6f";

    ImGuiSliderFlags Flag = 0;
    IMGUI_TYPE ImguiType = IMGUI_TYPE::SLIDER1;
    bool AddNumberDrawFlag = true;
#endif

    // コンストラクタ
    IMGUI_CONTROL_VARIABLE()
#ifdef _DEBUG
        : Speed(1.0f)
        , Step(0.0f)
        , StepFast(0.0f)
        , Min()
        , Max()
        , Label("NONE")
        , Format("%.6f")
        , Flag(0)
        , ImguiType(IMGUI_TYPE::SLIDER1)
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
    IMGUI_CONTROL_VARIABLE(const IMGUI_CONTROL_VARIABLE& other)
#ifdef _DEBUG
        : VariableDatas(other.VariableDatas)
        , Speed(other.Speed)
        , Step(other.Step)
        , StepFast(other.StepFast)
        , Min()
        , Max()
        , Label(other.Label)
        , Format(other.Format)
        , Flag(other.Flag)
        , ImguiType(other.ImguiType)
        , AddNumberDrawFlag(other.AddNumberDrawFlag)
#endif
    {
#ifdef _DEBUG
        for (int i = 0; i < IMGUI_VARIABLE_MAX; i++)
        {
            PreVariable[i] = other.PreVariable[i];
            ChangeVariable[i] = other.ChangeVariable[i];
            Min[i] = other.Min[i];
            Max[i] = other.Max[i];
        }
#endif
    }

    // 引数付きコンストラクタ
    IMGUI_CONTROL_VARIABLE(
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
        bool addNumberFlag = true
    )
#ifdef _DEBUG
        : VariableDatas(variableDatas)
        , Speed(speed)
        , Step(step)
        , StepFast(stepFast)
        , Min()
        , Max()
        , Label(label)
        , Format(format)
        , Flag(flag)
        , ImguiType(imguiType)
        , AddNumberDrawFlag(addNumberFlag)
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

            // 引数の範囲を各変数の型に合わせる
            if (i < static_cast<int>(VariableDatas.size()))
            {
                IMGUI_VARIABLE_DATA minData(min);
                IMGUI_VARIABLE_DATA maxData(max);

                switch (VariableDatas[i].VariableType)
                {
                case IMGUI_VARIABLE_TYPE::CHAR:
                {
                    char minValue;
                    char maxValue;
                    minData.GetValueToChar(minValue);
                    maxData.GetValueToChar(maxValue);
                    Min[i] = IMGUI_VARIABLE_DATA(minValue);
                    Max[i] = IMGUI_VARIABLE_DATA(maxValue);
                    break;
                }
                case IMGUI_VARIABLE_TYPE::UNSIGNED_CHAR:
                {
                    char minValue;
                    char maxValue;
                    minData.GetValueToChar(minValue);
                    maxData.GetValueToChar(maxValue);
                    Min[i] = IMGUI_VARIABLE_DATA(
                        static_cast<unsigned char>(minValue));
                    Max[i] = IMGUI_VARIABLE_DATA(
                        static_cast<unsigned char>(maxValue));
                    break;
                }
                case IMGUI_VARIABLE_TYPE::SHORT:
                {
                    short minValue;
                    short maxValue;
                    minData.GetValueToShort(minValue);
                    maxData.GetValueToShort(maxValue);
                    Min[i] = IMGUI_VARIABLE_DATA(minValue);
                    Max[i] = IMGUI_VARIABLE_DATA(maxValue);
                    break;
                }
                case IMGUI_VARIABLE_TYPE::UNSIGNED_SHORT:
                {
                    short minValue;
                    short maxValue;
                    minData.GetValueToShort(minValue);
                    maxData.GetValueToShort(maxValue);
                    Min[i] = IMGUI_VARIABLE_DATA(
                        static_cast<unsigned short>(minValue));
                    Max[i] = IMGUI_VARIABLE_DATA(
                        static_cast<unsigned short>(maxValue));
                    break;
                }
                case IMGUI_VARIABLE_TYPE::INT:
                {
                    int minValue;
                    int maxValue;
                    minData.GetValueToInt(minValue);
                    maxData.GetValueToInt(maxValue);
                    Min[i] = IMGUI_VARIABLE_DATA(minValue);
                    Max[i] = IMGUI_VARIABLE_DATA(maxValue);
                    break;
                }
                case IMGUI_VARIABLE_TYPE::UNSIGNED_INT:
                {
                    int minValue;
                    int maxValue;
                    minData.GetValueToInt(minValue);
                    maxData.GetValueToInt(maxValue);
                    Min[i] = IMGUI_VARIABLE_DATA(
                        static_cast<unsigned int>(minValue));
                    Max[i] = IMGUI_VARIABLE_DATA(
                        static_cast<unsigned int>(maxValue));
                    break;
                }
                case IMGUI_VARIABLE_TYPE::LONG:
                {
                    long minValue;
                    long maxValue;
                    minData.GetValueToLong(minValue);
                    maxData.GetValueToLong(maxValue);
                    Min[i] = IMGUI_VARIABLE_DATA(minValue);
                    Max[i] = IMGUI_VARIABLE_DATA(maxValue);
                    break;
                }
                case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG:
                {
                    long minValue;
                    long maxValue;
                    minData.GetValueToLong(minValue);
                    maxData.GetValueToLong(maxValue);
                    Min[i] = IMGUI_VARIABLE_DATA(
                        static_cast<unsigned long>(minValue));
                    Max[i] = IMGUI_VARIABLE_DATA(
                        static_cast<unsigned long>(maxValue));
                    break;
                }
                case IMGUI_VARIABLE_TYPE::LONG_LONG:
                {
                    long long minValue;
                    long long maxValue;
                    minData.GetValueToLongLong(minValue);
                    maxData.GetValueToLongLong(maxValue);
                    Min[i] = IMGUI_VARIABLE_DATA(minValue);
                    Max[i] = IMGUI_VARIABLE_DATA(maxValue);
                    break;
                }
                case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG_LONG:
                {
                    long long minValue;
                    long long maxValue;
                    minData.GetValueToLongLong(minValue);
                    maxData.GetValueToLongLong(maxValue);
                    Min[i] = IMGUI_VARIABLE_DATA(
                        static_cast<unsigned long long>(minValue));
                    Max[i] = IMGUI_VARIABLE_DATA(
                        static_cast<unsigned long long>(maxValue));
                    break;
                }
                case IMGUI_VARIABLE_TYPE::FLOAT:
                {
                    float minValue;
                    float maxValue;
                    minData.GetValueToFloat(minValue);
                    maxData.GetValueToFloat(maxValue);
                    Min[i] = IMGUI_VARIABLE_DATA(minValue);
                    Max[i] = IMGUI_VARIABLE_DATA(maxValue);
                    break;
                }
                case IMGUI_VARIABLE_TYPE::DOUBLE:
                {
                    double minValue;
                    double maxValue;
                    minData.GetValueToDouble(minValue);
                    maxData.GetValueToDouble(maxValue);
                    Min[i] = IMGUI_VARIABLE_DATA(minValue);
                    Max[i] = IMGUI_VARIABLE_DATA(maxValue);
                    break;
                }
                case IMGUI_VARIABLE_TYPE::LONG_DOUBLE:
                {
                    double minValue;
                    double maxValue;
                    minData.GetValueToDouble(minValue);
                    maxData.GetValueToDouble(maxValue);
                    Min[i] = IMGUI_VARIABLE_DATA(
                        static_cast<long double>(minValue));
                    Max[i] = IMGUI_VARIABLE_DATA(
                        static_cast<long double>(maxValue));
                    break;
                }
                }
            }
            else
            {
                Min[i] = min;
                Max[i] = max;
            }
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
            Min[i] = IMGUI_VARIABLE_DATA();
            Max[i] = IMGUI_VARIABLE_DATA();
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
        for (size_t i = 0; i < VariableDatas.size(); i++)
        {
            Min[i] = IMGUI_VARIABLE_DATA(min, VariableDatas[i].VariableType);
        }
#endif
    }

    // 最大値を一括設定
    template<typename T>
    void SetMax(T max)
    {
#ifdef _DEBUG
        for (size_t i = 0; i < VariableDatas.size(); i++)
        {
            Max[i] = IMGUI_VARIABLE_DATA(max, VariableDatas[i].VariableType);
        }
#endif
    }

    // ラベル設定
    void SetLabel(const std::string& label)
    {
#ifdef _DEBUG
        Label = label;
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
        Flag = flag;
#endif
    }

    // ImGui種類設定
    void SetImguiType(IMGUI_TYPE imguiType)
    {
#ifdef _DEBUG
        ImguiType = imguiType;
#endif
    }

    // 追加ナンバー描画フラグ設定
    void SetAddNumberFlag(bool addNumberDrawFlag)
    {
#ifdef _DEBUG
        AddNumberDrawFlag = addNumberDrawFlag;
#endif
    }

    // float用データ生成
    static IMGUI_CONTROL_VARIABLE GetImguiData(
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
        bool addNumberDrawFlag = true
    )
    {
        IMGUI_CONTROL_VARIABLE imguiData;

#ifdef _DEBUG
        imguiData.Speed = speed;
        imguiData.Step = step;
        imguiData.StepFast = stepFast;
        imguiData.Label = label;
        imguiData.Format = format;
        imguiData.Flag = flag;
        imguiData.ImguiType = imguiType;
        imguiData.AddNumberDrawFlag = addNumberDrawFlag;

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
    static IMGUI_CONTROL_VARIABLE GetImguiData(
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
        bool addNumberDrawFlag = true
    )
    {
        IMGUI_CONTROL_VARIABLE imguiData;

#ifdef _DEBUG
        imguiData.Speed = speed;
        imguiData.Step = step;
        imguiData.StepFast = stepFast;
        imguiData.Label = label;
        imguiData.Format = format;
        imguiData.Flag = flag;
        imguiData.ImguiType = imguiType;
        imguiData.AddNumberDrawFlag = addNumberDrawFlag;

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
    static IMGUI_CONTROL_VARIABLE GetImguiData(
        const std::vector<IMGUI_VARIABLE_POITER_DATA>& variableDatas,
        float speed = 1.0f,
        float step = 1.0f,
        float stepFast = 1.0f,
        const std::string& label = "NONE",
        const std::string& format = "%d",
        ImGuiSliderFlags flag = 0,
        IMGUI_TYPE imguiType = IMGUI_TYPE::SLIDER1,
        bool addNumberDrawFlag = true
    )
    {
        IMGUI_CONTROL_VARIABLE imguiData;

#ifdef _DEBUG
        imguiData.Speed = speed;
        imguiData.Step = step;
        imguiData.StepFast = stepFast;
        imguiData.Label = label;
        imguiData.Format = format;
        imguiData.Flag = flag;
        imguiData.ImguiType = imguiType;
        imguiData.AddNumberDrawFlag = addNumberDrawFlag;

        imguiData.VariableDatas = variableDatas;
#endif

        return imguiData;
    }
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
    std::vector<IMGUI_CONTROL_VARIABLE> ImguiControlVariableDatas = {};
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
        std::vector<IMGUI_CONTROL_VARIABLE> imguiControlVariableDatas = {},
        std::vector<IMGUI_GROUP_DATA> childDatas = {}
    )
    {
        IMGUI_GROUP_DATA imguiGroupData;
#ifdef _DEBUG
        imguiGroupData.GroupType = groupType;
        imguiGroupData.GroupName = groupName;
        imguiGroupData.ImguiControlVariableDatas = imguiControlVariableDatas;
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

    /// <summary>Imgui管理変数情報追加</summary>
    void AddImguiControlVariableData(IMGUI_CONTROL_VARIABLE imguiControlVariableData)
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
    std::vector<IMGUI_CONTROL_VARIABLE>* GetImguiControlVariableDatas()
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