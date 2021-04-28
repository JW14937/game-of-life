#include "logic.h"
#include "fileHandling.h"
#include <stdlib.h>
#include <string.h>

/** Opens the file with provided filename
 * Reads the file and extracts information about the world from it
 * Validates the other command line arguments, which should only contain digits 
 * Puts all the information into a const variable of type struct World accessed via pointer
 * Returns the pointer to the world structure if successful, NULL otherwise */
const struct World* loadInitialState (const char* filename, const char* generationsString, const char* rowsString, const char* columnsString) {

    // Convert the last 3 command arguments (generations, rows, columns) to integers

    // Generations
    if(!onlyDigits(generationsString)) {
        printf("\nError: Generations must be a number\n");
        exit(1);
    }
    int generations = atoi(generationsString);

    // Rows
    if(!onlyDigits(rowsString)) {
        printf("\nError: Rows must be a number\n");
        exit(1);
    }
    int rows = atoi(rowsString);

    // Columns
    if(!onlyDigits(columnsString)) {
        printf("\nError: Columns must be a number\n");
        exit(1);
    }
    int columns = atoi(columnsString);


    // Open the file

    FILE *file;
    file = fopen(filename, "r");
    if(file == NULL) {
        printf("\nError: File with this name could not be opened\n");
    }

    // Allocate the memory for the world structure

    const struct World* initialStateWorld = NULL;
    int** initialStateArray = malloc2DArray(rows, columns);
    initialStateWorld = mallocWorld(generations, rows, columns, initialStateArray);


    // Read through the file line by line

    char line[MAX_COLS];
    int rowCounter = 0;

    while(fgets(line, MAX_COLS, file) != NULL) {

        line[strcspn(line, "\n")] = 0; // Remove the trailing newline

        // Validate that the line contains only digits and is of a correct length
        if(!onlyDigits(line)) {
            printf("\nError: The file must only contain digits\n");
            exit(1);
        }
        if(strlen(line) != columns) {
            printf("\nError: The file contains more columns than specified\n");
            exit(1);
        }

        // Go through each character in the line, validate it, and add to the initialStateArray
        for(int i=0; i<strlen(line); i++) {

            if(line[i] == '1') { initialStateArray[rowCounter][i] = 1; }

            else if(line[i] == '0') { initialStateArray[rowCounter][i] = 0; }

            else {
                printf("\nError: The file must only contain 1 and  0 characters");
                exit(1);
            }
        }

        rowCounter++;
    }

    fclose(file);

    // Final validation
    if(!worldIsValid(initialStateWorld)) {
        printf("\nError: The world is not valid\n");
        printf("\nEither one of the command-line arguments or the initial state file are incorrect, or there was an error loading the file\n");
        exit(1);
    }

    return initialStateWorld;
}

/** Saves the state of the 2D array in a txt file
 * Then frees the memory allocated for the 2D array and World struct
 * Returns 0 if successful, 1 otherwise */
 int saveFinalState (const struct World* finalState, const char* filename) {

    // Validate the world
    if(!worldIsValid(finalState)) {
        printf("\nError: Could not save the final state, as it was invalid\n");
        return 1;
    }

    // Open the file

    FILE *file;
    file = fopen(filename, "w");
    if(file == NULL) {
        printf("\nError: The file to save the final state could not be opened\n");
        return 1;
    }

    // Save the final array state to the file, line by line
    for(int i=0; i<finalState->rows; i++) {

        for(int j=0; j<finalState->columns; j++) {
            fprintf(file, "%d", finalState->state[i][j]);
        }

        if(i != (finalState->rows-1)) { fprintf(file, "\n"); }
    }

    fclose(file);
    freeWorld(finalState);

    return 0;
}

/** Checks whether the provided text contains only numbers
 * Returns 1 if yes, 0 otherwise */
int onlyDigits (const char* text) {

    for(int i=0; i<strlen(text); i++) {
        if(text[i] < 48 || text[i] > 57) {
            return 0;
        }
    }

    return 1;
}