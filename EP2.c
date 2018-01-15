#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include <string.h>
//Typedef e struct que serão padrão para fila e pilha
typedef struct noh Lista;

struct noh {
    char simbolo;
    Lista *prox;
};

//Pega um elemento 's' e enfileira na fila 'f'
void queue (Lista **f, char s) {
    Lista *novo = (Lista *)malloc(sizeof(Lista));
    Lista *aux;

    novo->simbolo = s;
    novo->prox = NULL;

    if ((*f) == NULL)
        *f = novo;
    else {
        aux = *f;
        while (aux->prox != NULL)
            aux = aux->prox;
        aux->prox = novo;
    }
}

//Pega o elemento 's' e empilha na pilha 'p'
void push (Lista **p, char s) {
    Lista *novo =  (Lista *)malloc(sizeof(Lista));
    novo->simbolo = s;

    if ((*p) == NULL)
        novo->prox = NULL;
    else
        novo->prox = (*p);

    (*p) = novo;
}

//Desempilha um elemento da pilha 'p'
char pop (Lista **p) {
    Lista *aux = *p;
    char temp = aux->simbolo;
    *p = (*p)->prox;
    free(aux);
    return temp;
}

//Imprimir quando não há parenteses externos
void imprimir (Lista *p) {
    Lista *aux = p;

    while (aux != NULL) {
        printf("%c", aux->simbolo);
        aux = aux->prox;
    }
}

//Imprimir quando há parenteses externos
void imprimirPre (Lista *p) {
    Lista *aux = p->prox;

    while (aux->prox != NULL) {
        printf("%c", aux->simbolo);
        aux = aux->prox;
    }
}

//Recebe uma pilha 'p' e devolve o valor no topo
char top (Lista *p) {
    return p->simbolo;
}

//Função que verifica qual operador tem maior precedência. Devolve 0 se forem iguais,
//-1 caso op1 tiver menor precedência que op2 e 1 se maior.
int precedencia (char op1, char op2) {
    if ((op1 == '+' || op1 == '-') && (op2 == '+' || op2 == '-'))
        return 0;
    else if ((op1 == '*' || op1 == '/') && (op2 == '*' || op2 == '/'))
        return 0;
    else if ((op1 == '*' || op1 == '/') && (op2 == '+' || op2 == '-'))
        return 1;
    else if ((op1 == '+' || op1 == '-') && (op2 == '*' || op2 == '/'))
        return -1;
}

//Verifica se a pilha está vazia
int pilhaVazia (Lista *p) {
    if (p == NULL) return 0;
    return 1;
}

//O nosso algoritmo para transformar infixa para prefixa, exige a inversão da
//expresso aritmética de entrada. Além disso, precisamos trocar ')' por '(' e '(' por ')'.
void reverterExp (Lista **exp, Lista **expRev) {
    Lista *aux = *exp;

    push(&(*expRev), ')');
    while (aux != NULL) {
        if (aux->simbolo == '(')
            push(&(*expRev), ')');
        else if (aux->simbolo == ')')
            push(&(*expRev), '(');
        else
            push(&(*expRev), aux->simbolo);
        aux = aux->prox;
    }
    push(&(*expRev), '(');
}

//Recebe uma expressão aritmética infixa chamada 'entrada', faz a sua leitura e devolve uma
//expressão posfixa em 'saida'. A lista 'operadores' é auxiliar para os operandos.
//A ideia do algoritmo é baseada no algoritmo Shunting Yard
//https://brilliant.org/wiki/shunting-yard-algorithm/
void InfixToPosfix (Lista **entrada, Lista **saida, Lista **operadores) {
    char buffer;
    while (*entrada!=NULL) {
        buffer = pop(&(*entrada));

        if ((buffer >= 'a' && buffer <= 'z') || (buffer >= 'A' && buffer <= 'Z')) {
            queue(&(*saida), buffer);
        }
        if ((buffer == '+') || (buffer == '-') || (buffer == '*') || (buffer == '/')) {
            while (pilhaVazia((*operadores)) == 1 && (precedencia(top(*operadores), buffer) == 0 || precedencia(top(*operadores), buffer) == 1) && top(*operadores) != '(') {
                queue(&(*saida), pop(&(*operadores)));
            }
            push(&(*operadores), buffer);
        }
        if (buffer == '(')
            push(&(*operadores), buffer);
        if (buffer == ')') {
            while (top((*operadores)) != '(') {
                queue(&(*saida), pop(&(*operadores)));
            }
            pop(&(*operadores));
        }
    }

    while ((*operadores) != NULL) {
        queue(&(*saida), pop(&(*operadores)));
    }
}

//Limpa a Lista 'l' para que possa receber uma nova expressão aritmética.
void limparLista (Lista **l) {
    Lista *aux;

    while (*l != NULL) {
        aux = *l;
        (*l) = (*l)->prox;
        free(aux);
    }

    (*l) == NULL;
}

int main() {
    Lista *entrada = NULL;
    Lista *entradaRev = NULL;
    Lista *saida = NULL;
    Lista *operadores = NULL;
    char buffer[100];
    char opcao;
    int i;

    printf("Digite a opção desejada: \n");
    printf("0 - Digitar uma expressão de entrada e limpar listas: \n");
    printf("1 - INFIXA para POSFIXA: \n");
    printf("2 - INFIXA para PREFIXA: \n");
    printf("x - Para sair \n");
    scanf(" %c", &opcao);

    while (opcao != 'x' && opcao != 'X') {
        switch (opcao) {
            case '0':
                i = 0;
                limparLista(&entrada);
                limparLista(&entradaRev);
                limparLista(&saida);
                limparLista(&operadores);
                printf("\nDigite a expressão matemática: \n");
                scanf("%s", buffer);
                while (buffer[i] != '\0') {
                    queue(&entrada, buffer[i]);
                    i++;
                    //scanf(" %c", &buffer);
                }
                printf("Expressão matemática digitada: \n");
                imprimir(entrada);
            break;
            case '1':
                InfixToPosfix(&entrada, &saida, &operadores);
                printf("\nPosfixa: ");
                imprimir(saida);
                printf("\n");
            break;
            //Para transformar INFIXA para PREFIXA, nós fazemos a leitura da expressão de entrada
            //invertemos a ordem, por exemplo, A+B se torna B+A. Depois, aplicamos a mesma função de
            //Infixa para posfixa. Por fim, nós tornamos a inverter a saída, para ficar na forma PREFIXA
            //http://scanftree.com/Data_Structure/infix-to-prefix
            case '2':
                reverterExp(&entrada, &entradaRev);
                entrada = entradaRev;
                InfixToPosfix(&entrada, &saida, &operadores);
                printf("\nPrefixa: ");
                entradaRev = NULL;
                reverterExp(&saida, &entradaRev);
                imprimirPre(entradaRev);
                printf("\n");
            break;
            default:
                printf("\nOpção Inválida\n");
            break;
        }
        printf("\nDigite novamente uma opção: \n");
        printf("0 - Digitar uma expressão de entrada e limpar listas: \n");
        printf("1 - INFIXA para POSFIXA: \n");
        printf("2 - INFIXA para PREFIXA: \n");
        printf("x - Para sair \n");
        scanf(" %c", &opcao);
    }

    printf("\nSaida final:\n");
    limparLista(&saida);
    imprimir(saida);

    return 0;
}
