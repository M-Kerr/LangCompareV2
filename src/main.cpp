#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include <QVector>
#include "languages/languages.h"
#include "helpers/helpers.h"
#include <QQmlContext>



int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("LANGUAGES", QVariant::fromValue(LANGUAGES));
    qmlRegisterInterface<Code>("Code", 1);
//    qmlRegisterType<Code>("Code", 1, 0, "Code");
    QVector<Code*> code_files;



    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    if (!set_cwd_to_application_dir(argv)) return 1;



    // TODO: Parse argv input for a CLI argument to run application
    // in command line instead of GUI.
    // TODO: Uncomment below code.

    // Fill vector with user submitted code for benchmarking
    Languages::build_code_list(code_files);

    //Open pipe to receive results
    int pipe_fd[2];
    if (pipe(pipe_fd) < 0 )
    {
        qFatal("Pipe failed to open");
    }

    // Benchmark code
    for (Code *const code: qAsConst(code_files))
    {
        code->execute(pipe_fd[0], pipe_fd[1]);
    }

    // Print results
    for (const Code *code: qAsConst(code_files))
    {
        code->print_results();
    }

    return app.exec();
}
