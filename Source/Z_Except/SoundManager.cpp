#include "SoundManager.h"

SoundManager::SoundManager()
{
    // BGM
    LoadBGM("Resource/Sound/学園アイドルマスター_初星学園_EndressDance.wav");// タイトル


    // SE
    LoadSE("Resource/Sound/入店音.mp3"); // ボタンSE

    ChangeVolume();
}
SoundManager::~SoundManager()
{
}


void SoundManager::Initialize()
{
}


void SoundManager::ChangeVolume()
{
	for (int i = 0; i < Sound_BGM_List.size(); i++)
	{
		ChangeVolumeSoundMem(mnBGMVolume, Sound_BGM_List.at(i).second);
	}
	for (int i = 0; i < Sound_SE_List.size(); i++)
	{
		ChangeVolumeSoundMem(mnSEVolume, Sound_SE_List.at(i).second);
	}
}


// BGMを読み込む
int SoundManager::LoadBGM(string pathName)
{
    // すでに読み込まれたデータか確認
    for (int i = 0; i < Sound_BGM_List.size(); i++)
    {
        if (Sound_BGM_List.at(i).first == pathName)
        {
            //return 0;
            return DuplicateSoundMem(Sound_BGM_List.at(i).second);
        }
    }

    // 読み込まれていなかったら
    int handle = LoadSoundMem(pathName.c_str());
    if (handle == -1)
    {
        return -1;
    }

    // 追加
    Sound_BGM_List.push_back(pair<string, int>(pathName, handle));
    return handle;
}
// SEを読み込む
int SoundManager::LoadSE(string pathName)
{
    // すでに読み込まれたデータか確認
    for (int i = 0; i < Sound_SE_List.size(); i++)
    {
        if (Sound_SE_List.at(i).first == pathName)
        {
            return DuplicateSoundMem(Sound_SE_List.at(i).second);
        }
    }

    // 読み込まれていなかったら
    int handle = LoadSoundMem(pathName.c_str());
    if (handle == -1)
    {
        return -1;
    }

    // 追加
    Sound_SE_List.push_back(pair<string, int>(pathName, handle));
    return handle;
}



// BGMを再生する
void SoundManager::PlayBGM(string pathName)
{
    // 再生
    for (int i = 0; i < Sound_BGM_List.size(); i++)
    {
        if (Sound_BGM_List.at(i).first == pathName)
        {
            //ChangeVolumeSoundMem(mnBGMVolume, Sound_BGM_List.at(i).second);
            PlaySoundMem(Sound_BGM_List.at(i).second, DX_PLAYTYPE_BACK);
            
            //NowBGM = Sound_BGM_List.at(i).second;

            break;
        }
    }
}
// SEを再生する
void SoundManager::PlaySE(string pathName)
{
    for (int i = 0; i < Sound_SE_List.size(); i++)
    {
        if (Sound_SE_List.at(i).first == pathName)
        {
            ChangeVolumeSoundMem(mnSEVolume, Sound_SE_List.at(i).second);
            PlaySoundMem(Sound_SE_List.at(i).second, DX_PLAYTYPE_BACK, true);
        
            break;
        }
    }
}



// 全ての音を止める
void SoundManager::StopAll()
{
    for (int i = 0; i < Sound_BGM_List.size(); i++)
    {
        StopSoundMem(Sound_BGM_List.at(i).second);
    }

    for (int i = 0; i < Sound_SE_List.size(); i++)
    {
        StopSoundMem(Sound_SE_List.at(i).second);
    }
}
// BGMだけ止める
void SoundManager::StopBGM()
{
    for (int i = 0; i < Sound_BGM_List.size(); i++)
    {
        StopSoundMem(Sound_BGM_List.at(i).second);
    }
}
// SEだけ止める
void SoundManager::StopSE()
{
    for (int i = 0; i < Sound_SE_List.size(); i++)
    {
        StopSoundMem(Sound_SE_List.at(i).second);
    }
}




// すべてのサウンドを削除する
void SoundManager::DeleteSound()
{
    for (int i = 0; i < Sound_BGM_List.size(); i++)
    {
        DeleteSoundMem(Sound_SE_List.at(i).second);
    }

    for (int i = 0; i < Sound_SE_List.size(); i++)
    {
        DeleteSoundMem(Sound_SE_List.at(i).second);
    }
}

void SoundManager::Finalize()
{
	// サウンドの削除
	DeleteSound();
}