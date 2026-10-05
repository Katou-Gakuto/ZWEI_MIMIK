#pragma once

#include <chrono>
#include <cstdint>
#include <string>
#include <vector>

class PerformanceProfiler
{
public:
    using Clock = std::chrono::high_resolution_clock;
    using TimePoint = Clock::time_point;

    struct Result
    {
        std::string Name;

        uint64_t MeasureCount;

        double TotalMicroseconds;
        double AverageMicroseconds;
        double MinMicroseconds;
        double MaxMicroseconds;
        double MedianMicroseconds;
        double StandardDeviation;
    };

public:
    PerformanceProfiler();

    void Start(const std::string& name);
    void Stop();

    Result GetResult() const;

    void WritePerformanceResult(
        const std::string& fileName) const;

    void Reset();

private:
    std::string mName;

    TimePoint mStartTime;

    std::vector<double> mTimes;

    int mPlusFileNumber;
};