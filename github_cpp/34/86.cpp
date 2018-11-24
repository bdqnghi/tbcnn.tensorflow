/*
Naive Bayes模型
输入：n*(m+1)的矩阵,最后一列为分类Y，取值-1,1，应用于二分类
	  n*m为特征矩阵，取值为整数
输出：训练出一个朴素贝叶斯分类器，对于给定的m维输入，输出分类
*/
#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
using namespace std;
typedef vector<vector<int> > matrix;
typedef vector<int> column;//表示一列
typedef vector<int> row;//表示一行
typedef pair<int,int> pii;
double lambda = 1; // 拉普拉斯平滑因子
double py[2];// 先验概率
int posCnt,negCnt;
vector<map<pii,double> > pxy; // 条件概率 
row diffCnt;//存储每一列X不同元素的个数
void train(matrix &X,column &Y){
	int n = X.size(),m = X[0].size();
	//计算两种分类的先验概率P(Y=1),P(Y=-1)
	posCnt = 0,negCnt = 0;
	for(int i = 0;i < n;i++) posCnt += (Y[i]==1 ? 1 : 0);
	negCnt = n - posCnt;
	py[0] = (posCnt+lambda)/(n+2.0*lambda);
	py[1] = (negCnt+lambda)/(n+2.0*lambda);
	//计算条件概率P(X|Y)
	pxy.clear();
	set<int> mSet;
	for(int j = 0;j < m;j++){
		map<pii,double> mp;
		mp.clear();
		mSet.clear();
		for(int i = 0;i < n;i++){
			pii tp = make_pair(X[i][j],Y[i]);
			if(mp.find(tp) == mp.end()) mp[tp] = 0;
			mp[tp] += 1;
			mSet.insert(X[i][j]);
		}
		diffCnt.push_back(mSet.size());
		map<pii, double>::iterator it;
		for(it = mp.begin();it != mp.end();it++){
			int tmpCnt = it->first.second==1 ? posCnt : negCnt; 
			mp[it->first] = (it->second+lambda)/(tmpCnt+diffCnt[j]*lambda);
		}
		pxy.push_back(mp);
	}
}
// 计算p(Y=y)*multi(P(Xi|y))
double getProbility(row &X,int y){
	double ret = py[y == 1 ? 0 : 1];
	for(int i = 0;i < pxy.size();i++){
		map<pii,double> mp = pxy[i];
		pii tmp = make_pair(X[i],y);
		int tmpCnt = y==1 ? posCnt : negCnt;
		//判断P(Xi|Y=y)是否出现过，没出现按0处理，要加上正则化即拉普拉斯平滑
		if(mp.find(tmp) == mp.end()) ret = ret*lambda/(diffCnt[i]*lambda+tmpCnt);
		else ret *= mp[tmp]; 
	}
	return ret;
}
int classifyNB(row &X){
	double posP,negP;
	posP = getProbility(X,1);
	negP = getProbility(X,-1);
	printf("posP:%.4f\n", posP);
	printf("negP:%.4f\n", negP);
	return posP > negP ? 1 : -1;
}
int main(){
	int n,m;
	while(~scanf("%d %d",&n,&m)){
		matrix X;
		column Y;
		X.clear(),Y.clear();
		int x,y;
		for(int i = 0;i < n;i++){
			row r;
			r.clear();
			for(int j = 0;j < m;j++){
				scanf("%d",&x);
				r.push_back(x);
			}
			X.push_back(r);
			scanf("%d",&y);
			Y.push_back(y);
		}
		train(X,Y);
		int q;
		scanf("%d",&q);
		row r;
		int ca = 1;
		while(q--){
			r.clear();
			for(int i = 0;i < m;i++){
				scanf("%d",&x);
				r.push_back(x);
			}
			printf("Case %d: %d\n", ca++,classifyNB(r));
		}
	}
	return 0;
}
/*数据格式，<统计学习方法>例4.1
15 2
1 1 -1
1 2 -1
1 2 1
1 1 1
1 1 -1
2 1 -1
2 2 -1
2 2 1
2 3 1
2 3 1
3 3 1
3 2 1
3 2 1
3 3 1
3 3 -1
1
2 1
*/