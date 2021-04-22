#include "unity.h"
#include "fileHandling.h"
#include "logic.h"
//#include "graphics.h"
#include <stdlib.h>

void test_finalState() {

    struct World w;
    w.nrOfGenerations = 3;
    w.rows = 3;
    w.columns = 4;
    int** a;
    a = (int**)malloc(3* sizeof(int*));
    a[0] = (int*)malloc(4 * sizeof(int));
    a[0][0] = 0;
    a[0][1] = 1;
    a[0][2] = 0;
    a[0][3] = 1;
    a[1] = (int*)malloc(4 * sizeof(int));
    a[1][0] = 0;
    a[1][1] = 1;
    a[1][2] = 1;
    a[1][3] = 0;
    a[2] = (int*)malloc(4 * sizeof(int));
    a[2][0] = 1;
    a[2][1] = 1;
    a[2][2] = 0;
    a[2][3] = 1;
    w.state = a;

    const struct World* p = finalState(&w);
    TEST_ASSERT_NOT_NULL_MESSAGE(p, "finalState returned a NULL pointer");
    TEST_ASSERT_NOT_NULL_MESSAGE(p->state, "finalState returned pointer to World with NULL state array");
    TEST_ASSERT_NOT_EMPTY_MESSAGE(p->state, "finalState returned pointer to World with empty state array");
    TEST_ASSERT_EQUAL_INT(p->nrOfGenerations, w.nrOfGenerations);
    TEST_ASSERT_MESSAGE(p->state[0][0] == 0, "Wrong final cell [0][0] state");
    TEST_ASSERT_MESSAGE(p->state[1][0] == 0, "Wrong final cell [1][0] state");
    TEST_ASSERT_MESSAGE(p->state[1][1] == 1, "Wrong final cell [1][1] state");
    TEST_ASSERT_MESSAGE(p->state[2][1] == 1, "Wrong final cell [2][1] state");
    TEST_ASSERT_MESSAGE(p->state[2][2] == 0, "Wrong final cell [2][2] state");

    free(a[0]);
    free(a[1]);
    free(a[2]);
    free(a[3]);
    free(a);
}

void test_nextState() {

    int** a;
    a = (int**)malloc(3* sizeof(int*));
    a[0] = (int*)malloc(4 * sizeof(int));
    a[0] = (int*)malloc(4 * sizeof(int));
    a[0][0] = 0;
    a[0][1] = 1;
    a[0][2] = 0;
    a[0][3] = 1;
    a[1] = (int*)malloc(4 * sizeof(int));
    a[1][0] = 0;
    a[1][1] = 1;
    a[1][2] = 1;
    a[1][3] = 0;
    a[2] = (int*)malloc(4 * sizeof(int));
    a[2][0] = 1;
    a[2][1] = 1;
    a[2][2] = 0;
    a[2][3] = 1;

    int** nextA = nextState(a, 3, 4);

    TEST_ASSERT_NOT_NULL_MESSAGE(nextA, "nextState returned a NULL pointer");
    TEST_ASSERT_NOT_EMPTY_MESSAGE(nextA, "nextState returned pointer to an empty state array");
    TEST_ASSERT_MESSAGE(nextA[0][0] == 0, "Wrong final cell [0][0] state");
    TEST_ASSERT_MESSAGE(nextA[1][0] == 0, "Wrong final cell [1][0] state");
    TEST_ASSERT_MESSAGE(nextA[1][2] == 0, "Wrong final cell [1][2] state");
    TEST_ASSERT_MESSAGE(nextA[2][1] == 1, "Wrong final cell [2][1] state");
    TEST_ASSERT_MESSAGE(nextA[2][3] == 0, "Wrong final cell [2][3] state");

    free(a[0]);
    free(a[1]);
    free(a[2]);
    free(a[3]);
    free(a);
}

void setUp() {

}

void tearDown() {

}

int main() {
    UNITY_BEGIN();
    RUN_TEST(test_finalState);
    RUN_TEST(test_nextState);

    return UNITY_END();
}