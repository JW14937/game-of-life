#include "logic.h"
#include <stdlib.h>
#include <stdio.h>

/** Takes in a pointer to World structure containing initial state
 * Then iterates through all generations, and calculates the next one by calling nextState
 * The only thing different between initialState and finalState is the 2D world state array
 * Returns pointer to World structure containing final state 2D array if successful, NULL otherwise */
const struct World* finalState (const struct World* initialState) {

    // Validation
    if(!worldIsValid(initialState)) { 
        printf("\nError: Could not calculate the final state. The initial state world is invalid\n");
        exit(1); 
    }
    if(initialState->nrOfGenerations == 0) { 

        // Create a copy, because it will be freed at the end
        struct World* worldCopy = NULL;

        int** arrayCopy = NULL;
        arrayCopy = malloc2DArray(initialState->rows, initialState->columns);

        for(int i=0; i<initialState->rows; i++) {
            for(int j=0; j<initialState->columns; j++) {
                arrayCopy[i][j] = initialState->state[i][j];
            }
        }

        worldCopy = mallocWorld(initialState->nrOfGenerations, initialState->rows, initialState->columns, arrayCopy);
        return worldCopy; 
    }

    // First generation
    int** nextStateArray = nextState(initialState->state, initialState->rows, initialState->columns);

    // Subsequent generations

    for(int i=1; i<initialState->nrOfGenerations; i++) {

        // Create a buffer copy:
        // Allocate memory
        int** bufferArray = NULL;
        bufferArray = malloc2DArray(initialState->rows, initialState->columns);
        // Copy
        for(int i=0; i<initialState->rows; i++) {
            for(int j=0; j<initialState->columns; j++) {
                bufferArray[i][j] = nextStateArray[i][j];
            }
        }
        
        // Free the memory occupied by the previous nextStateArray
        free2DArray(nextStateArray, initialState->rows, initialState->columns);

        // Advance the generations by 1, using the buffer copy
        nextStateArray = nextState(bufferArray, initialState->rows, initialState->columns);

        // Free the buffer copy
        free2DArray(bufferArray, initialState->rows, initialState->columns);
    }

    struct World* finalState = NULL;
    finalState = mallocWorld(initialState->nrOfGenerations, initialState->rows, initialState->columns, nextStateArray);

    return finalState;
    // Free the nextStateArray memory at the end function

}

/** Takes in a pointer to 2D array containing state of the world, and nr of rows and columns in that array
 * Calculates the state of the world in the next generation, according to the rules of the Game of Life
 * Returns the next state of the world (pointer to 2D array), or a NULL pointer if an error occured
 * Possible errors: 
 * - Incorrect nr of rows or columns
 * - A cell containing something other than 1 or 0 
 * - Null pointer to previous state array */
int** nextState (const int** prevState, const int rows, const int cols) {

    // Null pointer and rows/columns outside of range validation

    if(prevState == NULL) { 
        printf("\nError: Could not calculate next state. The previous state array is NULL\n");
        exit(1); 
    }
    if(rows <= 0 || cols <= 0 || rows > MAX_ROWS || cols > MAX_COLS) { 
        printf("\nError: Could not calculate next state. The rows or columns are out of bounds\n");
        printf("Rows must be between 2 and %d\n", MAX_ROWS);
        printf("Columns must be between 2 and %d\n", MAX_COLS);
        exit(1); 
    }

    // Allocate space for the state array after 1 generation

    int** nextStateArray;
    nextStateArray = malloc2DArray(rows, cols);

    for(int i=0; i<rows; i++) {
        for(int j=0; j<cols; j++) {
            // Accessing a single cell

            // Validate that cell contains 1 or 0
            if(!(prevState[i][j]==0 || prevState[i][j]==1)) { exit(1); }

            // Count the neighbours
            int neighbours = 0;

            // Top-left
            if( (i-1)>=0 && (j-1)>=0 && prevState[i-1][j-1]==1 ) neighbours++;
            // Top
            if( (i-1)>=0 && prevState[i-1][j]==1 ) neighbours++;
            // Top-right
            if( (i-1)>=0 && (j+1)<cols && prevState[i-1][j+1]==1) neighbours++;
            // Left
            if( (j-1)>=0 && prevState[i][j-1]==1 ) neighbours++;
            // Right
            if( (j+1)<cols && prevState[i][j+1]==1 ) neighbours++;
            // Bottom-left
            if( (i+1)<rows && (j-1)>=0 && prevState[i+1][j-1]==1 ) neighbours++;
            // Bottom
            if( (i+1)<rows && prevState[i+1][j]==1 ) neighbours++;
            // Bottom-right
            if( (i+1)<rows && (j+1)<cols && prevState[i+1][j+1]==1 ) neighbours++;


            // Considering live cells

            if(prevState[i][j]==1) {

                // Underpopulation or overpopulation
                if(neighbours < 2 || neighbours > 3) { nextStateArray[i][j] = 0; }

                // Neighbourhood is just right
                else { nextStateArray[i][j] = 1; }
            }

            // Considering dead cells

            else {

                // Reproduction
                if(neighbours == 3) { nextStateArray[i][j] = 1; }

                // Stay dead
                else { nextStateArray[i][j] = 0; }
            }
        }
    }

    return nextStateArray;
}

