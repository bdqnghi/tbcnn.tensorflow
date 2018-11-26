#include <iostream>
#include <cstdio>
using namespace std;

const int MAX_LAYER = 100; // Hanoi Tower 最多幾層

// Hanoi Tower Data
int rod[3][MAX_LAYER];
int rod_height[3];

void hanoi_init(int layer);
void hanoi_move_tower(int layer);
void _hanoi_move_tower(int layer, int start_rod, int end_rod);
void hanoi_single_move(int start_rod, int end_rod);
void print_hanoi_tower();

int main(){
    hanoi_init(8);
    print_hanoi_tower();
    getchar();
    hanoi_move_tower(8);
}

// function implementation
void hanoi_init(int layer){
    rod_height[0] = layer;
    rod_height[1] = rod_height[2] = 0;

    for(int i=0; i<layer; i++){
        rod[0][i] = 8 - i; // 8 ~ 1
    }
}

void hanoi_move_tower(int layer){
    _hanoi_move_tower(layer, 0, 2);
}

void _hanoi_move_tower(int layer, int start_rod, int end_rod){
    if(layer == 1){
        hanoi_single_move(start_rod, end_rod);
        return;
    }

    int last_rod = 3 - start_rod - end_rod; // sum of three rod = 3 ( 0+1+2 )
    _hanoi_move_tower(layer-1, start_rod, last_rod);
    hanoi_single_move(start_rod, end_rod);
    _hanoi_move_tower(layer-1, last_rod, end_rod);
}

void hanoi_single_move(int start_rod, int end_rod){
    if(rod_height[start_rod] < 1){
        cout << "Error: move empty rod" << endl;
        return;
    }
    int move_disk = rod[start_rod][ rod_height[start_rod] - 1 ];
    rod_height[start_rod]--;
    rod[end_rod][ rod_height[end_rod] ] = move_disk;
    rod_height[end_rod]++;

    print_hanoi_tower();
    getchar();
}

void print_hanoi_tower(){
    const char rod_name[3] = {'a', 'b', 'c'};
    for(int i=0; i<3; i++){
        cout << rod_name[i] << ": ";
        for(int j=0; j<rod_height[i]; j++){
            if( j != 0 )
                cout << ", ";
            cout << rod[i][j];
        }
        cout << endl;
    }
}
