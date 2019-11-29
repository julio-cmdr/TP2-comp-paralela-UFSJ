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

	for(i = 0; i < eco.l; i++) {
		for (j = 0; j < eco.c; j++) {
			if (eco.matrix[i][j].index != -1) {
				object_print(eco.animals[eco.matrix[i][j].type][eco.matrix[i][j].index]);
			}
		}
	}

	printf("\n");
	ecosystem_print(&eco, 0);

	int rabbit_count = 0;

	for(i = 0; i < eco.n_gen; i++){
		// Deciding movement
		for(j = 0; j < eco.animal_count[RABBIT]; j++){
			move_rabbit(&eco, j);
		}

		// Synchronizing.
		// TODO: otimizar
		for(j = 0; j < eco.animal_count[RABBIT]; j++){
			ecosystem_resolve_conflicts(&eco, j, RABBIT, RABBIT);
		}
		// Normalizing the list.
		// TODO: talvez deixar o loop de fora p/ facilitar a paralelização?
		rabbit_count = ecosystem_normalize(&eco, RABBIT);
		eco.animal_count[RABBIT] = rabbit_count;

		// Updating the position.
		for (j = 0; j < eco.animal_count[RABBIT]; j++) {
			rabbit_count += ecosystem_update_position(&eco, j, RABBIT);
		}

		eco.animal_count[RABBIT] = rabbit_count;

		/*
		for(j = 0; j < eco.animal_count[FOX]; j++){
			move_fox(&eco, j);
		}
		*/
		ecosystem_print(&eco, i + 1);
	}

	return 0;
}
