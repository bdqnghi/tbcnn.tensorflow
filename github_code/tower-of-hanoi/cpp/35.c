#include <iostream>
using std::cin;
using std::cerr;
using std::cout;
using std::endl;

void TowerOfHanoi(int count, int source, int destination, int spare){
        cerr << "TowerOfHanoi(" << count << ", " << source << ", " << destination << ", " << spare << ")\n";
        if( count == 1){
                cout << "Move the top disk from " << source << " to " << destination << endl;
        }else{
                TowerOfHanoi( count-1, source, spare, destination );
                TowerOfHanoi( 1, source, destination, spare);
                TowerOfHanoi( count-1, spare, destination, source);
        }
}

int main(){
        int numRings = -1;
        int startingTower = 1;
        int spareTower = 2;
        int endingTower = 3;

        cin >> numRings;
        //            count     source         destination  spare
        TowerOfHanoi( numRings, startingTower, endingTower, spareTower);

        return 0;
} 
/* output (2 is input)
2
TowerOfHanoi(2, 1, 3, 2)
TowerOfHanoi(1, 1, 2, 3)
Move the top disk from 1 to 2
TowerOfHanoi(1, 1, 3, 2)
Move the top disk from 1 to 3
TowerOfHanoi(1, 2, 3, 1)
Move the top disk from 2 to 3
*/ 
