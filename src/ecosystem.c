#include "ecosystem.h"

Ecosystem ecosystem_init(char *file) {
	Ecosystem eco;

	FILE *arq;
	arq = fopen(file, "r");

	eco.animal_count[0] = eco.animal_count[1] = 0;

	if (arq == NULL) {
		perror("Erro ao abrir o arquivo!\n");
		exit(1);
	} else {
		fscanf(arq, "%d %d %d %d %d %d %d\n", &eco.gen_proc_rabbits, &eco.gen_proc_fox, &eco.gen_food_fox, &eco.n_gen, &eco.l, &eco.c, &eco.n);

		eco.matrix = malloc(eco.l * sizeof *eco.matrix);
		for (int i = 0; i < eco.l; i++) {
			eco.matrix[i] = malloc(eco.c * sizeof *eco.matrix[i]);

			for (int j = 0; j < eco.c; j++) {
				eco.matrix[i][j].type = EMPTY;
				eco.matrix[i][j].index = -1;
			}
		}

		eco.animals[RABBIT] = malloc(eco.l * eco.c * sizeof *eco.animals[RABBIT]);
		eco.animals[FOX] = malloc(eco.l * eco.c * sizeof *eco.animals[FOX]);

		char type[7];
		int x, y;
		void *(*constructors[2])(int, int) = {
			new_rabbit, new_fox
		};

		for (int i = 0; i < eco.n; i++) {
			fscanf(arq,"%s %d %d\n", type, &x, &y);

			if(strcmp(type, "ROCHA") == 0){
				eco.matrix[x][y].type = ROCK;
				eco.matrix[x][y].index = -1;
			} else {
				int animal_id = (type[0] % 2 == 0);
				eco.animals[animal_id][eco.animal_count[animal_id]] = constructors[animal_id](x, y);
				eco.matrix[x][y].index = eco.animal_count[animal_id];
				eco.matrix[x][y].type = animal_id;
				eco.animal_count[animal_id]++;
			}
		}
		fclose(arq);
	}
	return eco;
}

bool cell_has_object(const Ecosystem *eco, int x, int y, int type) {
	if (x < 0 || x >= eco->c || y < 0 || y >= eco->l) {
		return false;
	}

	return eco->matrix[y][x].type == type;
}

bool get_next_cell(const Ecosystem *eco, int obj_type, int obj_index, int cell_type) {
    Animal *animal = eco->animals[obj_type][obj_index];
    int x = animal->pos.x;
    int y = animal->pos.y;

    Position adj[4];

    int x2, y2, p = 0;
    for(int i = 0; i < 4; i++){
		x2 = (i % 2) * (2 - i);
		y2 = !(i % 2) * (i - 1);
		if (cell_has_object(eco, x + x2, y + y2, cell_type)) {
			adj[p].x = x + x2;
			adj[p].y = y + y2;
			p++;
		}
    }

	if(p > 0){
		// fórmula para escolha da próxima célula
		animal->next_pos = adj[(eco->n_gen + x + y) % p];
		return true;
	}

	return false;
}

void move_rabbit(Ecosystem *eco, int index){
	Rabbit *rabbit = eco->animals[RABBIT][index];

	if (get_next_cell(eco, RABBIT, index, EMPTY)){
		if(rabbit->data.generation == eco->gen_proc_rabbits){
			rabbit->child = new_rabbit(rabbit->data.pos.x, rabbit->data.pos.y);
			rabbit->data.generation = -1;
		}
	}

	rabbit->data.generation++;
}

void move_fox(Ecosystem *eco, int index){
	Fox *fox = eco->animals[FOX][index];

	bool moved = get_next_cell(eco, FOX, index, RABBIT);

	if (!moved) {
		// Killing the fox.
		if (fox->hungry == eco->gen_food_fox) {
			KILL(fox->data);

			return;
		} else {
			// Tries to go to an empty cell.
			moved = get_next_cell(eco, FOX, index, EMPTY);
		}
	}

	if (moved) {
		if(fox->data.generation == eco->gen_proc_fox) {
			fox->child = new_fox(fox->data.pos.x, fox->data.pos.y);
			fox->data.generation = -1;
		}
	}
	fox->data.generation++;
}

void ecosystem_print(const Ecosystem *eco) {
	for(int i = 0; i < eco->l; i++){
		for(int j = 0; j < eco->c; j++){
			if(eco->matrix[i][j].type != EMPTY){
				printf("%d ", eco->matrix[i][j].type);
			}else{
				printf("- ");
			}
		}
		printf("\n");
	}
}
