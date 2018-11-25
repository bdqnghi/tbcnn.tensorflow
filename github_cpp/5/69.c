






#include <cstdlib>
#include <iostream>
#include <fstream>
using namespace std;


void display(int list[], int size){
	cout<<"The elements of the array are:\n";
	for(int i=0; i<size ; i++){
		cout<<list[i]<<" ";
    }
    cout<<endl;
    
}




unsigned long long insertionSort(int list[], int size){
	int i,j,temp;
    unsigned long long count = 0;
	for(i=1; i < size; i++)
	{
		temp = list[i];
		j= i-1;
		while((temp<list[j]) && (j>=0)){
			count++;
            list[j+1]=list[j];
			j--;
		}
		list[j+1] = temp;
        count++;
	}
    return count;
}




void fillArray(int list[], std::ifstream &file){
    
    if(!file) {
        cout <<"Failed to open file ";
        return;
    }
    
    int n, i=0;
    while (!file.eof()) {
        file >> n;
        list[i] = n;
        i++;
    }
    
}

int main (int argc, char *argv[]){
    if (argc != 2){
        printf("Please enter number of elements to be sorted\n");
        return -1;
    }
    
    int amount;
    unsigned long long total;
    amount = atoi(argv[1]);
    
    int list1[amount], list2[amount], list3[amount], list4[amount], list5[amount], list6[amount], list7[amount], list8[amount], list9[amount], list10[amount], list11[amount], list12[amount], list13[amount], list14[amount], list15[amount], list16[amount], list17[amount], list18[amount], list19[amount], list20[amount];
    
    std::ifstream file1("num1.txt");
    std::ifstream file2("num2.txt");
    std::ifstream file3("num3.txt");
    std::ifstream file4("num4.txt");
    std::ifstream file5("num5.txt");
    std::ifstream file6("num6.txt");
    std::ifstream file7("num7.txt");
    std::ifstream file8("num8.txt");
    std::ifstream file9("num9.txt");
    std::ifstream file10("num10.txt");
    std::ifstream file11("num11.txt");
    std::ifstream file12("num12.txt");
    std::ifstream file13("num13.txt");
    std::ifstream file14("num14.txt");
    std::ifstream file15("num15.txt");
    std::ifstream file16("num16.txt");
    std::ifstream file17("num17.txt");
    std::ifstream file18("num18.txt");
    std::ifstream file19("num19.txt");
    std::ifstream file20("num20.txt");
    
    fillArray(list1, file1);
    fillArray(list2, file2);
    fillArray(list3, file3);
    fillArray(list4, file4);
    fillArray(list5, file5);
    fillArray(list6, file6);
    fillArray(list7, file7);
    fillArray(list8, file8);
    fillArray(list9, file9);
    fillArray(list10, file10);
    fillArray(list11, file11);
    fillArray(list12, file12);
    fillArray(list13, file13);
    fillArray(list14, file14);
    fillArray(list15, file15);
    fillArray(list16, file16);
    fillArray(list17, file17);
    fillArray(list18, file18);
    fillArray(list19, file19);
    fillArray(list20, file20);
    
    total = insertionSort(list1, amount);
    total += insertionSort(list2, amount);
    
    
    total += insertionSort(list3, amount);
    total += insertionSort(list4, amount);
    
    
    
    total += insertionSort(list5, amount);
    total += insertionSort(list6, amount);
    
    
    total += insertionSort(list7, amount);
    total += insertionSort(list8, amount);
    
    
    
    
    total += insertionSort(list9, amount);
    total += insertionSort(list10, amount);
    
    
    total += insertionSort(list11, amount);
    total += insertionSort(list12, amount);
    
    
    
    total += insertionSort(list13, amount);
    total += insertionSort(list14, amount);
    
    
    total += insertionSort(list15, amount);
    total += insertionSort(list16, amount);
    
    
    
    
    total += insertionSort(list17, amount);
    total += insertionSort(list18, amount);
    
    
    total += insertionSort(list19, amount);
    total += insertionSort(list20, amount);
    
    
    
    
    
    unsigned long long average = (total)/20;
    
    
    
    ofstream output("outputInsertion.txt", ios::app);
    if (output.is_open())
    {
        
        output <<"average comparisons for "<<amount<<" elements "<<average<<endl;
        output.close();
    }
}
