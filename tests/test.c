#include "builder.h"
#include "nergassert.h"
#include <stdlib.h>

void test_init_cmd_items_not_null(void) 
{
  command_t *cmd = init_cmd_items();

  assert_not_null(cmd, "cmd must not be null");
  assert_not_null(cmd->main_cmd, "main_cmd must not be null");
  assert_not_null(cmd->c_files, "c_files must not be null");
  assert_not_null(cmd->c_headers, "c_headers must not be null");
  assert_not_null(cmd->c_output, "c_output must not be null");
  free(cmd);
}

void test_append_only_main_cmd(void) 
{
  command_t *cmd = init_cmd_items();

  append_main_cmd(cmd);
  assert_not_null(cmd->main_cmd->elements, "main_cmd->elements must not be null");

  char *full_cmd = consolidate_cmd(cmd);
  assert_equals_str("gcc ", full_cmd, "full_cmd must be 'gcc'");
  free(cmd);
  free(full_cmd);
}

void test_append_only_c_flags(void)
{
  command_t *cmd = init_cmd_items();

  append_c_flags(cmd);
  assert_not_null(cmd->c_flags->elements, "c_flags->elements must not be null");

  char *full_cmd = consolidate_cmd(cmd);
  assert_equals_str(
      "-Wall -Wextra -Werror -std=c99 -v -gdb ", 
      full_cmd, 
      "full_cmd must has not all the flags"
      );

  free(cmd);
  free(full_cmd);
}

void test_append_only_c_headers(void)
{
  command_t *cmd = init_cmd_items();
  
  append_c_headers(cmd);
  assert_not_null(cmd->c_headers->elements, "c_headers->elements must not be null");

  char *full_cmd = consolidate_cmd(cmd);
  assert_equals_str(
      "-I./include ",
      full_cmd,
      "full_cmd must have all the references to the dependencies"
      );
}

void test_append_only_c_files(void)
{
  command_t *cmd = init_cmd_items();

  append_c_files(cmd);
  assert_not_null(cmd->c_files->elements, "c_files->elements must not be null");

  char *full_cmd = consolidate_cmd(cmd);
  assert_equals_str(
      "./src/builder.c ",
      full_cmd,
      "full_cmd must contain all the references to the c files"
      );
}

void test_append_only_c_output(void)
{
  command_t *cmd = init_cmd_items();
  
  append_c_output(cmd);
  assert_not_null(cmd->c_output->elements, "c_output->elements must not be null");

  char *full_cmd = consolidate_cmd(cmd);
  assert_equals_str(
      "-o ./build/nergbuild.o",
      full_cmd,
      "full_cmd must contain the output for the compilation process"
      );
}

void test_create_full_command(void)
{
  command_t *cmd = init_cmd_items();

  append_main_cmd(cmd);
  append_c_flags(cmd);
  append_c_headers(cmd);
  append_c_files(cmd);
  append_c_output(cmd);

  char *full_cmd = consolidate_cmd(cmd);
  assert_equals_str(
      "gcc "                                    
      "-Wall -Wextra -Werror -std=c99 -v -gdb " 
      "-I./include "                            
      "./src/builder.c "                        
      "-o ./build/nergbuild.o",
      full_cmd,
      "full_cmd must contain all the paramenters"
      );
}


int main(int argc, char *argv[])
{

  test_init_cmd_items_not_null();
  test_append_only_main_cmd();
  test_append_only_c_flags();
  test_append_only_c_headers();
  test_append_only_c_files();
  test_append_only_c_output();
  test_create_full_command();

  // command_t *cmd = init_cmd_items();
  // append_main_cmd(cmd);
  // append_c_flags(cmd);
  // append_c_headers(cmd);
  // append_c_files(cmd);
  // append_c_output(cmd);


  // char *full_cmd = consolidate_cmd(cmd);
  // 
  // free(cmd);
  // free(full_cmd);
  return 0; 
}

