#include "ui.h"

#include <stdio.h>

#define COLOR_RESET  "\x1b[0m"
#define COLOR_RED    "\x1b[31m"
#define COLOR_GREEN  "\x1b[32m"
#define COLOR_YELLOW "\x1b[33m"
#define COLOR_CYAN   "\x1b[36m"
#define COLOR_BOLD   "\x1b[1m"

static const char *strength_color(int score) {
    if (score <= 39) {
        return COLOR_RED;
    }
    if (score <= 69) {
        return COLOR_YELLOW;
    }
    return COLOR_GREEN;
}

static void print_yes_no(int value) {
    printf("%s", value ? "YES" : "NO");
}

static void print_strength_meter(int score) {
    int blocks = score / 5;
    const char *color = strength_color(score);

    printf("Strength Meter       : %s[", color);
    for (int i = 0; i < 20; i++) {
        if (i < blocks) {
            printf("█");
        } else {
            printf("░");
        }
    }
    printf("] %d%%%s\n", score, COLOR_RESET);
}

void print_banner(void) {
    printf("%s====================================%s\n", COLOR_CYAN, COLOR_RESET);
    printf("%s%sSMART AI PASSWORD STRENGTH ANALYZER%s\n", COLOR_BOLD, COLOR_CYAN, COLOR_RESET);
    printf("%s====================================%s\n\n", COLOR_CYAN, COLOR_RESET);
}

void print_dashboard(const PasswordFeatures *features) {
    const char *label = classify_strength(features->score);
    const char *color = strength_color(features->score);

    printf("Password Length      : %d\n", features->length);

    printf("Uppercase Letters    : ");
    print_yes_no(features->upper);
    printf("\n");

    printf("Lowercase Letters    : ");
    print_yes_no(features->lower);
    printf("\n");

    printf("Digits               : ");
    print_yes_no(features->digits);
    printf("\n");

    printf("Special Characters   : ");
    print_yes_no(features->special);
    printf("\n");

    printf("Repeated Characters  : ");
    print_yes_no(features->repeated);
    printf("\n");

    printf("Sequential Patterns  : ");
    print_yes_no(features->sequential);
    printf("\n\n");

    printf("Entropy              : %.1f bits\n", features->entropy);
    printf("Password Score       : %d/100\n", features->score);
    printf("Strength             : %s%s%s\n", color, label, COLOR_RESET);
    print_strength_meter(features->score);
}

void print_recommendations(const PasswordFeatures *features) {
    int has_issues = 0;

    printf("\nRecommendations:\n\n");

    if (!features->upper) {
        printf("* Add uppercase letters\n");
        has_issues = 1;
    }
    if (!features->digits) {
        printf("* Add digits\n");
        has_issues = 1;
    }
    if (!features->special) {
        printf("* Add special characters\n");
        has_issues = 1;
    }
    if (features->length < 12) {
        printf("* Increase password length\n");
        has_issues = 1;
    }
    if (features->sequential) {
        printf("* Avoid sequential patterns\n");
        has_issues = 1;
    }
    if (features->repeated) {
        printf("* Avoid repeated characters\n");
        has_issues = 1;
    }

    if (!has_issues) {
        printf("* No major weaknesses found\n");
    }

    printf("\n====================================\n");
}
