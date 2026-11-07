#include <stdio.h>
#include "bst.h"

int main(void) {
    // inteiros
    int numeros[] = {50, 30, 70, 20, 40, 60, 80};
    No *raiz = NULL;

    for (int i = 0; i < 7; i++) raiz = bst_inserir(raiz, &numeros[i], comparar_inteiro);

    printf("Em ordem: "); bst_em_ordem(raiz, imprimir_inteiro);    printf("\n");
    printf("Decrescente: "); bst_decrescente(raiz, imprimir_inteiro); printf("\n");
    printf("Elementos: %d | Altura: %d\n", bst_contar(raiz), bst_altura(raiz));

    int busca = 40;
    printf("Buscar 40: %s\n", bst_buscar(raiz, &busca, comparar_inteiro) ? "achou" : "nao achou");

    int alvo = 50;
    raiz = bst_remover(raiz, &alvo, comparar_inteiro);
    printf("Sem o 50: "); bst_em_ordem(raiz, imprimir_inteiro);    printf("\n");

    bst_limpar(raiz);
    raiz = NULL;

    // strings (ignora maiúsculas/minúsculas) 
    char *nomes[] = {"Raul", "Fulano", "Ciclano"};
    for (int i = 0; i < 3; i++) raiz = bst_inserir(raiz, nomes[i], comparar_string);

    printf("Nomes: "); bst_em_ordem(raiz, imprimir_string); printf("\n");

    bst_limpar(raiz);
    return 0;
}
