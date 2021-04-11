#include "logic.h"
#include <stdlib.h>

/** Takes in a pointer to World structure containing initial state
 * Then iterates through all generations, and calculates the next one by calling nextState
 * The only thing different between initialState and finalState is the 2D world state array
 * Returns pointer to World structure containing final state 2D array if successful, NULL otherwise */
const struct World* finalState (const struct World* initialState) {
    // If any validation doesn't work, exit program
    // Validate struct pointer (not null) and array pointer (not null)
    // Validate row and col, and generations (within range)
    // Create a non-const 2D array (not pointer), and copy initial state array into it
    // Create a pointer to that array and pass to nextState
    // Change the state of the 2D array to that returned by nextState pointer
    // Free the nextState pointer - first each row, then ** pointer (like in saveFinalState)

    // Iterate through all generations

    // Malloc for finalState struct pointer
    // Malloc for final array using ** pointers and copy the non-const 2D array into it
    return NULL;
}

/** Takes in a pointer to 2D array containing state of the world, and nr of rows and columns in that array
 * Calculates the state of the world in the next generation, according to the rules of the Game of Life
 * Returns the next state of the world (pointer to 2D array), or a NULL pointer if an error occured
 * Possible errors: 
 * - Incorrect nr of rows or columns
 * - A cell containing something other than 1 or 0 
 * - Null pointer to previous state array */
int** nextState (int** prevState, const int rows, const int cols) {

    if(prevState == NULL) { exit(1); }
    if(rows<=0 || cols<=0 || rows>MAX_ROWS || cols>MAX_COLS) { exit(1); }

    // Allocate space for the state array after 1 generation
    int** nextStateArray;
    nextStateArray = (int**)malloc(rows * sizeof(int*));
    for(int i=0; i<cols; i++) { nextStateArray[i] = (int*)malloc(cols * sizeof(int)); }

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