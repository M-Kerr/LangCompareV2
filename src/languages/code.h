#pragma once

#include <QObject>
#include <QString>
#include <QFileInfo>
#include <QDebug>
#include "results.h"
#include "compile_and_run_failure.h"

static const QString CPP_WRAPPER_FILE("code/wrapper.cpp");
static const QString PYTHON_WRAPPER_FILE("code/wrapper.py");

/**
 * @brief Abstracts the user-submitted code files.
 */
class Code : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString language_ READ get_language)
    Q_PROPERTY(QFileInfo file_ READ get_file)
    Q_PROPERTY(QString iters_ READ get_iters)
    Q_PROPERTY(QString limit_ READ get_limit)

    const QString language_;
    const QFileInfo file_;
    unsigned iters_;
    unsigned limit_;

    bool cpp_execute(int read_fd, int write_fd);
    bool python_execute(int read_fd, int write_fd);
protected:

    Results results;

public:

    explicit Code(QObject *parent = nullptr): QObject(parent){};
    explicit Code(const QString language, const QString file_name,
                  QObject *parent = nullptr, unsigned iters = 1,
                  unsigned limit = 0);
    Code(const Code&) = delete;
    virtual ~Code(){};

    const QString &get_language() const;
    const QFileInfo &get_file() const;
    const unsigned &get_iters() const;
    const unsigned &get_limit() const;
    const Results &get_results() const;

    //! @brief returns file name without extension.
    Q_INVOKABLE QString file_name() const;
    //! @brief returns absolute path to the file's directory.
    Q_INVOKABLE QString file_path() const;
    //! @brief returns absolute path to the file, without the extension.
    Q_INVOKABLE QString output_file() const;

    void print_results() const;

    QString get_directory_prefix();

    /**
     * @brief execute compiles and runs the code files.
     * @param read_fd pipe file descriptor read end.
     * @param write_fd pipe file descriptor write end.
     * @return bool true upon success.
     */
    Q_INVOKABLE virtual bool execute(int read_fd, int write_fd);

signals:

public slots:
};
// Makes available for qobject_cast<Code> conversions
Q_DECLARE_INTERFACE(Code, "Code")
