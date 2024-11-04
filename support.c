#include "headers.h"
int supportmain(char *cmd1)
{
    int outputstore = dup(STDOUT_FILENO);
    int inputstore = dup(STDIN_FILENO);

    char cmd[MAX_SIZE];
    strcpy(cmd, cmd1);
    int xxxx = 0;
    for (int i = 1; i < strlen(cmd); i++)
    {
        if (cmd[i] == '>' && cmd[i - 1] == '>')
        {
            xxxx = 1;
        }
    }
    if (strchr(cmd, '|'))
    {

        pipeHandle(cmd);
    }
    else if (strchr(cmd, '>') || strchr(cmd, '<'))
    {
        redirec(cmd);
    }

    else
    {
        support(cmd);
    }
    dup2(inputstore, STDIN_FILENO);
    dup2(outputstore, STDOUT_FILENO);
}
int support(char *cmd)
{

    char *token;
    char *token1;
    char res[MAX_SIZE];
    char forward[MAX_SIZE];
    strcpy(forward, cmd);
    char *res1 = cmd;
    strcpy(res, cmd);
    // token = strtok_r(res, " ", &res);
    int numOfTokens = 0;
    while ((token1 = strtok_r(res1, " ", &res1)))

    {
        if (numOfTokens == 0)
        {
            token = token1;
        }
        numOfTokens++;
    }
    // printf("%s\n",cmd);
    token[strcspn(token, "\n")] = 0;

    if (strcmp("echo", token) == 0)
    {
        // putInFile("echo\n");
        int x = echo1(res);
        if (x == 0)
        {
            putInFile(forward);
        }
    }
    else if (strcmp("pwd", token) == 0)
    {
        if (numOfTokens > 1)
        {
            printf("Too many arguments\n");
            return 0;
        }
        // putInFile("pwd\n");
        int x = pwd();
        if (x == 0)
        {
            putInFile(forward);
        }
    }
    else if (strcmp("cd", token) == 0)
    {

        int x = cd(res);
        if (x == 0)
        {
            putInFile(forward);
        }
    }
    else if (strcmp("pinfo", token) == 0)
    {

        int x = pinfo(res);
        if (x == 0)
        {
            putInFile(forward);
        }
    }
    else if (strcmp("history", token) == 0)
    {
        putInFile("history");
        extractHistory(res);
    }
    else if (strcmp("ls", token) == 0)
    {
        int x = ls(res);
        if (x == 0)
        {
            putInFile(forward); // error with semicolon, ls -al;
        }
    }
    else if (strcmp("discover", token) == 0)
    {
        int x = discover(res);
        if (x == 0)
        {
            putInFile(forward);
        }
    }
    else if (strcmp("exit", token) == 0)
    {
        putInFile("exit");
        exit(0);
    }
    else if (strcmp("jobs", token) == 0)
    {
        int x = jobs(res);
        if (x == 0)
        {
            putInFile(forward);
        }
    }
    else if (strcmp("sig", token) == 0)
    {

        int x = sig(res);
        if (x == 0)
        {
            putInFile(forward);
        }
    }
    else if (strcmp("fg", token) == 0)
    {
        time_t t;
        t = time(NULL);

        int x = fg(res);
        if (x == 0)
        {
            putInFile(forward);
        }
        int time_taken = time(NULL) - t;
        // double time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
        if (time_taken > 1)
        // printf("It took %d seconds to execute \n", time_taken);
        {
            char printTimeBuff[MAX_SIZE];
            sprintf(printTimeBuff, "took %d s", time_taken);
            strcpy(printTime, printTimeBuff);
        }
    }
    else if (strcmp("bg", token) == 0)
    {

        int x = bg(res);
        if (x == 0)
        {
            putInFile(forward);
        }
    }
    else
    {

        // printf(RED"Invalid Argument %s\n"RESET, token);
        time_t t;
        t = time(NULL);
        int x = foreground(res);
        forepid = getpid();
        int time_taken = time(NULL) - t;
        // double time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
        if (time_taken > 1)
        // printf("It took %d seconds to execute \n", time_taken);
        {
            char printTimeBuff[MAX_SIZE];
            sprintf(printTimeBuff, "took %d s", time_taken);
            strcpy(printTime, printTimeBuff);
        }
        if (x == 0)
        {
            putInFile(forward);
        }
    }
}