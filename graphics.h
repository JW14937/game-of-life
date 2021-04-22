#include <SDL.h>

int display (const struct World* initialState);
static int initialiseDisplay ();
static int displayState (const int** state, const int rows, const int cols);

#define TILE_SIZE 32

// Below citation
typedef struct game_node {
    int x;
    int y;
} node;


