package testing;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;
import java.util.Scanner;

public class TowerOfHanoi {
	
	
//	public static void move(int n,  String from, String to, String using) {
//		if(n == 1) {
//			System.out.println("move disk from " + from + " to " + to);
//		}
//		else {
//			move(n-1, from , using, to );
//			move(1, from, to, using);
//			move(n-1, using, to , from);
//			
//		}
//	}
	
	public static void move(int n, String from, String to, String using) {
		//base case
		if( n==1 ) {
			System.out.println("move disk from " + from + " to "+ to);
		}else {
			//recursive part:    // A = from, B = using, C = to
			move( n-1, from, using, to); //eventually from A(first/from) to B (middle/using) with the help of C (last/to)
			move( 1, from, to, using ); // then 1 left in A, so move from A to 
			move( n-1, using, to, from); // the at last from B(using) to C(to) using A(from)
		}
	}
	
	//==========^^^^^^^^^^^^^ Tower of Hanoi ^^^^^^^^^^^=====================
	
	// EASIER:::
//	public static void printIt(String S, int n) {
//		for ( int i = 0; i < n; i++) { //starting from 0 so <n b/c if not 0----n+1 copy will be printed
//			System.out.println(S);
//		}
//		
//	}
	
	public static void printIt( String S, int n) {
		for( int i =0 ; i < n; i++) {
			System.out.println(S);
		}
	}
	//=============== EASIER:::^^^^^^^^^^^^^^^^^^^^
	
//	public static void printItToo(String s, int n) {
//		if(n == 0) {
//			return; // THIS IS FOR VOID RETURN.
//		}
//		else {
//			System.out.println(s); //Do it ONCE 
//			printItToo(s, n-1);  //n-1 more
//		}
//	}
	public static void printItToo( String S, int n) {
		// base case
		if( n == 0 ) {
			return;
			//recursive stuff
		}else {
			System.out.println(S);
			printItToo( S, n-1);
		}
		
	}
	
	
	
	
	// ::::::::FIBONACCI::::::::
	public static int fibonacci(int n) {
		//base case
		if( n == 0 ) {
			return 0;
		}else if( n == 1 ) {
			return 1;
		// recursion step/definition
		}else {
			int f = fibonacci( n-1 )+ fibonacci( n-2 );
			return f;
		}
		
	}
	
	//=============MULITYIPLIER==============	
	public static int multiplier(int m, int n) {
//		if( m == 1 ) {
//			return n;
////		
////		}
////		if( m > 0) {
//		}else{
//			return m + multiplier(m-1, n);
////		}else{
////			return 0;
////	    }
//		}
		if ( m == 1) {
			return n;
		}else {
			return n + multiplier( m- 1, n ); 
		}
	}
	
	//=============COUNT ZEROS==============	
	public static int countZeros(long n) {
		// Base Cases:
		if ( n == 0) {
			return 0;
			
		}else if( n != 0 && n < 10L ){
			return 1;
		}
		
		boolean ifItsZero = ( n % 10L == 0 );
		
		if (ifItsZero == true) {
			return 1 + countZeros(n / 10L);
		}
		
		else {
			return 0 + countZeros( n / 10L );
		}
		
//		// Base Case:
//		if ( n == 0) {
//			return 0;
//			
//		}else if ( n!= 0 && n <= 10L) {
//			return 1;
//		}
//		
//		if ( n % 10L == 0) {
//			return 1 + countZeros( n / 10L);
//		}else {
//			countZeros( n / 10L);
//		}
	}
	
	
	//=============POWER OF TEN============
	public static double powerOfTen(int n) {
//		//base case
//		if( n == 0) {
//			return 1.0;
//			
//		//recursive case
//		}if (n > 0) {
//			return 10.0 * powerOfTen(n-1);
//		}else{
//			return 1.0 / powerOfTen(-n);
//		}
		
		//base case
		if ( n == 0) {
			return 1.0;
		}else if ( n > 0) {
			return 10 * powerOfTen( n-1 );
		
		}else {
			return 1.0 /  powerOfTen( -n); // -n so -(-input) == positive input
		}
	}
	
