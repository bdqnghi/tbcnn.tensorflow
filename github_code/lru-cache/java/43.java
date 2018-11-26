import java.util.Scanner;
import java.util.ArrayList;
import java.util.Arrays;

public class LRU {

	public static int search(int[] c, int str) {
		int result = -1;
		for (int i = 0; i < c.length; i++) {
			if (str == c[i]) {
				result = i;
				break;
			}
		}
		return result;
	}

	public static int max(int age[]) {
		int max = 0;
		int result = -1;
		for (int i = 0; i < age.length; i++) {
			if (max < age[i]) {
				max = age[i];
				result = i;
			}
		}
		return result;

	}

	public static void show(int[] cache) {
		for (int i = 0; i < cache.length; i++) {
			System.out.print(cache[i] + " ");
		}
		System.out.println();
	}

	public static void main(String[] args) {
		Scanner scan = new Scanner(System.in);
		String inputLine = scan.nextLine();
		String inputs[] = inputLine.split(" ");

		int size = 3;
		int k = 0;

		int[] cache = new int[size];
		int[] age = new int[size];
		int[] str = new int[inputs.length];
		
		for(int i=0;i<str.length;i++)
		{
			str[i]=Integer.parseInt(inputs[i]);
		}
		ArrayList<Integer> arr = new ArrayList<Integer>();
		Arrays.fill(age, 0);


		for (int i = 0; i < str.length; i++) {
			for (int j = 0; j < k; j++)
				age[j] += 1;
			if (size > k && search(cache, str[i]) == -1) {
				cache[k] = str[i];
			} else if (size > k && search(cache, str[i]) != -1) {
				cache[k] = str[i];
				age[search(cache, str[i])] = 0;
			} else if (size <= k && search(cache, str[i]) == -1) {
				if (size > 0) {
					arr.add(cache[max(age)]);
					cache[max(age)] = str[i];
					age[max(age)] = 0;
				}
			} else if (size <= k && search(cache, str[i]) != -1) {
				if (size > 0) {
					age[search(cache, str[i])] = 0;
				}
			}
			if (k < size)
				k++;
		}
		for (int a : arr)
			System.out.println(a);
	}
}