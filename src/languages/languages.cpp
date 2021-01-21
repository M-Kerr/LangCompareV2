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

void Languages::set_engine(QQmlApplicationEngine *engine)
{
    engine_ = engine;
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

        auto code = new Code(language, file_name, nullptr, iters, time);
        auto file = code->get_file();
        if (!file.exists())
        {
            qWarning() << "Code submission failed";
            delete code;
            continue;
        }

        qInfo() << file_name << " added successfully...\n\n";
        code_files.push_back(code);
    }
}

//TODO
void Languages::execute_code()
{
//    // Fill vector with user submitted code for benchmarking
//    Languages::build_code_list();

//    //Open pipe to receive results
//    // FIXME: turn these blocks into Languages:: methods
//    int pipe_fd[2];
//    if (pipe(pipe_fd) < 0 )
//    {
//        qFatal("Pipe failed to open");
//    }

//    // Benchmark code
//    // FIXME: turn these blocks into Languages:: methods
//    for (QObject *const code: qAsConst(Languages::code_files))
//    {
//        Code *cp = qobject_cast<Code *>(code);
//        cp->execute(pipe_fd[0], pipe_fd[1]);
//    }

//    // Print results
//    // FIXME: turn these blocks into Languages:: methods
//    for (const QObject *code: qAsConst(Languages::code_files))
//    {
//        Code *cp = qobject_cast<Code *>(code);
//        cp->print_results();
//    }
}

bool Languages::qml_build_code_list(const QString &language, const QUrl &file_url,
                                    QObject *parent, unsigned iters,
                                    unsigned timeout)
{
    auto code = new Code(language, file_url.toLocalFile(), parent, iters, timeout);
    auto file = code->get_file();
    if (!file.exists())
    {
        qWarning() << "Code submission failed";
        delete code;
        return false;
    }

    code_files.append(code);

    // Refresh the QML model
    engine_->rootContext()->setContextProperty(
                "code_files", QVariant::fromValue(code_files));

    return true;
}

void Languages::qml_execute_code()
{
    //Open pipe to receive results
    int pipe_fd[2];
    if (pipe(pipe_fd) < 0 )
    {
        qFatal("Pipe failed to open");
    }

    // NOTE: Our model is inside QML, will have to iterate through each CodeButton object
    // In the model inside QML.
    // Benchmark code
//    for (QObject *const code: qAsConst(Languages::code_files))
//    {
//        Code *cp = qobject_cast<Code *>(code);
//        cp->execute(pipe_fd[0], pipe_fd[1]);
//    }

    // NOTE: Our model is inside QML, will have to iterate through each
    // CodeButton object in the model inside QML.
    // TODO: need to create QML functionality to render charts of results
    // objects
    // Print results
//    for (const QObject *code: qAsConst(Languages::code_files))
//    {
//        Code *cp = qobject_cast<Code *>(code);
//        cp->print_results();
//    }
}

















































