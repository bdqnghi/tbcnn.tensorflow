#include <stdlib.h>
#include "../headers/heap.h"

//#define TESTING_HEAP


#define swap(p, c, t)({                 \
  (t) = (p)->children;                  \
  (p)->children = (c)->children;        \
  (c)->children = t;                    \
  if((p)->parent){                      \
    if((p)->parent->child[0] == (p)){   \
      (p)->parent->child[0] = c;        \
    } else{                             \
      (p)->parent->child[1] = c;        \
    }                                   \
  }                                     \
  (c)->parent = (p)->parent;            \
  (p)->parent = (c);                    \
  if((p)->child[0] == (c)){             \
    (p)->child[0] = (c)->child[0];      \
    (c)->child[0] = (p)->child[1];      \
    (p)->child[1] = (c)->child[1];      \
    (c)->child[1] = (c)->child[0];      \
    (c)->child[0] = (p);                \
    if((c)->child[1]){                  \
      (c)->child[1]->parent = (c);      \
    }                                   \
  } else{                               \
    (p)->child[1] = (c)->child[1];      \
    (c)->child[1] = (p)->child[0];      \
    (p)->child[0] = (c)->child[0];      \
    (c)->child[0] = (c)->child[1];      \
    (c)->child[1] = (p);                \
    if((c)->child[0]){                  \
      (c)->child[0]->parent = (c);      \
    }                                   \
  }                                     \
  if((p)->child[0]){                    \
    (p)->child[0]->parent = (p);        \
  }                                     \
  if((p)->child[1]){                    \
    (p)->child[1]->parent = (p);        \
  }                                     \
})




typedef struct heap_node{
  struct heap_node *parent;
  struct heap_node *child[2];
  uint32_t children;
  void *data;
} heap_node_t;


/**
 * this method is used to place a new node in the closest vacant location to the top of the heap.
 * @param  h                       the heap that will get the new node
 * @param  n                       the node that needs to be placed
 * @author Collin Vincent <collinvincent96@gmail.com>
 * @date   2017-02-08T10:46:20+000
 */
void place_node(heap_node_t *h, heap_node_t *n);

/**
 * this method makes recursive calls that will end up freeing all the dynamically allocated heap nodes in the heap
 * @param  n                       a node that will free every child and then itself
 * @author Collin Vincent <collinvincent96@gmail.com>
 * @date   2017-02-08T10:48:01+000
 */
void clear_node(heap_node_t *n);



void place_node(heap_node_t *h, heap_node_t *n){
  (h->children)++;
  if(h->child[0]==NULL){
    h->child[0] = n;
    n->parent = h;
  } else if(h->child[1]==NULL){
    h->child[1] = n;
    n->parent = h;
  } else if(h->child[0]->children <= h->child[1]->children){
    place_node(h->child[0], n);
  } else{
    place_node(h->child[1], n);
  }
}

void *peek(heap_t *h){
  if(!h->top)
    return NULL;
  return h->top->data;
}

void clear_node(heap_node_t *n){
  if(n==NULL){
    return;
  }
  clear_node(n->child[0]);
  clear_node(n->child[1]);
  free(n);
}

void update_node(heap_t *h, heap_node_t *n){
  uint32_t t;
  heap_node_t *p;
  if(!n->data)
    return;
  while(n->parent && h->compare(n->data, n->parent->data) > 0){
    p = n->parent;
    swap(p, n, t);
  }
  if(!(n->parent)){
    h->top = n;
  }
}

void clear_heap(heap_t *h){
  clear_node(h->top);
  h->top = NULL;
  free(h);
}

void *heap_pop(heap_t *h){
  heap_node_t *n, *c;
  uint32_t t;

  n = h->top;

  if(!n){
    return NULL;
  }
  void *ans = n->data;
  n->data = NULL;
  while(n->children){
    if(n->child[0] && n->child[1]){
      if(h->compare(n->child[0]->data, n->child[1]->data) > 0){
        c = n->child[0];
      } else{
        c = n->child[1];
      }
    } else if(n->child[0]){
      c = n->child[0];
    } else if(n->child[1]){
      c = n->child[1];
    }
    if(!(n->parent)){
      h->top = c;
    }
    swap(n, c, t);
    c->children--;
  }
  if(n->parent){
    if(n->parent->child[0] == n){
      n->parent->child[0] = NULL;
    } else{
      n->parent->child[1] = NULL;
    }
  } else{
    h->top = NULL;
  }
  free(n);
  return ans;
}

static heap_node_t *insert_vertex(heap_t *h, void *v){
  heap_node_t *n;
  heap_node_t *p;
  uint32_t t;

  n = (heap_node_t*)calloc(1, sizeof (*n));

  n->data = v;
  if(h->top == NULL){
    h->top = n;
    return n;
  }
  place_node(h->top, n);
  while(n->parent && h->compare(n->data, n->parent->data) > 0){
    p = n->parent;
    swap(p, n, t);
  }
  if(!(n->parent)){
    h->top = n;
  }
  return n;
}

void init_heap(heap_t **h, int32_t (*compare)(void*, void*)){
  *h = (heap_t *)calloc(1, sizeof (heap_t));
  (*h)->compare = compare;
  (*h)->clear = &clear_heap;
  (*h)->insert = &insert_vertex;
  (*h)->pop = &heap_pop;
  (*h)->update = &update_node;
  (*h)->peek = &peek;
}


#ifdef TESTING_HEAP

#include <stdio.h>
#include <string.h>

static uint8_t print_heap_node(heap_node_t *n, uint8_t s){
  uint8_t a, b;

  if(!n){
    if(!s){
      printf("null ");
    }
    return 0;
  } else{
     if(s){
       a = print_heap_node(n->child[0], s-1);
       b = print_heap_node(n->child[1], s-1);
       return a+b;
     } else{
       printf("%d ", *((int*)(n->data)));
       return 1;
     }
  }
}

static void print_heap(heap_t *h){
  uint8_t i = 0;
  while(print_heap_node(h->top, i)){
    printf("\n");
    i++;
  }
  printf("\n");
}

static int32_t cmp(void *n, void *p){
  return *((int*)p) - *((int*)n);
}

int main(int argc, char const *argv[]){
  heap_t *h;
  heap_node_t *n;
  init_heap(&h, cmp);
  int *t, c = 1;
  char s[20];

  while(c){
    printf("enter command: ");
    scanf("%s", s);
    if(!strcmp(s, "add")){
      t = malloc(sizeof (int));
      printf("enter number: ");
      scanf("%d", t);
      n = h->insert(h, t);
      print_heap(h);
    } else if(!strcmp(s, "pop")){
      t = h->pop(h);
      if(t){
        printf("number popped: %d\n", (int)(*t));
        print_heap(h);
        free(t);
      }
    } else if(!strcmp(s,"update")){
      printf("enter new number: ");
      scanf("%d", t);
      n->data = t;
      h->update(h, n);
      print_heap(h);
    } else if(!strcmp(s, "exit")){
      c = 0;
    }
  }
  return 1;
}

#endif
