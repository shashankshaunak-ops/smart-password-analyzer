#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>

void strip_newline(char *str);
int is_special_char(char c);
size_t safe_strlen(const char *str);

#endif
