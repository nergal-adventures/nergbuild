#pragma once

#include <assert.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DA_MIN_CAPACITY 4

#define C_MAIN_COMMAND "gcc"
#define CF_WARNINGS_ALL "Wall"
#define CF_PEDANTIC "Wpedantic"
#define CF_WARNINGS_EXTRA "Wextra"
#define CF_WARNINGS_ERROR "Werror"
#define CF_DEBUG "gdb"
#define CF_STD "std=c99"
#define CF_VERBOSE "v"

typedef struct DynamicArray {
  size_t size;
  size_t capacity;
  void **elements;
} darray_t;

typedef struct Command {
  darray_t *main_cmd;
  darray_t *c_flags;
  darray_t *c_headers;
  darray_t *c_files;
  darray_t *c_output;
} command_t;

darray_t *init_darray(void);
command_t *init_cmd_items(void);

void darray_append_items_null(darray_t *array, ...);
void append_main_cmd(const command_t *cmd);
void append_c_flags(const command_t *cmd);
void append_c_headers(const command_t *cmd);
void append_c_files(const command_t *cmd);
void append_c_output(const command_t *cmd);

char *consolidate_cmd(const command_t *cmd);

