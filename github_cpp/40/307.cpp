// Program to sort array using quick sort

#include <iostream>
using namespace std;
const int MAX = 10 ;

class array
{
	private :

		int arr[MAX] ;
		int count ;

	public :

		array( ) ;
		void add ( int item ) ;
		int getcount( ) ;
		static int partition ( int *, int, int ) ;
		void quiksort ( int lower, int upper ) ;
		void display( ) ;
} ;
array :: array( )
{
	count = 0 ;
	for ( int i = 0 ; i < MAX ; i++ )
		arr[i] = 0 ;
}
void array :: add ( int item )
{
 if( count < MAX )
	
		arr[count] = item ;
		count++ ;
	
}
int array :: getcount( )
{
	return count ;
}


void array :: quiksort ( int lower, int upper )
{
	if ( upper > lower )
	{
		int i = partition ( arr, lower, upper ) ;
		quiksort ( lower, i - 1 ) ;
		quiksort ( i + 1, upper ) ;
	}
}
int array :: partition ( int *a, int lower, int upper )
{
	int i, p, q, t ;

	p = lower + 1 ;
	q = upper ;
	i = a[lower] ;

	while ( q >= p )
	{
		while ( a[p] < i )
			p++ ;

		while ( a[q] > i )
			q-- ;

		if ( q > p )
		{
			t = a[p] ;
			a[p] = a[q] ;
			a[q] = t ;
		}
	}

	t = a[lower] ;
	a[lower] = a[q] ;
	a[q] = t ;

	return q ;
}
void array :: display( )
{
	for ( int i = 0 ; i < count ; i++ )
		cout << arr[i] << "  " ;
	cout << endl ;
}


int main( )
{
	array a;
    int n;
    cout<<"Enter number of elements : ";
    cin>>n;
    cout<<"Enter "<<n<<" numbers:\n";
    for(int i=0;i<n;i++)
    {
            int num;
            cin>>num;
            a.add(num);
    }
            
	cout << "\nQuik sort.\n" ;
	cout << "\nArray before sorting:" << endl ;
	a.display( ) ;

	int c = a.getcount( ) ;

	a.quiksort ( 0, c - 1 ) ;
	cout << "\nArray after quick sorting:" << endl ;
	a.display( ) ;
	return 0;
}
