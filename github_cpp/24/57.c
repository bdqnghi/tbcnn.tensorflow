


#ifndef CPP_BINARY_TREE_H
#define CPP_BINARY_TREE_H

class BinaryTree {
 public:
  class Node;
  Node *root = nullptr;
  bool Add(std::string name, int id);
  bool Search(std::string name, int id);
  std::string GetNameById(int id);
  int GetIdByName(std::string name);

  
  void PrintInOrder();
  void PrintPreOrder();
  void PrintPostOrder();

  
  void PrintLevelOrder();
};

class BinaryTree::Node {
 public:
  class Data {
   public:
    int id;
    std::string name;



  };

  BinaryTree::Node::Data *data = new BinaryTree::Node::Data;
  Node();
  Node(std::string name, int id) {
    this->data->name = name;
    this->data->id = id;
  }

  Node *left = nullptr;
  Node *right = nullptr;
  bool Add(std::string name, int id);
  bool Search(std::string name, int id);
  std::string GetNameById(int id);
  int GetIdByName(std::string name);
  void PrintInOrder();
  void PrintPreOrder();
  void PrintPostOrder();

  
  void PrintLevelOrder();

};





















#endif 
