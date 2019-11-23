#include "ecosystem.h"

Ecosystem ecosystem_init(char *file) {
	Ecosystem eco;

	FILE *arq;
	arq = fopen(file, "r");

	if (arq == NULL) {
		perror("Erro ao abrir o arquivo!\n");
		exit(1);
	} else {
		fscanf(arq, "%d %d %d %d %d %d %d\n", &eco.gen_proc_rabbits, &eco.gen_proc_fox, &eco.gen_comida_fox, &eco.n_gen, &eco.l, &eco.c, &eco.n);

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
				eco.objects[i] = (void*)new_rabbit(x, y, 0);

			}else{
				eco.objects[i] = (void*)new_fox(x, y, 0, 0);
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

static int f(int x){  // x
	return (x % 2) * (2 - x);
}

static int g(int y){  // y
	return !(y % 2) * (y - 1);
}

Position get_next_cell(const Ecosystem *eco, int obj_index, int cell_type) {	
	void *obj = eco->objects[obj_index];

    Position *pos = obj;
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

	int chosen_p = (eco->n_gen*p + x + y)%p;

	return adj[chosen_p];
}
