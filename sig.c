#include "headers.h"

int sig(char *cmd)
{

    cmd[strcspn(cmd, "\n")] = 0;
    char *token1;
    char *strtokUser;
    strtok_r(cmd, " ", &strtokUser);
    int jobNum, sigNum;
    char *jobNu = strtok_r(NULL, " ", &strtokUser);
    if (jobNu == NULL)
    {
        perror("Job Number is NULL");
        return 0;
    }
    jobNum = atoi(jobNu);
    char *signu = strtok_r(NULL, " ", &strtokUser);
    if (signu == NULL)
    {
        perror("Sig Number is NULL");
        return 0;
    }
    sigNum = atoi(signu);
    int i = 0;
    for (i = 0; i < totalbgJobs; i++)
    {
        if (jobsArr[i].jobid == jobNum)
        {
            break;
        }
    }
    if (i == totalbgJobs)
    {
        printf("Job Number does not exist\n");
        return 0;
    }
    if (kill(jobsArr[i].pid, sigNum) < 0)
    {
        printf("Could not execute\n");
        return 0;
    }
    return 0;
}