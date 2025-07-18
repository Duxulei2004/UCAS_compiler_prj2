// cact_io.c
#include "cact_io.h"
#include <stdio.h>

void print_int(int value) {
    printf("%d", value);
}

void print_float(float value) {
    printf("%f", value);
}

void print_char(char value) {
    putchar(value);
}

int get_int() {
    int val;
    scanf("%d", &val);
    return val;
}

float get_float() {
    float val;
    scanf("%f", &val);
    return val;
}

char get_char() {
    char val;
    scanf(" %c", &val);
    return val;
}
