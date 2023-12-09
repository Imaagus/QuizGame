#ifndef PUNTOS_H_INCLUDED
#define PUNTOS_H_INCLUDED
struct Puntos {
    int codPuntuacion;
    int actuales;
    int puntuacionMaxima;
};
typedef struct Puntos * PuntosPtr;
PuntosPtr reservarMemoriaPuntos();
void puntosActuales(PuntosPtr punt,int sumaPuntos);
void puntosMax(PuntosPtr punt);


#endif // PUNTOS_H_INCLUDED
