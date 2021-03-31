#include "logic.h"

/** Entry point for displaying the evolutionary process graphically
 * Takes in struct to initial state of the world and displays the cells as squares
 * Listens for user input - either right-arrow key or Esc
 * If right-arrow key is pressed, displays the next evolutionary step
 * If Esc is pressed, exits the program
 * Exits with code 0 if successful, returns 1 otherwise */
int display (const struct World* initialState) {

    // SDL
    // Loop through all generations, while user hasn't pressed Esc
    // Use nextState from logic
    return -1;

    // Free the array pointer for INITIAL state in the struct, and then the struct pointer itself
    // Work in reverse to deallocate the 2D array:
    // for(i=0; i<columns; i++)  { free(p[i]); }
    // free (p);

    // FREE before quitting, either bcs loop finished, or user pressed Esc

    exit(0);
}

/** Initialise the graphical display using SDL
 * Return 0 if successful, 1 otherwise */
static int initialiseDisplay () {

    return -1;
}

/** Takes in a pointer to 2D array representing a state of the world
 * Displays it graphically
 * Returns 0 if successful, 1 otherwise */
static int displayState (int** state, const int rows, const int cols) {

    return -1;
}