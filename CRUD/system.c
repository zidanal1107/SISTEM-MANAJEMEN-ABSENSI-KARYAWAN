#include <stdio.h>
#include <stdlib.h>
#include "data.h"

void clear(void) {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}