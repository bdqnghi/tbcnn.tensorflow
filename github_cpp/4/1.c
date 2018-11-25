

#include <iostream>
#include <stack>
#include <iomanip>
using namespace std;


void displayTowers(stack<int>, stack<int>, stack<int>); 
int isGameFinished(stack<int>, stack <int>, stack<int>); 

int main(){

stack <int> tower1; 
stack <int> tower2; 
stack <int> tower3; 
int size; 
int moveCounter = 0; 
string resp;

do{
cout << "Welcome to Tower of Hanoi!" << endl;
cout << "How many disks do you want to use? " << endl;

cin >> size;



while(size != 0 ){  

tower1.push(size);

size --;

}

cout << "Your job is to transfer the disks from the leftmost tower(1) to the rightmost (3)." << endl;


displayTowers(tower1, tower2, tower3);
    




    
int moveFrom, moveTo; 
int gameFinished = 0; 
int valHolder; 
do{
    
    cout << "Enter Your Move (to from):" << endl;
    cin >> moveFrom >> moveTo;
    cout << endl;
    
    
    
    if(moveFrom < 1 || moveFrom > 3){
        
        cout << "INVALID MOVE !!!!, try again" << endl;
        cout << "Enter Your Move (to from):" << endl;
        cin >> moveFrom >> moveTo;
        cout << endl;
        
    }
    
    if(moveTo < 1 || moveTo > 3){
        
        cout << "INVALID MOVE !!!!, try again" << endl;
        cout << "Enter Your Move (to from):" << endl;
        cin >> moveFrom >> moveTo;
        cout << endl;
        
    }
    
    
    
    
    switch(moveFrom){
        
        case 1:
            if(moveTo == 2){
                
                if(tower2.empty()){
                    
                    valHolder = tower1.top(); 
                
                    
                
                    tower1.pop(); 
                    tower2.push(valHolder);  
                
                    
                    
                    displayTowers(tower1, tower2, tower3);
                    ++ moveCounter;
                    gameFinished = isGameFinished(tower1, tower2,tower3);
                    
                }
                    else if(tower1.top() < tower2.top()){
                    
                    valHolder = tower1.top(); 
                
                    
                
                    tower1.pop(); 
                    tower2.push(valHolder);  
                
                    
                    
                    displayTowers(tower1, tower2, tower3);
                    ++ moveCounter;
                    gameFinished = isGameFinished(tower1, tower2,tower3);
                    
                    
                }
                
                else if(tower1.top() > tower2.top()){
                    
                    cout << "illegal Move! Re-Enter...." << endl;
                    
                    
                    
                }
                
                
            }
            
            else if(moveTo == 3){
                
            
               
                if(tower3.empty()){
                    
                    valHolder = tower1.top(); 
                
                    
                
                    tower1.pop(); 
                    tower3.push(valHolder);  
                
                    
                    
                    displayTowers(tower1, tower2, tower3);
                    ++ moveCounter;
                    gameFinished = isGameFinished(tower1, tower2,tower3);
                    
                    
                }
                    else if(tower1.top() < tower3.top()){
                    
                    valHolder = tower1.top(); 
                
                    
                
                    tower1.pop(); 
                    tower3.push(valHolder);  
                
                    
                    
                    displayTowers(tower1, tower2, tower3);
                    ++ moveCounter;
                    gameFinished = isGameFinished(tower1, tower2,tower3);
                    
                }
                
                else if(tower1.top() > tower3.top()){
                    
                    cout << "illegal Move! Re-Enter...." << endl;
                    
                    
                    
                }
            
                
            }
            
            break;
        
        case 2:
             if(moveTo == 1){
                
                     if(tower1.empty()){
                    
                    valHolder = tower2.top(); 
                
                    
                
                    tower2.pop(); 
                    tower1.push(valHolder);  
                
                    
                    
                    displayTowers(tower1, tower2, tower3);
                    ++ moveCounter;
                    gameFinished = isGameFinished(tower1, tower2,tower3);
                    
                }
                    else if(tower2.top() < tower1.top()){
                    
                    valHolder = tower2.top(); 
                
                    
                
                    tower2.pop(); 
                    tower1.push(valHolder);  
                
                    
                    
                    displayTowers(tower1, tower2, tower3);
                    ++ moveCounter;
                    gameFinished = isGameFinished(tower1, tower2,tower3);
                }
                
                else if(tower2.top() > tower1.top()){
                    
                    cout << "illegal Move! Re-Enter...." << endl;
                    
                    
                    
                }
   
            }
            
            else if(moveTo == 3){
                
                    if(tower3.empty()){
                    
                    valHolder = tower2.top(); 
                
                    
                
                    tower2.pop(); 
                    tower3.push(valHolder);  
                
                    
                    
                    displayTowers(tower1, tower2, tower3);
                    ++ moveCounter;
                    gameFinished = isGameFinished(tower1, tower2,tower3);
                }
                    else if(tower2.top() < tower3.top()){
                    
                    valHolder = tower2.top(); 
                
                    
                
                    tower2.pop(); 
                    tower3.push(valHolder);  
                
                    
                    
                    displayTowers(tower1, tower2, tower3);
                    ++ moveCounter;
                    gameFinished = isGameFinished(tower1, tower2,tower3);
                    
                }
                
                else if(tower2.top() > tower3.top()){
                    
                    cout << "illegal Move! Re-Enter...." << endl;
                    
                    
                    
                }
               
            }
            
            break;
        
        case 3:
              if(moveTo == 1){
                
                      if(tower1.empty()){
                    
                    valHolder = tower3.top(); 
                
                    
                
                    tower3.pop(); 
                    tower1.push(valHolder);  
                
                    
                    
                    displayTowers(tower1, tower2, tower3);
                    
                    ++ moveCounter;
                    gameFinished = isGameFinished(tower1, tower2,tower3);
                }
                    else if(tower3.top() < tower1.top()){
                    
                    valHolder = tower3.top(); 
                
                    
                
                    tower3.pop(); 
                    tower1.push(valHolder);  
                
                    
                    
                    displayTowers(tower1, tower2, tower3);
                    
                    ++ moveCounter;
                    gameFinished = isGameFinished(tower1, tower2,tower3);
                }
                
                else if(tower3.top() > tower1.top()){
                    
                    cout << "illegal Move! Re-Enter...." << endl;
                    
                    
                    
                }
                
                
            }
            
            else if(moveTo == 2){
                
                    if(tower2.empty()){
                    
                    valHolder = tower3.top(); 
                
                    
                
                    tower3.pop(); 
                    tower2.push(valHolder);  
                
                    
                    
                    displayTowers(tower1, tower2, tower3);
                    
                    ++ moveCounter;
                    gameFinished = isGameFinished(tower1, tower2,tower3);
                }
                    else if(tower3.top() < tower2.top()){
                    
                    valHolder = tower3.top(); 
                
                    
                
                    tower3.pop(); 
                    tower2.push(valHolder);  
                
                    
                    
                    displayTowers(tower1, tower2, tower3);
                    
                    
                    
                    ++ moveCounter;
                    
                    gameFinished = isGameFinished(tower1, tower2,tower3);
                }
                
                else if(tower3.top() > tower2.top()){
                    
                    cout << "illegal Move! Re-Enter...." << endl;
                    
                    
                    
                }
            }
            
            
            break;
        
        default:
            cout << "ERROR!!!, re-enter MOVE." << endl;
    }
    
}while(gameFinished != 1); 

cout << "Congradulations! you move the disks in " << moveCounter << "!!!!" << endl;
cout << "Would you like to play again(Yes or No): " << endl;
cin >> resp;





}while(resp == "Yes" || resp == "yes");


cout << "Thanks for Playing! Exiting..............." << endl;

return 0;

}


