#pragma once

class BaseModel;
class BaseModelHandle;
class BaseModelList
{
private:
    // 
    BaseModel *mpFirstModel;

    // 
    unsigned long long mnNextNumber;

    int DeleteAll();

    // 
    static unsigned long long &Handle2Number(BaseModelHandle &modelHandle);
    static const unsigned long long &Handle2Number(const BaseModelHandle &modelHandle);

public:
    BaseModelList();
    ~BaseModelList();

    int Initialize();
    int Finalize();
    int Draw();

    int Add(BaseModel *model, BaseModelHandle &modelHandle);

    BaseModel *SearchModelNumber(const BaseModelHandle &modelHandle) const;
};