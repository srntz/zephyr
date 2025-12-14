#ifndef ZEPHYR_TEST_HELPERS_H

#include <stdbool.h>

typedef void (*TestFunction)(void);

void IT(char *name, TestFunction f);
void ASSERT_INT_EQ(int expected, int got);
void ASSERT_BOOL_EQ(bool expected, bool got);

#define ZEPHYR_TEST_HELPERS_H

#endif //ZEPHYR_TEST_HELPERS_H