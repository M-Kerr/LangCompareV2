#include "python_code.h"

Python_Code::Python_Code(const QString file_name,
                         QObject *parent, unsigned iters, unsigned limit)
    : Code("Python", "code/py/" + file_name, parent, iters, limit)
{
}

const QString Python_Code::module_name() const
{
    //path() returns path without file
    QString name = get_file().path();
    // convert separators into periods
    name.replace(QDir::separator(), ".");
    // append filename
    name.append("." + file_name());
    return name;
}

bool Python_Code::execute(int read_fd, int write_fd)
{
    QString python_command = "python3 " + PYTHON_WRAPPER_FILE;
    // Only needs file name with .py extension removed,
    // importlib doesn't like .py filenames or path separators
    python_command      += " -name " + module_name()
                        + " -fd " + QString::number(write_fd)
                        + " -iter " + QString::number(get_iters())
                        + " -limit " + QString::number(get_limit());


    qInfo() << "\nExecuting Python " << output_file() << "...\n";
    int error_code = std::system(python_command.toLatin1());
    if (error_code)
    {
        QString error = "Error du.ri.ng execution of Python " + output_file()
                            + ". Error code " + QString::number(error_code);
        throw Compile_And_Run_Failure(error.toLatin1());
    }

    results.receive(read_fd);
    return true;
}
