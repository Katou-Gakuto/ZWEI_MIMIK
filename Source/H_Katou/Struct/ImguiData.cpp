#include "ImguiData.h"

/*-----------------------------------------------------------------------*/
/*                         変数データ(ポインタ)                          */
/*-----------------------------------------------------------------------*/

// コンストラクタ
IMGUI_VARIABLE_POITER_DATA::IMGUI_VARIABLE_POITER_DATA()
: VariableType(IMGUI_VARIABLE_TYPE::NONE)
, CharValue(nullptr)
{
}
IMGUI_VARIABLE_POITER_DATA::IMGUI_VARIABLE_POITER_DATA(char* value, IMGUI_VARIABLE_TYPE variableType)
: VariableType(variableType)
{
    switch (variableType)
    {
    case IMGUI_VARIABLE_TYPE::CHAR:
        this->CharValue = reinterpret_cast<char*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_CHAR:
        this->UnsignedCharValue = reinterpret_cast<unsigned char*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::SHORT:
        this->ShortValue = reinterpret_cast<short*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_SHORT:
        this->UnsignedShortValue = reinterpret_cast<unsigned short*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::INT:
        this->IntValue = reinterpret_cast<int*>(value);
        break;
    
    case IMGUI_VARIABLE_TYPE::UNSIGNED_INT:
        this->UnsignedIntValue = reinterpret_cast<unsigned int*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::LONG:
        this->LongValue = reinterpret_cast<long*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG:
        this->UnsignedLongValue = reinterpret_cast<unsigned long*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::LONG_LONG:
        this->LongLongValue = reinterpret_cast<long long*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG_LONG:
        this->UnsignedLongLongValue = reinterpret_cast<unsigned long long*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::FLOAT:
        this->FloatValue = reinterpret_cast<float*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::DOUBLE:
        this->DoubleValue = reinterpret_cast<double*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::LONG_DOUBLE:
        this->LongDoubleValue = reinterpret_cast<long double*>(value);
        break;
    }
}
IMGUI_VARIABLE_POITER_DATA::IMGUI_VARIABLE_POITER_DATA(unsigned char* value, IMGUI_VARIABLE_TYPE variableType)
: VariableType(variableType)
{
    switch (variableType)
    {
    case IMGUI_VARIABLE_TYPE::CHAR:
        this->CharValue = reinterpret_cast<char*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_CHAR:
        this->UnsignedCharValue = reinterpret_cast<unsigned char*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::SHORT:
        this->ShortValue = reinterpret_cast<short*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_SHORT:
        this->UnsignedShortValue = reinterpret_cast<unsigned short*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::INT:
        this->IntValue = reinterpret_cast<int*>(value);
        break;
    
    case IMGUI_VARIABLE_TYPE::UNSIGNED_INT:
        this->UnsignedIntValue = reinterpret_cast<unsigned int*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::LONG:
        this->LongValue = reinterpret_cast<long*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG:
        this->UnsignedLongValue = reinterpret_cast<unsigned long*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::LONG_LONG:
        this->LongLongValue = reinterpret_cast<long long*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG_LONG:
        this->UnsignedLongLongValue = reinterpret_cast<unsigned long long*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::FLOAT:
        this->FloatValue = reinterpret_cast<float*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::DOUBLE:
        this->DoubleValue = reinterpret_cast<double*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::LONG_DOUBLE:
        this->LongDoubleValue = reinterpret_cast<long double*>(value);
        break;
    }
}
IMGUI_VARIABLE_POITER_DATA::IMGUI_VARIABLE_POITER_DATA(short* value, IMGUI_VARIABLE_TYPE variableType)
: VariableType(variableType)
{
    switch (variableType)
    {
    case IMGUI_VARIABLE_TYPE::CHAR:
        this->CharValue = reinterpret_cast<char*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_CHAR:
        this->UnsignedCharValue = reinterpret_cast<unsigned char*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::SHORT:
        this->ShortValue = reinterpret_cast<short*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_SHORT:
        this->UnsignedShortValue = reinterpret_cast<unsigned short*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::INT:
        this->IntValue = reinterpret_cast<int*>(value);
        break;
    
    case IMGUI_VARIABLE_TYPE::UNSIGNED_INT:
        this->UnsignedIntValue = reinterpret_cast<unsigned int*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::LONG:
        this->LongValue = reinterpret_cast<long*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG:
        this->UnsignedLongValue = reinterpret_cast<unsigned long*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::LONG_LONG:
        this->LongLongValue = reinterpret_cast<long long*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG_LONG:
        this->UnsignedLongLongValue = reinterpret_cast<unsigned long long*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::FLOAT:
        this->FloatValue = reinterpret_cast<float*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::DOUBLE:
        this->DoubleValue = reinterpret_cast<double*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::LONG_DOUBLE:
        this->LongDoubleValue = reinterpret_cast<long double*>(value);
        break;
    }
}
IMGUI_VARIABLE_POITER_DATA::IMGUI_VARIABLE_POITER_DATA(unsigned short* value, IMGUI_VARIABLE_TYPE variableType)
: VariableType(variableType)
{
    switch (variableType)
    {
    case IMGUI_VARIABLE_TYPE::CHAR:
        this->CharValue = reinterpret_cast<char*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_CHAR:
        this->UnsignedCharValue = reinterpret_cast<unsigned char*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::SHORT:
        this->ShortValue = reinterpret_cast<short*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_SHORT:
        this->UnsignedShortValue = reinterpret_cast<unsigned short*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::INT:
        this->IntValue = reinterpret_cast<int*>(value);
        break;
    
    case IMGUI_VARIABLE_TYPE::UNSIGNED_INT:
        this->UnsignedIntValue = reinterpret_cast<unsigned int*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::LONG:
        this->LongValue = reinterpret_cast<long*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG:
        this->UnsignedLongValue = reinterpret_cast<unsigned long*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::LONG_LONG:
        this->LongLongValue = reinterpret_cast<long long*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG_LONG:
        this->UnsignedLongLongValue = reinterpret_cast<unsigned long long*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::FLOAT:
        this->FloatValue = reinterpret_cast<float*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::DOUBLE:
        this->DoubleValue = reinterpret_cast<double*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::LONG_DOUBLE:
        this->LongDoubleValue = reinterpret_cast<long double*>(value);
        break;
    }
}
IMGUI_VARIABLE_POITER_DATA::IMGUI_VARIABLE_POITER_DATA(int* value, IMGUI_VARIABLE_TYPE variableType)
: VariableType(variableType)
{
    switch (variableType)
    {
    case IMGUI_VARIABLE_TYPE::CHAR:
        this->CharValue = reinterpret_cast<char*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_CHAR:
        this->UnsignedCharValue = reinterpret_cast<unsigned char*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::SHORT:
        this->ShortValue = reinterpret_cast<short*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_SHORT:
        this->UnsignedShortValue = reinterpret_cast<unsigned short*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::INT:
        this->IntValue = reinterpret_cast<int*>(value);
        break;
    
    case IMGUI_VARIABLE_TYPE::UNSIGNED_INT:
        this->UnsignedIntValue = reinterpret_cast<unsigned int*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::LONG:
        this->LongValue = reinterpret_cast<long*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG:
        this->UnsignedLongValue = reinterpret_cast<unsigned long*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::LONG_LONG:
        this->LongLongValue = reinterpret_cast<long long*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG_LONG:
        this->UnsignedLongLongValue = reinterpret_cast<unsigned long long*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::FLOAT:
        this->FloatValue = reinterpret_cast<float*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::DOUBLE:
        this->DoubleValue = reinterpret_cast<double*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::LONG_DOUBLE:
        this->LongDoubleValue = reinterpret_cast<long double*>(value);
        break;
    }
}
IMGUI_VARIABLE_POITER_DATA::IMGUI_VARIABLE_POITER_DATA(unsigned int* value, IMGUI_VARIABLE_TYPE variableType)
: VariableType(variableType)
{
    switch (variableType)
    {
    case IMGUI_VARIABLE_TYPE::CHAR:
        this->CharValue = reinterpret_cast<char*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_CHAR:
        this->UnsignedCharValue = reinterpret_cast<unsigned char*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::SHORT:
        this->ShortValue = reinterpret_cast<short*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_SHORT:
        this->UnsignedShortValue = reinterpret_cast<unsigned short*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::INT:
        this->IntValue = reinterpret_cast<int*>(value);
        break;
    
    case IMGUI_VARIABLE_TYPE::UNSIGNED_INT:
        this->UnsignedIntValue = reinterpret_cast<unsigned int*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::LONG:
        this->LongValue = reinterpret_cast<long*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG:
        this->UnsignedLongValue = reinterpret_cast<unsigned long*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::LONG_LONG:
        this->LongLongValue = reinterpret_cast<long long*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG_LONG:
        this->UnsignedLongLongValue = reinterpret_cast<unsigned long long*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::FLOAT:
        this->FloatValue = reinterpret_cast<float*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::DOUBLE:
        this->DoubleValue = reinterpret_cast<double*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::LONG_DOUBLE:
        this->LongDoubleValue = reinterpret_cast<long double*>(value);
        break;
    }
}
IMGUI_VARIABLE_POITER_DATA::IMGUI_VARIABLE_POITER_DATA(long* value, IMGUI_VARIABLE_TYPE variableType)
: VariableType(variableType)
{
    switch (variableType)
    {
    case IMGUI_VARIABLE_TYPE::CHAR:
        this->CharValue = reinterpret_cast<char*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_CHAR:
        this->UnsignedCharValue = reinterpret_cast<unsigned char*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::SHORT:
        this->ShortValue = reinterpret_cast<short*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_SHORT:
        this->UnsignedShortValue = reinterpret_cast<unsigned short*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::INT:
        this->IntValue = reinterpret_cast<int*>(value);
        break;
    
    case IMGUI_VARIABLE_TYPE::UNSIGNED_INT:
        this->UnsignedIntValue = reinterpret_cast<unsigned int*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::LONG:
        this->LongValue = reinterpret_cast<long*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG:
        this->UnsignedLongValue = reinterpret_cast<unsigned long*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::LONG_LONG:
        this->LongLongValue = reinterpret_cast<long long*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG_LONG:
        this->UnsignedLongLongValue = reinterpret_cast<unsigned long long*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::FLOAT:
        this->FloatValue = reinterpret_cast<float*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::DOUBLE:
        this->DoubleValue = reinterpret_cast<double*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::LONG_DOUBLE:
        this->LongDoubleValue = reinterpret_cast<long double*>(value);
        break;
    }
}
IMGUI_VARIABLE_POITER_DATA::IMGUI_VARIABLE_POITER_DATA(unsigned long* value, IMGUI_VARIABLE_TYPE variableType)
: VariableType(variableType)
{
    switch (variableType)
    {
    case IMGUI_VARIABLE_TYPE::CHAR:
        this->CharValue = reinterpret_cast<char*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_CHAR:
        this->UnsignedCharValue = reinterpret_cast<unsigned char*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::SHORT:
        this->ShortValue = reinterpret_cast<short*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_SHORT:
        this->UnsignedShortValue = reinterpret_cast<unsigned short*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::INT:
        this->IntValue = reinterpret_cast<int*>(value);
        break;
    
    case IMGUI_VARIABLE_TYPE::UNSIGNED_INT:
        this->UnsignedIntValue = reinterpret_cast<unsigned int*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::LONG:
        this->LongValue = reinterpret_cast<long*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG:
        this->UnsignedLongValue = reinterpret_cast<unsigned long*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::LONG_LONG:
        this->LongLongValue = reinterpret_cast<long long*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG_LONG:
        this->UnsignedLongLongValue = reinterpret_cast<unsigned long long*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::FLOAT:
        this->FloatValue = reinterpret_cast<float*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::DOUBLE:
        this->DoubleValue = reinterpret_cast<double*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::LONG_DOUBLE:
        this->LongDoubleValue = reinterpret_cast<long double*>(value);
        break;
    }
}
IMGUI_VARIABLE_POITER_DATA::IMGUI_VARIABLE_POITER_DATA(long long* value, IMGUI_VARIABLE_TYPE variableType)
: VariableType(variableType)
{
    switch (variableType)
    {
    case IMGUI_VARIABLE_TYPE::CHAR:
        this->CharValue = reinterpret_cast<char*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_CHAR:
        this->UnsignedCharValue = reinterpret_cast<unsigned char*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::SHORT:
        this->ShortValue = reinterpret_cast<short*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_SHORT:
        this->UnsignedShortValue = reinterpret_cast<unsigned short*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::INT:
        this->IntValue = reinterpret_cast<int*>(value);
        break;
    
    case IMGUI_VARIABLE_TYPE::UNSIGNED_INT:
        this->UnsignedIntValue = reinterpret_cast<unsigned int*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::LONG:
        this->LongValue = reinterpret_cast<long*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG:
        this->UnsignedLongValue = reinterpret_cast<unsigned long*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::LONG_LONG:
        this->LongLongValue = reinterpret_cast<long long*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG_LONG:
        this->UnsignedLongLongValue = reinterpret_cast<unsigned long long*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::FLOAT:
        this->FloatValue = reinterpret_cast<float*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::DOUBLE:
        this->DoubleValue = reinterpret_cast<double*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::LONG_DOUBLE:
        this->LongDoubleValue = reinterpret_cast<long double*>(value);
        break;
    }
}
IMGUI_VARIABLE_POITER_DATA::IMGUI_VARIABLE_POITER_DATA(unsigned long long* value, IMGUI_VARIABLE_TYPE variableType)
: VariableType(variableType)
{
    switch (variableType)
    {
    case IMGUI_VARIABLE_TYPE::CHAR:
        this->CharValue = reinterpret_cast<char*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_CHAR:
        this->UnsignedCharValue = reinterpret_cast<unsigned char*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::SHORT:
        this->ShortValue = reinterpret_cast<short*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_SHORT:
        this->UnsignedShortValue = reinterpret_cast<unsigned short*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::INT:
        this->IntValue = reinterpret_cast<int*>(value);
        break;
    
    case IMGUI_VARIABLE_TYPE::UNSIGNED_INT:
        this->UnsignedIntValue = reinterpret_cast<unsigned int*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::LONG:
        this->LongValue = reinterpret_cast<long*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG:
        this->UnsignedLongValue = reinterpret_cast<unsigned long*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::LONG_LONG:
        this->LongLongValue = reinterpret_cast<long long*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG_LONG:
        this->UnsignedLongLongValue = reinterpret_cast<unsigned long long*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::FLOAT:
        this->FloatValue = reinterpret_cast<float*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::DOUBLE:
        this->DoubleValue = reinterpret_cast<double*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::LONG_DOUBLE:
        this->LongDoubleValue = reinterpret_cast<long double*>(value);
        break;
    }
}
IMGUI_VARIABLE_POITER_DATA::IMGUI_VARIABLE_POITER_DATA(float* value, IMGUI_VARIABLE_TYPE variableType)
: VariableType(variableType)
{
    switch (variableType)
    {
    case IMGUI_VARIABLE_TYPE::CHAR:
        this->CharValue = reinterpret_cast<char*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_CHAR:
        this->UnsignedCharValue = reinterpret_cast<unsigned char*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::SHORT:
        this->ShortValue = reinterpret_cast<short*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_SHORT:
        this->UnsignedShortValue = reinterpret_cast<unsigned short*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::INT:
        this->IntValue = reinterpret_cast<int*>(value);
        break;
    
    case IMGUI_VARIABLE_TYPE::UNSIGNED_INT:
        this->UnsignedIntValue = reinterpret_cast<unsigned int*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::LONG:
        this->LongValue = reinterpret_cast<long*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG:
        this->UnsignedLongValue = reinterpret_cast<unsigned long*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::LONG_LONG:
        this->LongLongValue = reinterpret_cast<long long*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG_LONG:
        this->UnsignedLongLongValue = reinterpret_cast<unsigned long long*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::FLOAT:
        this->FloatValue = reinterpret_cast<float*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::DOUBLE:
        this->DoubleValue = reinterpret_cast<double*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::LONG_DOUBLE:
        this->LongDoubleValue = reinterpret_cast<long double*>(value);
        break;
    }
}
IMGUI_VARIABLE_POITER_DATA::IMGUI_VARIABLE_POITER_DATA(double* value, IMGUI_VARIABLE_TYPE variableType)
: VariableType(variableType)
{
    switch (variableType)
    {
    case IMGUI_VARIABLE_TYPE::CHAR:
        this->CharValue = reinterpret_cast<char*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_CHAR:
        this->UnsignedCharValue = reinterpret_cast<unsigned char*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::SHORT:
        this->ShortValue = reinterpret_cast<short*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_SHORT:
        this->UnsignedShortValue = reinterpret_cast<unsigned short*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::INT:
        this->IntValue = reinterpret_cast<int*>(value);
        break;
    
    case IMGUI_VARIABLE_TYPE::UNSIGNED_INT:
        this->UnsignedIntValue = reinterpret_cast<unsigned int*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::LONG:
        this->LongValue = reinterpret_cast<long*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG:
        this->UnsignedLongValue = reinterpret_cast<unsigned long*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::LONG_LONG:
        this->LongLongValue = reinterpret_cast<long long*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG_LONG:
        this->UnsignedLongLongValue = reinterpret_cast<unsigned long long*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::FLOAT:
        this->FloatValue = reinterpret_cast<float*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::DOUBLE:
        this->DoubleValue = reinterpret_cast<double*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::LONG_DOUBLE:
        this->LongDoubleValue = reinterpret_cast<long double*>(value);
        break;
    }
}
IMGUI_VARIABLE_POITER_DATA::IMGUI_VARIABLE_POITER_DATA(long double* value, IMGUI_VARIABLE_TYPE variableType)
: VariableType(variableType)
{
    switch (variableType)
    {
    case IMGUI_VARIABLE_TYPE::CHAR:
        this->CharValue = reinterpret_cast<char*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_CHAR:
        this->UnsignedCharValue = reinterpret_cast<unsigned char*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::SHORT:
        this->ShortValue = reinterpret_cast<short*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_SHORT:
        this->UnsignedShortValue = reinterpret_cast<unsigned short*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::INT:
        this->IntValue = reinterpret_cast<int*>(value);
        break;
    
    case IMGUI_VARIABLE_TYPE::UNSIGNED_INT:
        this->UnsignedIntValue = reinterpret_cast<unsigned int*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::LONG:
        this->LongValue = reinterpret_cast<long*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG:
        this->UnsignedLongValue = reinterpret_cast<unsigned long*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::LONG_LONG:
        this->LongLongValue = reinterpret_cast<long long*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG_LONG:
        this->UnsignedLongLongValue = reinterpret_cast<unsigned long long*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::FLOAT:
        this->FloatValue = reinterpret_cast<float*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::DOUBLE:
        this->DoubleValue = reinterpret_cast<double*>(value);
        break;

    case IMGUI_VARIABLE_TYPE::LONG_DOUBLE:
        this->LongDoubleValue = reinterpret_cast<long double*>(value);
        break;
    }
}

