
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include <string.h>

typedef struct noh arvore;
typedef struct lista fila;
typedef struct treeStack stack;

//Estrutura da árvore
struct noh {
    char valor;
    arvore *esq;
    arvore *dir;
};
//Estrura da fila que lẽ a espressão aritmética
struct lista {
    char simbolo;
    fila *prox;
};
//Estrutura que empilha subarvores
struct treeStack {
    arvore *t;
    stack *prox;
};

//Inserir uma subarvore na pilha
void inserirStack (arvore **subtree, stack **s) {
    stack *nova = (stack *)malloc(sizeof(stack));

    nova->t = *subtree;
    if (*s == NULL)
        nova->prox = NULL;
    else
        nova->prox = *s;

    *s = nova;

}
//Desempilha uma subarvore
arvore *desempilhar (stack **s) {
    stack *aux = *s;
    arvore *temp;
    temp = aux->t;
    *s = (*s)->prox;
    free(aux);

    return temp;
}
//Inserir na """fila""" que faz a leitura da expressão, na verdade é uma pilha
void inserirFila (fila **f, char c) {
    fila *nova = (fila *)malloc(sizeof(fila));

    nova->simbolo = c;

    if (*f == NULL)
        nova->prox = NULL;
    else
        nova->prox = *f;

    *f = nova;
}
//Cria uma folha para a árvore
arvore *criarFolha (char c) {
    arvore *nova = (arvore *)malloc(sizeof(arvore));

    nova->valor = c;
    nova->esq = NULL;
    nova->dir = NULL;

    return nova;
}
//Cria um noh em uma árvore, com filhos 'esq' e 'dir' e pai 'c'
arvore *criaNoh (arvore **esq, arvore **dir, char c) {
    arvore *nova = (arvore *)malloc(sizeof(arvore));

    nova->valor = c;
    nova->esq = *esq;
    nova->dir = *dir;

    return nova;
}
//Recebe uma árvore e uma fila e começa a montar a árvore
arvore *inserir (arvore *t, fila *f) {
    arvore *no = NULL;
    arvore *e = NULL;
    arvore *d = NULL;
    fila *aux = f;
    stack *stackTree = NULL;
    char buffer;

    while (aux != NULL) {
        buffer = aux->simbolo;
        //se o 'buffer' for um operando, criamos uma folha e empilhamos
        if ((buffer >= 'a' && buffer <= 'z') || (buffer >= 'A' && buffer <= 'Z')) {
            no = criarFolha(buffer);
            inserirStack(&no, &stackTree);
        }
        //Se for um operador, nós desempilhamos 2 itens da pilha que serão os filhos 'esq' e 'dir'
        //criamos um 'noh' com o operador como para e 'esq' e 'dir' como filhos, em seguida empilhamos a subarvore
        if ((buffer == '+') || (buffer == '-') || (buffer == '*') || (buffer == '/')) {
            d = desempilhar(&stackTree);
            e = desempilhar(&stackTree);
            no = criaNoh(&d, &e, buffer);
            inserirStack(&no, &stackTree);
        }

        aux = aux->prox;
    }

    //No fim das iterações, só devemos ter um elemento na pilha que  a árvore completa
    return desempilhar(&stackTree);
}


