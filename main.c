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
	ecosystem_print(&eco);

	int rabbit_count = 0;
	int child_count;
	int next_index = 1;

	for(i = 0; i < eco.n_gen; i++){

		for(j = 0; j < eco.animal_count[RABBIT]; j++){
			move_rabbit(&eco, j);
		}

		child_count = 0;

		// TODO: otimizar
		for(j = 0; j < eco.animal_count[RABBIT]; j++){
			Rabbit *rabbit1 = eco.animals[RABBIT][j];

			if (rabbit1 != NULL) {
				child_count += rabbit1->child != NULL;
				for (int k = 0; k < eco.animal_count[RABBIT]; k++) {
					Rabbit *rabbit2 = eco.animals[RABBIT][k];

					if (
						j != k && rabbit2 != NULL &&
						rabbit1->data.next_pos.x == rabbit2->data.next_pos.x &&
						rabbit1->data.next_pos.y == rabbit2->data.next_pos.y
					) {
						int killed_index = rabbit1->data.generation < rabbit2->data.generation ? j : k;

						Rabbit *killed_rabbit = eco.animals[RABBIT][killed_index];
						eco.matrix[killed_rabbit->data.pos.y][killed_rabbit->data.pos.x].index = -1;
						eco.matrix[killed_rabbit->data.pos.y][killed_rabbit->data.pos.x].type = EMPTY;

						free(killed_rabbit);
						eco.animals[RABBIT][killed_index] = NULL;
					}
				}
			}
		}

		rabbit_count = 0;
		next_index = 1;

		// Normalizing the list.
		for (j = 0; j < eco.animal_count[RABBIT]; j++) {
			if (eco.animals[RABBIT][j] == NULL) {
				while (next_index < eco.animal_count[RABBIT] && eco.animals[RABBIT][next_index] == NULL) {
					next_index++;
				}

				if (next_index == eco.animal_count[RABBIT]) {
					break;
				}

				eco.animals[RABBIT][j] = eco.animals[RABBIT][next_index];
				eco.animals[RABBIT][next_index] = NULL;
				next_index++;
				rabbit_count++;
			} else {
				rabbit_count++;
				next_index = j + 2;
			}
		}

		eco.animal_count[RABBIT] = rabbit_count;
		//ecosystem_print(&eco); getchar();

		for (j = 0; j < eco.animal_count[RABBIT]; j++) {
			Rabbit *rabbit = eco.animals[RABBIT][j];
			if (rabbit->child != NULL) {
				eco.animals[RABBIT][rabbit_count] = rabbit->child;
				eco.matrix[rabbit->data.pos.y][rabbit->data.pos.x].index = rabbit_count++;
				rabbit->child = NULL;
			} else {
				eco.matrix[rabbit->data.pos.y][rabbit->data.pos.x].type = EMPTY;
				eco.matrix[rabbit->data.pos.y][rabbit->data.pos.x].index = -1;
			}

			rabbit->data.pos = rabbit->data.next_pos;
			eco.matrix[rabbit->data.pos.y][rabbit->data.pos.x].type = RABBIT;
			eco.matrix[rabbit->data.pos.y][rabbit->data.pos.x].index = j;
		}


		eco.animal_count[RABBIT] = rabbit_count;
		//eco.animals[RABBIT] = realloc(eco.animals[RABBIT], eco.animal_count[RABBIT] * sizeof *eco.animals[RABBIT]);

		/*
		for(j = 0; j < eco.animal_count[FOX]; j++){
			move_fox(&eco, j);
		}
		*/
		ecosystem_print(&eco); getchar();
	}

	return 0;
}
