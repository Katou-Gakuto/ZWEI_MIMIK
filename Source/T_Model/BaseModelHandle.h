#pragma once

// 
class BaseModelHandle
{
public:
    // 
    BaseModelHandle();

    // 
    ~BaseModelHandle();

    // ƒRƒs[‹Ö~
    BaseModelHandle(const BaseModelHandle &) = delete;

    // ƒRƒs[‹Ö~
    BaseModelHandle &operator=(const BaseModelHandle &) = delete;

    // ƒ€[ƒu‹Ö~
    BaseModelHandle(BaseModelHandle &&) = delete;

    // ƒ€[ƒu‹Ö~
    BaseModelHandle &operator=(BaseModelHandle &&) = delete;

    // ”äŠr‰‰Zq
    bool operator==(const BaseModelHandle &right);

    // ”äŠr‰‰Zq
    bool operator!=(const BaseModelHandle &right);

private:
    unsigned long long mnHandle;
};
