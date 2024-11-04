#include "headers.h"
void delProcess(int id)
{
    int check = 0;
    for (int i = 0; i < bgProcessNum; i++)
    {
        if (processes[i].pid == id)
        {
            check = 1;
            for (int j = i + 1; j < bgProcessNum; j++)
            {
                processes[j - 1] = processes[j];
            }
            bgProcessNum--;
            break;
        }
    }
}
void checkIfProcessIsOver()
{
    pid_t pid;
    int status;
    int forestatus;
    while ((pid = waitpid(-1, &status, WNOHANG)) > 0)
    {
        // for (int x = 0; x < bgProcessNum; x++)
        // {

        // }

        for (int x = 0; x < totalbgJobs; x++)
        {
            if (pid == jobsArr[x].pid)
            {
                if (WIFSTOPPED(status))
                {
                    jobsArr[x].status = 'T';
                }
                else if (WIFCONTINUED(status))
                {
                    jobsArr[x].status = 'R';
                }
                else if (WIFEXITED(status))
                {
                    if (pid < 0)
                    {
                        perror(RED "Error in process over" RESET);
                    }
                    int exit = WEXITSTATUS(status);

                    if (exit == 0)
                    {
                        printf("\nProcess %d exited normally with status 0\n", pid);
                        if (forepid == pidOfShell)
                        {
                            printDetails();
                        }
                        else if (kill(forepid, 0))
                        {
                            printDetails();
                        }
                    }
                    else
                    {
                        printf("Some error in exiting, status:%d\n", exit);
                        printDetails();
                    }
                    fflush(stdout);
                    delProcess(pid);

                    jobsArr[x].status = 'E';
                }
            }
        }
    }
}
int background(char *cmd, int countAndChar)
{
    char buf1[200];
    char *arr[MAX_SIZE];
    char *token;
    strcpy(buf1, cmd);
    char *buf = buf1;
    token = strtok_r(buf, " ", &buf);
    int i;
    // strcpy(arr[0],token);
    for (i = 0; token != NULL; i++)
    {

        arr[i] = token;
        token = strtok_r(NULL, " ", &buf);
    }
    arr[i] = NULL;
    pid_t pid = fork();
    setpgid(0, 0);
    if (pid < 0)
    {
        perror(RED "fork not working" RESET);
    }
    else if (!pid)
    {
        pid_t check = getpid();
        if (!(execvp(arr[0], arr)))
            ;
        {
            perror(RED "Error in execvp\n" RESET);
        }
        return 0;
    }
    else
    {
        processes[bgProcessNum].pid = pid;
        strcpy(processes[bgProcessNum].jobname, arr[0]);
        bgProcessNum += 1;
        jobsArr[totalbgJobs].pid = pid;
        jobsArr[totalbgJobs].jobid = totalbgJobs + 1;
        strcpy(jobsArr[totalbgJobs].jobname, arr[0]);
        // jobsArr[totalbgJobs].status='R';
        totalbgJobs++;
return 0;
        // printf("%s\n",processes[0].jobname);
    }
}
int foreground(char *cmd)
{
    char buf1[200];
    char *arr[MAX_SIZE];
    char *token;
    strcpy(buf1, cmd);
    char *buf = buf1;

    token = strtok_r(buf, " ", &buf);
    int i;
    // strcpy(arr[0],token);
    for (i = 0; token != NULL; i++)
    {

        arr[i] = token;
        token = strtok_r(NULL, " ", &buf);
    }
    arr[i] = NULL;
    pid_t pid = fork();
    if (pid < 0)
    {
        perror(RED "fork not working" RESET);
        return -1;
    }

    else
    {
        forepid = pid;
        strcpy(forepname, arr[0]);

        if (!pid)
        {
            if (execvp(arr[0], arr) == -1)
            {
                perror(RED "error in execvp, command not found" RESET);
                return -1;
            }
        }
        else
        {
            int lmao;
            waitpid(pid, &lmao, WUNTRACED);
        }
        forepid=pidOfShell;
    }
    return 0;
}