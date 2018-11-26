import java.io.*;
import java.util.regex.Pattern;
//Using heap-sort to process this problem,set the priority to the heap-sort
//Through the entire program, it need to run (n + nlogn + n + nlogn + n + k),two heap-sort and three loop to process data 
//here k for basic operations(like compare operation,assignment operation and so on)
//therefore, the time complexity is: O(nlogn)
//see the following comments for the details

public class TaskScheduler {
	static void scheduler(String file1, String file2, Integer m)
			throws IOException {
		File f1 = new File(file1);
		if (!f1.exists()) {
			System.out.println("File1 does not exist");
			return;
		}
		BufferedReader readTxt = new BufferedReader(new FileReader(file1));
		String textLine = "";
		String str = "";
		
		while ((textLine = readTxt.readLine()) != null) {
			str += " " + textLine;
		}
		String S1 = str.trim();
//		System.out.println("3: "+ S1);
		String[] FileData = S1.split("\\s{1,}");
		readTxt.close();
//		System.out.println(FileData);
		int n = FileData.length / 3 + 1;
//		System.out.println("n = "+n);
		String[][] task = new String[n][4];
		int q = 1;
		
		for (int i = 0; i < FileData.length; i = i + 3) {
			task[q][1] = FileData[i + 1];
			task[q][2] = FileData[i + 2];
			task[q][0] = FileData[i];
			if (Pattern.matches("[a-zA-Z0-9]+", FileData[i])) {
				task[q][0] = FileData[i];
//				System.out.println("FileData[2] = "+FileData[2]);
//				System.out.println(task[q][0]);
				if (i + 1 < FileData.length && Pattern.matches("[0-9]+", FileData[i + 1])) 
				{	
					if (i + 2 < FileData.length && Pattern.matches("[0-9]+", FileData[i + 2])) 
					{			
			//			System.out.println("task[q][2] = "+task[q][2]);
						task[q][3] = "0";
						q++;
					} 
					else 
					{
						System.out.println("Input error when reading the attributes of the taskname: " + task[q][0] + " wrong deadline time: " + task[q][2]);
						System.exit(1);
					}
				} 
				else 
				{
					System.out.println("Input error when reading the attributes of the taskname: " + task[q][0] + " wrong release time: " + task[q][1]);
					System.exit(1);
				}
			} 
			else 
			{
				
				System.out.println("Input error when reading the attributes of the taskname: " + task[q][0]);
				System.exit(1);
			}
		}
		// call heapsort method, sort the initial array
		// see the detailed analysis of time complexity in the method body
		heapSort(task);
		
		// this "for" loop to process the release time
		// when the number of tasks which have same release time more than the
		// number of cores,add 1 of the value of release time
		// this loop run n times,since there is no nest within the loop body
		int time = 0;
		int cores = m;
		for (int i = 1; i < n; i++) {
			if (time > Integer.parseInt(task[i][2]) - 1) {
				System.out.println("no feasible schedule");
				return;
			}
			if (Integer.parseInt(task[i][1]) <= time) {
				if (cores > 0) {
					task[i][3] = String.valueOf(time);
					cores--;
				} else {
					time++;
					cores = m;
					i--;
				}
			} else {
				time = Integer.parseInt(task[i][1]);
				cores = m;
				i--;
			}
		}
		// call the heapsort again, to sort the final array
		// see the detailed analysis of time complexity in the method body
		heapSort2(task);
		
		
		String S2 = "";
		// this loop to output the data of array to string
		for (int i = 1; i < n; i++) {
			S2 = S2 + task[i][0] + " " + task[i][3] + " ";
		}
	
		File f2 = new File(file2);
//		if (f2.exists()) {
//			System.out.println("File2 already exists");
//			return;
//		}
		FileWriter output = new FileWriter(f2);
		output.write(S2);
		output.flush();
		output.close();

	}

