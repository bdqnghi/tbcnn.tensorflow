package algo;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.util.ArrayList;
import java.util.StringTokenizer;

public class Main {
	public static void main(String args[]) throws IOException {
		new Task().run();
	}
	
	static class Task {
		private int N;
		private int[] arr;
		
		private StringTokenizer st = null;
		private BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		private BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
		private StringTokenizer getStringTokenizer() throws IOException {
			return new StringTokenizer(br.readLine(), " ");
		}
		
		private void input() throws IOException {
			st = getStringTokenizer();
			N = Integer.parseInt(st.nextToken());
			arr = new int[N];
			
			for(int i=0; i<N; i++) {
				st = getStringTokenizer();
				arr[i] = Integer.parseInt(st.nextToken());
			}
		}
		
		private void merge(int[] arr, int left, int mid, int right) {
			int lIdx = left;
			int rIdx = mid+1;
			int idx = left;
			int[] sortArr = new int[arr.length];
			
			while(lIdx <= mid && rIdx <= right) {
				while(lIdx <= mid && arr[lIdx] <= arr[rIdx]) {
					sortArr[idx++] = arr[lIdx++]; 
				}
				
				while(rIdx <= right && arr[rIdx] < arr[lIdx]) {
					sortArr[idx++] = arr[rIdx++];
				}
			}
			
			if(lIdx <= mid) {
				for(int i=lIdx; i<=mid; i++) {
					sortArr[idx++] = arr[i];
				}
			} else {
				for(int i=rIdx; i<=right; i++) {
					sortArr[idx++] = arr[i]; 
				}
			}
			
			for(int i=left; i<=right; i++) {
				arr[i] = sortArr[i];
			}
		}
		
		private void mergeSort(int[] arr, int left, int right) {
			if(left < right) {
				int mid = (left+right)/2;
				mergeSort(arr, left, mid);
				mergeSort(arr, mid+1, right);
				merge(arr, left, mid, right);
			}
		}
		
		public void run() throws IOException {
			input();
			mergeSort(arr, 0, arr.length-1);
			print();
			close();
		}
		
		private void print() throws IOException {
			for(int i=0; i<N; i++) {
				bw.write(String.valueOf(arr[i])+"\n");
			}
		}
		
		private void close() throws IOException { 
			bw.close();
			br.close();
		}
	}
}
