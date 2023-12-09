#include <stdio.h>
#include <stdlib.h>
#include "puntos.h"

PuntosPtr reservarMemoriaPuntos(){
    PuntosPtr puntos=(PuntosPtr)malloc(sizeof(struct Puntos));
    return puntos;
}
void puntosActuales(PuntosPtr punt,int sumaPuntos){
    punt->actuales+= sumaPuntos;
}
void puntosMax(PuntosPtr punt) {
    if (punt->actuales > punt->puntuacionMaxima) {
        punt->puntuacionMaxima = punt->actuales;
    }
}
