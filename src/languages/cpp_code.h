#pragma once
#include "code.h"

// Path to C++ wrapper file that benchmarks submitted code and returns
// results. Used as the entry point when running user submitted code.
static const QString CPP_WRAPPER_FILE("code/wrapper.cpp");

class Cpp_Code : public Code
{
    Q_OBJECT

public:

    explicit Cpp_Code(const QFileInfo file,
                      QObject *parent = nullptr,
                      unsigned iters= 1, unsigned limit= 0);


    bool execute(int read_fd, int write_fd) override;

signals:

public slots:

};

