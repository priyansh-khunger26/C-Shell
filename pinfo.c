#include "headers.h"

int pinfo(char *command)
{
    char buf1[MAX_SIZE];
    char buf[MAX_SIZE * 10];
    int pid = getpid();
    strcpy(buf1, command);
    char *temp = strtok(buf1, " ");
    temp = strtok(NULL, " ");
    if (temp != NULL)
    {        
        temp[strlen(temp) +1] = '\0';

        for (int i = strlen(temp) - 1; i >= 0; i--)
        {
            if (!(temp[i] >= '0' && temp[i] <= '9'))
            {
                return -1;
            }
        }

        pid = atoi(temp);
        printf("%d\n",pid);

    }
    snprintf(buf, sizeof(buf), "/proc/%d/status", pid);
    // freopen("output.txt", "w", stdout);
    // system(buf);
    // freopen("/dev/tty", "w", stdout); /*for gcc, ubuntu*/
    char *token = strtok(buf, "\n");
    printf("pid : %d\n", pid);
    int i = 0;
    FILE *fp = fopen(buf, "r");
    char *line = NULL;
    size_t len = 0;

    while ((getline(&line, &len, fp)) != -1)

    {
        if (i == 2)
        {
            int id = getpgid(pid);
            line[strcspn(line, "\n")] = 0;

            if (id == pid)
                printf("process %s+\n", line);
            else
                printf("process %s\n", line);
        }
        if (i == 17)
        {
            char tok_util[MAX_SIZE];
            strcpy(tok_util, line);
            char *tk = strtok(tok_util, ":");
            tk = strtok(NULL, ":");
            tk[strcspn(tk, "\n")] = 0;
            printf("Process Memory: %s {Virtual Memory}\n", tk);
            break;
        }

        token = strtok(NULL, "\n");
        i++;
    }
    fclose(fp);
    sprintf(buf, "/proc/%d/exe", pid);
    char extractPath[MAX_SIZE];
    int lmaoheck;
    if ((lmaoheck = readlink(buf, extractPath, MAX_SIZE)) < 0)
    {
        printf("executable Path : Cannot extract the Path\n");
        return -1;
    }
    extractPath[lmaoheck] = '\0';
    char ans[MAX_SIZE];
    ans[0] = '~';
    int check = 1;
    for (int i = 0; i < strlen(initialDir); i++)
    {
        if (initialDir[i] != extractPath[i])
        {
            check = 0;
            break;
        }
    }

    if (check == 1)
    {
        int x = strlen(initialDir);
        for (int i = x; i < strlen(extractPath); i++)
        {
            ans[-x + i + 1] = extractPath[i];
        }
        ans[strlen(extractPath) - x + 1] = '\0';
    }
    else
    {
        strcpy(ans, extractPath);
    }
    printf("executable Path:%s\n", ans);
    return 0;
}