/**
 * @file   maxmin_k.hh
 * @author  <ywei@ubiquant.com>
 * @date   Mon Jul 22 13:38:37 2013
 * 
 * @brief  A O(log(n))-time, O(n)-space algorithm for select k-th data from a window data maintain in a data flow.
 *         with red-black-tree.
 * 
 */

#ifndef __MAXMIN_K_HH__
#define __MAXMIN_K_HH__

#include <vector>

enum Color{
  BLACK,
  RED
};

template <typename T>
class RBNode{
 public:
  const T *key;			/**< The data */
  int index;			/**< The index of the data in the flow*/
  int size;			/**< The size of the sub tree*/
  Color color;			/**< Color of this node */
  RBNode *left;			/**< The pointer to the left son of this node */
  RBNode *right;		/**< The pointer to the right son of this node */
  RBNode *parent;		/**< The pointer to the parent os this node */
};

template <typename T>
class MaxMinKWindow{
 public:
  //constructor
  MaxMinKWindow(size_t n);	

  //copy constructor
  MaxMinKWindow(const MaxMinKWindow& mmw):
    nil_key(mmw.nil_key),    
    index(mmw.index),
    length_k(mmw.length_k)
  {
    nil = new RBNode<T>;
    nil -> color = BLACK;
    nil -> size = 0;
    nil -> key = &(this->nil_key);
    root = nil;
    nodes.resize(length_k);
    pool = new RBNode<T>[length_k + 1];
    poolroot = pool;
    for(int i = 0; i < length_k; i ++){
      pool[i].right = &pool[i +1];
      pool[ i + 1].parent = &pool[i];
    }
    if(mmw.root != mmw.nil){
      root = pool_pop();
      root -> parent = nil;
      copy_tree(root, mmw.root, mmw);
    }else{
      root = nil;
    }
  };

  MaxMinKWindow& operator=(const MaxMinKWindow &mmw)
  {
    nil_key = mmw.nil_key;
    index = mmw.index;
    length_k = mmw.length_k;
    nil = new RBNode<T>;
    nil -> color = BLACK;
    nil -> size = 0;
    nil -> key = &(this->nil_key);
    root = nil;
    nodes.resize(length_k);
    pool = new RBNode<T>[length_k + 1];
    poolroot = pool;
    for(int i = 0; i < length_k; i ++){
      pool[i].right = &pool[i +1];
      pool[ i + 1].parent = &pool[i];
    }
    if(mmw.root != mmw.nil){
      root = pool_pop();
      root -> parent = nil;
      copy_tree(root, mmw.root, mmw);
    }else{
      root = nil;
    }
    return (*this);

  ~MaxMinKWindow();
  
  /** 
   * define nan(not a number).
   * 
   * @param nan, define the value of nan as "not a number"
   * 
   * @return 
   */
  void set_nan(T nan);

  /** 
   * clear all data. 
   * 
   */
  void clear();
  
 /**
   *  main operation of MaxMinWindow
   *  1.insert a data into datawindow.
   *  2.remove oldest data if datawindow is full.
   *  3.maintain the tree depth of the red-black-tree.
   *
   * @param x 
   */
  void add_new(const T &x);
  
  /** 
   * get constant reference of min-k value in datawindow, k >= 1 
   * 
   * @param k 
   * 
   * @return 
   */
  inline const T& mink_val(size_t k) const;
  
  /** 
   * get constant reference of max-k value in datawindow, k >= 1
   * 
   * @param k 
   * 
   * @return 
   */
  inline const T& maxk_val(size_t k) const;

  inline int mink_pos(int k) const {
    if(k < 1 || k > root -> size){
      return -1;
    }else{
      if(index < length_k){
	return (Select(root, k) -> index);
      }else{
	return (Select(root, k) -> index - index + length_k);
      }
    }
  }
  
  inline int maxk_pos(int k) const {
    if(k > root->size || k < 1){
      return -1;
    }
    if(index < length_k){
      return (Select(root, index - k+1) -> index);
    }else{
      return (Select(root, length_k - k + 1) -> index -index + length_k);
    }
  }
  
  /** 
   * get constant reference of min value in datawindow
   * 
   * 
   * @return 
   */
  inline const T& min_val() const;
  
  /** 
   * get constant reference of max value in datawindow
   * 
   * 
   * @return 
   */
  inline const T& max_val() const;

  inline int min_pos() const {
    if(index < length_k){
      return (Minimum(root) -> index);
    }else{
      return (Minimum(root) -> index - (index -length_k));
    }
  }
  inline int max_pos() const { 
    if(index < length_k){
      return (Maximum(root) -> index);
    }else{
      return (Maximum(root) -> index) - index + length_k;
    }
  }

 private:
  //@{ red-black tree methods.
  RBNode<T>* Successor(RBNode<T> *z);	

  void InsertNode(RBNode<T> *z); 

  void DeleteNode(int index);	
  void copy_tree(RBNode<T> *node, const RBNode<T>*from, const MaxMinKWindow<T>& mmw);

  RBNode<T>* DeleteNode(RBNode<T> *z);
  
  inline RBNode<T>* Maximum(RBNode<T> *z) const; 
  inline RBNode<T>* Minimum(RBNode<T> *z) const;
  inline RBNode<T>* Select(RBNode<T>*x, size_t i) const; 

  inline RBNode<T>* pool_pop();	
  inline void pool_push(RBNode<T> *z); 

  RBNode<T>* poolroot; int poolsize; 

  int length_k;		
  std::vector <RBNode<T>*> nodes;   /**< pointers point the last length_k Nodes*/
  RBNode<T>* root;		/**< root of the tree */

  size_t index;			/**< The count of the flow after last clear() */

  RBNode<T>* nil;
  T nil_key;
  void LeftRotate(RBNode<T>* x);
  void RightRotate(RBNode<T>* x);
  void InsertFixup(RBNode<T>* z);
  void DeleteFixup(RBNode<T>* x);

  RBNode<T>* pool;
  //@}
};

#include "maxmin_k.tpp"

#endif //__MAXMIN_K_HH__
