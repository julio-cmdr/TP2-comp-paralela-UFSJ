#include "object.h"
#include "ecosystem.h"

void object_print(void *obj){
    if(TYPEOF(obj) == RABBIT){
        Rabbit *rabbit = (Rabbit*)obj;
        printf("Rabbit pos (%d, %d) generation: %d\n", rabbit->data.pos.x, rabbit->data.pos.y, rabbit->generation);
    }else if(TYPEOF(obj) == FOX){
        Fox *fox = (Fox*)obj;
        printf("Fox    pos (%d, %d) generation: %d hungry: %d\n", fox->data.pos.x, fox->data.pos.y, fox->generation, fox->hungry);
    }else{
        Rock *rock = (Rock*)obj;
        printf("Rock   pos (%d, %d)\n", rock->data.pos.x, rock->data.pos.y);
    }
}

void *new_object(int type, size_t size, int x, int y) {
    Common_data *object = malloc(size);

    object->type = type;
    object->pos.x = x;
    object->pos.y = y;

    return object;
}

Rock *new_rock(int x, int y){
    Rock *rock = new_object(ROCK, sizeof(Rock), x, y);
    
    return rock;
}

Rabbit *new_rabbit(int x, int y){
    Rabbit *rabbit = new_object(RABBIT, sizeof(Rabbit), x, y);
    rabbit->generation = 0;

    return rabbit;
}

Fox *new_fox(int x, int y){
    Fox *fox = new_object(FOX, sizeof(Fox), x, y);
    fox->hungry = 0;
    fox->generation = 0;

    return fox;
}