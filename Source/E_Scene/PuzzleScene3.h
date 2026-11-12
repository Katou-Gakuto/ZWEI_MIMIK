#pragma once

#include "BasePuzzleScene.h"

class PuzzleScene3_1 : public BasePuzzleScene
{
public:
    // 
    PuzzleScene3_1();

    // 
    ~PuzzleScene3_1() override;

    // 
    int MapCreate(GameObjectManager &objManager) override;

    void GetMastObjectsInitPos(
        VECTOR2D &playerLightPos,
        VECTOR2D &playerShadowPos,
        VECTOR2D &goalLightPos,
        VECTOR2D &goalShadowPos) const override;

    // 
    void GetMapSize(VECTOR2D &mapSize) const override;

    // 
    uint32_t GetUseLightAreaCount() const override;
};

class PuzzleScene3_2 : public BasePuzzleScene
{
public:
    // 
    PuzzleScene3_2();

    // 
    ~PuzzleScene3_2() override;

    // 
    int MapCreate(GameObjectManager &objManager) override;

    void GetMastObjectsInitPos(
        VECTOR2D &playerLightPos,
        VECTOR2D &playerShadowPos,
        VECTOR2D &goalLightPos,
        VECTOR2D &goalShadowPos) const override;

    // 
    void GetMapSize(VECTOR2D &mapSize) const override;

    // 
    uint32_t GetUseLightAreaCount() const override;
};

class PuzzleScene3_3 : public BasePuzzleScene
{
public:
    // 
    PuzzleScene3_3();

    // 
    ~PuzzleScene3_3() override;

    // 
    int MapCreate(GameObjectManager &objManager) override;

    void GetMastObjectsInitPos(
        VECTOR2D &playerLightPos,
        VECTOR2D &playerShadowPos,
        VECTOR2D &goalLightPos,
        VECTOR2D &goalShadowPos) const override;

    // 
    void GetMapSize(VECTOR2D &mapSize) const override;

    // 
    uint32_t GetUseLightAreaCount() const override;
};

class PuzzleScene3_4 : public BasePuzzleScene
{
public:
    // 
    PuzzleScene3_4();

    // 
    ~PuzzleScene3_4() override;

    // 
    int MapCreate(GameObjectManager &objManager) override;

    void GetMastObjectsInitPos(
        VECTOR2D &playerLightPos,
        VECTOR2D &playerShadowPos,
        VECTOR2D &goalLightPos,
        VECTOR2D &goalShadowPos) const override;

    // 
    void GetMapSize(VECTOR2D &mapSize) const override;

    // 
    uint32_t GetUseLightAreaCount() const override;
};
