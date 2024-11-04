#include "headers.h"
int flag_d = 0;
int flag_f = 0;
int done = 0;
char dirname[200];
char filename[200];
int search = 0;
void initialise_discover()
{

    flag_d = 0;
    flag_f = 0;
    done = 0;
    search = 0;
    filename[0] = '\0';
}
void tokeniser_discover(char *token1)
{
    if (strcmp("-df", token1) == 0 || strcmp("-fd", token1) == 0)
    {
        flag_d = 1;
        flag_f = 1;
    }
    else if (strcmp("-d", token1) == 0)
    {
        flag_d = 1;
    }
    else if (strcmp("-f", token1) == 0)
    {
        flag_f = 1;
    }
    else if (strcmp("~", token1) == 0)
    {
        strcpy(dirname, homeDir);
        done = 1;
    }
    else if (strcmp(".", token1) == 0 || token1 == NULL)
    {
        strcpy(dirname, mydir);
        done = 1;
    }
     else  if (token1[0] == '"' )
    {
        if (token1[0] == '"')
        {
            char buffer_use[MAX_SIZE];
            int i;
            for ( i = 1; i < strlen(token1) - 1; i++)
            {
                buffer_use[i - 1] = token1[i];
            }
            buffer_use[i-1]='\0';
            
            strcpy(filename, buffer_use);
        }
        
    }
    else
    {
        if (token1[0] == '/')
        {
            struct stat st;

            stat(token1, &st);
            strcpy(dirname, token1);

            return;
        }
        char path[MAX_SIZE * 3];

        strcpy(path, mydir);
        strcat(path, "/");
        strcat(path, token1);

        struct stat st; // check if directory or file and return path
        stat(path, &st);
        strcpy(dirname, path);
        done++;
    }
    // if (token1[0] == '/')
    // {
    //     struct stat st;

    //     stat(token1, &st);
    //     strcpy(filename, token1);

    //     return;
    // }
    // char path[MAX_SIZE * 3];

    // strcpy(path, mydir);
    // strcat(path, "/");
    // strcat(path, token1);

    // struct stat st; // check if directory or file and return path
    // stat(path, &st);
}
void pathPrinter(char *file, int dir)
{
    char ans[MAX_SIZE];

    int x = strlen(mydir);
    x++;
    for (int i = x; i < strlen(file); i++)
    {
        ans[-x + i] = file[i];
    }
    ans[strlen(file) - x] = '\0';
    if (dir == 0)
    {
        printf(BLU "%s\n" RESET, ans);
    }
    else if (dir == 1)
    {
        printf(WHT "%s\n" RESET, ans);
    }
    else
    {
        printf(GRN "%s\n" RESET, ans);
    }
    return;
}
void discoverOut(char *path)
{
    if ((flag_d == 0 && flag_f == 0) || (flag_d == 1 && flag_f == 1))
    {
        struct dirent **namelist;
        int n = scandir(path, &namelist, NULL, alphasort);
        if (n == -1)
        {
            perror("scandir");
        }
        char *buff_useless = (char *)malloc(200 * sizeof(char));
        strcpy(buff_useless, path);
        char hash[20] = "/";
        strcat(buff_useless, hash);
        for (int i = 0; i < n; i++)
        {
            char *fileChecker = (char *)malloc(200 * sizeof(char));
            strcpy(fileChecker, buff_useless);
            strcat(fileChecker, namelist[i]->d_name);
            struct stat st;
            stat(fileChecker, &st);
            if (S_ISREG(st.st_mode) == 0)
            {
                // IS A DIRECTORY
                // if(!(strcmp(namelist[i]->d_name,".")==0 || strcmp(namelist[i]->d_name,"..")) )
                if (namelist[i]->d_name[0] != '.')
                {
                    // printf(BLU "%s\n" RESET, namelist[i]->d_name);
                    pathPrinter(fileChecker, 0);
                    discoverOut(fileChecker);
                }
            }
            else if (st.st_mode & S_IXUSR)
            {
                pathPrinter(fileChecker, 1);
            }
            else
            {
                pathPrinter(fileChecker, 2);
            }

            free(namelist[i]);
            free(fileChecker);
        }
        //  printf(BLU ".\n" RESET);

        free(buff_useless);
        return;
    }
    else if (flag_d == 1)
    {
        struct dirent **namelist;
        int n = scandir(path, &namelist, NULL, alphasort);
        if (n == -1)
        {
            perror("scandir");
        }
        char *buff_useless = (char *)malloc(200 * sizeof(char));
        strcpy(buff_useless, path);
        char hash[20] = "/";
        strcat(buff_useless, hash);
        for (int i = 0; i < n; i++)
        {
            char *fileChecker = (char *)malloc(200 * sizeof(char));
            strcpy(fileChecker, buff_useless);
            strcat(fileChecker, namelist[i]->d_name);
            struct stat st;
            stat(fileChecker, &st);
            if (S_ISREG(st.st_mode) == 0)
            {
                // IS A DIRECTORY
                // if(!(strcmp(namelist[i]->d_name,".")==0 || strcmp(namelist[i]->d_name,"..")) )
                if (namelist[i]->d_name[0] != '.')
                {
                    // printf(BLU "%s\n" RESET, namelist[i]->d_name);
                    pathPrinter(fileChecker, 0);
                    discoverOut(fileChecker);
                }
            }

            free(namelist[i]);
            free(fileChecker);
        }
        //  printf(BLU ".\n" RESET);

        free(buff_useless);
        return;
    }
    else if (flag_f == 1)
    {
        struct dirent **namelist;
        int n = scandir(path, &namelist, NULL, alphasort);
        if (n == -1)
        {
            perror("scandir");
        }
        char *buff_useless = (char *)malloc(200 * sizeof(char));
        strcpy(buff_useless, path);
        char hash[20] = "/";
        strcat(buff_useless, hash);
        for (int i = 0; i < n; i++)
        {
            char *fileChecker = (char *)malloc(200 * sizeof(char));
            strcpy(fileChecker, buff_useless);
            strcat(fileChecker, namelist[i]->d_name);
            struct stat st;
            stat(fileChecker, &st);
            if (S_ISREG(st.st_mode) == 0)
            {
                if (namelist[i]->d_name[0] != '.')

                    discoverOut(fileChecker);
            }
            else if (st.st_mode & S_IXUSR)
            {
                pathPrinter(fileChecker, 1);
            }
            else
            {
                pathPrinter(fileChecker, 2);
            }

            free(namelist[i]);
            free(fileChecker);
        }
        //  printf(BLU ".\n" RESET);

        free(buff_useless);
        return;
    }
}
void discoverSearch(char *path)
{
    
    if ((flag_d == 0 && flag_f == 0) || (flag_d == 1 && flag_f == 1))
    {
        struct dirent **namelist;
        int n = scandir(path, &namelist, NULL, alphasort);
        if (n == -1)
        {
            perror("scandir");
        }
        char *buff_useless = (char *)malloc(200 * sizeof(char));
        strcpy(buff_useless, path);
        char hash[20] = "/";
        strcat(buff_useless, hash);
        for (int i = 0; i < n; i++)
        {
            char *fileChecker = (char *)malloc(200 * sizeof(char));
            strcpy(fileChecker, buff_useless);
            strcat(fileChecker, namelist[i]->d_name);
            struct stat st;

            stat(fileChecker, &st);
            if (S_ISREG(st.st_mode) == 0)
            {
                if (namelist[i]->d_name[0] != '.')
                {
                    if (strcmp(namelist[i]->d_name, filename) == 0)
                    {
                        pathPrinter(fileChecker, 0);
                        search = 1;
                    }
                    discoverSearch(fileChecker);
                }
            }
            else if (st.st_mode & S_IXUSR)
            {
                if (strcmp(namelist[i]->d_name, filename) == 0)
                {
                    pathPrinter(fileChecker, 0);
                    search = 1;
                }
            }
            else
            {
                if (strcmp(namelist[i]->d_name, filename) == 0)
                {
                    pathPrinter(fileChecker, 0);
                    search = 1;
                }
            }

            free(namelist[i]);
            free(fileChecker);
        }
        //  printf(BLU ".\n" RESET);

        free(buff_useless);
        return;
    }
    else if (flag_d == 1)
    {
        struct dirent **namelist;
        int n = scandir(path, &namelist, NULL, alphasort);
        if (n == -1)
        {
            perror("scandir");
        }
        char *buff_useless = (char *)malloc(200 * sizeof(char));
        strcpy(buff_useless, path);
        char hash[20] = "/";
        strcat(buff_useless, hash);
        for (int i = 0; i < n; i++)
        {
            char *fileChecker = (char *)malloc(200 * sizeof(char));
            strcpy(fileChecker, buff_useless);
            strcat(fileChecker, namelist[i]->d_name);
            struct stat st;
            stat(fileChecker, &st);
            if (S_ISREG(st.st_mode) == 0)
            {
                if (namelist[i]->d_name[0] != '.')
                {
                    if (strcmp(namelist[i]->d_name, filename) == 0)
                    {
                        pathPrinter(fileChecker, 0);
                        search = 1;
                    }
                    discoverSearch(fileChecker);
                }
            }
            free(namelist[i]);
            free(fileChecker);
        }
        //  printf(BLU ".\n" RESET);

        free(buff_useless);
        return;
    }
    else if (flag_f == 1)
    {
        struct dirent **namelist;
        int n = scandir(path, &namelist, NULL, alphasort);
        if (n == -1)
        {
            perror("scandir");
        }
        char *buff_useless = (char *)malloc(200 * sizeof(char));
        strcpy(buff_useless, path);
        char hash[20] = "/";
        strcat(buff_useless, hash);
        for (int i = 0; i < n; i++)
        {
            char *fileChecker = (char *)malloc(200 * sizeof(char));
            strcpy(fileChecker, buff_useless);
            strcat(fileChecker, namelist[i]->d_name);
            struct stat st;
            stat(fileChecker, &st);
            if (S_ISREG(st.st_mode) == 0)
            {
                if (namelist[i]->d_name[0] != '.')
                {
                    discoverSearch(fileChecker);
                }
            }
            else if (st.st_mode & S_IXUSR)
            {
                if (strcmp(namelist[i]->d_name, filename) == 0)
                {
                    pathPrinter(fileChecker, 0);
                    search = 1;
                }
            }
            else
            {
                if (strcmp(namelist[i]->d_name, filename) == 0)
                {
                    pathPrinter(fileChecker, 0);
                    search = 1;
                }
            }

            free(namelist[i]);
            free(fileChecker);
        }
        //  printf(BLU ".\n" RESET);

        free(buff_useless);
        return;
    }
}
int discover(char *cmd)
{
    initialise_discover();
    strcpy(dirname, mydir);
    int checkIfFound = 0;

    cmd[strcspn(cmd, "\n")] = 0;
    char buf1[MAX_SIZE];
    char res[MAX_SIZE];
    strcpy(buf1, cmd);
    char *token1;
    char *buf = buf1;
    token1 = strtok_r(buf, " ", &buf);
    while ((token1 = strtok_r(buf, " ", &buf)) != NULL)
    {
        tokeniser_discover(token1);
    }
    if (filename[0] == '\0')
    {
        discoverOut(dirname);
        return 0;
    }
    else
    {
        // printf("%s\n", filename);
        discoverSearch(dirname);
    }
    if (search == 0)
    {
        printf(RED "File not found\n" RESET);
        discoverOut(dirname);
    }
    return 0;
}