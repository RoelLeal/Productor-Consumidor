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

int random() {
	srand(time(NULL));
	return 1 + rand() % 10;
}

int main() {
	
	int producido = 0;
	
	struct consumidor consumidor;
	struct productor productor;
	
	productor.estado = true;
	consumidor.estado = false;
	
	#pragma omp parallel num_threads(1)
	{
		if(produccionTotal <= 100 && 
		  consumidor.estado == false) {
			printf("%i \n", random());
			printf("Hola");
			productor.estado = false;
		}
	}
	#pragma omp parallel num_threads(1)
	{
		if(produccionTotal <= 100 &&
			productor.estado == false) {
			printf("%i \n", random());
			printf("Adios");
			consumidor.estado = false;
		}
	}
	if(produccionTotal < 100)
		return 0;
	main();
	
	return 0;
}
