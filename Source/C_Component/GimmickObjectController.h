
#include "BaseComponent.h"

#include <cstdint>
#include <vector>

#include "../F_PuzzleGimmick/PuzzleGimmickData.h"

#include "../Y_Tool/VECTOR.h"

/*
GameManagerにAddする順番は
Button→GimmickObject
にしてくださいな。
*/

/*
鏡は基本的には普通の壁と同じようにComponentを持たせる
工夫する部分はGameObject::Create()内で生成する当たり判定がただの四角じゃなくて
本来なら四角の当たり判定の部分を、4個のRayにし『鏡面判定のRay + 普通の壁のRay * 3』にするところ
*/

// 
class GimmickObjectController : public BaseComponent
{
public:
    // 
    GimmickObjectController(GameObject *myObject);

    //
    ~GimmickObjectController();

    int Create() override;
    int Initialize() override;
    int Finalize() override;
    int EarlyUpdate() override;
    int Update() override;
    int HitOnCollision(BaseCollision *myCollision, BaseCollision *hitCollision) override;
    int LateUpdate() override;
    int Draw() override;

    // 
    bool AddGimmick(BaseGimmickTrigger *gimmickTrigger, BaseGimmickExecutor *gimmickExecutor);

    // 
    template<class Trigger>
    std::vector<Trigger *> SearchGimmickTrigger() const
    {
        // 
        Trigger *current = nullptr;

        // 
        std::vector<Trigger *> outBox;

        // 
        for (size_t i = 0; i < this->mlGimmickList.size(); i++)
        {
            // 
            current = dynamic_cast<Trigger *>(this->mlGimmickList[i].mpTrigger);

            // 
            if (current == nullptr)
            {
                continue;
            }

            // 
            outBox.push_back(current);
        }

        // 
        return outBox;
    }

    // 
    template<class Executor>
    std::vector<Executor *> SearchGimmickExecutor() const
    {
        // 
        Executor *current = nullptr;

        // 
        std::vector<Executor *> outBox;

        // 
        for (size_t i = 0; i < this->mlGimmickList.size(); i++)
        {
            // 
            current = dynamic_cast<Executor *>(this->mlGimmickList[i].mpExecutor);

            // 
            if (current == nullptr)
            {
                continue;
            }

            // 
            outBox.push_back(current);
        }

        // 
        return outBox;
    }

    // 
    PuzzleGimmickData *GetGimmickBox() { return this->mlGimmickList.data(); }
    const PuzzleGimmickData *GetGimmickBox() const { return this->mlGimmickList.data(); }

    // 
    size_t GetGimmickCount() const { return this->mlGimmickList.size(); }

private:
    // 
    std::vector<PuzzleGimmickData> mlGimmickList;
};
