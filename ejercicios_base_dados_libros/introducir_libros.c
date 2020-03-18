#include <mysql.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// Intoducir dados en base ya creada
#define SERVIDOR "localhost"
#define USUARIO "root"
#define SENHA "mysql"
#define BASE "libros"

int main(int argc, char **argv){
	
	MYSQL *conn;
	int err;
	unsigned int codigo;
	char titulo[25];
	char autor[25];
	float preco;
	int i;
	char query[80];
	char precs[9];
	char codigs[10];
	conn=mysql_init(NULL);
	FILE *arq;
	char filename[40];
	int temp;
	
	if(conn==NULL){
		
		printf("Error ao criar conexao: %u %s\n",mysql_errno(conn), mysql_error(conn));
		exit (1);
		
	}
	
	conn=mysql_real_connect(conn,SERVIDOR,USUARIO,SENHA,BASE,0, NULL, 0);
	
	if(conn==NULL){
		
		printf("Erro ao iniciar conexao: %u%s\n",mysql_errno(conn),mysql_error(conn));
		exit (1);
	}

	
	printf("Nome do arquivo: ");
	scanf("%s",&filename[0]);
	arq=fopen(filename, "r");
	
	if (arq==NULL){
		perror("Error");
		return 1;
	}else{ 
		
		if (arq==NULL){
			perror("Error");
			return 1;
		}else{
			
			while(!feof(arq)) {
				
					//for(i=0;i<4;++i) {
					//printf("Escreva o codigo, titulo, autor e preco do livro separados por um espaco: \n");
					//err=scanf("%u %s %s %f", &codigo, &titulo[0], &autor[0], &preco);
				
				err=fscanf(arq,"%u %s %s %f", &codigo, &titulo[0], &autor[0], &preco);
				
				if(err!=4){
					
					// Caso esteja na ultima linha, para nao repetir
					if(err<0){
						exit(1);
					}
					
					printf("Erro ao introduzir dados\n");
					printf("%d",err); 
					
				}
				// Codigo titulo autor preco
				strcpy (query, "INSERT INTO libros VALUES ('");
				sprintf(codigs, "%u", codigo);
				strcat (query, codigs);
				strcat (query, "','");
				strcat (query, titulo);
				strcat (query, "','");
				strcat (query, autor); 
				strcat (query, "',");
				sprintf(precs, "%.2f", preco);
				strcat (query, precs); 
				strcat (query, ");");
				printf("query = %s\n", query);
				err = mysql_query(conn, query);
				
				// Nao precisa esvaziar string pq tem o fim da linha e comeca no 0
				if (err!=0){
					printf ("Error ao introduzir dados na base %u %s\n", mysql_errno(conn), mysql_error(conn));
					exit (1); 
				}
				
			}
			
		}
	}
	
	fclose(arq);
	mysql_close (conn);
	
	exit(0); 
}
	
	
	
