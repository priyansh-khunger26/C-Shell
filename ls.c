#include "headers.h"
char dirname[20][200];
char filename[20][200];
int flag_l = 0;
int flag_a = 0;
int dir = 0;
int file = 0;
long int total = 0;
void initialise()
{
    // dirname = malloc(20 * MAX_SIZE * sizeof(char));
    // filename = malloc(20 * MAX_SIZE * sizeof(char));

    flag_l = 0;
    flag_a = 0;
    dir = 0;
    file = 0;
    total = 0;
}
void tokeniser(char *token1)
{
    if (strcmp("-al", token1) == 0 || strcmp("-la", token1) == 0)
    {
        flag_a = 1;
        flag_l = 1;
    }
    else if (strcmp("-l", token1) == 0)
    {
        flag_l = 1;
    }
    else if (strcmp("-a", token1) == 0)
    {
        flag_a = 1;
    }
    else if (strcmp("~", token1) == 0)
    {
        strcpy(dirname[dir], homeDir);
        dir += 1;
    }
    else if (strcmp(".", token1) == 0 || token1 == NULL)
    {
        strcpy(dirname[dir], mydir);
        dir += 1;
    }
    else
    {
        if (token1[0] == '/')
        {
            struct stat st;

            stat(token1, &st);
            if (S_ISREG(st.st_mode) == 0)
            {
                strcpy(dirname[dir], token1);
                dir += 1;
            }
            else
            {
                strcpy(filename[file], token1);
                file += 1;
            }
            return;
        }
        char path[MAX_SIZE * 3];

        strcpy(path, mydir);
        strcat(path, "/");
        strcat(path, token1);

        struct stat st; // check if directory or file and return path
        stat(path, &st);
        if (S_ISREG(st.st_mode) == 0)
        {
            strcpy(dirname[dir], path);
            dir += 1;
        }
        else
        {
            strcpy(filename[file], path);
            file += 1;
        }
    }
}

