#define ARRAY_SIZE(x) (sizeof(x) / sizeof(x[0]))

#include <assert.h>
#include <stdlib.h>

#include "3ds.h"

uint8_t sub_buffer[320*240 * 3];

static int handle_count = 0;
static void* handles[1000];
static const int handle_base = 1337000;

void* create_handle(Handle* handle, size_t size) {
  assert(handle_count < ARRAY_SIZE(handles));
  void* data = malloc(size);
  handles[handle_count] = data;
  *handle = handle_base + handle_count++;
  return data;
}

void* get_handle(Handle handle) {
  return handles[handle - handle_base];
}

void destroy_handle(Handle handle) {
  free(handles[handle - handle_base]);
  handles[handle - handle_base] = NULL;
}
