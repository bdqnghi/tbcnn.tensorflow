package algorithm;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;
import java.util.Stack;

public class LRU {
	public static void main(String[] args) throws FileNotFoundException {

		Scanner sc = new Scanner(new FileInputStream("src/algorithm/LRU.txt"));

		// Scanner sc = new Scanner(System.in);

		int sizeOfCache = sc.nextInt();
		sc.nextLine();
		Stack<String> stack = new Stack<>();
		String[] cache = new String[sizeOfCache];
		stack.push("");
		stack.push("");
		stack.push("");
		ArrayList<String> inputList = new ArrayList<>();
		int result = 0;

		while (sc.hasNext()) {
			inputList.add(sc.next());
		}

		for (int i = 0; i < inputList.size(); i++) {
			int time = 5;
			int index = 2;
			for (int j = 2; j > -1; j--) {
				String tempString = stack.pop();
				if (tempString.equals(inputList.get(i))) {
					time = 1;
					continue;
				}
				cache[index] = tempString;
				index--;
			} // forCache
			result += time;

			stack.push(cache[2]);
			stack.push(cache[1]);
			stack.push(inputList.get(i));

		}

		System.out.println(result);

	}// main

}// class