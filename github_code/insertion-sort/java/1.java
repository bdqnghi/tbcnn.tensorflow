import java.util.Random;

public class Insertion
    /* 
       Performs insertion sort on an array of InsertionSortNodes.  The
       key field of the InsertionSortNode determines the order of the
       node in the array.  The value field contains the data. In this
       version, the array being sorted is a static field as opposed to
       an argument of the insertionSort method.

       MINUS: there were bunch of lemmas that needed to be proved in 
       insertionSort_Insertion-lemmas.thy
       but vcgen changed slightly and they do not get recognized as sufficient
       any more.

    */
{
    public static InsertionSortNode[] arr;

    /*:
      public static specvar content :: objset;
      vardefs "content == { n. EX i. 0 <= i & i < (Array.length Insertion.arr) & Insertion.arr.[i] = n}"

      // elements are nonnull:
      invariant "(ALL k. (0 <= k & k < (Array.length Insertion.arr)) --> Insertion.arr.[k] ~= null)"

      // elements are distinct:
      invariant "(ALL k. (ALL l. ((0 <= k & k < (Array.length Insertion.arr) & 0 <= l & l < (Array.length Insertion.arr) & k ~= l) --> 
	Insertion.arr.[k] ~= Insertion.arr.[l])))"
    */

    public static void main(String[] args)
    {
	Random generator = new Random();
	
	int size = generator.nextInt(50);

	arr = new InsertionSortNode[size];

	int i = 0;
	
	while(i < arr.length)
	{
	    arr[i] = new InsertionSortNode();
	    arr[i].key = generator.nextInt(100);
	    i = i + 1;
	}

	printArray();
	
	insertionSort();

	printArray();
    }
    
    /* In this version of insertionSort, the precondition additionally
       states that there are no duplicates in the array. The
       postcondition checks not only the sorted-ness of the array, but
       also that it contains the same set of elements as the original array. */
    public static void insertionSort()
    /*: 
      requires "Insertion.arr ~= null"	
      modifies "Array.arrayState", content
      ensures "Insertion.arr ~= null &
        comment ''finalArrayIsTrue''
          (ALL k. ((0 <= k & k < ((Array.length Insertion.arr) - 1)) --> 
            (Insertion.arr.[k]..InsertionSortNode.key <= Insertion.arr.[k+1]..InsertionSortNode.key))) &
        comment ''arrayLengthPreserved''
          (Array.length Insertion.arr) = (Array.length (old Insertion.arr)) &
        comment ''setOfelementsPreserved''
          content = (old content)"
    */
    {
	int i = 1;

	while 
	    /*: inv "(ALL k. (0 <= k & k < (i - 1)) -->
		(Insertion.arr.[k]..InsertionSortNode.key <= Insertion.arr.[k+1]..InsertionSortNode.key)) &
		content = (old content) &
		(ALL k. (ALL l. ((0 <= k & k < (Array.length Insertion.arr) & 0 <= l & l < (Array.length Insertion.arr) & k ~= l) --> 
		Insertion.arr.[k] ~= Insertion.arr.[l])))"
	     */
	    (i < arr.length)
	{
	    int j = i;
	    while
		/*: inv "j <= i &  
		  (ALL k. (0 <= k & k < (Array.length Insertion.arr)) --> Insertion.arr.[k] ~= null) &
		  (ALL k. (0 <= k & k < (j - 1)) --> 
		  (Insertion.arr.[k]..InsertionSortNode.key <= Insertion.arr.[k + 1]..InsertionSortNode.key)) &
		  (ALL k. (j <= k & k < i) --> 
		  (Insertion.arr.[k]..InsertionSortNode.key <= Insertion.arr.[k + 1]..InsertionSortNode.key)) &
		  ((0 < j & j < i) --> 
		  (Insertion.arr.[j - 1]..InsertionSortNode.key <= Insertion.arr.[j + 1]..InsertionSortNode.key)) &
		  content = (old content) &
		  (ALL k. (ALL l. ((0 <= k & k < (Array.length Insertion.arr) & 0 <= l & l < (Array.length Insertion.arr) & k ~= l) --> 
		  Insertion.arr.[k] ~= Insertion.arr.[l])))"
		 */
		(j > 0)
	    {
		if (arr[j].key < arr[j-1].key)
		{
		    InsertionSortNode tmp = arr[j];
		    arr[j] = arr[j-1];
		    arr[j-1] = tmp;
		}
		j = j - 1;
	    }
	    i = i + 1;
	}
    }

    public static void printArray()
    {
	int i = 0;

	while(i < arr.length)
	{
	    System.out.print(arr[i].key + " ");
	    i = i + 1;
	}

	System.out.println("");
    }
}
