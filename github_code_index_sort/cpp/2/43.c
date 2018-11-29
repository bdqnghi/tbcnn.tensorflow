/*
    Conor Patrick, HW5
    04/22/2014
    mergesort.cpp
        Implementation of mergesort.h (mergesort algorithm)
*/

#include "mergesort.h"


/*
    Begin merge sort given a pointer to data and it's size.
*/
mergeSort::mergeSort(item *p, int s){
    this->_data = p;
    this->_size = s;
    this->tmp = new item[s];
    if (this->tmp == NULL)
        throw(string("new returned NULL in mergeSort::mergeSort"));
    this->sort(this->_data, 0, this->_size);
}
/*
    Clean up
*/
mergeSort::~mergeSort(){
    if (this->tmp != NULL) delete[] this->tmp;
}
/*
    print out array
*/
void mergeSort::print(){
    for (int i = 0; i< _size; i++){
	cout<< (_data[i]).letter
	    << ":"
	    << _data[i].freq;
	if (i+1 < _size) cout << ", ";
    }
    cout << endl;
}

/*
    Writes mergeSort results to a file
*/
void mergeSort::write(ofstream &file){
    for (int i = 0; i< _size; i++){
	file<< (_data[i]).letter
	    << " "
	    << _data[i].freq
            << endl;
    }
    
}
/*
    Recursively split array into segments and mergesort.
*/ 
void mergeSort::sort(item items[], int start, int end){
    
    if (end-start < 2) return;                // all sorted.
    
    int mid = (end + start)/2;
	    this->sort(items,start, mid );
    this->sort(items,mid, end);
    
    this->merge(items, start, mid, end);
}
/*
    Combines two segments while ordering them
*/
void mergeSort::merge(item items[], int start, int mid, int end){
    int i = start;
    int leftStart = start,  leftEnd = mid;
    int rightStart = mid,  rightEnd = end;
    
    /* Merge and order two array segments */
    for (/* */; leftStart< leftEnd && rightStart < rightEnd; ++i){
	if (items[leftStart].freq < items[rightStart].freq ){
	    tmp[i] = items[leftStart];
	    ++leftStart;
	}else{
	    tmp[i] = items[rightStart];
	    ++rightStart;
	}
	  
    }
    /* copy over any leftovers */
    for (/* */; leftStart < leftEnd; ++leftStart, ++i)
	tmp[i] = items[leftStart];
	
    for (/* */; rightStart < rightEnd; ++rightStart, ++i)
	tmp[i] = items[rightStart];
	
    /* copy over from the tmp array */
    for (i=start; i<end; ++i)
	this->_data[i] = tmp[i];
    
}
/*
    Operator overloads for comparisons
*/
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


