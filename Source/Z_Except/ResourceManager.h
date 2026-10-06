#pragma once
#include <DxLib.h>
#include <vector>
#include <string>

using namespace std;

class ResourceManager
{
public:
    ResourceManager();
    ~ResourceManager();

    int LoadMadel(string pathName);
    int LoadGraphics(string athName);
    int Update();
    int Draw();
    void DeleteAll();

    //int GetotaResource() { return resourceMapList.size() + graphicResourceMapList.size(); }

public:
    // リソースファイルの名前
	static string msResourceFile;

private:
    vector<pair<string, int>>resourceMapList;
    vector<pair<string, int>>graphicResourceMapList;
};