#include "MinimumSpanningTree.h"

int main() {
	cout << endl;
	cout << "**        �������ģ��ϵͳ         **" << endl;
	cout << "===================================" << endl;
	cout << "**       A --- ������������       **" << endl;
	cout << "**       B --- ��ӵ����ı�       **" << endl;
	cout << "**       C --- ������С������     **" << endl;
	cout << "**       D --- ��ʾ��С������     **" << endl;
	cout << "**       E --- �˳�����           **" << endl;
	cout << "===================================" << endl;

	char key;
	char temp;
	Graph graph;
	vector<Arc> mst;

	while (1){
		cout <<endl<< "��ѡ�����:";
		cin >> key;
		switch (key){
		case 'A':
			cout << "�����붥�����:";
			cin >> graph.vex_num;
			cout << "�������������������ƣ�";
			for (int i = 0; i < graph.vex_num; i++) {
				cin >> temp;
				graph.vexs.push_back(temp);
			}
			break;
		case 'B':
			cout << "������ߵ�������";
			cin >> graph.arc_num;
			createUDG(graph);
			break;
		case 'C':
			cout << "��������ʼ���㣺";
			cin >> temp;
			constructMST(graph, temp, mst);
			cout << "����Prim��С��������"<<endl;
			break;
		case 'D':
			cout << "��С�������Ķ��㼰��Ϊ��" << endl;
			displayMST(mst);
			break;
		case 'E':
			return 0;
			break;
		default:
			break;
		}
	}

	system("pause");
	return 0;
}
