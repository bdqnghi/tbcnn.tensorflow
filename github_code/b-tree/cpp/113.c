#ifndef BTREE_ITERATOR_H
#define BTREE_ITERATOR_H

#include <iterator>
#include <cassert>


// using namespace std;
template <typename T> class btree;
template<typename T> class btree_iterator;
template<typename T> class const_btree_iterator;

template <typename T>class btree_iterator{
	
public:
	typedef ptrdiff_t                  		difference_type;
	typedef std::bidirectional_iterator_tag	iterator_category;
	typedef T 						   		value_type;
	typedef T* 								pointer;
	typedef T& 								reference;
	friend class const_btree_iterator<T>;

	reference       operator *() const;
	pointer         operator->() const { return &(operator*()); }

	//prefix
	btree_iterator& operator++();
	btree_iterator& operator--();

	//postfix
	btree_iterator  operator++(int);
	btree_iterator  operator--(int);

	//copy assignment
	btree_iterator& operator =(const btree_iterator& other);

	//compare with const and non-const iterator
	bool			operator==(const btree_iterator& other) const;
	bool            operator==(const const_btree_iterator<T>& other) const;
	bool			operator!=(const btree_iterator& other) const { return !operator==(other); }
	bool            operator!=(const const_btree_iterator<T>& other) const { return !operator==(other); }
	
	//for increament
	//find the element in parent that is greater
	void moveUp_increament(value_type element );
	//find the element in children that is smaller
	void moveDown_increament();
	
	//for decreamtent
	//find the element in parent that is smaller 
	void moveUp_decreament(value_type);
	//find the element in children that is greater
	void moveDown_decreament();
	

	value_type currElement(){return pointee_->elem_[index_];}

	//constructor
	btree_iterator(typename btree<T>::Node *pointee = nullptr, size_t maxNum = 0, 
			const btree<T> *btree = nullptr):
			pointee_{pointee}, index_{maxNum}, btree_{btree}{}
	
	//copy constructor (from non-const)
	btree_iterator(const btree_iterator<T>& rhs) : 
			pointee_{rhs.pointee_}, index_{rhs.index_}, btree_{rhs.btree_}{}

	//copy constructor (from const)
	btree_iterator(const const_btree_iterator<T>& rhs) : 
			pointee_{rhs.pointee_}, index_{rhs.index_}, btree_{rhs.btree_}{}

	

private:
	typename btree<T>::Node *pointee_;
	size_t 					index_;
	const btree<T> 			*btree_;
};

template <typename T>class const_btree_iterator{
	friend class btree_iterator<T>;
public:
	typedef ptrdiff_t                  		difference_type;
	typedef std::bidirectional_iterator_tag	iterator_category;
	typedef T 						   		value_type;
	typedef const T* 								pointer;
	typedef const T& 								reference;

	reference       	  operator*()  const;
	pointer        		  operator->() const { return &(operator*()); }

	//prefix
	const_btree_iterator& operator++();
	const_btree_iterator& operator--();

	//postfix
	const_btree_iterator  operator++(int);
	const_btree_iterator  operator--(int);

	//copy assignment
	const_btree_iterator& operator =(const const_btree_iterator& other);

	//compare with const and non-const iterator
	bool				  operator==(const const_btree_iterator& other) const;
	bool            	  operator==(const btree_iterator<T>& other) const;
	bool				  operator!=(const const_btree_iterator& other) const	{ return !operator==(other); }
	bool            	  operator!=(const btree_iterator<T>& other) const		{ return !operator==(other); }
	
	//constructor
	const_btree_iterator(typename btree<T>::Node *pointee = nullptr, size_t maxNum = 0, 
			const btree<T> *btree = nullptr):
			pointee_{pointee}, index_{maxNum}, btree_{btree}{}

	//copy constructor (from non-const)
	const_btree_iterator(const btree_iterator<T>& rhs) : 
			pointee_{rhs.pointee_}, index_{rhs.index_}, btree_{rhs.btree_}{}

	//copy constructor (from non-const)
	const_btree_iterator(const const_btree_iterator<T>& rhs) : 
			pointee_{rhs.pointee_}, index_{rhs.index_}, btree_{rhs.btree_}{}
	
	//for increament
	//find the element in parent that is greater
	void moveUp_increament(value_type element );
	//find the element in children that is smaller
	void moveDown_increament();
	
	//for decreamtent
	//find the element in parent that is smaller 
	void moveUp_decreament(value_type);
	//find the element in children that is greater
	void moveDown_decreament();
	

	value_type currElement(){return pointee_->elem_[index_];}



private:
	typename btree<T>::Node *pointee_;
	size_t 					index_;
	const btree<T> 			*btree_;
};

#include "btree_iterator.tem"
#endif


