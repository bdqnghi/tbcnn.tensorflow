/**
    Maximum Gap
    Bucket-sort method
    ~O(n)
*/
class Solution {
public:
    struct bucket {
        int low, high;
        bucket() : low(-1), high(-1) {}
    };
    int maximumGap(const vector<int> &A) {
        if(A.size() < 2) return 0;
        int maxn = A[0];
        int minn = A[0];
        
        for(int i = 0; i < A.size(); ++i) {
            maxn = max(maxn, A[i]);
            minn = min(minn, A[i]);
        }
        if(maxn == minn) return 0;
        vector <bucket> b(A.size() + 1);
        double interval = (double) A.size() / (double)(maxn - minn);
        for(int i = 0; i < A.size(); ++i) {
            int index = (int) (A[i] - minn) * interval;
            if(b[index].low == -1) {
                b[index].low = A[i];
                b[index].high = A[i];
            }
            else {
                b[index].low = min(A[i], b[index].low);
                b[index].high = max(A[i], b[index].high);
            }
        }
        int res = 0;
        int prev = b[0].high;
        for(int i = 1; i < b.size(); i++){
            if(b[i].low != -1){
                res = max(res, b[i].low - prev);
                prev = b[i].high;
            }
        }
        return res;
    }

};