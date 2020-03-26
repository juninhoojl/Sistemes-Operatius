

#include "basedados.h"

// Intoducir dados en base ya creada

// Arquivo /media/psf/Home/Documents/Sistemes-Operatius/ficheros_sql

// Insere usuarios OK
// Cria jogo com usuarios do arquivo game FILE OK
// Relaciona eles com o jogo OK
// Incrementa um na pontuacao de um deles
// define vencedor
// Encerra partida
// Funcao para inserir os jogadores


int insere_Player(char nome_arq[], MYSQL *conn);


// Funcao para criar Game inserir usernames do array e retrornar o id do game que estao
unsigned int cria_Game(MYSQL *conn, char players[QTDMAX][TAMUSERNAME], int qtd);

// Funcao para alterar pontuacao de um usuario especifico
int altera_Pontuacao(MYSQL *conn, unsigned int id_game, char player[], int alt_score);

int insere_user(char user[], char senha[], MYSQL *conn);

int loga_user(char user[], char senha[], MYSQL *conn);

int existe_user(char user[], MYSQL *conn);

int desativa_user(char user[], char senha[], MYSQL *conn);

int ativa_user(char user[], char senha[], MYSQL *conn);

int user_ativo(char user[], MYSQL *conn);

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
	
	
	/*
	for(i=0;i<qtdp;i++){
		printf("Player %d = %s\n",i,players[i]);
	}
	
	*/
	
	
	insere_user("juninhos1","1qaz2wsx",conn);
	
	
	insere_user("jose","asdfghjk",conn);
	loga_user("jose","asdfghjk",conn);
	
	desativa_user("jose","asdfghjk",conn);
	

	printf("ATIVO = %d", user_ativo("juninhos1",conn));
	
	ativa_user("jose","asdfghjk",conn);
	
	
	
	// Descomentar para inserir jugadores
	//insere_Player(PLAYERFILE, conn);
	
	//id_jogo=cria_Game(conn, players, qtdp);
	
	//altera_Pontuacao(conn, 1, players[0], 10);
	
	qtdp=3;
	
	// Descomentar para criar juego
	//
	//printf("IdJogo = %u\n",id_jogo); 
	
	/*	for(i=0;i<qtdp;i++){*/
	/*		printf("Player %d = %s\n",i,players[i]);*/
	/*	}*/
	
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
	
	
	
int insere_user(char user[], char senha[], MYSQL *conn){
	
	// Conferir se existe USUARIO
	// se nao nao insere
	char query[80];
	int err;
	
	if(existe_user(user,conn)){
		
		printf("Usuario ja existe\n");
		return 1;
	}else{
		strcpy (query, "INSERT INTO Player (Username, Password) VALUES ('");
		strcat (query, user);
		strcat (query, "','");
		strcat (query, senha); 
		strcat (query, "'");
		strcat (query, ");");
		printf("query = %s\n", query);
		err = mysql_query(conn, query);
		
		if (err!=0){
			printf ("Error ao introduzir dados na base %u %s\n", mysql_errno(conn), mysql_error(conn));
			return 1;
		}else{
			
			printf("Usuario inserido com sucesso\n");
		}
	}
	return 0;
}
	
// Deleta usuario (altera flag de ativo para false);
// Ativo recebe bit false
	
int loga_user(char user[], char senha[], MYSQL *conn){
	
	char query[80];
	int err;
	MYSQL_RES *resultado;
	MYSQL_ROW row;

	if(existe_user(user,conn)){
		
		// SELECT EXISTS(SELECT * FROM Player WHERE Username = 'jose' AND Password = 'asdfghjk');
		
		strcpy (query, "SELECT EXISTS(SELECT * FROM Player WHERE Username = '");
		strcat (query, user);
		strcat (query, "' AND Password = '");
		strcat (query, senha);
		strcat (query, "');");
		
		err = mysql_query(conn, query);
		
		if (err!=0) {
			printf ("Error ao consultar usuario na base %u %s\n", mysql_errno(conn), mysql_error(conn));
			exit (1); 
		}
		
		resultado = mysql_store_result(conn);
		row = mysql_fetch_row(resultado);
		
		if(atoi(row[0]) == 1){ // Login ok
			
			printf("Usuario e senha corretos\n");
			return 1;
			
		}else{ // Nao pode logar
			
			printf("Usuario e/ou senha incorretos\n");
			
		}
		
	}else{
		printf("Usuario nao existe\n");
	}

	return 0;
}
	


int user_ativo(char user[], MYSQL *conn){
	
	char query[80];
	int err;
	MYSQL_RES *resultado;
	MYSQL_ROW row;
	char valor;
	
	// Somente se existe
	
	if(existe_user(user,conn)){

		strcpy (query, "SELECT Ativo FROM Player WHERE Username = '");
		strcat (query, user);
		strcat (query, "';");
		
		err = mysql_query(conn, query);
		
		if (err!=0) {
			printf ("Error ao consultar usuario na base %u %s\n", mysql_errno(conn), mysql_error(conn));
			exit (1); 
		}
		
		resultado = mysql_store_result(conn);
		row = mysql_fetch_row(resultado);
		
		
	}else{
		//Retorna 2 se nao exite
		return 2;
	}
	
	
	
	
	return atoi(row[0]);
}
	

	
int desativa_user(char user[], char senha[], MYSQL *conn){
	
	char query[80];
	int err;
	MYSQL_RES *resultado;
	MYSQL_ROW row;
	
	// Se pode se autenticar pode se remover
	
	if(loga_user(user,senha,conn)){
		
		printf("Pode ser deletado\n");
	}
	strcpy (query, "UPDATE Player SET Ativo=0 WHERE Username='");
	strcat (query, user);
	strcat (query, "';");
	
	printf("query = %s\n", query);
	
	err = mysql_query(conn, query);
	
	if (err!=0){
		printf ("Error ao remover usuario na base %u %s\n", mysql_errno(conn), mysql_error(conn));
		return 1;
	}

	return 0;
}
	
