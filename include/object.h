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

typedef struct animal{
	Position pos;
	int type;
	int generation;
} Animal;

typedef struct fox{
	Animal data;
	struct fox *child;
	int hungry;
}Fox;

typedef struct rabbit{
	Animal data;
	struct rabbit *child;
}Rabbit;

typedef struct object {
	int type;
	int index;
} Object;

#define TYPEOF(a) ((Animal*)(a))->type

#define KILL(o) ((o).pos.x = -1, (o).pos.y = -1)

void object_print(void *obj);

void *new_rabbit(int x, int y);

void *new_fox(int x, int y);

#endif // OBJECT_H
