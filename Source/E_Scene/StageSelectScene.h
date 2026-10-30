#pragma once

#include "BaseScene.h"

#include "../Z_Except/CursorMoveSupporter.h"

class StageSelectScene : public BaseScene
{
public:
   // 
   StageSelectScene();

   // 
   ~StageSelectScene();

   // 
   int Create() override;

   // 
   int Initialize() override;

   // 
   int Finalize() override;

   // 
   int Update() override;

   // 
   int Draw() override;

private:
   // 
   int mnCurrentStage; //選択中のステージ

   // 
   unsigned long  mnUnlockStageCount;

   // 
   CursorMoveData mdMoveData;

   static const int StageMax = 12; // ステージの数

   int CubeHandle[StageMax];
   float CubeSize[StageMax];
   float CubeX[StageMax];
   float CubeY[StageMax];
   int CubeStage[StageMax];  // ステージを表示する場所

   int StageNum; //ステージの番号

   int MoveCount;     // 回転させてる時間
   int MoveDirection; // どっちに移動してるかの保存

   float Interval = 600; // 

   bool ChangeFlag;   // 移動させた瞬間のフラグ

   //      -300
   //-800        800
   //       300

   // 3 4 5 0 1 2
};