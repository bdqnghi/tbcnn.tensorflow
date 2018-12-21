
package com.collection.sort.bubble;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;


public class Bubble
{

	
	public static void main(String[] args)
	{
		Integer[] arr =
		{ 3, 7, 8, 2, 9, 1, 4, 6, 5 };

		

		List<String> list = new ArrayList<String>();
		list.add("sfokp");
		list.add("adsa");
		list.add("dsada");
		list.add("mgiuy");
		list.add("xvcbvc");
		list.add("pkghsasa");
		Collections.sort(list, new StringComparator());
		System.out.println(list.toString());

		String[] strs =
		{ "sfokp", "adsa", "dsada", "mgiuy", "xvcbvc", "pkghsasa" };

		Utils.sort(strs, new StringComparator());

	}

	public static void sort(int[] arr)
	{
		boolean sorted;
		int len = arr.length;
		for (int i = 1; i < len - 1; i++)
		{
			sorted = true;
			for (int j = 0; j < len - 1; j++)
			{
				if (arr[j] > arr[j + 1])
				{
					int tmp = arr[j];
					arr[j] = arr[j + 1];
					arr[j + 1] = tmp;
					sorted = false;
				}
			}
			if (sorted)
			{
				break;
			}
			System.out.println(Arrays.toString(arr));
		}
	}
}
