#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX 50

typedef struct no Noh;
typedef struct cabeca Cabeca;

/* Cole��o de n�s com os nomes de cada crin�a */
struct no {
	char nome[MAX];
	Noh *prox;
};

/* N� cabe�a, guarda o n�mero de crian�a em cada cadeira */
struct cabeca {
	int nelementos;
	Noh *cadeiras;
};

//Inicializa o n� cabe�a
void inicializaCabeca (Cabeca **c) {
	*c = (Cabeca *)malloc(sizeof(Cabeca));
	(*c)->nelementos = 0;
	(*c)->cadeiras = NULL;
}

//Insere as crian�as em um n� circular
void inserirCrianca (Cabeca **c, char n[]) {
	Noh *novo = (Noh *)malloc(sizeof(Noh));
l	Noh *aux;
	strcpy(novo->nome, n);
	novo->prox=(*c)->cadeiras;
	(*c)->nelementos++;

	if ((*c)->cadeiras == NULL) {
		(*c)->cadeiras = novo;
		novo->prox = novo;
	}
	else {
		aux = (*c)->cadeiras;
		while (aux->prox != (*c)->cadeiras)
			aux = aux->prox;
		aux->prox = novo;
		novo->prox = (*c)->cadeiras;
	}
}

//Sorteia uma posi��o ao acaso
int sorteio (int N) {
	return rand()%(N + 1);
}

//Imprimi a lista circular atualizada
void imprimir (Cabeca *c) {
	Noh *aux = c->cadeiras;
	int i;


	for (i = 0; i < c->nelementos; i++) {
		printf("%s\n", aux->nome);
		aux = aux->prox;
	}
}

//Remover as crian�as uma a uma
//Ainda INCOMPLETA
void removerCrianca (Cabeca **c) {
	Noh *aux;
	int pos, i = 1;

	if ((*c)->nelementos==1)
		(*c)->cadeiras == NULL;
	else {
		pos = sorteio ((*c)->nelementos);
		if (pos == 1) {

		}
	}

	(*c)->nelementos--;
	
	
}

int main (void) {
	Cabeca *criancas = NULL;
	char n[MAX];

	inicializaCabeca(&criancas);
	inserirCrianca(&criancas, "Mauricio");
	imprimir(criancas);

	printf("\nDigite o nome da crianca, 'fim' encerra a leitura: ");
	scanf("%s", n);

	while (strcmp(n, "fim") != 0) {

		inserirCrianca(&criancas, n);
	 	imprimir(criancas);

	 	printf("\nDigite o nome da crianca, 'fim' encerra a leitura: ");
		scanf("%s", n);
	}



	printf("Vamos iniciar a brincadeira!");

	while (criancas->nelementos!=0) {
		if (criancas->nelementos==1)
			printf("\nA crian�ca vencedora eh: %s\n", criancas->cadeiras->nome);
			//removerCrianca(&criancas);
	}

    return 0;
}

