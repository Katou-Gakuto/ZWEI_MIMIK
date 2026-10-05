#include "PerformanceProfiler.h"

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <numeric>
#include <windows.h>

#include <dbghelp.h>
#include <filesystem>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

PerformanceProfiler::PerformanceProfiler()
: mName()
, mStartTime()
, mTimes()
{
    int count = 1;
    std::string filename;
    while (true)
    {
        filename = "LogDebug/" + std::to_string(count) + "PerformanceLog.txt";

        
        DWORD attributes = GetFileAttributesA(filename.c_str());

        if (!(attributes != INVALID_FILE_ATTRIBUTES &&
            !(attributes & FILE_ATTRIBUTE_DIRECTORY)))
        {
            break;
        }
        count++;
    }
    mPlusFileNumber = count;
}

void PerformanceProfiler::Start(const std::string& name)
{
    mName = name;

    mStartTime = Clock::now();
}

void PerformanceProfiler::Stop()
{
    const TimePoint endTime = Clock::now();

    const double elapsedTime =
        std::chrono::duration<double, std::micro>(
            endTime - mStartTime
        ).count();

    mTimes.push_back(elapsedTime);
}

PerformanceProfiler::Result PerformanceProfiler::GetResult() const
{
    Result result{};

    result.Name = mName;
    result.MeasureCount = mTimes.size();

    if (mTimes.empty())
    {
        return result;
    }

    result.TotalMicroseconds =
        std::accumulate(
            mTimes.begin(),
            mTimes.end(),
            0.0
        );

    result.AverageMicroseconds =
        result.TotalMicroseconds /
        static_cast<double>(mTimes.size());

    result.MinMicroseconds =
        *std::min_element(
            mTimes.begin(),
            mTimes.end()
        );

    result.MaxMicroseconds =
        *std::max_element(
            mTimes.begin(),
            mTimes.end()
        );

    std::vector<double> sortedTimes = mTimes;

    std::sort(
        sortedTimes.begin(),
        sortedTimes.end()
    );

    const size_t middle = sortedTimes.size() / 2;

    if (sortedTimes.size() % 2 == 0)
    {
        result.MedianMicroseconds =
            (sortedTimes[middle - 1] +
                sortedTimes[middle]) / 2.0;
    }
    else
    {
        result.MedianMicroseconds =
            sortedTimes[middle];
    }

    double variance = 0.0;

    for (const double time : mTimes)
    {
        const double difference =
            time - result.AverageMicroseconds;

        variance += difference * difference;
    }

    variance /= static_cast<double>(mTimes.size());

    result.StandardDeviation =
        std::sqrt(variance);

    return result;
}

void PerformanceProfiler::WritePerformanceResult(
    const std::string& fileName) const
{
    const Result result = GetResult();

    std::ofstream defaultFile(
        "LogDebug/" + std::to_string(mPlusFileNumber) + "PerformanceLog.txt",
        std::ios::app
    );

    std::ofstream file(
        "LogDebug/" + std::to_string(mPlusFileNumber) + fileName,
        std::ios::app
    );

    if ((!file) || (!defaultFile))
    {
        return;
    }
    defaultFile << "01\n";

    file << std::fixed << std::setprecision(3);

    file << "========================================\n";
    file << "ˆ—‘¬“x‘ª’èŒ‹‰Ê\n";
    file << "========================================\n";

    file << "¦ ƒÊsiƒ}ƒCƒNƒ•bj‚Í0.000001•b‚Å‚·B\n\n";

    file << "yˆ—–¼z\n";
    file << result.Name << "\n\n";

    file << "y‘ª’è‰ñ”z\n";
    file << result.MeasureCount << " ‰ñ\n";
    file << "à–¾Fˆ—ŽžŠÔ‚ð‘ª’è‚µ‚½‰ñ”‚Å‚·B\n\n";

    file << "y‡Œvˆ—ŽžŠÔz\n";
    file << result.TotalMicroseconds << " us\n";
    file << "à–¾F‚·‚×‚Ä‚Ì‘ª’èŒ‹‰Ê‚ð‡Œv‚µ‚½ˆ—ŽžŠÔ‚Å‚·B\n\n";

    file << "y•½‹Ïˆ—ŽžŠÔz\n";
    file << result.AverageMicroseconds << " us\n";
    file << "à–¾F1‰ñ‚ ‚½‚è‚Ì•½‹Ïˆ—ŽžŠÔ‚Å‚·B\n\n";

    file << "yÅ¬ˆ—ŽžŠÔz\n";
    file << result.MinMicroseconds << " us\n";
    file << "à–¾F‘ª’è‚µ‚½’†‚ÅÅ‚àˆ—‚ª‘¬‚©‚Á‚½‚Æ‚«‚ÌŽžŠÔ‚Å‚·B\n\n";

    file << "yÅ‘åˆ—ŽžŠÔz\n";
    file << result.MaxMicroseconds << " us\n";
    file << "à–¾F‘ª’è‚µ‚½’†‚ÅÅ‚àˆ—‚ª’x‚©‚Á‚½‚Æ‚«‚ÌŽžŠÔ‚Å‚·B\n\n";

    file << "y’†‰›’lz\n";
    file << result.MedianMicroseconds << " us\n";
    file << "à–¾Fˆ—ŽžŠÔ‚ð¬‚³‚¢‡‚É•À‚×‚½‚Æ‚«‚Ì’†‰›‚Ì’l‚Å‚·B\n\n";

    file << "y•W€•Î·z\n";
    file << result.StandardDeviation << " us\n";
    file << "à–¾Fˆ—ŽžŠÔ‚ª•½‹Ï‚©‚ç‚Ç‚Ì’ö“x‚Î‚ç‚Â‚¢‚Ä‚¢‚é‚©‚ð•\‚µ‚Ü‚·B\n\n";

    file << "yÅ‘å|Å¬‚Ì·z\n";
    file << result.MaxMicroseconds -
        result.MinMicroseconds
        << " us\n";
    file << "à–¾FÅ‚à‘¬‚¢ˆ—‚ÆÅ‚à’x‚¢ˆ—‚ÌŽžŠÔ·‚Å‚·B\n\n";

    file << "========================================\n\n";
}

void PerformanceProfiler::Reset()
{
    mTimes.clear();
}