	// Process of heap-sort:
	// set a heap which has n elements,the method to adjust is:
	// swapping the root element with last element, the heap is broken at this
	// time,because the root node does not satisfy
	// the rules of heap,and left-subtree and right-subtree still are heaps.
	// then the current root swap with child
	// (the bigger one within left and right child), if root swap with left
	// child, the left_subtree will be broken,since
	// the root of left-subtree does not satisfy the rules of heap, for
	// right-subtree and vice versa, keep process the subtree
	// use the above swapping method,until to the leaf node, the heap is rebuilded.
	// //////////////////////////////////////////////////////////////////////////////
	// Analysis of heap-sort Time Complexity:
	// during building the max heap, since we build the heap according to the
	// attributes of complete binary tree,
	// swapping child if necessary,for every non-ending node, actually run
	// comparison operation and
	// swap operation two times,therefore, the time complexity of entire
	// build-heap is O(n)
	// when sorting, select temporary root to rebuild the heap need run time
	// complexity O(logi)
	// also need adjust n-1 times,therefore, the time complexity of rebuild-heap
	// is O(nlogn)
	// so, in general, the time complexity of heap-sort is O(nlogn)
	public static void heapSort(String[][] data) {
		// according to the attributes of complete binary tree,we start to
		// create the initial heap
		for (int i = data.length / 2; i > 0; i--)
			adjust(i, data.length - 1, data);
		for (int i = data.length - 1; i > 0; i--) {
			// swap root with last element, and adjust the rest n-1 nodes
			swap(1, i, data);
			adjust(1, i - 1, data);
		}
	}
    //same heaosort but used to process different priority
	public static void heapSort2(String[][] data) {
		// according to the attributes of complete binary tree,we start to
		// create the initial heap
		for (int i = data.length / 2; i > 0; i--)
			adjust2(i, data.length - 1, data);
		for (int i = data.length - 1; i > 0; i--) {
			// swap root with last element, and adjust the rest n-1 nodes
			swap(1, i, data);
			adjust2(1, i - 1, data);
		}
	}
	// swapping these two element
	public static void swap(int i, int j, String[][] data) {
		String temp[] = data[i];
		data[i] = data[j];
		data[j] = temp;
	}


	public static void adjust(int i, int n, String[][] data) {
		int child;
		for (; i <= n / 2;) {
			child = i * 2;
			if (child + 1 <= n && Compare(data[child], data[child + 1])) {
				// if the value of next child more than current child, so
				// current child is the bigger one
				child += 1;
			}
			if (Compare(data[i], data[child])) {
				swap(i, child, data);
				// after swapping, if the root is current child maybe doesn't
				// satisfy the rule of heap,
				// so start to adjust from current child
				i = child;
			} else
				break;
		}
	}
	public static void adjust2(int i, int n, String[][] data) {
		int child;
		for (; i <= n / 2;) {
			child = i * 2;
			if (child + 1 <= n && Compare2(data[child], data[child + 1])) {
				// if the value of next child more than current child, so
				// current child is the bigger one
				child += 1;
			}
			if (Compare2(data[i], data[child])) {
				swap(i, child, data);
				// after swapping, if the root is current child maybe doesn't
				// satisfy the rule of heap,
				// so start to adjust from current child
				i = child;
			} else
				break;
		}
	}

	// set the priority of processing,sorting the release time firstly
	// after release time sorted, then process the deadline and start-time
	public static boolean Compare(String[] task1, String[] task2) {
		if (Integer.parseInt(task1[1]) <= Integer.parseInt(task2[1])) {
			if (Integer.parseInt(task1[1]) < Integer.parseInt(task2[1])) {
				return true;
			} else if (Integer.parseInt(task1[2]) <= Integer.parseInt(task2[2])) {
				if (Integer.parseInt(task1[2]) < Integer.parseInt(task2[2])) {
					return true;
				} else if (Integer.parseInt(task1[3]) < Integer
						.parseInt(task2[3])) {
					return true;
				}
			}
		}
		return false;
	}
	// set the priority of processing,sorting the start time firstly
	// after start time sorted, then process the deadline and release time
	public static boolean Compare2(String[] task1, String[] task2) {
		if (Integer.parseInt(task1[3]) <= Integer.parseInt(task2[3])) {
			if (Integer.parseInt(task1[3]) < Integer.parseInt(task2[3])) {
				return true;
			} else if (Integer.parseInt(task1[2]) <= Integer.parseInt(task2[2])) {
				if (Integer.parseInt(task1[2]) < Integer.parseInt(task2[2])) {
					return true;
				} else if (Integer.parseInt(task1[1]) < Integer
						.parseInt(task2[1])) {
					return true;
				}
			}
		}
		return false;
	}

	 public static void main(String[] args) throws Exception{

		    TaskScheduler.scheduler("samplefile1.txt", "feasibleschedule1", 4);
		   /** There is a feasible schedule on 4 cores */      
		    TaskScheduler.scheduler("samplefile1.txt", "feasibleschedule2", 3);
		   /** There is no feasible schedule on 3 cores */
		    TaskScheduler.scheduler("samplefile2.txt", "feasibleschedule3", 5);
		   /** There is a feasible scheduler on 5 cores */ 
		    TaskScheduler.scheduler("samplefile2.txt", "feasibleschedule4", 4);
		   /** There is no feasible schedule on 4 cores */

		   /** The sample task sets are sorted. You can shuffle the tasks and test your program again */  

		  }

}
