#ifndef PREGUNTA_H_INCLUDED
#define PREGUNTA_H_INCLUDED
#include "respuesta.h"
struct Pregunta {
    int nroPregunta;
    char Pregunta[100];
    RespuestaPtr respPosibles[4];
};
typedef struct Pregunta * PreguntaPtr;
void cargarPregDesdeArch(PreguntaPtr preg[]);




#endif // PREGUNTA_H_INCLUDED
