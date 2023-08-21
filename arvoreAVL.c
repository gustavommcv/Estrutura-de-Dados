#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int valor;
    struct no *esquerdo, *direito;
    short altura;
} No;

No* novoNo(int x); // Funcao que cria um novo no / x == valor a ser inserido / return o endereco do novoNo
short maior (short a, short b); // Retorna o maior dentro dois valores / a, b -> altura de dois nos da arvore
short alturaDoNo(No *no); // Retorna a altura de um no ou -1 caso ele seja NULL
short fatorDeBalanceamento(No *no); // Calcula e retorna o fator de balanceamento de um no
No* balancear(No *raiz); // Recebe o no desbalanceado e retorna a nova raiz balanceada (Ocorre sempre depois de uma insercao ou remocao)
No *inserir(No *raiz, int x); // Insere novo no na arvore / retorna o endereco do novo no ou nova raiz apos o balanceamento
No* remover(No *raiz, int chave); // Remove um no da arvore / retornamos a raiz pois pode ser necessario o balanceamento
void imprimir(No *raiz, int nivel); // Imprime todos os nos da arvore
No* seed(No *no); // Carrega valores pre definidos para a arvore
// Rotacoes
No* rotacaoEsquerda(No *r);
No* rotacaoDireita(No *r);
No* rotacaoEsquerdaDireita(No *r);
No* rotacaoDireitaEsquerda(No *r);

int main() {
    int op, valor;
    No *raiz = NULL;

    do {
        printf("\n\n\t0 - Sair\n\t1 - Inserir\n\t2 - Remover\n\t3 - Imprimir\n\t4 - Carregar arvore\n");
        scanf("%d", &op);

        switch (op) {
        case 0:
            printf("\n\tSaindo . . .\n");
            break;
        
        case 1:
            printf("\n\tDigite um valor a ser inserido: ");
            scanf("%d", &valor);
            raiz = inserir(raiz, valor);
            break;
        
        case 2:
            printf("\n\tDigite um valor a ser removido: ");
            scanf("%d", &valor);
            raiz = remover(raiz, valor);
            break;
            
        case 3:
            imprimir(raiz, 1);
            break;

        case 4:
            raiz = seed(raiz);
            break;

        default:
            printf("\n\tOpcao invalida\n");
            break;
        }
    } while(op != 0);
        
    return 0;
}

No* novoNo(int x) {
    No *novo = malloc(sizeof(No));

    if (novo) {
        novo->valor = x;
        novo->esquerdo = NULL;
        novo->direito = NULL;
        novo->altura = 0;
    } else {
        printf("\n\tErro ao alocar no em novoNo()!\n");
    }

    return novo;
}

short maior (short a, short b) {
    return (a > b) ? a: b;
}

short alturaDoNo(No *no) {
    if (no == NULL) {
        return -1;
    } else {
        return no->altura;
    }
}

short fatorDeBalanceamento(No *no) {
    if (no) {
        return (alturaDoNo(no->esquerdo) - alturaDoNo(no->direito));
    } else {
        return 0;
    }
}

No* rotacaoEsquerda(No *r) {
    No *y, *f;

    y = r->direito;
    f = y->esquerdo;

    y->esquerdo = r;
    r->direito = f;

    r->altura = maior(alturaDoNo(r->esquerdo), alturaDoNo(r->direito)) + 1;
    y->altura = maior(alturaDoNo(y->esquerdo), alturaDoNo(y->direito)) + 1;

    return y;
}

No* rotacaoDireita(No *r) {
    No *y, *f;

    y = r->esquerdo;
    f = y->direito;
    
    y->direito = r;
    r->esquerdo = f;

    r->altura = maior(alturaDoNo(r->esquerdo), alturaDoNo(r->direito)) + 1;
    y->altura = maior(alturaDoNo(y->esquerdo), alturaDoNo(y->direito)) + 1;

    return y;
}

No* rotacaoEsquerdaDireita(No *r) {
    r->esquerdo = rotacaoEsquerda(r->esquerdo);
    return rotacaoDireita(r);
}

No* rotacaoDireitaEsquerda(No *r) {
    r->direito = rotacaoDireita(r->direito);
    return rotacaoEsquerda(r);
}

