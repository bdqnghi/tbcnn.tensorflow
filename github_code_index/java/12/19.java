
import java.util.Scanner;
class MatrixTranspose{
	public static void main(String[] args){
		int[][] matrix = new int[3][3];
		int[][] matrixTranspose = new int[3][3];
		int flag = 1;
		Scanner s = new Scanner(System.in);
		for(int i=0; i<3; i++){
			for(int j=0; j<3; j++){
				matrix[i][j] = s.nextInt();
			}
		}
		for(int i=0;i<3;i++){
			for(int j=0;j<3;j++){
				matrixTranspose[j][i] = matrix[i][j];
			}
		}
		for(int i=0;i<3;i++){
			for(int j=0;j<3;j++){
				if(matrixTranspose[i][j]!=matrix[i][j]){
					flag = 0;
					break;
				}
			}
		}
		if(flag == 0){
			System.out.println("They are not symmetric");
		}
		else {
			System.out.println("They are the symmetric");
		}
	}
}
