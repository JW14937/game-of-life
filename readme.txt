The unit tests can be compiled using cmake. Unfortunately, to run the main program, it has to be compiled manually using the following command:

gcc main.c logic.c graphics.c fileHandling.c -std=c99 -lSDL2 -o ./life

Then, the program can be run with the following command:

./life <name_of_the_initial_state_file.txt> <nr_of_generations> <rows> <columns>

For the initial state file, the provided glider.txt can be used:

./life glider.txt 4 6 6