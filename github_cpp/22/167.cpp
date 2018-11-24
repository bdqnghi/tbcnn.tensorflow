#include <iostream>

const int buffSize = 1000000;

class Heap {
  
    int* buff_;
    int size_;
     
     void siftDown(int i) {
        while (2 * i + 1 < size_) {
            int k = 2 * i + 1;
            if ((2 * i + 2 < size_) && (buff_[2 * i + 2] < buff_[2 * i + 1]))
                k = 2 * i + 2;
            if (buff_[i] > buff_[k]) {
                std::swap(buff_[i], buff_[k]);
                i = k;
            } else
                break;
        }
    }

    void siftUp(int i) {
        while (buff_[i] < buff_[(i - 1) / 2]) {
            std::swap(buff_[i], buff_[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }

    void build(int* arr, int size_) {
        for (int j = 0; j < size_; ++j) {
            buff_[j] = arr[j];
            siftUp(j);
        }
    }
    
  public:

    ~Heap() {
        delete[] buff_;
    }

    Heap(int elemnumber = 0, int* arr = nullptr) { 
        size_ = elemnumber;
        buff_ = new int[buffSize];
        build(arr, size_);
    }

    int size() const {
        return size_;
    }

    int erase() {
        int min = buff_[0];
        buff_[0] = buff_[size_ - 1];
        --size_;
        siftDown(0);
        return min;
    }

    void add(int newElem) {
        ++size_;
        buff_[size_ - 1] = newElem;
        siftUp(size_ - 1);
    }

    int get () const {
        return buff_[0];
    }
};

void heapSort(int* arr, int elemNumber) {
    Heap h = Heap(elemNumber, arr);
    for (int i = 0; i < elemNumber; ++i)
        arr[i] = h.erase();
}

int main () {
    int elemNumber;
    std::cin >> elemNumber;
    int* arr = new int[elemNumber];
    for (int i = 0; i < elemNumber; ++i)
        std::cin >> arr[i];
    heapSort(arr, elemNumber);
    for (int i = 0; i < elemNumber; ++i)
        std::cout << arr[i] << " ";
    delete[] arr;
    return 0;
} 