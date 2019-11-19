/**
 * TP2-comp-paralela-UFSJ
 *
 * ecossistema.c
 *
 * Júlio Resende - julio.cmdr@gmail.com
 * Paulo Tobias - paulohtobias@outlook.com
 *
 */

#ifndef ECOSSISTEMA_H
#define ECOSSISTEMA_H

#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "objeto.h"

typedef struct eco {
	int gen_proc_coelhos;
	int gen_proc_raposas;
	int gen_comida_raposas;
	int n_gen;
	int l, c;
	int n;
	Objeto *objetos;
} Ecossistema;

Ecossistema init_ecossistema(char *file);

#endif // ECOSSISTEMA_H