	public static double powerOfTenFaster(int n) {
		// base case
		if ( n < 0 ) {
			return 1.0 / powerOfTenFaster(-n);
			
		}else if( n == 0) {
			return 1.0;
			
		// if even	
		}else if ( n % 2 == 0) {
				return powerOfTenFaster(n/2) * powerOfTenFaster(n/2);
		}else{
				return 10.0 * powerOfTenFaster(n-1);
			}
	}
	
	public static String removeRepeats(String str) {
		
		int n = str.length();
		// base case:
		if ( n == 1) {
			return str;
		//recursive step:
		}else if( str.charAt(0) != str.charAt(1) ){
			return str.charAt(0) + removeRepeats( str.substring(1, n));
		}else {
			return removeRepeats(str.substring(1, n));
		}

	}	
	
	
	public static int binaryToInt( String b ) {
		//base case
		int n = b.length();
		if( n == 0) {
			if( b == "1" ) {
				return 1;
			}else {
				return 0;
			}
		}else if ( b.charAt(0) == '1') {
			
			return (int) (1 * Math.pow(2, n-1) +  binaryToInt( b.substring(1, n) ));
		}else {
			return 0 + binaryToInt(b.substring(1, n) );
		}
	}
	
	
	public static String intToBinary( int value ) {
		
		
		if( value == 0){
			return "0";
		}else if( value == 1) {
			return "1";
			
		}else {
			
		
//			
//		}else {
			return intToBinary(value /2) + value % 2;
		
		
		}
		
	}
	
//	public static boolean almostSeq(int[] sequence) {
////		return false;
//		for ( int i = 0; i < sequence.length; i++) {
//			sequence
//		}
//		return false;
//	}
	
	public static int dat( int n) {
		if ( n == 1) {
			return 1;
		}else if ( n == 2) {
			return 2;
		}else if ( n == 3) {
			return 5;
		}else {
			return dat(n - 1) + dat(n - 2) + dat(n -3);
		}
//		if ( n == 1) {
//			System.out.print(n+ " ");
//			return 1;
//		}else {
//		
//		int last = n * 2 + dat(n - 1);
//		System.out.print(n+ " ");
//		return last;
//		}
	}
	
	public static void datdisser(int n) {
		
		if( n == 0) {
			return;
		}
		int m = TowerOfHanoi.dat(n);
		
		datdisser(n - 1);
		System.out.print(m+ " ");
	}
	
	
	public static int datdat( int n) {
		if ( n == 1) {
			System.out.print("1" + " " );
			return 1;
		}else if( n == 2) {
			System.out.print("1" + " " + "2" + " " );
			return 2;
		}else if( n == 3) {
			System.out.print("1" + " " + "2" + " " + "5" + " ");
			
			return 5;
		}else {
		
		int last = n * 2 + dat(n - 1);
		System.out.print(n+ " ");
		return last;
		}
	}
	
	public static int letterCounter(String s) {
		int k;

		if (s.isEmpty()) {
			return 0;
		}if (s.endsWith(" ") || s.endsWith(".") || s.endsWith(",")  ) {
			k = 0;
			return k = k + letterCounter(s.substring(0, s.length()-1));
		}else{
			k = 1;
			return k = k + letterCounter(s.substring(0, s.length()-1));
		}
		
	}
	
	public static int wordCounter(String s) {
		
		if (s.isEmpty()) {
			return 0;
		}
		String[] ans = s.split("\\s+");
		return ans.length;
	}
	
	
	public static int spaceCounter(String s) {
		int k;

		if (s.isEmpty()) {
			return 0;
		}if (s.endsWith(" ")) {
			k = 1;
			return k = k + spaceCounter(s.substring(0, s.length()-1));
		}else{
			k = 0;
			return k = k + spaceCounter(s.substring(0, s.length()-1));
		}
		
	}
	
