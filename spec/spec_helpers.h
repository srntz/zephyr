#ifndef ZEPHYR_TEST_HELPERS_H

typedef void (*TestFunction)(void);

void IT(char *name, TestFunction f);
void ASSERT_INT_EQ(int expected, int got);

#define ZEPHYR_TEST_HELPERS_H

#endif //ZEPHYR_TEST_HELPERS_H