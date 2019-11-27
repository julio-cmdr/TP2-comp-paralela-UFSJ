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
	for(int i = 0; i < eco.l; i++){
		for(int j = 0; j < eco.c; j++){
			if(eco.matrix[i][j].type != EMPTY){
				printf("%d ", eco.matrix[i][j].type);
			}else{
				printf("- ");
			}
		}
		printf("\n");
	}

	for(i = 0; i < eco.n_gen; i++){

		for(j = 0; j < eco.animal_count[RABBIT]; j++){
			move_rabbit(&eco, j);
		}

		// TODO: sincronizar

		for(j = 0; j < eco.animal_count[FOX]; j++){
			move_fox(&eco, j);
		}
	}

	return 0;
}
