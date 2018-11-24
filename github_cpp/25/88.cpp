#include <bits/stdc++.h>

using namespace std;

typedef char permType;
typedef int dataType;

class Fenwick {
	private:
		const static int MAXN = 105000;
		int N;
		dataType B1[MAXN], B2[MAXN];
		
		int LSOne(int S){
			return (S & (-S));
		}
		void build(int n){
			N = n+10;
			memset(B1, 0, sizeof B1);
			memset(B2, 0, sizeof B2);
		}
		void build(dataType *A, int n){
			build(n);
			for (int i=0; i<n; i++){
				updateRange(i+1, i+1, A[i]);
			}
		}
		dataType query1(int b){
			dataType sum = 0;
			for (; b; b -= LSOne(b)) sum += B1[b];
			return sum;
		}
		dataType query2(int b){
			dataType sum = 0;
			for (; b; b -= LSOne(b)) sum += B2[b];
			return sum;
		}
		dataType query(int b){
			return query1(b) * b - query2(b);
		}
		void update1(int k, dataType v){
			for (; k <= N; k += LSOne(k)) B1[k] += v;
		}
		void update2(int k, dataType v){
			for (; k <= N; k += LSOne(k)) B2[k] += v;
		}

	public:
		Fenwick(int n){
			build(n);
		}
		Fenwick(dataType *A, int n){
			build(A, n);
		}
		dataType queryRange(int i, int j){
			return query(j) - query(i - 1);
		}
		void updateRange(int i, int j, dataType v){
			update1(i, v);
			update1(j + 1, -v);
			update2(i, v * (i - 1));
			update2(j + 1, -v * j);
		}
};

class Permutation {
    private:
        vector<int> getFactoradic(long long x, int len){
            vector<int> v;
            int i = 1;
            long long n = x;
            while (n != 0){
                v.push_back(n % i);
                n /= i;
                i++;
            }
            while (v.size() < len){
                v.push_back(0);
            }
            reverse(v.begin(), v.end());
            return v;
        }

    public:
        vector<permType> getPermutation(vector<permType> str, long long n){
            sort(str.begin(), str.end());
            vector<int> factoradic = getFactoradic(n, str.size());
            vector<permType> ret;
            bool used[str.size()+5];
            memset(used, 0, sizeof used);
            int count;
            for (int i=0; i<factoradic.size(); i++){
                count = -1;
                for (int j=0; j<str.size(); j++){
                    if (!used[j]){
                        count++;
                        if (count == factoradic[i]){
                            used[j] = 1;
                            ret.push_back(str[j]);
                        }
                    }
                }
            }
            return ret;
        }

        vector<permType> getPermutation2(vector<permType> str, long long n){
            sort(str.begin(), str.end());
            vector<int> factoradic = getFactoradic(n, str.size());
            vector<permType> ret;
            Fenwick fen(str.size());
            for (int i=0; i<str.size(); i++){
				fen.updateRange(i+1, i+1, 1);
			}
			int pos,val,low,high,mid;
            for (int i=0; i<factoradic.size(); i++){
                pos = str.size() + 10;
                low = 0;
                high = str.size()-1;
                while (low <= high){
                    mid = (low + high) / 2;
                    val = fen.queryRange(1, mid+1);
                    if (val == 1 + factoradic[i]){
                        pos = min(pos, mid);
                    }
                    if (val < 1 + factoradic[i]){
                        low = mid + 1;
                    } else {
                        high = mid - 1;
                    }
                }
                ret.push_back(str[pos]);
                fen.updateRange(pos+1, pos+1, -1);
            }
            return ret;
        }
};

int main(){
    Permutation perm;
    string s;
    cin >> s;
    vector<char> c;
    for (int i=0; i<s.length(); i++){
        c.push_back(s[i]);
    }
    long long n;
    cin >> n;
    
    clock_t start;
    clock_t end;

    start = clock();
    vector<char> x = perm.getPermutation(c, n);
    end = clock();
    cout << float( end - start ) /  CLOCKS_PER_SEC << endl;
    for (int i=0; i<x.size(); i++){
        cout << x[i];
    }
    cout << endl;

    start = clock();
    vector<char> x2 = perm.getPermutation2(c, n);
    end = clock();
    cout << float( end - start ) /  CLOCKS_PER_SEC << endl;
    for (int i=0; i<x2.size(); i++){
        cout << x2[i];
    }
    cout << endl;
    return 0;
}

