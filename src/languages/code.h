#pragma once

#include <QObject>
#include <QString>
#include <QFileInfo>
#include <QDebug>
#include <QUrl>
#include "results.h"
#include "compile_and_run_failure.h"

//!@brief supported languages and their relative user-code subdirectory
static const QMap<QString, QString> LANGUAGES = {
    {"c++", "code/cpp/"},
    {"python", "code/py/"}
    // Add additional languages here...
};

static const QString CPP_WRAPPER_FILE("code/wrapper.cpp");
static const QString PYTHON_WRAPPER_FILE("code/wrapper.py");

/**
 * @brief Abstracts the user-submitted code files.
 */
class Code : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString language_ READ get_language WRITE set_language
               NOTIFY languageChanged)
    Q_PROPERTY(QUrl file_ READ get_file_url WRITE set_file
               NOTIFY fileChanged)
    Q_PROPERTY(unsigned iters_ READ get_iters WRITE set_iters
               NOTIFY itersChanged)
    Q_PROPERTY(unsigned limit_ READ get_limit WRITE set_limit
               NOTIFY limitChanged)

    QString language_;
    QFileInfo file_;
    unsigned iters_;
    unsigned limit_;

    bool cpp_execute_(int read_fd, int write_fd);
    bool python_execute_(int read_fd, int write_fd);

protected:

    Results results;

public:

    explicit Code(QObject *parent = nullptr);
    explicit Code(const QString language, const QString file_name,
                  QObject *parent = nullptr, unsigned iters = 1,
                  unsigned limit = 0);
    Code(const Code&) = delete;
    virtual ~Code(){};

    const QString &get_language() const;
    void set_language(QString language);
    const QFileInfo &get_file() const;
    QUrl get_file_url() const;
    void set_file(QUrl file_path);
    void set_file(QString file_path);
    const unsigned &get_iters() const;
    void set_iters(unsigned iters);
    const unsigned &get_limit() const;
    void set_limit(unsigned limit);

    const Results &get_results() const;

    //! @brief returns file name without extension.
    Q_INVOKABLE QString file_name() const;
    //! @brief returns absolute path to the file.
    Q_INVOKABLE QString file_path() const;
    //! @brief returns absolute path to the file, without the extension.
    Q_INVOKABLE QString output_file() const;

    Q_INVOKABLE void print_results() const;

    QString get_directory_prefix();

    /**
     * @brief execute compiles and runs the code files.
     * @param read_fd pipe file descriptor read end.
     * @param write_fd pipe file descriptor write end.
     * @return bool true upon success.
     */
    Q_INVOKABLE virtual bool execute(int read_fd, int write_fd);

signals:
    void languageChanged(QString language);
    void fileChanged(QString file);
    void itersChanged(unsigned iters);
    void limitChanged(unsigned limit);

public slots:
};
// Makes available for qobject_cast<Code> conversions
Q_DECLARE_INTERFACE(Code, "Code")
