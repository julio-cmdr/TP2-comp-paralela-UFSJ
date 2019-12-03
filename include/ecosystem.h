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
	int current_gen;
	int n_gen;
	int l, c;
	int n;
	int rock_count;
	int animal_count[2];
	void **animals[2];
	Object **matrix;
}Ecosystem;

Ecosystem ecosystem_init(char *file);

bool cell_has_object(const Ecosystem *eco, int l, int c, int type);

bool get_next_cell(const Ecosystem *eco, int obj_type, int obj_index, int cell_type);

void move_rabbit(Ecosystem *eco, int index);

void move_fox(Ecosystem *eco, int index);

void ecosystem_resolve_conflicts(Ecosystem *eco, int animal1_index, int type1, int type2);

void ecosystem_normalize(Ecosystem *eco, int type);

void ecosystem_update_position(Ecosystem *eco, int animal_index, int type);

void ecosystem_print(const Ecosystem *eco);

#endif // ECOSYSTEM_H
