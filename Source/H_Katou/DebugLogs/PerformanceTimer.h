#pragma once

#include <chrono>
#include <string>

class PerformanceTimer
{
private:
    std::string mName;
    std::chrono::steady_clock::time_point mStartTime;
    double mElapsedTime;

    bool mIsRunning;

public:
    PerformanceTimer(const std::string& name);

    // 計測開始
    void Start();

    // 計測終了
    void End();

    // 計測結果をファイル出力
    bool OutputToFile() const;
};
