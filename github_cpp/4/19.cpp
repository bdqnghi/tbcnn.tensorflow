#include<iostream>
#include<conio.h>
using namespace std;

class Hanoi
{
 		int a_top,b_top,c_top;
		int *tower_a,*tower_b,*tower_c; 		
 		public:
			void hanoi(int,char*,char*,char*);   
			void initialize(int);
			void process(int);
			void evenProcessing();
			void oddProcessing();	 
				 
}; 		
int no_of_movements=0;
void Hanoi::hanoi(int disk,char *source,char *dest,char *spare)
{		

       if(disk>0)
        {
            hanoi(disk-1,source,spare,dest);
            cout<<source<<" --> "<<dest<<endl;
             no_of_movements++;		
            hanoi(disk-1,spare,dest,source);
        }	  
}
void Hanoi::initialize(int disks)
{
 	  tower_a=new int[disks];
 	   tower_b=new int[disks];
 	    tower_c=new int[disks];
 	    
 	     tower_a[0]=999;
            tower_b[0]=999;
            tower_c[0]=999;
 	    for(int i=1;i<disks;i++)
 	    {
		  		tower_a[i]=disks-i+1;
				  tower_b[i]=0;
				  tower_c[i]=0;	 			
		  			
       }	
		 a_top=disks;
            b_top=0;
            c_top=0;		
 	  
 	  
} 	  
void Hanoi::process(int disks)
{	 if(disks%2==0)
                evenProcessing();
            else         
                oddProcessing();
} 	  
void Hanoi::evenProcessing()
{	 int number_of_movements=0;
            
            while(1)
            {
                if(tower_a[a_top]==999 && tower_b[b_top]==999)
                    break;
            if(tower_a[a_top] < tower_b[b_top])
            {
                cout<<"A --> B\n";
                tower_b[++b_top]=tower_a[a_top--];
                tower_a[a_top+1]=0;                
            }
            else
            {
                cout<<"B --> A\n";
                tower_a[++a_top]=tower_b[b_top--];
                tower_b[b_top+1]=0;
            }
            number_of_movements++;
            if(tower_a[a_top] < tower_c[c_top])
            {
                cout<<"A --> C\n";
                tower_c[++c_top]=tower_a[a_top--];
                tower_a[a_top+1]=0;
            }
            else
            {
                cout<<"C --> A\n";
                tower_a[++a_top]=tower_c[c_top--];
                tower_c[c_top+1]=0;
            }
            number_of_movements++;
            if(tower_c[c_top] < tower_b[b_top])
            {
                cout<<"C --> B\n";
                tower_b[++b_top]=tower_c[c_top--];
                tower_c[c_top+1]=0;
            }
            else
            {
                cout<<"B --> C\n";
                tower_c[++c_top]=tower_b[b_top--];
                tower_b[b_top+1]=0;
            }
            number_of_movements++;
            }    
            cout<<"\nTotal Disk Movements:"<<number_of_movements;
 	  
 	  
}
void Hanoi::oddProcessing()
{	 int number_of_movements=0;
            
            while(1)
            {                
                if(tower_a[a_top]==999 && tower_b[b_top]==999)
                    break;
                if(tower_a[a_top] < tower_c[c_top])
                {
                     cout<<"A --> C\n";
                     tower_c[++c_top]=tower_a[a_top--];
                     tower_a[a_top+1]=0;
                }
                else
                {
                     cout<<"C --> A\n";
                     tower_a[++a_top]=tower_c[c_top--];
                     tower_c[c_top+1]=0;
                }
                number_of_movements++;
                if(tower_a[a_top]==999 && tower_b[b_top]==999)
                    break;
                if(tower_a[a_top] < tower_b[b_top])
                {
                     cout<<"A --> B\n";
                     tower_b[++b_top]=tower_a[a_top--];
                     tower_a[a_top+1]=0;                
                }
                else
                {
                     cout<<"B --> A\n";
                     tower_a[++a_top]=tower_b[b_top--];
                     tower_b[b_top+1]=0;
                }
                number_of_movements++;
                if(tower_a[a_top]==999 && tower_b[b_top]==999)
                    break;
                if(tower_c[c_top] < tower_b[b_top])
                {
                     cout<<"C --> B\n";
                     tower_b[++b_top]=tower_c[c_top--];
                     tower_c[c_top+1]=0;
                }
                else
                {
                     cout<<"B --> C\n";
                     tower_c[++c_top]=tower_b[b_top--];
                     tower_b[b_top+1]=0;
                }
                number_of_movements++;
            }
            cout<<"\nTotal Disk Movements:"<<number_of_movements;
 	  
		
} 	  
int main()
{	 int disks,ch;
	 char ch1;
	 Hanoi obj;
 	 do{
	  cout<<"\n Enter No. of Disks :";
    cin>>disks;
    
	 if(disks<1)
	 {
	  	  cout<<"\n Wrong Number of Disks";
	  	  getch();
	  	  continue;
    }		  	 
   system("cls");
    cout<<"\n Menu";
 	 cout<<"\n 1-Recursive Tower Of hanoi";
 	 cout<<"\n 2-Non Recursive Tower of hanoi";
 	 cout<<"\n 3-Exit";
 	 cout<<"\n Enter your choice:";
 	 cin>>ch;
 	 if(ch==1)
 	 {	  obj.hanoi(disks,"A","B","C");	
	 	  cout<<"Total Disk Movements:"<<no_of_movements; 
	 }
	  	 
    else if(ch==2)
 	 {		obj.initialize(disks);
 	 		obj.process(disks);
	 }
	 else if(ch==3);
    else
	 	  cout<<"\n Wrong Choice Entered !!"; 	 
   if(ch!=3){
	cout<<"\n Do you want to continue?(y/n)?:";
   cin>>ch1;
	}
   }while(ch!=3 && (ch1=='y' || ch1=='Y'));  	  
 	
 	 return 0;
}