arvore *inserir2 (arvore *t, fila *f) {
    arvore *no = NULL;
    arvore *e = NULL;
    arvore *d = NULL;
    fila *aux = f;
    stack *stackTree = NULL;
    char buffer;

    while (aux != NULL) {
        buffer = aux->simbolo;
        //se o 'buffer' for um operando, criamos uma folha e empilhamos
        if ((buffer >= 'a' && buffer <= 'z') || (buffer >= 'A' && buffer <= 'Z')) {
            no = criarFolha(buffer);
            inserirStack(&no, &stackTree);
        }
        //Se for um operador, nós desempilhamos 2 itens da pilha que serão os filhos 'esq' e 'dir'
        //criamos um 'noh' com o operador como para e 'esq' e 'dir' como filhos, em seguida empilhamos a subarvore
        if ((buffer == '+') || (buffer == '-') || (buffer == '*') || (buffer == '/')) {
            e = desempilhar(&stackTree);
            d = desempilhar(&stackTree);
            no = criaNoh(&d, &e, buffer);
            inserirStack(&no, &stackTree);
        }

        aux = aux->prox;
    }

    //No fim das iterações, só devemos ter um elemento na pilha que  a árvore completa
    return desempilhar(&stackTree);
}
//Funções comuns de impresso de arvore PreOrder, InOrder e PosOrder
void pesquisaPreOrder (arvore *t) {
    arvore *aux = t;

    if (aux != NULL) {
        printf("%c ", aux->valor);
        pesquisaPreOrder(aux->esq);
        pesquisaPreOrder(aux->dir);
    }
}


void pesquisaInOrder (arvore *t) {
    arvore *aux = t;

    if (aux != NULL) {
        pesquisaInOrder(aux->esq);
        printf("%c ", aux->valor);
        pesquisaInOrder(aux->dir);
    }
}

void pesquisaPosOrder (arvore *t) {
    arvore *aux = t;

    if (aux != NULL) {
        pesquisaPosOrder(aux->esq);
        pesquisaPosOrder(aux->dir);
        printf("%c ", aux->valor);
    }
}

void inserirRev (fila **l, char c) {
    fila *novo = (fila *)malloc(sizeof(fila));
    fila *aux = *l;

    novo->simbolo = c;
    novo->prox = NULL;
    if (aux == NULL)
        *l = novo;
    else {
        while (aux->prox != NULL)
            aux = aux->prox;
        aux->prox = novo;
    }
}

void reverterExp (fila **exp, fila **expRev) {
    fila *aux = *exp;

    while (aux != NULL) {
        inserirFila(&(*expRev), aux->simbolo);
        aux = aux->prox;
    }

    printf("\nInvetida\n");
}

void limparLista (fila **l) {
    fila *aux;

    while (*l != NULL) {
        aux = *l;
        (*l) = (*l)->prox;
        free(aux);
    }

    (*l) == NULL;
}

void imprimir (fila *l) {
    fila *aux = l;

    while (aux != NULL) {
        printf("%c ", aux->simbolo);
        aux = aux->prox;
    }
    printf("***");
}

int main() {
    arvore *t = NULL;
    arvore *t2 = NULL;
    fila *queue = NULL;
    fila *queueRev = NULL;
    int i = 0;

    char expressao[100];

    printf("Digite a expressão aritmética em Pre Order (Não use espaços entre operadores e operandos): \n");
    scanf("%s", expressao);
    printf("Expressão aritmética passada: %s", expressao);
    while (expressao[i] != '\0') {
        inserirFila(&queue, expressao[i]);
        i++;
    }

    t = inserir(t, queue);

    printf("\nInorder: \n");
    pesquisaInOrder(t);

    printf("\nPreorder: \n");
    pesquisaPreOrder(t);

    printf("\nPosorder: \n");
    pesquisaPosOrder(t);

    limparLista(&queue);

    printf("\nDigite a expressão aritmética em Pos Order (Não use espaços entre operadores e operandos): \n");
    scanf("%s", expressao);
    printf("Expressão aritmética passada: %s", expressao);

    i = 0;
    while (expressao[i] != '\0') {
        inserirFila(&queue, expressao[i]);
        i++;
    }


    reverterExp(&queue, &queueRev);
    //imprimir(queueRev);
    t2 = inserir2(t, queueRev);

    printf("\nInorder: \n");
    pesquisaInOrder(t2);

    printf("\nPreorder: \n");
    pesquisaPreOrder(t2);

    printf("\nPosorder: \n");
    pesquisaPosOrder(t2);


    return 0;
}
