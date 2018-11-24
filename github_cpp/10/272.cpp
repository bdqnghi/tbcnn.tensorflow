/*#include<iostream>
#include<string>
#include<list>
#include<stdio.h>
using namespace std;

int dir[4][2]= {{-1, 0},{1, 0},{0, -1}, {0, 1}}; //�ĸ����򣬷ֱ�����ϣ��£�����
int arr[10][10];   // �Թ�

struct node {  // x��������� y����������
    int x;
    int y;
    node (int x1, int y1):x(x1), y(y1) {}
};

// ʹ���������������

void print(list<node> m) {   //���·��
    cout << "(" << m.front().x << "," << m.front().y << ")";   //���ÿ������֮��Ŀո�����
    m.pop_front();
    while (!m.empty()) {
        cout << " (" << m.front().x << "," << m.front().y << ")";
        m.pop_front();
    }
    cout << endl;
}

int Path(node cur, node end, list<node> s) {
    if (cur.x == end.x && cur.y == end.y) {  // ��ǰ������ڽ�������ʱ����1�����ҵ�һ��·�������ݹ�ͻ������ԭ���뿴�±�ע��
        print(s);
        return 1;
    }
    for (int i = 0; i < 4; i++) {  // 4������ֱ�̽��
        node next(cur.x + dir[i][0], cur.y + dir[i][1]);   // ������һ��Ҫ����̽���ĵ�
        if (next.x >= 0 && next.x <= end.x && next.y >= 0 && next.y <= end.y && arr[next.x][next.y] == 0) {   //�ж��¸����Ƿ����
            s.push_back(next);      // ���ԣ���������������·���С�
            arr[next.x][next.y] = 1;    // ��ʱ������Ѿ��߹������Ϊ1��
            if (Path(next, end, s)) return 1;   // ��������λ�ü�cur�м�¼λ�ã��ݹ������һλ�õĲ��ҡ�ѭ��������
                                               // ���һֱ���������²��ң�֪���ҵ��յ㣬��ײ㺯���ͻ᷵��1�����ŷ��ص������ڶ��㣬ִ��if��䣬���ŷ���1��
                                              // ֱ�����������ݹ麯���� 
            s.pop_back();     // ������²���ʧ�ܣ��ͻ�����ifִ����һ�䣬���Ǿ�Ҫ���ݣ����磬��a�ҵ�b�����ҵ�c�������²���ʧ�ܡ�˵��c����㲻��ȡ��
                             // ���·���b��һ��������������Ϊ��ǰ����λ��c�����ǽ�c������·���У�Ȼ�������������������ʧ��˵��c�����У���������
                            // Ҫ������·�����Ƴ�����pop��c.
         }
    }
    return 0;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int m, n, i, j;
        string st;
        cin >> m >> n;
        getline(cin, st);
        for (i = 0; i < m; i++) {  //�����Թ�
            getline(cin, st);
            for (j = 0; j < n; j++)
                arr[i][j] = st[j] - '0';
        }
        list<node> s;
        node sta(0, 0), end(m-1, n-1);   //��¼��ʼ�ͽ������ꡣ
        s.push_back(sta);
        arr[0][0] = 1;    
        if (Path(sta, end, s) == 0) cout << "no" << endl;
    }
	system("pause");
    return 0;
}*/



