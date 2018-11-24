#include <stdio.h>
#include <algorithm>

#include <gflags/gflags.h>
#include <glog/logging.h>

/*
 * https://blog.csdn.net/fx677588/article/details/68951593
 * 二维数组dp, 其中每个元素代表一个状态, 其中dp[i][j] 表示从序号为0 的物体到序号为i 的物体止的集合中的若干个物品放入体积为j的背包中的最大价值.
 * dp[n - 1][W] 即是我们想要的结果
 */
int solve(int v[], int w[], int n, int W, int **dp){
	for(int i = 0; i < n; i++){
		for(int j = 1; j <= W; j++){
			if(j < w[i]){
				if(i == 0){
					dp[i][j] = 0;
				}
				else{
					dp[i][j] = dp[i - 1][j];
				}
			}
			else{
				if(i == 0){
					dp[i][j] = v[i];
				}
				else{
					dp[i][j] = std::max(dp[i - 1][j] , dp[i - 1][j - w[i]] + v[i]);
				}
			}
			fprintf(stdout, "% 3d ", dp[i][j]);
		}
		fprintf(stdout, "\n");
	}
	return dp[n - 1][W];
}

int main(int argc, char* argv[]){
	google::InitGoogleLogging(argv[0]);
	google::ParseCommandLineFlags(&argc, &argv, true);
	FLAGS_alsologtostderr = true;
	FLAGS_colorlogtostderr = true;

	int v[] = {2 , 5 , 3 , 10 , 4}; // value
	int w[] = {1 , 3 , 2 , 6 , 2}; // weight
	int n = sizeof(v) / sizeof(v[0]);
	int W = 12; // total weight which bag can support

	int **dp = new int*[n + 1];
	for(int i = 0; i < n + 1; i++){
		dp[i] = new int[W + 1];
	}

	/* 初始状态 f[0−N][0]都为0, 表示体积为0的背包啥价值的物品都装不进去 */
	for(int i = 0; i < n + 1; i++){
		dp[i][0] = 0;
	}

	int res = solve(v, w, n, W, dp);
	LOG(INFO) << "max: " << res;

	for(int i = 0; i < n; i++){
		delete []dp[i];
	}
	delete []dp;

	google::ShutdownGoogleLogging();
	return 0;
}

