#include "object.h"
#include "ecosystem.h"

void object_print(void *obj){
    if(TYPEOF(obj) == RABBIT){
        Rabbit *rabbit = obj;
        printf("Rabbit pos (%d, %d) generation: %d\n", rabbit->data.pos.x, rabbit->data.pos.y, rabbit->data.generation);
    }else if(TYPEOF(obj) == FOX){
        Fox *fox = obj;
        printf("Fox    pos (%d, %d) generation: %d hungry: %d\n", fox->data.pos.x, fox->data.pos.y, fox->data.generation, fox->hungry);
    }
}

void *new_animal(int type, size_t size, int x, int y) {
    Animal *object = malloc(size);

    object->type = type;
    object->pos.x = x;
    object->pos.y = y;
    object->next_pos.x = x;
    object->next_pos.y = y;
    object->generation = 0;

    return object;
}

void *new_rabbit(int x, int y){
    Rabbit *rabbit = new_animal(RABBIT, sizeof(Rabbit), x, y);
    rabbit->child = NULL;

    return rabbit;
}

void *new_fox(int x, int y){
    Fox *fox = new_animal(FOX, sizeof(Fox), x, y);
    fox->hungry = 0;
    fox->child = NULL;

    return fox;
}
