#include "analyzer.h"
#include "ui.h"
#include "utils.h"

#include <stdio.h>

#define MAX_PASSWORD_LEN 100

int main(void) {
    char password[MAX_PASSWORD_LEN + 2];
    PasswordFeatures features;

    print_banner();
    printf("Enter password (max %d chars): ", MAX_PASSWORD_LEN);

    if (fgets(password, sizeof(password), stdin) == NULL) {
        printf("\nInput error.\n");
        return 1;
    }

    strip_newline(password);

    analyze_password(password, &features);

    printf("\n");
    print_dashboard(&features);
    print_recommendations(&features);

    return 0;
}
