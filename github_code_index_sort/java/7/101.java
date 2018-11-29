package aeminium.shellsort;
import java.util.Random;
public class SeqShellSort {
	
	public static Integer[] data;
	
	public static int DEFAULT_SIZE  = 10000;
	
	SeqShellSort(){
		
		data = new Integer[DEFAULT_SIZE];
	}
	
	/*public static void createColl(int size){
    	 data = new Integer[size];
	}*/
    public static Integer[] InitializeColl(Integer[] data) {
	        
    	Random randGen = new Random();// do nothing
	        
	        for (Integer i = 0; i < data.length; i++) {
	            data[i] = (randGen.nextInt());// value flow rule for data
	        }
	        return data;// Read-only rule for data
	}
	public static void displayArray(Integer[] data) {
		for (int i = 0; i < data.length; i++) {
			System.out.println(""+ data[i]);
		}
	}
	public static void Sort(Integer[] data, Integer[] gaps)
    {
        for (Integer gap : gaps){
            
        	for (Integer i = gap; i < data.length; i++){
                Integer temp = data[i];
                Integer j = i;
                for (; j >= gap && data[j - gap] > temp; j -= gap)
                {
                    data[j] = data[j - gap];
                }
                data[j] = temp;
            }
        }
    }
	public static boolean isSorted(Integer[] data) {
        for (Integer i = 1; i < data.length; i++) {
            if (data[i-1] > data[i])
                return false;
        }
        return true;// do nothing
    }
}
class Client{
	
	public static Integer[] gaps = new Integer[] {701,301,132,57,23,10,4,1};
	
	/*public static Integer[] createGaps(){
		 gaps = new Integer[] {701,301,132,57,23,10,4,1};
		 return gaps;// 
	}*/
	public static void main(String[] args) throws Exception{
		
		long start = System.nanoTime();
		//SeqShellSort.createColl(SeqShellSort.DEFAULT_SIZE); 
		SeqShellSort.InitializeColl(SeqShellSort.data); 
		SeqShellSort.displayArray(SeqShellSort.data); 
		if(!SeqShellSort.isSorted(SeqShellSort.data)){
			SeqShellSort.Sort(SeqShellSort.data,Client.gaps);
		}
		System.out.println("Sorted Array");
		long end = System.nanoTime();
    	long elapsedTime = end - start;
    	double ms = (double)elapsedTime / 1000000.0;
    	System.out.println(" Milli Seconds Time = "+ms);
	}
}

