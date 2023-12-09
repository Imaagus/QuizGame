#ifndef JUGADOR_H_INCLUDED
#define JUGADOR_H_INCLUDED
#include "pregunta.h"
#include "puntos.h"
struct Jugador {
    char alias[20];
    int dni;
    PreguntaPtr preguntasJuego [25];
    PuntosPtr puntos;
};
typedef struct Jugador * JugadorPtr;

int cantJugadores();
void cargarPreguntaAleatoria(PreguntaPtr preg[],JugadorPtr jug,int t);
void cuentaRegresiva(int segundos);
void jugadorGanador(JugadorPtr jugadores[], int numJugadores);
int desempate(JugadorPtr jugadores[], int numJugadores);
JugadorPtr cargarJugador(PreguntaPtr preg[]);
void cargarJugadores(JugadorPtr jug[],PreguntaPtr preg[],int t);
void mostrarJugador(JugadorPtr jug);
void mostrarJugadores(JugadorPtr jug[],int t);
void guardarJugadorArch(JugadorPtr jug,int t);
void verPuntajesYJugadoresQueJugaron(JugadorPtr jugadores[]);

#endif // JUGADOR_H_INCLUDED
