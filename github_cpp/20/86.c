

#include <iostream>
using namespace std;



template<typename Comparable>
class RedBlackTree{

    public:
        

        

        enum {RED, BLACK};
    private:
        struct RedBlackNode{
            Comparable element;
            RedBlackNode * left;
            RedBlackNode * right;
            int color;

            RedBlackNode(const Comparable & e = Comparable(), RedBlackNode * lt = NULL, RedBlackNode * rt = NULL, int c = BLACK){}
        };

        RedBlackNode * root;
        RedBlackNode * nullNode;
        
        
        RedBlackNode * current;
        RedBlackNode * parent;
        RedBlackNode * grand;
        RedBlackNode * great;
};






int main()
{
    RedBlackTree<int> tree;   


    return 0;
}
