#include <stdio.h>
#include <mysql.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
// Pensar em criptografar senhar no futuro
#include <openssl/md5.h> 

// Intoducir dados en base ya creada
#define SERVIDOR "localhost"
#define USUARIO "root"
#define SENHA "mysql"
#define BASE "GameSO"
#define PLAYERFILE "players.txt"
#define GAMEFILE "games.txt"

// Arquivo /media/psf/Home/Documents/Sistemes-Operatius/ficheros_sql

// Insere usuarios OK
// Cria jogo com usuarios do arquivo game FILE
// Relaciona eles com o jogo
// Incrementa um na pontuacao de um deles
// define vencedor
// Encerra partida

// Funcao para inserir os jogadores
int insere_Player(char *nome_arq[], MYSQL *conn);

//
int insere_Player(char *nome_arq[], MYSQL *conn);

// Query para editar UPDATE refranero SET fecha="2003-06-01" WHERE ID=1;


int main(int argc, char **argv){
	
	MYSQL *conn;
	int err;

	

	conn=mysql_init(NULL);
	
	//char filename[40];

	// Inserir jogadores
	// Senha 25
	// Username 25
	
	

	/*	INSERT INTO Player (Username, Password) VALUES ('Jose', '1qaz2wsx');*/
	/*	INSERT INTO Player (Username, Password) VALUES ('Luiz', '2wsx3edc');*/
	
	/*	INSERT INTO Game (Duracion,Vencedor) VALUES (33,1);*/
	/*	INSERT INTO Game (Duracion,Vencedor) VALUES (30,2);*/
	
	/*	INSERT INTO Relaciona (IDg,IDp) VALUES (1,1);*/
	/*	INSERT INTO Relaciona (IDg,IDp) VALUES (1,2);*/
	
	
	if(conn==NULL){
		printf("Error ao criar conexao: %u %s\n",mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	
	conn=mysql_real_connect(conn,SERVIDOR,USUARIO,SENHA,BASE,0, NULL, 0);
	
	if(conn==NULL){
		printf("Erro ao iniciar conexao: %u%s\n",mysql_errno(conn),mysql_error(conn));
		exit (1);
	}
	

	
	insere_Player(PLAYERFILE, conn);
	
	
	mysql_close (conn);
	
	
	exit(0);
	
/*	arq=fopen(GAMEFILE, "r");*/
	
/*	if (arq==NULL){*/
/*		perror("Error");*/
/*		return 1;*/
/*	}else{ */
		
/*		if (arq==NULL){*/
/*			perror("Error");*/
/*			return 1;*/
/*		}else{*/
			
/*			while(!feof(arq)) {*/
				
/*				err=fscanf(arq,"%s %s", &username[0], &senha[0]);*/
				
/*				if(err!=2){*/
					
					// Caso esteja na ultima linha, para nao repetir
/*					if(err<0){*/
/*						exit(1);*/
/*					}*/
/*					printf("Erro ao introduzir dados\n");*/
/*					printf("%d",err); */
					
/*				}*/
/*				strcpy (query, "INSERT INTO Player (Username, Password) VALUES ('");*/
/*				strcat (query, username);*/
/*				strcat (query, "','");*/
/*				strcat (query, senha); */
/*				strcat (query, "'");*/
/*				strcat (query, ");");*/
/*				printf("query = %s\n", query);*/
/*				err = mysql_query(conn, query);*/
				
/*				if (err!=0){*/
/*					printf ("Error ao introduzir dados na base %u %s\n", mysql_errno(conn), mysql_error(conn));*/
/*					exit (1); */
/*				}*/
/*			}*/
/*		}*/
/*	}*/
/*	fclose(arq);*/
	
	
	
	exit(0); 
}

	
	
	
	
	
int insere_Player(char *nome_arq[], MYSQL *conn){
	
	FILE *arq;
	int err;
	char username[25];
	char senha[25];
	char query[80];
	
	// Abre arquivo
	arq=fopen(nome_arq, "r");
	
	// Insere dados
	if (arq==NULL){
		perror("Error");
		return 1;
	}else{ 
		
		if (arq==NULL){
			perror("Error");
			return 1;
		}else{
			
			while(!feof(arq)) {
				
				err=fscanf(arq,"%s %s", &username[0], &senha[0]);
				
				if(err!=2){
					
					// Caso esteja na ultima linha, para nao repetir
					if(err<0){
						return 1;
					}
					printf("Erro ao introduzir dados\n");
					printf("%d",err); 
					
				}
				strcpy (query, "INSERT INTO Player (Username, Password) VALUES ('");
				strcat (query, username);
				strcat (query, "','");
				strcat (query, senha); 
				strcat (query, "'");
				strcat (query, ");");
				printf("query = %s\n", query);
				err = mysql_query(conn, query);
				
				if (err!=0){
					printf ("Error ao introduzir dados na base %u %s\n", mysql_errno(conn), mysql_error(conn));
					return 1;
				}
			}
		}
	}
	
	// Fecha arquivo
	fclose(arq);
	
	return 0;
}
	
	
	
	
	
	
	
