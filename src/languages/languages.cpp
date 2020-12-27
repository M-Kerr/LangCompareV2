#include "languages.h"

Code *code_factory(const QString &language, const QString &file_name,
                   QObject *parent)
{
    // C++
    if (language.toLower() == "c++" || language.toLower() == "cpp")
    {
        auto code = new Code_Cpp(file_name, parent);
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
        auto code = new Code_Python(file_name, parent);
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
    QTextStream q_cin(stdin, QIODevice::ReadOnly);

    while (true)
    {
        // Print supported languages and receive input
        qInfo()   << "\nEnter a language to add, or 'R' to run\n"
                << "\t" << LANGUAGES.join(", ") << "\n";
        q_cin >> language;
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
        q_cin >> file_name;

        // Generate a Code* according to the input
        auto code = code_factory(language, file_name);
        if (code == nullptr)
        {
            qWarning() << "Code submission failed";
            continue;
        }

        // TODO request number of iterations and time limit
        // and save to Code member var

        qInfo() << file_name << " added successfully...\n\n";
        code_files.push_back(code);
    }
}