// コピー・ムーブ
IMGUI_VARIABLE_POITER_DATA::IMGUI_VARIABLE_POITER_DATA(const IMGUI_VARIABLE_POITER_DATA& other)
: VariableType(other.VariableType)
{
    switch (other.VariableType)
    {
    case IMGUI_VARIABLE_TYPE::CHAR:
        this->CharValue = other.CharValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_CHAR:
        this->UnsignedCharValue = other.UnsignedCharValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::SHORT:
        this->ShortValue = other.ShortValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_SHORT:
        this->UnsignedShortValue = other.UnsignedShortValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::INT:
        this->IntValue = other.IntValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_INT:
        this->UnsignedIntValue = other.UnsignedIntValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG:
        this->LongValue = other.LongValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG:
        this->UnsignedLongValue = other.UnsignedLongValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_LONG:
        this->LongLongValue = other.LongLongValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG_LONG:
        this->UnsignedLongLongValue = other.UnsignedLongLongValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::FLOAT:
        this->FloatValue = other.FloatValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::DOUBLE:
        this->DoubleValue = other.DoubleValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_DOUBLE:
        this->LongDoubleValue = other.LongDoubleValue;
        break;
    }
}

IMGUI_VARIABLE_POITER_DATA::IMGUI_VARIABLE_POITER_DATA(IMGUI_VARIABLE_POITER_DATA&& other)
: VariableType(other.VariableType)
{
    switch (other.VariableType)
    {
    case IMGUI_VARIABLE_TYPE::CHAR:
        this->CharValue = other.CharValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_CHAR:
        this->UnsignedCharValue = other.UnsignedCharValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::SHORT:
        this->ShortValue = other.ShortValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_SHORT:
        this->UnsignedShortValue = other.UnsignedShortValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::INT:
        this->IntValue = other.IntValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_INT:
        this->UnsignedIntValue = other.UnsignedIntValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG:
        this->LongValue = other.LongValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG:
        this->UnsignedLongValue = other.UnsignedLongValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_LONG:
        this->LongLongValue = other.LongLongValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG_LONG:
        this->UnsignedLongLongValue = other.UnsignedLongLongValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::FLOAT:
        this->FloatValue = other.FloatValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::DOUBLE:
        this->DoubleValue = other.DoubleValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_DOUBLE:
        this->LongDoubleValue = other.LongDoubleValue;
        break;
    }
}

IMGUI_VARIABLE_POITER_DATA& IMGUI_VARIABLE_POITER_DATA::operator=(const IMGUI_VARIABLE_POITER_DATA& other)
{
    this->VariableType = other.VariableType;
    switch (other.VariableType)
    {
    case IMGUI_VARIABLE_TYPE::CHAR:
        this->CharValue = other.CharValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_CHAR:
        this->UnsignedCharValue = other.UnsignedCharValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::SHORT:
        this->ShortValue = other.ShortValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_SHORT:
        this->UnsignedShortValue = other.UnsignedShortValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::INT:
        this->IntValue = other.IntValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_INT:
        this->UnsignedIntValue = other.UnsignedIntValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG:
        this->LongValue = other.LongValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG:
        this->UnsignedLongValue = other.UnsignedLongValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_LONG:
        this->LongLongValue = other.LongLongValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG_LONG:
        this->UnsignedLongLongValue = other.UnsignedLongLongValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::FLOAT:
        this->FloatValue = other.FloatValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::DOUBLE:
        this->DoubleValue = other.DoubleValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_DOUBLE:
        this->LongDoubleValue = other.LongDoubleValue;
        break;
    }

    return *this;
}

