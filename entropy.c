#include "entropy.h"
#include "utils.h"

#include <ctype.h>
#include <math.h>

static int get_charset_size(const char *password) {
    int has_lower = 0;
    int has_upper = 0;
    int has_digit = 0;
    int has_special = 0;

    for (size_t i = 0; password[i] != '\0'; i++) {
        unsigned char c = (unsigned char)password[i];

        if (islower(c)) {
            has_lower = 1;
        } else if (isupper(c)) {
            has_upper = 1;
        } else if (isdigit(c)) {
            has_digit = 1;
        } else if (is_special_char((char)c)) {
            has_special = 1;
        }
    }

    return has_lower * 26 + has_upper * 26 + has_digit * 10 + has_special * 32;
}

double calculate_entropy(const char *password) {
    int charset_size;
    size_t length;

    if (password == NULL || password[0] == '\0') {
        return 0.0;
    }

    charset_size = get_charset_size(password);
    length = safe_strlen(password);

    if (charset_size <= 1 || length == 0) {
        return 0.0;
    }

    return (double)length * (log((double)charset_size) / log(2.0));
}
