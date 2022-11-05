#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
#endif

#include "debugmalloc.h"

int main() {
#ifdef _WIN32
    SetConsoleCP(1250);
    SetConsoleOutputCP(1250);
#endif
    debugmalloc_log_file("debugmalloc_log.txt");
    return 0;
}
