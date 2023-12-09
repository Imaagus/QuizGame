#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "jugador.h"
#include "juego.h"
int cantJugadores(){
    int cantidad;
    char buffer[256];
    do{
        printf("Ingrese la cantidad de jugadores (2 a 4): ");
        if(scanf("%d", &cantidad) != 1){
            printf("Respuesta no valida. Por favor, ingrese un numero valido.\n");
            scanf("%s", buffer);
        }else if (cantidad < 2 || cantidad > 4){
            printf("Cantidad fuera del rango valido (2 a 4).\n");
        }
    }while(cantidad < 2 || cantidad > 4);
    return cantidad;
}

void cuentaRegresiva(int segundos) {
    for (int i = segundos; i > 0; i--) {
        printf("%d.. ", i);
        fflush(stdout);
        sleep(1);
    }
    printf("\n");
}
int desempate(JugadorPtr jugadores[], int numJugadores){
    srand(time(NULL));
    int numeroAleatorio= rand()%1000;
    int respuestaCorrecta= 120 + numeroAleatorio * 10;
    int jugadorMasCercano= -1;
    int diferenciaMinima= INT_MAX;
    printf("Pregunta matematica: 120 + %d * 10\n", numeroAleatorio);

    for (int i = 0; i < numJugadores; i++) {
        printf("%s, ingresa tu respuesta: ", jugadores[i]->alias);
        int respuestaJugador;
        scanf("%d", &respuestaJugador);

        int diferencia = abs(respuestaCorrecta - respuestaJugador);
        if (diferencia < diferenciaMinima) {
            diferenciaMinima = diferencia;
            jugadorMasCercano = i;
        }
    }
    jugadores[jugadorMasCercano]->puntos->actuales += 10;
    guardarJugadorArch(jugadores[jugadorMasCercano], 1);
    return jugadores[jugadorMasCercano];
}

