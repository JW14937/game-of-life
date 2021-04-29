#include "unity.h"
#include "fileHandling.h"
#include "logic.h"
#include "graphics.h"
#include <stdlib.h>
#include <string.h>


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
    TEST_ASSERT_NOT_NULL_MESSAGE(finWEmpty, "finalState (Empty world) returned a NULL pointer");
    TEST_ASSERT_NOT_NULL_MESSAGE(finWEmpty->state, "finalState (Empty world) returned pointer to World with NULL state array");
    TEST_ASSERT_NOT_EMPTY_MESSAGE(finWEmpty->state, "finalState (Empty world) returned pointer to World with empty state array");
    TEST_ASSERT_EQUAL_INT(finWEmpty->nrOfGenerations, wEmpty.nrOfGenerations);
    TEST_ASSERT_MESSAGE(finWEmpty->state[0][0] == 0, "finalState (Empty world): Wrong final cell [0][0] state");
    TEST_ASSERT_MESSAGE(finWEmpty->state[0][1] == 0, "finalState (Empty world): Wrong final cell [0][1] state");
    TEST_ASSERT_MESSAGE(finWEmpty->state[1][1] == 0, "finalState (Empty world): Wrong final cell [1][1] state");
    TEST_ASSERT_MESSAGE(finWEmpty->state[2][0] == 0, "finalState (Empty world): Wrong final cell [2][0] state");
    TEST_ASSERT_MESSAGE(finWEmpty->state[2][1] == 0, "finalState (Empty world): Wrong final cell [2][1] state");

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
    TEST_ASSERT_NOT_NULL_MESSAGE(finWZeroGens, "finalState (0 generations) returned a NULL pointer");
    TEST_ASSERT_NOT_NULL_MESSAGE(finWZeroGens->state, "finalState (0 generations) returned pointer to World with NULL state array");
    TEST_ASSERT_NOT_EMPTY_MESSAGE(finWZeroGens->state, "finalState (0 generations) returned pointer to World with empty state array");
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
    TEST_ASSERT_MESSAGE(nextNorm[0][0] == 0, "nextState: Wrong next cell [0][0] state");
    TEST_ASSERT_MESSAGE(nextNorm[1][0] == 0, "nextState: Wrong next cell [1][0] state");
    TEST_ASSERT_MESSAGE(nextNorm[1][2] == 0, "nextState: Wrong next cell [1][2] state");
    TEST_ASSERT_MESSAGE(nextNorm[2][1] == 1, "nextState: Wrong next cell [2][1] state");
    TEST_ASSERT_MESSAGE(nextNorm[2][3] == 0, "nextState: Wrong next cell [2][3] state");

    free2DArray(a, 3, 4);
    free2DArray(nextNorm, 3, 4);


    // Minimum size

    a = malloc2DArray(2, 2);
    
    a[0][0] = 1;
    a[0][1] = 1;
    a[1][0] = 0;
    a[1][1] = 1;

    int** nextMin = nextState(a, 2, 2);

    TEST_ASSERT_NOT_NULL_MESSAGE(nextMin, "nextState (Min size) returned a NULL pointer");
    TEST_ASSERT_NOT_EMPTY_MESSAGE(nextMin, "nextState (Min size) returned pointer to an empty state array");
    TEST_ASSERT_MESSAGE(nextMin[0][0] == 1, "nextState (Min size): Wrong next cell [0][0] state");
    TEST_ASSERT_MESSAGE(nextMin[0][1] == 1, "nextState (Min size): Wrong next cell [0][1] state");
    TEST_ASSERT_MESSAGE(nextMin[1][0] == 1, "nextState (Min size): Wrong next cell [1][0] state");
    TEST_ASSERT_MESSAGE(nextMin[1][1] == 1, "nextState (Min size): Wrong next cell [1][1] state");

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
    TEST_ASSERT_MESSAGE(result == 1, "worldIsValid: Result should be 1 for a normal case");

    // 0 generations

    w.nrOfGenerations = 0;
    result = worldIsValid(&w);
    TEST_ASSERT_MESSAGE(result == 1, "worldIsValid: Result should be 1 for 0 generations");

    // Maximum allowed nr of generations

    w.nrOfGenerations = MAX_GENERATIONS;
    result = worldIsValid(&w);
    TEST_ASSERT_MESSAGE(result == 1, "worldIsValid: Result should be 1 for maximum allowed nr of generations");

    // Negative generations

    w.nrOfGenerations = -3;
    result = worldIsValid(&w);
    TEST_ASSERT_MESSAGE(result == 0, "worldIsValid: Result should be 0 for negative generations");
    w.nrOfGenerations = 3;

    // Generations out of bounds

    w.nrOfGenerations = MAX_GENERATIONS+5;
    result = worldIsValid(&w);
    TEST_ASSERT_MESSAGE(result == 0, "worldIsValid: Result should be 0 for generations out of bounds");
    w.nrOfGenerations = 3; 

    // A cell with value other than 1 or 0

    a[1][1] = 5;
    result = worldIsValid(&w);
    TEST_ASSERT_MESSAGE(result == 0, "worldIsValid: Result should be 0 for cells with values other than 1 or 0");
    a[1][1] = 1;

    free2DArray(a, 3, 4);
}

