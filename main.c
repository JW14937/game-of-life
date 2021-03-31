#include "fileHandling.h"
#include "logic.h"
#include "graphics.h"

int main(int argc, char *argv[])  {

    if(argc != 2) {
      printf("Provide 2 arguments: <initial state txt file name> <nr of generations>\n");
      return 1;
    }

    const struct World* initialState = loadInitialState(argv[0], argv[1]);

    // First calculate the final state (finalState), then save it to file (saveFinalState)
    saveFinalState(finalState(initialState), "finalState.txt");

    // Display the evolutionary process graphically
    display(initialState);

    return 0;
}