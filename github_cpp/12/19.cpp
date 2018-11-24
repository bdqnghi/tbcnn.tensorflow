/*
  경로 찾기 문제
  
  참고 :  http://gnujoow.github.io/boj/2016/09/08/BOJ5-11403/
http://www.crocus.co.kr/536
*/
#include <cstdio>
int N;
int map[100][100] = { 0, };

int main() {
	int temp;
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &map[i][j]);
		}
	}

	for (int k = 0; k < N; k++) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (map[i][k] && map[k][j]) {
					map[i][j] = 1;
				}
			}
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			printf("%d ", map[i][j]);
		}
		printf("\n");
	}

	return 0;
}
