#include "analyzer.h"
#include "entropy.h"

#include <ctype.h>
#include <stddef.h>

static int has_sequential_pattern(const char *password) {
    int seq_found = 0;

    for (size_t i = 0; password[i] != '\0' && password[i + 2] != '\0'; i++) {
        int a = (unsigned char)password[i];
        int b = (unsigned char)password[i + 1];
        int c = (unsigned char)password[i + 2];

        if ((b == a + 1 && c == b + 1) || (b == a - 1 && c == b - 1)) {
            seq_found = 1;
            break;
        }
    }

    return seq_found;
}

static int clamp_score(int score) {
    if (score < 0) {
        return 0;
    }
    if (score > 100) {
        return 100;
    }
    return score;
}

void analyze_password(const char *password, PasswordFeatures *features) {
    int score = 0;

    if (password == NULL || features == NULL) {
        return;
    }

    features->length = 0;
    features->upper = 0;
    features->lower = 0;
    features->digits = 0;
    features->special = 0;
    features->repeated = 0;
    features->sequential = 0;
    features->entropy = 0.0;
    features->score = 0;

    for (size_t i = 0; password[i] != '\0'; i++) {
        unsigned char c = (unsigned char)password[i];
        features->length++;

        if (isupper(c)) {
            features->upper = 1;
        } else if (islower(c)) {
            features->lower = 1;
        } else if (isdigit(c)) {
            features->digits = 1;
        } else {
            features->special = 1;
        }

        if (i > 0 && password[i] == password[i - 1]) {
            features->repeated = 1;
        }
    }

    features->sequential = has_sequential_pattern(password);
    features->entropy = calculate_entropy(password);

    if (features->length >= 12) {
        score += 30;
    } else if (features->length >= 8) {
        score += 15;
    }

    if (features->upper) {
        score += 15;
    }
    if (features->lower) {
        score += 10;
    }
    if (features->digits) {
        score += 15;
    }
    if (features->special) {
        score += 20;
    }
    if (features->repeated) {
        score -= 15;
    }
    if (features->sequential) {
        score -= 20;
    }

    features->score = clamp_score(score);
}

const char *classify_strength(int score) {
    if (score <= 39) {
        return "WEAK";
    }
    if (score <= 69) {
        return "MEDIUM";
    }
    return "STRONG";
}
