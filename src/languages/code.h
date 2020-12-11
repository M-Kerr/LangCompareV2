//TODO will have to call the IPC read function from the execute method
#pragma once

#include <QObject>
#include <QString>
#include <QDebug>
#include "results.h"
#include "compile_and_run_failure.h"

class Code : public QObject
{
    Q_OBJECT

    const QString _language;
    const QString _file_name;
    const QString _file_path;
    unsigned _iters;
    unsigned _limit;

protected:

    Results results;

public:

    explicit Code(const QString language, const QString file, const QString path,
                  QObject *parent = nullptr, unsigned iters = 1,
                  unsigned limit = 0);
    Code(const Code&) = delete;

    const QString &get_language();
    const QString &get_file_name();
    const QString &get_file_path();
    const unsigned &get_iters();
    const unsigned &get_limit();
    const Results &get_results();

    void print_results();

    virtual bool execute(int read_fd, int write_fd) = 0;

signals:

public slots:
};

