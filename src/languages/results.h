#pragma once

#include <QObject>
#include <QDebug>
#include <unistd.h>// Pipes
#include <errno.h>
#include <system_error>

class Results : public QObject
{
    Q_OBJECT

    unsigned long long duration_ns;
    double duration_us;
    double duration_ms;

public:
    explicit Results(QObject *parent = nullptr);

    // Currently receives duration data as string from pipe
    void receive(int fd);
    void print() const;

signals:

public slots:
};



