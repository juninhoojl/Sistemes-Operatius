#ifndef basedados_h
#define basedados_h

#include <stdio.h>
#include <mysql.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

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
// Pensar em criptografar senhar no futuro
// #include <openssl/md5.h> 

typedef struct BitVal{
	
	unsigned x:1;
}bitval;




#endif
