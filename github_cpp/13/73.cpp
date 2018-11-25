#include <iostream>
#include <cstdlib>
#include <ctime>        
#include <fstream>     
#include <limits>     
#include<windows.h>
using namespace std;

struct node  
{
    int data;
    node *next, *prev;
  
    

};
node *bighead,*tail;
static int setValue = 0; 

void display()
{
    node *curPtr = bighead;
    while(curPtr!=NULL)
    {
        cout<<curPtr->data<<" ";

        curPtr=curPtr->next;
    }
  cout<<endl;
}

void add(node *head,int item)
{
    if(head==NULL) 
    {
        node *newPtr = new node;
        newPtr->data = item;
        bighead = newPtr;
        tail = newPtr;
        newPtr->prev = NULL;
        newPtr->next= NULL;

    }

    else
    {
        node *newPtr = new node;
        newPtr->data = item;
        tail->next = newPtr;
        newPtr->prev = tail;  
        tail = newPtr;
        newPtr->next = NULL;

    }
}
void outFile()
{
     int maxsize;
     int value;
     int user;
     bool bFail;
    srand(time(0)); 

              do{
                    cout<<"\nEnter the data set you wish to sort:<greater than zero (0)> ";
                    cin>>maxsize;  

                   try{
                            if(maxsize < 0){
                            throw -1;
                        }
                            else if(cin.fail()){ 
                            throw 'a';
                        }

                    } catch(int a) {
                        cout<<"\nDo not enter negative number...\n" <<endl;
                        cin.clear();
                        cin.ignore();
                        

                    } catch(...) {
                        cout<<"\nPlease only enter other number greater than zero...\n"<< endl;
                        cin.clear();
                        cin.ignore();
                        

                    }

                }while(maxsize<=0);

                 setValue = maxsize;
                 ofstream output;
                 output.open("output.txt");
                if(output.fail())
                {
                  cerr<<"Error while opening file";
                  exit(1);
                }
             for(int i=0;i < maxsize;i++) 
               {
                value = (1 +rand()% 10); 
                output<<value<<" ";
               }
              output.close();
}

void inputFile()
{
    bighead = NULL;
     ifstream input;
      input.open("output.txt");
      if(input.fail())
      {
          cerr<<"Error while opening file"<<endl;
          exit(1);
      }

      while(true)
      {   int x;
          input>>x;
          if(input.eof()) break;

          add(bighead,x);
      }

      input.close();
}
void BubbleSort()
{ 

     inputFile();
     display();
    bool noexchange;
    int pass=1;
    node *r = bighead;

    while((r != NULL )&& (!noexchange))
        {
            cout<<endl;
         noexchange=true;
         if(setValue <=20)
            cout<<"  Pass : "<<pass<<endl;

        node *q=bighead;
        while(q->next != NULL){
            if(q->data > q->next->data){
                cout<<"\nSwap: "<<q->data<< " with "<<q->next->data<< " : "<<endl;
                swap(q->data, q->next->data);
                 noexchange=false;
            }
            q=q->next; 

              if(setValue <=20)
                  display();

        }
        r=r->next; 

        pass++;
    }
    cout<<endl;
    display();
}
void menu()
{
    char val;

     do{

            BubbleSort();
            cout<<"Do you wish to sort again bubble sort..<y/n>: ";
            cin>>val;
             outFile();


     }while(val== 'y');

}
int main()
{


    outFile();  
     menu();
    cout<<endl;

    cout<<"System Exiting...Thank You...."<<endl;
    return 0;
}
