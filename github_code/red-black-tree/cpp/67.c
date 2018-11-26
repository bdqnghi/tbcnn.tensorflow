#include "car.h"
#include "people.h"
#include <iostream>
#include "list.h"
#include "red-black-tree.cpp"


using namespace std;


int main() {
	FireCars newcar;
	People emin;
	list ListOfFireCars;
	cout << "Out of list start: " << endl;
	for (int i = 0; i < 10; i++)
	{
		ListOfFireCars.Add(newcar);
	}
	
	ListOfFireCars.Show();
	cout << "Out of list END. " << endl;

    //cout << emin.getF();

    int n;
    bitree mybitree;
    cout<<"Не смог придумать куда запихать дерево, так что просто демонстрация его работы: " <<endl<< "введите количество элементов  ";
    cin>>n; //Вводим количество элементов
    for (int i=0;i<n;++i)
        {

        mybitree.push(1+rand()%(100),&mybitree.tree); //И каждый кладем в дерево
        }
    cout<<"ваше дерево\n";
        mybitree.print(mybitree.tree,0);
        system("echo program ended");

	return 0;
}
