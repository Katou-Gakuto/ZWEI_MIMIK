#pragma once
#include <DxLib.h>
#include <vector>
#include <string>

using namespace std;

class SoundManager
{
public:

    SoundManager();
    ~SoundManager();

    // Ç±Ç±Ç≈Ç∑Ç◊Çƒì«Ç›çûÇﬁ
    void Initialize();
    void Finalize();

    // âπó í≤êÆ
    void SetBGMVolume(int volume) { mnBGMVolume = volume; }
    void SetSEVolume(int volume) { mnSEVolume = volume; }
    void ChangeVolume();

    // ì«Ç›çûÇ›
    int LoadBGM(string pathName);
    int LoadSE(string pathName);

    // çƒê∂
    void PlayBGM(string pathName);
    void PlaySE(string pathName);

    // í‚é~
    void StopAll();

    void StopBGM();
    void StopSE();

    // çÌèú
    void DeleteSound();

    // âπó 
    int mnBGMVolume = 255;
    int mnSEVolume = 155; 

private:

    // BGMvector
    vector<pair<string, int>> Sound_BGM_List;

    // SEMvector
    vector<pair<string, int>> Sound_SE_List;
};