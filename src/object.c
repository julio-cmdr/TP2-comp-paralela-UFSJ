#include "object.h"
#include "ecosystem.h"

void object_print(int type, int l, int c){
    static char types[][16] = {
        "COELHO", "RAPOSA", "ROCHA"
    };
    printf("%s %d %d\n", types[type], l, c);
}

void *new_animal(int type, size_t size, int l, int c) {
    Animal *object = malloc(size);

    object->type = type;
    object->pos.l = l;
    object->pos.c = c;
    object->next_pos.l = l;
    object->next_pos.c = c;
    object->generation = 0;
    object->dead = false;

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
