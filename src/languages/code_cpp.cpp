#include "code_cpp.h"


Code_Cpp::Code_Cpp(const QString file_name,
                   QObject *parent, unsigned iters, unsigned limit)
    : Code("C++", "code/cpp/" + file_name, parent, iters, limit)
{
}

bool Code_Cpp::execute(int read_fd, int write_fd)
{
    // Triple escape characters pass forward the quote escape to shell.
    // The file name needs to be wrapped in quotes within the macro.
    QString compile_command = "clang++ -O3 -std=c++17 -Icpp/ -DFILEPATH=\\\""
                                   + file_path() + "\\\" -DFD=";
    compile_command += QString::number(write_fd);
    compile_command += " " + CPP_WRAPPER_FILE;
    compile_command += " -o ";
    compile_command += output_file();

    qInfo() << "\nCompiling C++ " << file_name() << "...";
    int error_code = std::system(compile_command.toLatin1());
    if (error_code)
    {
        QString error = "Error during compilation of CPP " + file_name()
                            + "\nError code " + QString::number(error_code);
        throw Compile_And_Run_Failure(error.toLatin1());
    }

    // Run CPP executable
    QString run_cpp_command =   output_file() + " "
                                + QString::number(get_iters()) + " "
                                + QString::number(get_limit());

    qInfo() << "Executing C++ " << file_name() << "...\n";
    error_code = std::system(run_cpp_command.toLatin1());
    if (error_code)
    {
        QString error = "Error during execution of CPP " + file_name()
                            + "\nError code " + QString::number(error_code);
        throw Compile_And_Run_Failure(error.toLatin1());
    }

    results.receive(read_fd);
    return true;
}
