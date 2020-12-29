#include "languages.h"

Code *code_factory(const QString &language, const QString &file_name,
                   QObject *parent, unsigned iters, unsigned timeout)
{
    // C++
    if (language.toLower() == "c++" || language.toLower() == "cpp")
    {
        auto code = new Code_Cpp(file_name, parent, iters, timeout);
        auto file = code->get_file();
        if (file.exists())
        {
            return code;
        }
        else
        {
            delete code;
            return nullptr;
        }
    }
    // Python
    else if (language.toLower() == "python")
    {
        auto code = new Code_Python(file_name, parent, iters, timeout);
        auto file = code->get_file();
        if (file.exists())
        {
            return code;
        }
        else
        {
            delete code;
            return nullptr;
        }
    }
    else
    {
        return nullptr;
    }
}

void build_code_list(QVector<Code*> &code_files)
{
    QString language;
    QTextStream q_stdin(stdin, QIODevice::ReadOnly);
    while (true)
    {
        // Print supported languages and receive input
        qInfo()   << "\nEnter a language to add, or 'R' to run\n"
                << "\t" << LANGUAGES.join(", ") << "\n";
        q_stdin >> language;
        if (language.toLower() == 'r')
        {
            clear_console();
            break;
        }
        else if (!LANGUAGES.contains(language, Qt::CaseInsensitive))
        {
            qWarning() << "\nLanguage " << language << " not currently supported.";
            continue;
        }

        // Request the file's name.
        // Assumes file resides in ./code/<language> directory
        QString file_name;
        qInfo()     << "\nEnter the full file name (E.g., FileName.cpp): \n";
        q_stdin >> file_name;

        unsigned iters;
        do {
        qInfo() << "\nEnter the number of iterations to run, "
                   << "averaging the results:\n";
        q_stdin >> iters;
        } while (!iters);

        unsigned time;
        do {
        qInfo() << "\nEnter the timeout length in seconds. 0 == no timeout:\n";
        q_stdin >> time;
        } while (!time);

        // Generate a Code* according to the input
        auto code = code_factory(language, file_name, nullptr, iters, time);
        if (code == nullptr)
        {
            qWarning() << "Code submission failed";
            continue;
        }

        qInfo() << file_name << " added successfully...\n\n";
        code_files.push_back(code);
    }
}












































































































































