#ifndef ANALYZER_H
#define ANALYZER_H

typedef struct {
    int length;
    int upper;
    int lower;
    int digits;
    int special;
    int repeated;
    int sequential;
    double entropy;
    int score;
} PasswordFeatures;

void analyze_password(const char *password, PasswordFeatures *features);
const char *classify_strength(int score);

#endif
