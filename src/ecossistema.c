#include "ecossistema.h"

Ecossistema init_ecossistema(char *file) {
	Ecossistema eco;

	FILE *arq;
	arq = fopen(file, "r");

	if (arq == NULL) {
		perror("Erro ao abrir o arquivo!\n");
		exit(1);
	} else {
		fscanf(arq, "%d %d %d %d %d %d %d\n", &eco.gen_proc_coelhos, &eco.gen_proc_raposas, &eco.gen_comida_raposas, &eco.n_gen, &eco.l, &eco.c, &eco.n);

		eco.objetos = (Objeto*) malloc(eco.n * sizeof(Objeto));

        char tipo[7];
		for (int i = 0; i < eco.n; i++) {
			fscanf(arq,"%s %d %d\n", tipo, &eco.objetos[i].x, &eco.objetos[i].y);
            eco.objetos[i].fome = eco.objetos[i].idade_proc = 0;
            
            // imagino que tenha forma mais elegante de fazer isso:
            if(strcmp(tipo, "ROCHA") == 0){
                eco.objetos[i].tipo = ROCHA;
            }else if(strcmp(tipo, "COELHO") == 0){
                eco.objetos[i].tipo = COELHO;
            }else{
                eco.objetos[i].tipo = RAPOSA;
            }
		}
		fclose(arq);
	}
	return eco;
}
