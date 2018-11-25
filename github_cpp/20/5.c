


#include <cstdlib>
#include "redblacktree.h"

typedef enum ColorType{ RED, BLACK } ColorType;

struct RedBlackNode {
    ElementType element;
    Position left;
    Position right;
    ColorType color;
};

static ColorType getColor(Position position){
    if (position == NULL)
        return BLACK;
    return position->color;
}

RedBlackTree makeEmpty(RedBlackTree tree) {
    if (tree == NULL)
        return NULL;
    makeEmpty(tree->left);
    makeEmpty(tree->right);
    std::free(tree);
    return NULL;
}
