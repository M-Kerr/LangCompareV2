#include "helpers.h"

void clear_console()
{
#if defined _WIN32
#include<conio.h>
    clrscr();
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)\
    || defined(__APPLE__)
    qDebug() << u8"\033[2J\033[1;1H";
#endif
}

bool set_cwd_to_application_dir(char *argv[])
{
    QFileInfo appfile(argv[0]);
    if (!QDir::setCurrent(appfile.absolutePath()))
    {
        qCritical() << "failed to change cwd to application directory";
        return false;
    }
    return true;
}
