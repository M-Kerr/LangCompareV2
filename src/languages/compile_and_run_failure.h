#pragma once
#include <exception>

class Compile_And_Run_Failure: public std::exception
{
    const char *_error;
    public:
        Compile_And_Run_Failure(const char *error)
            : _error(error){}
        const char* what() const _NOEXCEPT override
        {
            return _error;
        }
};