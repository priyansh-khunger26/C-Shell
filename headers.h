#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <pwd.h>
#include <grp.h>
#include <fcntl.h>
#include <dirent.h>
#include <time.h>
#include <signal.h>
#include <errno.h>
#include<ctype.h>
#include <termios.h>

#define RED "\x1B[31m"
#define GRN "\x1B[32m"
#define YEL "\x1B[33m"
#define BLU "\x1B[34m"
#define MAG "\x1B[35m"
#define CYN "\x1B[36m"
#define WHT "\x1B[37m"
#define RESET "\x1B[0m"

#define MAX_SIZE 200
#define GLOBAL_VALS 300

char sysname[GLOBAL_VALS];
char initialDir[MAX_SIZE];
char homeDir[MAX_SIZE];
char mydir[MAX_SIZE];
int forepid;
char forepname[MAX_SIZE];
char printTime[MAX_SIZE];
struct backgroundProcess
{
    int pid;
    char jobname[MAX_SIZE];
} jh;
struct checkJobs
{
    int pid;
    char jobname[MAX_SIZE];
    char status;
    int jobid;
} ;
struct checkJobs * jobsArr;
int totalbgJobs;
struct backgroundProcess *processes;
int bgProcessNum;
int pidOfShell;
int pwd();
int cd(char *cmd);
int echo1(char *cmd);
int ls(char *cmd);
int printDetails();
int cd(char *cmd);
int support(char *cmd);
int supportmain(char *cmd);
int pinfo(char *cmd);
int putInFile(char *cmd);
int ls(char *cmd);
int extractHistory(char *cmd);
int discover(char *cmd);
int jobs(char *cmd);
int background(char *cmd,int count);
int foreground(char *cmd);
void checkIfProcessIsOver();
int sig(char *cmd);
int fg(char*cmd);
int bg(char*cmd);
int redirec(char *cmd);
int pipeHandle(char *cmd);
int autocomplete(char *arg,char *val);