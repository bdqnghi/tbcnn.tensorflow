package lineartimesort;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Random;

public class Bucketsort {
	
	public double[] bucketsort(double[] arr) {
		int n=arr.length;
		double[] A =new double[n];
		ArrayList<Double>[] B=new ArrayList[n];
		for (int i = 0; i < n; i++) {
			B[i]=new ArrayList<Double>();
		}
		for (int i = 0; i < n; i++) {
			B[(int) Math.floor(n*arr[i])].add(arr[i]);
		}
		int j=0;
		for (int i = 0; i < n; i++) {
			Collections.sort(B[i]);
			for (int k = 0; k < B[i].size(); k++,j++) {
				A[j]=B[i].get(k);
			}
		}
		return A;
		
	}
	
	public static void main(String[] args) {
		
		double[] arr=new double[10000];
		double[] A=new double[arr.length];
		for (int i = 0; i < arr.length; i++) {
			Random random=new Random();
			arr[i]=random.nextDouble();
		}
		for (int i = 0; i < arr.length; i++) {
			System.out.printf("%.4f ", arr[i]);
		}
		System.out.println();
		Bucketsort bucketsort=new Bucketsort();
		A=bucketsort.bucketsort(arr);
		for (int i = 0; i < A.length; i++) {
			System.out.printf("%.4f ", A[i]);
		}
	}

}
