The unit tests can be compiled using cmake. Unfortunately, to run the main program, it has to be compiled manually using the following command:

gcc main.c logic.c graphics.c fileHandling.c -std=c99 -lSDL2 -o ./life

Then, the program can be run with the following command:

./life <name_of_the_initial_state_file.txt> <nr_of_generations> <rows> <columns>

The initial state file must be a .txt file containing rows of 1's (live cells) and 0's (dead cells)


The program will save the state of the world after the specified number of generations to a file called "finalState.txt".

Then, the initial state world will be displayed graphically. The user can advance by 1 generation by clicking the right-arrow key. The number of generations that can be displayed graphically is determined by the nr of generations specified by the user as an argument. When the last generation is reached, the graphical window closes after 2 seconds.
The graphical window can be closed before the final generation, if the user closes the window or presses Esc.