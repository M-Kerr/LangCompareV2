#pragma once

#include <QObject>
#include <QDebug>
#include <unistd.h>// Pipes
#include <errno.h>
#include <system_error>

class Results : public QObject
{
    Q_OBJECT

    bool success = false;
    unsigned long long duration_ns{0};
    double duration_us{0};
    double duration_ms{0};

public:
    explicit Results(QObject *parent = nullptr);

    bool get_success() const;
    unsigned long long get_duration_ns() const;
    double get_duration_us() const;
    double get_duration_ms() const;

    // Currently receives duration data as string from pipe
    void receive(int fd);
    void print() const;


signals:

public slots:
};



