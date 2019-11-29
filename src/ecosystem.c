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
		int l, c;
		void *(*constructors[2])(int, int) = {
			new_rabbit, new_fox
		};

		for (int i = 0; i < eco.n; i++) {
			fscanf(arq,"%s %d %d\n", type, &l, &c);

			if(strcmp(type, "ROCHA") == 0){
				eco.matrix[l][c].type = ROCK;
				eco.matrix[l][c].index = -1;
			} else {
				int animal_id = (type[0] % 2 == 0);
				eco.animals[animal_id][eco.animal_count[animal_id]] = constructors[animal_id](l, c);
				eco.matrix[l][c].index = eco.animal_count[animal_id];
				eco.matrix[l][c].type = animal_id;
				eco.animal_count[animal_id]++;
			}
		}
		fclose(arq);
	}
	return eco;
}

bool cell_has_object(const Ecosystem *eco, int l, int c, int type) {
	if (l < 0 || l >= eco->l || c < 0 || c >= eco->c) {
		return false;
	}

	return eco->matrix[l][c].type == type;
}

bool get_next_cell(const Ecosystem *eco, int obj_type, int obj_index, int cell_type) {
    Animal *animal = eco->animals[obj_type][obj_index];
    int l = animal->pos.l;
    int c = animal->pos.c;

    Position adj[4];

    int lo, co, p = 0;
    for(int i = 0; i < 4; i++){
		/* * * * * * * * * *
		 *      offsets    *
		 *       l |  c    *
		 *   0: -1 |  0    *
		 *   1:  0 |  1    *
		 *   2:  1 |  0    *
		 *   3:  0 | -1    *
		 * * * * * * * * * */
		lo = !(i & 1) * (i - 1);
		co = (i & 1) * (2 - i);

		if (cell_has_object(eco, l + lo, c + co, cell_type)) {
			adj[p].l = l + lo;
			adj[p].c = c + co;
			p++;
		}
    }

	if(p > 0){
		// fórmula para escolha da próxima célula
		animal->next_pos = adj[(eco->n_gen + l + c) % p];
		return true;
	}

	return false;
}

void move_rabbit(Ecosystem *eco, int index){
	Rabbit *rabbit = eco->animals[RABBIT][index];

	if (get_next_cell(eco, RABBIT, index, EMPTY)){
		if(rabbit->data.generation == eco->gen_proc_rabbits){
			rabbit->data.child = new_rabbit(rabbit->data.pos.l, rabbit->data.pos.c);
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
			fox->data.child = new_fox(fox->data.pos.l, fox->data.pos.c);
			fox->data.generation = -1;
		}
	}
	fox->data.generation++;
}

void ecosystem_resolve_conflicts(Ecosystem *eco, int animal1_index, int type1, int type2) {
	Animal *animal1 = eco->animals[type1][animal1_index];

	if (animal1 != NULL) {
		int d = type1 == type2 ? 0 : (type1 == RABBIT ? -1 : 1);

		for (int animal2_index = 0; animal2_index < eco->animal_count[type2]; animal2_index++) {
			Animal *animal2 = eco->animals[type2][animal2_index];

			if (
				animal1_index != animal2_index && animal2 != NULL &&
				animal1->next_pos.l == animal2->next_pos.l &&
				animal1->next_pos.c == animal2->next_pos.c
			) {
				int killed_index;
				int killed_type;
				if (d > 0) {
					killed_type = type2;
					killed_index = animal2_index;
				} else if (d < 0) {
					killed_type = type1;
					killed_index = animal1_index;
				} else {
					if (animal1->generation < animal2->generation) {
						killed_type = type1;
						killed_index = animal1_index;
					} else {
						killed_type = type2;
						killed_index = animal2_index;
					}
					killed_index = animal1->generation < animal2->generation ? animal1_index : animal2_index;
				}

				Animal *killed_animal = eco->animals[killed_type][killed_index];
				eco->matrix[killed_animal->pos.l][killed_animal->pos.c].index = -1;
				eco->matrix[killed_animal->pos.l][killed_animal->pos.c].type = EMPTY;

				free(killed_animal);
				eco->animals[RABBIT][killed_index] = NULL;
			}
		}
	}
}

int ecosystem_normalize(Ecosystem *eco, int type) {
	int animal_count = 0;
	int next_index = 1;
	for (int i = 0; i < eco->animal_count[type]; i++) {
		if (eco->animals[type][i] == NULL) {
			while (next_index < eco->animal_count[type] && eco->animals[type][next_index] == NULL) {
				next_index++;
			}

			if (next_index == eco->animal_count[type]) {
				break;
			}

			eco->animals[type][i] = eco->animals[type][next_index];
			eco->animals[type][next_index] = NULL;
			next_index++;
			animal_count++;
		} else {
			animal_count++;
			next_index = i + 2;
		}
	}

	return animal_count;
}

int ecosystem_update_position(Ecosystem *eco, int animal_index, int type) {
	int animal_count = eco->animal_count[type];
	Animal *animal = eco->animals[RABBIT][animal_index];
	if (animal->child != NULL) {
		eco->animals[RABBIT][animal_count] = animal->child;
		eco->matrix[animal->pos.l][animal->pos.c].index = animal_count++;
		animal->child = NULL;
	} else {
		eco->matrix[animal->pos.l][animal->pos.c].type = EMPTY;
		eco->matrix[animal->pos.l][animal->pos.c].index = -1;
	}

	animal->pos = animal->next_pos;
	eco->matrix[animal->pos.l][animal->pos.c].type = RABBIT;
	eco->matrix[animal->pos.l][animal->pos.c].index = animal_index;

	return animal_count;
}

void ecosystem_print(const Ecosystem *eco, int current_gen) {
	system("clear");
	printf("Gen %d\n", current_gen);

	for(int i = 0; i < eco->c * 2 + 2; i++) {
		putchar('-');
	}
	putchar('\n');


	for(int i = 0; i < eco->l; i++){
		putchar('|');
		for(int j = 0; j < eco->c; j++){
			if(eco->matrix[i][j].type != EMPTY){
				printf("%d ", eco->matrix[i][j].type);
			}else{
				printf("- ");
			}
		}
		printf("|\n");
	}

	for(int i = 0; i < eco->c * 2 + 2; i++) {
		putchar('-');
	}
	putchar('\n');

	getchar();
}
