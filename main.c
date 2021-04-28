#include "fileHandling.h"
#include "logic.h"
#include "graphics.h"

int main(int argc, char *argv[])  {

    if(argc != 5) {
      printf("Provide 4 arguments: <initial state txt file name> <nr of generations> <rows> <columns>\n");
      return 1;
    }

    const struct World* initialState = loadInitialState(argv[1], argv[2], argv[3], argv[4]);

    // First calculate the final state (finalState), then save it to file (saveFinalState)
    saveFinalState(finalState(initialState), "finalState.txt");

    // Display the evolutionary process graphically
    display(initialState);

    // Free the memory allocated to the initial World structure
    freeWorld(initialState);

    return 0;
}