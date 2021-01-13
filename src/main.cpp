#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include <QVector>
#include "languages/languages.h"
#include "helpers/helpers.h"
#include <QQmlContext>
#include <QScopedPointer>
#include <QSharedPointer>



int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    Languages::start_qml(&engine);
//    Languages languages{};
//    qmlRegisterType<Code>("Languages", 1, 0, "Languages");
//    engine.rootContext()->setContextProperty("languages_instance", &languages);
//    QScopedPointer<Languages> languages_singleton(new Languages(&engine));
//    qmlRegisterSingletonInstance("Languages", 1, 0, "Languages",
//                                 languages_singleton.get());
    QStringList available_languages = LANGUAGES.keys();
    engine.rootContext()->setContextProperty("LANGUAGES",
                                             QVariant::fromValue(
                                                 available_languages));

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

/*
    // Fill vector with user submitted code for benchmarking
    Languages::build_code_list();

    //Open pipe to receive results
    // FIXME: turn these blocks into Languages:: methods
    int pipe_fd[2];
    if (pipe(pipe_fd) < 0 )
    {
        qFatal("Pipe failed to open");
    }

    // Benchmark code
    // FIXME: turn these blocks into Languages:: methods
    for (QObject *const code: qAsConst(Languages::code_files))
    {
        // I need to upcast the object ahhh
        Code *cp = qobject_cast<Code *>(code);
        cp->execute(pipe_fd[0], pipe_fd[1]);
    }

    // Print results
    // FIXME: turn these blocks into Languages:: methods
    for (const QObject *code: qAsConst(Languages::code_files))
    {
        Code *cp = qobject_cast<Code *>(code);
        cp->print_results();
    }
*/
    return app.exec();
}
