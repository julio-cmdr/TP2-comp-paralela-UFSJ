#include "object.h"
#include "ecosystem.h"

void object_print(void *obj){
    if(TYPEOF(obj) == RABBIT){
        Rabbit *rabbit = obj;
        printf("Rabbit pos (%d, %d) generation: %d\n", rabbit->data.pos.l, rabbit->data.pos.c, rabbit->data.generation);
    }else if(TYPEOF(obj) == FOX){
        Fox *fox = obj;
        printf("Fox    pos (%d, %d) generation: %d hungry: %d\n", fox->data.pos.l, fox->data.pos.c, fox->data.generation, fox->hungry);
    }
}

void *new_animal(int type, size_t size, int l, int c) {
    Animal *object = malloc(size);

    object->type = type;
    object->pos.l = l;
    object->pos.c = c;
    object->next_pos.l = l;
    object->next_pos.c = c;
    object->generation = 0;

    return object;
}

void *new_rabbit(int l, int c){
    Rabbit *rabbit = new_animal(RABBIT, sizeof(Rabbit), l, c);
    rabbit->data.child = NULL;

    return rabbit;
}

void *new_fox(int l, int c){
    Fox *fox = new_animal(FOX, sizeof(Fox), l, c);
    fox->hungry = 0;
    fox->data.child = NULL;

    return fox;
}
