#include<iostream>
const int m=10;
 	int a1[5][5],b[5][5];
 	int a[m];
using namespace std;
class S{
	
		
int t;
public : 
S();
void push(int n);
int pop();
~S();
};
S::S(){
	t=-1;
}
void S::push(int n){
	if(t==m-1){
		cout<<"stack fll"<<endl;
		return;
	}
	t++;
	a[t]=n;
	
}
int S::pop(){
	if(t==-1){
		cout<<"EMPTY   "<<endl;
		return 0;
	}
	int d=a[t];
	t--;
	return d;
}
S::~S(){
	
}


void DFS(int n){
	
	int counter=0;
	S a2;
	
	a2.push(n);
	cout<<" "<<n<<" "<<endl;
		for(int j=0;j<5;j++){
				a1[j][n]=0;
			}
	
	for(int i=0;i<5;i++){
		
		if(a1[n][i]==1){
			counter++;
			for(int j=0;j<5;j++){
				a1[j][i]=0;
			}
			DFS(i);
			
	}
		
		}
		if(counter!=0){
			
			
				
		int d;
		d = a2.pop();
		
		return;		
			
		}
		
		
		
		
		
		
	}

	
	
	
	
	





int main(){

	
	cout<<"ENTER THE ADJACENCY MATRIX FOR THE SAME "<<endl;
	for(int i=0;i<5;i++){
		cout<<" row "<<i+1;
			cout<<endl;
				for(int j=0;j<5;j++){
					cout<<"ENTER THE COLUMN NO : "<<j+1<<"   ";
			cin>>a1[i][j];
		
		}
		cout<<endl;
	}

	for(int i=0;i<5;i++){
		
			cout<<endl;
				for(int j=0;j<5;j++){
					
			b[i][j]=a1[i][j];
		
		}
	
	}
	for(int i=0;i<5;i++){
		cout<<" [ ";
		for(int j=0;j<5;j++){
			cout<<" "<<b[i][j]<<"  ";
			
		}
		cout<<" ] "<<endl;
	}
	int n;
	cout<<"THE STARTING NODE ( 0 to 4) "<<endl;
	cin>>n;
	
	
	DFS(n);
	
	
	cout<<"CHECK WHETHER THE FOLLOWING GRAPH IS STRONGLY CONNECTED OR NOT :--> "<<endl;

	
	
	
	
	
	return 0;
	
}
	
	
	
	
	

