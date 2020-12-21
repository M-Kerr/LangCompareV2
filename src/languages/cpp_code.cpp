#include "cpp_code.h"


Cpp_Code::Cpp_Code(const QFileInfo file,
                   QObject *parent, unsigned iters, unsigned limit)
    : Code("C++", file, parent, iters, limit)
{
}

/**
 * @brief Cpp_Code::execute compiles and runs user submitted C++ code.
 *
 * includes user code into CPP_WRAPPER_FILE.
 *
 * @param read_fd pipe file descriptor read end.
 * @param write_fd pipe file descriptor write end.
 * @return bool true if successful.
 */
bool Cpp_Code::execute(int read_fd, int write_fd)
{
    // Remove extensions for executable name.
    QString file_name = get_file().completeBaseName();
    QString file_path = get_file().absoluteFilePath();

    // Triple escape characters pass forward the quote escape to shell.
    // The file name needs to be wrapped in quotes within the macro.
    QString compile_command = "clang++ -O3 -std=c++17 -Icpp/ -DFILEPATH=\\\""
                                   + file_path + "\\\" -DFD=";
    compile_command += QString::number(write_fd);
    compile_command += " " + CPP_WRAPPER_FILE;
    compile_command += " -o ";
    compile_command += file_name;

    qInfo() << "\nCompiling C++ " << file_name << "...";
    int error_code = std::system(compile_command.toLatin1());
    if (error_code)
    {
        QString error = "Error during compilation of CPP " + file_name
                            + "\nError code " + QString::number(error_code);
        throw Compile_And_Run_Failure(error.toLatin1());
    }

    // Run CPP executable
    QString run_cpp_command =   "./" + file_name + " "
                                + QString::number(get_iters()) + " "
                                + QString::number(get_limit());

    qInfo() << "Executing C++ " << file_name << "...\n";
    error_code = std::system(run_cpp_command.toLatin1());
    if (error_code)
    {
        QString error = "Error during execution of CPP " + file_name
                            + "\nError code " + QString::number(error_code);
        throw Compile_And_Run_Failure(error.toLatin1());
    }

    results.receive(read_fd);
    return true;
}
