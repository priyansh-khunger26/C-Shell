#include "headers.h"

int printDetails()
{
    char *name;
    char ans[MAX_SIZE];
    getcwd(mydir, MAX_SIZE);
    gethostname(sysname, GLOBAL_VALS);
    name = getenv("USER");
    ans[0] = '~';
    int check = 1;
    for (int i = 0; i < strlen(initialDir); i++)
    {
        if (initialDir[i] != mydir[i])
        {
            check = 0;
            break;
        }
    }

    if (check == 1)
    {
        int x = strlen(initialDir);
        for (int i = x; i < strlen(mydir); i++)
        {
            ans[-x + i + 1] = mydir[i];
        }
        ans[strlen(mydir) - x + 1] = '\0';
    }
    else
    {
        strcpy(ans, mydir);
    }
    if (printTime[0] != '\0')
    {
        strcat(ans, printTime);
    }
    printf("<" WHT "%s" BLU "@%s" YEL ":%s" RESET ">", name, sysname, ans);
    if (printTime[0] != '\0')

        printTime[0] = '\0';
    return 0;
}