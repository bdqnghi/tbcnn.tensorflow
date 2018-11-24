#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <list>
#include <queue>
using namespace std;

#define INFI 1000
typedef struct _mark {
    int pre_suc;
    int max_incr;
} MARK;

int iteration = 0; //增光路径数目
const int N = 100;
list<int> setS;
bool isMark[N], isCheck[N], isDone;
MARK markList[N];
int c[N][N], f[N][N];
int n; //顶点数

int Maxflow();
void Mincut();                                   //isMark的点就是最小割
int IncrFlowAuxi(int index);                     //计算增广路径中的最大可增量
void IncrFlow();                                 //增广路径的增加
void Mark(int index, int pre_suc, int max_incr); //被标记表示可能被纳入新路径
int ford_fulkerson();

int main(void)
{
    int n = 4;
    for (int k = 0; k < n; ++k) {
        memset(c[k], 0, sizeof(c[0][0]) * n);
        memset(f[k], 0, sizeof(f[0][0]) * n); //初始各分支流量为0
        memset(isMark, false, n);
        memset(isCheck, false, n);
    }
    isMark[0] = true; //给源做永久标记
    markList[0].max_incr = INFI;
    markList[0].pre_suc = INFI;
    c[0][1] = 20;
    c[0][2] = 10;
    c[1][2] = 30;
    c[1][3] = 10;
    c[2][3] = 20;
    cout << "最大流为：" << ford_fulkerson() << endl;
    cout << "最大割的S集合为：{";
    for (list<int>::iterator i = setS.begin(); i != setS.end(); i++) {
        printf("%d  ", *i);
    }
    cout << "}" << endl;
    cout << "增广路径个数为：" << iteration << endl;
}

int Maxflow()
{
    int flow = 0;
    for (int i = 0; i < n; i++) {
        flow += f[0][i];
    }
    return flow;
}

void Mincut()
{
    int i = 0;
    while (i < n) {
        if (isMark[i])
            setS.push_back(i);
        i++;
    }
}

int IncrFlowAuxi(int index)
{
    if (index == 0)
        return markList[index].max_incr;
    int prev = markList[index].pre_suc;
    int maxIncr = markList[index].max_incr;
    return min(maxIncr, IncrFlowAuxi(prev)); //递归求瓶颈值为最大增量
}

void IncrFlow()
{
    iteration++;
    int incr = IncrFlowAuxi(n - 1); //最大可增量
    int index = n - 1;
    int prev;
    while (index != 0) {
        prev = markList[index].pre_suc;
        f[prev][index] += incr; //增广路径增加后，相应的流量进行更新
        index = prev;
    }
}

void Mark(int index, int pre_suc, int max_incr)
{
    isMark[index] = true;
    markList[index].pre_suc = pre_suc;
    markList[index].max_incr = max_incr; //当前路径的流值
}

void Check(int i)
{
    isCheck[i] = true;
    for (int j = 0; j < n; j++) {
        if (c[i][j] > 0 && !isMark[j] && c[i][j] > f[i][j]) //forward 边
            Mark(j, i, min(markList[i].max_incr, c[i][j] - f[i][j]));
        if (c[j][i] > 0 && !isMark[j] && f[j][i] > 0) //reverse 边
            Mark(j, i, min(markList[i].max_incr, f[j][i]));
    }
}

int ford_fulkerson()
{
    int i;
    while (1) {
        isDone = true;
        i = 0;
        while (i < n) {
            if (isMark[i] && !isCheck[i]) //是否所有标记的点都已被检查
            {
                isDone = false;
                break;
            }
            i++;
        }
        if (isDone) //结束，计算最小割和最大流
        {
            Mincut();
            return Maxflow();
        }
        while (i < n) {
            if (isMark[i] && !isCheck[i]) {
                Check(i);
                i = 0;
            }
            if (isMark[n - 1]) //如果汇t被标记，说明找到了一条增广路径，则增加该条路径的最大可增加量
            {
                IncrFlow();
                memset(isMark + 1, false, n - 1); //增加该增广路径后，除了源s，其余标记抹去
                memset(isCheck, false, n);
            } else
                i++;
        }
    }
}
