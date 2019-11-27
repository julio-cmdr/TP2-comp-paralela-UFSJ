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
#include <stdbool.h>
#include "object.h"

typedef struct ecosystem {
	int gen_proc_rabbits;
	int gen_proc_fox;
	int gen_food_fox;
	int n_gen;
	int l, c;
	int n;
	int animal_count[2];
	void **animals[2];
	Object **matrix;
}Ecosystem;

Ecosystem ecosystem_init(char *file);

bool cell_has_object(const Ecosystem *eco, int x, int y, int type);

bool get_next_cell(const Ecosystem *eco, int obj_type, int obj_index, Position *pos, int cell_type);

void move_rabbit(Ecosystem *eco, int index);

void move_fox(Ecosystem *eco, int index);

#endif // ECOSYSTEM_H