int ativa_user(char user[], char senha[], MYSQL *conn){
	
	char query[80];
	int err;
	MYSQL_RES *resultado;
	MYSQL_ROW row;
	
	// Se pode se autenticar pode se remover
	
	if(loga_user(user,senha,conn)){
		
		printf("Pode ser ativado\n");
	}
	strcpy (query, "UPDATE Player SET Ativo=1 WHERE Username='");
	strcat (query, user);
	strcat (query, "';");
	
	printf("query = %s\n", query);
	
	err = mysql_query(conn, query);
	
	if (err!=0){
		printf ("Error ao ativar usuario na base %u %s\n", mysql_errno(conn), mysql_error(conn));
		return 1;
	}
	
	return 0;
}


int existe_user(char user[], MYSQL *conn){
	
	char query[80];
	int err;
	MYSQL_RES *resultado;
	MYSQL_ROW row;
	
	strcpy (query, "SELECT EXISTS(SELECT * FROM Player WHERE Username = '");
	strcat (query, user);
	strcat (query, "');");
	
	err = mysql_query(conn, query);
	
	if (err!=0) {
		printf ("Error ao consultar usuario na base %u %s\n", mysql_errno(conn), mysql_error(conn));
		exit (1); 
	}
	
	resultado = mysql_store_result(conn);
	row = mysql_fetch_row(resultado);
	
	// Quantidade que existe, tem que ser 1 para existir
	
	return atoi(row[0]);
}

	
	
// Recebe pessoas que vao entrar em um jogo
unsigned int cria_Game(MYSQL *conn, char players[QTDMAX][TAMUSERNAME], int qtd){
	
	int err,i=0;
	unsigned int id_game=0;
	char query[80];
	char id_games[10];
	MYSQL_RES *resultado;
	MYSQL_ROW row;
	
	// Cria Game
	strcpy (query, "INSERT INTO Game () VALUES ();");
	err = mysql_query(conn, query);
	
	if (err!=0){
		printf ("Error ao introduzir dados na base %u %s\n", mysql_errno(conn), mysql_error(conn));
		return 1;
	}
	
	// Seleciona ultimo ID
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
		
		//INSERT INTO Relaciona (Game,Player) VALUES (1,'Luiz');
		printf("id_game = %u\n",id_game);
		strcpy (query, "INSERT INTO Relaciona (Game,Player) VALUES ('");
		sprintf(id_games, "%u", id_game);
		strcat (query, id_games);
		strcat (query, "','");
		strcat (query, players[i]);
		strcat (query, "'");
		strcat (query, ");");
		printf("query = %s\n", query);
		err = mysql_query(conn, query);
		
		// Nao precisa esvaziar string pq tem o fim da linha e comeca no 0
		if (err!=0){
			printf ("Error ao introduzir dados na base %u %s\n", mysql_errno(conn), mysql_error(conn));
			exit (1); 
		}
		
	}
	
	// Retorna id do Game que foram adicionados
	return id_game;
}

	
int altera_Pontuacao(MYSQL *conn, unsigned int id_game, char player[], int alt_score){
	
	// Query para editar 
	// UPDATE Relaciona SET score=PONTOS WHERE Player=PLAYERNAME AND Game=GAMEID;
	
	// Antes consulta os pontos atuais faz a conta com a alteracao
	
	int err,i=0;
	//unsigned int id_game=0;
	char query[80];
	char id_games[10];
	MYSQL_RES *resultado;
	MYSQL_ROW row;
	int score=10;
	char scores[10];
	
	
	strcpy (query, "SELECT Score from Relaciona WHERE Game='");
	sprintf(id_games, "%u", id_game);
	strcat (query, id_games);
	strcat (query, "' AND Player='");
	strcat (query, player);
	strcat (query, "';");
	
	printf("query = %s\n", query);
	
	err = mysql_query(conn, query);
	
	if (err!=0){
		printf ("Error ao introduzir dados na base %u %s\n", mysql_errno(conn), mysql_error(conn));
		return 1;
	}
	
	resultado = mysql_store_result(conn);
	row = mysql_fetch_row(resultado);
	
	score = atoi (row[0]);
	
	printf("\nSCORE = %d\n",score);
	
	score += alt_score;
	
	strcpy (query, "UPDATE Relaciona SET score='");
	sprintf(scores, "%d", score);
	strcat (query, scores);
	strcat (query, "' WHERE Player='");
	strcat (query, player);
	strcat (query, "' AND Game='");
	sprintf(id_games, "%d", id_game);
	strcat (query, id_games);
	strcat (query, "';");
	printf("query = %s\n", query);
	
	err = mysql_query(conn, query);
	
	if (err!=0){
		printf ("Error ao introduzir dados na base %u %s\n", mysql_errno(conn), mysql_error(conn));
		return 1;
	}
	
	
	return 0;
}

