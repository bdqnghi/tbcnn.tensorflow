#include <iostream>
#include <cstdlib>
#include "../hh/avltree.hh"

using namespace std;

void menu();

int main()
{

  AVLTree<int> tree;
  int elem;
  int choice = 1;

  system("clear");
  while(choice != 0)
  {
    menu();
    cout << "Your choice: ";
    cin >> choice;
    switch(choice)
      {
        case 0:
          {
            break;
          }
        case 1:
          {
            system("clear");
            tree.add_elem(elem);
            break;
          }
        case 2:
          {
            system("clear");
            cout << "Enter node to remove: ";
            cin >> elem;
            tree.remove_elem(elem);
            break;
          }
        case 3:
          {
            system("clear");
            tree.show_root();
            break;
          }
        case 4:
          {
            system("clear");
            tree.show_height();
            break;
          }
        case 5:
          {
            system("clear");
            tree.preorder();
            break;
          }
        case 6:
          {
            system("clear");
            tree.inorder();
            break;
          }
        case 7:
          {
            system("clear");
            tree.postorder();
            break;
          }
        default:
          {
            cout << "Wrong choice!" << endl;
            break;
          }
      }
  }
}

void menu()
{
    cout << "--------------- AVL TREE ---------------\n" <<
            "0 - EXIT\n" <<
            "1 - ADD NEW NODE TO AVL-TREE\n" <<
            "2 - REMOVE NODE FROM AVL-TREE\n" <<
            "3 - SHOW ROOT OF AVL-TREE\n" <<
            "4 - SHOW HEIGHT OF THE TREE\n" <<
            "5 - PRE-ORDER\n" <<
            "6 - IN-ORDER\n" <<
            "7 - POST-ORDER\n" << endl;
}
