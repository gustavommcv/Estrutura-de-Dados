#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int valor;
    struct no *proximo;
} No;

void inserir_na_fila(No **fila, int num) {
    No *aux, *novo = malloc(sizeof(No));

    if(novo) {
        novo->valor = num;
        novo->proximo = NULL;

        if (*fila == NULL) { // fila vazia
            *fila = novo;
        } else {
            aux = *fila;
            while(aux->proximo) {
                aux = aux->proximo;
            }
            aux->proximo = novo;
        }

    } else {
        printf("\nErro ao alocar memoria\n");
    }
}

No* remover_da_fila(No **fila) {
    No *remover = NULL;

    if(*fila) {
        remover = *fila;
        *fila = remover->proximo;
    } else {
        printf("\nFila vazia!\n");
    }
    return remover;
}

void imprimir(No *fila) {
    printf("\n-------- Fila --------\n");
    while(fila) {
        printf("%d ", fila->valor);
        fila = fila->proximo;
    }
    printf("\n------ Fim Fila ------\n");
}

int main(void) {
    No *r, *fila = NULL;
    int opcao, valor;

    do{
        printf("\n0 - Sair\n1 - Inserir\n2 - Remover\n3 - Imprimir\n");
        scanf("%d", &opcao);

        switch (opcao) {
        case 1:
            printf("Digite um valor: ");
            scanf("%d", &valor);
            inserir_na_fila(&fila, valor);
            break;
        
        case 2:
            r = remover_da_fila(&fila);
            if(r) {
                printf("Removido: %d\n", r->valor);
                free(r);
            }
            break;
        
        case 3:
            imprimir(fila);
            break;

        default:
            if(opcao != 0)
                printf("\nOpcao invalida!!!\n");
        }

    } while (opcao != 0);
    

    return 0;
}