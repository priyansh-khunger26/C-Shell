#include "headers.h"
char ans[MAX_SIZE][MAX_SIZE];

int complete_util(char *arg)
{
    char name[MAX_SIZE];
    strcpy(name, arg);
    struct dirent **namelist;
    int n;
    char dirname[MAX_SIZE];
    getcwd(dirname, MAX_SIZE);
    n = scandir(dirname, &namelist, NULL, alphasort);
    if (n == -1)
    {
        perror("scandir");
    }
    char *buff_useless = (char *)malloc(200 * sizeof(char));
    strcpy(buff_useless, dirname);
    char hash[20] = "/";
    strcat(buff_useless, hash);
    int ptr = 0;
    for (int i = 0; i < n; i++)
    {
        if (namelist[i]->d_name[0] == '.')
        {
            continue;
        }
        char *fileChecker = (char *)malloc(200 * sizeof(char));
        strcpy(fileChecker, buff_useless);
        strcat(fileChecker, namelist[i]->d_name);
        struct stat st;
        stat(fileChecker, &st);
        int val = strlen(name);
        if (strlen(namelist[i]->d_name) < val)
        {
            val = strlen(namelist[i]->d_name);
        }
        int checkIfSame = 1;
        for (int x = 0; x < val; x++)
        {
            if (namelist[i]->d_name[x] != name[x])
            {
                checkIfSame = 0;
                break;
            }
        }
        if (checkIfSame == 1)
        {
            if (S_ISREG(st.st_mode) == 0)
            {
                char lmaolmao[MAX_SIZE];
                strcpy(lmaolmao, namelist[i]->d_name);
                strcat(lmaolmao, "/");
                strcpy(ans[ptr], lmaolmao);
            }
            else
            {
                char lmaolmao[MAX_SIZE];
                strcpy(lmaolmao, namelist[i]->d_name);
                strcat(lmaolmao, " ");
                strcpy(ans[ptr], lmaolmao);
            }
            ptr++;
        }
        free(namelist[i]);
        free(fileChecker);
    }

    free(buff_useless);
    return ptr;
}

int autocomplete(char *arg, char *val)
{
    char buf[MAX_SIZE], cmd[MAX_SIZE], res[MAX_SIZE];
    strcpy(cmd, arg);
    strcpy(res, arg);
    char *useless;
    char prevToken[MAX_SIZE];
    int numOfVals = 0;
    char execute[MAX_SIZE];
    char *token = strtok(res, " ");
    int tokenWasnull = 0;

    if (token == NULL)
    {
        char waste[2] = "\0";

        numOfVals = complete_util(waste);
        tokenWasnull = 1;

        printf("\n");

        for (int i = 0; i < numOfVals; i++)
        {
            printf("%s\n", ans[i]);
        }
        printDetails();
        return numOfVals;
    }
    else
    {
        strcpy(execute, token);

        while (token != NULL)
        {
            strcpy(prevToken, token);
            token = strtok(NULL, " ");
        }
        if (cmd[strlen(cmd) - 1] == ' ')
        {
            char waste[2] = "\0";
            strcpy(prevToken, waste);
            numOfVals = complete_util(waste);
        }
        else
        {
            numOfVals = complete_util(prevToken);
        }

        if (numOfVals == 1)
        {

            for (int i = 0; i < strlen(prevToken); i++)
            {
                printf("\b \b");
            }
            if (tokenWasnull == 1)
            {
                printf("%s\n", ans[0]);
                if (val[0] != '\0')
                    strcat(val, ans[0]);
                else
                    strcpy(val, ans[0]);
            }
            else
            {
                for (int i = 0; i < strlen(cmd) - strlen(prevToken); i++)
                {
                    // printf("%c", cmd[i]);
                    val[i] = cmd[i];
                }
                // printf("%d",strlen(ans[0]));
                if ((strlen(cmd) - strlen(prevToken)) != 0)
                    strcat(val, ans[0]);
                else
                {
                    strcpy(val, ans[0]);
                }
                printf("%s", ans[0]);
            }
        }
        else
        {
            printf("\n");

            for (int i = 0; i < numOfVals; i++)
            {
                printf("%s\n", ans[i]);
            }
            printDetails();
            for (int i = 0; i < strlen(cmd); i++)
            {
                printf("%c", cmd[i]);
                val[i] = cmd[i];
            }
            val[strlen(cmd)] = '\0';
        }
        return numOfVals;
    }
}