	public static void Counter(String s) {
		
		int L = TowerOfHanoi.letterCounter(s) ;
		int W = TowerOfHanoi.wordCounter(s);
		int S = TowerOfHanoi.spaceCounter(s);
		
		if ( L == 0) {
			System.out.println("\""+ s +"\" "+ "has no letters.");
		}else if (L == 1) {
			System.out.println("\""+ s +"\" "+ "has "+ L + " letter.");
		}else if ( L > 1) {
			System.out.println("\""+ s +"\" "+ "has "+ L + " letters.");
		}
		
		if ( W == 0) {
			System.out.println("\""+ s +"\" "+ "has no words.");
		}else if (W == 1) {
			System.out.println("\""+ s +"\" "+ "has "+ W + " word.");
		}else if ( W > 1) {
			System.out.println("\""+ s +"\" "+ "has "+ W + " words.");
		}
		
		if ( S == 0) {
			System.out.println("\""+ s +"\" "+ "has no spaces.");
		}else if (S == 1) {
			System.out.println("\""+ s +"\" "+ "has "+ S + " space.");
		}else if ( S > 1) {
			System.out.println("\""+ s +"\" "+ "has "+ S + " spaces.");

		}
		
		
		
	}
	
	
	
	
	public static boolean palind(String s ) {
		if (s.isEmpty() || s.length() == 1) {
			return true;
		}else if (s.charAt(0) != s.charAt(s.length()-1)) {
			return false;
		}
		String A = s.substring(0, s.length()-1);
		String B = A.substring(1,A.length());
		return true && palind(B);
		
	}
	
	
    public static int[] solve(int a0, int a1, int a2, int b0, int b1, int b2) {
    	
        /*
         * Write your code here.
         */
    		int[] arr;
    		arr = new int[2];
    		int a = 0;
    		int b = 0;
    		if( a0 > b0) {
    			a++;
    			arr[0] = a;
    		}if( a0 < b0) {
    			b++;
    			arr[1] = b;
    		}if( a1 > b1) {
    			a++;
    			arr[0] = a;
    		}if( a1 < b1) {
    			b++;
    			arr[1] = b;
    		}if( a2 > b2) {
    			a++;
    			arr[0] = a;
    		}if( a2 < b2) {
    			b++;
    			arr[1] = b;
    		}
    		return arr;
//    		arr[0] = 1;
//    		arr[1] = 2;
//    		if( a0 == b0 ) {
//    			
//    		}
    }
    
    public static int diagonalDifference(int[][] a) {
        /*
         * Write your code here.
         */
    		int leftDiag = 0;
    		int rightDiag = 0;
        for(int i =0 ; i< a.length; i++) {
        		leftDiag = leftDiag + a[i][i];
        		rightDiag = rightDiag + a[i][a.length - 1 - i];
        }
        return Math.abs(leftDiag - rightDiag);
//        return rightDiag;
    }
    
    public static void plusMinus(int[] arr) {
        /*
         * Write your code here.
         */
    		double pos = 0;
    		double neg = 0;
    		double zer = 0;
    		for (int i = 0; i< arr.length ; i++) {
    			if (arr[i] > 0) {
    				pos++;
    			}else if( arr[i] < 0) {
    				neg++;
    			}else {
    				zer++;
    			}
    		}
    		System.out.println(pos/arr.length);
    		System.out.println(neg/arr.length);
    		System.out.println(zer/arr.length);
    }
    
    public static void staircase(int n) {
        /*
         * Write your code here.
         */
        for (int i = 0; i < n; i++){
        	
        		for (int k = 0 ; k < n-1-i ; k++) {
        			System.out.print(" ");
        		}
            for(int j = 0 ; j < i; j++){
                System.out.print("#");
            }System.out.println("#");
        }
//    		if(n == 0) {
//    			return;
//    		}
//    		for(int k = 0 ; k < n-1; k++) {
//    			System.out.print(" ");
//    		}for(int i = 0; i < n; i++ ) {
//    			System.out.
//    		}
        

    }
    
    public static void miniMaxSum(int[] arr) {
        /*
         * Write your code here.
         */
    		double sum = 0;
    		double a = 0;
    		double b = 0;
    		double max = 0;
    		double min = 0;
    		for(int i=0; i<arr.length; i ++) {
    			sum = sum + arr[i];
    		}
    		for(int j=0; j<arr.length;j++) {
    			a = sum - arr[j];
    			b = sum - arr[j+1];
    			max = Math.max( max, a);
    			
    			
    		}
        
    		System.out.println((int)min+ " "+ (int)max);
    }
    
