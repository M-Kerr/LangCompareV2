#include "results.h"

Results::Results(QObject *parent) : QObject(parent)
{
}

bool Results::get_success() const
{
    return success;
}

unsigned long long Results::get_duration_ns() const
{
    return duration_ns;
}

double Results::get_duration_us() const
{
    return duration_us;
}

double Results::get_duration_ms() const
{
    return duration_ms;
}

void Results::receive(int fd)
{
    std::string data_str;
    std::vector<char> buf;
    size_t msg_size;

    // The payload begins with a benchmarking success or failure character
    // 0 or 1 delimited with '\n'.
    // Followed by the size of the message, delimited with '\n'
    // Followed by the message (benchmarking results)

    // Read chars into buffer for the first two newlines
    for (int j = 0; j < 2; j++)
    {
        for (int i = 0; ; i++)
        {
            // Create a new slot at the back of array to write
            buf.push_back('0');
            if (read(fd, buf.data() + i, 1) < 0)
            {

                qWarning() << "Error reading stream";
                throw std::system_error(errno, std::system_category());
            }
            if (buf[i] == '\n')
            {
                break;
            }
        }
        // remove newline
        buf.pop_back();
        data_str.assign(buf.data(), buf.size());

        // success indicator
        if (j == 0)
        {
            success = std::stoi(data_str);
            if (success) emit successChanged(success);
            buf.clear();
            buf.resize(0);
        }
        // incomming message size
        else
        {
            msg_size = std::stoi(data_str);
            buf.clear();
            buf.resize(msg_size);
        }
    }

    // Timing results
    if (read(fd, buf.data(), msg_size) < 0)
    {
        qWarning() << "Error reading timing results";
    }
    data_str.assign(buf.data(), buf.size());

    // Assign results
    if (success)
    {
        duration_ns = std::stoll(data_str);
        duration_us = duration_ns * 0.001;
        duration_ms = duration_us * 0.001;
    }
}

void Results::print() const
{
    qInfo() << "\n\tTiming Duration: " << duration_ns << "ns"
              << " (" << duration_us << "us, " << duration_ms << "ms)\n\n";
}
