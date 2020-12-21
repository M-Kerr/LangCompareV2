#pragma once
#include "code.h"

/**
 * @brief CPP_WRAPPER_FILE path to C++ wrapper file
 * The C++ wrapper file benchmarks submitted code and returns
 * the results.
 */
static const QString CPP_WRAPPER_FILE("code/wrapper.cpp");

/**
 * @brief Code subclass representing C++ code files.
 */
class Cpp_Code : public Code
{
    Q_OBJECT

public:

    explicit Cpp_Code(const QFileInfo file,
                      QObject *parent = nullptr, unsigned iters= 1,
                      unsigned limit= 0);


    bool execute(int read_fd, int write_fd) override;

signals:

public slots:

};

