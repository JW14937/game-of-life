#include "unity.h"
#include "fileHandling.h"
#include "logic.h"
//#include "graphics.h"
#include <stdlib.h>


// Logic module

void test_finalState() {

    // A normal case

    struct World wNorm;
    wNorm.nrOfGenerations = 3;
    wNorm.rows = 3;
    wNorm.columns = 4;
    int** a = NULL;
    a = malloc2DArray(wNorm.rows, wNorm.columns);

    a[0][0] = 0;
    a[0][1] = 1;
    a[0][2] = 0;
    a[0][3] = 1;
    a[1][0] = 0;
    a[1][1] = 1;
    a[1][2] = 1;
    a[1][3] = 0;
    a[2][0] = 1;
    a[2][1] = 1;
    a[2][2] = 0;
    a[2][3] = 1;
    wNorm.state = a;

    const struct World* finWNorm = finalState(&wNorm);
    TEST_ASSERT_NOT_NULL_MESSAGE(finWNorm, "finalState returned a NULL pointer");
    TEST_ASSERT_NOT_NULL_MESSAGE(finWNorm->state, "finalState returned pointer to World with NULL state array");
    TEST_ASSERT_NOT_EMPTY_MESSAGE(finWNorm->state, "finalState returned pointer to World with empty state array");
    TEST_ASSERT_EQUAL_INT(finWNorm->nrOfGenerations, wNorm.nrOfGenerations);
    TEST_ASSERT_MESSAGE(finWNorm->state[0][0] == 0, "Wrong final cell [0][0] state");
    TEST_ASSERT_MESSAGE(finWNorm->state[1][0] == 0, "Wrong final cell [1][0] state");
    TEST_ASSERT_MESSAGE(finWNorm->state[1][1] == 1, "Wrong final cell [1][1] state");
    TEST_ASSERT_MESSAGE(finWNorm->state[2][1] == 1, "Wrong final cell [2][1] state");
    TEST_ASSERT_MESSAGE(finWNorm->state[2][2] == 0, "Wrong final cell [2][2] state");

    free2DArray(a, wNorm.rows, wNorm.columns);
    freeWorld(finWNorm);


    // Empty world

    struct World wEmpty;
    wEmpty.nrOfGenerations = 3;
    wEmpty.rows = 3;
    wEmpty.columns = 3;
    a = malloc2DArray(wEmpty.rows, wEmpty.columns);
    
    for(int i=0; i<wEmpty.rows; i++) {
        for(int j=0; j<wEmpty.columns; j++) {
            a[i][j] = 0;
        }
    }

    wEmpty.state = a;

    const struct World* finWEmpty = finalState(&wEmpty);
    TEST_ASSERT_NOT_NULL_MESSAGE(finWEmpty, "finalState returned a NULL pointer");
    TEST_ASSERT_NOT_NULL_MESSAGE(finWEmpty->state, "finalState returned pointer to World with NULL state array");
    TEST_ASSERT_NOT_EMPTY_MESSAGE(finWEmpty->state, "finalState returned pointer to World with empty state array");
    TEST_ASSERT_EQUAL_INT(finWEmpty->nrOfGenerations, wEmpty.nrOfGenerations);
    TEST_ASSERT_MESSAGE(finWEmpty->state[0][0] == 0, "Wrong final cell [0][0] state");
    TEST_ASSERT_MESSAGE(finWEmpty->state[0][1] == 0, "Wrong final cell [0][1] state");
    TEST_ASSERT_MESSAGE(finWEmpty->state[1][1] == 0, "Wrong final cell [1][1] state");
    TEST_ASSERT_MESSAGE(finWEmpty->state[2][0] == 0, "Wrong final cell [2][0] state");
    TEST_ASSERT_MESSAGE(finWEmpty->state[2][1] == 0, "Wrong final cell [2][1] state");

    free2DArray(a, wEmpty.rows, wEmpty.columns);
    freeWorld(finWEmpty);


    // 0 generations

    struct World wZeroGens;
    wZeroGens.nrOfGenerations = 0;
    wZeroGens.rows = 3;
    wZeroGens.columns = 4;
    a = malloc2DArray(wZeroGens.rows, wZeroGens.columns);

    a[0][0] = 1;
    a[0][1] = 1;
    a[0][2] = 0;
    a[0][3] = 1;
    a[1][0] = 1;
    a[1][1] = 1;
    a[1][2] = 0;
    a[1][3] = 0;
    a[2][0] = 1;
    a[2][1] = 0;
    a[2][2] = 0;
    a[2][3] = 1;
    wZeroGens.state = a;

    const struct World* finWZeroGens = finalState(&wZeroGens);
    TEST_ASSERT_NOT_NULL_MESSAGE(finWZeroGens, "finalState returned a NULL pointer");
    TEST_ASSERT_NOT_NULL_MESSAGE(finWZeroGens->state, "finalState returned pointer to World with NULL state array");
    TEST_ASSERT_NOT_EMPTY_MESSAGE(finWZeroGens->state, "finalState returned pointer to World with empty state array");
    TEST_ASSERT_EQUAL_INT(finWZeroGens->nrOfGenerations, wZeroGens.nrOfGenerations);
    TEST_ASSERT_EQUAL_INT(finWZeroGens->state[0][0], wZeroGens.state[0][0]);
    TEST_ASSERT_EQUAL_INT(finWZeroGens->state[1][0], wZeroGens.state[1][0]);
    TEST_ASSERT_EQUAL_INT(finWZeroGens->state[1][1], wZeroGens.state[1][1]);
    TEST_ASSERT_EQUAL_INT(finWZeroGens->state[2][1], wZeroGens.state[2][1]);
    TEST_ASSERT_EQUAL_INT(finWZeroGens->state[2][2], wZeroGens.state[2][2]);

    free2DArray(a, wZeroGens.rows, wZeroGens.columns);
    freeWorld(finWZeroGens);

}

