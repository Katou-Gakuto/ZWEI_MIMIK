#include "GimmickObjectController.h"

// 
GimmickObjectController::GimmickObjectController(GameObject *myObject) :
    BaseComponent(myObject, ComponentTagAndOrder::CTAO_GimmickController)
{
}

//
GimmickObjectController::~GimmickObjectController()
{
    // 
    for (auto &data : this->mlGimmickList)
    {
        delete data.mpTrigger;
        delete data.mpExecutor;
    }

    this->mlGimmickList.clear();
}

// 
int GimmickObjectController::Create()
{
    // 
    return 0;
}

// 
int GimmickObjectController::Initialize()
{
    // 
    for (uint32_t i = 0; i < this->mlGimmickList.size(); i++)
    {

    }

    // 
    return 0;
}

int GimmickObjectController::Finalize()
{
    // 
    return 0;
}

int GimmickObjectController::EarlyUpdate()
{
    // 
    for (uint32_t i = 0; i < this->mlGimmickList.size(); i++)
    {
        // 
        this->mlGimmickList[i].mpExecutor->LateUpdate((this->mlGimmickList[i].mbTriggerSignal));
    }

    // 
    return 0;
}

int GimmickObjectController::Update()
{
    // 
    for (uint32_t i = 0; i < this->mlGimmickList.size(); i++)
    {
        // 
        this->mlGimmickList[i].mbTriggerSignal = this->mlGimmickList[i].mpTrigger->GetSignal();

        // 
        this->mlGimmickList[i].mpExecutor->Update((this->mlGimmickList[i].mbTriggerSignal));
    }

    // 
    return 0;
}

int GimmickObjectController::HitOnCollision(BaseCollision *myCollision, BaseCollision *hitCollision)
{
    // 
    return 0;
}

int GimmickObjectController::LateUpdate()
{
    // 
    for (uint32_t i = 0; i < this->mlGimmickList.size(); i++)
    {
        // 
        this->mlGimmickList[i].mpExecutor->LateUpdate((this->mlGimmickList[i].mbTriggerSignal));
    }

    // 
    return 0;
}

int GimmickObjectController::Draw()
{
    // 
    for (uint32_t i = 0; i < this->mlGimmickList.size(); i++)
    {
        // 
        this->mlGimmickList[i].mbTriggerSignal = this->mlGimmickList[i].mpTrigger->GetSignal();

        // 
        this->mlGimmickList[i].mpExecutor->Draw((this->mlGimmickList[i].mbTriggerSignal));
    }

    // 
    return 0;
}

// 
bool GimmickObjectController::AddGimmick(BaseGimmickTrigger *gimmickTrigger, BaseGimmickExecutor *gimmickExecutor)
{
    // 
    if (gimmickTrigger == nullptr ||
        gimmickExecutor == nullptr)
    {
        // 
        return false;
    }

    // 
    PuzzleGimmickData data;
    data.mbTriggerSignal = false;
    data.mpTrigger = gimmickTrigger;
    data.mpExecutor = gimmickExecutor;

    // 
    this->mlGimmickList.push_back(data);

    // 
    return true;
}
