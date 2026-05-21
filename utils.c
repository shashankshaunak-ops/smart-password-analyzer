#include "utils.h"

#include <ctype.h>
#include <string.h>

void strip_newline(char *str) {
    if (str == NULL) {
        return;
    }

    str[strcspn(str, "\n")] = '\0';
}

int is_special_char(char c) {
    return !isalnum((unsigned char)c);
}

size_t safe_strlen(const char *str) {
    if (str == NULL) {
        return 0;
    }
    return strlen(str);
}
