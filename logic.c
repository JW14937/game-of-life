#include "logic.h"
#include <stdlib.h>

/** Takes in a pointer to World structure containing initial state
 * Then iterates through all generations, and calculates the next one by calling nextState
 * The only thing different between initialState and finalState is the 2D world state array
 * Returns pointer to World structure containing final state 2D array if successful, 0 otherwise */
const struct World* finalState (const struct World* initialState) {
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
    // Validate nr of rows and columns (in range)
    // Make sure prevState not null
    // Go through all rows and columns in the 2D array; make sure each row not null
    // Calculate the next state using rules of Game of Life
    // On edges - assume neighbours outside are dead
    // First, calculate nr of neighbours, then pick next state depending on it
    // Create a 2D array using pointer, malloc each cell (like in fileHandling)
    // Return the pointer
    return NULL;
}