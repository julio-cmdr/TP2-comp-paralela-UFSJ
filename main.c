#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include "ecosystem.h"

int main(int argc, char *argv[]) {
	if (argc < 2) {
		printf("Favor passar um arquivo de entrada!\n");
		exit(1);
	}

	int i, j;
	Ecosystem eco = ecosystem_init(argv[1]);

	extern int gverbose;
	for (i = 2; i < argc; i++) {
		if (strcmp(argv[i], "-v") == 0 && i + 1 < argc) {
			gverbose = atoi(argv[i + 1]);
			break;
		}
	}

	for(eco.current_gen = 0; eco.current_gen < eco.n_gen; eco.current_gen++){
		ecosystem_print(&eco);
		// Deciding movement
		for(j = 0; j < eco.animal_count[RABBIT]; j++){
			move_rabbit(&eco, j);
		}

		for(j = 0; j < eco.animal_count[RABBIT]; j++){
			ecosystem_resolve_conflicts(&eco, j, RABBIT, RABBIT);
		}

		// Updating the position.
		for (j = 0; j < eco.animal_count[RABBIT]; j++) {
			ecosystem_update_position(&eco, j, RABBIT);
		}

		//ecosystem_print(&eco);

		for(j = 0; j < eco.animal_count[FOX]; j++){
			move_fox(&eco, j);
		}

		for(j = 0; j < eco.animal_count[FOX]; j++){
			ecosystem_resolve_conflicts(&eco, j, FOX, FOX);
		}
		for(j = 0; j < eco.animal_count[RABBIT]; j++){
			ecosystem_resolve_conflicts(&eco, j, RABBIT, FOX);
		}

		// Updating the position.
		for (j = 0; j < eco.animal_count[FOX]; j++) {
			ecosystem_update_position(&eco, j, FOX);
		}

		// TODO: talvez deixar o loop de fora p/ facilitar a paralelização?
		ecosystem_normalize(&eco, RABBIT);
		ecosystem_normalize(&eco, FOX);

	}
	ecosystem_print(&eco);

	eco.n = eco.animal_count[FOX] + eco.animal_count[RABBIT] + eco.rock_count;

	printf("%d %d %d %d %d %d %d\n", eco.gen_proc_rabbits, eco.gen_proc_fox, eco.gen_food_fox, eco.n_gen, eco.l, eco.c, eco.n);
	for(i = 0; i < eco.l; i++) {
		for (j = 0; j < eco.c; j++) {
			if (eco.matrix[i][j].type != EMPTY) {
				object_print(eco.matrix[i][j].type, i, j);
			}
		}
	}

	return 0;
}