int isGameFinished(stack<int> stack1,stack<int> stack2,stack<int> stack3 ){
    
    int fin;
    
    
    if(stack1.empty() && stack2.empty()){
        
        fin = 1;
        
        
    }
    
    else 
        fin = 0;
    
    
    
    return fin;

    
    
    
}


void displayTowers(stack<int> stack1, stack<int> stack2, stack<int> stack3){
    
    int tower1Size = stack1.size();
    int tower2Size = stack2.size();
    int tower3Size = stack3.size();
    
    
    int tower1Arr[tower1Size];
    int tower2Arr[tower2Size];
    int tower3Arr[tower3Size];
    
    
    
    
    for(int i = 0; i < tower1Size; i++){
        
        tower1Arr[i] = stack1.top();
        stack1.pop();
        
    }
    
    for(int j = 0; j < tower2Size; j++){
        
        tower2Arr[j] = stack2.top();
        stack2.pop();
        
    }
    
    for(int k = 0; k < tower3Size; k++){
        
        tower3Arr[k] = stack3.top();
        stack3.pop();
        
    }
    
  
        
    
        
    
    
    for(int z = 0; z < tower1Size; z++){
        
        cout << "\t";
    
        for(int a = 0; a < tower1Arr[z]; a++){
    
            cout << "*";
        
        
        }
        
        cout << endl;
    }
    
   
    
    cout << endl;
    
    cout << "=================" << endl;
    
    
    
    
    
    for(int y = 0; y < tower2Size; y++){
        
        cout << "\t";
    
        for(int b = 0; b < tower2Arr[y]; b++){
    
            cout << "*";
        
        
        }
        
        cout << endl;
    }
    
    
  
    
    
    cout << endl;
    
    cout << "=================" << endl;
     
  
    
     for(int y = 0; y < tower3Size; y++){
        
        cout << "\t";
    
        for(int b = 0; b < tower3Arr[y]; b++){
    
            cout << "*";
        
        
        }
        
        cout << endl;
    }
    
    
   
    
    cout << endl;
    
    cout << "=================" << endl;
    
    
    
    
}





