#pragma once

#include <QFileInfo>
#include <QMap>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QUrl>
#include "code.h"
#include "helpers/helpers.h"

//!@brief Languages class contains functions to build Code* objects
class Languages: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<QObject*> code_files READ get_code_files)

    static QQmlApplicationEngine *engine_;
public:
    explicit Languages(QObject *parent = nullptr);

    static QList<QObject*> code_files;

    static void start_qml(QQmlApplicationEngine *engine);
    Q_INVOKABLE static QList<QObject*> &get_code_files();

    /**
 * @brief code_factory builds Code subclasses.
 *
 * Builds a Code subclass according to the submitted file's language
 *
 * @param language code file language
 * @param file_name code file name and extension
 * @param parent Q_OBJECT parent pointer
 * @return Code *, nullptr on failure
 */

    /**
 * @brief Fills a vector with Code file objects via user input.
 */
    Q_INVOKABLE static void build_code_list();
    Q_INVOKABLE static bool qml_build_code_list(const QString &language,
                                                const QUrl &file_url,
                                                QObject *parent = nullptr,
                                                unsigned iters = 1,
                                                unsigned timeout = 0);

signals:
    void code_filesChanged();

public slots:
};
