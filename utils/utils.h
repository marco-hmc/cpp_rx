#pragma once

#include <chrono>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <utility>

enum class Status { kSuccess, kFailure };

#define DISABLE_COPY_AND_ASSIGN(ClassName) \
    ClassName(const ClassName&) = delete;  \
    ClassName& operator=(const ClassName&) = delete;

#define DISABLE_CONSTRUCTION(ClassName)   \
    ClassName() = delete;                 \
    ClassName(const ClassName&) = delete; \
    ClassName& operator=(const ClassName&) = delete;

#define DISABLE_MOVE(ClassName)      \
    ClassName(ClassName&&) = delete; \
    ClassName& operator=(ClassName&&) = delete;

namespace myUtils {
    template <typename Func, typename... Args>
    inline std::string measure_time(Func&& func, Args&&... args) {
        auto start = std::chrono::high_resolution_clock::now();
        std::forward<Func>(func)(std::forward<Args>(args)...);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration =
            std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
        double nanoseconds = duration.count();

        std::ostringstream oss;
        if (nanoseconds < 1000) {
            oss << std::fixed << std::setprecision(1) << nanoseconds << " ns";
        } else if (nanoseconds < 1000000) {
            double microseconds = nanoseconds / 1000;
            oss << std::fixed << std::setprecision(1) << microseconds << " μs";
        } else if (nanoseconds < 1000000000) {
            double milliseconds = nanoseconds / 1000000;
            oss << std::fixed << std::setprecision(1) << milliseconds << " ms";
        } else {
            double seconds = nanoseconds / 1000000000;
            oss << std::fixed << std::setprecision(2) << seconds << " s";
        }
        return oss.str();
    }

}  // namespace myUtils