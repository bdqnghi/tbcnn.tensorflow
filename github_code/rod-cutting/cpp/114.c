#include <bits/stdc++.h>
using namespace std;

class CuttingRod {
    vector<int> prices;
    int rl;  //rod length

    public:
     CuttingRod(vector<int> prices, int rl) {
         this->prices = prices;
         this->rl = rl;
     }

     int maxVal() {
         vector<int> mv(rl);
         mv[0] = prices[0];  //price of length
         // start frot smallert length, for each length calc.
         // the max value which can obtained by cutting rod
         for (int len = 1; len <= rl; len++) {
             mv[len - 1] = prices[len - 1];
             for (int j = 1; j <= len / 2; j++) {
                 int t = mv[j - 1] + mv[len - j - 1];
                 if (t > mv[len - 1]) mv[len - 1] = t;
             }
         }
         return mv[rl - 1];
     }
};

int main() {
    vector<int> arr = {3, 5, 8, 9, 10, 17, 17, 20};
    CuttingRod *cr = new CuttingRod(arr, arr.size());
    cout << cr->maxVal() << endl;
    return 0;
}
