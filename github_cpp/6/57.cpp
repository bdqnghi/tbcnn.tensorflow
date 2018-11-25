
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int A, B, C;
bool visited[21][21][21] = {0};

void DepthFirstSearch(int a, int b, int c) {
    if (visited[a][b][c]) {
        return;
    }
    visited[a][b][c] = true;
    DepthFirstSearch(a - min(a, B - b), b + min(a, B - b), c); 
    DepthFirstSearch(a - min(a, C - c), b, c + min(a, C - c)); 
    DepthFirstSearch(a + min(b, A - a), b - min(b, A - a), c); 
    DepthFirstSearch(a, b - min(b, C - c), c + min(b, C - c)); 
    DepthFirstSearch(a + min(c, A - a), b, c - min(c, A - a)); 
    DepthFirstSearch(a, b + min(c, B - b), c - min(c, B - b)); 
}

int main() {
    ofstream fout("milk3.out");
    ifstream fin("milk3.in");

    fin >> A >> B >> C;

    DepthFirstSearch(0, 0, C);

    vector<int> solutions;
    for (int c = 0; c <= C; c++) {
        if (visited[0][C - c][c]) {
            solutions.push_back(c);
        }
    }
    for (int i = 0; i < solutions.size(); i++) {
        fout << solutions[i] << ((i == solutions.size() - 1) ? '\n' : ' ');
    }

    return 0;
}