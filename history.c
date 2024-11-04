#include "headers.h"
char path[MAX_SIZE] = "/history.txt";
int putInFile(char *cmd)
{
    char path1[MAX_SIZE * 2];
    strcpy(path1, initialDir);
    strcat(path1, path);

    FILE *fp = fopen(path1, "r");
    if (fp == NULL)
    {
        FILE *fp1 = fopen(path1, "w");
        fclose(fp1);
    }
    fp = fopen(path1, "r");
    char *line;
    size_t len = 0;
    int lines = 1;

    if (fp != NULL)
    {
        char line1[200];
        while ((getline(&line, &len, fp)) != -1)
        {
            strcpy(line1, line);
            lines++;
        }
        fclose(fp);
        fp = fopen(path1, "a");

        char cmd1[MAX_SIZE];
        strcpy(cmd1, cmd);
        line1[strcspn(line1, "\n")] = 0;
        cmd1[strcspn(cmd1, "\n")] = 0;

        if (strcmp(line1, cmd1) == 0)
        {
            return 0;
        }
        fprintf(fp, "%s\n", cmd);
        fclose(fp);
    }
    char entireFile[22][200];
    if (lines > 20)
    {
        fp = fopen(path1, "r");
        int i = 0, read = 0;
        size_t len = 0;
        while ((read = getline(&line, &len, fp)) != -1)
        {

            strcpy(entireFile[i], line);
            i++;
        }
        fclose(fp);
        fp = fopen(path1, "w");
        i = 1;
        while (i < 20)
        {
            fprintf(fp, "%s", entireFile[i]);
            i++;
        }
        fprintf(fp, "%s\n", cmd);
        fclose(fp);
    }
    else
    {
        return 0;
    }
}
// most recent command at end of file

int extractHistory(char *cmd)
{
    char path1[MAX_SIZE * 2];
    strcpy(path1, initialDir);
    strcat(path1, path);
    size_t len = 0;
    int lines = 1;
    char *line;

    char buf1[MAX_SIZE];
    char buf[MAX_SIZE * 10];
    int num = 10;
    strcpy(buf1, cmd);
    char *temp = strtok(buf1, " ");
    temp = strtok(NULL, " ");

    if (temp != NULL)
    {
        // temp[strlen(temp) - 1] = '\0';

        for (int i = strlen(temp) - 1; i >= 0; i--)
        {
            if (!(temp[i] >= '0' && temp[i] <= '9'))
            {
                return -1;
            }
        }
        num = atoi(temp);
    }
    if (num > 20)
    {
        printf(RED "Only 20 values allowed" RESET);
        return -1;
    }
    if(num==0)
    {
        return 0;
    }
    // char hist[200] = "history ";
    // strcat(hist, cmd);
    putInFile(cmd);
    char entireFile[22][200];

    FILE *fp = fopen(path1, "r");
    int i = 0, read = 0;
    len = 0;
    while ((read = getline(&line, &len, fp)) != -1)
    {

        strcpy(entireFile[i], line);
        i++;
    }
    if (num > i)
    {
        num = i;
    }
    int beg=0;
    printf("%d\n",num);
    // if(i>10) beg=i-10;
    for (i = 20-num; i <20; i++)
    {
        printf("%s", entireFile[i]);
    }
    
    fclose(fp);
}