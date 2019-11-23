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

	Ecosystem eco = ecosystem_init(argv[1]);

	for(int i = 0; i < eco.n; i++)
		object_print(eco.objects[i]);

	printf("\n");
	for(int i = 0; i < eco.l; i++){
		for(int j = 0; j < eco.c; j++){
			if(eco.matrix[i][j] != NULL){
				printf("%d ", ((Common_data*)(eco.matrix[i][j]))->type);
			}else{
				printf("- ");
			}
		}
		printf("\n");
	}

	return 0;
}