IMGUI_VARIABLE_POITER_DATA& IMGUI_VARIABLE_POITER_DATA::operator=(IMGUI_VARIABLE_POITER_DATA&& other)
{
    this->VariableType = other.VariableType;
    switch (other.VariableType)
    {
    case IMGUI_VARIABLE_TYPE::CHAR:
        this->CharValue = other.CharValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_CHAR:
        this->UnsignedCharValue = other.UnsignedCharValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::SHORT:
        this->ShortValue = other.ShortValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_SHORT:
        this->UnsignedShortValue = other.UnsignedShortValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::INT:
        this->IntValue = other.IntValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_INT:
        this->UnsignedIntValue = other.UnsignedIntValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG:
        this->LongValue = other.LongValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG:
        this->UnsignedLongValue = other.UnsignedLongValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_LONG:
        this->LongLongValue = other.LongLongValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG_LONG:
        this->UnsignedLongLongValue = other.UnsignedLongLongValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::FLOAT:
        this->FloatValue = other.FloatValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::DOUBLE:
        this->DoubleValue = other.DoubleValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_DOUBLE:
        this->LongDoubleValue = other.LongDoubleValue;
        break;
    }

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
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG_LONG:
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
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG_LONG:
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
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG_LONG:
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
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG_LONG:
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
IMGUI_VARIABLE_POITER_DATA& IMGUI_VARIABLE_POITER_DATA::operator=(long long value)
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
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG_LONG:
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
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG_LONG:
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
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG_LONG:
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
IMGUI_VARIABLE_POITER_DATA& IMGUI_VARIABLE_POITER_DATA::operator=(const IMGUI_VARIABLE_DATA& valueData)
{
    if (this->VariableType != valueData.VariableType)
    {
        return *this;
    }
    switch (valueData.VariableType)
    {
    case IMGUI_VARIABLE_TYPE::CHAR:
        if (this->CharValue == nullptr) { break; }
        *this->CharValue = valueData.CharValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_CHAR:
        if (this->UnsignedCharValue == nullptr) { break; }
        *this->UnsignedCharValue = valueData.UnsignedCharValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::SHORT:
        if (this->ShortValue == nullptr) { break; }
        *this->ShortValue = valueData.ShortValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_SHORT:
        if (this->UnsignedShortValue == nullptr) { break; }
        *this->UnsignedShortValue = valueData.UnsignedShortValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::INT:
        if (this->IntValue == nullptr) { break; }
        *this->IntValue = valueData.IntValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_INT:
        if (this->UnsignedIntValue == nullptr) { break; }
        *this->UnsignedIntValue = valueData.UnsignedIntValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG:
        if (this->LongValue == nullptr) { break; }
        *this->LongValue = valueData.LongValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG:
        if (this->UnsignedLongValue == nullptr) { break; }
        *this->UnsignedLongValue = valueData.UnsignedLongValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_LONG:
        if (this->LongLongValue == nullptr) { break; }
        *this->LongLongValue = valueData.LongLongValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG_LONG:
        if (this->UnsignedLongLongValue == nullptr) { break; }
        *this->UnsignedLongLongValue = valueData.UnsignedLongLongValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::FLOAT:
        if (this->FloatValue == nullptr) { break; }
        *this->FloatValue = valueData.FloatValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::DOUBLE:
        if (this->DoubleValue == nullptr) { break; }
        *this->DoubleValue = valueData.DoubleValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_DOUBLE:
        if (this->LongDoubleValue == nullptr) { break; }
        *this->LongDoubleValue = valueData.LongDoubleValue;
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
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG_LONG:
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
void IMGUI_VARIABLE_POITER_DATA::GetValueToUnsignedChar(unsigned char& unsignedCharValue) const
{
    switch (VariableType)
    {
    case IMGUI_VARIABLE_TYPE::CHAR:
        if (this->CharValue == nullptr) { break; }
        unsignedCharValue = static_cast<unsigned char>(*this->CharValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_CHAR:
        if (this->UnsignedCharValue == nullptr) { break; }
        unsignedCharValue = static_cast<unsigned char>(*this->UnsignedCharValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::SHORT:
        if (this->ShortValue == nullptr) { break; }
        unsignedCharValue = static_cast<unsigned char>(*this->ShortValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_SHORT:
        if (this->UnsignedShortValue == nullptr) { break; }
        unsignedCharValue = static_cast<unsigned char>(*this->UnsignedShortValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::INT:
        if (this->IntValue == nullptr) { break; }
        unsignedCharValue = static_cast<unsigned char>(*this->IntValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_INT:
        if (this->UnsignedIntValue == nullptr) { break; }
        unsignedCharValue = static_cast<unsigned char>(*this->UnsignedIntValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG:
        if (this->LongValue == nullptr) { break; }
        unsignedCharValue = static_cast<unsigned char>(*this->LongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG:
        if (this->UnsignedLongValue == nullptr) { break; }
        unsignedCharValue = static_cast<unsigned char>(*this->UnsignedLongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_LONG:
        if (this->LongLongValue == nullptr) { break; }
        unsignedCharValue = static_cast<unsigned char>(*this->LongLongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG_LONG:
        if (this->UnsignedLongLongValue == nullptr) { break; }
        unsignedCharValue = static_cast<unsigned char>(*this->UnsignedLongLongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::FLOAT:
        if (this->FloatValue == nullptr) { break; }
        unsignedCharValue = static_cast<unsigned char>(*this->FloatValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::DOUBLE:
        if (this->DoubleValue == nullptr) { break; }
        unsignedCharValue = static_cast<unsigned char>(*this->DoubleValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_DOUBLE:
        if (this->LongDoubleValue == nullptr) { break; }
        unsignedCharValue = static_cast<unsigned char>(*this->LongDoubleValue);
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
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG_LONG:
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
void IMGUI_VARIABLE_POITER_DATA::GetValueToUnsignedShort(unsigned short& unsignedShortValue) const
{
    switch (VariableType)
    {
    case IMGUI_VARIABLE_TYPE::CHAR:
        if (this->CharValue == nullptr) { break; }
        unsignedShortValue = static_cast<unsigned short>(*this->CharValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_CHAR:
        if (this->UnsignedCharValue == nullptr) { break; }
        unsignedShortValue = static_cast<unsigned short>(*this->UnsignedCharValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::SHORT:
        if (this->ShortValue == nullptr) { break; }
        unsignedShortValue = static_cast<unsigned short>(*this->ShortValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_SHORT:
        if (this->UnsignedShortValue == nullptr) { break; }
        unsignedShortValue = static_cast<unsigned short>(*this->UnsignedShortValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::INT:
        if (this->IntValue == nullptr) { break; }
        unsignedShortValue = static_cast<unsigned short>(*this->IntValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_INT:
        if (this->UnsignedIntValue == nullptr) { break; }
        unsignedShortValue = static_cast<unsigned short>(*this->UnsignedIntValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG:
        if (this->LongValue == nullptr) { break; }
        unsignedShortValue = static_cast<unsigned short>(*this->LongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG:
        if (this->UnsignedLongValue == nullptr) { break; }
        unsignedShortValue = static_cast<unsigned short>(*this->UnsignedLongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_LONG:
        if (this->LongLongValue == nullptr) { break; }
        unsignedShortValue = static_cast<unsigned short>(*this->LongLongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG_LONG:
        if (this->UnsignedLongLongValue == nullptr) { break; }
        unsignedShortValue = static_cast<unsigned short>(*this->UnsignedLongLongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::FLOAT:
        if (this->FloatValue == nullptr) { break; }
        unsignedShortValue = static_cast<unsigned short>(*this->FloatValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::DOUBLE:
        if (this->DoubleValue == nullptr) { break; }
        unsignedShortValue = static_cast<unsigned short>(*this->DoubleValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_DOUBLE:
        if (this->LongDoubleValue == nullptr) { break; }
        unsignedShortValue = static_cast<unsigned short>(*this->LongDoubleValue);
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
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG_LONG:
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
void IMGUI_VARIABLE_POITER_DATA::GetValueToUnsignedInt(unsigned int& unsignedIntValue) const
{
    switch (VariableType)
    {
    case IMGUI_VARIABLE_TYPE::CHAR:
        if (this->CharValue == nullptr) { break; }
        unsignedIntValue = static_cast<unsigned int>(*this->CharValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_CHAR:
        if (this->UnsignedCharValue == nullptr) { break; }
        unsignedIntValue = static_cast<unsigned int>(*this->UnsignedCharValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::SHORT:
        if (this->ShortValue == nullptr) { break; }
        unsignedIntValue = static_cast<unsigned int>(*this->ShortValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_SHORT:
        if (this->UnsignedShortValue == nullptr) { break; }
        unsignedIntValue = static_cast<unsigned int>(*this->UnsignedShortValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::INT:
        if (this->IntValue == nullptr) { break; }
        unsignedIntValue = static_cast<unsigned int>(*this->IntValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_INT:
        if (this->UnsignedIntValue == nullptr) { break; }
        unsignedIntValue = static_cast<unsigned int>(*this->UnsignedIntValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG:
        if (this->LongValue == nullptr) { break; }
        unsignedIntValue = static_cast<unsigned int>(*this->LongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG:
        if (this->UnsignedLongValue == nullptr) { break; }
        unsignedIntValue = static_cast<unsigned int>(*this->UnsignedLongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_LONG:
        if (this->LongLongValue == nullptr) { break; }
        unsignedIntValue = static_cast<unsigned int>(*this->LongLongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG_LONG:
        if (this->UnsignedLongLongValue == nullptr) { break; }
        unsignedIntValue = static_cast<unsigned int>(*this->UnsignedLongLongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::FLOAT:
        if (this->FloatValue == nullptr) { break; }
        unsignedIntValue = static_cast<unsigned int>(*this->FloatValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::DOUBLE:
        if (this->DoubleValue == nullptr) { break; }
        unsignedIntValue = static_cast<unsigned int>(*this->DoubleValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_DOUBLE:
        if (this->LongDoubleValue == nullptr) { break; }
        unsignedIntValue = static_cast<unsigned int>(*this->LongDoubleValue);
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
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG_LONG:
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
void IMGUI_VARIABLE_POITER_DATA::GetValueToUnsignedLong(unsigned long& unsignedLongValue) const
{
    switch (VariableType)
    {
    case IMGUI_VARIABLE_TYPE::CHAR:
        if (this->CharValue == nullptr) { break; }
        unsignedLongValue = static_cast<unsigned long>(*this->CharValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_CHAR:
        if (this->UnsignedCharValue == nullptr) { break; }
        unsignedLongValue = static_cast<unsigned long>(*this->UnsignedCharValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::SHORT:
        if (this->ShortValue == nullptr) { break; }
        unsignedLongValue = static_cast<unsigned long>(*this->ShortValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_SHORT:
        if (this->UnsignedShortValue == nullptr) { break; }
        unsignedLongValue = static_cast<unsigned long>(*this->UnsignedShortValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::INT:
        if (this->IntValue == nullptr) { break; }
        unsignedLongValue = static_cast<unsigned long>(*this->IntValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_INT:
        if (this->UnsignedIntValue == nullptr) { break; }
        unsignedLongValue = static_cast<unsigned long>(*this->UnsignedIntValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG:
        if (this->LongValue == nullptr) { break; }
        unsignedLongValue = static_cast<unsigned long>(*this->LongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG:
        if (this->UnsignedLongValue == nullptr) { break; }
        unsignedLongValue = static_cast<unsigned long>(*this->UnsignedLongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_LONG:
        if (this->LongLongValue == nullptr) { break; }
        unsignedLongValue = static_cast<unsigned long>(*this->LongLongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG_LONG:
        if (this->UnsignedLongLongValue == nullptr) { break; }
        unsignedLongValue = static_cast<unsigned long>(*this->UnsignedLongLongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::FLOAT:
        if (this->FloatValue == nullptr) { break; }
        unsignedLongValue = static_cast<unsigned long>(*this->FloatValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::DOUBLE:
        if (this->DoubleValue == nullptr) { break; }
        unsignedLongValue = static_cast<unsigned long>(*this->DoubleValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_DOUBLE:
        if (this->LongDoubleValue == nullptr) { break; }
        unsignedLongValue = static_cast<unsigned long>(*this->LongDoubleValue);
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
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG_LONG:
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
void IMGUI_VARIABLE_POITER_DATA::GetValueToUnsignedLongLong(unsigned long long& unsignedLongLongValue) const
{
    switch (VariableType)
    {
    case IMGUI_VARIABLE_TYPE::CHAR:
        if (this->CharValue == nullptr) { break; }
        unsignedLongLongValue = static_cast<unsigned long long>(*this->CharValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_CHAR:
        if (this->UnsignedCharValue == nullptr) { break; }
        unsignedLongLongValue = static_cast<unsigned long long>(*this->UnsignedCharValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::SHORT:
        if (this->ShortValue == nullptr) { break; }
        unsignedLongLongValue = static_cast<unsigned long long>(*this->ShortValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_SHORT:
        if (this->UnsignedShortValue == nullptr) { break; }
        unsignedLongLongValue = static_cast<unsigned long long>(*this->UnsignedShortValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::INT:
        if (this->IntValue == nullptr) { break; }
        unsignedLongLongValue = static_cast<unsigned long long>(*this->IntValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_INT:
        if (this->UnsignedIntValue == nullptr) { break; }
        unsignedLongLongValue = static_cast<unsigned long long>(*this->UnsignedIntValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG:
        if (this->LongValue == nullptr) { break; }
        unsignedLongLongValue = static_cast<unsigned long long>(*this->LongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG:
        if (this->UnsignedLongValue == nullptr) { break; }
        unsignedLongLongValue = static_cast<unsigned long long>(*this->UnsignedLongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_LONG:
        if (this->LongLongValue == nullptr) { break; }
        unsignedLongLongValue = static_cast<unsigned long long>(*this->LongLongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG_LONG:
        if (this->UnsignedLongLongValue == nullptr) { break; }
        unsignedLongLongValue = static_cast<unsigned long long>(*this->UnsignedLongLongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::FLOAT:
        if (this->FloatValue == nullptr) { break; }
        unsignedLongLongValue = static_cast<unsigned long long>(*this->FloatValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::DOUBLE:
        if (this->DoubleValue == nullptr) { break; }
        unsignedLongLongValue = static_cast<unsigned long long>(*this->DoubleValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_DOUBLE:
        if (this->LongDoubleValue == nullptr) { break; }
        unsignedLongLongValue = static_cast<unsigned long long>(*this->LongDoubleValue);
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
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG_LONG:
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
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG_LONG:
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
void IMGUI_VARIABLE_POITER_DATA::GetValueToLongDouble(long double& longDoubleValue) const
{
    switch (VariableType)
    {
    case IMGUI_VARIABLE_TYPE::CHAR:
        if (this->CharValue == nullptr) { break; }
        longDoubleValue = static_cast<long double>(*this->CharValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_CHAR:
        if (this->UnsignedCharValue == nullptr) { break; }
        longDoubleValue = static_cast<long double>(*this->UnsignedCharValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::SHORT:
        if (this->ShortValue == nullptr) { break; }
        longDoubleValue = static_cast<long double>(*this->ShortValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_SHORT:
        if (this->UnsignedShortValue == nullptr) { break; }
        longDoubleValue = static_cast<long double>(*this->UnsignedShortValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::INT:
        if (this->IntValue == nullptr) { break; }
        longDoubleValue = static_cast<long double>(*this->IntValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_INT:
        if (this->UnsignedIntValue == nullptr) { break; }
        longDoubleValue = static_cast<long double>(*this->UnsignedIntValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG:
        if (this->LongValue == nullptr) { break; }
        longDoubleValue = static_cast<long double>(*this->LongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG:
        if (this->UnsignedLongValue == nullptr) { break; }
        longDoubleValue = static_cast<long double>(*this->UnsignedLongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_LONG:
        if (this->LongLongValue == nullptr) { break; }
        longDoubleValue = static_cast<long double>(*this->LongLongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG_LONG:
        if (this->UnsignedLongLongValue == nullptr) { break; }
        longDoubleValue = static_cast<long double>(*this->UnsignedLongLongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::FLOAT:
        if (this->FloatValue == nullptr) { break; }
        longDoubleValue = static_cast<long double>(*this->FloatValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::DOUBLE:
        if (this->DoubleValue == nullptr) { break; }
        longDoubleValue = static_cast<long double>(*this->DoubleValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_DOUBLE:
        if (this->LongDoubleValue == nullptr) { break; }
        longDoubleValue = static_cast<long double>(*this->LongDoubleValue);
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
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG_LONG:
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
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG_LONG:
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
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG_LONG:
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


/*-----------------------------------------------------------------------*/
/*                            変数データ(値)                             */
/*-----------------------------------------------------------------------*/

// コンストラクタ
IMGUI_VARIABLE_DATA::IMGUI_VARIABLE_DATA()
: VariableType(IMGUI_VARIABLE_TYPE::NONE)
, LongDoubleValue(0)
{
}
IMGUI_VARIABLE_DATA::IMGUI_VARIABLE_DATA(char value, IMGUI_VARIABLE_TYPE variableType)
: VariableType(variableType)
{
    switch (variableType)
    {
    case IMGUI_VARIABLE_TYPE::CHAR:
        this->CharValue = static_cast<char>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_CHAR:
        this->UnsignedCharValue = static_cast<unsigned char>(value);
        break;

    case IMGUI_VARIABLE_TYPE::SHORT:
        this->ShortValue = static_cast<short>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_SHORT:
        this->UnsignedShortValue = static_cast<unsigned short>(value);
        break;

    case IMGUI_VARIABLE_TYPE::INT:
        this->IntValue = static_cast<int>(value);
        break;
    
    case IMGUI_VARIABLE_TYPE::UNSIGNED_INT:
        this->UnsignedIntValue = static_cast<unsigned int>(value);
        break;

    case IMGUI_VARIABLE_TYPE::LONG:
        this->LongValue = static_cast<long>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG:
        this->UnsignedLongValue = static_cast<unsigned long>(value);
        break;

    case IMGUI_VARIABLE_TYPE::LONG_LONG:
        this->LongLongValue = static_cast<long long>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG_LONG:
        this->UnsignedLongLongValue = static_cast<unsigned long long>(value);
        break;

    case IMGUI_VARIABLE_TYPE::FLOAT:
        this->FloatValue = static_cast<float>(value);
        break;

    case IMGUI_VARIABLE_TYPE::DOUBLE:
        this->DoubleValue = static_cast<double>(value);
        break;

    case IMGUI_VARIABLE_TYPE::LONG_DOUBLE:
        this->LongDoubleValue = static_cast<long double>(value);
        break;
    }
}
IMGUI_VARIABLE_DATA::IMGUI_VARIABLE_DATA(unsigned char value, IMGUI_VARIABLE_TYPE variableType)
: VariableType(variableType)
{
    switch (variableType)
    {
    case IMGUI_VARIABLE_TYPE::CHAR:
        this->CharValue = static_cast<char>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_CHAR:
        this->UnsignedCharValue = static_cast<unsigned char>(value);
        break;

    case IMGUI_VARIABLE_TYPE::SHORT:
        this->ShortValue = static_cast<short>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_SHORT:
        this->UnsignedShortValue = static_cast<unsigned short>(value);
        break;

    case IMGUI_VARIABLE_TYPE::INT:
        this->IntValue = static_cast<int>(value);
        break;
    
    case IMGUI_VARIABLE_TYPE::UNSIGNED_INT:
        this->UnsignedIntValue = static_cast<unsigned int>(value);
        break;

    case IMGUI_VARIABLE_TYPE::LONG:
        this->LongValue = static_cast<long>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG:
        this->UnsignedLongValue = static_cast<unsigned long>(value);
        break;

    case IMGUI_VARIABLE_TYPE::LONG_LONG:
        this->LongLongValue = static_cast<long long>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG_LONG:
        this->UnsignedLongLongValue = static_cast<unsigned long long>(value);
        break;

    case IMGUI_VARIABLE_TYPE::FLOAT:
        this->FloatValue = static_cast<float>(value);
        break;

    case IMGUI_VARIABLE_TYPE::DOUBLE:
        this->DoubleValue = static_cast<double>(value);
        break;

    case IMGUI_VARIABLE_TYPE::LONG_DOUBLE:
        this->LongDoubleValue = static_cast<long double>(value);
        break;
    }
}
IMGUI_VARIABLE_DATA::IMGUI_VARIABLE_DATA(short value, IMGUI_VARIABLE_TYPE variableType)
: VariableType(variableType)
{
    switch (variableType)
    {
    case IMGUI_VARIABLE_TYPE::CHAR:
        this->CharValue = static_cast<char>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_CHAR:
        this->UnsignedCharValue = static_cast<unsigned char>(value);
        break;

    case IMGUI_VARIABLE_TYPE::SHORT:
        this->ShortValue = static_cast<short>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_SHORT:
        this->UnsignedShortValue = static_cast<unsigned short>(value);
        break;

    case IMGUI_VARIABLE_TYPE::INT:
        this->IntValue = static_cast<int>(value);
        break;
    
    case IMGUI_VARIABLE_TYPE::UNSIGNED_INT:
        this->UnsignedIntValue = static_cast<unsigned int>(value);
        break;

    case IMGUI_VARIABLE_TYPE::LONG:
        this->LongValue = static_cast<long>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG:
        this->UnsignedLongValue = static_cast<unsigned long>(value);
        break;

    case IMGUI_VARIABLE_TYPE::LONG_LONG:
        this->LongLongValue = static_cast<long long>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG_LONG:
        this->UnsignedLongLongValue = static_cast<unsigned long long>(value);
        break;

    case IMGUI_VARIABLE_TYPE::FLOAT:
        this->FloatValue = static_cast<float>(value);
        break;

    case IMGUI_VARIABLE_TYPE::DOUBLE:
        this->DoubleValue = static_cast<double>(value);
        break;

    case IMGUI_VARIABLE_TYPE::LONG_DOUBLE:
        this->LongDoubleValue = static_cast<long double>(value);
        break;
    }
}
IMGUI_VARIABLE_DATA::IMGUI_VARIABLE_DATA(unsigned short value, IMGUI_VARIABLE_TYPE variableType)
: VariableType(variableType)
{
    switch (variableType)
    {
    case IMGUI_VARIABLE_TYPE::CHAR:
        this->CharValue = static_cast<char>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_CHAR:
        this->UnsignedCharValue = static_cast<unsigned char>(value);
        break;

    case IMGUI_VARIABLE_TYPE::SHORT:
        this->ShortValue = static_cast<short>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_SHORT:
        this->UnsignedShortValue = static_cast<unsigned short>(value);
        break;

    case IMGUI_VARIABLE_TYPE::INT:
        this->IntValue = static_cast<int>(value);
        break;
    
    case IMGUI_VARIABLE_TYPE::UNSIGNED_INT:
        this->UnsignedIntValue = static_cast<unsigned int>(value);
        break;

    case IMGUI_VARIABLE_TYPE::LONG:
        this->LongValue = static_cast<long>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG:
        this->UnsignedLongValue = static_cast<unsigned long>(value);
        break;

    case IMGUI_VARIABLE_TYPE::LONG_LONG:
        this->LongLongValue = static_cast<long long>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG_LONG:
        this->UnsignedLongLongValue = static_cast<unsigned long long>(value);
        break;

    case IMGUI_VARIABLE_TYPE::FLOAT:
        this->FloatValue = static_cast<float>(value);
        break;

    case IMGUI_VARIABLE_TYPE::DOUBLE:
        this->DoubleValue = static_cast<double>(value);
        break;

    case IMGUI_VARIABLE_TYPE::LONG_DOUBLE:
        this->LongDoubleValue = static_cast<long double>(value);
        break;
    }
}
IMGUI_VARIABLE_DATA::IMGUI_VARIABLE_DATA(int value, IMGUI_VARIABLE_TYPE variableType)
: VariableType(variableType)
{
    switch (variableType)
    {
    case IMGUI_VARIABLE_TYPE::CHAR:
        this->CharValue = static_cast<char>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_CHAR:
        this->UnsignedCharValue = static_cast<unsigned char>(value);
        break;

    case IMGUI_VARIABLE_TYPE::SHORT:
        this->ShortValue = static_cast<short>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_SHORT:
        this->UnsignedShortValue = static_cast<unsigned short>(value);
        break;

    case IMGUI_VARIABLE_TYPE::INT:
        this->IntValue = static_cast<int>(value);
        break;
    
    case IMGUI_VARIABLE_TYPE::UNSIGNED_INT:
        this->UnsignedIntValue = static_cast<unsigned int>(value);
        break;

    case IMGUI_VARIABLE_TYPE::LONG:
        this->LongValue = static_cast<long>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG:
        this->UnsignedLongValue = static_cast<unsigned long>(value);
        break;

    case IMGUI_VARIABLE_TYPE::LONG_LONG:
        this->LongLongValue = static_cast<long long>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG_LONG:
        this->UnsignedLongLongValue = static_cast<unsigned long long>(value);
        break;

    case IMGUI_VARIABLE_TYPE::FLOAT:
        this->FloatValue = static_cast<float>(value);
        break;

    case IMGUI_VARIABLE_TYPE::DOUBLE:
        this->DoubleValue = static_cast<double>(value);
        break;

    case IMGUI_VARIABLE_TYPE::LONG_DOUBLE:
        this->LongDoubleValue = static_cast<long double>(value);
        break;
    }
}
IMGUI_VARIABLE_DATA::IMGUI_VARIABLE_DATA(unsigned int value, IMGUI_VARIABLE_TYPE variableType)
: VariableType(variableType)
{
    switch (variableType)
    {
    case IMGUI_VARIABLE_TYPE::CHAR:
        this->CharValue = static_cast<char>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_CHAR:
        this->UnsignedCharValue = static_cast<unsigned char>(value);
        break;

    case IMGUI_VARIABLE_TYPE::SHORT:
        this->ShortValue = static_cast<short>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_SHORT:
        this->UnsignedShortValue = static_cast<unsigned short>(value);
        break;

    case IMGUI_VARIABLE_TYPE::INT:
        this->IntValue = static_cast<int>(value);
        break;
    
    case IMGUI_VARIABLE_TYPE::UNSIGNED_INT:
        this->UnsignedIntValue = static_cast<unsigned int>(value);
        break;

    case IMGUI_VARIABLE_TYPE::LONG:
        this->LongValue = static_cast<long>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG:
        this->UnsignedLongValue = static_cast<unsigned long>(value);
        break;

    case IMGUI_VARIABLE_TYPE::LONG_LONG:
        this->LongLongValue = static_cast<long long>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG_LONG:
        this->UnsignedLongLongValue = static_cast<unsigned long long>(value);
        break;

    case IMGUI_VARIABLE_TYPE::FLOAT:
        this->FloatValue = static_cast<float>(value);
        break;

    case IMGUI_VARIABLE_TYPE::DOUBLE:
        this->DoubleValue = static_cast<double>(value);
        break;

    case IMGUI_VARIABLE_TYPE::LONG_DOUBLE:
        this->LongDoubleValue = static_cast<long double>(value);
        break;
    }
}
IMGUI_VARIABLE_DATA::IMGUI_VARIABLE_DATA(long value, IMGUI_VARIABLE_TYPE variableType)
: VariableType(variableType)
{
    switch (variableType)
    {
    case IMGUI_VARIABLE_TYPE::CHAR:
        this->CharValue = static_cast<char>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_CHAR:
        this->UnsignedCharValue = static_cast<unsigned char>(value);
        break;

    case IMGUI_VARIABLE_TYPE::SHORT:
        this->ShortValue = static_cast<short>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_SHORT:
        this->UnsignedShortValue = static_cast<unsigned short>(value);
        break;

    case IMGUI_VARIABLE_TYPE::INT:
        this->IntValue = static_cast<int>(value);
        break;
    
    case IMGUI_VARIABLE_TYPE::UNSIGNED_INT:
        this->UnsignedIntValue = static_cast<unsigned int>(value);
        break;

    case IMGUI_VARIABLE_TYPE::LONG:
        this->LongValue = static_cast<long>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG:
        this->UnsignedLongValue = static_cast<unsigned long>(value);
        break;

    case IMGUI_VARIABLE_TYPE::LONG_LONG:
        this->LongLongValue = static_cast<long long>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG_LONG:
        this->UnsignedLongLongValue = static_cast<unsigned long long>(value);
        break;

    case IMGUI_VARIABLE_TYPE::FLOAT:
        this->FloatValue = static_cast<float>(value);
        break;

    case IMGUI_VARIABLE_TYPE::DOUBLE:
        this->DoubleValue = static_cast<double>(value);
        break;

    case IMGUI_VARIABLE_TYPE::LONG_DOUBLE:
        this->LongDoubleValue = static_cast<long double>(value);
        break;
    }
}
IMGUI_VARIABLE_DATA::IMGUI_VARIABLE_DATA(unsigned long value, IMGUI_VARIABLE_TYPE variableType)
: VariableType(variableType)
{
    switch (variableType)
    {
    case IMGUI_VARIABLE_TYPE::CHAR:
        this->CharValue = static_cast<char>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_CHAR:
        this->UnsignedCharValue = static_cast<unsigned char>(value);
        break;

    case IMGUI_VARIABLE_TYPE::SHORT:
        this->ShortValue = static_cast<short>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_SHORT:
        this->UnsignedShortValue = static_cast<unsigned short>(value);
        break;

    case IMGUI_VARIABLE_TYPE::INT:
        this->IntValue = static_cast<int>(value);
        break;
    
    case IMGUI_VARIABLE_TYPE::UNSIGNED_INT:
        this->UnsignedIntValue = static_cast<unsigned int>(value);
        break;

    case IMGUI_VARIABLE_TYPE::LONG:
        this->LongValue = static_cast<long>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG:
        this->UnsignedLongValue = static_cast<unsigned long>(value);
        break;

    case IMGUI_VARIABLE_TYPE::LONG_LONG:
        this->LongLongValue = static_cast<long long>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG_LONG:
        this->UnsignedLongLongValue = static_cast<unsigned long long>(value);
        break;

    case IMGUI_VARIABLE_TYPE::FLOAT:
        this->FloatValue = static_cast<float>(value);
        break;

    case IMGUI_VARIABLE_TYPE::DOUBLE:
        this->DoubleValue = static_cast<double>(value);
        break;

    case IMGUI_VARIABLE_TYPE::LONG_DOUBLE:
        this->LongDoubleValue = static_cast<long double>(value);
        break;
    }
}
IMGUI_VARIABLE_DATA::IMGUI_VARIABLE_DATA(long long value, IMGUI_VARIABLE_TYPE variableType)
: VariableType(variableType)
{
    switch (variableType)
    {
    case IMGUI_VARIABLE_TYPE::CHAR:
        this->CharValue = static_cast<char>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_CHAR:
        this->UnsignedCharValue = static_cast<unsigned char>(value);
        break;

    case IMGUI_VARIABLE_TYPE::SHORT:
        this->ShortValue = static_cast<short>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_SHORT:
        this->UnsignedShortValue = static_cast<unsigned short>(value);
        break;

    case IMGUI_VARIABLE_TYPE::INT:
        this->IntValue = static_cast<int>(value);
        break;
    
    case IMGUI_VARIABLE_TYPE::UNSIGNED_INT:
        this->UnsignedIntValue = static_cast<unsigned int>(value);
        break;

    case IMGUI_VARIABLE_TYPE::LONG:
        this->LongValue = static_cast<long>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG:
        this->UnsignedLongValue = static_cast<unsigned long>(value);
        break;

    case IMGUI_VARIABLE_TYPE::LONG_LONG:
        this->LongLongValue = static_cast<long long>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG_LONG:
        this->UnsignedLongLongValue = static_cast<unsigned long long>(value);
        break;

    case IMGUI_VARIABLE_TYPE::FLOAT:
        this->FloatValue = static_cast<float>(value);
        break;

    case IMGUI_VARIABLE_TYPE::DOUBLE:
        this->DoubleValue = static_cast<double>(value);
        break;

    case IMGUI_VARIABLE_TYPE::LONG_DOUBLE:
        this->LongDoubleValue = static_cast<long double>(value);
        break;
    }
}
IMGUI_VARIABLE_DATA::IMGUI_VARIABLE_DATA(unsigned long long value, IMGUI_VARIABLE_TYPE variableType)
: VariableType(variableType)
{
    switch (variableType)
    {
    case IMGUI_VARIABLE_TYPE::CHAR:
        this->CharValue = static_cast<char>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_CHAR:
        this->UnsignedCharValue = static_cast<unsigned char>(value);
        break;

    case IMGUI_VARIABLE_TYPE::SHORT:
        this->ShortValue = static_cast<short>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_SHORT:
        this->UnsignedShortValue = static_cast<unsigned short>(value);
        break;

    case IMGUI_VARIABLE_TYPE::INT:
        this->IntValue = static_cast<int>(value);
        break;
    
    case IMGUI_VARIABLE_TYPE::UNSIGNED_INT:
        this->UnsignedIntValue = static_cast<unsigned int>(value);
        break;

    case IMGUI_VARIABLE_TYPE::LONG:
        this->LongValue = static_cast<long>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG:
        this->UnsignedLongValue = static_cast<unsigned long>(value);
        break;

    case IMGUI_VARIABLE_TYPE::LONG_LONG:
        this->LongLongValue = static_cast<long long>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG_LONG:
        this->UnsignedLongLongValue = static_cast<unsigned long long>(value);
        break;

    case IMGUI_VARIABLE_TYPE::FLOAT:
        this->FloatValue = static_cast<float>(value);
        break;

    case IMGUI_VARIABLE_TYPE::DOUBLE:
        this->DoubleValue = static_cast<double>(value);
        break;

    case IMGUI_VARIABLE_TYPE::LONG_DOUBLE:
        this->LongDoubleValue = static_cast<long double>(value);
        break;
    }
}
IMGUI_VARIABLE_DATA::IMGUI_VARIABLE_DATA(float value, IMGUI_VARIABLE_TYPE variableType)
: VariableType(variableType)
{
    switch (variableType)
    {
    case IMGUI_VARIABLE_TYPE::CHAR:
        this->CharValue = static_cast<char>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_CHAR:
        this->UnsignedCharValue = static_cast<unsigned char>(value);
        break;

    case IMGUI_VARIABLE_TYPE::SHORT:
        this->ShortValue = static_cast<short>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_SHORT:
        this->UnsignedShortValue = static_cast<unsigned short>(value);
        break;

    case IMGUI_VARIABLE_TYPE::INT:
        this->IntValue = static_cast<int>(value);
        break;
    
    case IMGUI_VARIABLE_TYPE::UNSIGNED_INT:
        this->UnsignedIntValue = static_cast<unsigned int>(value);
        break;

    case IMGUI_VARIABLE_TYPE::LONG:
        this->LongValue = static_cast<long>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG:
        this->UnsignedLongValue = static_cast<unsigned long>(value);
        break;

    case IMGUI_VARIABLE_TYPE::LONG_LONG:
        this->LongLongValue = static_cast<long long>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG_LONG:
        this->UnsignedLongLongValue = static_cast<unsigned long long>(value);
        break;

    case IMGUI_VARIABLE_TYPE::FLOAT:
        this->FloatValue = static_cast<float>(value);
        break;

    case IMGUI_VARIABLE_TYPE::DOUBLE:
        this->DoubleValue = static_cast<double>(value);
        break;

    case IMGUI_VARIABLE_TYPE::LONG_DOUBLE:
        this->LongDoubleValue = static_cast<long double>(value);
        break;
    }
}
IMGUI_VARIABLE_DATA::IMGUI_VARIABLE_DATA(double value, IMGUI_VARIABLE_TYPE variableType)
: VariableType(variableType)
{
    switch (variableType)
    {
    case IMGUI_VARIABLE_TYPE::CHAR:
        this->CharValue = static_cast<char>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_CHAR:
        this->UnsignedCharValue = static_cast<unsigned char>(value);
        break;

    case IMGUI_VARIABLE_TYPE::SHORT:
        this->ShortValue = static_cast<short>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_SHORT:
        this->UnsignedShortValue = static_cast<unsigned short>(value);
        break;

    case IMGUI_VARIABLE_TYPE::INT:
        this->IntValue = static_cast<int>(value);
        break;
    
    case IMGUI_VARIABLE_TYPE::UNSIGNED_INT:
        this->UnsignedIntValue = static_cast<unsigned int>(value);
        break;

    case IMGUI_VARIABLE_TYPE::LONG:
        this->LongValue = static_cast<long>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG:
        this->UnsignedLongValue = static_cast<unsigned long>(value);
        break;

    case IMGUI_VARIABLE_TYPE::LONG_LONG:
        this->LongLongValue = static_cast<long long>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG_LONG:
        this->UnsignedLongLongValue = static_cast<unsigned long long>(value);
        break;

    case IMGUI_VARIABLE_TYPE::FLOAT:
        this->FloatValue = static_cast<float>(value);
        break;

    case IMGUI_VARIABLE_TYPE::DOUBLE:
        this->DoubleValue = static_cast<double>(value);
        break;

    case IMGUI_VARIABLE_TYPE::LONG_DOUBLE:
        this->LongDoubleValue = static_cast<long double>(value);
        break;
    }
}
IMGUI_VARIABLE_DATA::IMGUI_VARIABLE_DATA(long double value, IMGUI_VARIABLE_TYPE variableType)
: VariableType(variableType)
{
    switch (variableType)
    {
    case IMGUI_VARIABLE_TYPE::CHAR:
        this->CharValue = static_cast<char>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_CHAR:
        this->UnsignedCharValue = static_cast<unsigned char>(value);
        break;

    case IMGUI_VARIABLE_TYPE::SHORT:
        this->ShortValue = static_cast<short>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_SHORT:
        this->UnsignedShortValue = static_cast<unsigned short>(value);
        break;

    case IMGUI_VARIABLE_TYPE::INT:
        this->IntValue = static_cast<int>(value);
        break;
    
    case IMGUI_VARIABLE_TYPE::UNSIGNED_INT:
        this->UnsignedIntValue = static_cast<unsigned int>(value);
        break;

    case IMGUI_VARIABLE_TYPE::LONG:
        this->LongValue = static_cast<long>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG:
        this->UnsignedLongValue = static_cast<unsigned long>(value);
        break;

    case IMGUI_VARIABLE_TYPE::LONG_LONG:
        this->LongLongValue = static_cast<long long>(value);
        break;

    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG_LONG:
        this->UnsignedLongLongValue = static_cast<unsigned long long>(value);
        break;

    case IMGUI_VARIABLE_TYPE::FLOAT:
        this->FloatValue = static_cast<float>(value);
        break;

    case IMGUI_VARIABLE_TYPE::DOUBLE:
        this->DoubleValue = static_cast<double>(value);
        break;

    case IMGUI_VARIABLE_TYPE::LONG_DOUBLE:
        this->LongDoubleValue = static_cast<long double>(value);
        break;
    }
}

// コピー・ムーブ
IMGUI_VARIABLE_DATA::IMGUI_VARIABLE_DATA(const IMGUI_VARIABLE_DATA& other)
: VariableType(other.VariableType)
{
    switch (other.VariableType)
    {
    case IMGUI_VARIABLE_TYPE::CHAR:
        this->CharValue = other.CharValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_CHAR:
        this->UnsignedCharValue = other.UnsignedCharValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::SHORT:
        this->ShortValue = other.ShortValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_SHORT:
        this->UnsignedShortValue = other.UnsignedShortValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::INT:
        this->IntValue = other.IntValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_INT:
        this->UnsignedIntValue = other.UnsignedIntValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG:
        this->LongValue = other.LongValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG:
        this->UnsignedLongValue = other.UnsignedLongValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_LONG:
        this->LongLongValue = other.LongLongValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG_LONG:
        this->UnsignedLongLongValue = other.UnsignedLongLongValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::FLOAT:
        this->FloatValue = other.FloatValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::DOUBLE:
        this->DoubleValue = other.DoubleValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_DOUBLE:
        this->LongDoubleValue = other.LongDoubleValue;
        break;
    }
}

IMGUI_VARIABLE_DATA::IMGUI_VARIABLE_DATA(IMGUI_VARIABLE_DATA&& other)
: VariableType(other.VariableType)
{
    switch (other.VariableType)
    {
    case IMGUI_VARIABLE_TYPE::CHAR:
        this->CharValue = other.CharValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_CHAR:
        this->UnsignedCharValue = other.UnsignedCharValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::SHORT:
        this->ShortValue = other.ShortValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_SHORT:
        this->UnsignedShortValue = other.UnsignedShortValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::INT:
        this->IntValue = other.IntValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_INT:
        this->UnsignedIntValue = other.UnsignedIntValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG:
        this->LongValue = other.LongValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG:
        this->UnsignedLongValue = other.UnsignedLongValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_LONG:
        this->LongLongValue = other.LongLongValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG_LONG:
        this->UnsignedLongLongValue = other.UnsignedLongLongValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::FLOAT:
        this->FloatValue = other.FloatValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::DOUBLE:
        this->DoubleValue = other.DoubleValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_DOUBLE:
        this->LongDoubleValue = other.LongDoubleValue;
        break;
    }
}

IMGUI_VARIABLE_DATA& IMGUI_VARIABLE_DATA::operator=(const IMGUI_VARIABLE_DATA& other)
{
    this->VariableType = other.VariableType;
    switch (other.VariableType)
    {
    case IMGUI_VARIABLE_TYPE::CHAR:
        this->CharValue = other.CharValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_CHAR:
        this->UnsignedCharValue = other.UnsignedCharValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::SHORT:
        this->ShortValue = other.ShortValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_SHORT:
        this->UnsignedShortValue = other.UnsignedShortValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::INT:
        this->IntValue = other.IntValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_INT:
        this->UnsignedIntValue = other.UnsignedIntValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG:
        this->LongValue = other.LongValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG:
        this->UnsignedLongValue = other.UnsignedLongValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_LONG:
        this->LongLongValue = other.LongLongValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG_LONG:
        this->UnsignedLongLongValue = other.UnsignedLongLongValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::FLOAT:
        this->FloatValue = other.FloatValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::DOUBLE:
        this->DoubleValue = other.DoubleValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_DOUBLE:
        this->LongDoubleValue = other.LongDoubleValue;
        break;
    }

    return *this;
}

IMGUI_VARIABLE_DATA& IMGUI_VARIABLE_DATA::operator=(IMGUI_VARIABLE_DATA&& other)
{
    this->VariableType = other.VariableType;
    switch (other.VariableType)
    {
    case IMGUI_VARIABLE_TYPE::CHAR:
        this->CharValue = other.CharValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_CHAR:
        this->UnsignedCharValue = other.UnsignedCharValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::SHORT:
        this->ShortValue = other.ShortValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_SHORT:
        this->UnsignedShortValue = other.UnsignedShortValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::INT:
        this->IntValue = other.IntValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_INT:
        this->UnsignedIntValue = other.UnsignedIntValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG:
        this->LongValue = other.LongValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG:
        this->UnsignedLongValue = other.UnsignedLongValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_LONG:
        this->LongLongValue = other.LongLongValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG_LONG:
        this->UnsignedLongLongValue = other.UnsignedLongLongValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::FLOAT:
        this->FloatValue = other.FloatValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::DOUBLE:
        this->DoubleValue = other.DoubleValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_DOUBLE:
        this->LongDoubleValue = other.LongDoubleValue;
        break;
    }

    return *this;
}


// デストラクタ
IMGUI_VARIABLE_DATA::~IMGUI_VARIABLE_DATA()
{
}

// 値の代入
IMGUI_VARIABLE_DATA& IMGUI_VARIABLE_DATA::operator=(char value)
{
    switch (VariableType)
    {
    case IMGUI_VARIABLE_TYPE::CHAR:
        this->CharValue = static_cast<char>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_CHAR:
        this->UnsignedCharValue = static_cast<unsigned char>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::SHORT:
        this->ShortValue = static_cast<short>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_SHORT:
        this->UnsignedShortValue = static_cast<unsigned short>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::INT:
        this->IntValue = static_cast<int>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_INT:
        this->UnsignedIntValue = static_cast<unsigned int>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG:
        this->LongValue = static_cast<long>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG:
        this->UnsignedLongValue = static_cast<unsigned long>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_LONG:
        this->LongLongValue = static_cast<long long>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG_LONG:
        this->UnsignedLongLongValue = static_cast<unsigned long long>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::FLOAT:
        this->FloatValue = static_cast<float>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::DOUBLE:
        this->DoubleValue = static_cast<double>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_DOUBLE:
        this->LongDoubleValue = static_cast<long double>(value);
        break;
    }

    return *this;
}
IMGUI_VARIABLE_DATA& IMGUI_VARIABLE_DATA::operator=(short value)
{
    switch (VariableType)
    {
    case IMGUI_VARIABLE_TYPE::CHAR:
        this->CharValue = static_cast<char>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_CHAR:
        this->UnsignedCharValue = static_cast<unsigned char>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::SHORT:
        this->ShortValue = static_cast<short>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_SHORT:
        this->UnsignedShortValue = static_cast<unsigned short>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::INT:
        this->IntValue = static_cast<int>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_INT:
        this->UnsignedIntValue = static_cast<unsigned int>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG:
        this->LongValue = static_cast<long>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG:
        this->UnsignedLongValue = static_cast<unsigned long>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_LONG:
        this->LongLongValue = static_cast<long long>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG_LONG:
        this->UnsignedLongLongValue = static_cast<unsigned long long>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::FLOAT:
        this->FloatValue = static_cast<float>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::DOUBLE:
        this->DoubleValue = static_cast<double>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_DOUBLE:
        this->LongDoubleValue = static_cast<long double>(value);
        break;
    }

    return *this;
}
IMGUI_VARIABLE_DATA& IMGUI_VARIABLE_DATA::operator=(int value)
{
    switch (VariableType)
    {
    case IMGUI_VARIABLE_TYPE::CHAR:
        this->CharValue = static_cast<char>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_CHAR:
        this->UnsignedCharValue = static_cast<unsigned char>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::SHORT:
        this->ShortValue = static_cast<short>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_SHORT:
        this->UnsignedShortValue = static_cast<unsigned short>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::INT:
        this->IntValue = static_cast<int>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_INT:
        this->UnsignedIntValue = static_cast<unsigned int>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG:
        this->LongValue = static_cast<long>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG:
        this->UnsignedLongValue = static_cast<unsigned long>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_LONG:
        this->LongLongValue = static_cast<long long>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG_LONG:
        this->UnsignedLongLongValue = static_cast<unsigned long long>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::FLOAT:
        this->FloatValue = static_cast<float>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::DOUBLE:
        this->DoubleValue = static_cast<double>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_DOUBLE:
        this->LongDoubleValue = static_cast<long double>(value);
        break;
    }

    return *this;
}
IMGUI_VARIABLE_DATA& IMGUI_VARIABLE_DATA::operator=(long value)
{
    switch (VariableType)
    {
    case IMGUI_VARIABLE_TYPE::CHAR:
        this->CharValue = static_cast<char>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_CHAR:
        this->UnsignedCharValue = static_cast<unsigned char>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::SHORT:
        this->ShortValue = static_cast<short>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_SHORT:
        this->UnsignedShortValue = static_cast<unsigned short>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::INT:
        this->IntValue = static_cast<int>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_INT:
        this->UnsignedIntValue = static_cast<unsigned int>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG:
        this->LongValue = static_cast<long>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG:
        this->UnsignedLongValue = static_cast<unsigned long>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_LONG:
        this->LongLongValue = static_cast<long long>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG_LONG:
        this->UnsignedLongLongValue = static_cast<unsigned long long>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::FLOAT:
        this->FloatValue = static_cast<float>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::DOUBLE:
        this->DoubleValue = static_cast<double>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_DOUBLE:
        this->LongDoubleValue = static_cast<long double>(value);
        break;
    }

    return *this;
}
IMGUI_VARIABLE_DATA& IMGUI_VARIABLE_DATA::operator=(long long value)
{
    switch (VariableType)
    {
    case IMGUI_VARIABLE_TYPE::CHAR:
        this->CharValue = static_cast<char>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_CHAR:
        this->UnsignedCharValue = static_cast<unsigned char>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::SHORT:
        this->ShortValue = static_cast<short>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_SHORT:
        this->UnsignedShortValue = static_cast<unsigned short>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::INT:
        this->IntValue = static_cast<int>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_INT:
        this->UnsignedIntValue = static_cast<unsigned int>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG:
        this->LongValue = static_cast<long>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG:
        this->UnsignedLongValue = static_cast<unsigned long>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_LONG:
        this->LongLongValue = static_cast<long long>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG_LONG:
        this->UnsignedLongLongValue = static_cast<unsigned long long>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::FLOAT:
        this->FloatValue = static_cast<float>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::DOUBLE:
        this->DoubleValue = static_cast<double>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_DOUBLE:
        this->LongDoubleValue = static_cast<long double>(value);
        break;
    }

    return *this;
}
IMGUI_VARIABLE_DATA& IMGUI_VARIABLE_DATA::operator=(float value)
{
    switch (VariableType)
    {
    case IMGUI_VARIABLE_TYPE::CHAR:
        this->CharValue = static_cast<char>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_CHAR:
        this->UnsignedCharValue = static_cast<unsigned char>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::SHORT:
        this->ShortValue = static_cast<short>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_SHORT:
        this->UnsignedShortValue = static_cast<unsigned short>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::INT:
        this->IntValue = static_cast<int>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_INT:
        this->UnsignedIntValue = static_cast<unsigned int>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG:
        this->LongValue = static_cast<long>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG:
        this->UnsignedLongValue = static_cast<unsigned long>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_LONG:
        this->LongLongValue = static_cast<long long>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG_LONG:
        this->UnsignedLongLongValue = static_cast<unsigned long long>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::FLOAT:
        this->FloatValue = static_cast<float>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::DOUBLE:
        this->DoubleValue = static_cast<double>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_DOUBLE:
        this->LongDoubleValue = static_cast<long double>(value);
        break;
    }

    return *this;
}
IMGUI_VARIABLE_DATA& IMGUI_VARIABLE_DATA::operator=(double value)
{
    switch (VariableType)
    {
    case IMGUI_VARIABLE_TYPE::CHAR:
        this->CharValue = static_cast<char>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_CHAR:
        this->UnsignedCharValue = static_cast<unsigned char>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::SHORT:
        this->ShortValue = static_cast<short>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_SHORT:
        this->UnsignedShortValue = static_cast<unsigned short>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::INT:
        this->IntValue = static_cast<int>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_INT:
        this->UnsignedIntValue = static_cast<unsigned int>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG:
        this->LongValue = static_cast<long>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG:
        this->UnsignedLongValue = static_cast<unsigned long>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_LONG:
        this->LongLongValue = static_cast<long long>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG_LONG:
        this->UnsignedLongLongValue = static_cast<unsigned long long>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::FLOAT:
        this->FloatValue = static_cast<float>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::DOUBLE:
        this->DoubleValue = static_cast<double>(value);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_DOUBLE:
        this->LongDoubleValue = static_cast<long double>(value);
        break;
    }

    return *this;
}
IMGUI_VARIABLE_DATA& IMGUI_VARIABLE_DATA::operator=(const IMGUI_VARIABLE_POITER_DATA& poiterData)
{
    if (this->VariableType != poiterData.VariableType)
    {
        return *this;
    }
    switch (poiterData.VariableType)
    {
    case IMGUI_VARIABLE_TYPE::CHAR:
        if (poiterData.CharValue == nullptr) { break; }
        this->CharValue = *poiterData.CharValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_CHAR:
        if (poiterData.UnsignedCharValue == nullptr) { break; }
        this->UnsignedCharValue = *poiterData.UnsignedCharValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::SHORT:
        if (poiterData.ShortValue == nullptr) { break; }
        this->ShortValue = *poiterData.ShortValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_SHORT:
        if (poiterData.UnsignedShortValue == nullptr) { break; }
        this->UnsignedShortValue = *poiterData.UnsignedShortValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::INT:
        if (poiterData.IntValue == nullptr) { break; }
        this->IntValue = *poiterData.IntValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_INT:
        if (poiterData.UnsignedIntValue == nullptr) { break; }
        this->UnsignedIntValue = *poiterData.UnsignedIntValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG:
        if (poiterData.LongValue == nullptr) { break; }
        this->LongValue = *poiterData.LongValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG:
        if (poiterData.UnsignedLongValue == nullptr) { break; }
        this->UnsignedLongValue = *poiterData.UnsignedLongValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_LONG:
        if (poiterData.LongLongValue == nullptr) { break; }
        this->LongLongValue = *poiterData.LongLongValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG_LONG:
        if (poiterData.UnsignedLongLongValue == nullptr) { break; }
        this->UnsignedLongLongValue = *poiterData.UnsignedLongLongValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::FLOAT:
        if (poiterData.FloatValue == nullptr) { break; }
        this->FloatValue = *poiterData.FloatValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::DOUBLE:
        if (poiterData.DoubleValue == nullptr) { break; }
        this->DoubleValue = *poiterData.DoubleValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_DOUBLE:
        if (poiterData.LongDoubleValue == nullptr) { break; }
        this->LongDoubleValue = *poiterData.LongDoubleValue;
        break;
    }
    return *this;
}

// 値の取得
void IMGUI_VARIABLE_DATA::GetValueToChar(char& charValue) const
{
    switch (VariableType)
    {
    case IMGUI_VARIABLE_TYPE::CHAR:
        charValue = static_cast<char>(this->CharValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_CHAR:
        charValue = static_cast<char>(this->UnsignedCharValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::SHORT:
        charValue = static_cast<char>(this->ShortValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_SHORT:
        charValue = static_cast<char>(this->UnsignedShortValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::INT:
        charValue = static_cast<char>(this->IntValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_INT:
        charValue = static_cast<char>(this->UnsignedIntValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG:
        charValue = static_cast<char>(this->LongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG:
        charValue = static_cast<char>(this->UnsignedLongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_LONG:
        charValue = static_cast<char>(this->LongLongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG_LONG:
        charValue = static_cast<char>(this->UnsignedLongLongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::FLOAT:
        charValue = static_cast<char>(this->FloatValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::DOUBLE:
        charValue = static_cast<char>(this->DoubleValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_DOUBLE:
        charValue = static_cast<char>(this->LongDoubleValue);
        break;
    }
}
void IMGUI_VARIABLE_DATA::GetValueToUnsignedChar(unsigned char& unsignedCharValue) const
{

    switch (VariableType)
    {
    case IMGUI_VARIABLE_TYPE::CHAR:
        unsignedCharValue = static_cast<unsigned char>(this->CharValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_CHAR:
        unsignedCharValue = static_cast<unsigned char>(this->UnsignedCharValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::SHORT:
        unsignedCharValue = static_cast<unsigned char>(this->ShortValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_SHORT:
        unsignedCharValue = static_cast<unsigned char>(this->UnsignedShortValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::INT:
        unsignedCharValue = static_cast<unsigned char>(this->IntValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_INT:
        unsignedCharValue = static_cast<unsigned char>(this->UnsignedIntValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG:
        unsignedCharValue = static_cast<unsigned char>(this->LongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG:
        unsignedCharValue = static_cast<unsigned char>(this->UnsignedLongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_LONG:
        unsignedCharValue = static_cast<unsigned char>(this->LongLongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG_LONG:
        unsignedCharValue = static_cast<unsigned char>(this->UnsignedLongLongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::FLOAT:
        unsignedCharValue = static_cast<unsigned char>(this->FloatValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::DOUBLE:
        unsignedCharValue = static_cast<unsigned char>(this->DoubleValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_DOUBLE:
        unsignedCharValue = static_cast<unsigned char>(this->LongDoubleValue);
        break;
    }
}
void IMGUI_VARIABLE_DATA::GetValueToShort(short& shortValue) const
{
    switch (VariableType)
    {
    case IMGUI_VARIABLE_TYPE::CHAR:
        shortValue = static_cast<short>(this->CharValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_CHAR:
        shortValue = static_cast<short>(this->UnsignedCharValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::SHORT:
        shortValue = static_cast<short>(this->ShortValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_SHORT:
        shortValue = static_cast<short>(this->UnsignedShortValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::INT:
        shortValue = static_cast<short>(this->IntValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_INT:
        shortValue = static_cast<short>(this->UnsignedIntValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG:
        shortValue = static_cast<short>(this->LongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG:
        shortValue = static_cast<short>(this->UnsignedLongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_LONG:
        shortValue = static_cast<short>(this->LongLongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG_LONG:
        shortValue = static_cast<short>(this->UnsignedLongLongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::FLOAT:
        shortValue = static_cast<short>(this->FloatValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::DOUBLE:
        shortValue = static_cast<short>(this->DoubleValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_DOUBLE:
        shortValue = static_cast<short>(this->LongDoubleValue);
        break;
    }
}
void IMGUI_VARIABLE_DATA::GetValueToUnsignedShort(unsigned short& unsignedShortValue) const
{

    switch (VariableType)
    {
    case IMGUI_VARIABLE_TYPE::CHAR:
        unsignedShortValue = static_cast<unsigned short>(this->CharValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_CHAR:
        unsignedShortValue = static_cast<unsigned short>(this->UnsignedCharValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::SHORT:
        unsignedShortValue = static_cast<unsigned short>(this->ShortValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_SHORT:
        unsignedShortValue = static_cast<unsigned short>(this->UnsignedShortValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::INT:
        unsignedShortValue = static_cast<unsigned short>(this->IntValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_INT:
        unsignedShortValue = static_cast<unsigned short>(this->UnsignedIntValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG:
        unsignedShortValue = static_cast<unsigned short>(this->LongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG:
        unsignedShortValue = static_cast<unsigned short>(this->UnsignedLongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_LONG:
        unsignedShortValue = static_cast<unsigned short>(this->LongLongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG_LONG:
        unsignedShortValue = static_cast<unsigned short>(this->UnsignedLongLongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::FLOAT:
        unsignedShortValue = static_cast<unsigned short>(this->FloatValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::DOUBLE:
        unsignedShortValue = static_cast<unsigned short>(this->DoubleValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_DOUBLE:
        unsignedShortValue = static_cast<unsigned short>(this->LongDoubleValue);
        break;
    }
}
void IMGUI_VARIABLE_DATA::GetValueToInt(int& intValue) const
{
    switch (VariableType)
    {
    case IMGUI_VARIABLE_TYPE::CHAR:
        intValue = static_cast<int>(this->CharValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_CHAR:
        intValue = static_cast<int>(this->UnsignedCharValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::SHORT:
        intValue = static_cast<int>(this->ShortValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_SHORT:
        intValue = static_cast<int>(this->UnsignedShortValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::INT:
        intValue = static_cast<int>(this->IntValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_INT:
        intValue = static_cast<int>(this->UnsignedIntValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG:
        intValue = static_cast<int>(this->LongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG:
        intValue = static_cast<int>(this->UnsignedLongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_LONG:
        intValue = static_cast<int>(this->LongLongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG_LONG:
        intValue = static_cast<int>(this->UnsignedLongLongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::FLOAT:
        intValue = static_cast<int>(this->FloatValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::DOUBLE:
        intValue = static_cast<int>(this->DoubleValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_DOUBLE:
        intValue = static_cast<int>(this->LongDoubleValue);
        break;
    }
}
void IMGUI_VARIABLE_DATA::GetValueToUnsignedInt(unsigned int& unsignedIntValue) const
{

    switch (VariableType)
    {
    case IMGUI_VARIABLE_TYPE::CHAR:
        unsignedIntValue = static_cast<unsigned int>(this->CharValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_CHAR:
        unsignedIntValue = static_cast<unsigned int>(this->UnsignedCharValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::SHORT:
        unsignedIntValue = static_cast<unsigned int>(this->ShortValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_SHORT:
        unsignedIntValue = static_cast<unsigned int>(this->UnsignedShortValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::INT:
        unsignedIntValue = static_cast<unsigned int>(this->IntValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_INT:
        unsignedIntValue = static_cast<unsigned int>(this->UnsignedIntValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG:
        unsignedIntValue = static_cast<unsigned int>(this->LongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG:
        unsignedIntValue = static_cast<unsigned int>(this->UnsignedLongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_LONG:
        unsignedIntValue = static_cast<unsigned int>(this->LongLongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG_LONG:
        unsignedIntValue = static_cast<unsigned int>(this->UnsignedLongLongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::FLOAT:
        unsignedIntValue = static_cast<unsigned int>(this->FloatValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::DOUBLE:
        unsignedIntValue = static_cast<unsigned int>(this->DoubleValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_DOUBLE:
        unsignedIntValue = static_cast<unsigned int>(this->LongDoubleValue);
        break;
    }
}
void IMGUI_VARIABLE_DATA::GetValueToLong(long& longValue) const
{
    switch (VariableType)
    {
    case IMGUI_VARIABLE_TYPE::CHAR:
        longValue = static_cast<long>(this->CharValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_CHAR:
        longValue = static_cast<long>(this->UnsignedCharValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::SHORT:
        longValue = static_cast<long>(this->ShortValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_SHORT:
        longValue = static_cast<long>(this->UnsignedShortValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::INT:
        longValue = static_cast<long>(this->IntValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_INT:
        longValue = static_cast<long>(this->UnsignedIntValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG:
        longValue = static_cast<long>(this->LongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG:
        longValue = static_cast<long>(this->UnsignedLongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_LONG:
        longValue = static_cast<long>(this->LongLongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG_LONG:
        longValue = static_cast<long>(this->UnsignedLongLongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::FLOAT:
        longValue = static_cast<long>(this->FloatValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::DOUBLE:
        longValue = static_cast<long>(this->DoubleValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_DOUBLE:
        longValue = static_cast<long>(this->LongDoubleValue);
        break;
    }
}
void IMGUI_VARIABLE_DATA::GetValueToUnsignedLong(unsigned long& unsignedLongValue) const
{

    switch (VariableType)
    {
    case IMGUI_VARIABLE_TYPE::CHAR:
        unsignedLongValue = static_cast<unsigned long>(this->CharValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_CHAR:
        unsignedLongValue = static_cast<unsigned long>(this->UnsignedCharValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::SHORT:
        unsignedLongValue = static_cast<unsigned long>(this->ShortValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_SHORT:
        unsignedLongValue = static_cast<unsigned long>(this->UnsignedShortValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::INT:
        unsignedLongValue = static_cast<unsigned long>(this->IntValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_INT:
        unsignedLongValue = static_cast<unsigned long>(this->UnsignedIntValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG:
        unsignedLongValue = static_cast<unsigned long>(this->LongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG:
        unsignedLongValue = static_cast<unsigned long>(this->UnsignedLongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_LONG:
        unsignedLongValue = static_cast<unsigned long>(this->LongLongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG_LONG:
        unsignedLongValue = static_cast<unsigned long>(this->UnsignedLongLongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::FLOAT:
        unsignedLongValue = static_cast<unsigned long>(this->FloatValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::DOUBLE:
        unsignedLongValue = static_cast<unsigned long>(this->DoubleValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_DOUBLE:
        unsignedLongValue = static_cast<unsigned long>(this->LongDoubleValue);
        break;
    }
}
void IMGUI_VARIABLE_DATA::GetValueToLongLong(long long& longlongValue) const
{
    switch (VariableType)
    {
    case IMGUI_VARIABLE_TYPE::CHAR:
        longlongValue = static_cast<long long>(this->CharValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_CHAR:
        longlongValue = static_cast<long long>(this->UnsignedCharValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::SHORT:
        longlongValue = static_cast<long long>(this->ShortValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_SHORT:
        longlongValue = static_cast<long long>(this->UnsignedShortValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::INT:
        longlongValue = static_cast<long long>(this->IntValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_INT:
        longlongValue = static_cast<long long>(this->UnsignedIntValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG:
        longlongValue = static_cast<long long>(this->LongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG:
        longlongValue = static_cast<long long>(this->UnsignedLongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_LONG:
        longlongValue = static_cast<long long>(this->LongLongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG_LONG:
        longlongValue = static_cast<long long>(this->UnsignedLongLongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::FLOAT:
        longlongValue = static_cast<long long>(this->FloatValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::DOUBLE:
        longlongValue = static_cast<long long>(this->DoubleValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_DOUBLE:
        longlongValue = static_cast<long long>(this->LongDoubleValue);
        break;
    }
}
void IMGUI_VARIABLE_DATA::GetValueToUnsignedLongLong(unsigned long long& unsignedLongLongValue) const
{

    switch (VariableType)
    {
    case IMGUI_VARIABLE_TYPE::CHAR:
        unsignedLongLongValue = static_cast<unsigned long long>(this->CharValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_CHAR:
        unsignedLongLongValue = static_cast<unsigned long long>(this->UnsignedCharValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::SHORT:
        unsignedLongLongValue = static_cast<unsigned long long>(this->ShortValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_SHORT:
        unsignedLongLongValue = static_cast<unsigned long long>(this->UnsignedShortValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::INT:
        unsignedLongLongValue = static_cast<unsigned long long>(this->IntValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_INT:
        unsignedLongLongValue = static_cast<unsigned long long>(this->UnsignedIntValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG:
        unsignedLongLongValue = static_cast<unsigned long long>(this->LongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG:
        unsignedLongLongValue = static_cast<unsigned long long>(this->UnsignedLongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_LONG:
        unsignedLongLongValue = static_cast<unsigned long long>(this->LongLongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG_LONG:
        unsignedLongLongValue = static_cast<unsigned long long>(this->UnsignedLongLongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::FLOAT:
        unsignedLongLongValue = static_cast<unsigned long long>(this->FloatValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::DOUBLE:
        unsignedLongLongValue = static_cast<unsigned long long>(this->DoubleValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_DOUBLE:
        unsignedLongLongValue = static_cast<unsigned long long>(this->LongDoubleValue);
        break;
    }
}
void IMGUI_VARIABLE_DATA::GetValueToFloat(float& floatValue) const
{
    switch (VariableType)
    {
    case IMGUI_VARIABLE_TYPE::CHAR:
        floatValue = static_cast<float>(this->CharValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_CHAR:
        floatValue = static_cast<float>(this->UnsignedCharValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::SHORT:
        floatValue = static_cast<float>(this->ShortValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_SHORT:
        floatValue = static_cast<float>(this->UnsignedShortValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::INT:
        floatValue = static_cast<float>(this->IntValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_INT:
        floatValue = static_cast<float>(this->UnsignedIntValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG:
        floatValue = static_cast<float>(this->LongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG:
        floatValue = static_cast<float>(this->UnsignedLongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_LONG:
        floatValue = static_cast<float>(this->LongLongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG_LONG:
        floatValue = static_cast<float>(this->UnsignedLongLongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::FLOAT:
        floatValue = static_cast<float>(this->FloatValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::DOUBLE:
        floatValue = static_cast<float>(this->DoubleValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_DOUBLE:
        floatValue = static_cast<float>(this->LongDoubleValue);
        break;
    }
}
void IMGUI_VARIABLE_DATA::GetValueToDouble(double& doubleValue) const
{
    switch (VariableType)
    {
    case IMGUI_VARIABLE_TYPE::CHAR:
        doubleValue = static_cast<double>(this->CharValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_CHAR:
        doubleValue = static_cast<double>(this->UnsignedCharValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::SHORT:
        doubleValue = static_cast<double>(this->ShortValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_SHORT:
        doubleValue = static_cast<double>(this->UnsignedShortValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::INT:
        doubleValue = static_cast<double>(this->IntValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_INT:
        doubleValue = static_cast<double>(this->UnsignedIntValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG:
        doubleValue = static_cast<double>(this->LongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG:
        doubleValue = static_cast<double>(this->UnsignedLongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_LONG:
        doubleValue = static_cast<double>(this->LongLongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG_LONG:
        doubleValue = static_cast<double>(this->UnsignedLongLongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::FLOAT:
        doubleValue = static_cast<double>(this->FloatValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::DOUBLE:
        doubleValue = static_cast<double>(this->DoubleValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_DOUBLE:
        doubleValue = static_cast<double>(this->LongDoubleValue);
        break;
    }
}
void IMGUI_VARIABLE_DATA::GetValueToLongDouble(long double& doubleValue) const
{

    switch (VariableType)
    {
    case IMGUI_VARIABLE_TYPE::CHAR:
        doubleValue = static_cast<long double>(this->CharValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_CHAR:
        doubleValue = static_cast<long double>(this->UnsignedCharValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::SHORT:
        doubleValue = static_cast<long double>(this->ShortValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_SHORT:
        doubleValue = static_cast<long double>(this->UnsignedShortValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::INT:
        doubleValue = static_cast<long double>(this->IntValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_INT:
        doubleValue = static_cast<long double>(this->UnsignedIntValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG:
        doubleValue = static_cast<long double>(this->LongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG:
        doubleValue = static_cast<long double>(this->UnsignedLongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_LONG:
        doubleValue = static_cast<long double>(this->LongLongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG_LONG:
        doubleValue = static_cast<long double>(this->UnsignedLongLongValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::FLOAT:
        doubleValue = static_cast<long double>(this->FloatValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::DOUBLE:
        doubleValue = static_cast<long double>(this->DoubleValue);
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_DOUBLE:
        doubleValue = static_cast<long double>(this->LongDoubleValue);
        break;
    }
}

// インクリメント・デクリメント
IMGUI_VARIABLE_DATA& IMGUI_VARIABLE_DATA::operator++()
{
    switch (VariableType)
    {
    case IMGUI_VARIABLE_TYPE::CHAR:
        ++this->CharValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_CHAR:
        ++this->UnsignedCharValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::SHORT:
        ++this->ShortValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_SHORT:
        ++this->UnsignedShortValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::INT:
        ++this->IntValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_INT:
        ++this->UnsignedIntValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG:
        ++this->LongValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG:
        ++this->UnsignedLongValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_LONG:
        ++this->LongLongValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG_LONG:
        ++this->UnsignedLongLongValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::FLOAT:
        ++this->FloatValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::DOUBLE:
        ++this->DoubleValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_DOUBLE:
        ++this->LongDoubleValue;
        break;
    }

    return *this;
}

IMGUI_VARIABLE_DATA& IMGUI_VARIABLE_DATA::operator--()
{
    switch (VariableType)
    {
    case IMGUI_VARIABLE_TYPE::CHAR:
        --this->CharValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_CHAR:
        --this->UnsignedCharValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::SHORT:
        --this->ShortValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_SHORT:
        --this->UnsignedShortValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::INT:
        --this->IntValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_INT:
        --this->UnsignedIntValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG:
        --this->LongValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG:
        --this->UnsignedLongValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_LONG:
        --this->LongLongValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG_LONG:
        --this->UnsignedLongLongValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::FLOAT:
        --this->FloatValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::DOUBLE:
        --this->DoubleValue;
        break;
        
    case IMGUI_VARIABLE_TYPE::LONG_DOUBLE:
        --this->LongDoubleValue;
        break;
    }

    return *this;
}


const void* IMGUI_VARIABLE_DATA::GetPointer() const
{
    switch (VariableType)
    {
    case IMGUI_VARIABLE_TYPE::CHAR:
        return &this->CharValue;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_CHAR:
        return &this->UnsignedCharValue;
        
    case IMGUI_VARIABLE_TYPE::SHORT:
        return &this->ShortValue;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_SHORT:
        return &this->UnsignedShortValue;
        
    case IMGUI_VARIABLE_TYPE::INT:
        return &this->IntValue;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_INT:
        return &this->UnsignedIntValue;
        
    case IMGUI_VARIABLE_TYPE::LONG:
        return &this->LongValue;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG:
        return &this->UnsignedLongValue;
        
    case IMGUI_VARIABLE_TYPE::LONG_LONG:
        return &this->LongLongValue;
        
    case IMGUI_VARIABLE_TYPE::UNSIGNED_LONG_LONG:
        return &this->UnsignedLongLongValue;
        
    case IMGUI_VARIABLE_TYPE::FLOAT:
        return &this->FloatValue;
        
    case IMGUI_VARIABLE_TYPE::DOUBLE:
        return &this->DoubleValue;
        
    case IMGUI_VARIABLE_TYPE::LONG_DOUBLE:
        return &this->LongDoubleValue;
    }

    return nullptr;
}




/*-----------------------------------------------------------------------*/
/*                      imgui全種類描画用1つ分情報                       */
/*-----------------------------------------------------------------------*/
// コンストラクタ
IMGUI_ALL_DRAW_ONE_DATA::IMGUI_ALL_DRAW_ONE_DATA()
: MyImguiDrawMode(IMGUI_DRAW_MODE::NONE)
{
}

IMGUI_ALL_DRAW_ONE_DATA::IMGUI_ALL_DRAW_ONE_DATA(IMGUI_VARIABLE_CONTROL value)
: MyImguiDrawMode(IMGUI_DRAW_MODE::VARIABLE)
, ImguiVariableControl(value)
{
}

IMGUI_ALL_DRAW_ONE_DATA::IMGUI_ALL_DRAW_ONE_DATA(IMGUI_BUTTON_CONTROL value)
: MyImguiDrawMode(IMGUI_DRAW_MODE::BUTTON)
, ImguiButtonControl(value)
{
}

IMGUI_ALL_DRAW_ONE_DATA::IMGUI_ALL_DRAW_ONE_DATA(IMGUI_LAYOUT_CONTROL value)
: MyImguiDrawMode(IMGUI_DRAW_MODE::LAYOUT)
, ImguiLayoutControl(value)
{
}

// コピー・ムーブコンストラクタ
IMGUI_ALL_DRAW_ONE_DATA::IMGUI_ALL_DRAW_ONE_DATA(const IMGUI_ALL_DRAW_ONE_DATA& other)
: MyImguiDrawMode(other.MyImguiDrawMode)
, ImguiVariableControl(other.ImguiVariableControl)
, ImguiButtonControl(other.ImguiButtonControl)
, ImguiLayoutControl(other.ImguiLayoutControl)
{
}

IMGUI_ALL_DRAW_ONE_DATA::IMGUI_ALL_DRAW_ONE_DATA(IMGUI_ALL_DRAW_ONE_DATA&& other)
: MyImguiDrawMode(other.MyImguiDrawMode)
, ImguiVariableControl(other.ImguiVariableControl)
, ImguiButtonControl(other.ImguiButtonControl)
, ImguiLayoutControl(other.ImguiLayoutControl)
{
}

// コピー代入演算子
IMGUI_ALL_DRAW_ONE_DATA& IMGUI_ALL_DRAW_ONE_DATA::operator=(const IMGUI_ALL_DRAW_ONE_DATA& other)
{
    if (this != &other)
    {
        MyImguiDrawMode = other.MyImguiDrawMode;
        ImguiVariableControl = other.ImguiVariableControl;
        ImguiButtonControl = other.ImguiButtonControl;
        ImguiLayoutControl = other.ImguiLayoutControl;
    }

    return *this;
}

// ムーブ代入演算子
IMGUI_ALL_DRAW_ONE_DATA& IMGUI_ALL_DRAW_ONE_DATA::operator=(IMGUI_ALL_DRAW_ONE_DATA&& other)
{
    if (this != &other)
    {
        MyImguiDrawMode = other.MyImguiDrawMode;
        ImguiVariableControl = other.ImguiVariableControl;
        ImguiButtonControl = other.ImguiButtonControl;
        ImguiLayoutControl = other.ImguiLayoutControl;
    }

    return *this;
}

// デストラクタ
IMGUI_ALL_DRAW_ONE_DATA::~IMGUI_ALL_DRAW_ONE_DATA()
{
}

// 変数コントロール代入
IMGUI_ALL_DRAW_ONE_DATA& IMGUI_ALL_DRAW_ONE_DATA::operator=(const IMGUI_VARIABLE_CONTROL& other)
{
    MyImguiDrawMode = IMGUI_DRAW_MODE::VARIABLE;
    ImguiVariableControl = other;

    return *this;
}

IMGUI_ALL_DRAW_ONE_DATA& IMGUI_ALL_DRAW_ONE_DATA::operator=(IMGUI_VARIABLE_CONTROL&& other)
{
    MyImguiDrawMode = IMGUI_DRAW_MODE::VARIABLE;
    ImguiVariableControl = other;

    return *this;
}

// ボタンコントロール代入
IMGUI_ALL_DRAW_ONE_DATA& IMGUI_ALL_DRAW_ONE_DATA::operator=(const IMGUI_BUTTON_CONTROL& other)
{
    MyImguiDrawMode = IMGUI_DRAW_MODE::BUTTON;
    ImguiButtonControl = other;

    return *this;
}

IMGUI_ALL_DRAW_ONE_DATA& IMGUI_ALL_DRAW_ONE_DATA::operator=(IMGUI_BUTTON_CONTROL&& other)
{
    MyImguiDrawMode = IMGUI_DRAW_MODE::BUTTON;
    ImguiButtonControl = other;

    return *this;
}

// レイアウトコントロール代入
IMGUI_ALL_DRAW_ONE_DATA& IMGUI_ALL_DRAW_ONE_DATA::operator=(const IMGUI_LAYOUT_CONTROL& other)
{
    MyImguiDrawMode = IMGUI_DRAW_MODE::LAYOUT;
    ImguiLayoutControl = other;

    return *this;
}

IMGUI_ALL_DRAW_ONE_DATA& IMGUI_ALL_DRAW_ONE_DATA::operator=(IMGUI_LAYOUT_CONTROL&& other)
{
    MyImguiDrawMode = IMGUI_DRAW_MODE::LAYOUT;
    ImguiLayoutControl = other;

    return *this;
}