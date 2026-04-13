#include "runner.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



pid_t run_command_async(char *command)
{
    int *fdin = malloc(sizeof(int *));
    int *fdout = malloc(sizeof(int *));
    pid_t cpid = fork();
    if (cpid < 0) {
        printf("Could not fork child process");
    }

    if (cpid == 0) {
        if (fdin) {
            if (dup2(*fdin, STDIN_FILENO) < 0) {
                printf("Could not setup stdin for child process");
            }
                printf("fdin: %d\n", *fdin);
        }

        if (fdout) {
            if (dup2(*fdout, STDIN_FILENO) < 0) {
                printf("Could not setup stdin for child process");
            }
                printf("fdout: %d\n", *fdout);
        }

        char * const args[] = { "/usr/bin/ls", "-la", NULL };

        if (execvp(args[0], args) < 0) {
            printf("Could not exec process: %s\n", strerror(errno));
        }
    }

    return cpid;
}
