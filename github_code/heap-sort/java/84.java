package sort;

import java.io.BufferedInputStream;
import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.InputStreamReader;

public class HeapSort {
	private int heaplength = 0;

	public void heapTheNode(int[] heap, int i) {
		int left = 2 * i + 1;
		int right = 2 * i + 2;
		int large = i;
		if (left < heaplength && heap[left] > heap[i])
			large = left;
		if (right < heaplength && heap[right] > heap[large])
			large = right;
		if (large != i) {
			int temp = heap[large];
			heap[large] = heap[i];
			heap[i] = temp;
			heapTheNode(heap, large);
		}
	}

	public void buildTheHeap(int[] heap) {
		heaplength = heap.length;
		for (int i = (heap.length - 1) / 2 - 1; i >= 0; i--) {
			heapTheNode(heap, i);
		}
	}

	public void heapSort(int[] heap) {
		buildTheHeap(heap);
		for (int i = heap.length - 1; i > 0; i--) {
			int temp = heap[0];
			heap[0] = heap[i];
			heap[i] = temp;
			heaplength--;
			heapTheNode(heap, 0);
		}
	}

	public static void main(String[] args) throws Exception {
		HeapSort heapSort = new HeapSort();
		int [] array = {100,60,70,50,32,65};
		heapSort.heapSort(array);
		for(int temp:array){
			System.out.print(temp+"\t");
		}

		
		
		
//    FileInputStream fis=null;
//	fis = new FileInputStream("D://a.txt");
//	BufferedInputStream bis=new BufferedInputStream(fis);
//	InputStreamReader isr=new InputStreamReader(bis);
//	BufferedReader br=new BufferedReader(isr);
//
//	String temp=null;
//	int [] array =new int [500000];
//	int s=0;
//	while((temp=br.readLine())!=null){
//		array[s]=Integer.parseInt(temp);
//		s++;
//	}
//	br.close();
//	isr.close();
//	bis.close();
//	fis.close();
//
//	HeapSort heapSort = new HeapSort();
//	long time=System.nanoTime();
//	heapSort.heapSort(array);
//	long time1=System.nanoTime();
//	System.out.println(time+"    "+time1+"\t\t"+(time1-time));
//	for(int te:array){
//		System.out.println(te+"\t");
//	}
	}
}
