#include <cstdio>
#include <cstring>

#define MAXS 2005
#define max(a,b) a>b?a:b
#define min(a,b) a<b?a:b
using namespace std;

char a[MAXS], b[MAXS];
int ta, tb;

int casos;
int dp[MAXS][MAXS];

int solve(int ta, int tb){
	if(ta < 0 && tb < 0)
		return 0;
	if(ta < 0)
		return tb + 1;
	if(tb < 0)
		return ta + 1;

	int &ans = dp[ta][tb];
	if(ans == -1){
		ans = 1<<30;

		if(a[ta] == b[tb] )
			ans = min(ans, solve(ta - 1, tb - 1));
		else
			ans = min(ans, 1 + solve(ta - 1, tb - 1));// con un solo cambio convierto en lo mismo
		ans = min(ans, 1 + solve(ta - 1, tb    ));
		ans = min(ans, 1 + solve(ta    , tb - 1));
	}
	return ans;
}
int main(){
	//freopen("entrada.in", "r", stdin);
	scanf("%d", &casos);
	while(casos--){
		scanf("%s%s", a, b);
		ta = strlen(a);
		tb = strlen(b);
		memset(dp, -1, sizeof(dp));
		printf("%d\n",solve(ta-1, tb - 1));
	}
	return 0;
}