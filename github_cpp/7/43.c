

#include "mergesort.h"



mergeSort::mergeSort(item *p, int s){
    this->_data = p;
    this->_size = s;
    this->tmp = new item[s];
    if (this->tmp == NULL)
        throw(string("new returned NULL in mergeSort::mergeSort"));
    this->sort(this->_data, 0, this->_size);
}

mergeSort::~mergeSort(){
    if (this->tmp != NULL) delete[] this->tmp;
}

void mergeSort::print(){
    for (int i = 0; i< _size; i++){
	cout<< (_data[i]).letter
	    << ":"
	    << _data[i].freq;
	if (i+1 < _size) cout << ", ";
    }
    cout << endl;
}


void mergeSort::write(ofstream &file){
    for (int i = 0; i< _size; i++){
	file<< (_data[i]).letter
	    << " "
	    << _data[i].freq
            << endl;
    }
    
}
 
void mergeSort::sort(item items[], int start, int end){
    
    if (end-start < 2) return;                
    
    int mid = (end + start)/2;
	    this->sort(items,start, mid );
    this->sort(items,mid, end);
    
    this->merge(items, start, mid, end);
}

void mergeSort::merge(item items[], int start, int mid, int end){
    int i = start;
    int leftStart = start,  leftEnd = mid;
    int rightStart = mid,  rightEnd = end;
    
    
    for (; leftStart< leftEnd && rightStart < rightEnd; ++i){
	if (items[leftStart].freq < items[rightStart].freq ){
	    tmp[i] = items[leftStart];
	    ++leftStart;
	}else{
	    tmp[i] = items[rightStart];
	    ++rightStart;
	}
	  
    }
    
    for (; leftStart < leftEnd; ++leftStart, ++i)
	tmp[i] = items[leftStart];
	
    for (; rightStart < rightEnd; ++rightStart, ++i)
	tmp[i] = items[rightStart];
	
    
    for (i=start; i<end; ++i)
	this->_data[i] = tmp[i];
    
}

bool item::operator<(const item &orig){
    return (this->freq < orig.freq);
}
bool item::operator>(const item &orig){
    return (this->freq > orig.freq);
}
bool item::operator>=(const item &orig){
    return (this->freq >= orig.freq);
}
bool item::operator<=(const item &orig){
    return (this->freq <= orig.freq);
}


