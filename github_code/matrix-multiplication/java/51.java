package fs_l1;

import java.util.Scanner;

public class MatrixMultiplication {

	public static void main(String... args)	{
		int R1, C1, R2, C2;

		Scanner sc = new Scanner(System.in);

		System.out.println("Enter the no.of rows in 1st Matrix :");
		R1 = sc.nextInt();		
		System.out.println("Enter the no.of columns in 1st Matrix :");
		C1 = sc.nextInt();


		System.out.println("Enter the no.of rows in 2nd Matrix :");
		R2 = sc.nextInt();	
		System.out.println("Enter the no.of columns in 2nd Matrix :");
		C2 = sc.nextInt();

		if (C1 != R2){

		System.out.println("Matrix multiplication is not possible. Columns(C1) of the 1st Matrix and Rows(R2) of the 2nd Matrix should be same!!");
		System.exit(1);

		}

		// First Matrix
		int [][] mat1 = new int [R1][C1];

		System.out.println("Input the values for your 1st Matrix - " + R1 + "*" + C1 );
	
		//Getting info
		for (int i=0; i<R1; i++){
			for (int j=0; j<C1; j++){
				System.out.println("Enter A" + (i + 1) + (j + 1) + " :");
				mat1[i][j] = sc.nextInt();
			}	
		}
		
		System.out.println("");
		//Display back info
		for (int i=0; i<R1; i++){
			for (int j=0; j<C1; j++){		
			System.out.print(mat1[i][j] + " ");
			}	
			System.out.println("");
		}

		
		// Second Matrix
		int [][] mat2 = new int [R2][C2];

		System.out.println("Input the values for your 2nd Matrix - " + R2 + "*" + C2 );
	
		//Getting info
		for (int i=0; i<R2; i++){
			for (int j=0; j<C2; j++){
				System.out.println("Enter B" + (i + 1) + (j + 1) + " :");
				mat2[i][j] = sc.nextInt();
			}	
		}
		
		System.out.println("");
		//Display back info
		for (int i=0; i<R2; i++){
			for (int j=0; j<C2; j++){		
			System.out.print(mat2[i][j] + " ");
			}	
			System.out.println("");
		}


		sc.close();
		
		// Resultant Matrix
		int [][] mat3 = new int [R1][C2];
		
		//Matrix Multiplication
		for (int i=0; i<R1; i++){
			for (int j=0; j<C2; j++){
				for (int k=0; k<C1; k++){
					mat3[i][j] = mat3[i][j]  + (mat1[i][k] * mat2[k][j]);
				}
			}
		}

		System.out.println("");
		System.out.println("Resultant Matrix after Multiplication is : ");
		//Display back Resultant Matrix
		for (int i=0; i<R1; i++){
			for (int j=0; j<C2; j++){		
			System.out.print(mat3[i][j] + " ");
			}	
			System.out.println("");
			
			
		}
	}
}
