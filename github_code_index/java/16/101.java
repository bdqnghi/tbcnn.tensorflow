package quicksort_multithreaded;
import java.util.*;

public class QuickSort {

	int size;
	int[] tab;
	int index_first = 0;
	int index_last;
	int pivot_first;
	int pivot_second;
	int pivot_third;
	FirstThread First;
	SecondThread Second;
	AnotherThread Third;
	AnotherThread Fourth;
	
	QuickSort(int size, int tab[], boolean print){
		
		this.size = size;
		this.index_last = size - 1;
		this.tab = tab;

		this.First = new FirstThread("Pierwszy!");
		try{
			System.out.println("Oczekiwanie W�tku g��wnego na zako�czenie w�tk�w!");
			this.First.First.join();
		}catch (InterruptedException e){
			
		}
		System.out.println(">>Wszystkie w�tki zosta�y zako�czone!");
		
		if(print){
			System.out.println("Prezentowanie macierzy!");
			for(int i = 0;i < size; i++){
				System.out.println(this.tab[i]);
			}
		}	
	}
	
	private class FirstThread implements Runnable{
		
		Thread First;
		String name;
		FirstThread(String threadname){
			name = threadname;
			First = new Thread(this,name);
			System.out.println("<NEW>Konstruktor W�tku: " + First);
			First.start();
		}
		@Override
		public void run() {
			System.out.println("<BEGIN>Rozpocz�cie W�tku: " + First);
			
			QuickSort.this.pivot_second = QuickSort.this.sort_once(QuickSort.this.index_first, QuickSort.this.index_last);
						
			QuickSort.this.Second = new QuickSort.SecondThread("W�tek!");
				
			QuickSort.this.pivot_first = QuickSort.this.sort_once(QuickSort.this.index_first, QuickSort.this.pivot_second);
			
			QuickSort.this.Third = new QuickSort.AnotherThread("Trzeci!", QuickSort.this.pivot_first + 1, QuickSort.this.pivot_second);
			
			QuickSort.this.sort_till_the_end(QuickSort.this.index_first, QuickSort.this.pivot_first);
			
			try{
				if(QuickSort.this.Second.Second.isAlive())
					QuickSort.this.Second.Second.join();
				if(QuickSort.this.Third.Another.isAlive())
					QuickSort.this.Third.Another.join();
				if(QuickSort.this.Fourth.Another.isAlive())
					QuickSort.this.Fourth.Another.join();
				
			}catch (InterruptedException e){
				
			}	
			System.out.println("<END>Zako�czenie W�tku: " + First);
		}
	}
	private class SecondThread implements Runnable{
		
		Thread Second;
		String name;
		SecondThread(String threadname){
			name = threadname;
			Second = new Thread(this,name);
			System.out.println("<NEW>Konstruktor W�tku: " + Second);
			Second.start();
		}
		@Override
		public void run() {
			System.out.println("<BEGIN>Rozpocz�cie W�tku: " + Second);
			
			QuickSort.this.pivot_third = QuickSort.this.sort_once(QuickSort.this.pivot_second + 1, QuickSort.this.index_last);
			
			QuickSort.this.Fourth = new QuickSort.AnotherThread("Czwarty!", QuickSort.this.pivot_third + 1, QuickSort.this.index_last);
			
			QuickSort.this.sort_till_the_end(QuickSort.this.pivot_second + 1, QuickSort.this.pivot_third);
			
			System.out.println("<END>Zako�czenie W�tku: " + Second);
		}	
	}
	private class AnotherThread implements Runnable{
		
		Thread Another;
		String name;
		int from;
		int to;
		AnotherThread(String threadname, int from, int to){
			name = threadname;
			this.from = from;
			this.to = to;
			Another = new Thread(this,name);
			System.out.println("<NEW>Konstruktor W�tku: " + Another);
			Another.start();
		}
		@Override
		public void run() {
			System.out.println("<BEGIN>Rozpocz�cie W�tku: " + Another);
			
			QuickSort.this.sort_till_the_end(from, to);
			
			System.out.println("<END>Zako�czenie W�tku: " + Another);
		}
	}
	public void swap(int i, int j){
		int tmp = this.tab[i];
		this.tab[i] = this.tab[j];
		this.tab[j] = tmp;
	}
	
	public int sort_once(int left, int right){
		
		int i = left-1;
		int j = right+1;
		int pivot_index = (int)(Math.round((left+right)/2));
		int pivot_value = this.tab[pivot_index];

		while(true){
			i=i+1;
			while(pivot_value>this.tab[i]){
				i=i+1;
			}
			j=j-1;
			while(pivot_value<this.tab[j]){
				j=j-1;
			}
			if(i >= j){
				break;
			}
			this.swap(i, j);
		}
		return j;
	}
	public void sort_till_the_end(int left, int right){
		
		if( left < right){
			int i = left-1;
			int j = right+1;
			int pivot_index = (int)(Math.round((left+right)/2));
			int pivot_value = this.tab[pivot_index];
			
			while(i<j){
				i=i+1;
				while(pivot_value>this.tab[i]){
					i=i+1;
				}
				j=j-1;
				while(pivot_value<this.tab[j]){
					j=j-1;
				}
				if(i >= j){
					break;
				}else{
					this.swap(i, j);
				}
			}
			this.sort_till_the_end(left, j);
			this.sort_till_the_end(j+1, right);
		}
	}
}