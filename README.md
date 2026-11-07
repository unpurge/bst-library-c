# libds

**SO recomendada: POSIX (Linux/MacOS).**
Biblioteca em C de estruturas de dados **genéricos**.
Um código bem genérico, mas feito com interrese e um bucado de estresse :).
**Estado atual:** árvore binária de busca (BST) completa e testada.
Agradeço imensamente a quem estiver lendo isso :). -unpurge

## Por que "genérica"?

A árvore guarda `void *`, então serve para `int`, strings ou structs suas.
Como ela não sabe comparar os dados, você entrega uma **função de comparação** (ponteiro de função) a cada operação.

## Exemplo

#include <stdio.h>
#include "bst.h"

int main(void) {
    int v[] = {50, 30, 70, 20, 40};
    No *raiz = NULL;

    for (int i = 0; i < 5; i++)
        raiz = bst_inserir(raiz, &v[i], comparar_inteiro);

    bst_em_ordem(raiz, imprimir_inteiro);   // 20 30 40 50 70 
    printf("\n");

    bst_limpar(raiz);
    raiz = NULL;
    return 0;
}

Um exemplo maior (busca, remoção e strings) está em [examples/exemplo.c].

## Como compilar e testar

Requisitos: gcc e make (Linux ou macOS).

make test      # roda os testes com AddressSanitizer e UBSan
make exemplo   # compila e roda o exemplo
make clean

Para compilar o exemplo: gcc -Imain main/bst.c examples/exemplo.c -o programa
Para usar na sua aplicação: gcc -Imain main/bst.c seu_main.c -o programa

## API

| Função | O que faz | Complexidade |

Complexidade:
-> O(n): significa que o tempo  que o tempo de execução cresce proporcionalmente ao número total de elementos.
-> O(h): significa que o tempo cresce proporcionalmente à altura da estrutura.

| bst_inserir | Insere um dado (duplicatas são ignoradas) | O(h) |
| bst_remover | Remove um dado (0, 1 ou 2 filhos) | O(h) |
| bst_buscar | Diz se o dado existe | O(h) |
| bst_minimo / `bst_maximo` | Menor / maior dado (`NULL` se vazia) | O(h) |
| bst_contar | Quantidade de elementos | O(n) |
| bst_altura | Altura da árvore (vazia = 0) | O(n) |
| bst_pre_ordem, bst_em_ordem, bst_pos_ordem, bst_decrescente | Percursos com função de impressão | O(n) |
| bst_limpar | Libera todos os nós | O(n) |

Comparadores e impressores prontos: `comparar_inteiro`, `comparar_string` (ignora maiúsculas/minúsculas), `imprimir_inteiro`, `imprimir_string`, `imprimir_caractere`.

## Decisões de design

- **Genérica com `void *` e ponteiros de função**, em vez de uma versão para cada tipo, para aproveitar o embalo :).
- **A árvore não é dona dos dados:** ela só guarda ponteiros. Não copia nem libera o conteúdo. Os dados precisam continuar vivos enquanto estiverem na árvore.
- **Sem duplicatas:** inserir um dado igual a um existente não faz nada.
- **Remoção com dois filhos:** o nó recebe o maior valor da subárvore esquerda, que depois é removido de lá.
- **Funções devolvem a nova raiz** (`raiz = bst_inserir(raiz, ...)`), o que evita ponteiro para ponteiro.
- **comparar_string usa strcasecmp:** requer POSIX (Linux/macOS); no Windows seria `_stricmp`.

## Sobre o desenvolvimento

A estrutura original da BST foi escrita por mim. A revisão de nomes e palavras, a simplificação de algumas funções, a correção de um bug no comparador de strings e a base dos testes foram feitas com ajuda de uma IA (Claude). 

## Licença

MIT. Veja [LICENSE].

Este é meu primeiro projeto, algo simples, mas pude dar o primeiro passo neste mundo kkkk. 
-unpurge :)