void test_mallocWorld() {

    // A normal case

    struct World* w;
    int** a;
    a = malloc2DArray(3, 4);
    w = mallocWorld(10, 3, 4, a);

    TEST_ASSERT_MESSAGE(w->nrOfGenerations == 10, "mallocWorld: Wrong nr of generations");
    TEST_ASSERT_MESSAGE(w->rows == 3, "mallocWorld: Wrong nr of rows");
    TEST_ASSERT_MESSAGE(w->columns == 4, "mallocWorld: Wrong nr of columns");

    freeWorld(w);

}

// File handling module

void test_loadInitialState() {

    // Create an example file

    FILE *file;
    file = fopen("exampleInitialStateFile.txt", "w");
    if(file == NULL) {
        printf("\nError: The file to create an example for unit tests could not be opened\n");
        return 1;
    }

    fprintf(file, "101010100001\n");
    fprintf(file, "100010100010\n");
    fprintf(file, "000101001101\n");

    fclose(file);

    // A normal case

    const struct World* w = NULL;
    w = loadInitialState("exampleInitialStateFile.txt", "5", "3", "12");

    TEST_ASSERT_NOT_NULL_MESSAGE(w, "loadInitialState returned a NULL pointer");
    TEST_ASSERT_NOT_NULL_MESSAGE(w->state, "loadInitialState returned pointer to World with NULL state array");
    TEST_ASSERT_NOT_EMPTY_MESSAGE(w->state, "loadInitialState returned pointer to World with empty state array");
    TEST_ASSERT_MESSAGE(w->nrOfGenerations == 5, "loadInitialState: Wrong nr of generations");
    TEST_ASSERT_MESSAGE(w->rows == 3, "loadInitialState: Wrong nr of rows");
    TEST_ASSERT_MESSAGE(w->columns == 12, "loadInitialState: Wrong nr of columns");
    TEST_ASSERT_MESSAGE(w->state[0][0] == 1, "loadInitialState: Wrong next cell [0][0] state");
    TEST_ASSERT_MESSAGE(w->state[0][11] == 1, "loadInitialState: Wrong next cell [0][11] state");
    TEST_ASSERT_MESSAGE(w->state[1][5] == 0, "loadInitialState: Wrong next cell [1][5] state");
    TEST_ASSERT_MESSAGE(w->state[1][10] == 1, "loadInitialState: Wrong next cell [1][10] state");
    TEST_ASSERT_MESSAGE(w->state[2][0] == 0, "loadInitialState: Wrong next cell [2][0] state");
    TEST_ASSERT_MESSAGE(w->state[2][7] == 0, "loadInitialState: Wrong next cell [2][7] state");
    TEST_ASSERT_MESSAGE(w->state[2][11] == 1, "loadInitialState: Wrong next cell [0][0] state");

    freeWorld(w);


    // Nr of generations at the maximum allowed value

    w = loadInitialState("exampleInitialStateFile.txt", "100", "3", "12");

    TEST_ASSERT_NOT_NULL_MESSAGE(w, "loadInitialState (Max Generations) returned a NULL pointer");
    TEST_ASSERT_NOT_NULL_MESSAGE(w->state, "loadInitialState (Max Generations) returned pointer to World with NULL state array");
    TEST_ASSERT_NOT_EMPTY_MESSAGE(w->state, "loadInitialState (Max Generations) returned pointer to World with empty state array");
    TEST_ASSERT_MESSAGE(w->nrOfGenerations == 100, "loadInitialState (Max Generations): Wrong nr of generations");
    TEST_ASSERT_MESSAGE(w->rows == 3, "loadInitialState (Max Generations): Wrong nr of rows");
    TEST_ASSERT_MESSAGE(w->columns == 12, "loadInitialState (Max Generations): Wrong nr of columns");
    TEST_ASSERT_MESSAGE(w->state[0][0] == 1, "loadInitialState (Max Generations): Wrong cell [0][0] state");
    TEST_ASSERT_MESSAGE(w->state[0][11] == 1, "loadInitialState (Max Generations): Wrong cell [0][11] state");
    TEST_ASSERT_MESSAGE(w->state[1][5] == 0, "loadInitialState (Max Generations): Wrong cell [1][5] state");
    TEST_ASSERT_MESSAGE(w->state[1][10] == 1, "loadInitialState (Max Generations): Wrong cell [1][10] state");
    TEST_ASSERT_MESSAGE(w->state[2][0] == 0, "loadInitialState (Max Generations): Wrong cell [2][0] state");
    TEST_ASSERT_MESSAGE(w->state[2][7] == 0, "loadInitialState (Max Generations): Wrong cell [2][7] state");
    TEST_ASSERT_MESSAGE(w->state[2][11] == 1, "loadInitialState (Max Generations): Wrong cell [0][0] state");

    freeWorld(w);
}

