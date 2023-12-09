#include <stdio.h>
#include <stdlib.h>
#include "juego.h"
#include "jugador.h"

void menuPrincipal(JuegoPtr juego) {
    juego=(JuegoPtr)malloc(sizeof(struct Juego));
    JugadorPtr jugHistoricos[10000];
    int opcion;

    char buffer[256];

    do{
        printf("\n------- Menu Principal de Locos por el futbol -------\n");
        printf("1. Jugar\n");
        printf("2. Ver puntajes y jugadores que ya jugaron\n");
        printf("3. Salir\n");
        printf("Seleccione una opcion: ");
        //Manejo de error por si ingresan caracteres o signos
        if(scanf("%d", &opcion) != 1){
            printf("\nOpcion no valida. Por favor, ingrese un numero valido.\n");
            scanf("%s", buffer);
        }else{
            switch(opcion){
                case 1:
                    iniciarJuego(juego);
                    break;
                case 2:
                    verPuntajesYJugadoresQueJugaron(jugHistoricos);
                    break;
                case 3:
                    printf("Saliendo del juego.\n");
                    break;
                default:
                    printf("Opcion no valida. Seleccione una opcion valida.\n");
                    break;
            }
        }
    }while(opcion != 3);
}

void iniciarJuego(JuegoPtr juego){
    system("cls");
    printf("\n                                  !!!BIENVENIDOS A LOCOS POR EL FUTBOL!!! \n\n");
    printf("Reglas a tener en cuenta para poder disfrutar de tu partida:\n");
    printf("\n--> Tenes 15 segundos para responder cada pregunta, si te pasas del tiempo perdes!!\n");
    printf("\n--> Cada jugador va responder las preguntas hasta que se equivoque y le toque al siguiente.\n");
    printf("\n--> Cada respuesta correcta vale 10 puntos, en caso de tardar mas de 10 segundos la respuesta valdra 5 puntos.\n");
    printf("\n--> En caso de empate habra una pregunta matematica para desempatar\n\n");
    printf("Ahora que ya conoces las reglas vamos a jugar!!! ");
    system("pause");
    system("cls");

    int cant=cantJugadores();
    PreguntaPtr preg[25];
    JugadorPtr jug[cant];
    system("pause");


    system("cls");
    printf("\n                                     Llego la hora de que empezemos!!!\n");
    cargarJugadores(jug,preg,cant);
    printf("Ya han jugado todos... ");
    system("pause");
    system("cls");
    jugadorGanador(jug,cant);
    system("pause");
    system("cls");
    printf("\nFin del juego, espero que lo hayan disfrutado!!!\n");
    mostrarJugadores(jug,cant);

}
void eliminarJugadorPorDNI(int dniAEliminar){
    FILE *archivo= fopen("registros.txt", "r");
    if(archivo == NULL){
        printf("No se pudo abrir el archivo de registros.\n");
        return;
    }
    //Creo registro temporal para guardar
    FILE *archivoTemp= fopen("registros_temp.txt", "w");
    if(archivoTemp == NULL){
        printf("No se pudo abrir el archivo temporal.\n");
        fclose(archivo);
        return;
    }

    int encontrado= 0;
    char alias[50];
    int dni;
    int puntuacionMaxima;

    while(!feof(archivo)){
        if(fscanf(archivo,"%s %d %d\n", alias, &dni, &puntuacionMaxima)!= 3){
            break;
        }
        if(dni == dniAEliminar){
            encontrado = 1;
        }else{
            fprintf(archivoTemp,"%s %d %d\n", alias, dni, puntuacionMaxima);
        }
    }
    fclose(archivo);
    fclose(archivoTemp);
    //Elimino el archivo y reescribo el temporal
    if(encontrado){
        remove("registros.txt");
        rename("registros_temp.txt", "registros.txt");
        printf("Jugador con DNI %d eliminado exitosamente.\n", dniAEliminar);
    }else{
        remove("registros_temp.txt");
        printf("No se encontro un jugador con DNI %d.\n", dniAEliminar);
    }
}

