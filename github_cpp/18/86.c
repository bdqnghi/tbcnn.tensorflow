

#include <iostream>
#include <vector>
#include <climits>
using namespace std;











class RodCutting {
private:
    int MemoizedCutRodAux(const vector<int>& p, vector<int>& r, size_t n);
public:
    
    int TopDownCutRod(const vector<int>& p, size_t n);
    
    int MemoizedCutRod(const vector<int>& p, size_t n);
    
    int BottomUpCutRod(const vector<int>& p, size_t n);
    
    int ExtendedBottomUpCutRod(const vector<int>& p, vector<int>& s, size_t n);
   
    void PrintCutRodSolution(const vector<int>& p, size_t n);
};


int RodCutting::TopDownCutRod(const vector<int>& p, size_t n) {
    if (n == 0) return 0;
    int q = INT_MIN;
    for (int i = 1; i <= n; i++) {
        q = max(q, p[i] + TopDownCutRod(p, n-i));  
    }
    return q;
}
    
int RodCutting::MemoizedCutRodAux(const vector<int>& p, vector<int>& r, size_t n) {
    
    if (r[n] >= 0) return r[n]; 
    int q = INT_MIN;
    if (n == 0) q = 0;
    else {
        for (int i = 1; i <= n; i++)
            q = max(q, p[i] + MemoizedCutRodAux(p, r, n-i));
    }
    r[n] = q;
    return q;
}

int RodCutting::MemoizedCutRod(const vector<int>& p, size_t n) {
    if (n == 0) return 0;
    vector<int>  r(n+1, INT_MIN);
    return  MemoizedCutRodAux(p, r, n);
}



int RodCutting::BottomUpCutRod(const vector<int>& p, size_t n) {
    vector<int> r(n+1, INT_MIN);
    r[0] = 0;
    for (int i = 1; i <= n; i++) {
        
        for (int j = 1; j <= i; j++) {
             r[i] = max(r[i], p[j]+r[i-j]);
        }
    }
    return r[n];
}

void RodCutting::PrintCutRodSolution(const vector<int>& p, size_t n) {
    vector<int> s(n+1, 0);
    cout << "Val: " << ExtendedBottomUpCutRod(p, s, n);
    cout << ", Solution: ";
    while (n > 0) {
        cout << s[n] << ", ";
        n = n - s[n];
    }

}


int RodCutting::ExtendedBottomUpCutRod(const vector<int>& p, vector<int>& s, size_t n) {
    vector<int> r(n+1, INT_MIN);
    r[0] = 0;
    for (int i = 1; i <= n; i++) {
        
        int q = INT_MIN;
        for (int j = 1; j <= i; j++) {
            
            if (q < (p[j] + r[i-j])) {
                q = p[j] + r[i-j];
                s[i] = j;
            }
        }
        r[i] = q;
    }
    return r[n];
}

int main() {
    vector<int> p = {0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
    RodCutting rc;

    cout << "------PrintCutRodSolution--------" << endl;
# if 0
    cout << "Rod Cut 4: ";
    rc.PrintCutRodSolution(p, 4);
    cout << endl;
    cout << "Rod Cut 5: ";
    rc.PrintCutRodSolution(p, 5);
    cout << endl;
    cout << "Rod Cut 6: ";
    rc.PrintCutRodSolution(p, 6);
    cout << endl;
    cout << "Rod Cut 7: ";
    rc.PrintCutRodSolution(p, 7);
    cout << endl;
    cout << "Rod Cut 8: ";
    rc.PrintCutRodSolution(p, 8);
    cout << endl;
    cout << "Rod Cut 9: ";
    rc.PrintCutRodSolution(p, 9);
    cout << endl;
#endif
    cout << "Rod Cut 15: ";
    rc.PrintCutRodSolution(p, 15); 
    cout << endl;
    cout << "Rod Cut 40: ";
    rc.PrintCutRodSolution(p, 40); 
    cout << endl;
    cout << "Rod Cut 100: ";
    rc.PrintCutRodSolution(p, 100);
    cout << endl;
   
    cout << "------BottomUpCutRod--------" << endl;
#if 0
    cout << rc.BottomUpCutRod(p, 4) << endl;
    cout << rc.BottomUpCutRod(p, 5) << endl;
    cout << rc.BottomUpCutRod(p, 6) << endl;
    cout << rc.BottomUpCutRod(p, 7) << endl;
    cout << rc.BottomUpCutRod(p, 8) << endl;
    cout << rc.BottomUpCutRod(p, 9) << endl;
#endif
    cout << rc.BottomUpCutRod(p, 40) << endl;
    cout << rc.MemoizedCutRod(p, 100) << endl;
#if 0
    cout << "------MemoizedCutRod--------" << endl;
    cout << rc.MemoizedCutRod(p, 4) << endl;
    cout << rc.MemoizedCutRod(p, 5) << endl;
    cout << rc.MemoizedCutRod(p, 6) << endl;
    cout << rc.MemoizedCutRod(p, 7) << endl;
    cout << rc.MemoizedCutRod(p, 8) << endl;
    cout << rc.MemoizedCutRod(p, 9) << endl;
    cout << rc.MemoizedCutRod(p, 40) << endl;
    cout << rc.MemoizedCutRod(p, 100) << endl;
#endif
    return 0;
}
