#include <assert.h>
#include <stdio.h>
#include <time.h>

#define TEST(func, test_name)                                  \
    do {                                                       \
        printf("Test '%s':\n", test_name);            \
        clock_t start = clock();                               \
        func();                                                \
        clock_t end = clock();                                 \
        printf("'%s' completed in %.2f ms\n\n",             \
               test_name,                                      \
               (double)(end - start) * 1000.0 / CLOCKS_PER_SEC); \
    } while (0)

#define TEST_ASSERT(condition, format, ...)                           \
    do {                                                          \
        if (!(condition)) {                                       \
            fprintf(stderr, "\t[FAIL]: " format "\n", ##__VA_ARGS__);   \
        }                                                         \
    } while (0)

#define TEST_LOG(format, ...) fprintf(stdout, "\t[LOG]: " format "\n", ##__VA_ARGS__)

#define TEST_LOG_BB(bb) \
    do { \
        fprintf(stdout, "\t[LOG]: 0x%llx\n", bb); \
    } while (0)

#define TEST_LOG_BOARD(bitboard) \
    do { \
        printf("\t[LOG]:\n\t\t"); \
        for (int i = 1; i <= 64; i++) { \
            printf("%llu", (bitboard >> (i - 1)) & 1); \
            if (i % 8 == 0) {   \
                printf("\n");   \
                if (i != 64) {  \
                    printf("\t\t"); \
                } \
            } \
        } \
    } while (0)

