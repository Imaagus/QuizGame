#ifndef RESPUESTA_H_INCLUDED
#define RESPUESTA_H_INCLUDED
struct Respuesta {
    int nroRespuesta;
    char respuesta[100];
    int nroPreg; //para asociarla a la pregunta
    int correcta; //0 o 1
};
typedef struct Respuesta * RespuestaPtr;

#endif // RESPUESTA_H_INCLUDED
