#include <stdio.h>
#include <stdlib.h>

// =========================================================================================================================================== //

// Esta arvore possui um conteudo do tipo inteiro e os ponteiros para esq, dir;
typedef struct no {
    int conteudo;
    struct no *esquerda, *direita;
} NoArvore;

// =========================================================================================================================================== //

//Prototypes
NoArvore* inserirV1(NoArvore *no, int valor); // Retorna um novo endereco usando recursividade para a raiz / futuros nos;
void inserirV2(NoArvore **no, int valor); // Uma maneira mais eficiente de inserir valores
void inserirV3(NoArvore **raiz, int valor); // Mais eficiente (sem retorno e sem recursao) versao iterativa
void imprimir(NoArvore *raiz); // Partindo da raiz realiza as impressoes de todos os elementos no console;
void imprimirCrescente(NoArvore *raiz); // Imprime os elementos em ordem crescente;
void imprimirDecrescente(NoArvore *raiz); // Em ordem decrescente;
NoArvore* buscarV1(NoArvore *raiz, int valor); // Busca um elemento e retorna seu endereco
NoArvore* buscarV2(NoArvore *raiz, int valor); // Mais eficiente (sem recursao)
NoArvore* defaultArv(NoArvore *no); // Carrega valores pre definidos para a arvore
int alturaArv(NoArvore *raiz); // Descobre a altura da arvore
int tamanho(NoArvore *raiz); // Descobre o tamanho total de nos na arvore
void reset(NoArvore **raiz); // Reseta a arvore, usamos ponteiro para ponteiro pois se liberarmos a raiz e nao alterarmos o endereco onde ela aponta para NULL, teremos um erro de ponteiro invalido
int qndFolhas(NoArvore *raiz); // Mostra a quantidade de folhas na arvore
NoArvore* remover(NoArvore *raiz, int chave); //Remove um valor escolhido pelo usuario

// =========================================================================================================================================== //

int main(void) {

    NoArvore *raiz = NULL, *busca; // Nao tem nenhum elemento ainda;

    int opcao, op, valor;
    /*
    Aqui podemos
    - Sair do programa
    - Inserir um elemento pelo teclado
    - Imprimir a arvore de forma crescente, decrescente e a partir da raiz
    - Buscar se existe ou nao um elemento nesta arvore
    - Remover elementos
    - Carregar um preset padrao para testar a arvore
    */
    do {

        printf("\n1 - Inserir\n2 - Imprimir\n3 - Buscar\n4 - Remover\n5 - Altura \n6 - Tamanho\n7 - Folhas\n8 - Carregar preset para testes\n9 - Reset\n0 - Sair\n\n");
        scanf("%d", &opcao);

        switch (opcao) {
        case 0:
            printf("\nSaindo . . .\n");
            break;
        
        case 1:
            printf("\nQual valor deseja inserir? ");
            scanf("%d", &valor);

            // raiz = inserirV1(raiz, valor);
            //inserirV2(&raiz, valor);
            inserirV3(&raiz, valor);
            break;
        
        case 2:
            printf("\n1 - Imprimir\n2 - Imprimir Crescente\n3 - Imprimir Decrescente\n\n");
            scanf("%d", &op);

            switch (op) {
            case 1:
                printf("\nImpressao da arvore binaria:\n");
                if (raiz) {
                    imprimir(raiz);
                    printf("\n");
                    printf("Tamanho: %d\n", tamanho(raiz));
                    printf("Raiz: %d\n", raiz->conteudo);
                } else {
                    printf("NULL\n");
                }
                break;

            case 2:
                printf("\nImpressao da arvore binaria:\n");
                if (raiz) {
                    imprimirCrescente(raiz);
                    printf("\n");
                    printf("Tamanho: %d\n", tamanho(raiz));
                    printf("Raiz: %d\n", raiz->conteudo);
                } else {
                    printf("NULL\n");
                }
                break;

            case 3:
                printf("\nImpressao da arvore binaria:\n");
                if (raiz) {
                    imprimirDecrescente(raiz);
                    printf("\n");
                    printf("Tamanho: %d\n", tamanho(raiz));
                    printf("Raiz: %d\n", raiz->conteudo);
                } else {
                    printf("NULL\n");
                }
                
                break;
            
            default:
                printf("\nOpcao invalida!\n");
                break;
            }
            break;
        
        case 3:
            printf("\nQual valor deseja buscar? ");
            scanf("%d", &valor);
            //busca = buscarV1(raiz, valor);
            busca = buscarV2(raiz, valor);

            if (busca) {
                printf("\nValor encontrado: %d\n", busca->conteudo);
            } else {
                printf("\nValor nao encontrado!\n");
            }
            break;

        case 4:
            imprimirCrescente(raiz);
            printf("\nQual valor deseja remover? ");
            scanf("%d", &valor);
            raiz = remover(raiz, valor);
            break;

        case 5:
            if (alturaArv(raiz) == -1){
                printf("\nAltura: %d\n", 0);
            } else {
                printf("\nAltura: %d\n", alturaArv(raiz));
            }
            
            break;

        case 6:
            printf("\nQuantidade de nos: %d\n", tamanho(raiz));
            break;

        case 7:
            printf("\nQuantidade de folhas: %d\n", qndFolhas(raiz));
            break;

        case 8:
            printf("\nCarregando . . .\n");
            if (raiz) {
                printf("\nImpossivel carregar em uma arvore nao vazia!\n");
                break;
            }
            raiz = defaultArv(raiz);
            break;

        case 9:
            printf("\nApagando . . .\n");
            if (raiz == NULL) {
                printf("\nImpossivel apagar uma arvore vazia!\n");
                break;
            } else {
                reset(&raiz);
            }
            break;

        default:
            printf("\nOpcao invalida!\n");
            break;
        }
    } while(opcao != 0);

    return 0;
}

