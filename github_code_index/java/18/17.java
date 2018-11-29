import java.util.*;

public class _23 {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Scanner input = new Scanner(System.in);
		
		String type = input.nextLine();
		int sort = input.nextInt();
		String[] Split = type.split(" ");
		ArrayList<Integer> num = new ArrayList<Integer>();
		
		for(int i = 0; i < Split.length; i++) {
			while(Integer.parseInt(Split[i]) != -999) {
				num.add(Integer.parseInt(Split[i]));
				break;
			}
		}
		
		ArrayList<Integer> bubbleSort = new ArrayList<Integer>(num);
		ArrayList<Integer> insertionSort = new ArrayList<Integer>(num);
		ArrayList<Integer> selectionSort = new ArrayList<Integer>(num);
		int bubbleCount = 0;
		int insertionCount = 0;
		int selectionCount = 0;
		
		if(sort == 0) {
			for(int h = bubbleSort.size() - 1; h > 0; h--) {
				for(int i = bubbleSort.size() - 2; i >= 0; i--) {
					if(bubbleSort.get(i) > bubbleSort.get(i+1)) {
						int temp = bubbleSort.get(i+1);
						bubbleSort.set(i+1, bubbleSort.get(i));
						bubbleSort.set(i, temp);
						bubbleCount++;
					}
				}
			}

			for(int j = 1; j < insertionSort.size(); j++) {
				if(insertionSort.get(j) < insertionSort.get(j-1)) {
					int temp = insertionSort.get(j);
					for(int m = j - 1; m >= 0; m--) {
						if(temp < insertionSort.get(m)) {
							insertionSort.set(m + 1, insertionSort.get(m));
							insertionSort.set(m, temp);
							insertionCount++;
						}
					}
				}
			}
			for(int n = 0; n < selectionSort.size(); n++) {
				int min = selectionSort.get(n);
				int position = 0;
				for(int m = n; m < selectionSort.size(); m++) {
					if(min > selectionSort.get(m)) {
						min = selectionSort.get(m);
						position = m;
					}
				}
				if(selectionSort.get(n) > min) {
					int temp = min;
					selectionSort.set(position, selectionSort.get(n));
					selectionSort.set(n, temp);
					selectionCount++;
				}
			}
			
			for(int z = 0; z < selectionSort.size(); z++) {
				System.out.print(selectionSort.get(z) + " ");
			}
			System.out.println();
			System.out.println("Bubble Sort change times = " + bubbleCount);
			System.out.println("Insertion Sort change times = " + insertionCount);
			System.out.println("Selection Sort change times = " + selectionCount);
		}

		if(sort == 1) {
			for(int h = bubbleSort.size() - 1; h > 0; h--) {
				for(int i = bubbleSort.size() - 2; i >= 0; i--) {
					if(bubbleSort.get(i) < bubbleSort.get(i+1)) {
						int temp = bubbleSort.get(i+1);
						bubbleSort.set(i+1, bubbleSort.get(i));
						bubbleSort.set(i, temp);
						bubbleCount++;
					}
				}
			}

			for(int j = 1; j < insertionSort.size(); j++) {
				if(insertionSort.get(j) > insertionSort.get(j-1)) {
					int temp = insertionSort.get(j);
					for(int m = j - 1; m >= 0; m--) {
						if(temp > insertionSort.get(m)) {
							insertionSort.set(m + 1, insertionSort.get(m));
							insertionSort.set(m, temp);
							insertionCount++;
						}
					}
				}
			}
			for(int n = 0; n < selectionSort.size(); n++) {
				int max = selectionSort.get(n);
				int position = 0;
				for(int m = n; m < selectionSort.size(); m++) {
					if(max < selectionSort.get(m)) {
						max = selectionSort.get(m);
						position = m;
					}
				}
				if(selectionSort.get(n) < max) {
					int temp = max;
					selectionSort.set(position, selectionSort.get(n));
					selectionSort.set(n, temp);
					selectionCount++;
				}
			}
			
			for(int z = 0; z < selectionSort.size(); z++) {
				System.out.print(selectionSort.get(z) + " ");
			}
			System.out.println();
			System.out.println("Bubble Sort change times = " + bubbleCount);
			System.out.println("Insertion Sort change times = " + insertionCount);
			System.out.println("Selection Sort change times = " + selectionCount);
		}		
	}
}