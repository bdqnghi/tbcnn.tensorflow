
#ifndef __SORT_H__
#define __SORT_H__




template< typename _type_ >
ID_INLINE void SwapValues( _type_ & a, _type_ & b ) {
	_type_ c = a;
	a = b;
	b = c;
}


template< typename _type_ >
class idSort {
public:
	virtual			~idSort() {}
	virtual void	Sort( _type_ * base, unsigned int num ) const = 0;
};


template< typename _type_, typename _derived_ >
class idSort_Quick : public idSort< _type_ > {
public:
	virtual void Sort( _type_ * base, unsigned int num ) const {
		if ( num <= 0 ) {
			return;
		}

		const int MAX_LEVELS = 128;
		int lo[MAX_LEVELS], hi[MAX_LEVELS];

		
		
		lo[0] = 0;
		hi[0] = num - 1;

		for ( int level = 0; level >= 0; ) {
			int i = lo[level];
			int j = hi[level];

			
			
			if ( ( ( j - i ) >= 4 ) && ( level < ( MAX_LEVELS - 1 ) ) ) {

				
				
				
				int pi = ( i + j ) / 2;

				
				SwapValues( base[j], base[pi] );

				
				_type_ & pivot = base[j--];

				
				do {
					while( static_cast< const _derived_ * >( this )->Compare( base[i], pivot ) < 0 ) { if ( ++i >= j ) break; }
					while( static_cast< const _derived_ * >( this )->Compare( base[j], pivot ) > 0 ) { if ( --j <= i ) break; }
					if ( i >= j ) break;
					SwapValues( base[i], base[j] );
				} while( ++i < --j );

				
				
				
				while ( static_cast< const _derived_ * >( this )->Compare( base[i], pivot ) <= 0 && i < hi[level] ) { i++; }
				while ( static_cast< const _derived_ * >( this )->Compare( base[j], pivot ) >= 0 && lo[level] < j ) { j--; }

				
				SwapValues( pivot, base[i] );

				assert( level < MAX_LEVELS - 1 );
				lo[level+1] = i;
				hi[level+1] = hi[level];
				hi[level] = j;
				level++;

			} else {

				
				for( ; i < j; j-- ) {
					int m = i;
					for ( int k = i + 1; k <= j; k++ ) {
						if ( static_cast< const _derived_ * >( this )->Compare( base[k], base[m] ) > 0 ) {
							m = k;
						}
					}
					SwapValues( base[m], base[j] );
				}
				level--;
			}
		}
	}
};


template< typename _type_ >
class idSort_QuickDefault : public idSort_Quick< _type_, idSort_QuickDefault< _type_ > > {
public:
	int Compare( const _type_ & a, const _type_ & b ) const { return a - b; }
};


template<>
class idSort_QuickDefault< float > : public idSort_Quick< float, idSort_QuickDefault< float > > {
public:
	int Compare( const float & a, const float & b ) const {
		if ( a < b ) {
			return -1;
		}
		if ( a > b ) {
			return 1;
		}
		return 0;
	}
};


template< typename _type_, typename _derived_ >
class idSort_Heap : public idSort< _type_ > {
public:
	virtual void Sort( _type_ * base, unsigned int num ) const {
		
#if 1
		
		for ( unsigned int i = num / 2; i > 0; i-- ) {
			
			unsigned int parent = i - 1;
			for ( unsigned int child = parent * 2 + 1; child < num; child = parent * 2 + 1 ) {
				if ( child + 1 < num && static_cast< const _derived_ * >( this )->Compare( base[child + 1], base[child] ) > 0 ) {
					child++;
				}
				if ( static_cast< const _derived_ * >( this )->Compare( base[child], base[parent] ) <= 0 ) {
					break;
				}
				SwapValues( base[parent], base[child] );
				parent = child;
			}
		}
#else
		
		for ( unsigned int i = 1; i < num; i++ ) {
			
			for ( unsigned int child = i; child > 0; ) {
				unsigned int parent = ( child - 1 ) / 2;
				if ( static_cast< const _derived_ * >( this )->Compare( base[parent], base[child] ) > 0 ) {
					break;
				}
				SwapValues( base[child], base[parent] );
				child = parent;
			}
		}
#endif
		
		for ( unsigned int i = num - 1; i > 0; i-- ) {
			SwapValues( base[0], base[i] );
			
			unsigned int parent = 0;
			for ( unsigned int child = parent * 2 + 1; child < i; child = parent * 2 + 1 ) {
				if ( child + 1 < i && static_cast< const _derived_ * >( this )->Compare( base[child + 1], base[child] ) > 0 ) {
					child++;
				}
				if ( static_cast< const _derived_ * >( this )->Compare( base[child], base[parent] ) <= 0 ) {
					break;
				}
				SwapValues( base[parent], base[child] );
				parent = child;
			}
		}
	}
};


template< typename _type_ >
class idSort_HeapDefault : public idSort_Heap< _type_, idSort_HeapDefault< _type_ > > {
public:
	int Compare( const _type_ & a, const _type_ & b ) const { return a - b; }
};


template< typename _type_, typename _derived_ >
class idSort_Insertion : public idSort< _type_ > {
public:
	virtual void Sort( _type_ * base, unsigned int num ) const {
		_type_ * lo = base;
		_type_ * hi = base + ( num - 1 );
		while( hi > lo ) {
			_type_ * max = lo;
			for ( _type_ * p = lo + 1; p <= hi; p++ ) {
				if ( static_cast< const _derived_ * >( this )->Compare( (*p), (*max) ) > 0 ) {
					max = p;
				}
			}
			SwapValues( *max, *hi );
			hi--;
		}
	}
};


template< typename _type_ >
class idSort_InsertionDefault : public idSort_Insertion< _type_, idSort_InsertionDefault< _type_ > > {
public:
	int Compare( const _type_ & a, const _type_ & b ) const { return a - b; }
};

#endif 
