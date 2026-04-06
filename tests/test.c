#include "builder.h"

int main(int argc, char *argv[])
{
  command_t *cmd = init_cmd_items();
  append_main_cmd(cmd);
  append_c_flags(cmd);
  append_c_headers(cmd);
  append_c_files(cmd);
  append_c_output(cmd);


  char *full_cmd = consolidate_cmd(cmd);
  
  free(cmd);
  free(full_cmd);
  return 0; 
}

