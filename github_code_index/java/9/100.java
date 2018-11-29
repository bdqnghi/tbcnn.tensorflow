package DailyProg;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.util.ArrayList;

public class heapsort {

	public static final int SIZEA = 32;
	public static final int SIZEB = 1024;
	
	
	public static void main(String args[]){
	
		ArrayList<Integer> first = new ArrayList<Integer>(SIZEA);
		ArrayList<Integer> second = new ArrayList<Integer>(SIZEB);
		
		for(int i =0; i < SIZEB; i++){
			if(i < SIZEA) first.add((int)(Math.random() * SIZEB*10));
			second.add((int)(Math.random() * SIZEB*10));
		}
	
		heapify(first);
		heapify(second);
		
		System.out.println(second.size());
		
		//printa(first);
		
		first.addAll(second);
		System.out.println(first.size());
		
		for(int i = SIZEA; i >= 0; i--){
			siftd(first, i);
		}
		
		System.out.println(first.size());
		
		ArrayList<Integer> temp = new ArrayList<Integer>();
		int stopper = first.size();
		
		for(int i = 0; i < stopper; i++){
			temp.add(getmin(first));
		}
		
		System.out.println(temp.size());
		if(verify(temp)) System.out.println("True");
		else System.out.println("FALSE");
		
		printa(temp);
		
		
	}
	
	public static int getmin(ArrayList<Integer> a){
		int retVal = a.get(0);
		a.set(0, a.get(a.size()-1));
		a.remove(a.size()-1);
		if(!a.isEmpty()) siftd(a,0);
		
		return retVal;
	}
	
	public static boolean verify(ArrayList<Integer> a){
		
		for(int i = 0; i < a.size()-1; i++){
			if(a.get(i) > a.get(i+1)) return false;
		}
		return true;
		
	}
	public static void printa(ArrayList<Integer> a){
		 try{
			  // Create file 
			  FileWriter fstream = new FileWriter("C:\\Users\\Kevin\\My Documents\\out.txt");
			  BufferedWriter out = new BufferedWriter(fstream);
			  
			  if(verify(a)) out.write("True");
			  for(int i = 0; i < a.size(); i++){
					out.write(i +": " +a.get(i)+"\r\n");
				}
			  
			  
			  //Close the output stream
			  out.close();
			  }catch (Exception e){//Catch exception if any
			  System.err.println("Error: " + e.getMessage());
			  }
		
		
	}
	
	public static void heapify(ArrayList<Integer> a){
		for(int i = a.size()/2; i >=0 ; i--){
			siftd(a,i);
		}
		
	}
	
	public static void siftd(ArrayList<Integer> a, int i){
		int left = i*2;
		int right = 2*i +1;
		int smallest = i;
		
		if(left < a.size() && a.get(left) < a.get(i) ){
			smallest = left;
		}
		if(right < a.size() && a.get(right) < a.get(smallest) ){
			smallest = right;
		}
		if(smallest != i){
			int temp = a.get(i);
			a.set(i,a.get(smallest));
			a.set(smallest, temp);
			siftd(a,smallest);
		}
	}
		
}
