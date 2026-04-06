#include "builder.h"
#include "logger.h"
#include <assert.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>


#define CURRENT_DIR "./"
#define LIB_DIR "./lib/"
#define HEADERS_DIR "include"

#define darray_append_items(array, ...) \
  darray_append_items_null(array, __VA_ARGS__, (const void *) -1)

darray_t *init_darray(void) {
  darray_t *tmp = malloc(sizeof(darray_t));
  assert(tmp != NULL);

  tmp->capacity = DA_MIN_CAPACITY;
  tmp->size = 0;
  tmp->elements = malloc(sizeof(char *) * DA_MIN_CAPACITY);
  assert(tmp->elements != NULL);

  return tmp;
}

command_t *init_cmd_items(void)
{
  command_t *cmd = malloc(sizeof(command_t));
  assert(cmd != NULL);
  
  cmd->main_cmd = init_darray();
  cmd->c_files = init_darray();
  cmd->c_flags = init_darray();
  cmd->c_headers = init_darray();
  cmd->c_output = init_darray();

  return cmd;
}

char *consolidate_cmd(const command_t *cmd)
{
  assert(cmd != NULL);

  assert(cmd->main_cmd != NULL);
  assert(cmd->c_flags != NULL);
  assert(cmd->c_headers != NULL);
  assert(cmd->c_files != NULL);
  assert(cmd->c_output != NULL);

  char *cmd_res = malloc(sizeof(char *));

  for (int i = 0; i < cmd->main_cmd->size; i++) {
    const char *item = cmd->main_cmd->elements[i];
    strcat(cmd_res, item);
    strcat(cmd_res, " ");
  }

  for (int i = 0; i < cmd->c_flags->size; i++) {
    const char *item = cmd->c_flags->elements[i];
    strcat(cmd_res, "-");
    strcat(cmd_res, item);
    strcat(cmd_res, " ");
  }

  for (int i = 0; i< cmd-> c_headers->size; i++) {
    const char *item = cmd->c_headers->elements[i];
    strcat(cmd_res, "-I./");
    strcat(cmd_res, item);
    strcat(cmd_res, " ");
  }

  // LOG_INFO("CMD_RES: %s", cmd_res);
  return cmd_res;
}

void darray_append_items_null(darray_t *array, ...)
{
  if (array == NULL) { return; }
  if (array->capacity <= 0) {
    array->capacity = DA_MIN_CAPACITY;
    array->elements = malloc(sizeof(char *));
  }

  va_list args;
  va_start(args, array);
  for (;;) {
    void *arg = va_arg(args, void *);
    if (arg == (const void *)-1) { break; }

    if (array->size + 1 >= array->capacity) {
      array->capacity *= 2;
      assert(array->elements != NULL);
      void **tmp = realloc(array->elements, array->capacity * sizeof(void *));
      if (tmp == NULL) { return; }
      array->elements = tmp;
    }

    array->elements[array->size] = arg;
    array->size ++;
  }
  va_end(args);
}

void append_main_cmd(const command_t *cmd)
{
  if (cmd == NULL) { return; }
  darray_append_items(cmd->main_cmd, C_MAIN_COMMAND);
}

void append_c_flags(const command_t *cmd)
{
  if (cmd == NULL) { return; }

  darray_append_items(
      cmd->c_flags,
      CF_WARNINGS_ALL,
      CF_WARNINGS_EXTRA,
      CF_WARNINGS_ERROR,
      CF_STD,
      CF_VERBOSE,
      CF_DEBUG
      );
}

void append_c_files(const command_t *cmd)
{
  assert(cmd != NULL);
}

void append_c_headers(const command_t *cmd)
{
  assert(cmd != NULL);

  DIR *current_dir = opendir(CURRENT_DIR);

  while (current_dir != NULL) {
    struct dirent *file = readdir(current_dir);
    if (file != NULL) {
      if (strcmp(file->d_name, HEADERS_DIR) == 0) {
        char *header_dir = file->d_name;
        darray_append_items(cmd->c_headers, header_dir);
        break;
      }
    } else {
      closedir(current_dir);
      break;
    }
  } 
}

void append_c_output(const command_t *cmd)
{
  assert(cmd != NULL);
}
