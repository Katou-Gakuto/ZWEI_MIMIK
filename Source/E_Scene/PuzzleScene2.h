#pragma once

#include "BasePuzzleScene.h"

class PuzzleScene2_1 : public BasePuzzleScene
{
public:
    // 
    PuzzleScene2_1();

    // 
    ~PuzzleScene2_1() override;

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

class PuzzleScene2_2 : public BasePuzzleScene
{
public:
    // 
    PuzzleScene2_2();

    // 
    ~PuzzleScene2_2() override;

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

class PuzzleScene2_3 : public BasePuzzleScene
{
public:
    // 
    PuzzleScene2_3();

    // 
    ~PuzzleScene2_3() override;

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

class PuzzleScene2_4 : public BasePuzzleScene
{
public:
    // 
    PuzzleScene2_4();

    // 
    ~PuzzleScene2_4() override;

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
