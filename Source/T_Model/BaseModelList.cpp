#include "BaseModelList.h"

#include "BaseModel.h"

int BaseModelList::DeleteAll()
{
    if (this->mpFirstModel == nullptr)
    {
        return 0;
    }
    BaseModel *current = this->mpFirstModel;
    BaseModel *next = nullptr;
    while (current != nullptr)
    {
        next = current->GetNext();
        if (next != nullptr)
        {
            next->SetPrevNext(nullptr, next->GetNext());
        }
        current->SetPrevNext(nullptr, nullptr);
        delete current;
        current = next;
    }
    this->mpFirstModel = nullptr;
    return 0;
}

unsigned long long &BaseModelList::Handle2Number(BaseModelHandle &modelHandle)
{
    // 
    void *handlePtr = &modelHandle;
    return *((unsigned long long *)(handlePtr));
}

const unsigned long long &BaseModelList::Handle2Number(const BaseModelHandle &modelHandle)
{
    // 
    const void *handlePtr = &modelHandle;
    return *((const unsigned long long *)(handlePtr));
}

BaseModelList::BaseModelList() :
    mpFirstModel(nullptr)
{

}

BaseModelList:: ~BaseModelList()
{
    this->DeleteAll();
}

int BaseModelList::Initialize()
{
    int temp = 0;
    BaseModel *current = this->mpFirstModel;
    while (current != nullptr)
    {
        if (current->GetDrawFlag())
        {
            temp = current->Initialize();
        }
        if (temp == 0)
        {
            current = current->GetNext();
        }
        else
        {
            break;
        }
    }
    return temp;
}

int BaseModelList::Finalize()
{
    int temp = 0;
    BaseModel *current = this->mpFirstModel;
    while (current != nullptr)
    {
        if (current->GetDrawFlag())
        {
            temp = current->Finalize();
        }
        if (temp == 0)
        {
            current = current->GetNext();
        }
        else
        {
            break;
        }
    }
    return temp;
}

int BaseModelList::Draw()
{
    int temp = 0;
    BaseModel *current = this->mpFirstModel;
    while (current != nullptr)
    {
        if (current->GetDrawFlag())
        {
            temp = current->BaseDraw();
        }
        if (temp == 0)
        {
            current = current->GetNext();
        }
        else
        {
            break;
        }
    }
    return temp;
}

int BaseModelList::Add(BaseModel *model, BaseModelHandle &modelHandle)
{
    if (model == nullptr)
    {
        return -1;
    }
    if (this->mpFirstModel == nullptr)
    {
        this->mpFirstModel = model;
        return 0;
    }
    int temp = 0;
    unsigned long long handleNumber = 0;
    BaseModel *current = this->mpFirstModel;
    while (current->GetNext() != nullptr)
    {
        if (handleNumber <= current->GetModelNumber())
        {
            // 
            handleNumber = current->GetModelNumber() + 1;
        }
        current = current->GetNext();
    }
    if (temp != 0)
    {
        return temp;
    }
    current->SetPrevNext(current->GetPrev(), model);
    model->SetPrevNext(current, nullptr);
    model->SetModelNumber(handleNumber);

    // 
    BaseModelList::Handle2Number(modelHandle) = handleNumber;

    return temp;
}

BaseModel *BaseModelList::SearchModelNumber(const BaseModelHandle &modelHandle) const
{
    BaseModel *current = this->mpFirstModel;
    while (current != nullptr)
    {
        if (current->GetModelNumber() == BaseModelList::Handle2Number(modelHandle))
        {
            break;
        }
        current = current->GetNext();
    }
    return current;
}
