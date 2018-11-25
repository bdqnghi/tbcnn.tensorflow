

#include <iostream>
#include <vector>
#include <climits>
#include <iomanip>
using namespace std;

class RodCutting {
public:
    RodCutting(vector<int>& xp) { p = xp; t = p.size()-1;}
    
    int TopDownCutRod(size_t n);
    
    int MemoizedCutRod(size_t n);
    
    int BottomUpCutRod(size_t n);
    
    int ExtendedBottomUpCutRod(vector<int>& s, size_t n);
    void PrintCutRodSolution(size_t n);
private:
    int MemoizedCutRodAux(vector<int>& r, size_t n);
    int BottomUpCutRodAux(size_t n);
private:
    vector<int>   p;
    size_t        t;  
};


int RodCutting::TopDownCutRod(size_t n) {
    if (n > t) { 
        cout << "Not supported for size: " << n << "larger than " << t << endl;
        cout << "Pls call BottomUpCutRodAux instead."<< endl;
        return -1;
    }
    if (n == 0) return 0;
    int q = INT_MIN;
    for (int i = 1; i <= n; i++) {
        q = max(q, p[i] + TopDownCutRod(n-i));  
    }
    return q;
}
    
int RodCutting::MemoizedCutRodAux(vector<int>& r, size_t n) {
    
    if (r[n] >= 0) return r[n]; 
    int q = INT_MIN;
    if (n == 0) q = 0;
    else {
        for (int i = 1; i <= n; i++)
            q = max(q, p[i] + MemoizedCutRodAux(r, n-i));
    }
    r[n] = q;
    return q;
}

int RodCutting::MemoizedCutRod(size_t n) {
    if (n > t) { 
        cout << "Not supported for size: " << n << "larger than " << t << endl;
        cout << "Pls call BottomUpCutRodAux instead."<< endl;
        return -1;
    }
    if (n == 0) return 0;
    vector<int>  r(n+1, INT_MIN);
    return  MemoizedCutRodAux(r, n);
}


int RodCutting::BottomUpCutRodAux(size_t n) {
    vector<int> r(n+1, INT_MIN);
    r[0] = 0;
    for (int i = 1; i <= n; i++) {
        
        for (int j = 1; j <= i; j++) {
            r[i] = max(r[i], p[j]+r[i-j]);
        }
    }
    return r[n];
}


int RodCutting::BottomUpCutRod(size_t n) {
    if (n <= t)
        return BottomUpCutRodAux(n);
    else
        return (n/t)*BottomUpCutRodAux(t) + BottomUpCutRodAux(n%t);;
}

void RodCutting::PrintCutRodSolution(size_t n) {
    vector<int> s;
    if (n > t) {
        vector<int> s1(t+1, 0);
        s.resize(n%t+1, 0);
        cout << "Revenue: " << setw(5) << (n/t)*ExtendedBottomUpCutRod(s1, t) + ExtendedBottomUpCutRod(s, n%t);
        cout << ", Solution: ";
        for (int i = 0, k = t; i < n/t; i++, k = t) {
            while (k > 0) {
                cout << s1[k] << ", ";
                k = k - s1[k];
            }
        }
        n = n%t;
    } else {
        s.resize(n+1, 0);
        cout << "Revenue: " << setw(5) << ExtendedBottomUpCutRod(s, n);
        cout << ", Solution: ";
    }
    while (n > 0) {
        cout << s[n] << ", ";
        n = n - s[n];
    }
}



int RodCutting::ExtendedBottomUpCutRod(vector<int>& s, size_t n) {
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
    RodCutting rc(p);

    cout << "------PrintCutRodSolution--------" << endl;
    for (int i = 0; i <= 30; i++) {
        cout << "Rod Cut " << setw(3) << i << ": ";
        rc.PrintCutRodSolution(i);
        cout << endl;
    }

    cout << "------BottomUpCutRod--------" << endl;
    for (int i = 0; i <= 30; i++) {
        cout << "Rod Cut " << setw(3) << i << ": ";
        cout << rc.BottomUpCutRod(i) << endl;
    }

    cout << "------MemoizedCutRod--------" << endl;
    for (int i = 0; i <= 10; i++) {
        cout << "Rod Cut " << setw(3) << i << ": ";
        cout << rc.MemoizedCutRod(i) << endl;
    }
    return 0;
}
