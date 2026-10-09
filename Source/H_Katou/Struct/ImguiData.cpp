#include "ImguiData.h"

// コンストラクタ
IMGUI_VARIABLE_POITER_DATA::IMGUI_VARIABLE_POITER_DATA()
: VariableType(IMGUI_VARIABLE_TYPE::NONE)
, CharValue(nullptr)
, UnsignedCharValue(nullptr)
, ShortValue(nullptr)
, UnsignedShortValue(nullptr)
, IntValue(nullptr)
, UnsignedIntValue(nullptr)
, LongValue(nullptr)
, UnsignedLongValue(nullptr)
, LongLongValue(nullptr)
, UnsignedLongLongValue(nullptr)
, FloatValue(nullptr)
, DoubleValue(nullptr)
, LongDoubleValue(nullptr)
{
}
IMGUI_VARIABLE_POITER_DATA::IMGUI_VARIABLE_POITER_DATA(char* value)
: VariableType(IMGUI_VARIABLE_TYPE::CHAR)
, CharValue(value)
, UnsignedCharValue(nullptr)
, ShortValue(nullptr)
, UnsignedShortValue(nullptr)
, IntValue(nullptr)
, UnsignedIntValue(nullptr)
, LongValue(nullptr)
, UnsignedLongValue(nullptr)
, LongLongValue(nullptr)
, UnsignedLongLongValue(nullptr)
, FloatValue(nullptr)
, DoubleValue(nullptr)
, LongDoubleValue(nullptr)
{
}
IMGUI_VARIABLE_POITER_DATA::IMGUI_VARIABLE_POITER_DATA(unsigned char* value)
: VariableType(IMGUI_VARIABLE_TYPE::UNSIGNED_CHAR)
, CharValue(nullptr)
, UnsignedCharValue(value)
, ShortValue(nullptr)
, UnsignedShortValue(nullptr)
, IntValue(nullptr)
, UnsignedIntValue(nullptr)
, LongValue(nullptr)
, UnsignedLongValue(nullptr)
, LongLongValue(nullptr)
, UnsignedLongLongValue(nullptr)
, FloatValue(nullptr)
, DoubleValue(nullptr)
, LongDoubleValue(nullptr)
{
}
IMGUI_VARIABLE_POITER_DATA::IMGUI_VARIABLE_POITER_DATA(short* value)
: VariableType(IMGUI_VARIABLE_TYPE::SHORT)
, CharValue(nullptr)
, UnsignedCharValue(nullptr)
, ShortValue(value)
, UnsignedShortValue(nullptr)
, IntValue(nullptr)
, UnsignedIntValue(nullptr)
, LongValue(nullptr)
, UnsignedLongValue(nullptr)
, LongLongValue(nullptr)
, UnsignedLongLongValue(nullptr)
, FloatValue(nullptr)
, DoubleValue(nullptr)
, LongDoubleValue(nullptr)
{
}
IMGUI_VARIABLE_POITER_DATA::IMGUI_VARIABLE_POITER_DATA(unsigned short* value)
: VariableType(IMGUI_VARIABLE_TYPE::UNSIGNED_SHORT)
, CharValue(nullptr)
, UnsignedCharValue(nullptr)
, ShortValue(nullptr)
, UnsignedShortValue(value)
, IntValue(nullptr)
, UnsignedIntValue(nullptr)
, LongValue(nullptr)
, UnsignedLongValue(nullptr)
, LongLongValue(nullptr)
, UnsignedLongLongValue(nullptr)
, FloatValue(nullptr)
, DoubleValue(nullptr)
, LongDoubleValue(nullptr)
{
}
IMGUI_VARIABLE_POITER_DATA::IMGUI_VARIABLE_POITER_DATA(int* value)
: VariableType(IMGUI_VARIABLE_TYPE::INT)
, CharValue(nullptr)
, UnsignedCharValue(nullptr)
, ShortValue(nullptr)
, UnsignedShortValue(nullptr)
, IntValue(value)
, UnsignedIntValue(nullptr)
, LongValue(nullptr)
, UnsignedLongValue(nullptr)
, LongLongValue(nullptr)
, UnsignedLongLongValue(nullptr)
, FloatValue(nullptr)
, DoubleValue(nullptr)
, LongDoubleValue(nullptr)
{
}
IMGUI_VARIABLE_POITER_DATA::IMGUI_VARIABLE_POITER_DATA(unsigned int* value)
: VariableType(IMGUI_VARIABLE_TYPE::UNSIGNED_INT)
, CharValue(nullptr)
, UnsignedCharValue(nullptr)
, ShortValue(nullptr)
, UnsignedShortValue(nullptr)
, IntValue(nullptr)
, UnsignedIntValue(value)
, LongValue(nullptr)
, UnsignedLongValue(nullptr)
, LongLongValue(nullptr)
, UnsignedLongLongValue(nullptr)
, FloatValue(nullptr)
, DoubleValue(nullptr)
, LongDoubleValue(nullptr)
{
}
IMGUI_VARIABLE_POITER_DATA::IMGUI_VARIABLE_POITER_DATA(long* value)
: VariableType(IMGUI_VARIABLE_TYPE::LONG)
, CharValue(nullptr)
, UnsignedCharValue(nullptr)
, ShortValue(nullptr)
, UnsignedShortValue(nullptr)
, IntValue(nullptr)
, UnsignedIntValue(nullptr)
, LongValue(value)
, UnsignedLongValue(nullptr)
, LongLongValue(nullptr)
, UnsignedLongLongValue(nullptr)
, FloatValue(nullptr)
, DoubleValue(nullptr)
, LongDoubleValue(nullptr)
{
}
IMGUI_VARIABLE_POITER_DATA::IMGUI_VARIABLE_POITER_DATA(unsigned long* value)
: VariableType(IMGUI_VARIABLE_TYPE::UNSIGNED_LONG)
, CharValue(nullptr)
, UnsignedCharValue(nullptr)
, ShortValue(nullptr)
, UnsignedShortValue(nullptr)
, IntValue(nullptr)
, UnsignedIntValue(nullptr)
, LongValue(nullptr)
, UnsignedLongValue(value)
, LongLongValue(nullptr)
, UnsignedLongLongValue(nullptr)
, FloatValue(nullptr)
, DoubleValue(nullptr)
, LongDoubleValue(nullptr)
{
}
IMGUI_VARIABLE_POITER_DATA::IMGUI_VARIABLE_POITER_DATA(long long* value)
: VariableType(IMGUI_VARIABLE_TYPE::LONG_LONG)
, CharValue(nullptr)
, UnsignedCharValue(nullptr)
, ShortValue(nullptr)
, UnsignedShortValue(nullptr)
, IntValue(nullptr)
, UnsignedIntValue(nullptr)
, LongValue(nullptr)
, UnsignedLongValue(nullptr)
, LongLongValue(value)
, UnsignedLongLongValue(nullptr)
, FloatValue(nullptr)
, DoubleValue(nullptr)
, LongDoubleValue(nullptr)
{
}
IMGUI_VARIABLE_POITER_DATA::IMGUI_VARIABLE_POITER_DATA(unsigned long long* value)
: VariableType(IMGUI_VARIABLE_TYPE::UNSIGNED_long_LONG)
, CharValue(nullptr)
, UnsignedCharValue(nullptr)
, ShortValue(nullptr)
, UnsignedShortValue(nullptr)
, IntValue(nullptr)
, UnsignedIntValue(nullptr)
, LongValue(nullptr)
, UnsignedLongValue(nullptr)
, LongLongValue(nullptr)
, UnsignedLongLongValue(value)
, FloatValue(nullptr)
, DoubleValue(nullptr)
, LongDoubleValue(nullptr)
{
}
IMGUI_VARIABLE_POITER_DATA::IMGUI_VARIABLE_POITER_DATA(float* value)
: VariableType(IMGUI_VARIABLE_TYPE::FLOAT)
, CharValue(nullptr)
, UnsignedCharValue(nullptr)
, ShortValue(nullptr)
, UnsignedShortValue(nullptr)
, IntValue(nullptr)
, UnsignedIntValue(nullptr)
, LongValue(nullptr)
, UnsignedLongValue(nullptr)
, LongLongValue(nullptr)
, UnsignedLongLongValue(nullptr)
, FloatValue(value)
, DoubleValue(nullptr)
, LongDoubleValue(nullptr)
{
}
IMGUI_VARIABLE_POITER_DATA::IMGUI_VARIABLE_POITER_DATA(double* value)
: VariableType(IMGUI_VARIABLE_TYPE::DOUBLE)
, CharValue(nullptr)
, UnsignedCharValue(nullptr)
, ShortValue(nullptr)
, UnsignedShortValue(nullptr)
, IntValue(nullptr)
, UnsignedIntValue(nullptr)
, LongValue(nullptr)
, UnsignedLongValue(nullptr)
, LongLongValue(nullptr)
, UnsignedLongLongValue(nullptr)
, FloatValue(nullptr)
, DoubleValue(value)
, LongDoubleValue(nullptr)
{
}
IMGUI_VARIABLE_POITER_DATA::IMGUI_VARIABLE_POITER_DATA(long double* value)
: VariableType(IMGUI_VARIABLE_TYPE::LONG_DOUBLE)
, CharValue(nullptr)
, UnsignedCharValue(nullptr)
, ShortValue(nullptr)
, UnsignedShortValue(nullptr)
, IntValue(nullptr)
, UnsignedIntValue(nullptr)
, LongValue(nullptr)
, UnsignedLongValue(nullptr)
, LongLongValue(nullptr)
, UnsignedLongLongValue(nullptr)
, FloatValue(nullptr)
, DoubleValue(nullptr)
, LongDoubleValue(value)
{
}

