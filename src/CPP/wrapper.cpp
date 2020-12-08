// Wrapper that times and runs CPP code
#include <iostream>
#include "CPP/benchmarking.hpp"
#include <unistd.h>
#include <string>
#ifdef FILENAME
#include FILENAME
#endif

#define MSGSIZE sizeof(long long int)

#ifdef CLASSNAME
//TODO: Receive num iterations and timeout length CLI args
int main(int argc, char *argv[])
{
    CLASSNAME code{};
    Benchmarking::Timer timer{};
    try
    {
        code.execute();
        timer.stop();
    } 
    catch (...) 
    {
        std::cerr   << "Exception thrown during execution" << std::endl;
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
#endif
#ifndef FD
#error Pipe file descriptor missing
#endif

    return 0;
}
#endif
#ifndef CLASSNAME
#error No C++ class provided
#endif

