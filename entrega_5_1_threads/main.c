#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *procesar_votos_fichero(void *thread_id);

int votaciones [2][10];

// Compilar com parametro -l pthread


int main(int argc, char *argv[]) {

	pthread_t thread;
	
	int j;
	
	for (j=0; j<10; j++){
		votaciones[0][j]=0;
		votaciones[1][j]=0;
	}
	
	pthread_create(&thread, NULL, procesar_votos_fichero, NULL);
	//Endereco de memoria da thread/ parametro nulo/ funcao que ela vai executar/ e o argumento da funcao
	
	printf ("Leemos votos del colegio 0\n");
	j=0;
	
	while (j<10){
		printf ("\nVotos del partido %d: ", j);
		scanf ("%d",&votaciones[0][j]);
		j=j+1;
	}
	
	pthread_join(thread, NULL);
	
	// Acumulamos los votos en la fila 0 de la matriz
	printf ("Acumulamos votos\n");
	for (j=0; j<10; j++){
		votaciones[0][j] = votaciones[0][j]+votaciones[1][j];
	}
	
	printf ("Resultados\n");
	for (j=0; j<10; j++){
		printf ("Votos para el partido %d: %d\n",j,votaciones[0][j]);
	}
	//scanf ("%*c"); 
	return 0;
}
	

void *procesar_votos_fichero(void *thread_id){
	
	FILE *f;
	f=fopen ("colegio.txt","r"); int j;
	j=0;
	
	while (j<10){
		fscanf (f,"%d",&votaciones[1][j]);
		j=j+1;
	}
	
	pthread_exit(0);
	return NULL; 
}
	
	
	
	
	
	
	
	
