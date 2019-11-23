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

Rock *new_rock(int x, int y){
    Rock *rock = (Rock*)malloc(sizeof(Rock));
    rock->data.type = ROCK;
    rock->data.pos.x = x;
    rock->data.pos.y = y;
    
    return rock;
}

Rabbit *new_rabbit(int x, int y, int generation){
    Rabbit *rabbit = (Rabbit*)malloc(sizeof(Rabbit));
    rabbit->data.type = RABBIT;
    rabbit->data.pos.x = x;
    rabbit->data.pos.y = y;
    rabbit->generation = generation;

    return rabbit;
}

Fox *new_fox(int x, int y, int generation, int hungry){
    Fox *fox = malloc(sizeof(Fox));
    fox->data.type = FOX;
    fox->data.pos.x = x;
    fox->data.pos.y = y;
    fox->hungry = hungry;
    fox->generation = generation;

    return fox;
}