No* balancear(No *raiz) {
    short fb = fatorDeBalanceamento(raiz);

    // Rotacao a esquerda
    if (fb < -1 && fatorDeBalanceamento(raiz->direito) <= 0) {
        raiz = rotacaoEsquerda(raiz);
    } 
    // Rotacao a direita
    else if (fb > 1 && fatorDeBalanceamento(raiz->esquerdo) >= 0) {
        raiz = rotacaoDireita(raiz);
    }
    // Rotacao dupla a esquerda
    else if (fb > 1 && fatorDeBalanceamento(raiz->esquerdo) < 0) {
        raiz = rotacaoEsquerdaDireita(raiz);
    }
    // Rotacao dupla a direita
    else if (fb < -1 && fatorDeBalanceamento(raiz->direito) > 0) {
        raiz = rotacaoDireitaEsquerda(raiz);
    }

    return raiz;
}

No *inserir(No *raiz, int x) {
    if (raiz == NULL) { // Arvore vazia
        return novoNo(x);
    } else {
        if (x < raiz->valor) {
            raiz->esquerdo = inserir(raiz->esquerdo, x);
        } else if (x > raiz->valor) {
            raiz->direito = inserir(raiz->direito, x);
        } else {
            printf("\n\tInsercao nao realizada!\n\tO elemento %d ja existe!\n", x);
        }
    }

    // Recalcula a altura de todos os nos entre a raiz e o novo no inserido
    raiz->altura = maior(alturaDoNo(raiz->esquerdo), alturaDoNo(raiz->direito)) +1;

    // Verifica a necessidade de rebalancear a arvore
    raiz = balancear(raiz);

    return raiz;
}

No* remover(No *raiz, int chave) {
    if (raiz == NULL) {
        printf("Valor nao encontrado!\n");
    } else { // Procura no a remover
        if(raiz->valor == chave) {
            // Remove nos folhas
            if(raiz->esquerdo == NULL && raiz->direito == NULL) {
                free(raiz);
                printf("\n\tElemento folha removido: %d!\n", chave);
                return NULL;
            } else {
                // Remove nos que possuem 2 filhos
                if (raiz->esquerdo != NULL && raiz->direito != NULL) {
                    No *aux = raiz->esquerdo;
                    while (aux->direito != NULL) {
                        aux = aux->direito;
                    }
                    raiz->valor = aux->valor;
                    aux->valor = chave;
                    printf("\n\tElemento trocado: %d!\n", chave);
                    raiz->esquerdo = remover(raiz->esquerdo, chave);

                    return raiz;
                } else {
                    // Remove nos que possuem apenas 1 filho
                    No *aux;
                    if (raiz->esquerdo != NULL) {
                        aux = raiz->esquerdo;
                    } else {
                        aux = raiz->direito;
                    }
                    free(raiz);
                    printf("\n\tElemento com 1 filho removido: %d!\n", chave);
                    return aux;
                }
            }
        } else {
            if (chave < raiz->valor) {
                raiz->esquerdo = remover(raiz->esquerdo, chave);
            } else {
                raiz->direito = remover(raiz->direito, chave);
            }
        }

        // Recalcula a altura de todos os nos entre a raiz e o novo no inserido
        raiz->altura = maior(alturaDoNo(raiz->esquerdo), alturaDoNo(raiz->direito)) +1;

        // Verifica a necessidade de rebalancear a arvore
        raiz = balancear(raiz);

        return raiz;
    }
}

void imprimir(No *raiz, int nivel) {
    int i;
    if (raiz) {
        imprimir(raiz->direito, nivel + 1);
        printf("\n\n");

        for (i = 0; i < nivel; i++) {
            printf("\t");
        }

        printf("%d", raiz->valor);
        imprimir(raiz->esquerdo, nivel + 1);
    }
}

No* seed(No *no) {
    no = inserir(no, 500);
    no = inserir(no, 250);
    no = inserir(no, 799);
    no = inserir(no, 187);
    no = inserir(no, 315);
    no = inserir(no, 570);
    no = inserir(no, 900);
    no = inserir(no, 190);
    no = inserir(no, 800);
    no = inserir(no, 215);

    return no;
}