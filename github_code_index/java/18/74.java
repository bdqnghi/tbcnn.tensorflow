import java.util.Scanner;

public class Selectionsort {

/* What Did I understand?
 * In selection sort, you have to identify the maximum/ minimum element in the list and put it in the proper position
 * Input: #of elements followed by elements in the list
 * output: the sorted order
 */
	
	public static void main(String[] args) {
		Scanner input = new Scanner(System.in);
		int noOfEle;
		noOfEle = input.nextInt();
		int array[] = new int[100];
		//Reading the elements from the input
		for(int i=0;i<noOfEle;i++){
			array[i] = input.nextInt();
		}
		input.close();
		//Perform the sort
		int maximum;
		int temp;
		for(int i=0;i<noOfEle;i++){
			//Select Maximum element and put at last.
			maximum = 0;
			for(int j=1;j<(noOfEle-i);j++){
				if(array[j]>array[maximum]){
					maximum = j;
				}
			}
			temp = array[noOfEle -i -1];
			array[noOfEle -i -1] = array[maximum];
			array[maximum] = temp;
		}
		//Display the elements
		for(int i=0;i<noOfEle;i++){
			System.out.println(array[i]);
		}
	}
}