    public static int birthdayCakeCandles(int n, int[] ar) {
        /*
         * Write your code here.
         */
    		int max = ar[0];
    		int counter =0;
    		for (int i = 0; i < n; i++) {
    			max = Math.max(ar[i], max);
    		}
    		for( int j = 0; j < n; j++) {
    			if ( ar[j]== max) {
    				counter++;
    			}
    		}
    		return counter;

    }
//    public static String timeConversion(String s) {
//        /*
//         * Write your code here.
//         */
//    		String time = s;
//    		if( time.contains("PM")) {
//    			time = time.replace("PM", "");
//    			String[] hms = time.split(":");
//    			if(hms[0].equals("12") ) {
//    				return time;
//    			}else {
//    				int hour = Integer.parseInt(hms[0]);
//    				hour = hour + 12;
//    				time = hour + ":"+ hms[1] +":"+ hms[2];
//    				
//    			}
//    			
//    		}else if( time.contains("AM")) {
//    			time = time.replace("AM", "");
//    			String[] hms = time.split(":");
//    			if(hms[0].equals("12") ) {
//    				hms[0] = "00";
//    				time = hms[0] + ":"+ hms[1] +":"+ hms[2];
//    				
//    			}
//    			return time;
//    		}
////        String result = s;
////        if (s.substring( s.length()-2 , s.length()).equals("PM")) {
////		int disboi = Integer.parseInt(s.substring(0,2));
////		
////		result = disboi + 12 + s.substring(2, s.length()-2);
////            return result;
////        	}else {
////		return result.substring(0, s.length()-2);
////        	}
//    }
    
    public static int[] gradingStudents(int[] grades) {
        /*
         * Write your code here.
         */
    		for(int i = 0 ; i < grades.length; i++) {
    			if(grades[i] >= 38) {
    				int grd = grades[i] % 10;
    				int grdTen = grades[i] / 10;
    				if ( grd == 5 || grd == 4 || grd == 3) {
    					grades[i] = grdTen*10 + 5;// 5 , 4 , 3   and 0 , 9 ,8
    				}else if (grd == 0 || grd == 9 || grd == 8) {
    					grades[i] = grdTen*10 + 10;
    				}
    			}
    			
    		}return grades;
        
    }
    
	

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		TowerOfHanoi.move(3, "from A", "to C", "using B");
		TowerOfHanoi.printIt("DOOL", 2);
		TowerOfHanoi.printItToo("DAB", 3);
		System.out.println(TowerOfHanoi.multiplier(3, 9));
		System.out.println(TowerOfHanoi.fibonacci(2));
		System.out.println(TowerOfHanoi.countZeros(100211032400L));
		System.out.println(TowerOfHanoi.powerOfTen(-2));
		System.out.println(TowerOfHanoi.powerOfTenFaster(5));
//		String s = "xxyyz";
//		String ss = "a";
//		System.out.println(s.charAt(s.length()-1  ));
//		System.out.println(s.charAt(s.length() - 2) == (s.charAt((s.length() -3 )) ));
//		System.out.println(ss.length());
//		int k = s.length();
//		System.out.println(s.charAt(0));
//		System.out.println(s.charAt(- s.length() + s.length() +1 ));
//		String g = s.substring(0, k);
//		System.out.println(s.substring(0, k));
//		System.out.println(g.substring(1, k));
		
		

		System.out.println(TowerOfHanoi.removeRepeats("xxxxhhyyjjjj bbuuu") );
		String b = "abcd";
		char bb = b.charAt(0);
		System.out.println( b );
		System.out.println( bb );
		System.out.println(TowerOfHanoi.binaryToInt( "11"));
		System.out.println(4 % 2);
		System.out.println(2 % 2);
		System.out.println(1 % 2);
		System.out.println(TowerOfHanoi.intToBinary(35));
		System.out.println(1 / 2);
		String k = "a";
		int kk = k.length();
		String f = k.substring(1, kk);
		
