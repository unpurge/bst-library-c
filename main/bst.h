#ifndef bst_h
#define bst_h

#include <stdbool.h>

// Nó da árvore. A árvore guarda apenas o ponteiro "dado": ela **NÂO** copia nem libera o conteúdo apontado.
typedef struct No {
	void *dado;
	struct No *esquerda;
	struct No *direita;
} No;

// Compara a com b: negativo se a < b, zero se iguais, positivo se a > b.
typedef int (*FuncComparar)(const void *a, const void *b);

// Imprime um dado (usada pelos percursos).
typedef void (*FuncImprimir)(const void *dado);

// Comparadores e impressores
int  comparar_inteiro(const void *a, const void *b);
int  comparar_string(const void *a, const void *b);  // ignora maiúsculas e/ou minúsculas.
void imprimir_inteiro(const void *dado);
void imprimir_string(const void *dado);
void imprimir_caractere(const void *dado);

// Estrutura. Recomenda usar o retorno: raiz = bst_inserir(raiz, ...) */
No  *bst_inserir(No *raiz, void *dado, FuncComparar comparar); // DUPLICATAS, ou valores repetidos, **NÂO** são inseridos.
No  *bst_remover(No *raiz, void *dado, FuncComparar comparar);
void bst_limpar(No *raiz); //raiz se tornará NULL.

// Consultas.
bool  bst_buscar(const No *raiz, const void *dado, FuncComparar comparar);
void *bst_minimo(const No *raiz);  // NULL se vazia.
void *bst_maximo(const No *raiz);  // NULL se vazia.
int   bst_contar(const No *raiz);
int   bst_altura(const No *raiz);  // se raiz = NULL, dará 0.

// Percursos 
void bst_pre_ordem(const No *raiz, FuncImprimir imprimir);
void bst_em_ordem(const No *raiz, FuncImprimir imprimir);
void bst_pos_ordem(const No *raiz, FuncImprimir imprimir);
void bst_decrescente(const No *raiz, FuncImprimir imprimir);

#endif
// Obrigado a pode ler até aqui.
// Toda a lógica foi escrita por mim, apenas pedi auxílio da IA para dar uma ajeitada e organizada em minha bagunça :).