/*#include<iostream>
#include<string>
#include<list>
#include<stack>
#include<stdio.h>
using namespace std;
struct point{
	int x;//������
	int y;//������
};

stack<point> path;

//define four directions which represents up,down,left,right;
char maze[11][11];//define maze;
int count=0;
void createmaze(int row,int col){
	for(int i=0;i<row+2;i++){
	maze[i][col+1]=maze[i][0]='1';
	}
	for(int i=0;i<col+2;i++){
	maze[0][i]=maze[row+1][i]='1';
	}
	for(int i=1;i<=row;i++){
		for(int j=1;j<=col;j++){
	cin>>maze[i][j];
	}
	}

}
bool apath(int row,int col,int x,int y){//ǰ��������������꣬��������������ǰ����
	maze[x][y]='-1';
	point t;
	t.x=x;
	t.y=y;
	path.push(t);
	if(row==x &&col==y){
	return true;
	}
	point move[4]={{-1,0},{1,0},{0,-1},{0,1}};
	for(int i=0;i<4;i++){
		if(maze[x+move[i].x][y+move[i].y]=='0'){
		if(apath(row,col,x+move[i].x,y+move[i].y))
			return true;
		}
	}
	path.pop();
	return false;
}
void print(int row,int col){
	point temp;
	stack<point>p;
	while(!path.empty()){
	temp=path.top();
	p.push(temp);
	path.pop();
	}
	//temp=p.top();
	//cout<<"("<<temp.x-1<<","<<temp.y-1<<")";
	//count++;
	//p.pop();
	while(!p.empty()){
	//temp=p.top();
	//cout<<" ("<<temp.x-1<<","<<temp.y-1<<")";
	count++;
	p.pop();
	}
	//cout<<endl;
	cout<<count<<endl;
}
int main(){
int t,r,c;
while(cin>>t&&t!=0){
int c=t;
int r=t;
createmaze(r,c);
if(apath(r,c,1,1)){
print(r,c);
}else{
cout<<0<<endl;
}
}
system("pause");
return 0;
}
*/



// Problem#: 11878
// Submission#: 3145923
// The source code is licensed under Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License
// URI: http://creativecommons.org/licenses/by-nc-sa/3.0/
// All Copyright reserved by Informatic Lab of Sun Yat-sen University
/*#include<iostream>
#include<stack>
#include<stdio.h>
using namespace std;

struct point {
    int x;
    int y;
};

stack<point> path;
point move[4]={{-1,0},{1,0},{0,-1},{0,1}};
//point move[4] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
char maze[11][11];

void createMaze(int row,int column){
    //�����Թ���ע�⵽��0��ʾ���ߣ�1��ʾǽ��������������Թ�����ǽΧ�ţ������ʱ��Ͳ����ر�ע��߽�����
    for(int i=0; i<row+2; i++)
        maze[i][0] = maze[i][column+1] = '1';
    for(int j=0; j<column+2; j++)
        maze[0][j] = maze[row+1][j] = '1';
    for(int i=1; i<=row; i++){
        for (int j = 1; j <= column; j++)
             cin >> maze[i][j];
    }
}

bool aPath(int row, int col, int x, int y) {
    maze[x][y] = '-1';
    point t;
    t.x = x;
    t.y = y;
    path.push(t);
    if (x == row && y == col) {
            return true;
        }
	point move[4]={{-1,0},{1,0},{0,-1},{0,1}};
    for (int i = 0; i < 4; i++) {
        if (maze[x + move[i].x][y + move[i].y] == '0') {
            if (aPath(row, col, x + move[i].x, y + move[i].y)) return true;
        }
    }
    path.pop();
    return false;
}

void printPath(int row, int col) {
    point temp;
    stack<point> p;
    while (!path.empty()) {
        temp = path.top();
        p.push(temp);
        path.pop();
    }
    temp = p.top();
    cout << "(" << temp.x - 1 << "," << temp.y - 1 << ")";
    p.pop();
    while (!p.empty()) {
        temp = p.top();
        cout << " (" << temp.x - 1 << "," << temp.y - 1 << ")";
        p.pop();
    }
    cout << endl;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int row, col;
        cin >> row >> col; 
        createMaze(row, col);
        if (aPath(row, col, 1, 1)) {
            printPath(row, col);
        } else {
            cout << "no" << endl;
        }
    }
	system("pause");
    return 0;
}   */              



#include<iostream>
#include<stdio.h>
#include<vector>
#include<algorithm>
#include<memory.h>
using namespace std;

struct point {
    int x;
    int y;
	int totaltonext;
};//����ṹ��

int move_x[] = {-1, -1, -2, -2, 1, 1, 2, 2};
int move_y[] = {-2, 2, 1, -1, 2, -2, 1, -1};

