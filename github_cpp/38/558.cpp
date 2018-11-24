

#include <iostream>

using namespace std;

// Forehead declaration.
void TestQueue();

int main()
{
    TestQueue();
    return 0;
}

template<class _tT>
class _cQueue
{
    typedef _tT ElementType;
    typedef size_t SizeType;
public:
    _cQueue(SizeType nCreateSize);
    bool empty();
    bool full();
    void dispose();
    void makeEmpty();
    void enqueue(ElementType ele);
    void dequeue();
    ElementType front();
    template<class _tT>
    friend ostream& operator<< (ostream&, const _cQueue<_tT>&);

private:
    ElementType* index_;
    SizeType nCapacity_;
    SizeType nSize_;
    SizeType nFront_;
    SizeType nRear_;
};

void TestQueue()
{
    _cQueue<int> q(10);
    q.enqueue(5);
    q.enqueue(6);
    q.enqueue(9);
    q.enqueue(10);
    cout << q << endl;
    q.dequeue();
    q.dequeue();
    q.dequeue();
    cout << q << endl;
}

template<class _tT>
_cQueue<_tT>::_cQueue(SizeType nCreateSize):
    index_(new typename _cQueue<_tT>::ElementType[nCreateSize]),
    nCapacity_(nCreateSize),
    nSize_(0),
    nFront_(0),
    nRear_(0)
{

}

template<class _tT>
bool _cQueue<_tT>::empty()
{
    return nSize_ == 0;
}

template<class _tT>
void _cQueue<_tT>::dispose()
{
    // Simply implement the dispose().
    // Doesn't think about the memory manager.

    nSize_(0);
    nFront_(0);
    nRear_(0);
}

template<class _tT>
void _cQueue<_tT>::makeEmpty()
{
    nSize_(0);
    nFront_(0);
    nRear_(0);
}

template<class _tT>
bool _cQueue<_tT>::full()
{
    return nSize_ != 0 && nFront_ == nRear_;
}

template<class _tT>
void _cQueue<_tT>::enqueue(typename _cQueue<_tT>::ElementType ele)
{
    if(!full())
    {
        index_[nFront_ ++ ] = ele;
        if(nFront_ == nCapacity_)
        {
            nFront_ = 0;
        }
        ++ nSize_;
    }
}

template<class _tT>
void _cQueue<_tT>::dequeue()
{
    if(!empty())
    {
        if(nRear_ == nCapacity_ - 1)
        {
            nRear_ = 0;
        }
        else
        {
            ++ nRear_;
        }
        -- nSize_;
    }
}

template<class _tT>
typename _cQueue<_tT>::ElementType _cQueue<_tT>::front()
{
    return index_[nFront_];
}

template<class _tT>
ostream& operator<< (ostream& os, const _cQueue<_tT>& q)
{
    for(typename _cQueue<_tT>::SizeType i = q.nRear_; i != q.nFront_;)
    {
        os << q.index_[i ++ ] << "   ";
        if(i == q.nCapacity_)
        {
            i = 0;
        }
    }
    return os << endl;
}