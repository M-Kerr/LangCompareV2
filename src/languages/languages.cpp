#include "languages.h"

Languages::Languages(QObject *parent)
    : QObject(parent)
{
}

QQmlApplicationEngine *Languages::engine_ = nullptr;

QList<QObject *> Languages::code_files{};

QList<QObject *> &Languages::get_code_files()
{
    return code_files;
}



/* ==================================
 * EDIT THIS METHOD TO ADD A LANGUAGE
 * ================================== */
Code *Languages::code_factory(const QString &language, const QString &file_name,
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
/* ==================================
 * EDIT ABOVE METHOD TO ADD A LANGUAGE
 * ================================== */


void Languages::start_qml(QQmlApplicationEngine *engine)
{
    qmlRegisterUncreatableType<Languages>("Languagues", 1, 0, "Languages",
                                          "Static methods, only");
//    qmlRegisterType<Code>("Code", 1, 0, "Code");
//    qmlRegisterType<Code_Cpp>("Code", 1, 0, "Code_Cpp");
//    qmlRegisterAnonymousType<Code>("Code", 1);
    qmlRegisterInterface<Code>("Code", 1);
//    qmlRegisterAnonymousType<Languages>("Languages", 1);
    engine_ = engine;
    engine_->rootContext()->setContextProperty(
                "code_files", QVariant::fromValue(code_files));
}

void Languages::build_code_list()
{
    QString language;
    QTextStream q_stdin(stdin, QIODevice::ReadOnly);
    while (true)
    {
        // Print supported languages and receive input
        qInfo()   << "\nEnter a language to add, or 'R' to run\n"
                  << "\t" << LANGUAGES.keys().join(", ") << "\n";
        q_stdin >> language;
        language = language.toLower();

        if (language.toLower() == 'r')
        {
            clear_console();
            break;
        }
        else if (!LANGUAGES.contains(language))
        {
            qWarning() << "\nLanguage " << language << " not currently supported.";
            continue;
        }

        // Request the file's name.
        // Assumes file resides in ./code/<language> directory
        QString file_name;
        qInfo()     << "\nEnter the file name and extension (E.g., FileName.cpp): \n";
        q_stdin >> file_name;
        // Add relative code subdirectory
        file_name.prepend(LANGUAGES[language]);

        unsigned iters;
        qInfo() << "\nEnter the number of iterations to run,"
                << "averaging the results:\n";
        q_stdin >> iters;

        unsigned time;
        qInfo() << "\nEnter the timeout length in seconds. 0 == no timeout:\n";
        q_stdin >> time;

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


void Languages::qml_build_code_list(const QString &language, const QUrl &file_url,
                                    QObject *parent, unsigned iters,
                                    unsigned timeout)
{
    auto code_p = code_factory(language, file_url.toLocalFile(), parent, iters, timeout);
    if (!code_p)
    {
        qInfo() << "\nCODE_FACTORY FAILED\n";
        return;
    }

    code_files.append(code_p);

    // Refresh the QML model
    engine_->rootContext()->setContextProperty(
                "code_files", QVariant::fromValue(code_files));

    // FIXME: Delete debug below
    qInfo() << "THIS IS THE VALUE " +
               code_files.back()->property("language_").toString();
}

















































