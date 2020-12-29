/* HEADER ONLY LIBRARY
 *
 * Very simple Timer object, times a section of code.
 * Currently does not support multiple iterations to calculate an average
 * execution time.
 *
 * This timing module is C++ only (no C), because the use of the <chrono> STL
 * header.
 *
 * Instantiate a Benchmarking::Timer object to time code within a scope,
 * Optionally, call .stop() at any time to stop the timer.
 */
#ifndef SRC_BENCHMARKING_HPP
#define SRC_BENCHMARKING_HPP

#include <stdio.h>
#include <chrono>
#include <string>

namespace Benchmarking
{

// Starts a timer upon instantiation.
// Instantiate this object above the code you want to time.
// Timer::stop() will stop the timer and calculate the duration.
class Timer
{
    bool stopped{true};
  public:
    
    //std::chrono::time_point<std::chrono::steady_clock> start_time_point;
    using Time = decltype(std::chrono::high_resolution_clock::now());
    Time end_time_point, start_time_point;
    
    //Nanoseconds, microseconds, milliseconds
    unsigned long long int ns{0};
    double us{0};
    double ms{0};
    
    Timer() = default;

    void start()
    {
        stopped = false;
        start_time_point = std::chrono::high_resolution_clock::now();
    }

    // Stops the timer and calculates duration.
    void stop()
    {
        if (!stopped)
        {
            end_time_point = std::chrono::high_resolution_clock::now();
            
            auto start =
                std::chrono::time_point_cast<std::chrono::nanoseconds>(
                    start_time_point).time_since_epoch().count();
            auto end = std::chrono::time_point_cast<std::chrono::nanoseconds>(
                end_time_point).time_since_epoch().count();
            
            ns = end - start;
            us = ns * 0.001;
            ms = us * 0.001;
            
            stopped = true;
        }
    }
};

int main();
} // namespace Benchmarking
#endif
