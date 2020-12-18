//TODO will have to call the IPC read function from the execute method
#pragma once

#include <QObject>
#include <QString>
#include <QFileInfo>
#include <QDebug>
#include "results.h"
#include "compile_and_run_failure.h"

class Code : public QObject
{
    Q_OBJECT

    const QString _language;
    const QFileInfo _file;
    unsigned _iters;
    unsigned _limit;

protected:

    Results results;

public:

    explicit Code(const QString language, const QFileInfo file,
                  QObject *parent = nullptr, unsigned iters = 1,
                  unsigned limit = 0);
    Code(const Code&) = delete;

    const QString &get_language() const;
    const QFileInfo &get_file() const;
    const unsigned &get_iters() const;
    const unsigned &get_limit() const;
    const Results &get_results() const;

    void print_results() const;

    virtual bool execute(int read_fd, int write_fd) = 0;

signals:

public slots:
};

