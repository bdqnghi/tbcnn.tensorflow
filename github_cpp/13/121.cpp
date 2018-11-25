

#include <iostream>
#include <fstream>
#include <string>
using namespace std;


void sort(double gpa[],std::string names[], int i);
 
int main(){
	const int size= 5;
		std::string names[size];
		double gpa[size];
		int i=0;
		ifstream fin("gpa.txt");
		while ( !fin.eof() && (i < size))
		{
			fin >> names[i];
			fin >> gpa[i];
			i++;
		}
		while(i<5 && in >> gpa[i]){
		i++;
	}
	sort(gpa,names);
	for(int gpa=0; gpa<i; gpa++){
		cout << gpa[i] << "  ";
	}
	cout << endl;
	in.close();
	return 0;

		for (int i= 0; i <size; i++)
			cout << names[i] << ":" << gpa[i]<<endl; 



		}


void sort(double gpa[], std::string names[], int i);
{

	for(int pass=0; pass < n-1; pass++){
		for(int comp=0; comp < n-1-pass; comp++){
			if(a[comp]>a[comp+1]){
				int temp=a[comp];
				a[comp] = a[comp+1];
				a[comp+1] = temp;
			}
		}
	}
}
