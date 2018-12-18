
package com.anuragkapur.sorting;


public class InsertionSort {

    public void sort(int a[]) {

        if(a == null || a.length <= 1) {
            return;
        }

        insertNumberAtIndexInSortedArray(a, 1);
    }

    private void insertNumberAtIndexInSortedArray(int a[], int index) {

        if (index == a.length) {
            return;
        }

        int number = a[index];
        int i;
        for (i=index-1; i >= 0; i--) {
            if (number < a[i]) {
                a[i+1] = a[i];
            } else {
                break;
            }
        }

        a[i+1] = number;

        insertNumberAtIndexInSortedArray(a, index+1);
    }

	
	public static void main(String[] args) {
		
		
		int a[] = {5,1,4,3,8,6,9,10,7,2};

        
		for (int i = 1; i < a.length; i++) {
			int key = a[i];
			int j = i - 1;
			while(j >= 0 && a[j] > key) {
				a[j + 1] = a[j];
				j --;
			}
			a[j + 1] = key;
		}
		
		
		for (int i = 0; i < a.length; i++) {
			System.out.println(a[i]);
		}
	}

}