/*
 * Class Name = SeqShellSort
Compilation Unit Names = SeqShellSort.java
Class Name = SeqShellSort
Method Name = main
Ref-Var= data, Pre-Permissions=none, Post Permissions=unique
Ref-Var= gaps, Pre-Permissions=none, Post Permissions=unique
Method Name = createColl
Ref-Var= data, Pre-Permissions=none, Post Permissions=unique
Method Name = InitializeColl
Ref-Var= data, Pre-Permissions=share, Post Permissions=share
Method Name = displayArray
Ref-Var= data, Pre-Permissions=pure, Post Permissions=pure
Method Name = inc
Ref-Var= data, Pre-Permissions=share, Post Permissions=share
Method Name = dec
Ref-Var= data, Pre-Permissions=share, Post Permissions=share
Method Name = createGaps
Ref-Var= gaps, Pre-Permissions=none, Post Permissions=unique
Method Name = Sort
Ref-Var= data, Pre-Permissions=share, Post Permissions=share
Ref-Var= gaps, Pre-Permissions=pure, Post Permissions=pure
Method Name = isSorted
Ref-Var= data, Pre-Permissions=pure, Post Permissions=pure
//////////////////////////////////////////////////////////////////////////
Class Name = SeqShellSort
Method Name = main
Ref-Var= shellsort.SeqShellSort.data, Pre-Permissions=none, Post Permissions=unique
Ref-Var= shellsort.SeqShellSort.gaps, Pre-Permissions=none, Post Permissions=unique
Method Name = createColl
Ref-Var= shellsort.SeqShellSort.data, Pre-Permissions=none, Post Permissions=unique
Method Name = InitializeColl
Ref-Var= shellsort.SeqShellSort.data, Pre-Permissions=share, Post Permissions=share
Method Name = displayArray
Ref-Var= shellsort.SeqShellSort.data, Pre-Permissions=pure, Post Permissions=pure
Method Name = inc
Ref-Var= shellsort.SeqShellSort.data, Pre-Permissions=share, Post Permissions=share
Method Name = dec
Ref-Var= shellsort.SeqShellSort.data, Pre-Permissions=share, Post Permissions=share
Method Name = createGaps
Ref-Var= shellsort.SeqShellSort.gaps, Pre-Permissions=none, Post Permissions=unique
Method Name = Sort
Ref-Var= shellsort.SeqShellSort.data, Pre-Permissions=share, Post Permissions=share
Ref-Var= shellsort.SeqShellSort.gaps, Pre-Permissions=pure, Post Permissions=pure
Method Name = isSorted
Ref-Var= shellsort.SeqShellSort.data, Pre-Permissions=pure, Post Permissions=pure

//////////////////////////////////////////////////////

Class Name = SeqShellSort
Method Name = main
none java.lang.Integer[] shellsort.SeqShellSort.data >> unique java.lang.Integer[] shellsort.SeqShellSort.data
none java.lang.Integer[] shellsort.SeqShellSort.gaps >> unique java.lang.Integer[] shellsort.SeqShellSort.gaps
Method Name = createColl
none java.lang.Integer[] shellsort.SeqShellSort.data >> unique java.lang.Integer[] shellsort.SeqShellSort.data
Method Name = InitializeColl
share java.lang.Integer[] shellsort.SeqShellSort.data >> share java.lang.Integer[] shellsort.SeqShellSort.data
Method Name = displayArray
pure java.lang.Integer[] shellsort.SeqShellSort.data >> pure java.lang.Integer[] shellsort.SeqShellSort.data
Method Name = inc
share java.lang.Integer[] shellsort.SeqShellSort.data >> share java.lang.Integer[] shellsort.SeqShellSort.data
Method Name = dec
share java.lang.Integer[] shellsort.SeqShellSort.data >> share java.lang.Integer[] shellsort.SeqShellSort.data
Method Name = createGaps
none java.lang.Integer[] shellsort.SeqShellSort.gaps >> unique java.lang.Integer[] shellsort.SeqShellSort.gaps
Method Name = Sort
share java.lang.Integer[] shellsort.SeqShellSort.data >> share java.lang.Integer[] shellsort.SeqShellSort.data
pure java.lang.Integer[] shellsort.SeqShellSort.gaps >> pure java.lang.Integer[] shellsort.SeqShellSort.gaps
Method Name = isSorted
pure java.lang.Integer[] shellsort.SeqShellSort.data >> pure java.lang.Integer[] shellsort.SeqShellSort.data

//////////////////////////////////////////////////////
Class Name = SeqShellSort
Method Name = main
@Perm(requires="none(shellsort.SeqShellSort.data) * none(shellsort.SeqShellSort.gaps) in ALIVE", ensures= "unique(shellsort.SeqShellSort.data) * unique(shellsort.SeqShellSort.gaps) in ALIVE")
Method Name = createColl
@Perm(requires="none(shellsort.SeqShellSort.data) in ALIVE", ensures= "unique(shellsort.SeqShellSort.data) in ALIVE")
Method Name = InitializeColl
@Perm(requires="share(shellsort.SeqShellSort.data) in ALIVE", ensures= "share(shellsort.SeqShellSort.data) in ALIVE")
Method Name = displayArray
@Perm(requires="pure(shellsort.SeqShellSort.data) in ALIVE", ensures= "pure(shellsort.SeqShellSort.data) in ALIVE")
Method Name = inc
@Perm(requires="share(shellsort.SeqShellSort.data) in ALIVE", ensures= "share(shellsort.SeqShellSort.data) in ALIVE")
Method Name = dec
@Perm(requires="share(shellsort.SeqShellSort.data) in ALIVE", ensures= "share(shellsort.SeqShellSort.data) in ALIVE")
Method Name = getGaps
@Perm(requires="none(shellsort.SeqShellSort.gaps) in ALIVE", ensures= "unique(shellsort.SeqShellSort.gaps) in ALIVE")
Method Name = Sort
@Perm(requires="share(shellsort.SeqShellSort.data) * pure(shellsort.SeqShellSort.gaps) in ALIVE", ensures= "share(shellsort.SeqShellSort.data) * pure(shellsort.SeqShellSort.gaps) in ALIVE")
Method Name = isSorted
@Perm(requires="pure(shellsort.SeqShellSort.data) in ALIVE", ensures= "pure(shellsort.SeqShellSort.data) in ALIVE")

//////////////////////////////////////////////////////*/
