//{{{ Knuth Morris Pratt
int *buildFail(char *p) {
	int m = strlen(p);
	int *fail = new int[m+1];
	int j = fail[0] = -1;
	for (int i = 1; i <= m; ++i) {
		while (j >= 0 && p[j] != p[i-1]) j = fail[j];
		fail[i] = ++j;
	}
	return fail;
}

int match(char *t, char *p, int *fail) {
	int n = strlen(t), m = strlen(p);
	int count = 0;
	for (int i = 0, k = 0; i < n; ++i,++k) {
		if(k==m)k=fail[k];
		while (k >= 0 && p[k] != t[i]) k = fail[k];
		//matching p[0]..p[k] == t[i-k]..[i]
		if (k == m-1) {
			count++;
		}
	}
	return count;
}
//}}}
