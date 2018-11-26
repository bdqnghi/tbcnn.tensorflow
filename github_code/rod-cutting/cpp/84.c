//2013011769_KangSeungWon_508
#include <stdio.h>
#include <vector>
using namespace std;

void Rodcutting(vector<int>& p, vector<int>& r, vector<int>& s, int N);
void printRodcutting(vector<int>& p, vector<int>& s, int n);

int main()
{
	int N;
	vector<int> r, s, p;

	scanf("%d", &N);

	r.resize(N+1);
	s.resize(N+1);
	p.resize(N+1);

	p[0] = 0;

	for (int i = 1; i <= N; ++i) {
		scanf("%d", &p[i]);
	}

	Rodcutting(p, r, s, N);
	printf("%d\n", r[N]);
	printRodcutting(p, s, N);

	return 0;
}


void Rodcutting(vector<int>& p, vector<int>& r, vector<int>& s, int N) {

	int q, i, j;
	r[0] = 0;

	for (i = 1; i <= N; ++i) {
		q = -987654321;

		for (j = 1; j <= i; ++j) {
			if (q < p[j] + r[i-j]) {
				q = p[j] + r[i-j];
				s[i] = j;
			}
		}

		r[i] = q;
	}
}

void printRodcutting(vector<int>& p, vector<int>& s, int n)
{
	while (n > 0) {
		printf("%d ", s[n]);
		n -= s[n];
	}

	printf("\n");
}

