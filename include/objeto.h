/**
 * TP2-comp-paralela-UFSJ
 *
 * objeto.c
 *
 * Júlio Resende - julio.cmdr@gmail.com
 * Paulo Tobias - paulohtobias@outlook.com
 *
 */

#ifndef OBJETO_H
#define OBJETO_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

enum {
	COELHO = 0,
	RAPOSA = 1,
	ROCHA = 2,
};

typedef struct obj {
	int x, y;
	int idade_proc;
	int fome;
	int tipo;
} Objeto;

void objeto_print(Objeto obj);

#endif // OBJETO_H
