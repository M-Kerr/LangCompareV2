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
