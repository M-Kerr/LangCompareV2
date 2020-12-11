#pragma once

#include "code.h"

static const QString PYTHON_WRAPPER_FILE("code/wrapper.py");

class Python_Code : public Code
{
    Q_OBJECT

protected:

public:

    explicit Python_Code(const QString file, const QString path,
                         QObject *parent = nullptr,
                         unsigned iters= 1, unsigned limit= 0);

    bool execute(int read_fd, int write_fd) override;

signals:

public slots:

};
