#include "code.h"

Code::Code(const QString language, const QString file_name,
           QObject *parent, unsigned iters, unsigned limit)

    : QObject(parent), language_(language), file_(file_name),
      iters_(iters), limit_(limit), results(this)
{
    //TODO Delete debug line below
    qInfo() << language << " Code obj created";
    qInfo() << "file name " << file_name;

}

const QString &Code::get_language() const
{
    return language_;
}

const QFileInfo &Code::get_file() const
{
    return file_;
}

QString Code::file_name() const
{
    return file_.completeBaseName();
}

QString Code::file_path() const
{
    return file_.absoluteFilePath();
}

QString Code::output_file() const
{
    return file_.absolutePath() + "/" + file_name();
}

const unsigned &Code::get_iters() const
{
    return iters_;
}

const unsigned &Code::get_limit() const
{
    return limit_;
}

const Results &Code::get_results() const
{
    return results;
}

void Code::print_results() const
{
    qInfo().noquote().nospace() << "\n\t" << language_ << " "
                                << file_.completeBaseName() << " results:";
    results.print();
}

bool Code::cpp_execute(int read_fd, int write_fd)
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

bool Code::python_execute(int read_fd, int write_fd)
{
    QString python_command = "python3 " + PYTHON_WRAPPER_FILE;
    python_command      += " -name " + output_file()
                        + " -fd " + QString::number(write_fd)
                        + " -iter " + QString::number(get_iters())
                        + " -limit " + QString::number(get_limit());

    qInfo() << "\nExecuting Python " << file_name() << "...\n";
    int error_code = std::system(python_command.toLatin1());
    if (error_code)
    {
        QString error = "Error during execution of Python " + output_file()
                            + ". Error code " + QString::number(error_code);
        throw Compile_And_Run_Failure(error.toLatin1());
    }

    results.receive(read_fd);
    return true;
}

bool Code::execute(int read_fd, int write_fd)
{
    if (language_ == "c++")
    {
        cpp_execute(read_fd, write_fd);
    } else if (language_ == "python")
    {
        python_execute(read_fd, write_fd);
    }

    return true;
}
