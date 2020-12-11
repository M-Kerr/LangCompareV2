#include "python_code.h"

Python_Code::Python_Code(const QString file, const QString path,
                         QObject *parent, unsigned iters, unsigned limit)
    : Code("Python", file, path, parent, iters, limit)
{
}

bool Python_Code::execute(int read_fd, int write_fd)
{

    // Only needs file name with .py extension removed,
    // importlib doesn't like .py filenames or path separators
    QString file = get_file_name();
    QString name_no_extension = file.chopped(
                file.length() - file.lastIndexOf("."));

    QString python_command = "python3 " + PYTHON_WRAPPER_FILE;
    python_command      += " -name " + name_no_extension
                        + " -fd " + QString::number(write_fd)
                        + " -iter " + QString::number(get_iters())
                        + " -limit " + QString::number(get_limit());


    qInfo() << "\nExecuting " << file << "...\n";
    int error_code = std::system(python_command.toLatin1());
    if (error_code)
    {
        QString error = "Error during execution of Python " + file
                            + "\nError code " + QString::number(error_code);
        throw Compile_And_Run_Failure(error.toLatin1());
    }

    results.receive(read_fd);
    print_results();

    return true;
}