void cargarPreguntaAleatoria(PreguntaPtr preg[],JugadorPtr jug, int t){
    jug->puntos=reservarMemoriaPuntos();
    jug->puntos->actuales=0;
    srand(time(NULL));
    int preguntasRespondidas= 0;
    int respuestaCorrecta= 1;
    int preguntasMostradas[t];

    for(int i = 0; i < t; i++){
        preguntasMostradas[i]= 0;
    }

    while(respuestaCorrecta){
        int indiceAleatorio= rand()%t;
        do{
            indiceAleatorio= rand()%t;
        }while(preguntasMostradas[indiceAleatorio]);

        preguntasMostradas[indiceAleatorio] = 1;

        PreguntaPtr pregunta= preg[indiceAleatorio];

        printf("Pregunta: %s\n", pregunta->Pregunta);

        for(int i = 0; i < 4; i++){
            printf("%d. %s\n", i + 1, pregunta->respPosibles[i]->respuesta);
        }

        printf("Tenes 15 segundos para elegir una respuesta...\n");
        clock_t tiempoInicio = clock();

        int respuestaJugador;
        int ManejoCaracter;
        //Reviso si envia un caracter o palabra para manejar el error
        do{
            printf("Elige el numero de tu respuesta: ");
            ManejoCaracter= scanf("%d", &respuestaJugador);

            if(ManejoCaracter != 1){
                guardarJugadorArch(jug, 1);
                printf("Opcion no valida. Debes ingresar un numero valido del 1 al 4.\n");
                while(getchar() != '\n'); //Limpio el bufer
            }else if(respuestaJugador < 1 || respuestaJugador > 4){
                guardarJugadorArch(jug, 1);
                printf("Opcion no valida. Debes elegir una de las opciones del 1 al 4.\n");
            }
        }while(ManejoCaracter != 1 || respuestaJugador < 1 || respuestaJugador > 4);

        //Calculo el tiempo
        clock_t tiempoTranscurrido= clock() - tiempoInicio;
        double segundosTranscurridos= ((double)tiempoTranscurrido) / CLOCKS_PER_SEC;

        if(respuestaJugador >= 1 && respuestaJugador <= 4){
            if(segundosTranscurridos >= 15.0){
                printf("Se agoto el tiempo, tardaste %.2f segundos. La respuesta era: ", segundosTranscurridos);
                for(int i = 0; i < 4; i++){
                    if(pregunta->respPosibles[i]->correcta == 1){
                        printf("%s\n", pregunta->respPosibles[i]->respuesta);
                        break;
                    }
                }
                guardarJugadorArch(jug,1);
                respuestaCorrecta = 0;
            }else{
                if(pregunta->respPosibles[respuestaJugador - 1]->correcta == 1){
                    printf("Respuesta correcta!!!\n\n");
                    if(segundosTranscurridos<10){
                    puntosActuales(jug->puntos,10);
                    }else{
                    puntosActuales(jug->puntos,5);
                    }
                    guardarJugadorArch(jug, 1);
                }else{
                    for(int i = 0; i < 4; i++){
                        if(pregunta->respPosibles[i]->correcta == 1){
                            printf("Respuesta incorrecta. La respuesta correcta era: %s\n", pregunta->respPosibles[i]->respuesta);
                            respuestaCorrecta = 0;
                            guardarJugadorArch(jug,1);
                            break;
                        }
                    }
                }
            }
        }
        //Llevo la cuenta de cuantas preguntas respondio por si llega a responder todas
        preguntasRespondidas++;
        if (preguntasRespondidas == t) {
            printf("Has respondido a todas las preguntas disponibles!!\n");
            respuestaCorrecta = 0;
        }
    }
    puntosMax(jug->puntos);
}
void jugadorGanador(JugadorPtr jugadores[], int numJugadores){
    JugadorPtr ganador = jugadores[0];

    int empate = 0;
    for(int i = 1; i < numJugadores; i++){
        if (jugadores[i]->puntos->actuales > ganador->puntos->actuales){
            ganador = jugadores[i];
            empate = 0;
        }else if(jugadores[i]->puntos->actuales == ganador->puntos->actuales){
            empate = 1;
        }
    }

    if(empate){
        printf("Hay un empate! Se realizara un desempate entre los jugadores con la maxima puntuacion.\n");
        JugadorPtr maximosPuntajes[50];
        int numMaximosPuntajes = 0;
        for (int i = 0; i < numJugadores; i++) {
            if(jugadores[i]->puntos->actuales == ganador->puntos->actuales){
                maximosPuntajes[numMaximosPuntajes] = jugadores[i];
                numMaximosPuntajes++;
            }
        }
        ganador = desempate(maximosPuntajes, numMaximosPuntajes);
        guardarJugadorArch(ganador, 1);
    }
    printf("\nEl ganador es ... %s con una puntuacion de %d.\n", ganador->alias, ganador->puntos->actuales);
}

JugadorPtr cargarJugador(PreguntaPtr preg[]){
    JugadorPtr jug=(JugadorPtr)malloc(sizeof(struct Jugador));
      do{
        printf("\n-- Cargar jugador --\n");
        printf("-- Ingrese alias de juego \n");
        fflush(stdin);
        gets(jug->alias);
            if(strlen(jug->alias) == 0){
                printf("El alias no puede quedar en blanco. Por favor, ingrese un alias valido.\n");  //Manejo de posible error
            }
        }while(strlen(jug->alias) == 0);

     do {
        printf("-- Ingrese dni\n");
        if (scanf("%d", &jug->dni) != 1 || jug->dni < 1000000 || jug->dni > 99999999) {
            printf("DNI no valido. Por favor, ingrese dni valido.\n");
            while (getchar() != '\n');
        }
    } while (jug->dni < 1000000 || jug->dni > 99999999); //Manejo de error por si envian caracteres
    system("cls");
    printf("Estas listo para jugar?\n");
    cuentaRegresiva(3);
    cargarPregDesdeArch(preg);
    cargarPreguntaAleatoria(preg,jug,25);
    system("pause");
    system("cls");
    return jug;
}

