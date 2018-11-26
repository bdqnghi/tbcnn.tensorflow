/*
    B-Tree - Antonio Carlos Falcão Petri e Thiago Yonamine
    DC - UFSCar - São Carlos - 2015
 */
#ifndef B_TREE_H
#define B_TREE_H

#if DEBUG
#include <stdio.h>
#endif

#include <stdlib.h>
#include <assert.h>

#include "util.h"
#include "btree_util.h"

/*
   B-Tree
   order:  número da ordem da B-Tree (cada nó da B-Tree possui [order-1, 2*order] filhos)
   root:   ponteiro para o nó raiz da B-Tree (possui [2, 2*order] filhos)
 */
typedef struct btree_t {
	int order;
	node_t *root;
} BTree;

/*
    Aloca e retorna uma B-Tree na Heap de ordem order
 */
BTree* btree_new(int order);
/*
    Inicializa uma B-Tree de ordem order.
    Utilizada como sub-procedimento na função btree_new().
    Pode ser utilizada para inicializar uma B-Tree criada na Stack.
 */
void btree_init(BTree *bt, int order);
/*
    Deleta uma B-Tree alocada na Stack.
    Utilizada como sub-procedimento na função btree_delete_h().
    NÃO tenta dar free na B-Tree: free(bt).
 */
void btree_delete_s(BTree *bt);
/*
    Deleta uma B-Tree alocada na Heap.
    EXECUTA um FREE na B-Tree: free(bt).
    Undefined behavior caso bt não tenha sido alocado com uma chamada à malloc().
 */
void btree_delete_h(BTree *bt);

/*
    Procura a chave key na B-Tree bt.
    Chama a função _btree_find_node() sobre a raiz de bt.
 */
node_position btree_find(BTree *bt, int key);
/*
    Insere a chave key na B-Tree bt, associando-a ao valor value.
    Trata o caso em que a raiz está cheia analisando a raiz
    e chamando (possivelmente) a função _btree_split().
    Chama a função _btree_insert_nonfull() sobre a raiz de bt.
 */
node_position btree_insert(BTree *bt, int key, void *value);
/*
    Remove a chave key na B-Tree bt.
    Chama a função _btree_remove_node() sobre a raiz de bt.
    ATENÇÃO: Pode não ser seguro acessar tal posição.
 */
node_position btree_remove(BTree *bt, int key);

/*
    Procura a key na sub-árvore com raiz node.
    Retorna um node_position para permitir a recuperação do valor
    associado à key.
    Retorna node_position(NULL, -1) caso key não seja encontrada.
 */
node_position _btree_find_node(node_t *node, int key);
/*
    Trata todos os casos de inserção de um pair na B-Tree.
    Retorna um node_position indicando onde a chave foi inserida.
    Retorna node_position(NULL, -1) caso key já exista em bt.

    order:  ordem da árvore à qual node pertence. Utilizado para alocar um novo nó.
 */
node_position _btree_insert_nonfull(node_t *node, pair_t *pair, int order);
/*
    Realiza a função split sobre x, na posição pos.
    order:  ordem da árvore à qual node pertence. Utilizado para alocar um novo nó.
 */
void _btree_split(node_t *x, int pos, int order);
/*
    Trata todos os casos de remoção de uma key na B-Tree.
    Realizada possíveis chamadas recursivas.

    Retorna um node_position indicando onde a chave estava localizada.
    ATENÇÃO: Pode não ser seguro acessar tal posição.
    Retorna node_position(NULL, -1) caso key não exista em bt.
 */
node_position _btree_remove_node(node_t *node, int key, int order);

/*
    Retorna o node_position da maior key em node
 */
inline node_position _node_find_max(node_t *node);
/*
    Retorna o node_position da menor key em node
 */
inline node_position _node_find_min(node_t *node);

#endif
