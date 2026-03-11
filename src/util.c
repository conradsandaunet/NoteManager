#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
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

char *read_multiline_input(void) {

    char line[512];
    char *result = NULL;
    char *new_result;
    size_t total_len = 0;
    size_t line_len;

    while (1) {
        if (fgets(line, sizeof(line), stdin) == NULL)
            break;

        line[strcspn(line, "\n")] = '\0';

        if (strcmp(line, "END") == 0)
            break;

        line_len = strlen(line);

        new_result = realloc(result, total_len + line_len + 2);
        if (new_result == NULL) {
            free(result);
            return NULL;
        }

        result = new_result;
        memcpy(result + total_len, line, line_len);
        total_len += line_len;

        result[total_len] = '\n';
        total_len++;
        result[total_len] = '\0';
    }

    if (result == NULL) {
        result = malloc(1);
        if (result == NULL)
            return NULL;
        result[0] = '\0';
    }

    return result;
}

void generate_timestamp(char *buffer, size_t size) {

    time_t now;
    struct tm *tm_info;

    now = time(NULL);
    tm_info = localtime(&now);

    if (tm_info == NULL) {
        if (size > 0)
            buffer[0] = '\0';
        return;
    }

    strftime(buffer, size, "%Y-%m-%d %H:%M:%S", tm_info);
}