void cargarJugadores(JugadorPtr jug[],PreguntaPtr preg[],int t){
    for(int i=0;i<t;i++){
        jug[i]=cargarJugador(preg);
    }
}
void mostrarJugador(JugadorPtr jug){
    printf("\n-- Alias: %s \n",jug->alias);
    printf("-- Dni: %d \n",jug->dni);
    printf("-- Puntaje: %d\n ",jug->puntos->actuales);
}
void mostrarJugadores(JugadorPtr jug[],int t){
    for(int i=0;i<t;i++){
        mostrarJugador(jug[i]);
    }
}


void guardarJugadorArch(JugadorPtr jug, int t){
    FILE *archivo= fopen("registros.txt", "r+");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo de puntaje\n");
        return;
    }

    int dniExistente= 0;
    int puntajeActual;
    long int jugadorPosicion= -1; //Guarda la posición del jugador actual

    while(!feof(archivo)){
        long int posicionActual= ftell(archivo);
        char alias[50];
        int dni;
        fscanf(archivo, "%s %d %d\n", alias, &dni, &puntajeActual);
        if(dni == jug->dni){
            dniExistente = 1;
            jugadorPosicion = posicionActual;
            if(jug->puntos->actuales > puntajeActual){
                fseek(archivo, jugadorPosicion, SEEK_SET);
                fprintf(archivo, "%s %d %d\n", jug->alias, jug->dni, jug->puntos->actuales);
            }
            break;
        }
    }
    if(!dniExistente){
        fseek(archivo, 0, SEEK_END);
        fprintf(archivo, "%s %d %d\n", jug->alias, jug->dni, jug->puntos->actuales);
    }
    fclose(archivo);
}

void verPuntajesYJugadoresQueJugaron(JugadorPtr jugadores[]){
    FILE *archivo = fopen("registros.txt", "r");
    if(archivo == NULL){
        printf("No se pudo abrir el archivo de registros.\n");
        return;
    }
    //Reviso si el archivo esta vacio
    int caracter= fgetc(archivo);
    if(caracter == EOF){
        printf("No hay jugadores registrados en el archivo.\n");
        fclose(archivo);
        return;
    }
    ungetc(caracter, archivo);

    printf("-- Jugadores que ya jugaron y sus puntajes maximos --\n");
    int i=0;
    while(!feof(archivo)){
        jugadores[i]=(JugadorPtr)malloc(sizeof(struct Jugador));
        jugadores[i]->puntos=reservarMemoriaPuntos();
        fscanf(archivo, "%s %d %d\n", jugadores[i]->alias, &(jugadores[i]->dni), &(jugadores[i]->puntos->puntuacionMaxima));
        printf("Alias: %s, DNI: %d, Puntaje Maximo: %d\n", jugadores[i]->alias, jugadores[i]->dni, jugadores[i]->puntos->puntuacionMaxima);
        i++;
    }
    fclose(archivo);

    //Eliminar jugador del historial
    int opcion;
    printf("Desea eliminar un jugador? (1 - Si / 0 - No): ");
    scanf("%d", &opcion);

    if(opcion == 1){
        int dniAEliminar;
        char buffer[256];
        int validInput = 0; //Variable para validar la entrada y manejar posibles errores
        do{
            printf("Ingrese el DNI del jugador a eliminar: ");
            if(scanf("%d", &dniAEliminar) == 1){
                validInput = 1; //La entrada es válida
            }else if(dniAEliminar < 1000000 || dniAEliminar > 99999999){
                printf("Dni invalido\n");
                scanf("%s", buffer); //Limpia el búfer
            }
        }while(!validInput || dniAEliminar <= 0);
    eliminarJugadorPorDNI(dniAEliminar);
    }
}