// =========================================================================================================================================== //

NoArvore* inserirV1(NoArvore *no, int valor) {
    if (no == NULL) { // Se a arvore nao possuir elemento nenhum . . .
        NoArvore *novo = (NoArvore*) malloc(sizeof(NoArvore)); // Alocamos memoria para um novo no;
        if (novo) { // Se conseguimos alocar memoria com sucesso . . .
            novo->conteudo = valor;
            novo->direita = NULL; 
            novo->esquerda = NULL; // Ainda nao possui nenhum elemento apontado, ja que estamos lidando com a raiz sozinha nesta condicao;
            return novo; // Retornamos este novo endereco;
        } else {
            printf("\nErro ao alocar memoria\n");
            return NULL;
        }
    } else { // Se a arvore possui pelo menos um elemento . . .
        // Chamada recursiva, o endereco 'no' passa a ser o no a esquerda, e so vai retornar um novo endereco para o elemento escolhido quando esta funcao chegar em um no folha;
        if (valor < no->conteudo) {
            no->esquerda = inserirV1(no->esquerda, valor); 
        }
        if (valor > no->conteudo) {
            no->direita = inserirV1(no->direita, valor);
        }
        return no;
    }
}

void inserirV2(NoArvore **raiz, int valor) {
    if (*raiz == NULL) { // O conteudo desde endereco eh nulo? (se vazia / *no == NULL)
        *raiz = malloc(sizeof(NoArvore)); // Colocando endereco diretamente na raiz
        (*raiz)->conteudo = valor;
        (*raiz)->direita = NULL;
        (*raiz)->esquerda = NULL;
    } else {
        if (valor < (*raiz)->conteudo) {
            inserirV2(&((*raiz)->esquerda), valor); // Demonio
        }

        if (valor > (*raiz)->conteudo) {
            inserirV2(&((*raiz)->direita), valor);
        }
    }
}

void inserirV3(NoArvore **raiz, int valor) {
    NoArvore *aux = *raiz;
    while(aux) {
        if(valor < aux->conteudo) {
            raiz = &aux->esquerda; //Variavel raiz local
        } else if (valor > aux->conteudo) {
            raiz = &aux->direita;
        } else {
            return; // Valor já existe na árvore, não faz nada
        }
        aux = *raiz;
    }
    aux = malloc(sizeof(NoArvore));
    aux->conteudo = valor;
    aux->direita = NULL;
    aux->esquerda = NULL;
    *raiz = aux;
}

void imprimir(NoArvore *raiz) {
    if (raiz) { // Se raiz existe . . .
        printf("%d ", raiz->conteudo);
        imprimir(raiz->esquerda);
        imprimir(raiz->direita);
    }
}

void imprimirCrescente(NoArvore *raiz) {
    if (raiz) {
        imprimirCrescente(raiz->esquerda);
        printf("%d ", raiz->conteudo);
        imprimirCrescente(raiz->direita);
    }
}

void imprimirDecrescente(NoArvore *raiz) {
    if (raiz) {
        imprimirDecrescente(raiz->direita);
        printf("%d ", raiz->conteudo);
        imprimirDecrescente(raiz->esquerda);
    }
}