// コピー・ムーブ
IMGUI_VARIABLE_POITER_DATA::IMGUI_VARIABLE_POITER_DATA(const IMGUI_VARIABLE_POITER_DATA& other)
: VariableType(other.VariableType)
, CharValue(other.CharValue)
, UnsignedCharValue(other.UnsignedCharValue)
, ShortValue(other.ShortValue)
, UnsignedShortValue(other.UnsignedShortValue)
, IntValue(other.IntValue)
, UnsignedIntValue(other.UnsignedIntValue)
, LongValue(other.LongValue)
, UnsignedLongValue(other.UnsignedLongValue)
, LongLongValue(other.LongLongValue)
, UnsignedLongLongValue(other.UnsignedLongLongValue)
, FloatValue(other.FloatValue)
, DoubleValue(other.DoubleValue)
, LongDoubleValue(other.LongDoubleValue)
{
}

IMGUI_VARIABLE_POITER_DATA::IMGUI_VARIABLE_POITER_DATA(IMGUI_VARIABLE_POITER_DATA&& other)
: VariableType(other.VariableType)
, CharValue(other.CharValue)
, UnsignedCharValue(other.UnsignedCharValue)
, ShortValue(other.ShortValue)
, UnsignedShortValue(other.UnsignedShortValue)
, IntValue(other.IntValue)
, UnsignedIntValue(other.UnsignedIntValue)
, LongValue(other.LongValue)
, UnsignedLongValue(other.UnsignedLongValue)
, LongLongValue(other.LongLongValue)
, UnsignedLongLongValue(other.UnsignedLongLongValue)
, FloatValue(other.FloatValue)
, DoubleValue(other.DoubleValue)
, LongDoubleValue(other.LongDoubleValue)
{
}

