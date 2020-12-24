#pragma once

#include <QObject>
#include <QString>
#include <QFileInfo>
#include <QDebug>
#include "results.h"
#include "compile_and_run_failure.h"

/**
 * @brief Abstracts the user-submitted code files.
 */
class Code : public QObject
{
    Q_OBJECT

    const QString language_;
    const QFileInfo file_;
    unsigned iters_;
    unsigned limit_;

protected:

    Results results;

public:

    explicit Code(const QString language, const QFileInfo file,
                  QObject *parent = nullptr, unsigned iters = 1,
                  unsigned limit = 0);
    Code(const Code&) = delete;
    virtual ~Code(){};

    const QString &get_language() const;
    const QFileInfo &get_file() const;
    const unsigned &get_iters() const;
    const unsigned &get_limit() const;
    const Results &get_results() const;

    void print_results() const;

    /**
     * @brief execute compiles and runs the code files.
     * @param read_fd pipe file descriptor read end
     * @param write_fd pipe file descriptor write end
     * @return bool true upon success
     */
    virtual bool execute(int read_fd, int write_fd) = 0;

signals:

public slots:
};

