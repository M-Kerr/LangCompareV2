// Wrapper that times and runs CPP code
#include <iostream>
#include "helpers/benchmarking.hpp"
#include <unistd.h>
#include <string>
#include <thread>
#include <chrono>
#include <mutex>
#ifdef FILEPATH
#include FILEPATH
#else
#error No C++ code file provided
#endif

namespace cpp_wrapper
{
std::mutex pipe_lock;
Benchmarking::Timer timer{};

void return_results(long iters, bool success = true)
{
    std::lock_guard<std::mutex> guard(pipe_lock);
#ifdef FD
    // WARNING average may not be large enough to hold results
    long double average_ns = (success) ? timer.ns / iters : 0;
    auto average = std::to_string(average_ns);
    auto msg_length = std::to_string(average.size()) + '\n';
    auto success_str = std::to_string(success) + '\n';

    // Payload begins with a benchmarking success or failure bool '\n' delimited
    // Followed by the size of the message, '\n' delimited
    // Followed by the message (timing results)
    if(write(FD, success_str.c_str(), success_str.size()) < 0)
        std::cerr << "Pipe write results status failed" << std::endl;
    if(write(FD, msg_length.c_str(), msg_length.size()) < 0)
        std::cerr << "Pipe write header failed" << std::endl;
    if (write(FD, average.c_str(), average.size()) < 0)
        std::cerr << "Pipe write timing results failed" << std::endl;

    std::cout << "RESULTS SENT: " << average << std::endl;

    std::exit(EXIT_SUCCESS);
#else
#error Write file descriptor missing
#endif
}

void timeout(const long s)
{
    std::this_thread::sleep_for(std::chrono::seconds(s));
    std::cout << "Timeout reached, ending run" << std::endl;
    return_results(1, false);
}
} // namespace cpp_wrapper

int main(int argc, char *argv[])
{
    long iters = std::stol(argv[1]);
    long timeout_s = std::stol(argv[2]);
    std::thread timeout_t{};
    if (timeout_s)
    {
        timeout_t = std::thread(cpp_wrapper::timeout, timeout_s);
    }

    cpp_wrapper::timer.start();
    for (int i = 0; i < iters; i++)
    {
    try
    {
        execute();
    } 
    catch (...) 
    {
        std::cerr   << "Exception thrown during C++ execution" << std::endl;
        return 1;
    }
    }
    cpp_wrapper::timer.stop();
    cpp_wrapper::return_results(iters, true);
}