NoArvore* buscarV1(NoArvore *raiz, int valor) {
    if (raiz) {
        if (valor == raiz->conteudo) {
            return raiz;
        } else if (valor < raiz->conteudo) {
            return buscarV1(raiz->esquerda, valor);
        } else {
            return buscarV1(raiz->direita, valor);
        }
    }
    return NULL;
}

NoArvore* buscarV2(NoArvore *raiz, int valor){
    while(raiz) {
        if (valor < raiz->conteudo) {
            raiz = raiz->esquerda;
        } else if (valor > raiz->conteudo) {
            raiz = raiz->direita;
        } else {
            return raiz;
        }
    }
    return NULL;
}

int alturaArv(NoArvore *raiz) { // 100 R500 700
    if (raiz == NULL) {
        return -1;
    } else {
        int esquerda = alturaArv(raiz->esquerda); // 0
        int direita = alturaArv(raiz->direita); //  0 + 1 == 1
        if (esquerda > direita) {
            return esquerda + 1;
        } else {
            return direita + 1;
        }
    }
}

int tamanho(NoArvore *raiz) { // 1 R50
    if (raiz == NULL) {
        return 0;
    } else {
        int tam = 1; // se nao eh nulo entao tem 1 elemento
        tam += tamanho(raiz->esquerda);
        tam += tamanho(raiz->direita);
        return tam;

        // return 1 + tamanho(raiz->esquerda) + tamanho(raiz->direita);

        // Operador ternario:
        // return (raiz == NULL) ? 0 : 1 + tamanho(raiz->esquerda) + tamanho(raiz->direita);
    }
}

int qndFolhas(NoArvore *raiz) {
    int tam = 0;
    if (raiz == NULL) {
        return 0;
    } else {
        if (raiz->esquerda == NULL && raiz->direita == NULL) {
            return 1;
        } else {
            tam += qndFolhas(raiz->direita);
            tam += qndFolhas(raiz->esquerda);
            return tam;

            // return qndFolhas(raiz->esquerda) + qndFolahs(raiz->direita);
        }
    }
}

NoArvore* remover(NoArvore *raiz, int chave) {
    if (raiz == NULL) {
        printf("Valor nao encontrado!\n");
        return NULL;
    } else {
        // Achou o conteudo a ser removido
        if (raiz->conteudo == chave) {
            // Remove nos folhas
            if (raiz->esquerda == NULL && raiz->direita == NULL) {
                free(raiz);
                printf("\nElemento folha removido: %d!\n", chave);
                return NULL;
            } else {
                // Remove nos que possuem 2 filhos
                if (raiz->esquerda != NULL && raiz->direita != NULL) {
                    NoArvore *aux = raiz->esquerda;
                    while (aux->direita != NULL) {
                        aux = aux->direita;
                    }
                    raiz->conteudo = aux->conteudo;
                    aux->conteudo = chave;
                    printf("Elemento trocado: %d!", chave);
                    raiz->esquerda = remover(raiz->esquerda, chave);
                    return raiz;
                } 
                // Remove nos com apenas 1 filho
                else {
                    NoArvore *aux;
                    if (raiz->esquerda != NULL) {
                        aux = raiz->esquerda;
                    } else {
                        aux = raiz->direita;
                    }
                    free(raiz);
                    printf("\nElemento com 1 filho removido: %d!\n", chave);
                    return aux;
                }
            }
        } else { // Procura o elemento a ser removido
            if (chave < raiz->conteudo) {
                raiz->esquerda = remover(raiz->esquerda, chave);
            } else {
                raiz->direita = remover(raiz->direita, chave);
            }
            return raiz; // Retorna este elemento
        }
    }
}

NoArvore* defaultArv(NoArvore *no) {
    no = inserirV1(no, 500);
    no = inserirV1(no, 250);
    no = inserirV1(no, 799);
    no = inserirV1(no, 187);
    no = inserirV1(no, 315);
    no = inserirV1(no, 570);
    no = inserirV1(no, 900);
    no = inserirV1(no, 190);
    no = inserirV1(no, 800);
    no = inserirV1(no, 215);

    return no;
}

void reset(NoArvore **raiz) {
    if (*raiz) {
        reset(&(*raiz)->direita);
        reset(&(*raiz)->esquerda);

        printf("Liberando no: %d\n", (*raiz)->conteudo);
        free(*raiz);
        *raiz = NULL; // Atualiza o ponteiro da raiz para NULL após liberar a memória
    }
}

