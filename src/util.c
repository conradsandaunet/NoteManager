#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"

char *str_to_lower(const char *s) {

    size_t i, len;
    char *result;

    if (s == NULL) {
        return NULL;
    }

    len = strlen(s);
    result = malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    for (i = 0; i < len; i++) {
        result[i] = (char)tolower((unsigned char)s[i]);
    }

    result[len] = '\0';
    return result;
}

void read_line(char *buffer, size_t size) {

    if (fgets(buffer, size, stdin) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';
    }
}

