import java.io.*;
import java.util.*;

class Radix {
	/** N.B. Sorterer a[] stigende –antar at: 0 ≤ a[i]) < 2^32*/
// viktig konstant 
final static int NUM_BIT =7;
// eller 6,8,9,10..
int []  radixMulti(int [] a) {
	long tt = System.nanoTime();
    // 1-5 digit radixSort of : a[]
	int max = a[0], numBit = 2, numDigits, n =a.length;
	int [] bit ;

    // a) finn max verdi i a[]
	for (int i = 1 ; i < n ; i++)
		if (a[i] > max) max = a[i];
    while (max >= (1L<<numBit) )numBit++; // antall siffer i max

    
    // bestem antall bit i numBits sifre
    numDigits = Math.max(1, numBit/NUM_BIT);
    bit = new int[numDigits];
    int rest = numBit%NUM_BIT, sum =0;
    // fordel bitene vi skal sortere paa jevnt
    for (int i = 0; i < bit.length; i++){
    	bit[i] = numBit/numDigits;
    	if ( rest-->0) bit[i]++;
    }
    int[] t=a, b = new int [n];
    for (int i =0; i < bit.length; i++) {
		radixSort( a,b,bit[i],sum );    // i-te siffer fra a[] til b[]
		sum += bit[i];
		// swap arrays (pointers only)
		t = a;
		a = b;
		b = t;
	}
	if ((bit.length&1) != 0 ) {
	//et odde antall sifre, kopier innhold tilbake til original a[] (nå b)
		System.arraycopy (a,0,b,0,a.length);
	}
	double tid = (System.nanoTime() -tt)/1000000.0;
	System.out.println("\nSorterte "+n+" tall serielt paa:" + tid + "millisek.");
	boolean order = testSort(a);
	System.out.println("a: " + order);
	//order = testSort(b);
	//System.out.println("b: " + order);
	return a;
} // end radix2



/** Sort a[] on one digit ; number of bits = maskLen, shiftet up 'shift' bits */
void radixSort ( int [] a, int [] b, int maskLen, int shift){
	//System.out.println(" radixSort maskLen:"+maskLen+", shift :"+shift);
	int  acumVal = 0, j, n = a.length;
	int mask = (1<<maskLen) -1;
	int [] count = new int [mask+1];

	
    // b) count=the frequency of each radix value in a
	for (int i = 0; i < n; i++) {
		count[(a[i]>>> shift) & mask]++;
	}

    // c) Add up in 'count' -accumulated values, i.e pointers
	for (int i = 0; i <= mask; i++) {
		j = count[i];
		count[i] = acumVal;
		acumVal += j;
	}

    // d) move numbers in sorted order a to b
	for (int i = 0; i < n; i++) {
		b[count[(a[i]>>>shift) & mask]++] = a[i];
	}
}// end radixSort





boolean testSort(int[] a) {
	boolean order = true;
	for (int i = 1; i < a.length; i++) {
		if (a[i-1] > a[i]) {
			order = false;
		}
	}
	return order;
}
}