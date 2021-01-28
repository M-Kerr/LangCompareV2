#pragma once

#include <QObject>
#include <QDebug>
#include <unistd.h>// Pipes
#include <errno.h>
#include <system_error>

class Results : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool success READ get_success NOTIFY successChanged)
    Q_PROPERTY(unsigned long long duration_ns READ get_duration_ns)
    Q_PROPERTY(double duration_us READ get_duration_us)
    Q_PROPERTY(double duration_ms READ get_duration_ms)

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
    void successChanged(bool);

public slots:
};



