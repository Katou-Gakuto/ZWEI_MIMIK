#pragma once

#include "BasePuzzleScene.h"

class PuzzleScene4_1 : public BasePuzzleScene
{
public:
    // 
    PuzzleScene4_1();

    // 
    ~PuzzleScene4_1() override;

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

class PuzzleScene4_2 : public BasePuzzleScene
{
public:
    // 
    PuzzleScene4_2();

    // 
    ~PuzzleScene4_2() override;

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

class PuzzleScene4_3 : public BasePuzzleScene
{
public:
    // 
    PuzzleScene4_3();

    // 
    ~PuzzleScene4_3() override;

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

class PuzzleScene4_4 : public BasePuzzleScene
{
public:
    // 
    PuzzleScene4_4();

    // 
    ~PuzzleScene4_4() override;

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
