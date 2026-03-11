#ifndef UTIL_H
#define UTIL_H

#include <stddef.h>

char *str_to_lower(const char *s);
void read_line(char *buffer, size_t size);
char *read_multiline_input(void);

#endif

