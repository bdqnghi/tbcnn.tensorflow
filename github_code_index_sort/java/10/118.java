import java.util.List;
import java.util.LinkedList;

public class bucketsort {
	/*
	 * bucket sort
	 */

	public void bucketSort(int[] array) {
		List<Integer> list[] = (LinkedList<Integer>[]) new LinkedList[10];
		for(int i = 0; i < list.length; i++) {
			list[i] = new LinkedList<Integer> ();
		}
		for(int i = 0; i < array.length; i++) {
			int count = array[i] / 10;
			insert(list[count], array[i]);
		}
		int count = 0;
		for(int i = 0; i < list.length; i++) {
			for(int j = 0; j < list[i].size(); j++) {
				array[count++] = list[i].get(j);
			}
		}
	}
	public void insert(List<Integer> list, int num) {
		for(int i = list.size() - 1; i >= 0; i--) {
			if(list.get(i) > num) {
				i--;
			}
			else {
				list.add(i + 1, num);
				return;
			}
		}
		list.add(0, num);
	}
	public static void main(String[] args) {
		int[] array = {1,2,2,2,3, 10, 3, 40, 20, 50, 80, 70,12, 16, 22, 30, 35, 39, 42, 45, 48, 50, 53, 55, 56};
		bucketsort ss = new bucketsort();
		ss.bucketSort(array);
		for(int i : array)
			System.out.println(i);
	}
}