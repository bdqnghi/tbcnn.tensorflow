package sorting;

import static sorting.Example.exch;
import static sorting.Example.isSorted;
import static sorting.Example.less;
import static sorting.Example.show;

import java.io.BufferedInputStream;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;
@SuppressWarnings("rawtypes")
public class Shell implements Sort {
	static int count;
	@Override
	public void sort(Comparable[] a) {
		int N = a.length;
		int h = 1;
		while (h < N / 3)
			h = h * 3 + 1;
		while (h >= 1) {
			for (int i = 0; i < N; i++) {
				count++;
				for (int j = i; j >= h && less(a[j], a[j - h]); j -= h) {
					exch(a, j, j - h);
				}
			}
			h /= 3;
		}
		System.out.println(count / N);
	}

	public static void main(String[] args) {
		Scanner scan = new Scanner(new BufferedInputStream(System.in), "UTF-8");
		List<String> target = new ArrayList<>();
		while (scan.hasNext())
			target.add(scan.next());
		String[] a = new String[target.size()];
		target.toArray(a);
		Sort sort = new Selection();
		sort.sort(a);
		System.out.println(isSorted(a));
		System.out.println(sort.getClass().getSimpleName());
		show(a);
		scan.close();
	}

}
