#include <assert.h>
#include <stdio.h>
#include <time.h>

#include "bitboard.h"

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

#define TEST(func, test_name)                                  \
    do {                                                       \
        printf(BLU "[TEST] " RESET test_name "\n");            \
        clock_t start = clock();                               \
        func();                                                \
        clock_t end = clock();                                 \
        printf(BLU "[TEST] " RESET test_name " completed in %.2f ms\n\n",             \
               (double)(end - start) * 1000.0 / CLOCKS_PER_SEC); \
    } while (0)

#define TEST_ASSERT(condition, format, ...)                           \
    do {                                                          \
        if (!(condition)) {                                       \
            fprintf(stderr, "\t" RED "[FAIL] " RESET format "\n", ##__VA_ARGS__);   \
        }                                                         \
    } while (0)

#define TEST_LOG(format, ...) fprintf(stdout, "\t[LOG] " format "\n", ##__VA_ARGS__)

#define TEST_LOG_BB(bb) \
    do { \
        fprintf(stdout, "\t[LOG] 0x%llx\n", bb); \
    } while (0)

#define TEST_LOG_BB_PRETTY(bb) \
    do { \
        printf("\t[LOG] "); \
        for (int i = 7; i >= 0; i--) { \
            if (i != 7) printf("\t       "); \
            else printf(" "); \
            for (int j = 0; j < 8; j++) { \
                int s = (i * 8) + j; \
                printf("%llu", (bb >> s) & 1); \
            } \
            printf("\n"); \
        } \
    } while (0)

#define TEST_LOG_MOVE_LIST(ml, prec) \
    do { \
        printf("\t[LOG] " prec " "); \
        for (size_t i = 0; i < ml.length; i++) { \
			Move move = ml.moves[i]; \
			printf("%s -> %s F%02d | ", SQUARE_NAMES[get_from_square(move)], SQUARE_NAMES[get_to_square(move)], get_flag(move)); \
		} \
        printf("\n"); \
    } while (0)
