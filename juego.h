#ifndef JUEGO_H_INCLUDED
#define JUEGO_H_INCLUDED
#include "jugador.h"
struct Juego {
    JugadorPtr jugadores[4];
};
typedef struct Juego * JuegoPtr;
void menuPrincipal(JuegoPtr juego);
void iniciarJuego(JuegoPtr juego);
void eliminarJugadorPorDNI(int dniAEliminar);

#endif // JUEGO_H_INCLUDED
