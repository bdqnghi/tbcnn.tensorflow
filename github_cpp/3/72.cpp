






#include "Code203_Tree.h"
#include <iostream>

using namespace std;

AVLTreeNode *createNewNode(int key);

int main()
{
   Code203_Tree *theAVLTree;
   char ans[32];

   cout << "Ready to test AVL trees. Press Enter to start.\n\n";
   gets(ans);

   
   


   theAVLTree = new Code203_Tree();
   cout<< "-----------------------------------------------\n";
   cout<< "TESTING CASE 1\n\n";
   
   cout << "\nAdding Node 50\n";
   theAVLTree->Insert(createNewNode(50));
   theAVLTree->PrintTree();
   
   cout << "\nAdding Node 20 to trigger test of Case 1 to left. Root is ancester.\n";
   theAVLTree->Insert(createNewNode(20));
   theAVLTree->PrintTree();
   
   cout << "\nAdding Node 70\n";
   theAVLTree->Insert(createNewNode(70));
   theAVLTree->PrintTree();
      
   cout << "\nAdding Node 90 to trigger test of Case 1 to right. Root is ancester.\n";
   theAVLTree->Insert(createNewNode(90));
   theAVLTree->PrintTree();
   cout<< "\nEND TESTING CASE 1\n\n";
   delete theAVLTree;
   cout<< "-----------------------------------------------\n";
   cout<< "-----------------------------------------------\n";

   cout << "\nPress Enter to start the next test.\n\n";
   gets(ans);

   
   theAVLTree = new Code203_Tree();
   cout<< "-----------------------------------------------\n";
   cout<< "TESTING CASE 2\n\n";
   
   cout << "\nAdding Node 50\n";
   theAVLTree->Insert(createNewNode(50));
   theAVLTree->PrintTree();
   
   cout << "\nAdding Node 20. Ancester's balance factor changes to L\n";
   theAVLTree->Insert(createNewNode(20));
   theAVLTree->PrintTree();
   
   cout << "\nAdding Node 70 to trigger test of Case 2. Ancester's balance factor changes to =\n";
   theAVLTree->Insert(createNewNode(70));
   theAVLTree->PrintTree();
   
   cout << "\nAdding Node 90. Ancester's balance factor changes to R.\n";
   theAVLTree->Insert(createNewNode(90));
   theAVLTree->PrintTree();
   
   cout << "\nAdding Node 15 to trigger test of Case 2. Ancesters balance factor changes to =\n";
   theAVLTree->Insert(createNewNode(15));
   theAVLTree->PrintTree();
   cout<< "\nEND TESTING CASE 2\n\n";
   delete theAVLTree;
   cout<< "-----------------------------------------------\n";
   cout<< "-----------------------------------------------\n";

   cout << "\nPress Enter to start the next test.\n\n";
   gets(ans);

   
   theAVLTree = new Code203_Tree();
   cout<< "-----------------------------------------------\n";
   cout<< "TESTING CASE 3a\n\n";
   
   cout << "\nAdding Node 50\n";
   theAVLTree->Insert(createNewNode(50));
   theAVLTree->PrintTree();
   
   cout << "\nAdding Node 20\n";
   theAVLTree->Insert(createNewNode(20));
   theAVLTree->PrintTree();
   
   cout << "\nAdding Node 70\n";
   theAVLTree->Insert(createNewNode(70));
   theAVLTree->PrintTree();
   
   cout << "\nAdding Node 60\n";
   theAVLTree->Insert(createNewNode(60));
   theAVLTree->PrintTree();
   
   cout << "\nAdding Node 90\n";
   theAVLTree->Insert(createNewNode(90));
   theAVLTree->PrintTree();
   
   cout << "\nAdding Node 95 to trigger test of case 3.\n";
   theAVLTree->Insert(createNewNode(95));
   theAVLTree->PrintTree();
   cout<< "\nEND TESTING CASE 3a\n\n";
   delete theAVLTree;
   cout<< "-----------------------------------------------\n";
   cout<< "-----------------------------------------------\n";

   cout << "\nPress Enter to start the next test.\n\n";
   gets(ans);

   
   theAVLTree = new Code203_Tree();
   cout<< "-----------------------------------------------\n";
   cout<< "TESTING CASE 3b\n\n";
   
   cout << "\nAdding Node 50\n";
   theAVLTree->Insert(createNewNode(50));
   theAVLTree->PrintTree();
   
   cout << "\nAdding Node 20\n";
   theAVLTree->Insert(createNewNode(20));
   theAVLTree->PrintTree();
   
   cout << "\nAdding Node 70\n";
   theAVLTree->Insert(createNewNode(70));
   theAVLTree->PrintTree();
   
   cout << "\nAdding Node 60\n";
   theAVLTree->Insert(createNewNode(60));
   theAVLTree->PrintTree();
   
   cout << "\nAdding Node 90\n";
   theAVLTree->Insert(createNewNode(90));
   theAVLTree->PrintTree();
   
   cout << "\nAdding Node 75 to trigger test of case 3.\n";
   theAVLTree->Insert(createNewNode(75));
   theAVLTree->PrintTree();
   cout<< "\nEND TESTING CASE 3b\n\n";
   delete theAVLTree;
   cout<< "-----------------------------------------------\n";
   cout<< "-----------------------------------------------\n";

   cout << "\nPress Enter to start the next test.\n\n";
   gets(ans);

     
   theAVLTree = new Code203_Tree();
   cout<< "-----------------------------------------------\n";
   cout<< "TESTING CASE 4a\n\n";
   
   cout << "\nAdding Node 50\n";
   theAVLTree->Insert(createNewNode(50));
   theAVLTree->PrintTree();
   
   cout << "\nAdding Node 20\n";
   theAVLTree->Insert(createNewNode(20));
   theAVLTree->PrintTree();
   
   cout << "\nAdding Node 70\n";
   theAVLTree->Insert(createNewNode(70));
   theAVLTree->PrintTree();
   
   cout << "\nAdding Node 30\n";
   theAVLTree->Insert(createNewNode(30));
   theAVLTree->PrintTree();
   
   cout << "\nAdding Node 15\n";
   theAVLTree->Insert(createNewNode(15));
   theAVLTree->PrintTree();
   
   cout << "\nAdding Node 10 to trigger test of case 4.\n";
   theAVLTree->Insert(createNewNode(10));
   theAVLTree->PrintTree();

   cout<< "\nEND TESTING CASE 4a\n\n";
   delete theAVLTree;
   cout<< "-----------------------------------------------\n";
   cout<< "-----------------------------------------------\n";

   
   cout << "\nPress Enter to start the next test.\n\n";
   gets(ans);

     
   theAVLTree = new Code203_Tree();
   cout<< "-----------------------------------------------\n";
   cout<< "TESTING CASE 4b\n\n";
   
   cout << "\nAdding Node 50\n";
   theAVLTree->Insert(createNewNode(50));
   theAVLTree->PrintTree();
   
   cout << "\nAdding Node 20\n";
   theAVLTree->Insert(createNewNode(20));
   theAVLTree->PrintTree();
   
   cout << "\nAdding Node 70\n";
   theAVLTree->Insert(createNewNode(70));
   theAVLTree->PrintTree();
   
   cout << "\nAdding Node 30\n";
   theAVLTree->Insert(createNewNode(30));
   theAVLTree->PrintTree();
   
   cout << "\nAdding Node 15\n";
   theAVLTree->Insert(createNewNode(15));
   theAVLTree->PrintTree();
   
   cout << "\nAdding Node 17 to trigger test of case 4.\n";
   theAVLTree->Insert(createNewNode(17));
   theAVLTree->PrintTree();

   cout<< "\nEND TESTING CASE 4b\n\n";
   delete theAVLTree;
   cout<< "-----------------------------------------------\n";
   cout<< "-----------------------------------------------\n";

   cout << "\nPress Enter to start the next test.\n\n";
   gets(ans);

   
   theAVLTree = new Code203_Tree();
   cout<< "-----------------------------------------------\n";
   cout<< "TESTING CASE 5a\n\n";
   
   cout << "\nAdding Node 50\n";
   theAVLTree->Insert(createNewNode(50));
   theAVLTree->PrintTree();
   
   cout << "\nAdding Node 20\n";
   theAVLTree->Insert(createNewNode(20));
   theAVLTree->PrintTree();
   
   cout << "\nAdding Node 70\n";
   theAVLTree->Insert(createNewNode(70));
   theAVLTree->PrintTree();
   
   cout << "\nAdding Node 15\n";
   theAVLTree->Insert(createNewNode(15));
   theAVLTree->PrintTree();
   
   cout << "\nAdding Node 30\n";
   theAVLTree->Insert(createNewNode(30));
   theAVLTree->PrintTree();
     
   cout << "\nAdding Node 25 to trigger test of case 5.\n";
   theAVLTree->Insert(createNewNode(25));
   theAVLTree->PrintTree();
   cout<< "\nEND TESTING CASE 5a\n\n";
   delete theAVLTree;
   cout<< "-----------------------------------------------\n";
   cout<< "-----------------------------------------------\n";

   cout << "\nPress Enter to start the next test.\n\n";
   gets(ans);

   
   theAVLTree = new Code203_Tree();
   cout<< "-----------------------------------------------\n";
   cout<< "TESTING CASE 5b\n\n";
   
   cout << "\nAdding Node 50\n";
   theAVLTree->Insert(createNewNode(50));
   theAVLTree->PrintTree();
   
   cout << "\nAdding Node 20\n";
   theAVLTree->Insert(createNewNode(20));
   theAVLTree->PrintTree();
   
   cout << "\nAdding Node 70\n";
   theAVLTree->Insert(createNewNode(70));
   theAVLTree->PrintTree();
   
   cout << "\nAdding Node 15\n";
   theAVLTree->Insert(createNewNode(15));
   theAVLTree->PrintTree();
   
   cout << "\nAdding Node 30\n";
   theAVLTree->Insert(createNewNode(30));
   theAVLTree->PrintTree();
     
   cout << "\nAdding Node 35 to trigger test of case 5.\n";
   theAVLTree->Insert(createNewNode(35));
   theAVLTree->PrintTree();
   cout<< "\nEND TESTING CASE 5b\n\n";
   delete theAVLTree;
   cout<< "-----------------------------------------------\n";
   cout<< "-----------------------------------------------\n";

   cout << "\nPress Enter to start the next test.\n\n";
   gets(ans);

      
   theAVLTree = new Code203_Tree();
   cout<< "-----------------------------------------------\n";
   cout<< "TESTING CASE 6a\n\n";
   
   cout << "\nAdding Node 50\n";
   theAVLTree->Insert(createNewNode(50));
   theAVLTree->PrintTree();
   
   cout << "\nAdding Node 20\n";
   theAVLTree->Insert(createNewNode(20));
   theAVLTree->PrintTree();
   
   cout << "\nAdding Node 70\n";
   theAVLTree->Insert(createNewNode(70));
   theAVLTree->PrintTree();
   
   cout << "\nAdding Node 60\n";
   theAVLTree->Insert(createNewNode(60));
   theAVLTree->PrintTree();
   
   cout << "\nAdding Node 90\n";
   theAVLTree->Insert(createNewNode(90));
   theAVLTree->PrintTree();
   cout<< "\n***** Adding Node to trigger test of case 6\n";
   
   cout << "\nAdding Node 55\n";
   theAVLTree->Insert(createNewNode(55));
   theAVLTree->PrintTree();
   cout<< "\nEND TESTING CASE 6a\n\n";
   delete theAVLTree;
   cout<< "-----------------------------------------------\n";
   cout<< "-----------------------------------------------\n";

      cout << "\nPress Enter to start the next test.\n\n";
   gets(ans);
      
   theAVLTree = new Code203_Tree();
   cout<< "-----------------------------------------------\n";
   cout<< "TESTING CASE 6b\n\n";
   
   cout << "\nAdding Node 50\n";
   theAVLTree->Insert(createNewNode(50));
   theAVLTree->PrintTree();
   
   cout << "\nAdding Node 20\n";
   theAVLTree->Insert(createNewNode(20));
   theAVLTree->PrintTree();
   
   cout << "\nAdding Node 70\n";
   theAVLTree->Insert(createNewNode(70));
   theAVLTree->PrintTree();
   
   cout << "\nAdding Node 60\n";
   theAVLTree->Insert(createNewNode(60));
   theAVLTree->PrintTree();
   
   cout << "\nAdding Node 90\n";
   theAVLTree->Insert(createNewNode(90));
   theAVLTree->PrintTree();
   cout<< "\n***** Adding Node to trigger test of case 6\n";
   
   cout << "\nAdding Node 65\n";
   theAVLTree->Insert(createNewNode(65));
   theAVLTree->PrintTree();
   cout<< "\nEND TESTING CASE 6b\n\n";
   delete theAVLTree;
   cout<< "-----------------------------------------------\n";
   cout<< "-----------------------------------------------\n";

   cout << "\nAll testing complete.\n";
   cout << "\nPress Enter to terminate the application.\n\n";
   gets(ans);}




AVLTreeNode *createNewNode(int key)
{
   AVLTreeNode *temp = new AVLTreeNode();
   temp->key = key;
   temp->left = NULL;
   temp->right = NULL;
   temp->parent = NULL;
   temp->balanceFactor = '=';
   return temp;
}
