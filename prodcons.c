#include <stdio.h>
#include <stdbool.h>
#include <omp.h>

struct consumidor {
	bool estado;
	int consumoActual;
} consumidor;

struct productor {
	bool estado;
	int produccionActual;
} productor;

int produccionTotal = 100;
int vectorProduccion[10];

int main() {
	
	
	int producido = 0;
	
	struct consumidor consumidor;
	struct productor productor;
	
	productor.estado = true;
	consumidor.estado = false;
	
	#pragma omp parallel sections 
	{
		#pragma omp section //PRODUCTOR
		{
			if(produccionTotal <= 100 && 
			consumidor.estado == false) {
				producido = 1 + rand() * 10;
				printf("%i", producido);
			}
		}
		#pragma omp section //CONSUMIDOR
		{
			if(produccionTotal <= 100 && 
			productor.estado == false) {
				
			}
		}
	}
}
