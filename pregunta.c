#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "respuesta.h"
#include "pregunta.h"

void cargarPregDesdeArch(PreguntaPtr preg[]){
    FILE* archivoPreguntas = fopen("preguntas.txt", "r");
    FILE* archivoRespuestas = fopen("respuestas.txt", "r");

    if(archivoPreguntas == NULL || archivoRespuestas == NULL){
        printf("No se pudo abrir uno de los archivos\n");
        return;
    }
    int pos = 0;
    while(!feof(archivoPreguntas) && !feof(archivoRespuestas)){
        preg[pos]= (PreguntaPtr)malloc(sizeof(struct Pregunta));
        fscanf(archivoPreguntas, "%d- %[^\n]\n", &(preg[pos]->nroPregunta), preg[pos]->Pregunta);
        for (int i = 0; i < 4; i++){
            preg[pos]->respPosibles[i] = (RespuestaPtr)malloc(sizeof(struct Respuesta));
            fscanf(archivoRespuestas, "%d-%[^-]-%d-%d\n", &(preg[pos]->respPosibles[i]->nroRespuesta), preg[pos]->respPosibles[i]->respuesta, &(preg[pos]->respPosibles[i]->nroPreg), &(preg[pos]->respPosibles[i]->correcta));
        }
        pos++;
    }
    fclose(archivoPreguntas);
    fclose(archivoRespuestas);
}


