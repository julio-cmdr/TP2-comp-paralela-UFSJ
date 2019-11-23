/**
 * TP2-comp-paralela-UFSJ
 *
 * object.c
 *
 * Júlio Resende - julio.cmdr@gmail.com
 * Paulo Tobias - paulohtobias@outlook.com
 *
 */

#ifndef OBJECT_H
#define OBJECT_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

enum {
	EMPTY = -1,
	RABBIT,
	FOX,
	ROCK,
};

typedef struct position{
	int x, y;
} Position;

typedef struct common_data{
	Position pos;
	int type;
} Common_data;

typedef struct rock{
	Common_data data;
}Rock;

typedef struct fox{
	Common_data data;
	int hungry;
	int generation;
}Fox;

typedef struct rabbit{
	Common_data data;
	int generation;
}Rabbit;

#define TYPEOF(a) ((Common_data*)(a))->type

void object_print(void *obj);

Rock *new_rock(int x, int y);

Rabbit *new_rabbit(int x, int y, int generation);

Fox *new_fox(int x, int y, int generation, int hungry);

#endif // OBJECT_H
