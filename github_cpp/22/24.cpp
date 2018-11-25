


#include "stdafx.h"
#include <iostream>
#include <fstream>

using namespace std;
ofstream ofs("Output1_e14023056.txt", ios::out);

struct ListNode
{
	int data;
	struct ListNode *next;
};

class BucketSort{
private:
	int key, temp;
	int count[10];
	ListNode *list[10];
	ListNode *tmp[10];
	ListNode *now;
public:
	void getdata();
	void sorting(); 
	void sort(int key); 
	void print(); 
};

void BucketSort::getdata(){
	for (int i = 0; i < 10; i++)
		count[i] = 0;
	for (key = 0; key < 10; key++)
		list[key] = NULL;
	ifstream ifs("Input1.txt", ios::in);
	if (!ifs)
		cout << "Fail to open the input file." << endl;
	else
	{
		ifs >> temp;
		while (!ifs.eof()){
			if (temp == '\n' )
				break;
			key = temp / 10;
			count[key]++;
			if (list[key] == NULL) {
				ListNode *now = new ListNode;
				now->data = temp;
				now->next = NULL;
				list[key] = now;
				tmp[key] = now;
			}
			else{
				ListNode *now = new ListNode;
				now->data = temp;
				now->next = NULL;
				tmp[key]->next = now;
				tmp[key] = tmp[key]->next;
			}
			ifs >> temp;
		}
	}
	ifs.close();
}

void BucketSort::sort(int key){
	ListNode *tmpsmall;
	ListNode *pos;

	now = list[key]; 

	if (now == NULL)
		cout<<" ";
	else{
		for (int i = 0; i < count[key]; i++){
			int time = i;
			pos = now;
			tmpsmall = now;

			while (time != count[key]){
				if (pos->data < now->data && pos->data <= tmpsmall->data){
					tmpsmall = pos;
					
				}
				pos = pos->next;
				time++;
			}
			if (tmpsmall->data < now->data){
				temp = tmpsmall->data;
				tmpsmall->data = now->data;
				now->data = temp;
			}
			now = now->next;
		}
	}

}

void BucketSort::print(){
	
	for (int n = 0; n < 10; n++){
		ofs << n << ": ";
		cout << n << ": ";
		now = list[n];
		if (now == NULL){
			ofs << endl;
			cout << endl;
		}
		else{
			do{
				ofs << now->data << " ";
				cout << now->data << " ";
				now = now->next;
			} while (now != NULL);
			ofs << endl;
			cout << endl;
		}
	}
}

void BucketSort::sorting(){
	for (key = 0; key < 10; key++){
		sort(key);
		ofs << endl << "key= " << key << endl;
		cout << endl << "key= " << key << endl;
		print();
	}
}

int main()
{
	BucketSort bs;
	bs.getdata();

	cout << "key" << endl;
	ofs << "key" << endl;
	bs.print(); 
	cout <<  endl;

	bs.sorting();
	cout << endl;

	ofs.close();

	system("pause");
	return 0;
}

