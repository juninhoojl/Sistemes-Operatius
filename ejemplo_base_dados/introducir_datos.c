#include <mysql.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// TESTE 
int main(int argc, char **argv){

	MYSQL *conn;
	int err;
	char dni[10];
	char nombre[25];
	int edad;
	char edads[3];
	int i;
	char consulta[80];
	conn=mysql_init(NULL);

	if(conn==NULL){

		printf("Error ao criar conexao: %u %s\n",mysql_errno(conn), mysql_error(conn));
		exit (1);

	}

	conn=mysql_real_connect(conn,"localhost","root","mysql","personas",0, NULL, 0);

	if(conn==NULL){

		printf("Erro ao iniciar conexao: %u%s\n",mysql_errno(conn),mysql_error(conn));
		exit (1);

	}

	for(i=0;i<4;++i) {
		printf("Escreva o DNI, nome e idade da pessoa separados por um espaco: \n");
		err=scanf("%s %s %d",dni,nombre,&edad);

		if(err!=3){
			printf("Erro ao introduzir dados\n");
			exit(1);
		}

		strcpy (consulta, "INSERT INTO personas VALUES ('");

		strcat (consulta, dni);

		strcat (consulta, "','");

		strcat (consulta, nombre);

		strcat (consulta, "',");

		sprintf(edads, "%d", edad);

		strcat (consulta, edads); 

		strcat (consulta, ");");

		printf("consulta = %s\n", consulta);

		err = mysql_query(conn, consulta);

		if (err!=0){

			printf ("Error ao introduzir dados na base %u %s\n", mysql_errno(conn), mysql_error(conn));
			exit (1); 
		}
		
	}

	
	mysql_close (conn);
	
	exit(0); 
}


