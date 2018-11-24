// Zayd Haque
// Tower of Hanoi Game using c++'s <stack>
#include <iostream>
#include <stack>
#include <iomanip>
using namespace std;

// function prototypes
void displayTowers(stack<int>, stack<int>, stack<int>); // displays tower
int isGameFinished(stack<int>, stack <int>, stack<int>); // checks if the game is finished

int main(){

stack <int> tower1; // tower 1
stack <int> tower2; // tower 2
stack <int> tower3; // tower 3 
int size; // size of the tower
int moveCounter = 0; // keeps count of the moves.
string resp;

do{
cout << "Welcome to Tower of Hanoi!" << endl;
cout << "How many disks do you want to use? " << endl;

cin >> size;



while(size != 0 ){  // adds the disks into tower1

tower1.push(size);
// used to check if the ints were added correctly cout << tower1.top() << endl;
size --;

}

cout << "Your job is to transfer the disks from the leftmost tower(1) to the rightmost (3)." << endl;


displayTowers(tower1, tower2, tower3);
    


// display the towers w/ DISKS like the handout, probs gonna use a function

    
int moveFrom, moveTo; // these are variables holding the data for where to move from and where to go 
int gameFinished = 0; // flag to be switched when the user finsihes the game
int valHolder; // holds the value to be moved.
do{
    // user enters their move 
    cout << "Enter Your Move (to from):" << endl;
    cin >> moveFrom >> moveTo;
    cout << endl;
    
    // input validation -------------------------------------------
    
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
    
    //---------------------------------------------------------------
    
    
    switch(moveFrom){
        
        case 1:
            if(moveTo == 2){
                
                if(tower2.empty()){
                    
                    valHolder = tower1.top(); // places what to move here in valHolder
                
                    //cout << valHolder << endl; checks if value placed right
                
                    tower1.pop(); // removes the top element
                    tower2.push(valHolder);  // adds valholder to tower2
                
                    //cout << tower2.top() << endl;  check if the move worked
                    // output the towers here
                    displayTowers(tower1, tower2, tower3);
                    ++ moveCounter;
                    gameFinished = isGameFinished(tower1, tower2,tower3);
                    
                }
                    else if(tower1.top() < tower2.top()){
                    
                    valHolder = tower1.top(); // places what to move here in valHolder
                
                    //cout << valHolder << endl; checks if value placed right
                
                    tower1.pop(); // removes the top element
                    tower2.push(valHolder);  // adds valholder to tower2
                
                    //cout << tower2.top() << endl;  check if the move worked
                    // output the towers here
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
                    
                    valHolder = tower1.top(); // places what to move here in valHolder
                
                    //cout << valHolder << endl; checks if value placed right
                
                    tower1.pop(); // removes the top element
                    tower3.push(valHolder);  // adds valholder to tower2
                
                    //cout << tower2.top() << endl;  check if the move worked
                    // output the towers here
                    displayTowers(tower1, tower2, tower3);
                    ++ moveCounter;
                    gameFinished = isGameFinished(tower1, tower2,tower3);
                    
                    
                }
                    else if(tower1.top() < tower3.top()){
                    
                    valHolder = tower1.top(); // places what to move here in valHolder
                
                    //cout << valHolder << endl; checks if value placed right
                
                    tower1.pop(); // removes the top element
                    tower3.push(valHolder);  // adds valholder to tower2
                
                    //cout << tower2.top() << endl;  check if the move worked
                    // output the towers here
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
                    
                    valHolder = tower2.top(); // places what to move here in valHolder
                
                    //cout << valHolder << endl; checks if value placed right
                
                    tower2.pop(); // removes the top element
                    tower1.push(valHolder);  // adds valholder to tower2
                
                    //cout << tower2.top() << endl;  check if the move worked
                    // output the towers here
                    displayTowers(tower1, tower2, tower3);
                    ++ moveCounter;
                    gameFinished = isGameFinished(tower1, tower2,tower3);
                    
                }
                    else if(tower2.top() < tower1.top()){
                    
                    valHolder = tower2.top(); // places what to move here in valHolder
                
                    //cout << valHolder << endl; checks if value placed right
                
                    tower2.pop(); // removes the top element
                    tower1.push(valHolder);  // adds valholder to tower2
                
                    //cout << tower2.top() << endl;  check if the move worked
                    // output the towers here
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
                    
                    valHolder = tower2.top(); // places what to move here in valHolder
                
                    //cout << valHolder << endl; checks if value placed right
                
                    tower2.pop(); // removes the top element
                    tower3.push(valHolder);  // adds valholder to tower2
                
                    //cout << tower2.top() << endl;  check if the move worked
                    // output the towers here
                    displayTowers(tower1, tower2, tower3);
                    ++ moveCounter;
                    gameFinished = isGameFinished(tower1, tower2,tower3);
                }
                    else if(tower2.top() < tower3.top()){
                    
                    valHolder = tower2.top(); // places what to move here in valHolder
                
                    //cout << valHolder << endl; checks if value placed right
                
                    tower2.pop(); // removes the top element
                    tower3.push(valHolder);  // adds valholder to tower2
                
                    //cout << tower2.top() << endl;  check if the move worked
                    // output the towers here
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
                    
                    valHolder = tower3.top(); // places what to move here in valHolder
                
                    //cout << valHolder << endl; checks if value placed right
                
                    tower3.pop(); // removes the top element
                    tower1.push(valHolder);  // adds valholder to tower2
                
                    //cout << tower2.top() << endl;  check if the move worked
                    // output the towers here
                    displayTowers(tower1, tower2, tower3);
                    
                    ++ moveCounter;
                    gameFinished = isGameFinished(tower1, tower2,tower3);
                }
                    else if(tower3.top() < tower1.top()){
                    
                    valHolder = tower3.top(); // places what to move here in valHolder
                
                    //cout << valHolder << endl; checks if value placed right
                
                    tower3.pop(); // removes the top element
                    tower1.push(valHolder);  // adds valholder to tower2
                
                    //cout << tower2.top() << endl;  check if the move worked
                    // output the towers here
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
                    
                    valHolder = tower3.top(); // places what to move here in valHolder
                
                    //cout << valHolder << endl; checks if value placed right
                
                    tower3.pop(); // removes the top element
                    tower2.push(valHolder);  // adds valholder to tower2
                
                    //cout << tower2.top() << endl;  check if the move worked
                    // output the towers here
                    displayTowers(tower1, tower2, tower3);
                    
                    ++ moveCounter;
                    gameFinished = isGameFinished(tower1, tower2,tower3);
                }
                    else if(tower3.top() < tower2.top()){
                    
                    valHolder = tower3.top(); // places what to move here in valHolder
                
                    //cout << valHolder << endl; checks if value placed right
                
                    tower3.pop(); // removes the top element
                    tower2.push(valHolder);  // adds valholder to tower2
                
                    //cout << tower2.top() << endl;  check if the move worked
                    // output the towers here
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
    
}while(gameFinished != 1); // keeps going till the game is finsihed

cout << "Congradulations! you move the disks in " << moveCounter << "!!!!" << endl;
cout << "Would you like to play again(Yes or No): " << endl;
cin >> resp;





}while(resp == "Yes" || resp == "yes");


cout << "Thanks for Playing! Exiting..............." << endl;

return 0;

}
// function IMPLEMENTATION -----------------------------------------------------------------------

int isGameFinished(stack<int> stack1,stack<int> stack2,stack<int> stack3 ){
    
    int fin;
    
    
    if(stack1.empty() && stack2.empty()){
        
        fin = 1;
        
        
    }
    
    else 
        fin = 0;
    
    
    
    return fin;

    
    
    
}

//-----------------------------------------------------------------------------------------------
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
    
  //  for(int h = 0; h < tower1Size; h ++){
        
    //    cout << "tower1 elements = " <<  h <<  ":" << tower1Arr[h] << endl;  ------------- TO CHECK IF THE COPYING WORKED ----------------
        
    //}displayTowers(tower1, tower2, tower3);
    
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

// ------------------------------------------------------------------------------------------------



