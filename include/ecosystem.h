/**
 * TP2-comp-paralela-UFSJ
 *
 * ecosystem.c
 *
 * Júlio Resende - julio.cmdr@gmail.com
 * Paulo Tobias - paulohtobias@outlook.com
 *
 */

#ifndef ECOSYSTEM_H
#define ECOSYSTEM_H

#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "object.h"

typedef struct ecosystem {
	int gen_proc_rabbits;
	int gen_proc_fox;
	int gen_comida_fox;
	int n_gen;
	int l, c;
	int n;
	void **objects;
	void ***matrix;
}Ecosystem;

Ecosystem ecosystem_init(char *file);

#endif // ECOSYSTEM_H
