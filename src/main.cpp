#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include <QVector>
#include <QQmlContext>
#include <QString>
#include "languages/languages.h"
#include "helpers/helpers.h"

const QtMessageHandler QT_DEFAULT_MSG_HANDLER = qInstallMessageHandler(nullptr);
static QScopedPointer<Languages> languages_singleton(new Languages);

void qmlConsoleHandler(QtMsgType type, const QMessageLogContext &context,
                       const QString &msg)
{
    // The qml engine outputs its own messages to QtWarningMsg, will clutter
    // GUI's console
    if (type != QtWarningMsg)
    {
        emit languages_singleton->new_message(msg);
    }

   // Return message to default handler for terminal output
    (*QT_DEFAULT_MSG_HANDLER)(type, context, msg);
}

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

//    qmlRegisterSingletonInstance("Languages", 1, 0, "Languages",
//                                 languages_singleton.get());
    qmlRegisterType<Code>("Code", 1, 0, "Code");
    engine.rootContext()->setContextProperty("Languages",
                                             languages_singleton.get());

    Languages::set_engine(&engine);
    engine.rootContext()->setContextProperty(
                "code_files", QVariant::fromValue(Languages::code_files));

    QStringList available_languages = LANGUAGES.keys();
    engine.rootContext()->setContextProperty("LANGUAGES",
                                             QVariant::fromValue(
                                                 available_languages));
    engine.rootContext()->
            setContextProperty("ExecutableDir",
                               QString(QCoreApplication::applicationDirPath()));

    qInstallMessageHandler(qmlConsoleHandler);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    // Ensures working dir is the application's directory.
    //  Required for correct paths to user submitted code.
    if(!QDir::setCurrent(app.applicationDirPath())) return 1;

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
