#include <stdio.h>
#include "spec_helpers.h"

void IT(char *name, TestFunction f) {
    printf("IT %s\n", name);
    f();
}

void ASSERT_INT_EQ(int expected, int got) {
    if (expected != got) {
        printf("EXAMPLE FAILED. EXPECTED: %d, GOT: %d", expected, got);
    }
};