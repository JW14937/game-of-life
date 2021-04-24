#include "fileHandling.h"
#include "logic.h"
//#include "graphics.h"

int main(int argc, char *argv[])  {

    /*if(argc != 3) {
      printf("Provide 2 arguments: <initial state txt file name> <nr of generations>\n");
      return 1;
    }*/

    //const struct World* initialState = loadInitialState(argv[0], argv[1]);

    // First calculate the final state (finalState), then save it to file (saveFinalState)
    //saveFinalState(finalState(initialState), "finalState.txt");

    // Display the evolutionary process graphically
    //display(initialState);

    struct World w;
    w.nrOfGenerations = 3;
    w.rows = 3;
    w.columns = 4;
    int** a;
    a = (int**)malloc(3* sizeof(int*));
    a[0] = (int*)malloc(4 * sizeof(int));
    a[0][0] = 0;
    a[0][1] = 1;
    a[0][2] = 0;
    a[0][3] = 1;
    a[1] = (int*)malloc(4 * sizeof(int));
    a[1][0] = 1;
    a[1][1] = 0;
    a[1][2] = 0;
    a[1][3] = 0;
    a[2] = (int*)malloc(4 * sizeof(int));
    a[2][0] = 0;
    a[2][1] = 1;
    a[2][2] = 0;
    a[2][3] = 1;
    w.state = a;

    const struct World* initialTestState = &w;

    finalState(initialTestState);

    //display(initialTestState);

    return 0;
}