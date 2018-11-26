#include<iostream>
using namespace std;

int tower(int N,char BEG,char AUX,char END)
{
    if (N==1)
    {
        cout << BEG << " => "<< END <<endl;
    }
    else
    {
        tower(N-1,BEG,END,AUX);
        cout << BEG << " => "<<END<<endl;
        tower(N-1,AUX,BEG,END);
    }
}

int main()
{
    int N;
    char BEG, AUX, END;
    BEG = 'A';
    AUX = 'B';
    END = 'C';
    cout <<"Enter the number of disk : ";
    cin >> N;
    cout<<"TOWER OF HANOI IS:\n ";
    tower(N,BEG,AUX,END);

    return 0;
}