IMGUI_VARIABLE_POITER_DATA& IMGUI_VARIABLE_POITER_DATA::operator=(const IMGUI_VARIABLE_POITER_DATA& other)
{
    this->VariableType = other.VariableType;
    this->CharValue = other.CharValue;
    this->UnsignedCharValue = other.UnsignedCharValue;
    this->ShortValue = other.ShortValue;
    this->UnsignedShortValue = other.UnsignedShortValue;
    this->IntValue = other.IntValue;
    this->UnsignedIntValue = other.UnsignedIntValue;
    this->LongValue = other.LongValue;
    this->UnsignedLongValue = other.UnsignedLongValue;
    this->LongLongValue = other.LongLongValue;
    this->UnsignedLongLongValue = other.UnsignedLongLongValue;
    this->FloatValue = other.FloatValue;
    this->DoubleValue = other.DoubleValue;
    this->LongDoubleValue = other.LongDoubleValue;

    return *this;
}

IMGUI_VARIABLE_POITER_DATA& IMGUI_VARIABLE_POITER_DATA::operator=(IMGUI_VARIABLE_POITER_DATA&& other)
{
    this->VariableType = other.VariableType;
    this->CharValue = other.CharValue;
    this->UnsignedCharValue = other.UnsignedCharValue;
    this->ShortValue = other.ShortValue;
    this->UnsignedShortValue = other.UnsignedShortValue;
    this->IntValue = other.IntValue;
    this->UnsignedIntValue = other.UnsignedIntValue;
    this->LongValue = other.LongValue;
    this->UnsignedLongValue = other.UnsignedLongValue;
    this->LongLongValue = other.LongLongValue;
    this->UnsignedLongLongValue = other.UnsignedLongLongValue;
    this->FloatValue = other.FloatValue;
    this->DoubleValue = other.DoubleValue;
    this->LongDoubleValue = other.LongDoubleValue;

    return *this;
}


// デストラクタ
IMGUI_VARIABLE_POITER_DATA::~IMGUI_VARIABLE_POITER_DATA()
{
}