bool tab[10][10];
int arr[64];
bool cmp(point,point);
bool solve(int ,point );
bool isvalued(point);
bool solve(int k,point m){//k��������
	point s;
//int x1,y1;
if(k==64){
for(int i=0;i<63;i++)
	cout<<arr[i]<<" ";
    cout<<arr[63]<<endl;
    return true;
}else {
	vector<point>tmp;
	for(int j=0;j<8;j++){
	s.x=m.x+move_x[j];
	s.y=m.y+move_y[j];
	s.totaltonext=0;

	if (isvalued(s)) {  
            //  cout << "p"; 
		       point w;
			   for(int l=0;l<8;l++){
			   w.x=s.x+move_x[l];
			   w.y=s.y+move_y[l];
			   if(isvalued(w))
				   s.totaltonext++;
			   }
			   tmp.push_back(s);
	}
	}
	sort(tmp.begin(),tmp.end(),cmp);

	for(int i=0;i<tmp.size();i++){
		      tab[tmp[i].x][tmp[i].y]=false;
                arr[k]=8*tmp[i].x+tmp[i].y+1;  
                if(solve(k+1,tmp[i]))
				return true;
                tab[tmp[i].x][tmp[i].y]=true;  
                //k--;  
            }  
	}
      return false;
 }

bool cmp(point a,point b){
	return a.totaltonext<b.totaltonext;
}
bool isvalued(point n){
return (n.x >= 1 && n.x <= 8 && n.y >= 1 && n.y <= 8 && tab[n.x][n.y]==true);
}

int main()  
{  
    int n;  
    point m;  
    //bool tab[8][8]=true;  
    
    while ( cin >> n && n!=-1 ) {  
		 memset(tab, 1, 10*10*sizeof(bool));
        m.x=(n-1)/8;  
        m.y=(n-1)%8;  
       
        arr[0]=n;  
        tab[m.x][m.y]=false;  
          
        solve(1,m);  
        //cin >> n;  
    }  
   //system("pause");  
    return 0;  
}  

/*#include <iostream>
#include <vector>
#include <memory.h>
#include <algorithm>
#include<stdio.h>
 
using namespace std;
 
struct point
{
    int x;
    int y;
    int totaltonext;
 
};
 
int board[10][10];
 
int move_x[] = {-1, -1, -2, -2, 1, 1, 2, 2};
int move_y[] = {-2, 2, 1, -1, 2, -2, 1, -1};
 
bool isfind;
int path[100];
bool dfs(point, int);
bool isvalue(point );
bool cmp(point , point );
 
int main()
{
    int n;
    point p;
     
 
    //freopen("C:\\Users\\Haojian\\Desktop\\test.txt", "r", stdin);
    while (cin >> n && n != -1)
    {
        isfind = false;
        memset(board, 0, 10*10*sizeof(int));
        p.x = (n - 1) / 8 + 1;
        p.y = n - ((p.x-1) * 8);
        //p.num = 1;
    //    path[p.num-1] = n;
        path[0] = n;
        board[p.x][p.y] = 1;
        dfs (p, 1);
 
    }
	system("pause");
    return 0;
}
 
 
bool dfs (point p, int current)
{
    point n;
 
     
    if (current == 64)
    {
        for (int i = 0; i < 63; i++)
            cout << path[i] << " ";
        cout << path[63];
        cout << endl;
        return true;
    }
    else
    {
        vector<point> tmp;
        for (int i = 0; i < 8; i++)
        {
            n.x = p.x + move_x[i];
            n.y = p.y + move_y[i];
            n.totaltonext = 0;
             
            if (isvalue(n))
            {
                 
                point k;
                for (int j = 0; j < 8; j++)
                {
                    k.x = n.x + move_x[j];
                    k.y = n.y + move_y[j];
                    if (isvalue(k))
                        n.totaltonext++;
                }
                 
                    tmp.push_back(n);
            }
        }
 
        sort(tmp.begin(), tmp.end(), cmp);
         
        for (int i = 0; i < tmp.size(); i++)
        {
            board[tmp[i].x][tmp[i].y] = 1;
            path[current] = (tmp[i].x - 1) * 8 + tmp[i].y;
            if (dfs(tmp[i], current+1)) return true;
            board[tmp[i].x][tmp[i].y] = 0;
        }
         
 
         
    }
    return false;
}
 
bool cmp(point a, point b)
{
    return a.totaltonext < b.totaltonext;
}
 
bool isvalue(point n)
{
    return (n.x >= 1 && n.x <= 8 && n.y >= 1 && n.y <= 8 && !board[n.x][n.y]);
}*/