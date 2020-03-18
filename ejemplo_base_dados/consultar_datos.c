#include <mysql.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// Consultar dados

int main(int argc, char **argv){

	MYSQL *conn;
	int err;
	MYSQL_RES *resultado;
	MYSQL_ROW row;
	int edad;
	char dni[10];
	char consulta [80];

	conn = mysql_init(NULL);

	if (conn==NULL){
		printf ("Error al crear la conexaon: %u %s\n", mysql_errno(conn), mysql_error(conn));
		exit (1); 
	}
	//inicializar la conexion
	conn = mysql_real_connect(conn,"localhost","root","mysql","personas",0, NULL, 0); 

	if (conn==NULL){
		printf ("Error al inicializar la conexaon: %u %s\n", mysql_errno(conn), mysql_error(conn));
		exit (1);
	}

	// consulta SQL para obtener una tabla con todos los datos // de la base de datos
	err=mysql_query (conn, "SELECT * FROM personas");

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
			edad = atoi (row[2]);
			// las columnas 0 y 1 contienen DNI y nombre
			printf ("DNI: %s, nombre: %s, edad: %d\n", row[0], row[1], edad);
			// obtenemos la siguiente fila
			row = mysql_fetch_row (resultado);
		}

	}
	
	printf ("Dame el DNI de la persona que quieres buscar\n");
	scanf ("%s", dni);
	strcpy (consulta,"SELECT nombre FROM personas WHERE dni = '"); 
	strcat (consulta, dni);
	strcat (consulta,"'");

	err=mysql_query (conn, consulta); 

	if (err!=0) {
		printf ("Error al consultar datos de la base %u %s\n", mysql_errno(conn), mysql_error(conn));
		exit (1); 
	}

	resultado = mysql_store_result (conn);
	row = mysql_fetch_row (resultado);

	if (row == NULL){
		printf ("No se han obtenido datos en la consulta\n");
	}else{
		printf ("Nombre de la persona: %s\n", row[0] );
	}

	mysql_close (conn);
	exit(0);
}

