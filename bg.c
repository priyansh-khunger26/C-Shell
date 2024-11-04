#include "headers.h"

int bg(char *cmd)
{
    cmd[strcspn(cmd, "\n")] = 0;
    char *token1;
    char *strtokUser;
    strtok_r(cmd, " ", &strtokUser);
    int jobNum, sigNum;
    char *s = strtok_r(NULL, " ", &strtokUser);
    if (s == NULL)
    {
        printf(RED "Job Number is NULL\n" RESET);
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
    if (jobsArr[i].status == 'R')
    {
        return 0;
    }
    if (jobsArr[i].status == 'T')
    {
        setpgid(jobsArr[i].pid, 0);
        kill(jobsArr[i].pid, SIGCONT);
        // printf("%s\n",jobsArr[i].jobname);
        // processes[bgProcessNum].pid = jobsArr[i].pid;
        // strcpy(processes[bgProcessNum].jobname, jobsArr[i].jobname);
        // bgProcessNum += 1;

        jobsArr[i].status = 'R';
    }
    return 0;
}
