#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include <QFile>
#include <QDir>
#include "languages/languages.h"
#include "helpers/clear_console.h"

// Builds a vector of Code file objects via user input
void build_code_list(QVector<Code *> &code_files)
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
int main(int argc, char *argv[])
{
    // Deprecated
    //QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/src/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    // Ensure working dir is the application's directory
    // Required for correct paths to user submitted code
    QFileInfo appfile(argv[0]);
    if (!QDir::setCurrent(appfile.absolutePath()))
    {
        qWarning() << "failed to change to application directory";
        return 1;
    }

    // Fill vector with user submitted code for benchmarking
    QVector<Code *> code_files;
    build_code_list(code_files);

    //Open pipe
    int pipe_fd[2];
    if (pipe(pipe_fd) < 0 )
    {
        qWarning() << "Pipe failed to open";
    }

    // Benchmark code
    for (const auto code: qAsConst(code_files))
    {
        code->execute(pipe_fd[0], pipe_fd[1]);
    }

    return app.exec();
}
