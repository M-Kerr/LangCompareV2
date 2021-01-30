#pragma once
#include <exception>

/**
 * @brief Exception class for a compile or a run failure on user-submitted code.
 */
class Compile_And_Run_Failure: public std::exception
{
    const char *_error;
    public:
        Compile_And_Run_Failure(const char *error)
            : _error(error){}
        const char* what() const noexcept override
        {
            return _error;
        }
};
