#include "ecosystem.h"

Ecosystem ecosystem_init(char *file) {
	Ecosystem eco;

	FILE *arq;
	arq = fopen(file, "r");

	if (arq == NULL) {
		perror("Erro ao abrir o arquivo!\n");
		exit(1);
	} else {
		fscanf(arq, "%d %d %d %d %d %d %d\n", &eco.gen_proc_rabbits, &eco.gen_proc_fox, &eco.gen_food_fox, &eco.n_gen, &eco.l, &eco.c, &eco.n);

		eco.matrix = (void***) malloc(eco.l * sizeof(void**));
		for (int i = 0; i < eco.l; i++) {
			eco.matrix[i] = (void**) malloc(eco.c * sizeof(void*));

			for (int j = 0; j < eco.c; j++) {
				eco.matrix[i][j] = NULL;
			}
		}

		eco.objects = (void**) malloc(eco.l * eco.c * sizeof(void*));

		char tipo[7];
		int x, y;
		for (int i = 0; i < eco.n; i++) {
			fscanf(arq,"%s %d %d\n", tipo, &x, &y);

			// imagino que tenha forma mais elegante de fazer isso:
			if(strcmp(tipo, "ROCHA") == 0){
				eco.objects[i] = (void*)new_rock(x, y);

			}else if(strcmp(tipo, "COELHO") == 0){
				eco.objects[i] = (void*)new_rabbit(x, y);

			}else{
				eco.objects[i] = (void*)new_fox(x, y);
			}

			eco.matrix[x][y] = eco.objects[i];
		}
		fclose(arq);
	}
	return eco;
}

bool cell_has_object(const Ecosystem *eco, int x, int y, int type) {
	if (x < 0 || x >= eco->c || y < 0 || y >= eco->l) {
		return false;
	}

	if(type == EMPTY) {
		return eco->matrix[x][y] == NULL;
	}
		
	return TYPEOF(eco->matrix[x][y]) == type;
}

bool get_next_cell(const Ecosystem *eco, int obj_index, Position *pos, int cell_type) {	
	int f(int x){  // x
		return (x % 2) * (2 - x);
	}

	int g(int y){  // y
		return !(y % 2) * (y - 1);
	}

    pos = eco->objects[obj_index];
    int x = pos->x;
    int y = pos->y;
    
    Position adj[4];

    int x2, y2, p = 0;
    for(int i = 0; i < 4; i++){
		x2 = f(x);
		y2 = g(y);
		if (!cell_has_object(eco, x + x2, y + y2, cell_type)){    
			adj[p].x = x + x2;
			adj[p].y = y + y2;
			p++;
		}
    }
	
	if(p > 0){
		pos = &adj[(eco->n_gen*p + x + y)%p];
		return true;
	}
	
	return false;
}

void move_rabbit(Ecosystem *eco, int index){
	Position next_pos;
	Rabbit *rabbit = eco->objects[index];

	if (get_next_cell(eco, index, &next_pos, EMPTY)){
		if(rabbit->generation == eco->gen_proc_rabbits){
			Rabbit *child_rabbit = new_rabbit(rabbit->data.pos.x, rabbit->data.pos.y);
			rabbit->generation = -1;
		}
		rabbit->data.pos = next_pos;
	}
	
	rabbit->generation++;

	// ADICIONAR/RETORNAR O FILHO
}

void move_fox(Ecosystem *eco, int index){
	Fox *fox = eco->objects[index];

	Position next_pos;
	bool moved = get_next_cell(eco, index, &next_pos, RABBIT);

	if (!moved) {
		// Killing the fox.
		if (fox->hungry == eco->gen_food_fox) {
			KILL(fox->data);

			return;
		} else {
			// Tries to go to an empty cell.
			moved = get_next_cell(eco, index, &next_pos, EMPTY);
		}
	}
	
	if (moved) {
		if(fox->generation == eco->gen_proc_fox) {
			Fox *child_fox = new_fox(fox->data.pos.x, fox->data.pos.y);
			fox->generation = -1;
		}
		fox->data.pos = next_pos;
	}
	fox->generation++;

	// ADICIONAR/RETORNAR O FILHO
}
