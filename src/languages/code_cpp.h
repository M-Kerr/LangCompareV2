//// I can refactor the Code objects to be one class that calls execute
//// Depending on its language variable
//#pragma once
//#include "code.h"

//static const QString CPP_WRAPPER_FILE("code/wrapper.cpp");

//class Code_Cpp : public Code
//{
//    Q_OBJECT
//    Q_PROPERTY(QString language_ READ get_language)
//    Q_PROPERTY(QFileInfo file_ READ get_file)
//    Q_PROPERTY(QString iters_ READ get_iters)
//    Q_PROPERTY(QString limit_ READ get_limit)
//public:
////    explicit Code_Cpp(QObject *parent = nullptr) :Code(parent){}

//    explicit Code_Cpp(const QString file_name,
//                      QObject *parent = nullptr, unsigned iters= 1,
//                      unsigned limit= 0);

//    const QString get_language() const;
//    const QFileInfo &get_file() const;
//    const unsigned &get_iters() const;
//    const unsigned &get_limit() const;

//    bool execute(int read_fd, int write_fd) override;

//signals:

//public slots:

//};

