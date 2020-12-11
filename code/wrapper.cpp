// Wrapper that times and runs CPP code
#include <iostream>
#include "helpers/benchmarking.hpp"
#include <unistd.h>
#include <string>
#ifdef FILEPATH
#include FILEPATH
#else
#error No C++ code file provided
#endif

#define MSGSIZE sizeof(long long int)

//TODO: Receive num iterations and timeout length CLI args
int main(int argc, char *argv[])
{
    Benchmarking::Timer timer{};
    try
    {
        execute();
        timer.stop();
    } 
    catch (...) 
    {
        std::cerr   << "Exception thrown during C++ execution" << std::endl;
        return 1;
    }
#ifdef FD
    // Convert timer.ns to string
    std::string ns_str = std::to_string(timer.ns);
    // write string size followed by newline
    std::string length = std::to_string(ns_str.size()) + '\n';
    if(write(FD, length.c_str(), length.size()) < 0)
        std::cerr << "Pipe write 1 failed" << std::endl;
    if (write(FD, ns_str.c_str(), ns_str.size()) < 0)
        std::cerr << "Pipe write 2 failed" << std::endl;
#else
#error Write file descriptor missing
#endif

    return 0;
}
