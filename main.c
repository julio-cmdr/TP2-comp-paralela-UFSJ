#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include "ecossistema.h"

int main(int argc, char *argv[]) {
	if (argc < 2) {
		printf("Favor passar um arquivo de entrada!\n");
		exit(1);
	}

	Ecossistema eco = init_ecossistema(argv[1]);

	for(int i = 0; i < eco.n; i++)
		objeto_print(eco.objetos[i]);

	return 0;
}
