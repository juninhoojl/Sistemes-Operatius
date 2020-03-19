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
#define QTDMAX 4
#define QTDMIN 2
#define CHARSNOME 25
#define TAMUSERNAME CHARSNOME+1

// Arquivo /media/psf/Home/Documents/Sistemes-Operatius/ficheros_sql

// Insere usuarios OK
// Cria jogo com usuarios do arquivo game FILE
// Relaciona eles com o jogo
// Incrementa um na pontuacao de um deles
// define vencedor
// Encerra partida

// Funcao para inserir os jogadores
int insere_Player(char nome_arq[], MYSQL *conn);

//
unsigned int cria_Game(MYSQL *conn, char players[QTDMAX][TAMUSERNAME], int qtd);
// Query para editar UPDATE refranero SET fecha="2003-06-01" WHERE ID=1;


int main(int argc, char **argv){
	
	
	char players[QTDMAX][TAMUSERNAME] = {"jose", "juninhoojl", "luiz"};
	
	int qtdp = 3;
	
	int i=0;
	
	unsigned int id_jogo=0;
	// Ler lista de pessoas para um mesmo jogo
	// Cria jogo
	// Pega o id e adiciona na lista
	
	MYSQL *conn;
	int err;
	
	conn=mysql_init(NULL);

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
	
	
	for(i=0;i<qtdp;i++){
		printf("Player %d = %s\n",i,players[i]);
	}
	
	
	//insere_Player(PLAYERFILE, conn);
	
	//insere_Player(PLAYERFILE, conn);
	qtdp=3;
	
	id_jogo=cria_Game(conn, players, qtdp);
	printf("IdJogo = %u\n",id_jogo); 
	
	for(i=0;i<qtdp;i++){
		printf("Player %d = %s\n",i,players[i]);
	}
	
	// Agora ja relaciona jogadores da lista usando id do game
	mysql_close (conn);
	
	
	exit(0); 
}

	
/*	INSERT INTO Player (Username, Password) VALUES ('Jose', '1qaz2wsx');*/
/*	INSERT INTO Player (Username, Password) VALUES ('Luiz', '2wsx3edc');*/
// Retorna ID do Game
int insere_Player(char nome_arq[], MYSQL *conn){
	
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
	
// Recebe pessoas que vao entrar em um jogo
unsigned int cria_Game(MYSQL *conn, char players[QTDMAX][TAMUSERNAME], int qtd){
	
	//FILE *arq;
	int err,i=0;
	unsigned int id_game=0;
	//char username[25];
	//char senha[25];
	char query[80];
	char id_games[10];
	MYSQL_RES *resultado;
	MYSQL_ROW row;
	
	//  Cria jogo e pega o ultimo id
	
	// INSERT INTO Game () VALUES ();
	// SELECT LAST_INSERT_ID();
	
	// Cria Game
	strcpy (query, "INSERT INTO Game () VALUES ();");
	err = mysql_query(conn, query);
	
	if (err!=0){
		printf ("Error ao introduzir dados na base %u %s\n", mysql_errno(conn), mysql_error(conn));
		return 1;
	}
	
	// Pega ultimo ID
	strcpy (query, "SELECT LAST_INSERT_ID();");
	err = mysql_query(conn, query);

	if (err!=0) {
		printf ("Error al consultar ultimo ID de la base %u %s\n", mysql_errno(conn), mysql_error(conn));
		exit (1); 
	}
	
	resultado = mysql_store_result(conn);
	row = mysql_fetch_row(resultado);
	
	id_game = atoi (row[0]);
	
	printf("id_game = %u\n",id_game); 
	
	
	
	for(i=0;i<qtd;i++){
		
		printf("Player %d = %s\n",i,players[i]);
		
	}
	
	
	/*
	
	for(i=0;i<qtd;i++){
		
		//INSERT INTO Relaciona (Game,Player) VALUES (1,'Luiz');
		
		printf("id_game = %u\n",id_game);
		
		strcpy (query, "INSERT INTO Relaciona (Game,Player) VALUES ('");
		sprintf(id_games, "%u", id_game);
		strcat (query, id_games);
		strcat (query, "','");
		strcat (query, players[i]);
		strcat (query, "','");
		strcat (query, ");");
		printf("query = %s\n", query);
		err = mysql_query(conn, query);
		
		// Nao precisa esvaziar string pq tem o fim da linha e comeca no 0
		if (err!=0){
			printf ("Error ao introduzir dados na base %u %s\n", mysql_errno(conn), mysql_error(conn));
			exit (1); 
		}
		
		
		
		
		//INSERT INTO Relaciona (Game,Player) VALUES (1,'Luiz');
		
	}
	
	
	
	*/
	

	return id_game;
}
	

	
	
	
	
	
	
