#include <stdio.h>
#include <stdbool.h>
#include <omp.h>
#include <stdlib.h>
#include <unistd.h>

struct consumidor {
    bool estado;
    int consumoActual;
} consumidor;

struct productor {
    bool estado;
    int produccionActual;
} productor;

int produccionTotal = 0;
int vectorProduccion[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

int random(int rango) {
    return 1 + rand() % rango;
}

int main() {
    int i = 0, tanda = 0, j = 0;
    bool vectorVacio = true;

    struct consumidor consumidor;
    struct productor productor;

    productor.estado = true;
    consumidor.estado = false;

    while (produccionTotal < 100) {
        #pragma omp sections
        {
            #pragma omp section
            {
                if (produccionTotal < 100 && 
					consumidor.estado == false && vectorVacio == true) {
                    tanda = 0;
					tanda = random(10);
                    produccionTotal += tanda;
                    printf("\nProductor: \n");
                    for (i = 0; i < tanda; i++) {
                        vectorProduccion[i] = 1;
                        for(j = 0; j < 10; j++) {
                        	printf("%i", vectorProduccion[j]);
                        	if (j == 4)
                            	printf("\n");
						}
						printf("\n\n");
                        sleep(2);
                    }
//                    for (i = 0; i < 10; i++) {
//                        printf("%i", vectorProduccion[i]);
//                        if (i == 4)
//                            printf("\n");
//                    }
                    vectorVacio = false;
                    productor.estado = false;
                }
            }
            // Consumidor
            #pragma omp section
            {
                if (produccionTotal < 100 && 
					productor.estado == false && vectorVacio == false) {
                	printf("\nConsumidor: \n");
                    for (i = 0; i < tanda; i++) {
                        for(j = 0; j < 10; j++) {
                        	printf("%i", vectorProduccion[j]);
                        	if (j == 4)
                            	printf("\n");
						}
						printf("\n\n");
						if(vectorProduccion[i] == 1)
                            vectorProduccion[i] = 0;
						sleep(2);
                    }
                    vectorVacio = true;
                    consumidor.estado = false;
                }
            }
        }
        sleep(2);
    }
    return 0;
}
