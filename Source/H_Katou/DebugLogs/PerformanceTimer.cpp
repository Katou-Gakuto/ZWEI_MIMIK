#include <fstream>
#include <Windows.h>

#include "PerformanceTimer.h"

PerformanceTimer::PerformanceTimer(const std::string& name)
: mName(name)
, mElapsedTime(0.0)
, mIsRunning(false)
{
}

// 計測開始
void PerformanceTimer::Start()
{
    mStartTime = std::chrono::steady_clock::now();
    mIsRunning = true;
}

// 計測終了
void PerformanceTimer::End()
{
    if (!mIsRunning)
    {
        return;
    }

    const auto endTime = std::chrono::steady_clock::now();

    mElapsedTime = std::chrono::duration<double, std::milli>(endTime - mStartTime).count();

    mIsRunning = false;

    OutputToFile();
}

// 計測結果をファイル出力
bool PerformanceTimer::OutputToFile() const
{
    std::string directory = "ReleaseTimeData";

    // フォルダ作成（既に存在する場合も問題なし）
    CreateDirectoryA(directory.c_str(), nullptr);

    const std::string filePath = directory + "/" + mName + ".txt";

    std::ofstream file(filePath, std::ios::app);

    if (!file.is_open())
    {
        return false;
    }

    file << "計測時間: " << mElapsedTime << " ms\n";

    return true;
}