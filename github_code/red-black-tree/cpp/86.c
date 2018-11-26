/*************************************************************************
	> File Name: RedBlackTree.cpp
	> Author: 
	> Mail: 
	> Created Time: 2016年04月09日 星期六 17时00分06秒
 ************************************************************************/

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

        RedBlackNode * root;//树的根节点
        RedBlackNode * nullNode;//当前节点的父节点的兄弟节点
        
        //用于插入函数的节点信息
        RedBlackNode * current;//当前插入的节点,X
        RedBlackNode * parent;//当前插入的节点的父节点,P
        RedBlackNode * grand;//当前插入的节点的祖父节点,G
        RedBlackNode * great;//当前插入的节点的曾祖父节点,GG
};





//测试主函数
int main()
{
    RedBlackTree<int> tree;   


    return 0;
}
