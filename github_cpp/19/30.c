

#pragma once








template <class T> void QuickSortRecursive(T *pArr, int d, int h, BOOL bAscending)
{
	int i,j;
	T str;

	i = h;
	j = d;

	str = pArr[((int) ((d+h) / 2))];

	do {

		if (bAscending) {
			while (pArr[j] < str) j++;
			while (pArr[i] > str) i--;
		} else {
			while (pArr[j] > str) j++;
			while (pArr[i] < str) i--;
		}

		if ( i >= j ) {

			if ( i != j ) {
				T zal;

				zal = pArr[i];
				pArr[i] = pArr[j];
				pArr[j] = zal;

			}

			i--;
			j++;
		}
	} while (j <= i);

	if (d < i) QuickSortRecursive(pArr,d,i,bAscending);
	if (j < h) QuickSortRecursive(pArr,j,h,bAscending);
}











template <class T> BOOL QuickSort(T *pArr, int iSize, BOOL bAscending = TRUE)
{
	BOOL rc = TRUE;

	if (iSize > 1) {

		try {

			int	low = 0,
				high = iSize - 1;

			QuickSortRecursive(pArr,low,high,bAscending);

		} catch (...) {
			::SetLastError(ERROR_INVALID_PARAMETER);
			rc = FALSE;
		}

	} else {
		::SetLastError(ERROR_INVALID_PARAMETER);
		rc = FALSE;
	}

	return rc;
}








template <class T, class PT> class CQArray : public CArray <T, PT>
{
public:
	void QuickSort(BOOL bAscending = TRUE);
};










template <class T, class TP> void CQArray<T,TP>::QuickSort(BOOL bAscending)
{
	if (GetSize() > 1) {
		::QuickSort(GetData(),GetSize(),bAscending);
	}
}
