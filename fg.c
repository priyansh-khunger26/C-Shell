#include "headers.h"

int fg(char *cmd)
{
    cmd[strcspn(cmd, "\n")] = 0;
    char *token1;
    char *strtokUser;
    strtok_r(cmd, " ", &strtokUser);
    int jobNum, sigNum;
    char *s = strtok_r(NULL, " ", &strtokUser);
    if (s == NULL)
    {
        printf(RED"Job Number is NULL\n"RESET);
        return 0;
    }
    jobNum = atoi(s);

    int i;
    for (i = 0; i < totalbgJobs; i++)
    {
        if (jobsArr[i].jobid == jobNum)
        {
            break;
        }
    }
    if (i == totalbgJobs)
    {
        printf(RED "Job Number is Not possible\n" RESET);
        return 0;
    }
    forepid = jobsArr[i].pid;
    strcpy(forepname, jobsArr[i].jobname);
     signal(SIGTTOU,SIG_IGN);
    signal(SIGTTIN,SIG_IGN);
    tcsetpgrp(STDIN_FILENO, jobsArr[i].pid);

    kill(jobsArr[i].pid, SIGCONT);
    int status;
    waitpid(jobsArr[i].pid, &status, WUNTRACED);
    if (WIFSTOPPED(status))
    {
        jobsArr[i].status = 'T';
    }
    else
    {
        jobsArr[i].status = 'E';
    }
    tcsetpgrp(STDIN_FILENO, pidOfShell);
    forepid = pidOfShell;
    return 0;
}
