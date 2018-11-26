
#include "sort/merge-sort.h"  // merge()  // merge-sort duplicated here

#include "sort/sort.h"  // selection_sort(), is_sorted()

#include "aux1/copy.h"
#include "fxtio.h"
#include "fxttypes.h"

#include "jjassert.h"
#include "nextarg.h"  // NXARGSTR()

//% Demo of the merge sort algorithm.


char *ff;
ulong nn;
static void PRINT(const char *f, ulong i, ulong n)
{
    ulong d = (ulong)(f - ff);
    f = ff;
//    cout << "  range0[" << i << ", " << n << "] : ";
    i += d;  n += d;

//    cout << "  range[" << i << ", " << n << "] : ";
    cout << "[";
    for (ulong k=0; k<i; ++k)  cout << "  ";
    for (ulong k=i; k<n; ++k)  cout << " " << f[k] << "";
    for (ulong k=n; k<nn; ++k)  cout << "  ";
    cout << " ]";
    cout << endl;
}
// -------------------------


template <typename Type>
void demo_merge_sort_rec(Type *f, ulong n, Type *t)
{
    if ( n<8 )
    {
        selection_sort(f, n);
        return;
    }

    const ulong na = n>>1;
    const ulong nb = n - na;

    demo_merge_sort_rec(f, na, t);
    demo_merge_sort_rec(f+na, nb, t);

    PRINT(f, 0, na);
    PRINT(f+na, 0, nb);

    merge(f, na, nb, t);
    for (ulong j=0; j<n; ++j)  f[j] = t[j];   // copy back
    PRINT(f, 0, n);
    cout << endl;

    jjassert( is_sorted(f, n) );
}
// -------------------------


template <typename Type>
void demo_merge_sort(Type *f, ulong n, Type *tmp=0)
{
    Type *t = tmp;
    if ( tmp==0 )  t = new Type[n];
    demo_merge_sort_rec(f, n, t);
    if ( tmp==0 )  delete [] t;
}
// -------------------------




int
main(int argc, char **argv)
{
    char *str;
    NXARGSTR(str, "String to sort", "nowsortmeADBACD54321");
//    NXARGSTR(str, "String to sort", "nowsortme");
//    NXARGSTR(str, "String to sort", "hgfedcba");
//    NXARGSTR(str, "String to sort", "TheBinarySplittingSchemeForProductsOrSo");
//    NXARGSTR(str, "String to sort", "2705520349807111576968325245272272053880818086");

    ulong n = strlen(str);
    char *f = new char[n+1];
    ff = f;  nn = n;
    acopy(str, f, n);

    bool q4 = 1;
    NXARG(q4, "Whether to use 4-way merging");

    PRINT(f, 0, n);  cout << endl;
    demo_merge_sort(f, n);
    jjassert( is_sorted(f, n) );


    // test routine in merge-sort.h:
    acopy(str, f, n);
    merge_sort(f, n);
    jjassert( is_sorted(f, n) );


    delete [] f;

    return 0;
}
// -------------------------



/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/sort"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/sort/merge-sort-demo.cc"
/// make-target2: "1demo DSRC=demo/sort/merge-sort-demo.cc DEMOFLAGS=-DTIMING"
/// End:

