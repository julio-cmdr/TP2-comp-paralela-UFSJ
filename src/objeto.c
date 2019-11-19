#include "objeto.h"

void objeto_print(Objeto obj){
    printf("Tipo %d; pos (%d, %d); idade_proc: %d fome: %d\n", obj.tipo, obj.x, obj.y, obj.idade_proc, obj.fome);
}