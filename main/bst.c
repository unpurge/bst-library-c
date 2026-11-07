#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "bst.h"

// Comparadores e Impressores

int comparar_inteiro(const void *a, const void *b) {
	int x = *(const int *)a;
	int y = *(const int *)b;
	return (x > y) - (x < y);
}

int comparar_string(const void *a, const void *b) {
	return strcasecmp((const char *)a, (const char *)b);
}

void imprimir_inteiro(const void *dado) { printf("%d ", *(const int *)dado); }
void imprimir_string(const void *dado) { printf("%s ", (const char *)dado); }
void imprimir_caractere(const void *dado) { printf("%c ", *(const char *)dado); }

// Estrutura 

No *bst_inserir(No *raiz, void *dado, FuncComparar comparar) {
	if (raiz == NULL) {
		No *novo = malloc(sizeof(No));
		if (novo == NULL) return NULL;
		novo->dado = dado;
		novo->esquerda = NULL;
		novo->direita = NULL;
		return novo;
	}
	int cmp = comparar(dado, raiz->dado);
	if (cmp < 0) raiz->esquerda = bst_inserir(raiz->esquerda, dado, comparar);
	else if (cmp > 0) raiz->direita = bst_inserir(raiz->direita,  dado, comparar);
	return raiz;
}

No *bst_remover(No *raiz, void *dado, FuncComparar comparar) {
	if (raiz == NULL) return NULL;
	
	int cmp = comparar(dado, raiz->dado);
	if (cmp < 0) {
		raiz->esquerda = bst_remover(raiz->esquerda, dado, comparar);
		return raiz;
	}
	if (cmp > 0) {
		raiz->direita = bst_remover(raiz->direita, dado, comparar);
		return raiz;
	}
	
	// achou: 0 ou 1 filho.
	if (raiz->esquerda == NULL || raiz->direita == NULL) {
		No *filho = (raiz->esquerda != NULL) ? raiz->esquerda : raiz->direita;
		free(raiz);
		return filho;
	}
	
	// 2 filhos: troca pelo maior da esquerda e remove ele de lá.
	void *maior = bst_maximo(raiz->esquerda);
	raiz->dado = maior;
	raiz->esquerda = bst_remover(raiz->esquerda, maior, comparar);
	return raiz;
}

void bst_limpar(No *raiz) {
	if (raiz == NULL) return;
	bst_limpar(raiz->esquerda);
	bst_limpar(raiz->direita);
	free(raiz);
	raiz = NULL; // Por segurança, incluí o NULL, caso o utilizador desta lib não atribua ao depois que a função acabar.
}

// Consultas

bool bst_buscar(const No *raiz, const void *dado, FuncComparar comparar) {
	while (raiz != NULL) {
		int cmp = comparar(dado, raiz->dado);
		if (cmp == 0) return true;
		raiz = (cmp < 0) ? raiz->esquerda : raiz->direita;
	}
	return false;
}

void *bst_minimo(const No *raiz) {
	if (raiz == NULL) return NULL;
	while (raiz->esquerda != NULL) raiz = raiz->esquerda;
	return raiz->dado;
}

void *bst_maximo(const No *raiz) {
	if (raiz == NULL) return NULL;
	while (raiz->direita != NULL) raiz = raiz->direita;
	return raiz->dado;
}

int bst_contar(const No *raiz) {
	if (raiz == NULL) return 0;
	return 1 + bst_contar(raiz->esquerda) + bst_contar(raiz->direita);
}

int bst_altura(const No *raiz) {
	if (raiz == NULL) return 0;
	int esq = bst_altura(raiz->esquerda);
	int dir = bst_altura(raiz->direita);
	return 1 + (esq > dir ? esq : dir);
}

// Percursos

void bst_pre_ordem(const No *raiz, FuncImprimir imprimir) {
	if (raiz == NULL) return;
	imprimir(raiz->dado);
	bst_pre_ordem(raiz->esquerda, imprimir);
	bst_pre_ordem(raiz->direita, imprimir);
}

void bst_em_ordem(const No *raiz, FuncImprimir imprimir) {
	if (raiz == NULL) return;
	bst_em_ordem(raiz->esquerda, imprimir);
	imprimir(raiz->dado);
	bst_em_ordem(raiz->direita, imprimir);
}

void bst_pos_ordem(const No *raiz, FuncImprimir imprimir) {
	if (raiz == NULL) return;
	bst_pos_ordem(raiz->esquerda, imprimir);
	bst_pos_ordem(raiz->direita, imprimir);
	imprimir(raiz->dado);
}

void bst_decrescente(const No *raiz, FuncImprimir imprimir) {
	if (raiz == NULL) return;
	bst_decrescente(raiz->direita, imprimir);
	imprimir(raiz->dado);
	bst_decrescente(raiz->esquerda, imprimir);
}