		System.out.println( k.substring(1, kk) +" and the length is :" + f.length());
		System.out.println( k );
		
		
		List<Integer> dis = new ArrayList<>(Arrays.asList(0,8,7,6,4,3,5,1,2,9));
		List<Integer> dat = dis.subList(3, dis.size());
		System.out.println(dat);
		System.out.println(dis);
		dat.set(5, 12);
		System.out.println(dat);
		System.out.println(dis);
		System.out.println( 10 );
		System.out.println( dis.subList(2, dis.size()-2) );
		
		int[] sequence;
		sequence = new int[4];
		sequence[0] = 1;
		sequence[1] = 3;
		sequence[2] = 2;
		sequence[3] = 1;
		System.out.println(sequence[0]+","+ sequence[1]+","+ sequence[2]+","+ sequence[3]);
		int lenSeq = sequence.length;
//		TowerOfHanoi.almostSeq(sequence);
//		int n = 4;
//		for (int j = 0; j < 6; j++) {
//			for(int i = 0; i < 6; i++) {
//				if(i >= j ) {
//					n = n-1;
//				}
//				System.out.print(n);
//			}
//			System.out.println(n);
//		}
//		
	
		
	System.out.println(TowerOfHanoi.dat(5));	
	TowerOfHanoi.datdisser(5);
	String ss = "abcc d  d";
	
	System.out.println(ss.contains(" "));
	
	System.out.println(TowerOfHanoi.letterCounter(ss));
	ss.substring(0, ss.length()-1);
//	Sytem.out.println(TowerOfHanoi.datdat(3));
	System.out.println(ss.substring(0, ss.length()-1));
	
	String[] inss = ss.split("\\s+");
	System.out.println(inss.length);
	TowerOfHanoi.Counter("LOVE");
	String kgk = "ABA";
//	System.out.println(kgk.charAt(0));
//	System.out.println(kgk.charAt(kgk.length()-1));
	TowerOfHanoi.palind("AABBAA");
	String A = kgk.substring(0, kgk.length()-1);
	String B = A.substring(1,A.length());
	System.out.println(B);
	System.out.println(TowerOfHanoi.palind("ACBAA"));
	TowerOfHanoi.Counter("All I do is count racks.");
//	System.out.println(TowerOfHanoi.solve(5, 6, 7, 3, 6, 10));
	int[] ar = TowerOfHanoi.solve(5, 6, 7, 3, 6, 10);
	System.out.println(ar[0]+ " "+ ar[1]);
	int[][] a;
	a = new int[3][3];
	a[0][0] = 11;
	a[0][1] = 2;
	a[0][2] = 4;
	a[1][0] = 4;
	a[1][1] = 5;
	a[1][2] = 6;
	a[2][0] = 10;
	a[2][1] = 8;
	a[2][2] = -12;
	int[][] foo = new int[][] {  new int[] { 1, 2, 3 }, new int[] { 1, 2, 3, 4}};
	System.out.println(TowerOfHanoi.diagonalDifference(a));
	int[] feel = new int[] { -4, 3, -9, 0, 4, 1 }; 
	TowerOfHanoi.plusMinus(feel);
	TowerOfHanoi.staircase(6);
	int[] sum = new int[] {3, 2, 1, 3};
//	TowerOfHanoi.miniMaxSum(sum);
	System.out.println(TowerOfHanoi.birthdayCakeCandles(4, sum));
	
//	String s = "05:05:45PM";
//	System.out.println(s.charAt(s.length()-2));
//	String result = s;
//	if (s.substring( s.length()-2 , s.length()).equals("PM")) {
//		int disboi = Integer.parseInt(s.substring(0,2));
//		
//		result = disboi + 12 + s.substring(2, s.length());
//		System.out.println(result);
//	}else {
//		System.out.println(result);

//	}
	
//	TowerOfHanoi.timeConversion("07:05:45PM");
	String s = "05:05:45PM";
	s = s.replace("PM", "");
	String[] hmsp = s.split(":");
	String h = hmsp[0];
	int kgh = Integer.parseInt(h) + 12;
	System.out.println(kgh +":"+ hmsp[1] + ":"+ hmsp[2]);
	System.out.println(67/10);
	int ll= 38;
	int[] grds = new int[] { 98, 38, 2, 0, 67, 38, 33}; 
	TowerOfHanoi.gradingStudents(grds);
	System.out.println(grds[1]);
	

	
	
	}

}
