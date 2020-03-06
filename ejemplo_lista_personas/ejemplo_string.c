#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int ContarA (char frase[80])
{
	int i=0;
	int cont=0;
	for (i=0; i< strlen(frase); i++)
		if ((frase[i] =='a')|| (frase[i]=='A'))
			cont = cont+1;
	return cont;
}

int main(void) {
	int edad;
	char nombre[20];
	float altura;
	char frase[80];
	printf ("Escribe tu nombre y tu edad separados por un blanco\n");
	int err = scanf ("%s %d", nombre, &edad);
	if (err !=2)
		printf ("Error en la entrada de datos");
	else
	{
		if (edad >18)
			printf ("%s: eres mayor de edad\n", nombre);
		printf ("Ahora escribe tu altura y tu frase favorita, separados por un blanco\n");
		err = scanf ("%f", &altura);
		gets (frase);

		if (err !=1)
			printf ("Error en la entrada de datos");
		else
		{
			int i=0;
			int cont=ContarA (frase);
			printf ("%s: tu altura es %f y tu en tu frase favorita la letra a se repite %d veces\n", nombre, altura, cont);
			printf ("Por cierto, la frase es: %s\n", frase);

		}
	}



}
