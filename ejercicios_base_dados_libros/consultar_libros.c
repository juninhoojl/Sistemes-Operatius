#include <mysql.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// Consultar livros
#define SERVIDOR "localhost"
#define USUARIO "root"
#define SENHA "mysql"
#define BASE "libros"

int main(int argc, char **argv){
	
	MYSQL *conn;
	int err;
	MYSQL_RES *resultado;
	MYSQL_ROW row;
	int edad;
	
	char consulta [80];
	
	char titulo[25];
	char autor[25];
	
	float preco;
	char precs[9];
	
	unsigned int codigo;
	char codigs[10];
	
	
	conn = mysql_init(NULL);
	
	if (conn==NULL){
		printf ("Error al crear la conexaon: %u %s\n", mysql_errno(conn), mysql_error(conn));
		exit (1); 
	}
	//inicializar la conexion
	conn = mysql_real_connect(conn,SERVIDOR,USUARIO,SENHA,BASE,0, NULL, 0); 
	
	if (conn==NULL){
		printf ("Error al inicializar la conexaon: %u %s\n", mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	
	// consulta todos os livros da base
	err=mysql_query (conn, "SELECT * FROM libros");
	
	if (err!=0){
		printf ("Error al consultar datos de la base %u %s\n", mysql_errno(conn), mysql_error(conn));
		exit (1); 
	}
	
	resultado = mysql_store_result (conn);
	row = mysql_fetch_row (resultado);
	
	if (row == NULL){
		printf ("No se han obtenido datos en la consulta\n"); 
	}else{
		while (row !=NULL) {
			codigo = atoi (row[0]);
			preco = strtof (row[3], NULL);
			printf ("Codigo: %u, Titulo: %s, Autor: %s, Preco: %.2f\n",codigo,row[1],row[2],preco);
			row = mysql_fetch_row (resultado);
		}
	}
	
	printf ("\nDame el nombre del autor que quieres buscar: ");
	scanf ("%s", &autor[0]);
	strcpy (consulta,"SELECT titulo FROM libros WHERE autor = '"); 
	strcat (consulta,autor);
	strcat (consulta,"'");
	
	err=mysql_query (conn, consulta); 
	
	if (err!=0) {
		printf ("Error al consultar datos de la base %u %s\n", mysql_errno(conn), mysql_error(conn));
		exit (1); 
	}
	
	resultado = mysql_store_result(conn);
	row = mysql_fetch_row(resultado);
	
	if (row == NULL){
		printf ("No se han obtenido datos en la consulta\n");
	}else{
		printf ("Libros del autor: %s\n", autor);
		while (row !=NULL) {
			printf ("\t%s\n", row[0] );
			row = mysql_fetch_row (resultado);
		}
	}
	
	printf ("\nDame el codigo del libro que quieres borrar: ");
	scanf ("%u", &codigo);
	strcpy (consulta,"DELETE FROM libros WHERE codigo = '"); 
	sprintf(codigs, "%u", codigo);
	strcat (consulta, codigs); 
	strcat (consulta,"'");
	err=mysql_query (conn, consulta);
	
	
	
	printf ("\nDame el precio para buscar libros: ");
	scanf ("%f", &preco);
	strcpy (consulta,"SELECT CODIGO FROM libros WHERE preco < '"); 
	sprintf(precs, "%f", preco);
	strcat (consulta,precs);
	strcat (consulta,"'");
	
	err=mysql_query (conn, consulta); 
	
	if (err!=0) {
		printf ("Error al consultar datos de la base %u %s\n", mysql_errno(conn), mysql_error(conn));
		exit (1); 
	}
	
	resultado = mysql_store_result(conn);
	row = mysql_fetch_row(resultado);
	
	if (row == NULL){
		printf ("No se han obtenido datos en la consulta\n");
	}else{
		printf ("Codigo de libros con precios inferiores a %.2f:\n",preco);
		while (row !=NULL) {
			printf ("\t%s\n", row[0] );
			row = mysql_fetch_row (resultado);
		}
	}

	mysql_close (conn);
	exit(0);
}
	

	
	
	
	
	