// 値の代入
IMGUI_VARIABLE_POITER_DATA& IMGUI_VARIABLE_POITER_DATA::operator=(char value)
{
    switch (VariableType)
    {
    case IMGUI_VARIABLE_TYPE::CHAR:
        if (this->CharValue == nullptr) { break; }
        *this->CharValue = static_cast<char>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_CHAR:
        if (this->UnsignedCharValue == nullptr) { break; }
        *this->UnsignedCharValue = static_cast<unsigned char>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::SHORT:
        if (this->ShortValue == nullptr) { break; }
        *this->ShortValue = static_cast<short>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_SHORT:
        if (this->UnsignedShortValue == nullptr) { break; }
        *this->UnsignedShortValue = static_cast<unsigned short>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::INT:
        if (this->IntValue == nullptr) { break; }
        *this->IntValue = static_cast<int>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_INT:
        if (this->UnsignedIntValue == nullptr) { break; }
        *this->UnsignedIntValue = static_cast<unsigned int>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG:
        if (this->LongValue == nullptr) { break; }
        *this->LongValue = static_cast<long>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG:
        if (this->UnsignedLongValue == nullptr) { break; }
        *this->UnsignedLongValue = static_cast<unsigned long>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_LONG:
        if (this->LongLongValue == nullptr) { break; }
        *this->LongLongValue = static_cast<long long>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_long_LONG:
        if (this->UnsignedLongLongValue == nullptr) { break; }
        *this->UnsignedLongLongValue = static_cast<unsigned long long>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::FLOAT:
        if (this->FloatValue == nullptr) { break; }
        *this->FloatValue = static_cast<float>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::DOUBLE:
        if (this->DoubleValue == nullptr) { break; }
        *this->DoubleValue = static_cast<double>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_DOUBLE:
        if (this->LongDoubleValue == nullptr) { break; }
        *this->LongDoubleValue = static_cast<long double>(value);
        break;
    }

    return *this;
}
IMGUI_VARIABLE_POITER_DATA& IMGUI_VARIABLE_POITER_DATA::operator=(short value)
{
    switch (VariableType)
    {
    case IMGUI_VARIABLE_TYPE::CHAR:
        if (this->CharValue == nullptr) { break; }
        *this->CharValue = static_cast<char>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_CHAR:
        if (this->UnsignedCharValue == nullptr) { break; }
        *this->UnsignedCharValue = static_cast<unsigned char>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::SHORT:
        if (this->ShortValue == nullptr) { break; }
        *this->ShortValue = static_cast<short>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_SHORT:
        if (this->UnsignedShortValue == nullptr) { break; }
        *this->UnsignedShortValue = static_cast<unsigned short>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::INT:
        if (this->IntValue == nullptr) { break; }
        *this->IntValue = static_cast<int>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_INT:
        if (this->UnsignedIntValue == nullptr) { break; }
        *this->UnsignedIntValue = static_cast<unsigned int>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG:
        if (this->LongValue == nullptr) { break; }
        *this->LongValue = static_cast<long>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG:
        if (this->UnsignedLongValue == nullptr) { break; }
        *this->UnsignedLongValue = static_cast<unsigned long>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_LONG:
        if (this->LongLongValue == nullptr) { break; }
        *this->LongLongValue = static_cast<long long>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_long_LONG:
        if (this->UnsignedLongLongValue == nullptr) { break; }
        *this->UnsignedLongLongValue = static_cast<unsigned long long>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::FLOAT:
        if (this->FloatValue == nullptr) { break; }
        *this->FloatValue = static_cast<float>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::DOUBLE:
        if (this->DoubleValue == nullptr) { break; }
        *this->DoubleValue = static_cast<double>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_DOUBLE:
        if (this->LongDoubleValue == nullptr) { break; }
        *this->LongDoubleValue = static_cast<long double>(value);
        break;
    }

    return *this;
}
IMGUI_VARIABLE_POITER_DATA& IMGUI_VARIABLE_POITER_DATA::operator=(int value)
{
    switch (VariableType)
    {
    case IMGUI_VARIABLE_TYPE::CHAR:
        if (this->CharValue == nullptr) { break; }
        *this->CharValue = static_cast<char>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_CHAR:
        if (this->UnsignedCharValue == nullptr) { break; }
        *this->UnsignedCharValue = static_cast<unsigned char>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::SHORT:
        if (this->ShortValue == nullptr) { break; }
        *this->ShortValue = static_cast<short>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_SHORT:
        if (this->UnsignedShortValue == nullptr) { break; }
        *this->UnsignedShortValue = static_cast<unsigned short>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::INT:
        if (this->IntValue == nullptr) { break; }
        *this->IntValue = static_cast<int>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_INT:
        if (this->UnsignedIntValue == nullptr) { break; }
        *this->UnsignedIntValue = static_cast<unsigned int>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG:
        if (this->LongValue == nullptr) { break; }
        *this->LongValue = static_cast<long>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG:
        if (this->UnsignedLongValue == nullptr) { break; }
        *this->UnsignedLongValue = static_cast<unsigned long>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_LONG:
        if (this->LongLongValue == nullptr) { break; }
        *this->LongLongValue = static_cast<long long>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_long_LONG:
        if (this->UnsignedLongLongValue == nullptr) { break; }
        *this->UnsignedLongLongValue = static_cast<unsigned long long>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::FLOAT:
        if (this->FloatValue == nullptr) { break; }
        *this->FloatValue = static_cast<float>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::DOUBLE:
        if (this->DoubleValue == nullptr) { break; }
        *this->DoubleValue = static_cast<double>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_DOUBLE:
        if (this->LongDoubleValue == nullptr) { break; }
        *this->LongDoubleValue = static_cast<long double>(value);
        break;
    }

    return *this;
}
IMGUI_VARIABLE_POITER_DATA& IMGUI_VARIABLE_POITER_DATA::operator=(long value)
{
    switch (VariableType)
    {
    case IMGUI_VARIABLE_TYPE::CHAR:
        if (this->CharValue == nullptr) { break; }
        *this->CharValue = static_cast<char>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_CHAR:
        if (this->UnsignedCharValue == nullptr) { break; }
        *this->UnsignedCharValue = static_cast<unsigned char>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::SHORT:
        if (this->ShortValue == nullptr) { break; }
        *this->ShortValue = static_cast<short>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_SHORT:
        if (this->UnsignedShortValue == nullptr) { break; }
        *this->UnsignedShortValue = static_cast<unsigned short>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::INT:
        if (this->IntValue == nullptr) { break; }
        *this->IntValue = static_cast<int>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_INT:
        if (this->UnsignedIntValue == nullptr) { break; }
        *this->UnsignedIntValue = static_cast<unsigned int>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG:
        if (this->LongValue == nullptr) { break; }
        *this->LongValue = static_cast<long>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG:
        if (this->UnsignedLongValue == nullptr) { break; }
        *this->UnsignedLongValue = static_cast<unsigned long>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_LONG:
        if (this->LongLongValue == nullptr) { break; }
        *this->LongLongValue = static_cast<long long>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_long_LONG:
        if (this->UnsignedLongLongValue == nullptr) { break; }
        *this->UnsignedLongLongValue = static_cast<unsigned long long>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::FLOAT:
        if (this->FloatValue == nullptr) { break; }
        *this->FloatValue = static_cast<float>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::DOUBLE:
        if (this->DoubleValue == nullptr) { break; }
        *this->DoubleValue = static_cast<double>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_DOUBLE:
        if (this->LongDoubleValue == nullptr) { break; }
        *this->LongDoubleValue = static_cast<long double>(value);
        break;
    }

    return *this;
}
IMGUI_VARIABLE_POITER_DATA& IMGUI_VARIABLE_POITER_DATA::operator=(long value)
{
    switch (VariableType)
    {
    case IMGUI_VARIABLE_TYPE::CHAR:
        if (this->CharValue == nullptr) { break; }
        *this->CharValue = static_cast<char>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_CHAR:
        if (this->UnsignedCharValue == nullptr) { break; }
        *this->UnsignedCharValue = static_cast<unsigned char>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::SHORT:
        if (this->ShortValue == nullptr) { break; }
        *this->ShortValue = static_cast<short>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_SHORT:
        if (this->UnsignedShortValue == nullptr) { break; }
        *this->UnsignedShortValue = static_cast<unsigned short>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::INT:
        if (this->IntValue == nullptr) { break; }
        *this->IntValue = static_cast<int>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_INT:
        if (this->UnsignedIntValue == nullptr) { break; }
        *this->UnsignedIntValue = static_cast<unsigned int>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG:
        if (this->LongValue == nullptr) { break; }
        *this->LongValue = static_cast<long>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG:
        if (this->UnsignedLongValue == nullptr) { break; }
        *this->UnsignedLongValue = static_cast<unsigned long>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_LONG:
        if (this->LongLongValue == nullptr) { break; }
        *this->LongLongValue = static_cast<long long>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_long_LONG:
        if (this->UnsignedLongLongValue == nullptr) { break; }
        *this->UnsignedLongLongValue = static_cast<unsigned long long>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::FLOAT:
        if (this->FloatValue == nullptr) { break; }
        *this->FloatValue = static_cast<float>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::DOUBLE:
        if (this->DoubleValue == nullptr) { break; }
        *this->DoubleValue = static_cast<double>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_DOUBLE:
        if (this->LongDoubleValue == nullptr) { break; }
        *this->LongDoubleValue = static_cast<long double>(value);
        break;
    }

    return *this;
}
IMGUI_VARIABLE_POITER_DATA& IMGUI_VARIABLE_POITER_DATA::operator=(float value)
{
    switch (VariableType)
    {
    case IMGUI_VARIABLE_TYPE::CHAR:
        if (this->CharValue == nullptr) { break; }
        *this->CharValue = static_cast<char>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_CHAR:
        if (this->UnsignedCharValue == nullptr) { break; }
        *this->UnsignedCharValue = static_cast<unsigned char>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::SHORT:
        if (this->ShortValue == nullptr) { break; }
        *this->ShortValue = static_cast<short>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_SHORT:
        if (this->UnsignedShortValue == nullptr) { break; }
        *this->UnsignedShortValue = static_cast<unsigned short>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::INT:
        if (this->IntValue == nullptr) { break; }
        *this->IntValue = static_cast<int>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_INT:
        if (this->UnsignedIntValue == nullptr) { break; }
        *this->UnsignedIntValue = static_cast<unsigned int>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG:
        if (this->LongValue == nullptr) { break; }
        *this->LongValue = static_cast<long>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG:
        if (this->UnsignedLongValue == nullptr) { break; }
        *this->UnsignedLongValue = static_cast<unsigned long>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_LONG:
        if (this->LongLongValue == nullptr) { break; }
        *this->LongLongValue = static_cast<long long>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_long_LONG:
        if (this->UnsignedLongLongValue == nullptr) { break; }
        *this->UnsignedLongLongValue = static_cast<unsigned long long>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::FLOAT:
        if (this->FloatValue == nullptr) { break; }
        *this->FloatValue = static_cast<float>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::DOUBLE:
        if (this->DoubleValue == nullptr) { break; }
        *this->DoubleValue = static_cast<double>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_DOUBLE:
        if (this->LongDoubleValue == nullptr) { break; }
        *this->LongDoubleValue = static_cast<long double>(value);
        break;
    }

    return *this;
}
IMGUI_VARIABLE_POITER_DATA& IMGUI_VARIABLE_POITER_DATA::operator=(double value)
{
    switch (VariableType)
    {
    case IMGUI_VARIABLE_TYPE::CHAR:
        if (this->CharValue == nullptr) { break; }
        *this->CharValue = static_cast<char>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_CHAR:
        if (this->UnsignedCharValue == nullptr) { break; }
        *this->UnsignedCharValue = static_cast<unsigned char>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::SHORT:
        if (this->ShortValue == nullptr) { break; }
        *this->ShortValue = static_cast<short>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_SHORT:
        if (this->UnsignedShortValue == nullptr) { break; }
        *this->UnsignedShortValue = static_cast<unsigned short>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::INT:
        if (this->IntValue == nullptr) { break; }
        *this->IntValue = static_cast<int>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_INT:
        if (this->UnsignedIntValue == nullptr) { break; }
        *this->UnsignedIntValue = static_cast<unsigned int>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG:
        if (this->LongValue == nullptr) { break; }
        *this->LongValue = static_cast<long>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG:
        if (this->UnsignedLongValue == nullptr) { break; }
        *this->UnsignedLongValue = static_cast<unsigned long>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_LONG:
        if (this->LongLongValue == nullptr) { break; }
        *this->LongLongValue = static_cast<long long>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_long_LONG:
        if (this->UnsignedLongLongValue == nullptr) { break; }
        *this->UnsignedLongLongValue = static_cast<unsigned long long>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::FLOAT:
        if (this->FloatValue == nullptr) { break; }
        *this->FloatValue = static_cast<float>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::DOUBLE:
        if (this->DoubleValue == nullptr) { break; }
        *this->DoubleValue = static_cast<double>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_DOUBLE:
        if (this->LongDoubleValue == nullptr) { break; }
        *this->LongDoubleValue = static_cast<long double>(value);
        break;
    }

    return *this;
}

