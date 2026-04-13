#include "runner.h"
#include <stdio.h>

void test_process_runner()
{
    run_command_async("ls");
}

int main()
{
    test_process_runner();

    return 0;
}