int lsactual()
{
    struct dirent **namelist;
    int n;
    // when ls -a

    if (flag_a == 1 && flag_l == 0)
    {
        // for directories
        for (int x = 0; x < dir; x++)
        {

            n = scandir(dirname[x], &namelist, NULL, alphasort);
            if (n == -1)
            {
                perror("scandir");
            }
            char *buff_useless = (char *)malloc(200 * sizeof(char));
            strcpy(buff_useless, dirname[x]);
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
                    printf(BLU "%s\n" RESET, namelist[i]->d_name);
                }
                else if (st.st_mode & S_IXUSR)
                {
                    printf(WHT "%s\n" RESET, namelist[i]->d_name);
                }
                else
                {
                    printf(GRN "%s\n" RESET, namelist[i]->d_name);
                }
                free(namelist[i]);
                free(fileChecker);
            }
            free(buff_useless);
        }
        // for file
        for (int x = 0; x < file; x++)
        {
            char ans[200];

            int xx = strlen(mydir);
            for (int i = xx + 1; i < strlen(filename[x]); i++)
            {

                ans[-xx + i - 1] = filename[x][i];
            }

            ans[strlen(filename[x]) - xx - 1] = '\0';

            printf("%s\n", ans);
        }
    }

    else if (flag_a == 0 && flag_l == 0)
    {
        // for directories
        for (int x = 0; x < dir; x++)
        {

            n = scandir(dirname[x], &namelist, NULL, alphasort);
            if (n == -1)
            {
                perror("scandir");
            }
            char *buff_useless = (char *)malloc(200 * sizeof(char));
            strcpy(buff_useless, dirname[x]);
            char hash[20] = "/";
            strcat(buff_useless, hash);
            for (int i = 0; i < n; i++)
            {
                if (namelist[i]->d_name[0] == '.')
                {
                    continue;
                }
                char *fileChecker = (char *)malloc(200 * sizeof(char));
                strcpy(fileChecker, buff_useless);
                strcat(fileChecker, namelist[i]->d_name);
                struct stat st;
                stat(fileChecker, &st);
                if (S_ISREG(st.st_mode) == 0)
                {
                    // IS A DIRECTORY
                    printf(BLU "%s\n" RESET, namelist[i]->d_name);
                }
                else if (st.st_mode & S_IXUSR)
                {
                    printf(WHT "%s\n" RESET, namelist[i]->d_name);
                }
                else
                {
                    printf(GRN "%s\n" RESET, namelist[i]->d_name);
                }
                free(namelist[i]);
                free(fileChecker);
            }
            free(buff_useless);
        }
        // for file
        for (int x = 0; x < file; x++)
        {
            char ans[200];
            int xx = strlen(mydir);
            for (int i = xx + 1; i < strlen(filename[x]); i++)
            {

                ans[-xx + i - 1] = filename[x][i];
            }

            ans[strlen(filename[x]) - xx - 1] = '\0';

            printf("%s\n", ans);
        }
    }
    else if (flag_l == 1 && flag_a == 0)
    {

        // for directories
        for (int x = 0; x < dir; x++)
        {
            char mainFolder[200];
            struct stat mainDir;
            struct dirent *token_main;
            total = 0;
            DIR *folder = opendir(dirname[x]);
            while (token_main = readdir(folder))
            {

                strcpy(mainFolder, dirname[x]);
                strcat(mainFolder, "/");
                strcat(mainFolder, token_main->d_name);
                if (token_main->d_name[0] == '.')
                {
                    continue;
                }
                if (stat(mainFolder, &mainDir) < 0)
                {
                    perror(mainFolder);
                    return -1;
                }
                total += mainDir.st_blocks;
            }
            printf("Total: %ld\n", total / 2);
            n = scandir(dirname[x], &namelist, NULL, alphasort);
            if (n == -1)
            {
                perror("scandir");
            }
            char *buff_useless = (char *)malloc(200 * sizeof(char));
            strcpy(buff_useless, dirname[x]);
            char hash[20] = "/";

            strcat(buff_useless, hash);

            for (int i = 0; i < n; i++)
            {
                if (namelist[i]->d_name[0] == '.')
                {
                    continue;
                }
                char *fileChecker = (char *)malloc(200 * sizeof(char));
                strcpy(fileChecker, buff_useless);
                strcat(fileChecker, namelist[i]->d_name);
                struct stat st;
                int num = stat(fileChecker, &st);

                if (num < 0)
                {
                    perror(RED "ERROR IN ls -l -a <names>" RESET);
                    return -1;
                }
                printf((S_ISDIR(st.st_mode)) ? "d" : "-");
                printf((st.st_mode & S_IRUSR) ? "r" : "-");
                printf((st.st_mode & S_IWUSR) ? "w" : "-");
                printf((st.st_mode & S_IXUSR) ? "x" : "-");
                printf((st.st_mode & S_IRGRP) ? "r" : "-");
                printf((st.st_mode & S_IWGRP) ? "w" : "-");
                printf((st.st_mode & S_IXGRP) ? "x" : "-");
                printf((st.st_mode & S_IROTH) ? "r" : "-");
                printf((st.st_mode & S_IWOTH) ? "w" : "-");
                printf((st.st_mode & S_IXOTH) ? "x" : "-");
                printf("\t");
                printf("%lu\t", st.st_nlink);
                printf("%s\t%s\t", getpwuid(st.st_uid)->pw_name, getgrgid(st.st_gid)->gr_name);
                printf("%ld\t", st.st_size);
                char date[20];
                strftime(date, 20, "%b %d   %H:%M", localtime(&(st.st_ctime)));
                printf("%s\t", date);
                if (S_ISREG(st.st_mode) == 0)
                {
                    // IS A DIRECTORY
                    printf(BLU "%s\n" RESET, namelist[i]->d_name);
                }
                else if (st.st_mode & S_IXUSR)
                {
                    printf(WHT "%s\n" RESET, namelist[i]->d_name);
                }
                else
                {
                    printf(GRN "%s\n" RESET, namelist[i]->d_name);
                }

                free(namelist[i]);
                free(fileChecker);
            }
            free(buff_useless);
        }
        // for file
        for (int x = 0; x < file; x++)
        {
            char ans[200];

            struct stat st;
            int num = stat(filename[x], &st);

            if (num < 0)
            {
                perror(RED "ERROR IN ls -l -a <names>" RESET);
                return -1;
            }

            printf((S_ISDIR(st.st_mode)) ? "d" : "-");
            printf((st.st_mode & S_IRUSR) ? "r" : "-");
            printf((st.st_mode & S_IWUSR) ? "w" : "-");
            printf((st.st_mode & S_IXUSR) ? "x" : "-");
            printf((st.st_mode & S_IRGRP) ? "r" : "-");
            printf((st.st_mode & S_IWGRP) ? "w" : "-");
            printf((st.st_mode & S_IXGRP) ? "x" : "-");
            printf((st.st_mode & S_IROTH) ? "r" : "-");
            printf((st.st_mode & S_IWOTH) ? "w" : "-");
            printf((st.st_mode & S_IXOTH) ? "x" : "-");
            printf("\t");
            printf("%lu\t", st.st_nlink);
            printf("%s\t%s\t", getpwuid(st.st_uid)->pw_name, getgrgid(st.st_gid)->gr_name);
            printf("%ld\t", st.st_size);
            char date[20];
            strftime(date, 20, "%b %d   %H:%M", localtime(&(st.st_ctime)));
            printf("%s\t", date);

            int xx = strlen(mydir);
            for (int i = xx + 1; i < strlen(filename[x]); i++)
            {

                ans[-xx + i - 1] = filename[x][i];
            }

            ans[strlen(filename[x]) - xx - 1] = '\0';
            if (S_ISREG(st.st_mode) == 0)
            {
                // IS A DIRECTORY
                printf(BLU "%s\n" RESET, ans);
            }
            else if (st.st_mode & S_IXUSR)
            {
                printf(WHT "%s\n" RESET, ans);
            }
            else
            {
                printf(GRN "%s\n" RESET, ans);
            }

            // printf("%s\n", ans);
        }
    }
    else if (flag_l == 1 && flag_a == 1)
    {
        // for directories
        for (int x = 0; x < dir; x++)
        {

            char mainFolder[200];
            struct stat mainDir;
            struct dirent *token_main;
            total = 0;
            DIR *folder = opendir(dirname[x]);

            while (token_main = readdir(folder))
            {

                strcpy(mainFolder, dirname[x]);
                strcat(mainFolder, "/");
                strcat(mainFolder, token_main->d_name);
                if (stat(mainFolder, &mainDir) < 0)
                {
                    perror(mainFolder);
                    return -1;
                }
                total += mainDir.st_blocks;
            }

            printf("Total: %ld\n", total / 2);

            n = scandir(dirname[x], &namelist, NULL, alphasort);
            if (n == -1)
            {
                perror("scandir");
            }
            char *buff_useless = (char *)malloc(200 * sizeof(char));
            strcpy(buff_useless, dirname[x]);
            char hash[20] = "/";
            strcat(buff_useless, hash);
            for (int i = 0; i < n; i++)
            {

                char *fileChecker = (char *)malloc(200 * sizeof(char));
                strcpy(fileChecker, buff_useless);
                strcat(fileChecker, namelist[i]->d_name);
                struct stat st;
                int num = stat(fileChecker, &st);

                if (num < 0)
                {
                    perror(RED "ERROR IN ls -l -a <names>" RESET);
                    return -1;
                }       


                printf((S_ISDIR(st.st_mode)) ? "d" : "-");
                printf((st.st_mode & S_IRUSR) ? "r" : "-");
                printf((st.st_mode & S_IWUSR) ? "w" : "-");
                printf((st.st_mode & S_IXUSR) ? "x" : "-");
                printf((st.st_mode & S_IRGRP) ? "r" : "-");
                printf((st.st_mode & S_IWGRP) ? "w" : "-");
                printf((st.st_mode & S_IXGRP) ? "x" : "-");
                printf((st.st_mode & S_IROTH) ? "r" : "-");
                printf((st.st_mode & S_IWOTH) ? "w" : "-");
                printf((st.st_mode & S_IXOTH) ? "x" : "-");
                printf("\t");
                printf("%lu\t", st.st_nlink);
                printf("%s\t%s\t", getpwuid(st.st_uid)->pw_name, getgrgid(st.st_gid)->gr_name);
                printf("%ld\t", st.st_size);
                char date[20];
                strftime(date, 20, "%b %d   %H:%M", localtime(&(st.st_ctime)));
                printf("%s\t", date);
                if (S_ISREG(st.st_mode) == 0)
                {
                    // IS A DIRECTORY
                    printf(BLU "%s\n" RESET, namelist[i]->d_name);
                }
                else if (st.st_mode & S_IXUSR)
                {
                    printf(WHT "%s\n" RESET, namelist[i]->d_name);
                }
                else
                {
                    printf(GRN "%s\n" RESET, namelist[i]->d_name);
                }

                free(namelist[i]);
                free(fileChecker);
            }
            free(buff_useless);
        }
        // for file
        for (int x = 0; x < file; x++)
        {
            char ans[200];
            struct stat st;
            int num = stat(filename[x], &st);

            if (num < 0)
            {
                perror(RED "ERROR IN ls -l -a <names>" RESET);
                return -1;
            }

            printf((S_ISDIR(st.st_mode)) ? "d" : "-");
            printf((st.st_mode & S_IRUSR) ? "r" : "-");
            printf((st.st_mode & S_IWUSR) ? "w" : "-");
            printf((st.st_mode & S_IXUSR) ? "x" : "-");
            printf((st.st_mode & S_IRGRP) ? "r" : "-");
            printf((st.st_mode & S_IWGRP) ? "w" : "-");
            printf((st.st_mode & S_IXGRP) ? "x" : "-");
            printf((st.st_mode & S_IROTH) ? "r" : "-");
            printf((st.st_mode & S_IWOTH) ? "w" : "-");
            printf((st.st_mode & S_IXOTH) ? "x" : "-");
            printf("\t");
            printf("%lu\t", st.st_nlink);
            printf("%s\t%s\t", getpwuid(st.st_uid)->pw_name, getgrgid(st.st_gid)->gr_name);
            printf("%ld\t", st.st_size);
            char date[20];
            strftime(date, 20, "%b %d   %H:%M", localtime(&(st.st_ctime)));
            printf("%s\t", date);

            int xx = strlen(mydir);
            for (int i = xx + 1; i < strlen(filename[x]); i++)
            {

                ans[-xx + i - 1] = filename[x][i];
            }

            ans[strlen(filename[x]) - xx - 1] = '\0';
            if (S_ISREG(st.st_mode) == 0)
            {
                // IS A DIRECTORY
                printf(BLU "%s\n" RESET, ans);
            }
            else if (st.st_mode & S_IXUSR)
            {
                printf(WHT "%s\n" RESET, ans);
            }
            else
            {
                printf(GRN "%s\n" RESET, ans);
            }

            // printf("%s\n", ans);
        }

    }
}

int ls(char *cmd)
{
    initialise();
    cmd[strcspn(cmd, "\n")] = 0;
    char buf1[MAX_SIZE];
    char res[MAX_SIZE];
    strcpy(buf1, cmd);
    char *token1;
    char *buf = buf1;
    strcpy(dirname[0], mydir);
    token1 = strtok_r(buf, " ", &buf);
    while ((token1 = strtok_r(buf, " ", &buf)) != NULL)
    {
        tokeniser(token1);
    }
    if (dir == 0 && file == 0)
        dir = 1;
    lsactual();
    return 0;
}
