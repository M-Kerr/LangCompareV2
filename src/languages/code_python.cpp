#include "code_python.h"

Code_Python::Code_Python(const QString file_name,
                         QObject *parent, unsigned iters, unsigned limit)
    : Code("Python", "code/py/" + file_name, parent, iters, limit)
{
}

bool Code_Python::execute(int read_fd, int write_fd)
{
    QString python_command = "python3 " + PYTHON_WRAPPER_FILE;
    python_command      += " -name " + output_file()
                        + " -fd " + QString::number(write_fd)
                        + " -iter " + QString::number(get_iters())
                        + " -limit " + QString::number(get_limit());

    qInfo() << "\nExecuting Python " << output_file() << "...\n";
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
