// Atividade em sala: Jose Luiz Correa

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX 10
#define MAIORIDADE 18	

typedef char Tpalavra [20];

typedef struct Pessoa {
	
	Tpalavra nome;
	int idade;
	
	
} pessoa;

typedef struct ListaPessoas {
	
	
	pessoa pessoas[MAX];
	int num;
	
} listaPessoas;


// Funcao ler pessoas
int lerLista(listaPessoas *l);

// Funcao para apresentar pessoas
void escreverLista(listaPessoas *l);

// Funcao para ordenar por nomes
void ordenarLista(listaPessoas *l);

// Funcao para mostrar somente maiores de idade
void mostraMaiores(listaPessoas *l);

// Funcao para remover pessoas
int removePessoa(listaPessoas *l, Tpalavra *palavra);

// Funcao para adicionar pessoas
int inserePessoa(listaPessoas *l, pessoa *nova);

// Funcao auxiliar para remover
void shiftEsquerda(listaPessoas *l, int posicao);

// Funcao auxiliar para adicionar
void shiftDireita(listaPessoas *l, int posicao, int tam);

// Funcao auxiliar para verificar se lista esta cheia
bool listaCheia(listaPessoas *l);

// Funcao com opcoes
void opcao(listaPessoas *l, int op);

// Funcao menu opcoes 
int menu(void);

int menu(void) {
	
	int opt;
	printf("Escolha a opcao:\n");
	printf("\t0. Sair\n");
	printf("\t1. Exibir lista\n");
	printf("\t2. Exibir maiores\n");
	printf("\t3. Adicionar pessoa\n");
	printf("\t4. Remover pessoa\n");
	printf("Opcao: "); scanf("%d", &opt);
	
	return opt;
}


//Funcao que seleciona as opcoes
void opcao(listaPessoas *l, int op) {
	
	pessoa aux;
	
	if(op == 0){ // Sair
		return;
	}else if(op == 1){ // Apresenta
		escreverLista(l);
		
	}else if(op == 2){ // Apresenta maiores
		mostraMaiores(l);
		
	}else if(op == 3){ // Inserir
		printf("Digite o nome e a idade da pessoa: ");
		scanf("%s %d", aux.nome, &aux.idade);
		inserePessoa(l,&aux);
		
	}else if(op == 4){ // Remover
		printf("Digite o nome da pessoa: ");
		scanf("%s", aux.nome);
		removePessoa(l, &aux.nome);
		
	}else{
		printf("Opcao invalida\n");
	}
	
	return;
}

int main(int argc, char *argv[]){
	
	listaPessoas lista;
	int erro=0, opt=0;
	
	erro=lerLista(&lista);
	
	if(erro!=0){
		printf("Erro ao ler dados\n");
		exit(1);
	}
	
	ordenarLista(&lista);
	escreverLista(&lista);
	
	do{
		opt=menu();
		opcao(&lista,opt);
	}while(opt);//enquanto diferente de zero
	
	
	return 0;
}


int lerLista(listaPessoas *l){
	
	int i=0, erro=0;
	
	printf("Digite o numero de pessoas na lista: ");
	erro = scanf("%d", &l->num);
	
	if(erro!=1){
		return -1;
	}
	
	for(i=0;i<l->num;i++){
		printf("Digite o nome e a idade da pessoa: ");
		erro = scanf("%s %d", &l->pessoas[i].nome[0], &l->pessoas[i].idade);
		
		if(erro!=2){ // Quantidade de conversoes
			return -1;
		}
	}
	return 0;
}


void escreverLista(listaPessoas *l){
	
	int i=0;
	
	for(i=0;i<l->num;i++){
		
		printf("Pessoa %d - Nome: %s, %d\n",i, l->pessoas[i].nome, l->pessoas[i].idade);
		
	}
	
	return;
}

void ordenarLista(listaPessoas *l){
	
	pessoa aux;
	
	int i=0,n=0,min=0;
	
	//De fora dita a posicao do ordenado
	for(i=0;i<l->num-1;i++){ // Na ultima passagem ja vai estar ordenado
		
		for(n=i+1;n<l->num;n++){
			
			if(strcmp (l->pessoas[n].nome, l->pessoas[i].nome) == 1){
				min=n;
			}
		}
		
		aux = l->pessoas[i];
		l->pessoas[i] = l->pessoas[min];
		l->pessoas[min] = aux;
		
	}
	
	return;
}

void mostraMaiores(listaPessoas *l){
	
	int i=0;
	
	for(i=0;i<l->num;i++){
		if(l->pessoas[i].idade >= MAIORIDADE){
			printf("Pessoa %d - Nome: %s, %d\n",i, l->pessoas[i].nome, l->pessoas[i].idade);
		}
	}
	
	return;
}
	

int removePessoa(listaPessoas *l, Tpalavra *palavra){

	int i=0;
	int flag = -1;
	// Flag continua menos um se nao encontrar
	
	for(i=0;i<l->num;i++){
		
		if(strcmp (l->pessoas[i].nome, *palavra) == 0){
			
			// Faz shift pra esquerda se nao for a ultima posicao
			if(i!=l->num){
				shiftEsquerda(l,i);
			}
			l->num-=1;
			flag = 0;
			// REMOVER 1 no tamanho aqui
		}
	}
	
	return flag;
}
	

int inserePessoa(listaPessoas *l, pessoa *nova){
	
	int i=0;
	
	if(listaCheia(l)){
		return -1;
	}

	// Menor que primeiro
	if(strcmp (l->pessoas[0].nome, nova->nome) >= 0){
		shiftDireita(l, 0, l->num-1);
		l->pessoas[0] = *nova;
	// Maior que ultimo
	}else if(strcmp (l->pessoas[l->num-1].nome, nova->nome) <= 0){
		l->pessoas[l->num] = *nova;
	}else{
		for(i=0;i<l->num;i++){
			if(strcmp (l->pessoas[i].nome, nova->nome) <= 0){
				if(strcmp (l->pessoas[i+1].nome, nova->nome) >= 0){
					shiftDireita(l, i+1, l->num-1);
					l->pessoas[i+1] = *nova;
					break;
				}
			}
		}
	}

	// Altera tamanho
	l->num+=1;

	return 0;
}


void shiftEsquerda(listaPessoas *l, int posicao){

	l->pessoas[posicao] = l->pessoas[posicao+1];
	// Ate posicao menos um
	if(posicao+1 < l->num){
		shiftEsquerda(l,posicao+1);
	}
	
	return;
}

void shiftDireita(listaPessoas *l, int posicao, int tam){
	
	// Comecando na ultima posicao adianta todos
	l->pessoas[tam+1] = l->pessoas[tam];
	// Ate posicao menos um
	if(tam > posicao){
		shiftDireita(l,posicao,tam-1);
	}
	
	return;
}

	
bool listaCheia(listaPessoas *l){
	
	if(l->num == MAX){
		return true;
	}
	
	return false;
}

