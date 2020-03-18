#include <mysql.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// Crear base de dados libros

#define SERVIDOR "localhost"
#define USUARIO "root"
#define SENHA "mysql"


int main(int argc, char **argv){
	
	
	MYSQL *conn;
	int err;
	
	conn=mysql_init(NULL);
	
	if(conn==NULL){
		
		printf("Error ao criar conexao: %u %s\n",mysql_errno(conn), mysql_error(conn));
		exit (1);
		
	}
	
	
	conn=mysql_real_connect(conn,SERVIDOR,USUARIO,SENHA,NULL,0,NULL,0);
	
	
	if(conn==NULL){
		
		printf("Erro ao iniciar conexao: %u%s\n",mysql_errno(conn),mysql_error(conn));
		exit (1);
		
	}
	
	mysql_query(conn,"drop database if exists libros;");
	err=mysql_query(conn,"create database libros;");
	
	if(err!=0){
		printf("Erro ao criar a base de dados: %u%s\n",mysql_errno(conn),mysql_error(conn));
		exit (1);
	}
	
	err=mysql_query(conn, "use libros;");
	
	if (err!=0){
		printf("Erro ao criar a base de dados: %u%s\n",mysql_errno(conn),mysql_error(conn));
		exit (1);
	}
	
	err=mysql_query(conn,"CREATE TABLE libros (CODIGO BIGINT not null primary key, titulo VARCHAR(25), autor VARCHAR(25), preco FLOAT (5,2))");
	
	if (err!=0){
		printf("Erro ao definir tabela: %u%s\n",mysql_errno(conn),mysql_error(conn));
		exit (1);
	}
	
	mysql_close(conn);
	
	return (0);
}
	
