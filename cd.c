#include "headers.h"

int cd(char *cmd)
{
    char *token;
    char *res = cmd;
    int numOfTokens = 0;
    char *token1;
    while ((token1 = strtok_r(res, " ", &res)))
    {
        token = token1;
        numOfTokens++;
    }
    if (numOfTokens > 2)
    {
        printf("Error in cd, Too many arguments\n");
        return -1;
    }
    token[strcspn(token, "\n")] = 0;

    if (numOfTokens==1)
    {
        strcpy(mydir, homeDir);
        chdir(homeDir);
        return 0;
    }

    if (strcmp(token, "~") == 0)
    {
        strcpy(mydir, homeDir);
        chdir(homeDir);
        return 0;
    }

    if (strcmp(token, "-") == 0)
    {
        int check = 1;
        char ans[MAX_SIZE];

        ans[0] = '~';

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
        printf("%s\n", ans);
        return 0;
    }

    char path[MAX_SIZE * 3];
    strcpy(path, mydir);
    strcat(path, "/");
    strcat(path, token);

    if (chdir(path) < 0)
    {

        printf(RED"%s\n"RESET, path);
        perror("Error in cd");
        return -1;
    }

    getcwd(mydir, MAX_SIZE);
    return 0;
    // if (strlen(mydir) < strlen(homeDir))
    // {
    //     chdir(homeDir);
    // }
}