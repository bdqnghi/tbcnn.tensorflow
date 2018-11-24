#include<iostream>
#include<cstdio>
#include<string>
#include<vector>
#include<queue>
#include<algorithm>
#include<stack>
#include <fstream>
#include <time.h>
#define BLACK 1
#define RED 0
#define Level_0 3000000
#define Level_1 30000000
#define Level_2 300000000
using namespace std;
char inp;
/*Max_val은 우수회원 세명의 총 사용금액과 key를 담는 벡터입니다*/
vector<pair<int, int> > Max_val;
/******************************************************************
Log는 물품결제 내역을 담는 구조체 입니다. when : 언제 what : 무엇을
howmuch : 얼마나 샀는지 노드에 담습니다. prev는 이전 Log next는 이후
로그를 가리킵니다.
*******************************************************************/
struct Log {
	long long when;
	string what;
	long long howmuch;
	Log *prev;
	Log *next;
};
/******************************************************************
Client는 각 고객들의 정보를 담는 구조체 입니다. key : 고객의 key값
name, phone : 이름, 전화번호 x,y : 고객의 x,y좌표 level : 고객등급
total : 총 사용량 , color : 트리 상에서 노드의 색 을 담습니다.
prev : 부모노드, right : 오른쪽 노드 , left : 왼쪽노드 를 가리킵니다.
start, end : 그 고객이 가진 로그의 시작 끝 주소를 가리킵니다.
*******************************************************************/
struct Client {
	int key;
	string name;
	string phone;
	int x;
	int y;
	int level = 0;
	long long total = 0;
	int color = 0;
	Client *prev = 0;
	Client *right = 0;
	Client *left = 0;
	Log *start = 0;
	Log *end = 0;
};
/******************************************************************
root를 담는 private변수가 있습니다. 나머지는 본 프로젝트에서 사용하는
함수들 입니다.
*******************************************************************/
class RBtree {
private:
	Client *root;
public:
	void rbtree();
	void insertItem(int Flag, int Key, string Name, string Phone, 
		int X, int Y, int Level, long long Total);
	bool isDoubleRed(Client *node);
	void recoloring(Client *node, Client *uncle);
	void restructuring(Client *node);
	void Rerestructuring(Client *node);
	int Find_depth(Client *node);
	void FindNode();
	void Find_info();
	void Insertgoods(Client *node, Log *temp);
	void Find_RecentLog();
};
void RBtree::rbtree() {
	root = 0;
}
/******************************************************************
 함수명: Find_info()
 동작: key값을 입력 받고 루트부터 key값을 비교해 가면서 노드를 찾습니다.
	  찾지 못한 상태로 leaf노드까지 내려갈 경우 트리 내에 해당 노드가
	  없는 것을 의미하므로 Not found!를 출력합니다.
	  있을 경우 이름, 전화번호, x, y좌표, 등급, 총 결제양, 뎁스를 출력
	  하게 됩니다. 여기서 depth를 출력하는 함수 또한 O(h)시간으로 수행
	  됩니다.
*******************************************************************/
void RBtree::Find_info() {
	int key;
	cin >> key;
	if (root == 0) {
		puts("Not found!");
		return;
	}
	Client *ptr = root;
	while (1) {
		if (ptr->key == key) {
			cout << ptr->name << " " << ptr->phone << " " << ptr->x << " " << ptr->y << " "
				<< ptr->level << " " << ptr->total << " " << Find_depth(ptr) << endl;
			break;
		}
		if (ptr->key > key) {
			if (ptr->left == 0) {
				printf("Not found!\n");
				break;
			}
			else ptr = ptr->left;
		}
		else {
			if (ptr->right == 0) {
				printf("Not found!\n");
				break;
			}
			else ptr = ptr->right;
		}
	}
}
/******************************************************************
 함수명: FindNode()
 동작: 새로운 상품 결제내역을 추가하는 함수입니다. 먼저 그 key값을 가진
	노드를 찾습니다. 그 후 level을 본 후 한도를 판단하여 한도를 넘어서는
	경우 로그를 추가시키지 않습니다. 만약 한도내에 들어올 경우 우수회원을
	판단하는 과정을 거친 후 Insertgoods함수를 실행하게 됩니다.
*******************************************************************/
void RBtree::FindNode() {
	int Key, val;
	long long E;
	string goods;
	cin >> Key >> E >> goods >> val;
	if (root == 0) {
		puts("Not found!");
		return;
	}
	Client *ptr = root;
	while (1) {
		/*일치할 경우 한도를 판단하게 됩니다. 넘어설 경우 depth를 출력하고
		while문을 빠져나오게 됩니다.*/
		if (ptr->key == Key) {
			if (ptr->level == 0) {
				if ((ptr->total) + val > Level_0) {
					printf("%d 0\n", Find_depth(ptr));
					break;
				}
			}
			else if (ptr->level == 1) {
				if ((ptr->total) + val > Level_1) {
					printf("%d 0\n", Find_depth(ptr));
					break;
				}
			}
			else if (ptr->level == 2) {
				if ((ptr->total) + val > Level_2) {
					printf("%d 0\n", Find_depth(ptr));
					break;
				}
			}
			/*한도를 넘지 않았을 경우*/
			ptr->total += val;
			/***************************************************************
			우수회원을 판단하는 부분입니다. 
			만약 비교 벡터에 아무런 값이 들어있지 않다면 입력을 해줍니다. 
			사이즈가 1보다 큰경우 벡터내에 이미 그 key값을 가지고 있다면 갱신을
			아닐경우 제일 최소값과 비교하여 추가를 해주는 방법으로 구현하였습니다.
			****************************************************************/
			if (Max_val.size() == 0)
				Max_val.push_back(make_pair(ptr->total, ptr->key));
			else if (Max_val.size() < 3){
				bool isthere = false;
				for (int i = 0; i < Max_val.size(); i++){
					if (ptr->key == Max_val[i].second){
						isthere = true;
						Max_val[i].first = ptr->total;
						break;
					}
				}
				if (!isthere)
					Max_val.push_back(make_pair(ptr->total, ptr->key));
				sort(Max_val.begin(), Max_val.end());
			}
			else{
				if (Max_val[0].first < ptr->total){
					bool isthere = false;
					for (int i = 0; i < Max_val.size(); i++){
						if (ptr->key == Max_val[i].second){
							isthere = true;
							Max_val[i].first = ptr->total;
							break;
						}
					}
					if (!isthere){
						Max_val[0].first = ptr->total;
						Max_val[0].second = ptr->key;
					}
					sort(Max_val.begin(), Max_val.end());
				}
			}
			/*새로운 로그를 만들어 추가시켜줍니다.*/
			Log *temp = new Log();
			temp->howmuch = val;
			temp->when = E;
			temp->what = goods;
			Insertgoods(ptr, temp);
			printf("%d 1\n", Find_depth(ptr));
			break;
		}
		if (ptr->key > Key) {
			if (ptr->left == 0) {
				puts("Not found!");
				break;
			}
			else ptr = ptr->left;
		}
		else {
			if (ptr->right == 0) {
				puts("Not found!");
				break;
			}
			else ptr = ptr->right;
		}
	}
}
/******************************************************************
함수명: Insertgoods(Client *node, Log *temp)
동작: 넘겨받은 해당 노드와 temp라는 새로 만든 로그 파일을 받아 진행합니다.
	로그가 처음 입력 될 경우와 있을 경우를 구분하여 입력합니다.
	없을 경우 end와 start를 temp로 지정해줍니다.
	있을경우 end의 next에 입력을 한 후 end를 temp로 지정합니다.
*******************************************************************/
void RBtree::Insertgoods(Client *node, Log *temp) {
	//로그가 없을 경우
	if (node->start == 0) {
		node->start = temp;
		node->end = temp;
		temp->prev = 0;
		temp->next = 0;
		return;
	}
	//있을 경우
	Log *st = node->end;
	st->next = temp;
	temp->prev = st;
	node->end = temp;
}
/******************************************************************
 함수명: Find_RecentLog()
 동작: key값을 기준으로 해당 노드를 찾습니다. 노드를 못찾고 leaft노드까지
	내려갈 경우 Not found!를 출력합니다. 노드를 찾았을 경우 해당 노드의
	로그의 end부터 Size만큼 차례대로 출력하면서 노드간 이동을 합니다.
*******************************************************************/
void RBtree::Find_RecentLog() {
	int Key, Size;
	cin >> Key >> Size;
	if (root == 0) {
		puts("Not found!");
		return;
	}
	Client *ptr = root;
	bool isDone = false;
	while (1) {
		if (ptr->key > Key) {
			if (ptr->left == 0) {
				puts("Not found!");
				return;
			}
			else ptr = ptr->left;
		}
		else if (ptr->key < Key) {
			if (ptr->right == 0) {
				puts("Not found!");
				return;
			}
			else ptr = ptr->right;
		}
		else {
			if (ptr->end == 0) {
				puts("0");
				break;
			}
			Log *st = ptr->end;
			for (int i = 0; i < Size; i++) {
				cout << st->when << " " << st->what << " " << st->howmuch << endl;
				if (st == ptr->start)
					return;
				st = st->prev;
				isDone = true;	//출력 후 탈출을 위한 flag입니다. 
			}
		}
		if (isDone) return;//출력이 완료瑛 경우 더이상 while문을 돌지 않습니다.
	}
}
/******************************************************************
함수명: Find_depth(Client *node)
동작: 해당 노드부터 root까지 이동을 하며 dep이라는 변수를 증가시켜 줍니다.
	root에 도달했을 경우 그 더해진 dep을 반환합니다.
*******************************************************************/
int RBtree::Find_depth(Client *node) {
	int dep = 0;
	if (root == 0) return 0;
	Client *ptr = node;
	while (1) {
		if (ptr == root) break;
		ptr = ptr->prev;
		dep++;
	}
	return dep;
}
/******************************************************************
함수명: isDoubleRed(Client *node)
동작: 자신의 노드와 부모 노드를 비교하여 두 노드 모두 트리상 RED일 경우
	true를 반환하게 됩니다.
*******************************************************************/
bool RBtree::isDoubleRed(Client *node) {
	if (node->prev == root) return 0;
	if (node == root) return 0;
	return (node->color == RED && node->prev->color == RED);
}
/******************************************************************
함수명: recoloring(Client *node, Client *uncle)
동작: 더블레드가 발생했고 uncle노드가 RED일때 recoloring을 진행하게 
	됩니다. 먼저 부모 노드와 삼촌 노드의 색을 black으로 만들어주고
	grandparent 노드가 root가 아닐경우 RED로 변경을 하게 됩니다.
	또한 root가 아닐경우 더블레드가 또 발생할 수 있으므로 판단을 하는
	함수로 다시 재귀적으로 진입하게 됩니다.
*******************************************************************/
void RBtree::recoloring(Client *node, Client *uncle) {
	node->prev->color = BLACK;
	uncle->color = BLACK;
	node = node->prev->prev;
	if (node == root) return;
	node->color = RED;
	if (isDoubleRed(node))
		Rerestructuring(node);
	return;
}
/*******************************************************************************************************
함수명:insertItem(int Flag, int Key, string Name, string Phone, int X, int Y, int Level, long long Total)
동작: temp라는 새로운 노드를 만들어 입력받은 데이터를 넣습니다. 그 후 key값을 비교하면서 내려가게 됩니다.
	leaf노드까지 내려 간 후 더블레드 여부를 판단하여 recoloring 혹은 restructuring 을 판단하는 함수로 진입하게
	됩니다. 이후 flag가 1일경우 처음 memberlist를 입력받은 것이 아니므로 depth를 출력하게 됩니다.
*********************************************************************************************************/
void RBtree::insertItem(int Flag, int Key, string Name, string Phone, 
	int X, int Y, int Level, long long Total) {
	Client *temp = new Client();
	temp->key = Key;
	temp->name = Name;
	temp->phone = Phone;
	temp->x = X;
	temp->y = Y;
	temp->level = Level;
	temp->total = Total;
	temp->color = RED;
	if (root == 0) {
		root = temp;
		temp->color = BLACK;
		return;
	}
	else {
		Client *ptr = root;
		while (1) {
			if (ptr->key > temp->key) {
				if (ptr->left == 0) {
					ptr->left = temp;
					temp->prev = ptr;
					break;
				}
				else
					ptr = ptr->left;
			}
			else if (ptr->key < temp->key) {
				if (ptr->right == 0) {
					ptr->right = temp;
					temp->prev = ptr;
					break;
				}
				else
					ptr = ptr->right;
			}
			else {
				cout << Find_depth(ptr) << " 0" << endl;
				return;
			}
		}
	}
	if (isDoubleRed(temp))
		Rerestructuring(temp);
	if (Flag == 1) cout << Find_depth(temp) << " 1" << endl;
}
/******************************************************************
함수명: Rerestructuring(Client *node)
동작: 처음으로 uncle노드를 grandparent 노드의 위치로 올린 후 
	좌 우 노드에 부모노드가 있는지 판단 한 뒤 그 반대 방향에 삼촌 노드 
	위치를 지정 하게 됩니다. 이 함수에 진입을 하게 된건 이미 더블레드가
	발생한 것이기 때문에 uncle의 색을 본 후 RED면 recoloring, BLACK이면
	restructuring을 수행하게 됩니다.
*******************************************************************/
void RBtree::Rerestructuring(Client *node) {
	Client *uncle = node->prev->prev;
	if (uncle->left == node->prev)
		uncle = uncle->right;
	else
		uncle = uncle->left;
	if (uncle == 0)
		restructuring(node);
	else if (uncle->color == RED)
		recoloring(node, uncle);
	else
		restructuring(node);
}
/******************************************************************
함수명: restructuring(Client *node)
동작: 3개의 노드를 각각 분리하여 크기순대로 mid, right, left노드를 지정
	하여 줍니다. 각 노드에 메달린 노드를 왼쪽 순서대로 T1,T2,T3,T4라 하면
	리스트럭처링을 하게 될 경우 T1, T4는 영향을 안받고 T2, T3를 Left, Right
	에 메달아 주기만 하면 되므로 각각 4가지 경우를 분리하여 생각하였습니다.
	연결 후 mid의 색을 BLACK 나머지를 RED로 한 후 함수가 종료되게
	됩니다. 만약 mid가 root가 될 경우 root노드로 지정을 해주고 아닐경우
	그 이전 노드에 연결하게 됩니다.
*******************************************************************/
void RBtree::restructuring(Client *node) {
	Client *parent = node->prev;
	Client *grand = node->prev->prev;
	Client  *T2, *T3, *mid, *Left, *Right, *Prev;
	int LeftRight = 0, isroot = 0;//0이면 Left, 1이면 Right, root면 0 아니면 1
	if (grand != root) {
		Prev = grand->prev;
		isroot = 1;
		if (grand->prev->right == grand)
			LeftRight = 1;
	}
	if (node->key > parent->key) {
		if (node->key > grand->key) {
			T2 = parent->left, T3 = node->left;
			mid = parent, Left = grand, Right = node;
		}
		else {
			T2 = node->left, T3 = node->right;
			mid = node, Left = parent, Right = grand;
		}
	}
	else {
		if (node->key > grand->key) {
			T2 = node->left, T3 = node->right;
			mid = node, Left = grand, Right = parent;
		}
		else {
			T2 = node->right, T3 = parent->right;
			mid = parent, Left = node, Right = grand;
		}
	}
	mid->left = Left, mid->right = Right;
	Left->prev = mid, Right->prev = mid;
	mid->color = BLACK, Left->color = RED, Right->color = RED;
	Left->right = T2, Right->left = T3;
	if (T2 != 0) Left->right->prev = Left;
	if (T3 != 0) Right->left->prev = Right;
	if (isroot == 1) {
		mid->prev = Prev;
		if (LeftRight == 1)
			Prev->right = mid;
		else
			Prev->left = mid;
	}
	else {
		root = mid;
		root->prev = 0;
	}
	return;
}
int main() {
//#ifdef _CONSOLE
	freopen("query_10k.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
//#endif
	std::ios::sync_with_stdio(false);
	string filename;
	printf("입력파일의 이름을 입력하세요: ");
	getline(cin, filename, '\n');
	ifstream fin;
	fin.open(filename.c_str(), ios::out);
	/*****************************************************************
	레드블랙 트리를 생성해 줍니다. 생성해 준 후 root를 0으로 초기화 합니다.
	******************************************************************/
	RBtree rbtree;
	rbtree.rbtree();
	int Key, X, Y, Level; long long Total = 0;
	string Name, Phone;
	/***************************************************************************
	처음 memberlist에서 입력을 받습니다. insertItem의 첫번째 인자인 flag가 0일경우
	Insert가 일어날때 승인이 되는지 depth가 몇인지 출력할 필요가 없으므로
	flag를 본후 판단하여 출력을 안하게 됩니다
	***************************************************************************/
	while (fin >> Key >> Name >> Phone >> X >> Y >> Level >> Total)
		rbtree.insertItem(0, Key, Name, Phone, X, Y, Level, Total);
	while (cin >> inp) {
		/******************************************************
		flag가 1이므로 Insert가 일어날때 승인이 되는지 depth가
		몇인지 출력하게 됩니다.
		******************************************************/
		if (inp == 'I') {
			cin >> Key >> Name >> Phone >> X >> Y;
			rbtree.insertItem(1, Key, Name, Phone, X, Y, 0, 0);
		}
		/*********************************************************
		회원이 있는지 없는지 찾아주는 함수 입니다. 함수 내에서 입력을
		받습니다. Key를 기준으로 찾아 없으면 Not found, 있으면 해당
		정보를 출력해줍니다.
		**********************************************************/
		else if (inp == 'P')
			rbtree.Find_info();
		/*************************************************************
		Key를 입력받아 그 키를 가진 노드가 있는지 먼저 찾습니다. 있을경우
		그 키에 대하여 내역을 추가 시키는 함수를 진행합니다.
		**************************************************************/
		else if (inp == 'A')
			rbtree.FindNode();
		/*********************************************************************
		Max_val이란 vector에는 오름차순으로 최대 3명의 우수 회원이 들어있습니다.
		요청이 들어올 경우 출력만 해주면 되므로 O(1)입니다.
		***********************************************************************/
		else if (inp == 'F'){
			for (int i = Max_val.size() - 1; i >= 0; i--)
				printf("%d ", Max_val[i].first);
			puts("");
		}
		/*********************************************************
		최근 결제내역을 조회하므로 먼저 Key를 입력받아 그 노드가 있는지
		찾습니다. 그 후 그 노드의 로그의 end부터 입력이 들어온 수만큼
		출력을 하게 됩니다. 
		***********************************************************/
		else if (inp == 'R')
			rbtree.Find_RecentLog();
		/**********************************
		Q가 들어올 경우 함수를 종료해 줍니다.
		**********************************/
		else if (inp == 'Q')
			return 0;
	}
}
