

















#ifndef _AVL_TREE_DECLS
#define _AVL_TREE_DECLS











class avl_key;
class avl_node;
class avl_tree;
typedef avl_node* avl_nodeptr;
typedef avl_nodeptr* avl_linkptr;
typedef avl_tree* avl_treeptr;





class avl_key { };





class avl_node {
   friend class avl_tree;
   friend class avl_iterator;

public:

   avl_node(avl_treeptr, const avl_key&);
   

   virtual ~avl_node();
   

   avl_nodeptr dup() const;
   

   virtual int compare(const avl_key& other) const = 0;
   

private:
   avl_nodeptr left;
   avl_nodeptr right;
   int balance;

   static void restore_trace(avl_nodeptr from, avl_nodeptr upto,
         int initial_direction);
   };



class avl_tree {
   friend class avl_node;
   friend class avl_iterator;

public:

   avl_tree();

   virtual ~avl_tree();
   

   avl_nodeptr find(const avl_key&) const;
   

   void remove(const avl_key&);
   

   size_t count() { return cnt; }
   

private:
   avl_nodeptr root;
   size_t cnt;

   int excise_from(avl_nodeptr&, const avl_key&);
   static int rebalance(avl_nodeptr&);
   static int rotate_left(avl_nodeptr&);
   static int rotate_right(avl_nodeptr&);
   };



class avl_iterator {
public:

   avl_iterator(const avl_tree*);
   

   virtual ~avl_iterator();

   avl_nodeptr next();
   

   void reset();
   

private:
   void traverse(avl_node*);
   const avl_tree* treep;
   struct avl_traversal* stackp;
   };

#endif
