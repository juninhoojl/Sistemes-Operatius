#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	int sock_conn, sock_listen, ret;
	struct sockaddr_in serv_adr;
	char peticao[512];
	char resposta[512];

	
	// Socket que vai esperar por alguma conexao, de escuta
	if ((sock_listen = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		printf("Error ao criar socket");
	}
	// Fem el bind al port
	
	memset(&serv_adr, 0, sizeof(serv_adr));// inicialitza a zero serv_addr
	serv_adr.sin_family = AF_INET;

	// Estamos escutando de qualquer endereco ip
	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	// escucharemos en el port 9050
	serv_adr.sin_port = htons(9050);
	
	// Associamos o socket que criamos com porta e tipo de dados
	if (bind(sock_listen, (struct sockaddr *) &serv_adr, sizeof(serv_adr)) < 0){
		
		printf ("Erro ao fazer bind");
	}
	
	// A fila de xonecoes nao pode ser maior que 2
	// Ate 2 podem estar na fila esperando pelo servidor
	if (listen(sock_listen, 3) < 0){
		printf("Erro na escuta");
	}
	
	int i;
	
	// Atenderemos solo 5 peticione
	// O normal eh nao ter limite
	for(i=0;i<5;i++){
		printf ("Escutando\n");
		
		// Quando escuta algo cria um socket de conexao
		sock_conn = accept(sock_listen, NULL, NULL);
		printf ("Recebi uma conexao\n");
		//sock_conn es el socket que usaremos para este cliente
		
		// Ahora recibimos su nombre, que dejamos en buff
		ret=read(sock_conn,peticao, sizeof(peticao));
		printf ("Recebido\n");
		
		// Tenemos que a?adirle la marca de fin de string 
		// para que no escriba lo que hay despues en el buffer
		peticao[ret]='\0';
		
		//Escribimos el nombre en la consola
		printf("Peticao: %s\n",peticao);
		
		// Ela dar um ponteiro que vai desde o comeco ate 
		// o caractere que queremos
		char *p=strtok(peticao,"/");
		// Sendo ele o
		int codigo=atoi(p);
		// Agora cortar ate o fim da string ou ate onde tem outra barra
		p=strtok(NULL,"/");
		char nombre[20];
		strcpy(nombre, p);
		printf("Codigo: %d, Nombre: %s\n", codigo, nombre);
		
		
		// A mensagem de peticao vem no estilo: 1/nombre ou 2/nombre
		// 2/juan, 1/maria...
		// Servicos 1 - Tamanho
		// Servico 2 - Nome bonito ou nao
		// Servico 3 - Pessoa alta ou nao
		
		// Determinar o que estao pedindo no servidor
		if (codigo == 1){ // Servico 1 - Tamanho
			sprintf(resposta,"%d",strlen(nombre));

		}else if (codigo == 2){ // Servico 2 - Nome bonito ou nao
			
			if((nombre[0]=='M') || (nombre[0]=='S')){
				strcpy(resposta,"SIM");
			}else{
				strcpy(resposta,"NAO");
			}
		}else{ // Servico 3 - Pessoa alta ou nao
			
			// Temos que coletar tambem a altura
			// 3/NOME/Altura
			// exemplo: 3/Jose/1.74
			// A partir do momento que foi feito um string tok ele substitui por null
			// Entao comeca no null
			p=strtok(NULL,"/");
			// Sendo ele uma altura eh float
			float altura=atof(p);
			
			if(altura > 1.7){ // Pessoa alta
				sprintf(resposta,"%s eh alto/a",strlen(nombre));
			}else{ // Pessoa baixa
				sprintf(resposta,"%s eh baixo/a",strlen(nombre));
			}
			
			// Enviamos a resposta
			write (sock_conn,resposta, strlen(resposta));
			// Servico encerrado para esse cliente
			close(sock_conn);
			
		}
	}	
}
