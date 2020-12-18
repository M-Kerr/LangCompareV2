#include "results.h"

Results::Results(QObject *parent) : QObject(parent)
{
}

void Results::receive(int fd)
{
    std::string data;
    std::vector<char> buf;
    // Reads chars into buffer until newline
    for (int i=0; ; i++)
    {
        buf.push_back('0');   // vector resizing
        if (read(fd, buf.data() + i, 1) < 0)
        {

            qWarning() << "Error reading stream size";
            throw std::system_error(errno, std::system_category());
        }
        if (buf[i] == '\n') break;
    }
    // Assign incomming message size to data
    buf.pop_back();
    data.assign(buf.data(), buf.size());
    size_t msg_size = std::stoi(data);
    buf.clear();
    buf.resize(msg_size);

    // Read incomming message
    if (read(fd, buf.data(), msg_size) < 0)
    {
        qWarning() << "Error reading pipe stream";
    }
    data.assign(buf.data(), buf.size());

    duration_ns = std::stoll(data);
    duration_us = duration_ns * 0.001;
    duration_ms = duration_us * 0.001;
}

void Results::print() const
{
    qInfo() << "\n\tTiming Duration: " << duration_ns << "ns"
              << " (" << duration_us << "us, " << duration_ms << "ms)\n\n";
}
