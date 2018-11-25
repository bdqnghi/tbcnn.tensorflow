#include <stdint.h>

class MergeSort {

public:

	/**
	 * @return an object of a merged list
	 */
	static MergeSort sort(const uint32_t list[], uint32_t listlen);
	

	MergeSort(const uint32_t list[], uint32_t listlen);

	virtual ~MergeSort();
		
	/**
	 * return use Copy Constructor
	 */
	MergeSort(const MergeSort& rhs);

	uint32_t* sortedList;

	uint32_t	sortedListLen;
		
private:

	/**
	 * @return an object of a merged list
	 */
	MergeSort& operator+=(const MergeSort&);
	
		
	/**
	 * @return an object of a merged list
	 */
	MergeSort& operator=(const MergeSort&);
};


