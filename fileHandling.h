#include <stdio.h>

const struct World* loadInitialState (const char* filename, const char* generations);
int saveFinalState (const struct World* finalState, const char* filename);
static int onlyNumbers (const char* text);