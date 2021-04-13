#define MAX_ROWS 50
#define MAX_COLS 50
#define MAX_GENERATIONS 100

// Struct containing information read from the initial state file
struct World {
    int nrOfGenerations; // User-specified number of generations (steps)
    int** state; // Pointer to a 2D array representing the world state
    int rows; // Nr of rows in the 2D array
    int columns; // Nr of columns in the 2D array
};

const struct World* finalState (const struct World* initialState);
int** nextState (const int** prevState, const int rows, const int cols);