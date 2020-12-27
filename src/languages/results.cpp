#include "results.h"

Results::Results(QObject *parent) : QObject(parent)
{
}

void Results::receive(int fd)
{
    std::string data_str;
    std::vector<char> buf;

    // Message header containing the incomming message's size
    // Reads chars into buffer until newline
    for (int i=0; ; i++)
    {
        buf.push_back('0');   // Create a new slot at the back of array to write
        if (read(fd, buf.data() + i, 1) < 0)
        {

            qWarning() << "Error reading stream size";
            throw std::system_error(errno, std::system_category());
        }
        if (buf[i] == '\n') break;
    }

    buf.pop_back(); // remove newline
    // Convert message size from string to size_t
    data_str.assign(buf.data(), buf.size());
    size_t msg_size = std::stoi(data_str);
    // Reset buf to receive incoming message
    buf.clear();
    buf.resize(msg_size);

    // receive duration data
    if (read(fd, buf.data(), msg_size) < 0)
    {
        qWarning() << "Error reading pipe stream";
    }
    data_str.assign(buf.data(), buf.size());

    duration_ns = std::stoll(data_str);
    duration_us = duration_ns * 0.001;
    duration_ms = duration_us * 0.001;
}

void Results::print() const
{
    qInfo() << "\n\tTiming Duration: " << duration_ns << "ns"
              << " (" << duration_us << "us, " << duration_ms << "ms)\n\n";
}
