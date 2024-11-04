#include "headers.h"
int compare(const void *p1, const void *p2)
{
    const struct checkJobs *elem1 = p1;
    const struct checkJobs *elem2 = p2;
    if (strcmp(elem1->jobname, elem2->jobname) == 0)
    {
        return 0;
    }
    else
    {
        int x = strlen(elem1->jobname), retval = -1;
        if (strlen(elem2->jobname) < x)
        {
            x = strlen(elem2->jobname);
            retval = 1;
        }
        for (int i = 0; i < x; i++)
        {
            if (elem1->jobname[i] > elem2->jobname[i])
            {
                return 1;
            }
            else if (elem1->jobname[i] < elem2->jobname[i])
            {
                return -1;
            }
        }
        return retval;
    }
}
int jobs(char *cmd)
{
    char buf[MAX_SIZE * 10];

    char *token1;
    char *res = cmd;
    strtok_r(NULL, " ", &res);

    char flag[200];
    flag[0] = '\0';
    int r_flag = 0, s_flag = 0;
    while ((token1 = strtok_r(NULL, " ", &res)) != NULL)
    {
        if (strcmp("-r", token1) == 0)
        {
            r_flag = 1;
        }
        if (strcmp("-s", token1) == 0)
        {
            s_flag = 1;
        }
        if ((strcmp("-sr", token1) == 0) || (strcmp("-rs", token1) == 0))
        {
            s_flag = 1;
            r_flag = 1;
        }
    }
    for (int i = 0; i < totalbgJobs; i++)
    {
        char buf[1000];
        int pid = jobsArr[i].pid;
        // printf("%d\n", pid);
        sprintf(buf, "/proc/%d/status", pid);
        // printf("%s\n", buf);
        FILE *fp = fopen(buf, "r");
        if (!fp)
        {
            jobsArr[i].status='E';
            // printf("jobs: error opening status file");
            continue;
        }
        char *line = NULL;
        size_t len = 0;
        int x = 0;
        char finStatus = 'E';
        while ((getline(&line, &len, fp)) != -1)

        {
            if (x == 2)
            {
                int id = getpgid(pid);
                line[strcspn(line, "\n")] = 0;
                char *token111 = strtok_r(NULL, " ", &line);
                // token111=strtok_r(NULL," ",&line);
                finStatus = token111[strlen(token111) - 1];
                break;
            }
            x++;
        }
        // printf("%c\n",finStatus);
        jobsArr[i].status = finStatus;
    }
    struct checkJobs useless;

    qsort(jobsArr, totalbgJobs, sizeof(useless), compare);
    for (int i = 0; i < totalbgJobs; i++)
    {
        if (jobsArr[i].status == 'T')
        {
            printf("[%d] Stopped %s [%d]\n", jobsArr[i].jobid, jobsArr[i].jobname, jobsArr[i].pid);
        }
        else if (jobsArr[i].status == 'R' || jobsArr[i].status == 'S')
        {
            printf("[%d] Running %s [%d]\n", jobsArr[i].jobid, jobsArr[i].jobname, jobsArr[i].pid);
        }
    }
    return 0;
    //     int status, pid, r = 0, s = 0;
    //     struct checkJobs *running = (struct checkJobs *)malloc(sizeof(struct checkJobs) * MAX_SIZE);
    //     struct checkJobs *stopped = (struct checkJobs *)malloc(sizeof(struct checkJobs) * MAX_SIZE);

    //     for (int i = 0; i < totalbgJobs; i++)
    //     {
    //         if (jobsArr[i].status == 'R')
    //         {
    //                         running[r]=jobsArr[i];

    //             running[r].pid = jobsArr[i].pid;
    //             running[r].status = jobsArr[i].status;
    //             strcpy(running[r++].jobname, jobsArr[i].jobname);
    //         }
    //         else if (jobsArr[i].status == 'T')
    //         {
    // stopped[s]=jobsArr[i];
    //             stopped[s].pid = jobsArr[i].pid;
    //             stopped[s].status = jobsArr[i].status;
    //             strcpy(stopped[s++].jobname, jobsArr[i].jobname);
    //         }
    //     }
    // struct checkJobs useless;
    // qsort(running, r, sizeof(useless), compare);
    // qsort(stopped, s, sizeof(useless), compare);
    // printf("%d\n%c\n%d\n", totalbgJobs,jobsArr[0].status,s);
    // if (r_flag == 1 && s_flag == 0)
    // {
    //     for (int i = 0; i < r; i++)
    //     {
    //         printf("[%d] Running %s [%d]\n", running[i].jobid, running[i].jobname, running[i].pid);
    //     }
    // }
    // else if ((s_flag == 1 && r_flag == 0))
    // {
    //     for (int i = 0; i < s; i++)
    //     {
    //         printf("[%d] Stopped %s [%d]\n", stopped[i].jobid, stopped[i].jobname, stopped[i].pid);
    //     }
    // }
    // else
    // {
    //     for (int i = 0; i < r; i++)
    //     {
    //         printf("[%d] Running %s [%d]\n", running[i].jobid, running[i].jobname, running[i].pid);
    //     }
    //     for (int i = 0; i < s; i++)
    //     {
    //         printf("[%d] Stopped %s [%d]\n", stopped[i].jobid, stopped[i].jobname, stopped[i].pid);
    //     }
    // }
    // return 0;
}