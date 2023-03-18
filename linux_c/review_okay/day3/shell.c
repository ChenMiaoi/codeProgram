#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

#define NUM 1024
#define SIZE 32

char cmd_line[NUM];
char* cmd_line_parse[SIZE];

int
get_cmd()
{
    write(2, "[mini-shell]# ", 14);
    memset(cmd_line, 0x00, NUM);
    fgets(cmd_line, NUM, stdin);
    if (cmd_line[0] == 0)
        return -1;
    return 0;
}

void 
parse_cmd()
{
    int argc;
    char* argv;
    argc = 0, argv = cmd_line;

    while (*argv != '\0') {
        if (!isspace(*argv)) {
            cmd_line_parse[argc++] = argv;
            while ((!isspace(*argv)) && (*argv) != '\0')
                ++argv;
        }else {
            while (isspace(*argv)) {
                *argv = '\0';
                ++argv;
            }
        }
    }
    cmd_line_parse[argc] = NULL;
}

void 
run_cmd()
{
    parse_cmd();
    if (cmd_line_parse[0] == NULL)
        exit(-1);
    execvp(cmd_line_parse[0], cmd_line_parse);
    exit(0);
}

int
main(int argc, char* argv[]) 
{
    pid_t pid;
    while (get_cmd() >= 0) {
        if (cmd_line[0] == 'c' && cmd_line[1] == 'd' && cmd_line[2] == ' ') {
            cmd_line[strlen(cmd_line) - 1] = 0;
            if (chdir(cmd_line + 3) < 0)
                fprintf(stdout, "cannot cd %s\n", cmd_line + 3);
            continue;
        }
        if (fork() == 0)
            run_cmd();
        wait(0);
    }
    exit(0);
}