void test_nextState() {

    // A normal case

    int** a = NULL;
    a = malloc2DArray(3, 4);
    
    a[0][0] = 0;
    a[0][1] = 1;
    a[0][2] = 0;
    a[0][3] = 1;
    a[1][0] = 0;
    a[1][1] = 1;
    a[1][2] = 1;
    a[1][3] = 0;
    a[2][0] = 1;
    a[2][1] = 1;
    a[2][2] = 0;
    a[2][3] = 1;

    int** nextNorm = nextState(a, 3, 4);

    TEST_ASSERT_NOT_NULL_MESSAGE(nextNorm, "nextState returned a NULL pointer");
    TEST_ASSERT_NOT_EMPTY_MESSAGE(nextNorm, "nextState returned pointer to an empty state array");
    TEST_ASSERT_MESSAGE(nextNorm[0][0] == 0, "Wrong next cell [0][0] state");
    TEST_ASSERT_MESSAGE(nextNorm[1][0] == 0, "Wrong next cell [1][0] state");
    TEST_ASSERT_MESSAGE(nextNorm[1][2] == 0, "Wrong next cell [1][2] state");
    TEST_ASSERT_MESSAGE(nextNorm[2][1] == 1, "Wrong next cell [2][1] state");
    TEST_ASSERT_MESSAGE(nextNorm[2][3] == 0, "Wrong next cell [2][3] state");

    free2DArray(a, 3, 4);
    free2DArray(nextNorm, 3, 4);


    // Minimum size

    a = malloc2DArray(2, 2);
    
    a[0][0] = 1;
    a[0][1] = 1;
    a[1][0] = 0;
    a[1][1] = 1;

    int** nextMin = nextState(a, 2, 2);

    TEST_ASSERT_NOT_NULL_MESSAGE(nextMin, "nextState returned a NULL pointer");
    TEST_ASSERT_NOT_EMPTY_MESSAGE(nextMin, "nextState returned pointer to an empty state array");
    TEST_ASSERT_MESSAGE(nextMin[0][0] == 1, "Wrong next cell [0][0] state");
    TEST_ASSERT_MESSAGE(nextMin[0][1] == 1, "Wrong next cell [0][1] state");
    TEST_ASSERT_MESSAGE(nextMin[1][0] == 1, "Wrong next cell [1][0] state");
    TEST_ASSERT_MESSAGE(nextMin[1][1] == 1, "Wrong next cell [1][1] state");

    free2DArray(a, 2, 2);
    free2DArray(nextMin, 2, 2);

}

void test_worldIsValid() {

    // A normal case

    struct World w;
    w.nrOfGenerations = 3;
    w.rows = 3;
    w.columns = 4;

    int** a = NULL;
    a = malloc2DArray(3, 4);
    a[0][0] = 0;
    a[0][1] = 1;
    a[0][2] = 0;
    a[0][3] = 1;
    a[1][0] = 0;
    a[1][1] = 1;
    a[1][2] = 1;
    a[1][3] = 0;
    a[2][0] = 1;
    a[2][1] = 1;
    a[2][2] = 0;
    a[2][3] = 1;

    w.state = a;

    int result = worldIsValid(&w);
    TEST_ASSERT_MESSAGE(result == 1, "Result should be 1 for a normal case");

    // 0 generations

    w.nrOfGenerations = 0;
    result = worldIsValid(&w);
    TEST_ASSERT_MESSAGE(result == 1, "Result should be 1 for 0 generations");

    // Maximum allowed nr of generations

    w.nrOfGenerations = MAX_GENERATIONS;
    result = worldIsValid(&w);
    TEST_ASSERT_MESSAGE(result == 1, "Result should be 1 for maximum allowed nr of generations");

    // Negative generations

    w.nrOfGenerations = -3;
    result = worldIsValid(&w);
    TEST_ASSERT_MESSAGE(result == 0, "Result should be 0 for negative generations");
    w.nrOfGenerations = 3;

    // Generations out of bounds

    w.nrOfGenerations = MAX_GENERATIONS+5;
    result = worldIsValid(&w);
    TEST_ASSERT_MESSAGE(result == 0, "Result should be 0 for generations out of bounds");
    w.nrOfGenerations = 3; 

    // A cell with value other than 1 or 0

    a[1][1] = 5;
    result = worldIsValid(&w);
    TEST_ASSERT_MESSAGE(result == 0, "Result should be 0 for cells with values other than 1 or 0");
    a[1][1] = 1;

    free2DArray(a, 3, 4);
}

void test_mallocWorld() {

    // A normal case

    struct World* w;
    int** a;
    a = malloc2DArray(3, 4);
    w = mallocWorld(10, 3, 4, a);

    TEST_ASSERT_MESSAGE(w->nrOfGenerations == 10, "Wrong nr of generations");
    TEST_ASSERT_MESSAGE(w->rows == 3, "Wrong nr of rows");
    TEST_ASSERT_MESSAGE(w->columns == 4, "Wrong nr of columns");

    freeWorld(w);

}


void setUp() {

}

void tearDown() {

}

int main() {
    UNITY_BEGIN();
    RUN_TEST(test_finalState);
    RUN_TEST(test_nextState);
    RUN_TEST(test_worldIsValid);
    RUN_TEST(test_mallocWorld);

    return UNITY_END();
}