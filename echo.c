#include "headers.h"

int echo1(char *cmd)
{
    char *token1;
    char *res = cmd;
    strtok_r(NULL, " ", &res);
    int i = 0;
    while ((token1 = strtok_r(NULL, " ", &res)))
    {
        token1[strcspn(token1, "\n")] = 0;
        if (i != 0)
        {
            printf(" ");
        }
        printf("%s", token1);
        i++;
    }
    printf("\n");
    return 0;
}