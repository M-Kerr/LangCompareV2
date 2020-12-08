//TODO: refactor.
//      Iterations and iteration average result,
//      time limits, 
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <exception>
#include <errno.h>
#include <system_error>
#include <unistd.h>
#include "wrappers.h"

#define LANGUAGES "C++, Python"

struct Duration
{
    unsigned long long ns;
    double us;
    double ms;
};

class Compile_And_Run_Failure: public std::exception
{
    std::string _error;
    public:
        Compile_And_Run_Failure(std::string error)
            : _error(error){}
        const char* what() const _NOEXCEPT override
        {
            return _error.c_str();
        }
};

void print_duration(std::string name, unsigned long long int ns, double us, double ms)
{
    std::cout << "\n" << name << " Timing Duration: " << ns << "ns"
              << " (" << us << "us, " << ms << "ms)" << std::endl;
}

// Receives duration data as string from pipe/socket 
Duration receive(int fd)
{
    std::string data;
    std::vector<char> buf;
    // Reads chars into buffer until newline
    for (int i=0; ; i++)
    {
        buf.push_back('0');   // vector resizing
        if (read(fd, buf.data() + i, 1) < 0)
        {
            std::cerr << "Error reading stream size" << std::endl;
            throw std::system_error(errno, std::system_category());
        }
        if (buf[i] == '\n') break;
    }
    // Assign incomming message size to data
    buf.pop_back();
    data.assign(buf.data(), buf.size());
    size_t msg_size = std::stoi(data);
    buf.clear();
    buf.resize(msg_size);

    // Read incomming message
    if (read(fd, buf.data(), msg_size) < 0)
    {
        std::cerr << "Error reading pipe stream" << std::endl;
    }
    data.assign(buf.data(), buf.size());
    
    Duration d;
    d.ns = std::stoll(data);
    d.us = d.ns * 0.001;
    d.ms = d.us * 0.001;
    return d;
}

void compile_run_cpp(   const std::string &compile_command, 
                        const std::string &cpp_file, 
                        const std::string &cpp_class)
{
    std::cout << "\nCompiling " << cpp_file << "..." << std::endl;
    int error_code = std::system(compile_command.data());
    if (error_code)
    {
        std::string error = "Error during compilation of CPP " + cpp_file
                            + "\nError code " + std::to_string(error_code);
        throw Compile_And_Run_Failure(error);
    }

    // Execute CPP executable
    std::cout << "\nExecuting CPP " << cpp_class << "...\n" << std::endl;
    std::string run_cpp_command = "./" + cpp_class;
    error_code = std::system(run_cpp_command.data());
    if (error_code)
    {
        std::string error = "Error during execution of CPP " + cpp_class
                            + "\nError code " + std::to_string(error_code);
        throw Compile_And_Run_Failure(error);
    }
}

void run_python(    const std::string &python_file, 
                    const std::string &python_class, 
                    int fd, int iters= 1, int limit= 0)
{
    std::string python_command = "python ";
    python_command += PYTHON_WRAPPER_FILE;
    python_command += " -name " + python_file 
                    + " -cname " + python_class
                    + " -fd " + std::to_string(fd) 
                    + " -iter " + std::to_string(iters)
                    + " -limit " + std::to_string(limit);

    std::cout << "\nExecuting Python " << python_class << "..." << std::endl;
    int error_code = std::system(python_command.data());
    if (error_code)
    {
        std::string error = "Error during execution of Python " + python_class
                            + "\nError code " + std::to_string(error_code);
        throw Compile_And_Run_Failure(error);
    }
}

void take_input()
{
    std::cout   << "Select Language\n"
                << "\t" << LANGUAGES << "\n\n"
                << "...>>>";

    std::string language;
    std::cin >> language;

    std::transform(language.begin(), language.end(), language.begin(), std::tolower);
    //TODO sanitize input and compare to list of languages

    // Receive CPP and python file name input
    std::string cpp_file;
    std::cout << "Enter the cpp file name: ";
    std::cin >> cpp_file;

    std::string cpp_class = cpp_file.substr(0, cpp_file.rfind('.'));
    cpp_file = "CPP/code/" + cpp_file;

    std::string python_file;
    std::cout << "Enter the python file name: ";
    std::cin >> python_file;
}

void cpp_setup()
{
}
void python_setup()
{
}

int main()
{
    
   
    // Python importlib doesn't like .py filenames
    int ext = python_file.rfind('.');
    if (ext != std::string::npos)
    {
        python_file = python_file.substr(0, ext);
    }
    std::string python_class = python_file;

    //Open a pipe to receive results
    int pipe_fd[2];
    if (pipe(pipe_fd) < 0 )
    {
        std::cerr << "Pipe failed to open" << std::endl;
    }

    // Compile and link CPP executable
    std::string compile_command = "clang++ -O3 -std=c++17 -Isrc/ -DFILENAME=\\\"" 
                                   + cpp_file + "\\\" -DCLASSNAME=" + cpp_class +
                                  " -DFD="; 
    
    compile_command += std::to_string(pipe_fd[1]); 
    compile_command += " " + std::string(CPP_WRAPPER_FILE);
    compile_command += " -o ";
    compile_command += cpp_class;

    compile_run_cpp(compile_command, cpp_file, cpp_class);
    auto cpp_duration = receive(pipe_fd[0]);
    print_duration(cpp_class, cpp_duration.ns, cpp_duration.us, cpp_duration.ms);

    run_python(python_file, python_class, pipe_fd[1]);
    auto python_duration = receive(pipe_fd[0]);
    print_duration(python_class, python_duration.ns, python_duration.us,
                    python_duration.ms);
    // Compare and output results

    return 0;
}
