#include <stdio.h>
#include <stdlib.h>

typedef struct no{
    int valor;
    struct no *proximo;
}No;

void inserir_no_inicio(No **lista, int num) {
    No *novo = malloc(sizeof(No));

    if(novo) {
        novo->valor = num;
        novo->proximo = *lista;
        *lista = novo;
    } else {
        printf("\nErro ao alocar memoria\n");
    }
}

void inserir_no_fim(No **lista, int num) {
    No *novo = malloc(sizeof(No));

    if(novo) {
        novo->valor = num;
        novo->proximo = NULL;
        
        //eh o primeiro?
        if(*lista == NULL) {
            *lista = novo;
        } else { //senao
            No *aux = *lista;
            while (aux->proximo){
                aux = aux->proximo;
            }
            aux->proximo = novo;
        }

    } else {
        printf("\nErro ao alocar memoria\n");
    }
}

void inserir_no_meio(No **lista, int num, int ant) {
    No *novo = malloc(sizeof(No));

    if(novo) {
        novo->valor = num;
        // eh o primeiro?
        if (*lista == NULL) {
            novo->proximo = NULL;
            *lista = novo;
        } else {
            No *aux = *lista;
            while(aux->valor != ant && aux->proximo) {
                aux = aux->proximo;
            }
            novo->proximo = aux->proximo;
            aux->proximo = novo;
        }

    } else {
        printf("\nErro ao alocar memoria\n");
    }
}

void imprimir(No *lista) {
    printf("\nLista: ");
    while(lista) {
        printf("%d ", lista->valor);
        lista = lista->proximo;
    }
    printf("\n\n");
}

int main() {

    No *lista = NULL;

    int opcao, valor, anterior;
    do{
        printf("\n0 - Sair\n1 - Inserir no Inicio\n2 - Inserir no Fim\n3 - Inserir no Meio\n4 - Imprimir\n\n");
        scanf("%d", &opcao);

        switch (opcao) {
        case 1:
            printf("\nDigite um valor: ");
            scanf("%d", &valor);
            inserir_no_inicio(&lista, valor);
            break;

        case 2:
            printf("\nDigite um valor: ");
            scanf("%d", &valor);
            inserir_no_fim(&lista, valor);
            break;

        case 3:
            printf("\nDigite o valor a ser inserido: ");
            scanf("%d%d", &valor, &anterior);
            printf("\nDigite um valor e o valor de referencia: ");
            inserir_no_meio(&lista, valor, anterior);
            break;

        case 4:
            imprimir(lista);
            break;

        default:
            if(opcao != 0)
                printf("\nOpcao invalida!!!\n");
        }

    } while (opcao != 0);

    return 0;
}
