#include "logic.h"
#include "fileHandling.h"

/** Opens the file with provided filename
 * Reads the file and extracts information about the world from it
 * Validates string "generations", which should only include numbers 
 * Puts all the information into a const variable of type struct World accessed via pointer
 * Returns the pointer to the world structure if successful, NULL otherwise */
const struct World* loadInitialState (const char* filename, const char* generations) {
    // Check if nr of generations within range, all numbers (onlyNumbers()), and stoi
    // Check if file with this name exists, open file
    // Create pointer to 2D array: int ** p
    // Read the 1st line, store in 1D array - that's our 1st row. Nr of columns = size of 1D array
    // On 1st line, malloc: p = (int* )malloc(sizeof(int* ));
    // p[row] = malloc(columns * sizeof(int)); 
    // For every column, initialise: p[row][col] = ...
    // Every next line, realloc to add new row: p = (int* )realloc(rows * sizeof(int* ));
    // Check if nr of columns in this line same as 1st line
    // p[row] = malloc(columns * sizeof(int));
    // For every column, initialise: p[row][col] = ...
    // https://www.geeksforgeeks.org/dynamically-allocate-2d-array-c/
    // arr[i][j] is same as *(*(arr+i)+j) 

    // Create the pointer to struct, MALLOC
    // Put rows, cols, generations into struct (directly by value, dereferencing struct)
    // Put pointer to array into struct
}

/** Saves the state of the 2D array in a txt file
 * Then frees the memory allocated for the 2D array and World struct
 * Returns 0 if successful, 1 otherwise */
 int saveFinalState (const struct World* finalState, const char* filename) {
    // Free the array pointer for FINAL state in the struct, and then the struct pointer itself
    // Work in reverse to deallocate the 2D array:
    // for(i=0; i<columns; i++)  { free(p[i]); }
    // free (p); 
}

/** Checks whether the provided text contains only numbers
 * Returns 1 if yes, 0 otherwise */
static int onlyNumbers (const char* text) {
    return -1;
}