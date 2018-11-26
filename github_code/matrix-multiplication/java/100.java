import java.util.Scanner;


public class MatrixMultiplication {

	/**
	 * @param args
	 */
	public static void main(String[] args) {

		Scanner input = new Scanner(System.in);

		System.out.println("Enter the Matrix Size");
		
		int size = input.nextInt();
		
		int [] [] x = new int [size] [size];
		int [] [] y = new int [size] [size];
		int [] [] z = new int [size] [size];
		
		// Get the X Matrix
		System.out.println("Enter the X Matrix elements: ");		
		for (int row = 0; row < size; row++) {
			for (int col = 0; col < size; col++) {
				System.out.println("Elements at the row: " + row + " & col: " + col);
				
				x[row][col] = input.nextInt();
			}
		}

		// Get the X Matrix
		System.out.println("Enter the X Matrix elements: ");
		for (int row = 0; row < size; row++) {
			for (int col = 0; col < size; col++) {
				System.out.println("Elements at the row: " + row + " & col: " + col);

				y[row][col] = input.nextInt();
			}
		}


		// Create the z Matrix
		for (int row = 0; row < size; row++) {
			for (int col = 0; col < size; col++) {

				int sum = 0;
				
				for (int i = 0; i < size; i++) {
					sum += (x[row][i] * y[i][col]) ;
				}
				
				z[row][col] = sum;
			}
		}
		
		// Print the out put
		for (int row = 0; row < size; row++) {
			for (int col = 0; col < size; col++) {
				System.out.print(z[row][col] + " ");
			}
			System.out.println(" ");
		}

	}

}
