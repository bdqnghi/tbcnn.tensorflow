package array;

import java.util.ArrayList;
import java.util.List;

public class SparseMatrixMultiplication {

	public static void main(String[] args) {
		int[][] A = {{1,0,0}, {-1,0,3}};
		int[][] B = {{7,0,0}, {0,0,0}, {0,0,1}};
		int[][] answer = multiply(A, B);
		
		for (int i=0; i<answer.length; i++) {
			for (int j=0; j<answer[0].length; j++) {
				System.out.print(answer[i][j] + " ");
			}
			System.out.println();
		}
	}

	public static int[][] multiply(int[][] A, int[][] B) {
        int row = A.length;
        int col = B[0].length;
        int mid = A[0].length;
        
        int[][] answer = new int[row][col];
        List<int[]>[] listA = new List[row];
        
        for (int i=0; i<row; i++) {
            List<int[]> list = new ArrayList<>();
            for (int j=0; j<mid; j++) {
                if (A[i][j] != 0) {
                    list.add(new int[]{j, A[i][j]});
                }
            }
            listA[i] = list;
        }
        
        for(int i=0; i<row; i++) {
            List<int[]> numsA = listA[i];
            for(int p=0; p<numsA.size(); p++) {
                int colA = numsA.get(p)[0];
                int valA = numsA.get(p)[1];
                
                for(int j=0; j<col; j++) {
                    int valB = B[colA][j];
                    answer[i][j] += valA * valB;
                }
            }
        }

        return answer;
    }
}
