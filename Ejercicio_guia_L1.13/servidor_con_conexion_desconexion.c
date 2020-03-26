#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>

#include "servidor.h"
#include "basedados.h"

int main(int argc, char *argv[]){
	
	printf("Soma = %d\n",soma(2,3));

	int sock_conn, sock_listen, ret;
	struct sockaddr_in serv_adr;
	char peticion[512];
	char respuesta[512];
	
	// Socket que vai esperar por alguma conexao, de escuta
	if ((sock_listen = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		printf("Error ao criar socket");
	// Fem el bind al port
	
	
	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family = AF_INET;
	
	// Estamos escutando de qualquer endereco ip
	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
	// Associamos o socket que criamos com porta e tipo de dados
	serv_adr.sin_port = htons(9000);
	if (bind(sock_listen, (struct sockaddr *) &serv_adr, sizeof(serv_adr)) < 0)
		printf ("Erro ao fazer bind");
	
	// A fila de xonecoes nao pode ser maior que 3
	// Ate 3 podem estar na fila esperando pelo servidor
	if (listen(sock_listen, 3) < 0)
		printf("Erro na escuta");
	
	int i;
	
	// Laco infinito
	for (;;){
		printf ("Escuchando\n");
		
		// Quando escuta algo cria um socket de conexao
		sock_conn = accept(sock_listen, NULL, NULL);

		printf ("Recebi uma conexao\n");


		int terminar =0;
		// Atender esse cliente ate que se desconecte
		
		while (terminar ==0)
		{
			// Ahora recibimos la petici?n
			ret=read(sock_conn,peticion, sizeof(peticion));
			printf ("Recibido\n");
			
			// Tenemos que a?adirle la marca de fin de string 
			// para que no escriba lo que hay despues en el buffer
			peticion[ret]='\0';
			
			
			printf ("Peticao: %s\n",peticion);
			
			// vamos a ver que quieren
			char *p = strtok( peticion, "/");
			int codigo =  atoi (p);
			// Ya tenemos el c?digo de la petici?n
			char nombre[20];
			
			if (codigo !=0)
			{
				p = strtok( NULL, "/");
				strcpy (nombre, p);
				// Ya tenemos el nombre
				printf ("Codigo: %d, Nome: %s\n", codigo, nombre);
			}
			
			if (codigo ==0) //petici?n de desconexi?n
				terminar=1;
			else if (codigo ==1) //piden la longitd del nombre
				sprintf (respuesta,"%d",(int)strlen (nombre));
			else if (codigo ==2)
				// quieren saber si el nombre es bonito
				if((nombre[0]=='M') || (nombre[0]=='S'))
				strcpy (respuesta,"SIM");
				else
					strcpy (respuesta,"NAO");
			else //quiere saber si es alto
			{
				p = strtok( NULL, "/");
				float altura =  atof (p);
				if (altura > 1.70)
					sprintf (respuesta, "%s eh alto",nombre);
				else
					sprintf (respuesta, "%s eh baixo",nombre);
			}
				
			if (codigo !=0)
			{
				
				printf ("Resposta: %s\n", respuesta);
				// Enviamos a resposta
				write (sock_conn,respuesta, strlen(respuesta));
			}
		}
		// O servico acabou para esse cliente
		close(sock_conn); 
	}
}
