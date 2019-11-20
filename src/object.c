#include "object.h"

void object_print(void *obj){
    if(TYPEOF(obj) == RABBIT){
        Rabbit *rabbit = (Rabbit*)obj;
        printf("Rabbit pos (%d, %d) generation: %d\n", rabbit->data.x, rabbit->data.y, rabbit->generation);
    }else if(TYPEOF(obj) == FOX){
        Fox *fox = (Fox*)obj;
        printf("Fox    pos (%d, %d) generation: %d hungry: %d\n", fox->data.x, fox->data.y, fox->generation, fox->hungry);
    }else{
        Rock *rock = (Rock*)obj;
        printf("Rock   pos (%d, %d)\n", rock->data.x, rock->data.y);
    }
}

Rock *new_rock(int x, int y){
    Rock *rock = (Rock*)malloc(sizeof(Rock));
    rock->data.type = ROCK;
    rock->data.x = x;
    rock->data.y = y;
    
    return rock;
}

Rabbit *new_rabbit(int x, int y, int generation){
    Rabbit *rabbit = (Rabbit*)malloc(sizeof(Rabbit));
    rabbit->data.type = RABBIT;
    rabbit->data.x = x;
    rabbit->data.y = y;
    rabbit->generation = generation;

    return rabbit;
}

Fox *new_fox(int x, int y, int generation, int hungry){
    Fox *fox = malloc(sizeof(Fox));
    fox->data.type = FOX;
    fox->data.x = x;
    fox->data.y = y;
    fox->hungry = hungry;
    fox->generation = generation;

    return fox;
}