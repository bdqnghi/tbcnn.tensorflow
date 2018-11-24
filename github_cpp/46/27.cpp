#include <iostream>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <bitset>


using namespace std;

int segment_tree[100000 * 5];

int segment_index[100001];


void initialize(int node, int start, int end){
	segment_tree[node] = 1;
	if(start == end)segment_index[start] = node/*or end*/;
	else {
		int v = node*2;
		int u = (end + start) / 2;
		initialize(v, start, u);//left node
		initialize((v) + 1, u + 1, end);//left node
	}
}

void update(int index){
	if(index == 1)return;
	int parent = index / 2;
	segment_tree[parent] = segment_tree[(index % 2 == 0) ? index + 1 : index - 1] * segment_tree[index];

	update(parent);
}

int query(int node, int start, int end, int qStart, int qEnd){

	if(qStart > end || qEnd < start)return 1;

	if(qStart <= start && qEnd >= end)return segment_tree[node];


	int v = node*2;
	int u = (end + start) / 2;
	int p1 = query(v,start,u, qStart,qEnd);
	int p2 = query(v + 1,u + 1, end, qStart,qEnd);

	return p1*p2;
}


int main(){

	int n = 0;
	int c = 0;

	while(scanf("%d%d",&n, &c) != EOF){
		initialize(1,1,n);

		for(int I = 1; I <= n; I++){
			int current = 0;

			scanf("%d",&current);

			if(current < 0)segment_tree[segment_index[I]] = -1;
			else if(current == 0)segment_tree[segment_index[I]] = 0;

			update(segment_index[I]);

		}

		string resultS;

		for(int I = 0; I < c; I++){
			char command = '0';
			char endL = '0';
			int a = 0;
			int b = 0;

			scanf("%c%c%d%d",&endL,&command,&a,&b);


			if(command == (int)'C'){
				if(b < 0)segment_tree[segment_index[a]] = -1;
				else if(b == 0)segment_tree[segment_index[a]] = 0;
				else segment_tree[segment_index[a]] = 1;

				update(segment_index[a]);


			}
			else {
				int result = query(1,1,n,a,b);
				if(result < 0)resultS.append("-");
				else if(result == 0)resultS.append("0");
				else resultS.append("+");
			}
		}

        cout << resultS << endl;
		//printf("%s\n",&resultS);

	}

	return  0;
}
