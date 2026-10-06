#include "Dxlib.h"
#include "ResourceManager.h"
#include "../Z_Except/Master.h"
#include "../T_Model/DXModelAnim.h"

string ResourceManager::msResourceFile = "Resource/";

ResourceManager::ResourceManager()
{
}
ResourceManager::~ResourceManager()
{
}

int ResourceManager::LoadMadel(string pathName)
{

    for (int i = 0; i < resourceMapList.size(); i++)
    {
        //すでに読み込まれたデータか確認
        if (resourceMapList.at(i).first == pathName)
        {
            //読み込まれたデータを複製する
            return MV1DuplicateModel(resourceMapList.at(i).second);
        }
    }

    //読み込まれていなかったら
	int handle = LoadGraph(pathName.c_str());
    if (handle == -1)
    {
        return -1;
    }
    //vectorに追加
    resourceMapList.push_back(pair<string, int>(pathName, handle));
    return handle;
}

int ResourceManager::LoadGraphics(string pathName)
{
    //すでに読み込まれたデータか確認
    for (int i = 0; i < graphicResourceMapList.size(); i++)
    {
        if (graphicResourceMapList.at(i).first == pathName)
        {
            return graphicResourceMapList.at(i).second;
        }
    }
    //読み込まれていなかったら
    int handle = LoadGraph(pathName.c_str());
    if (handle == -1)
    {
        return -1;

    }
    graphicResourceMapList.push_back(pair<string, int>(pathName, handle));
    return handle;
}

int ResourceManager::Update()
{
	//Master::mpDXAnimModel->Update();
    return 0;
}

int ResourceManager::Draw()
{/*
    Master::mpDXAnimModel->Draw();*/
	return 0;
}

void ResourceManager::DeleteAll()
{
   // graphicResourceMapList.clear();
}


