#include <stdio.h>
#include <stdbool.h>
#include <omp.h>
#include <stdlib.h>
#include <unistd.h>
#include <windows.h>  
#include <time.h>

void gotoxy(int x, int y) {
    HANDLE hcon;
    hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hcon, dwPos);
}

struct consumidor {
    bool estado;
    int consumoActual;
};

struct productor {
    bool estado;
    int produccionActual;
};

int producido = 0, consumido = 0;
int vectorProduccion[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

struct consumidor consumidor;
struct productor productor;

int randomsc(int rango) { // SINCERO
    return 1 + rand() % rango;
}

int randomcc(int rango) { // CONCERO
    return rand() % rango;
}

void imprimirPantalla() {
    gotoxy(20, 4);
    printf("Producido: %i", producido);
    gotoxy(20, 5);
    printf("Productor\n");
    gotoxy(20, 6);
    if(productor.estado == true) {
        printf("Estado: Activo");
    } else {
        printf("Estado: Durmiendo");
    }
    gotoxy(80, 4);
    printf("Consumido: %i", consumido);
    gotoxy(80, 5);
    printf("Consumidor\n");
    gotoxy(80, 6);
    if(consumidor.estado == true) {
        printf("Estado: Activo");
    } else {
        printf("Estado: Durmiendo");
    }
}

bool estaLleno() {
	int i = 0;
    for (i = 0; i < 10; i++) {
        if (vectorProduccion[i] != 1) {
            return false;
        }
    }
    return true;
}

int contarUnos() {
    int cont = 0, i = 0;
    for (i = 0; i < 10; i++) {
        if (vectorProduccion[i] == 1) {
            cont++;
        }
    }
    return cont;
}

int main() {
	
	srand(time(NULL));

    int i = 0, tanda = 0, j = 0, pos = 0;
    bool vectorVacio = true;

    productor.estado = true;
    consumidor.estado = false;

    while (producido < 100) {
        #pragma omp parallel sections
        {
            #pragma omp section
            {
                if (producido < 100 && consumidor.estado == false && vectorVacio == true) {
                    tanda = randomsc(10);
                    i = 0;
                    while (i < tanda) {
                        pos = randomcc(10);
                        if (vectorProduccion[pos] == 0) {
                            vectorProduccion[pos] = 1;
                            producido++;
                            system("cls");
                            imprimirPantalla();
                            for (j = 0; j < 10; j++) {
                                gotoxy(51 + j, 10);
                                printf("%i", vectorProduccion[j]);
                            }
                            sleep(randomsc(2));
                            i++;
                        } else if (estaLleno()) {
                            break;
                        }
                    }
                    tanda = 0;
                    vectorVacio = false;
                    productor.estado = false;
                    consumidor.estado = true; // Cambiar estado del consumidor
                }
            }
            // Consumidor
            #pragma omp section
            {
                if (producido < 100 && productor.estado == false && vectorVacio == false) {
                    tanda = randomsc(contarUnos());
                    i = 0;
                    while (i < tanda) {
                        pos = randomcc(10);
                        if (vectorProduccion[pos] == 1) {
                            vectorProduccion[pos] = 0;
                            consumido++;
                            system("cls");
                            imprimirPantalla();
                            for (j = 0; j < 10; j++) {
                                gotoxy(51 + j, 10);
                                printf("%i", vectorProduccion[j]);
                            }
                            sleep(randomsc(2));
                            i++;
                        }
                    }
                    tanda = 0;
                    vectorVacio = true;
                    productor.estado = true; // Cambiar estado del productor
                    consumidor.estado = false;
                }
            }
        }
        sleep(2);
    }
    return 0;
}

