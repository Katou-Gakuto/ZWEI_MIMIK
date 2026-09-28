#include "BaseModelHandle.h"

// 
BaseModelHandle::BaseModelHandle() :
    mnHandle(0)
{
}

// 
BaseModelHandle::~BaseModelHandle()
{
}

// ”äŠr‰‰ŽZŽq
bool BaseModelHandle::operator==(const BaseModelHandle &right)
{
    // 
    return this->mnHandle == right.mnHandle;
}

// ”äŠr‰‰ŽZŽq
bool BaseModelHandle::operator!=(const BaseModelHandle &right)
{
    // 
    return this->mnHandle != right.mnHandle;
}