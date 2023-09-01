#include "Common.h"

int println(const char *fmt, ...)
{
        char printf_buf[1024];
        va_list args;
        int printed;

        va_start(args, fmt);
        printed = vsprintf(printf_buf, fmt, args);
        va_end(args);

        puts(printf_buf);

        return printed;
}
