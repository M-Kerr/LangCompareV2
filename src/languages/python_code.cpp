#include "python_code.h"

Python_Code::Python_Code(const QFileInfo file,
                         QObject *parent, unsigned iters, unsigned limit)
    : Code("Python", file, parent, iters, limit)
{
}

bool Python_Code::execute(int read_fd, int write_fd)
{
    QString python_command = "python3 " + PYTHON_WRAPPER_FILE;
    // Only needs file name with .py extension removed,
    // importlib doesn't like .py filenames or path separators
    python_command      += " -name " + file_name()
                        + " -fd " + QString::number(write_fd)
                        + " -iter " + QString::number(get_iters())
                        + " -limit " + QString::number(get_limit());


    qInfo() << "\nExecuting Python " << file_name() << "...\n";
    int error_code = std::system(python_command.toLatin1());
    if (error_code)
    {
        QString error = "Error during execution of Python " + file_name()
                            + "\nError code " + QString::number(error_code);
        throw Compile_And_Run_Failure(error.toLatin1());
    }

    results.receive(read_fd);
    return true;
}
