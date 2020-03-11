//Programa en C para crear una base de datos
#include <mysql.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv){

	//Conector para acceder al servidor de bases de datos
	MYSQL *conn;
	int err;
	//Creamos una conexion al servidor MYSQL


	conn=mysql_init(NULL);

	if(conn==NULL){

		printf("Error ao criar conexao: %u %s\n",mysql_errno(conn), mysql_error(conn));
		exit (1);

	}

	//inicializar la conexion, indicando nuestras claves de acceso 
	// al servidor de bases de datos (user,pass)

	conn=mysql_real_connect(conn,"localhost","root","mysql",NULL,0,NULL,0);

	if(conn==NULL){

		printf("Erro ao iniciar conexao: %u%s\n",mysql_errno(conn),mysql_error(conn));
		exit (1);

	}

	mysql_query(conn,"drop database if exists personas;");
	err=mysql_query(conn,"create database personas;");

	if(err!=0){
		printf("Erro ao criar a base de dados: %u%s\n",mysql_errno(conn),mysql_error(conn));
		exit (1);
	}

	err=mysql_query(conn, "use personas;");

	if (err!=0){
		printf("Erro ao criar a base de dados: %u%s\n",mysql_errno(conn),mysql_error(conn));
		exit (1);
	}

	err=mysql_query(conn,"CREATE TABLE personas (DNI VARCHAR(10) not null primary key, nombre VARCHAR(25), edad int)");

	if (err!=0){

		printf("Erro ao definir tabela: %u%s\n",mysql_errno(conn),mysql_error(conn));
		exit (1);
	}

	mysql_close(conn);
		
		return (0);
}