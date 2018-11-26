#include<iostream>
#include<stack>
using namespace std;

//[file=mazepath.html title=""
const int RIGHT = 6;
const int DOWN = 5;
void PrintLocation(int down, int right) {
    string str = std::to_string(down) + " " + std::to_string(right);
    std::cout<<"["<<str<<"]"<<std::endl;
}

void PrintMaze(int array[][RIGHT], int down, int right) {
    for(int i=0; i<DOWN; i++) {
        for(int j=0; j<RIGHT; j++) {
            if(down == i && j == right)
                std::cout<<"["<<"x"<<"]";
            else
                std::cout<<"["<<array[i][j]<<"]";
        }
        std::cout<<std::endl;
    }
    std::cout<<std::endl;
}

bool DepthFirstSearch(int array[][RIGHT], int down, int right) {
    if(down < DOWN && right < RIGHT) {
        if(array[down][right] == 0 || array[down][right] == 2) {
            PrintMaze(array, down, right);
            if(DepthFirstSearch(array, down+1, right)) {
                PrintLocation(down, right); 
                return true;
            }

            if(array[down][right] == 2) {
                std::cout<<"Done"<<std::endl;
                PrintLocation(down, right); 
                return true;
            }

            if(DepthFirstSearch(array, down, right+1))     {
                PrintLocation(down, right); 
                return true;
            }
        }
    }
    return false;
}
//]

int main(int argc, char *argv[]) {
    const int row = 5;
    const int col = 6;
    int Array[row][col] = {
        {0, 1, 0, 1, 1, 1},
        {0, 0, 0, 0, 0, 0},
        {0, 1, 1, 0, 1, 0},
        {0, 0, 0, 0, 1, 0},
        {0, 0, 0, 0, 1, 2}
    };

    int right = 0;
    int down = 0;
    DepthFirstSearch(Array, down, right);
    std::cout<<std::endl;
}
