#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int matriz [7][7];
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            matriz [i][j] = rand() % 100;
        }

    }
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");

    }

    //ordenação
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            if (matriz[j][j] > matriz[j + 1][j + 1]) {
                int aux = matriz[j][j];
                matriz[j][j] = matriz[j + 1][j + 1];
                matriz[j + 1][j + 1] = aux;
            }
        }
    }
    printf("\n");
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");

    }
    // árvore

    typedef struct No {
        int dado;
        struct No* direita;
        struct No* esquerda;
    } No;

    No * criarArvore() {
        return NULL;
    }

    int NoVazio(No * raiz) {
        return raiz == NULL;
    }

    void exibirNo(No * raiz) {

        if (!NoVazio(raiz)) {
            printf("%p<-%d(%p)->%p\n", raiz->esquerda, raiz->dado, raiz, raiz->direita);
            exibirNo(raiz->esquerda);
            exibirNo(raiz->direita);
        }
    }

    void inserirDado(No** raiz, int dado) {

        if (*raiz == NULL) {
            *raiz = (No*) malloc(sizeof (No));
            (*raiz)->esquerda = NULL;
            (*raiz)->direita = NULL;
            (*raiz)->dado = dado;
        } else {
            if (dado < (*raiz)->dado) {

                inserirDado(&(*raiz)->esquerda, dado);
            }
            if (dado > (*raiz)->dado) {

                inserirDado(&(*raiz)->direita, dado);
            }
        }
    }

    int getValor(No** no) {
        if ((*no) != NULL) {
            return (*no)->dado;
        }
    }

    void gerarArquivoDot(FILE** arquivoDot, No * raiz) {
        if (raiz != NULL) {
            char s1[20];
            char s2[20];
            if (getValor(&raiz->esquerda) != 0) {
                sprintf(s1, "%d:sw->%d [ label=\"esq\"];\n", raiz->dado, getValor(&raiz->esquerda));
                fprintf((*arquivoDot), "%s", s1);
            }
            if (getValor(&raiz->direita) != 0) {
                sprintf(s2, "%d:se->%d [ label=\"dir\"];\n", raiz->dado, getValor(&raiz->direita));
                fprintf((*arquivoDot), "%s", s2);
            }
            gerarArquivoDot(arquivoDot, raiz->esquerda); //esquerda (subNo)
            gerarArquivoDot(arquivoDot, raiz->direita); //direita (subNo)
        }
    }

    printf("\n");
    No*raiz = criarArvore(); // Criação da Árvore 

    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            if (matriz[i][j] > matriz[i + 1][j + 1]) {
                inserirDado(&raiz, matriz[i + 1][j + 1]);
            }
        }
    }
    exibirNo(raiz);

    FILE* arquivoDot;
    arquivoDot = fopen("arvore.dot", "w");
    fprintf(arquivoDot, "%s", "digraph G {\nsplines=line;\n");
    gerarArquivoDot(&arquivoDot, raiz);
    fprintf(arquivoDot, "%s", "}\n");
    fclose(arquivoDot);
    free(raiz);
    system("dot -Tpng arvore.dot -o arvore.png");

    return 0;


}
