#include <iostream.h>
class Disk    
{
public:
int value;
Disk* next;
};
class Tower 
{
public:
int size;
Disk* current;
Tower()
{
  size=0;
  current=NULL;
}
int peep();
bool push(int);
bool pop();
bool isEmpty();
int getTowerSize();
void printTowerSize();
void printTowerDisks();
void printTowerMenu();
};
int Tower::peep()
{
      return this->current->value;
}
bool Tower::push(int ele)
{
Disk*      temp;
temp=new Disk;
      if(current==NULL)
      {
            temp->next=NULL;
            }
      else
      {
            temp->next=current;
      }
      temp->value=ele;
      this->current=temp;
      size++;
    return false;
}
bool Tower::pop()
{
      if(isEmpty())
      {
      cout<<"\nTower is Empty\n";      
      return false;
      }
      else
      {
      current=current->next;
      size=size--;
      }
      return true;
}
bool Tower::isEmpty()
{
      if(getTowerSize()==0)
      return true;
      return false;
}
int Tower::getTowerSize()
{
return size;
}
void Tower::printTowerSize()
{
cout<<"\nThe Size of the Tower:"<<size<<"\n";
}
void Tower::printTowerDisks()
{
      if(this->isEmpty())
      {
      cout<<"-----\n";
      cout<<" "<<endl;
      cout<<"-----\n";
      return;
      }
Disk *curr2;      
curr2=this->current; 
cout<<"-----\n";
            cout<<"Tower\n";
            cout<<"-----\n";
            int i=0;
            while(curr2 !=NULL)
            {
                  if(i>4)
                  break;
                  i++;
                  cout<<" |"<<curr2->value<<"|\n";
                  curr2=curr2->next;
            }
}
void createSourceTower(Tower *source,int numberOfDisks)
{
      for(int i=numberOfDisks;i>0;i--)
      {
      source->push(i);              
      }
}
void moveDisk(Tower *source,Tower *dest) 
 {
dest->push(source->current->value );
source->pop();
 }
void hanoi( int N, Tower *source, Tower *dest,Tower  *aux ) 
{
    if (N > 0 )
      {
      hanoi(N - 1, source, aux, dest);      
      moveDisk(source,dest);                
      hanoi(N - 1, aux, dest, source);      
      }
      }
void main()
{
Tower *source,*destination,*auxillary;
source=new Tower;
destination=new Tower;
auxillary=new Tower;
int numberOfDisks;
cout<<"Enter number of Disks in the source Tower";
cin>>numberOfDisks;
createSourceTower(source,numberOfDisks);
cout<<"********************************"<<endl;
cout<<"Initial Scenario of the Towers "<<endl;
cout<<"Source"<<endl;
source->printTowerDisks ();
cout<<"Auxillary"<<endl;
auxillary->printTowerDisks ();
cout<<"Destination"<<endl;
destination->printTowerDisks ();
hanoi( numberOfDisks,source,  destination, auxillary );
cout<<"**********************************"<<endl;
cout<<"Final Scenario of the Towers "<<endl;
cout<<"Source"<<endl;
source->printTowerDisks();
cout<<"Auxillary"<<endl;
auxillary->printTowerDisks ();
cout<<"Destination"<<endl;
destination->printTowerDisks ();
cout<<"***********************************"<<endl;
}
