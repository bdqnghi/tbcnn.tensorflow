
public class RadixSort {
		
		public static int digit(int number, int digit) {
			int n = 0;
			while (digit > 0) {
				if(number == 0) {
			    	return -1;
			    }
			    n = number % 10;
			    number = number / 10;
			    digit--;
			}
			return n;
		}
		
		public static void sort(int[] a) {
			if(a.length <=1) {
				return;
			}
			boolean sorted = false;
			int wallIndex = 0;
			int lowDigit = 11;
			int temp;
			int digitNum = 1;
			while(!sorted) {
				sorted = true;
				for(int i=0; i<a.length; i++) {
					int digit = digit(a[i], digitNum);
					if(digit==-1) {
						wallIndex++;
					} if( digit < lowDigit) {
						sorted = false;
						lowDigit = digit;
						temp = a[0];
						a[0] = a[i];
						a[i] = temp;
						wallIndex = 1;
					} else if(digit == lowDigit) {
						temp = a[wallIndex];
						a[wallIndex] = a[i];
						a[i] =temp;
						wallIndex++;
						sorted = false;
					}
				}
				lowDigit = 11;
				digitNum++;
			}
			
		}
		
		public static void main(String[] args) {
			int a[] = {5,4,8,1,3,6,34,8723,9,5,3,238,98,374,93,34,6,90,23};
			RadixSort.sort(a);
			
			for(int i=0; i<a.length; i++) {
				System.out.print(a[i] + " ");
			}
		}
}
