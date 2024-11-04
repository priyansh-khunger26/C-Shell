#include "headers.h"

int pwd()
{
    char dir[MAX_SIZE];
    getcwd(dir, MAX_SIZE);
    printf("%s\n", dir);
    return 0;
}