/** Takes in a pointer to a World structure and validates the values in it.
 * Returns 0 if one of the following errors is detected:
 * - Null pointer to the World structure or the state array
 * - Rows, columns or generations out of bounds
 * - A cell in the 2D array is not 1 or 0
 * Otherwise, returns 1 */
int worldIsValid (const struct World* world) {

    if(world == NULL) {
        printf("\nError: Pointer to the World structure null\n"); 
        return 0;
    }
    if(world->state == NULL) {
        printf("\nError: Pointer to the state array null\n"); 
        return 0;
    }
    if(world->rows < 2 || world->columns < 2) {
        printf("\nError: Rows or columns below the minimum for a 2D array\n"); 
        return 0;
    }
    if(world->rows > MAX_ROWS || world->columns > MAX_COLS) { 
        printf("\nError: Rows or columns exceeding the limit\n"); 
        return 0;
    }
    if(world->nrOfGenerations < 0 || world->nrOfGenerations > MAX_GENERATIONS) {
        printf("\nError: Number of generations out of bounds\n"); 
        return 0;
    }

    // Check that all cells are either 1 or 0
    for(int i=0; i<world->rows; i++) {
        for(int j=0; j<world->columns; j++) {

            if(world->state[i][j] != 1 && world->state[i][j] != 0) {
                printf("\nError: A cell in the 2D array has a value other than 1 or 0\n");
                return 0;
            }
        }
    }

    return 1;
}

/** Uses malloc to allocate space for a world structure
 * Initialises the structure with the supplied nr of rows, columns, generations, and the state array */
struct World* mallocWorld(int generations, int rows, int cols, int** stateArray) {

    struct World* worldPointer = (struct World* ) malloc(sizeof(struct World));
    
    worldPointer->nrOfGenerations = generations;
    worldPointer->rows = rows;
    worldPointer->columns = cols;
    worldPointer->state = stateArray;

    return worldPointer;
}

/** Uses malloc to allocate the desired number of rows and columns, using the supplied pointer
 * Returns the pointer to the array, or a NULL pointer if the nr of rows or columns is less than 2 */
int** malloc2DArray(int rows, int cols) {

    if(rows < 2 || cols < 2) {
        printf("\nError: Trying to allocate a 2D array with the nr of rows or columns < 2\n");
        printf("\nReturned a NULL pointer\n");
        int** errorPointer = NULL;

        return errorPointer;
    }

    int** arrayPointer = (int**)malloc(rows * sizeof(int*));
    for(int i=0; i<rows; i++) { arrayPointer[i] = (int*)malloc(cols * sizeof(int)); }

    return arrayPointer;
}

/** Frees the memory occupied by the World structure */
void freeWorld(struct World* world) {
    
    free2DArray(world->state, world->rows, world->columns);
    free(world);
}

/** Frees the memory occupied by the array to which the pointer is supplied as an argument
 * Requires the nr of rows and columns of the array */
void free2DArray (int** array, int rows, int cols) {
    for(int i=0; i<rows; i++) {
        free(array[i]);
    }
    free(array);
}