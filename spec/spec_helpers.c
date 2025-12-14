#include <stdio.h>
#include "spec_helpers.h"
#include <stdlib.h>
#include <stdbool.h>

void IT(char *name, const TestFunction f) {
    printf("IT %s\n", name);
    f();
}

void ASSERT_INT_EQ(const int expected, const int got) {
    if (expected != got) {
        printf("EXAMPLE FAILED. EXPECTED: %d, GOT: %d", expected, got);
        exit(1);
    }
};

void ASSERT_BOOL_EQ(const bool expected, const bool got) {
    if (expected != got) {
        printf("EXAMPLE FAILED. EXPECTED: %d, GOT: %d", expected, got);
        exit(1);
    }
}