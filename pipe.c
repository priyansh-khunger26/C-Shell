#include <fcntl.h>
#include <stdio.h>
#include "headers.h"
int redirec(char *args)
{
    char cmd[MAX_SIZE], res[MAX_SIZE];
    strcpy(cmd, args);
    strcpy(res, args);
    char outputfile[MAX_SIZE], inputfile[MAX_SIZE], buf[MAX_SIZE], filename[MAX_SIZE];
    int prevfile = 0, append = 0, i, indirect = 0, outdirect = 0;
    char *token = strtok(res, " ");
    char execute[MAX_SIZE];
    for (i = 0; i < strlen(cmd); i++)
    {
        if (cmd[i] == '>' || cmd[i] == '<')
        {
            break;
        }
        execute[i] = cmd[i];
    }
    execute[i] = '\0';
    while (token != NULL)
    {
        if (strcmp(token, "<") == 0)
        {
            indirect = 1;
            token = strtok(NULL, " ");
            if (token == NULL)
            {
                perror("Input files not specified\n");
                return 0;
            }
            strcpy(inputfile, token);
        }

        if (token != NULL && strcmp(token, ">") == 0)
        {
            outdirect = 1;
            prevfile = 0;
            token = strtok(NULL, " ");
            if (token == NULL)
            {

                perror("Output files not specified\n");
                return 0;
            }
            strcpy(outputfile, token);
        }

        if (token != NULL && strcmp(token, ">>") == 0)
        {
            outdirect = 1, append = 1;
            prevfile = 0;
            token = strtok(NULL, " ");
            if (token == NULL)
            {

                printf("Output files not specified\n");
                return 0;
            }
            strcpy(outputfile, token);
        }

        token = strtok(NULL, " ");
    }
    if (outdirect == 1 && indirect == 1)
    {
        int inp = open(inputfile, O_RDONLY);
        if (inp < 0)
        {
            perror("Input file not opening");
            return 0;
        }
        dup2(inp, STDIN_FILENO);
        close(inp);
        int out;
        if (append == 1)
        {
            out = open(outputfile, O_WRONLY | O_APPEND | O_CREAT, 0644);
            if (out < 0)
            {
                perror("Outputfile not working");
                return 0;
            }
        }
        else
        {
            out = open(outputfile, O_WRONLY | O_TRUNC | O_CREAT, 0644);
            if (out < 0)
            {
                perror("Outputfile not working");
                return 0;
            }
        }
        dup2(out, STDOUT_FILENO);
        close(out);
    }

    else if (outdirect == 1)
    {
        int out;

        // sprintf(buf,"hi\n");
        // write(STDOUT_FILENO,buf,3);
        if (append == 1)
        {
            out = open(outputfile, O_WRONLY | O_APPEND | O_CREAT, 0644);
            if (out < 0)
            {
                perror("Outputfile not working");
                return 0;
            }
        }
        else
        {
            out = open(outputfile, O_WRONLY | O_TRUNC | O_CREAT, 0644);
            if (out < 0)
            {
                perror("Outputfile not working");
                return 0;
            }
        }
        dup2(out, STDOUT_FILENO);
        close(out);
    }
    else
    {

        int inp = open(inputfile, O_RDONLY);
        if (inp < 0)
        {
            perror("Input file not opening");
            return 0;
        }
        dup2(inp, STDIN_FILENO);
        close(inp);
    }
    support(execute);
    return 0;
}
int pipeHandle(char *cmd)
{
    char copier[200];

    char res[MAX_SIZE];
    strcpy(res, cmd);
    char buf[MAX_SIZE + 2];
    int cmdlen = strlen(cmd);
    int outputstore = dup(STDOUT_FILENO);
    int inputstore = dup(STDIN_FILENO);
    int countlol = 0, i;
    int pipes_try[2], pipes_try_prev[2];
    for (int i = 0; i < strlen(cmd); i++)
    {
        if (cmd[i] == '|')
        {
            countlol++;
        }
    }
    char *useless;
    if (pipe(pipes_try) < 0)
    {
        perror("Could not create pipe.");
        return 0;
    }
    char *token = strtok_r(res, "|", &useless);
    if (dup2(pipes_try[1], STDOUT_FILENO) == -1)
    {
        perror("cant duplicate");
        return 0;
    }
    close(pipes_try[1]);

    strcpy(copier, token);
    // support(copier); // change here.

    if (strchr(copier, '>') || strchr(copier, '<'))
    {
        redirec(copier);
    }
    else
    {
        support(copier);
    }
    token = strtok_r(NULL, "|", &useless);
    pipes_try_prev[0] = pipes_try[0];
    pipes_try_prev[1] = pipes_try[1];
    for (i = 1; i < countlol; i++)
    {
        if (pipe(pipes_try) < 0)
        {
            perror("Could not create pipe.");
            return 0;
        }
        strcpy(copier, token);

        dup2(pipes_try_prev[0], STDIN_FILENO);
        dup2(pipes_try[1], STDOUT_FILENO);
        // support(copier); // change here

        if (strchr(copier, '>') || strchr(copier, '<'))
        {
            redirec(copier);
        }
        else
        {
            support(copier);
        }
        close(pipes_try_prev[0]);
        close(pipes_try[1]);
        token = strtok_r(NULL, "|", &useless);

        pipes_try_prev[0] = pipes_try[0];
        pipes_try_prev[1] = pipes_try[1];
    }
    dup2(pipes_try[0], STDIN_FILENO);
    close(pipes_try[0]);
    dup2(outputstore, STDOUT_FILENO);

    strcpy(copier, token);

    if (strchr(copier, '>') || strchr(copier, '<'))
    {
        sprintf(buf, "%s\n", copier);
        // write(outputstore, buf, sizeof(buf));

        redirec(copier);
    }
    else
    {
        support(copier);
    }
    dup2(inputstore, STDIN_FILENO);
    return 0;
}