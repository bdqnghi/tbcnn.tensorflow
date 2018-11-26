#include <iostream>
#include "cmn.cpp"

template <typename T>
void sort(T *data,size_t cnt){
    for(size_t idx=0;idx<cnt-1;++idx){
        for(size_t jdx=cnt-1;jdx>idx;--jdx){
            if(*(data+jdx)<*(data+jdx-1)){
                T tmp=*(data+jdx);
                *(data+jdx)=*(data+jdx-1);
                *(data+jdx-1)=tmp;
            }
        }
    }
}

void tst(){
    using std::cout;
    using std::endl;

    const size_t CNT=10;
    int *data=getRandData(CNT);
    cout << endl << endl << "Befor Sort:" << endl;
    showData(data,CNT);

    sort(data,CNT);

    cout << endl << endl << "After Sort:" << endl;
    showData(data,CNT);
    cout << endl << endl;
    
    delete [] data;
}


int main(int argc,char ** argv){
    tst();

    return 0;
}
