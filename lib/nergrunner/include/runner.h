#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <errno.h>
#include <fcntl.h>

typedef int Fd;

pid_t run_command_async(char *command);

