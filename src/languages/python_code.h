#pragma once
#include "code.h"

// Path to Python wrapper file that benchmarks submitted code and returns
// results. Used as the entry point when running user submitted code.
static const QString PYTHON_WRAPPER_FILE("code/wrapper.py");

class Python_Code : public Code
{
    Q_OBJECT

protected:

public:

    explicit Python_Code(const QFileInfo file,
                         QObject *parent = nullptr,
                         unsigned iters= 1, unsigned limit= 0);

    bool execute(int read_fd, int write_fd) override;

signals:

public slots:

};