void test_saveFinalState() {

    // A normal case

    int** a;
    a = malloc2DArray(2, 2);
    a[0][0] = 1;
    a[0][1] = 0;
    a[1][0] = 0;
    a[1][1] = 1;

    struct World* w;
    w = mallocWorld(5, 2, 2, a);

    saveFinalState(w, "testSaveFinalState.txt");
    
    printf("End of unit test");

    struct World* wCheck;
    wCheck = loadInitialState("testSaveFinalState.txt", "11", "2", "2");

    TEST_ASSERT_MESSAGE(wCheck->rows == 2, "saveFinalState: Wrong nr of rows");
    TEST_ASSERT_MESSAGE(wCheck->columns == 2, "saveFinalState: Wrong nr of columns");
    TEST_ASSERT_MESSAGE(wCheck->state[0][0] == 1, "saveFinalState: Wrong cell [0][0] state");
    TEST_ASSERT_MESSAGE(wCheck->state[0][1] == 0, "saveFinalState: Wrong cell [0][1] state");
    TEST_ASSERT_MESSAGE(wCheck->state[1][0] == 0, "saveFinalState: Wrong cell [1][0] state");
    TEST_ASSERT_MESSAGE(wCheck->state[1][1] == 1, "saveFinalState: Wrong cell [1][1] state");

    freeWorld(wCheck);
}

void test_onlyDigits() {

    int result;

    // A normal case

    result = onlyDigits("123");
    TEST_ASSERT_MESSAGE(result == 1, "onlyDigits should return 1 for 123");

    // Letter instead of a digit

    result = onlyDigits("123a5");
    TEST_ASSERT_MESSAGE(result == 0, "onlyDigits should return 0 for letters");

    // A space

    result = onlyDigits("12 3");
    TEST_ASSERT_MESSAGE(result == 0, "onlyDigits should return 0 for spaces");

    // A hyphen

    result = onlyDigits("12-3");
    TEST_ASSERT_MESSAGE(result == 0, "onlyDigits should return 0 for -");
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
    RUN_TEST(test_loadInitialState);
    RUN_TEST(test_saveFinalState);
    RUN_TEST(test_onlyDigits);

    return UNITY_END();
}