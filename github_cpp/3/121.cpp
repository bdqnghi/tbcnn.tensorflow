

#ifndef _AVL_H_INC
#define	_AVL_H_INC

#include <stdlib.h>
#include <stdbool.h>

#ifdef	__cplusplus
extern "C"
{
#endif

#ifndef AVL_PREFIX
    #error Expected define: AVL_PREFIX name
#endif

#ifndef AVL_NODE_TYPE
    #error Expected define: AVL_NODE_TYPE type
#endif

#ifndef AVL_TREE_TYPE
    #error Expected define: AVL_TREE_TYPE type
#endif

#ifndef AVL_CONST_TREE_TYPE
    #error Expected define: AVL_CONST_TREE_TYPE type
#endif

#ifndef AVL_REFERENCE_TYPE
    #error Expected define: AVL_REFERENCE_TYPE type
#endif

#ifndef AVL_HAS_PARENT_POINTER
    #error Expected define: AVL_HAS_PARENT_POINTER boolean.
#endif

#ifndef AVL_TREE_ROOT
    #error Expected define: AVL_TREE_ROOT(__tree__).
    
#endif



#define __AVL_PREFIXED(name_a,name_b) name_a ## name_b		
#define _AVL_PREFIXED(name_a,name_b) __AVL_PREFIXED(name_a,name_b)	
#define AVL_PREFIXED(name) _AVL_PREFIXED( AVL_PREFIX , name)		

typedef struct AVL_PREFIXED(avl_iterator) AVL_PREFIXED(avl_iterator);

struct AVL_PREFIXED(avl_iterator)
{
    s32 stack_pointer;
    AVL_NODE_TYPE* stack[AVL_MAX_DEPTH];    
};




void AVL_PREFIXED(avl_init)(AVL_TREE_TYPE* tree);



AVL_NODE_TYPE* AVL_PREFIXED(avl_find)(AVL_CONST_TREE_TYPE* tree,const AVL_REFERENCE_TYPE obj_hash);

AVL_NODE_TYPE* AVL_PREFIXED(avl_find_debug)(AVL_CONST_TREE_TYPE* tree,const AVL_REFERENCE_TYPE obj_hash);



AVL_NODE_TYPE* AVL_PREFIXED(avl_insert)(AVL_TREE_TYPE *tree,AVL_REFERENCE_TYPE obj_hash);



void AVL_PREFIXED(avl_delete)(AVL_TREE_TYPE *tree,AVL_REFERENCE_TYPE obj_hash);



void AVL_PREFIXED(avl_destroy)(AVL_TREE_TYPE *tree);

static inline bool AVL_PREFIXED(avl_isempty)(const AVL_TREE_TYPE *tree)
{
    return AVL_TREE_ROOT(tree) == NULL;
}



AVL_NODE_TYPE* AVL_PREFIXED(avl_node_last)(AVL_NODE_TYPE *node);

void AVL_PREFIXED(avl_iterator_init)(AVL_CONST_TREE_TYPE* tree,AVL_PREFIXED(avl_iterator*) iter);
bool AVL_PREFIXED(avl_iterator_hasnext)(AVL_PREFIXED(avl_iterator*) iter);
AVL_NODE_TYPE* AVL_PREFIXED(avl_iterator_next_node)(AVL_PREFIXED(avl_iterator*) iter);



void AVL_PREFIXED(avl_callback_and_destroy)(AVL_TREE_TYPE *tree,callback_function callback);

#if AVL_HAS_PARENT_POINTER != 0

AVL_NODE_TYPE* AVL_PREFIXED(avl_node_next)(AVL_NODE_TYPE* node);

AVL_NODE_TYPE* AVL_PREFIXED(avl_node_prev)(AVL_NODE_TYPE* node);

AVL_NODE_TYPE* AVL_PREFIXED(avl_node_mod_next)(AVL_NODE_TYPE* node);

AVL_NODE_TYPE* AVL_PREFIXED(avl_node_mod_prev)(AVL_NODE_TYPE* node);

#endif

int AVL_PREFIXED(avl_check)(AVL_TREE_TYPE *tree);
void AVL_PREFIXED(avl_dump)(AVL_TREE_TYPE *tree);

#ifdef	__cplusplus
}
#endif

#else

#error AVL.H.INC SHOULD NOT BE INCLUDED TWICE

#endif	
