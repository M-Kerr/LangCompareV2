#pragma once

#include <QFileInfo>
#include <QMap>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QUrl>
#include <QScopedPointer>
#include "code.h"
#include "helpers/helpers.h"

//!@brief Languages class contains functions to build Code* objects
class Languages: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<QObject*> code_files READ get_code_files)
    Q_PROPERTY(int read_fd_ READ get_read_fd)
    Q_PROPERTY(int write_fd_ READ get_write_fd)

    static QQmlApplicationEngine *engine_;
    static int read_fd_;
    static int write_fd_;
public:
    explicit Languages(QObject *parent = nullptr);

    void execute_code();

    static QList<QObject*> code_files;
    Q_INVOKABLE static QList<QObject*> &get_code_files();
    /*!
    * @brief Fills a vector with Code file objects via user input.
    */
    Q_INVOKABLE static void build_code_list();
    /*!
     * \brief qml_build_code_list builds a list of Code objects exposed to QML
     * Creating Code objects directly in QML instead of C++ is recommended,
     * however. See qml/components/CodeButton.qml
     */
    Q_INVOKABLE static bool qml_build_code_list(const QString &language,
                                                const QUrl &file_url,
                                                QObject *parent = nullptr,
                                                unsigned iters = 1,
                                                unsigned timeout = 0);

    static void set_engine(QQmlApplicationEngine *engine);
    static QQmlApplicationEngine *get_engine();
    static int get_read_fd();
    static int get_write_fd();

signals:
    void code_filesChanged();
    void new_message(QString);

public slots:
    //! @brief opens a pipe and sets read_fd_ and write_fd_
    void open_pipe();
};
