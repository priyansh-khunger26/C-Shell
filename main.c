#include "headers.h"
void sigIntHandle(int signum)
{
    printf("\b \b\b \b");

    if (forepid == pidOfShell)
    {
        fflush(stdout);
        return;
    }
    else
    {
        kill(forepid, SIGINT);
        // tcsetpgrp(STDIN_FILENO,pidOfShell);
        forepid = pidOfShell;

        fflush(stdout);
        return;
    }
}
void sigStpHandle(int signum)
{
    int pid = getpid();

    if (forepid == pidOfShell)
    {
        return;
    }
    printf("\b \b\b \b");

    if (forepid != pidOfShell)
    {
        kill(forepid, SIGTTIN);
        kill(forepid, SIGTSTP);
        processes[bgProcessNum].pid = forepid;
        strcpy(processes[bgProcessNum].jobname, forepname);
        bgProcessNum += 1;
        jobsArr[totalbgJobs].pid = forepid;
        jobsArr[totalbgJobs].jobid = totalbgJobs + 1;
        strcpy(jobsArr[totalbgJobs].jobname, forepname);
        jobsArr[totalbgJobs].status = 'T';
        totalbgJobs++;
        return;
    }
    // signal(SIGTSTP, sigStpHandle);
    if (pid == pidOfShell)
    {
        // printDetails();
        // printf("\n");
        fflush(stdout);
    }
    // for (int i = 0; i < bgProcessNum; i++)
    // {
    //     kill(processes[i].pid, SIGTSTP);
    // }
    // if (forepid == pidOfShell)
    // {
    //     fflush(stdout);
    // }
    // else
    // {
    //     kill(forepid, SIGTSTP);
    //     forepid = pidOfShell;

    //     fflush(stdout);
    // }
    // exit(0);
}

void die(const char *s)
{
    perror(s);
    exit(1);
}

struct termios orig_termios;

void disableRawMode()
{
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1)
        die("tcsetattr");
}

void enableRawMode()
{
    if (tcgetattr(STDIN_FILENO, &orig_termios) == -1)
        die("tcgetattr");
    atexit(disableRawMode);
    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ICANON | ECHO);
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
        die("tcsetattr");
}

int main()
{
    totalbgJobs = 0;
    size_t size = 100;
    char *commands = (char *)malloc(sizeof(char) * size);
    bgProcessNum = 0;
    getcwd(mydir, MAX_SIZE);
    getcwd(initialDir, MAX_SIZE);
    getcwd(homeDir, MAX_SIZE);
    processes = (struct backgroundProcess *)malloc(sizeof(struct backgroundProcess) * MAX_SIZE);
    jobsArr = (struct checkJobs *)malloc(sizeof(struct checkJobs) * MAX_SIZE);
    signal(SIGINT, sigIntHandle);
    signal(SIGTSTP, sigStpHandle);
    signal(SIGCHLD, checkIfProcessIsOver);

    printTime[0] = '\0';
    forepid = getpid();
    pidOfShell = getpid();
    while (1)
    {

        setbuf(stdout, NULL);

        enableRawMode();
        memset(commands, '\0', 100);

        printDetails();

        char c;
        int pt = 0;
        int tabPressed = 0;
        while (read(STDIN_FILENO, &c, 1) == 1)
        {
            if (iscntrl(c))
            {
                if (c == 10)
                {

                    commands[pt++] = c;
                    printf("%c", c);
                    break;
                }

                else if (c == 9)
                {
                    char *storer;
                    storer = (char *)malloc(MAX_SIZE * sizeof(char));
                    memset(storer, '\0', MAX_SIZE);
                    int retval = autocomplete(commands, storer);
                    // printf("%ld\n",strlen(storer));
                    strcpy(commands, storer);
                    pt = strlen(commands);
                    //    printf("%s\n",storer);
                    tabPressed = 1;
                    // if (retval != 1)
                    // {
                    //     break;
                    // }
                }
                else if (c == 127)
                { // backspace
                    if (pt > 0)
                    {
                        // printf("%d\n",pt);
                        if (commands[pt - 1] == 9)
                        {

                            for (int i = 0; i < 7; i++)
                            {
                                printf("\b");
                            }
                        }
                        commands[--pt] = '\0';
                        printf("\b \b");
                    }
                }
                else if (c == EOF)
                {
                }
                else if (c == 4)
                {
                    exit(0);
                }
            }
            else
            {
                commands[pt++] = c;
                printf("%c", c);
            }
        }
        disableRawMode();
        // printf("\nInput Read: [%s]\n", commands);

        commands[pt] = '\0';
        char *token1;
        token1 = strtok_r(commands, ";", &commands);
        while (token1 != NULL)
        {
            token1[strcspn(token1, "\n")] = 0;
            int countTokensOfAnd = 0;
            char token_handle1[200];
            strcpy(token_handle1, token1);

            if (strchr(token_handle1, '&') != NULL)
            {
                countTokensOfAnd++;
                char *token_handle;
                char *token_handle11 = token_handle1;
                int countAndChar = 0;
                for (int i = 0; i < strlen(token_handle1); i++)
                {
                    if (token_handle1[i] == '&')
                    {
                        countAndChar++;
                    }
                }
                token_handle = strtok(token_handle11, "&");
                char prev[200];
                while (token_handle != NULL && countAndChar != 0)
                {
                    // printf("%s\n", token_handle);
                    background(token_handle, countAndChar);

                    countAndChar--;
                    token_handle = strtok(NULL, "&");
                }

                if (token_handle != NULL)
                {
                    int check_if_no_space = 0;
                    for (int i = 0; i < strlen(token_handle); i++)
                    {
                        if (isalpha(token_handle[i]))
                        {
                            check_if_no_space = 1;
                            break;
                        }
                    }
                    if (check_if_no_space == 1)
                        supportmain(token_handle);
                }

                //                     printf("%s\n",token1);
                // char *token_final;
                //                 for (int i = 0; i < countTokensOfAnd; i++)
                //                 {
                //                     background(token1);
                //                     // printf("%d\n",countTokensOfAnd);
                //                     token1 = strtok(NULL, "&");

                //                 }
            }

            else if (token1 != NULL)
            {
                supportmain(token1);
            }
            token1 = strtok_r(NULL, ";", &commands);
        }
        // if(tabPressed==1)
        // {
        //     printf("\n");
        // }
    }
}