#include "cpp_code.h"


Cpp_Code::Cpp_Code(const QString file, const QString path,
                   QObject *parent, unsigned iters, unsigned limit)
    : Code("C++", file, path, parent, iters, limit)
{
}

bool Cpp_Code::execute(int read_fd, int write_fd)
{
    // Remove source and header extensions for executable name.
    // .chopped() removes n characters counting from the end, instead of
    // beginning...
    QString file = get_file_name();
    QString exe = file.chopped(
                        file.length() - file.lastIndexOf(
                        ".", -1, Qt::CaseInsensitive));

    // Triple escape characters pass forward the quote escape to shell.
    // The file name needs to be wrapped in quotes within the macro.
    QString compile_command = "clang++ -O3 -std=c++17 -Icpp/ -DFILEPATH=\\\""
                                   + get_file_path() + "\\\" -DFD=";
    compile_command += QString::number(write_fd);
    compile_command += " " + CPP_WRAPPER_FILE;
    compile_command += " -o ";
    compile_command += exe;

    qInfo() << "\nCompiling " << file << "...";
    int error_code = std::system(compile_command.toLatin1());
    if (error_code)
    {
        QString error = "Error during compilation of CPP " + file
                            + "\nError code " + QString::number(error_code);
        throw Compile_And_Run_Failure(error.toLatin1());
    }

    // Run CPP executable
    QString run_cpp_command =   "./" + exe + " "
                                + QString::number(get_iters()) + " "
                                + QString::number(get_limit());

    qInfo() << "Executing " << exe << "...\n";
    error_code = std::system(run_cpp_command.toLatin1());
    if (error_code)
    {
        QString error = "Error during execution of CPP " + exe
                            + "\nError code " + QString::number(error_code);
        throw Compile_And_Run_Failure(error.toLatin1());
    }

    results.receive(read_fd);
    print_results();

    return true;
}
