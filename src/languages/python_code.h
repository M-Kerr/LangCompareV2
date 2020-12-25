#pragma once
#include "code.h"
#include <QDir>

static const QString PYTHON_WRAPPER_FILE("code/wrapper.py");

class Python_Code : public Code
{
    Q_OBJECT

protected:

public:

    explicit Python_Code(const QString file_name,
                         QObject *parent = nullptr, unsigned iters= 1,
                         unsigned limit= 0);

    //! @brief returns the relative file path in python module form.
    //! Python requires period separators and no .py extension.
    //! E.g., package.hello_world
    const QString module_name() const;

    bool execute(int read_fd, int write_fd) override;

signals:

public slots:

};