// 値の取得
void IMGUI_VARIABLE_POITER_DATA::GetValueToChar(char& charValue) const
{
    switch (VariableType)
    {
    case IMGUI_VARIABLE_TYPE::CHAR:
        if (this->CharValue == nullptr) { break; }
        charValue = static_cast<char>(*this->CharValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_CHAR:
        if (this->UnsignedCharValue == nullptr) { break; }
        charValue = static_cast<char>(*this->UnsignedCharValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::SHORT:
        if (this->ShortValue == nullptr) { break; }
        charValue = static_cast<char>(*this->ShortValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_SHORT:
        if (this->UnsignedShortValue == nullptr) { break; }
        charValue = static_cast<char>(*this->UnsignedShortValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::INT:
        if (this->IntValue == nullptr) { break; }
        charValue = static_cast<char>(*this->IntValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_INT:
        if (this->UnsignedIntValue == nullptr) { break; }
        charValue = static_cast<char>(*this->UnsignedIntValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG:
        if (this->LongValue == nullptr) { break; }
        charValue = static_cast<char>(*this->LongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG:
        if (this->UnsignedLongValue == nullptr) { break; }
        charValue = static_cast<char>(*this->UnsignedLongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_LONG:
        if (this->LongLongValue == nullptr) { break; }
        charValue = static_cast<char>(*this->LongLongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_long_LONG:
        if (this->UnsignedLongLongValue == nullptr) { break; }
        charValue = static_cast<char>(*this->UnsignedLongLongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::FLOAT:
        if (this->FloatValue == nullptr) { break; }
        charValue = static_cast<char>(*this->FloatValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::DOUBLE:
        if (this->DoubleValue == nullptr) { break; }
        charValue = static_cast<char>(*this->DoubleValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_DOUBLE:
        if (this->LongDoubleValue == nullptr) { break; }
        charValue = static_cast<char>(*this->LongDoubleValue);
        break;
    }
}

void IMGUI_VARIABLE_POITER_DATA::GetValueToShort(short& shortValue) const
{
    switch (VariableType)
    {
    case IMGUI_VARIABLE_TYPE::CHAR:
        if (this->CharValue == nullptr) { break; }
        shortValue = static_cast<short>(*this->CharValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_CHAR:
        if (this->UnsignedCharValue == nullptr) { break; }
        shortValue = static_cast<short>(*this->UnsignedCharValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::SHORT:
        if (this->ShortValue == nullptr) { break; }
        shortValue = static_cast<short>(*this->ShortValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_SHORT:
        if (this->UnsignedShortValue == nullptr) { break; }
        shortValue = static_cast<short>(*this->UnsignedShortValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::INT:
        if (this->IntValue == nullptr) { break; }
        shortValue = static_cast<short>(*this->IntValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_INT:
        if (this->UnsignedIntValue == nullptr) { break; }
        shortValue = static_cast<short>(*this->UnsignedIntValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG:
        if (this->LongValue == nullptr) { break; }
        shortValue = static_cast<short>(*this->LongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG:
        if (this->UnsignedLongValue == nullptr) { break; }
        shortValue = static_cast<short>(*this->UnsignedLongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_LONG:
        if (this->LongLongValue == nullptr) { break; }
        shortValue = static_cast<short>(*this->LongLongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_long_LONG:
        if (this->UnsignedLongLongValue == nullptr) { break; }
        shortValue = static_cast<short>(*this->UnsignedLongLongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::FLOAT:
        if (this->FloatValue == nullptr) { break; }
        shortValue = static_cast<short>(*this->FloatValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::DOUBLE:
        if (this->DoubleValue == nullptr) { break; }
        shortValue = static_cast<short>(*this->DoubleValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_DOUBLE:
        if (this->LongDoubleValue == nullptr) { break; }
        shortValue = static_cast<short>(*this->LongDoubleValue);
        break;
    }
}

void IMGUI_VARIABLE_POITER_DATA::GetValueToInt(int& intValue) const
{
    switch (VariableType)
    {
    case IMGUI_VARIABLE_TYPE::CHAR:
        if (this->CharValue == nullptr) { break; }
        intValue = static_cast<int>(*this->CharValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_CHAR:
        if (this->UnsignedCharValue == nullptr) { break; }
        intValue = static_cast<int>(*this->UnsignedCharValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::SHORT:
        if (this->ShortValue == nullptr) { break; }
        intValue = static_cast<int>(*this->ShortValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_SHORT:
        if (this->UnsignedShortValue == nullptr) { break; }
        intValue = static_cast<int>(*this->UnsignedShortValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::INT:
        if (this->IntValue == nullptr) { break; }
        intValue = static_cast<int>(*this->IntValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_INT:
        if (this->UnsignedIntValue == nullptr) { break; }
        intValue = static_cast<int>(*this->UnsignedIntValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG:
        if (this->LongValue == nullptr) { break; }
        intValue = static_cast<int>(*this->LongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG:
        if (this->UnsignedLongValue == nullptr) { break; }
        intValue = static_cast<int>(*this->UnsignedLongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_LONG:
        if (this->LongLongValue == nullptr) { break; }
        intValue = static_cast<int>(*this->LongLongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_long_LONG:
        if (this->UnsignedLongLongValue == nullptr) { break; }
        intValue = static_cast<int>(*this->UnsignedLongLongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::FLOAT:
        if (this->FloatValue == nullptr) { break; }
        intValue = static_cast<int>(*this->FloatValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::DOUBLE:
        if (this->DoubleValue == nullptr) { break; }
        intValue = static_cast<int>(*this->DoubleValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_DOUBLE:
        if (this->LongDoubleValue == nullptr) { break; }
        intValue = static_cast<int>(*this->LongDoubleValue);
        break;
    }
}

void IMGUI_VARIABLE_POITER_DATA::GetValueToLong(long& longValue) const
{
    switch (VariableType)
    {
    case IMGUI_VARIABLE_TYPE::CHAR:
        if (this->CharValue == nullptr) { break; }
        longValue = static_cast<long>(*this->CharValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_CHAR:
        if (this->UnsignedCharValue == nullptr) { break; }
        longValue = static_cast<long>(*this->UnsignedCharValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::SHORT:
        if (this->ShortValue == nullptr) { break; }
        longValue = static_cast<long>(*this->ShortValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_SHORT:
        if (this->UnsignedShortValue == nullptr) { break; }
        longValue = static_cast<long>(*this->UnsignedShortValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::INT:
        if (this->IntValue == nullptr) { break; }
        longValue = static_cast<long>(*this->IntValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_INT:
        if (this->UnsignedIntValue == nullptr) { break; }
        longValue = static_cast<long>(*this->UnsignedIntValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG:
        if (this->LongValue == nullptr) { break; }
        longValue = static_cast<long>(*this->LongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG:
        if (this->UnsignedLongValue == nullptr) { break; }
        longValue = static_cast<long>(*this->UnsignedLongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_LONG:
        if (this->LongLongValue == nullptr) { break; }
        longValue = static_cast<long>(*this->LongLongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_long_LONG:
        if (this->UnsignedLongLongValue == nullptr) { break; }
        longValue = static_cast<long>(*this->UnsignedLongLongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::FLOAT:
        if (this->FloatValue == nullptr) { break; }
        longValue = static_cast<long>(*this->FloatValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::DOUBLE:
        if (this->DoubleValue == nullptr) { break; }
        longValue = static_cast<long>(*this->DoubleValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_DOUBLE:
        if (this->LongDoubleValue == nullptr) { break; }
        longValue = static_cast<long>(*this->LongDoubleValue);
        break;
    }
}

void IMGUI_VARIABLE_POITER_DATA::GetValueToLongLong(long long& longlongValue) const
{
    switch (VariableType)
    {
    case IMGUI_VARIABLE_TYPE::CHAR:
        if (this->CharValue == nullptr) { break; }
        longlongValue = static_cast<long long>(*this->CharValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_CHAR:
        if (this->UnsignedCharValue == nullptr) { break; }
        longlongValue = static_cast<long long>(*this->UnsignedCharValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::SHORT:
        if (this->ShortValue == nullptr) { break; }
        longlongValue = static_cast<long long>(*this->ShortValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_SHORT:
        if (this->UnsignedShortValue == nullptr) { break; }
        longlongValue = static_cast<long long>(*this->UnsignedShortValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::INT:
        if (this->IntValue == nullptr) { break; }
        longlongValue = static_cast<long long>(*this->IntValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_INT:
        if (this->UnsignedIntValue == nullptr) { break; }
        longlongValue = static_cast<long long>(*this->UnsignedIntValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG:
        if (this->LongValue == nullptr) { break; }
        longlongValue = static_cast<long long>(*this->LongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG:
        if (this->UnsignedLongValue == nullptr) { break; }
        longlongValue = static_cast<long long>(*this->UnsignedLongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_LONG:
        if (this->LongLongValue == nullptr) { break; }
        longlongValue = static_cast<long long>(*this->LongLongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_long_LONG:
        if (this->UnsignedLongLongValue == nullptr) { break; }
        longlongValue = static_cast<long long>(*this->UnsignedLongLongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::FLOAT:
        if (this->FloatValue == nullptr) { break; }
        longlongValue = static_cast<long long>(*this->FloatValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::DOUBLE:
        if (this->DoubleValue == nullptr) { break; }
        longlongValue = static_cast<long long>(*this->DoubleValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_DOUBLE:
        if (this->LongDoubleValue == nullptr) { break; }
        longlongValue = static_cast<long long>(*this->LongDoubleValue);
        break;
    }
}

void IMGUI_VARIABLE_POITER_DATA::GetValueToFloat(float& floatValue) const
{
    switch (VariableType)
    {
    case IMGUI_VARIABLE_TYPE::CHAR:
        if (this->CharValue == nullptr) { break; }
        floatValue = static_cast<float>(*this->CharValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_CHAR:
        if (this->UnsignedCharValue == nullptr) { break; }
        floatValue = static_cast<float>(*this->UnsignedCharValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::SHORT:
        if (this->ShortValue == nullptr) { break; }
        floatValue = static_cast<float>(*this->ShortValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_SHORT:
        if (this->UnsignedShortValue == nullptr) { break; }
        floatValue = static_cast<float>(*this->UnsignedShortValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::INT:
        if (this->IntValue == nullptr) { break; }
        floatValue = static_cast<float>(*this->IntValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_INT:
        if (this->UnsignedIntValue == nullptr) { break; }
        floatValue = static_cast<float>(*this->UnsignedIntValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG:
        if (this->LongValue == nullptr) { break; }
        floatValue = static_cast<float>(*this->LongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG:
        if (this->UnsignedLongValue == nullptr) { break; }
        floatValue = static_cast<float>(*this->UnsignedLongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_LONG:
        if (this->LongLongValue == nullptr) { break; }
        floatValue = static_cast<float>(*this->LongLongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_long_LONG:
        if (this->UnsignedLongLongValue == nullptr) { break; }
        floatValue = static_cast<float>(*this->UnsignedLongLongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::FLOAT:
        if (this->FloatValue == nullptr) { break; }
        floatValue = static_cast<float>(*this->FloatValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::DOUBLE:
        if (this->DoubleValue == nullptr) { break; }
        floatValue = static_cast<float>(*this->DoubleValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_DOUBLE:
        if (this->LongDoubleValue == nullptr) { break; }
        floatValue = static_cast<float>(*this->LongDoubleValue);
        break;
    }
}

void IMGUI_VARIABLE_POITER_DATA::GetValueToDouble(double& doubleValue) const
{
    switch (VariableType)
    {
    case IMGUI_VARIABLE_TYPE::CHAR:
        if (this->CharValue == nullptr) { break; }
        doubleValue = static_cast<double>(*this->CharValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_CHAR:
        if (this->UnsignedCharValue == nullptr) { break; }
        doubleValue = static_cast<double>(*this->UnsignedCharValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::SHORT:
        if (this->ShortValue == nullptr) { break; }
        doubleValue = static_cast<double>(*this->ShortValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_SHORT:
        if (this->UnsignedShortValue == nullptr) { break; }
        doubleValue = static_cast<double>(*this->UnsignedShortValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::INT:
        if (this->IntValue == nullptr) { break; }
        doubleValue = static_cast<double>(*this->IntValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_INT:
        if (this->UnsignedIntValue == nullptr) { break; }
        doubleValue = static_cast<double>(*this->UnsignedIntValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG:
        if (this->LongValue == nullptr) { break; }
        doubleValue = static_cast<double>(*this->LongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG:
        if (this->UnsignedLongValue == nullptr) { break; }
        doubleValue = static_cast<double>(*this->UnsignedLongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_LONG:
        if (this->LongLongValue == nullptr) { break; }
        doubleValue = static_cast<double>(*this->LongLongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_long_LONG:
        if (this->UnsignedLongLongValue == nullptr) { break; }
        doubleValue = static_cast<double>(*this->UnsignedLongLongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::FLOAT:
        if (this->FloatValue == nullptr) { break; }
        doubleValue = static_cast<double>(*this->FloatValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::DOUBLE:
        if (this->DoubleValue == nullptr) { break; }
        doubleValue = static_cast<double>(*this->DoubleValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_DOUBLE:
        if (this->LongDoubleValue == nullptr) { break; }
        doubleValue = static_cast<double>(*this->LongDoubleValue);
        break;
    }
}


// インクリメント・デクリメント
IMGUI_VARIABLE_POITER_DATA& IMGUI_VARIABLE_POITER_DATA::operator++()
{
    switch (VariableType)
    {
    case IMGUI_VARIABLE_TYPE::CHAR:
        if (this->CharValue == nullptr) { break; }
        this->CharValue++;
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_CHAR:
        if (this->UnsignedCharValue == nullptr) { break; }
        this->UnsignedCharValue++;
        break;
        
    case IMGUI_VARIABLE_TYPE::SHORT:
        if (this->ShortValue == nullptr) { break; }
        this->ShortValue++;
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_SHORT:
        if (this->UnsignedShortValue == nullptr) { break; }
        this->UnsignedShortValue++;
        break;
        
    case IMGUI_VARIABLE_TYPE::INT:
        if (this->IntValue == nullptr) { break; }
        this->IntValue++;
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_INT:
        if (this->UnsignedIntValue == nullptr) { break; }
        this->UnsignedIntValue++;
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG:
        if (this->LongValue == nullptr) { break; }
        this->LongValue++;
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG:
        if (this->UnsignedLongValue == nullptr) { break; }
        this->UnsignedLongValue++;
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_LONG:
        if (this->LongLongValue == nullptr) { break; }
        this->LongLongValue++;
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_long_LONG:
        if (this->UnsignedLongLongValue == nullptr) { break; }
        this->UnsignedLongLongValue++;
        break;
        
    case IMGUI_VARIABLE_TYPE::FLOAT:
        if (this->FloatValue == nullptr) { break; }
        this->FloatValue++;
        break;
        
    case IMGUI_VARIABLE_TYPE::DOUBLE:
        if (this->DoubleValue == nullptr) { break; }
        this->DoubleValue++;
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_DOUBLE:
        if (this->LongDoubleValue == nullptr) { break; }
        this->LongDoubleValue++;
        break;
    }

    return *this;
}

IMGUI_VARIABLE_POITER_DATA& IMGUI_VARIABLE_POITER_DATA::operator--()
{
    switch (VariableType)
    {
    case IMGUI_VARIABLE_TYPE::CHAR:
        if (this->CharValue == nullptr) { break; }
        this->CharValue--;
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_CHAR:
        if (this->UnsignedCharValue == nullptr) { break; }
        this->UnsignedCharValue--;
        break;
        
    case IMGUI_VARIABLE_TYPE::SHORT:
        if (this->ShortValue == nullptr) { break; }
        this->ShortValue--;
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_SHORT:
        if (this->UnsignedShortValue == nullptr) { break; }
        this->UnsignedShortValue--;
        break;
        
    case IMGUI_VARIABLE_TYPE::INT:
        if (this->IntValue == nullptr) { break; }
        this->IntValue--;
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_INT:
        if (this->UnsignedIntValue == nullptr) { break; }
        this->UnsignedIntValue--;
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG:
        if (this->LongValue == nullptr) { break; }
        this->LongValue--;
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG:
        if (this->UnsignedLongValue == nullptr) { break; }
        this->UnsignedLongValue--;
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_LONG:
        if (this->LongLongValue == nullptr) { break; }
        this->LongLongValue--;
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_long_LONG:
        if (this->UnsignedLongLongValue == nullptr) { break; }
        this->UnsignedLongLongValue--;
        break;
        
    case IMGUI_VARIABLE_TYPE::FLOAT:
        if (this->FloatValue == nullptr) { break; }
        this->FloatValue--;
        break;
        
    case IMGUI_VARIABLE_TYPE::DOUBLE:
        if (this->DoubleValue == nullptr) { break; }
        this->DoubleValue--;
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_DOUBLE:
        if (this->LongDoubleValue == nullptr) { break; }
        this->LongDoubleValue--;
        break;
    }

    return *this;
}


const void* IMGUI_VARIABLE_POITER_DATA::GetPointer() const
{
    switch (VariableType)
    {
    case IMGUI_VARIABLE_TYPE::CHAR:
        if (this->CharValue == nullptr) { break; }
        return this->CharValue;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_CHAR:
        if (this->UnsignedCharValue == nullptr) { break; }
        return this->UnsignedCharValue;
        
    case IMGUI_VARIABLE_TYPE::SHORT:
        if (this->ShortValue == nullptr) { break; }
        return this->ShortValue;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_SHORT:
        if (this->UnsignedShortValue == nullptr) { break; }
        return this->UnsignedShortValue;
        
    case IMGUI_VARIABLE_TYPE::INT:
        if (this->IntValue == nullptr) { break; }
        return this->IntValue;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_INT:
        if (this->UnsignedIntValue == nullptr) { break; }
        return this->UnsignedIntValue;
        
    case IMGUI_VARIABLE_TYPE::LONG:
        if (this->LongValue == nullptr) { break; }
        return this->LongValue;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG:
        if (this->UnsignedLongValue == nullptr) { break; }
        return this->UnsignedLongValue;
        
    case IMGUI_VARIABLE_TYPE::LONG_LONG:
        if (this->LongLongValue == nullptr) { break; }
        return this->LongLongValue;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_long_LONG:
        if (this->UnsignedLongLongValue == nullptr) { break; }
        return this->UnsignedLongLongValue;
        
    case IMGUI_VARIABLE_TYPE::FLOAT:
        if (this->FloatValue == nullptr) { break; }
        return this->FloatValue;
        
    case IMGUI_VARIABLE_TYPE::DOUBLE:
        if (this->DoubleValue == nullptr) { break; }
        return this->DoubleValue;
        
    case IMGUI_VARIABLE_TYPE::LONG_DOUBLE:
        if (this->LongDoubleValue == nullptr) { break; }
        return this->LongDoubleValue;
    }

    return nullptr;
}