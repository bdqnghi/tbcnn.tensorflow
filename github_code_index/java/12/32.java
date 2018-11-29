package Dynamic_Programming;

import java.util.HashMap;
import java.util.Map;

/**
 * Created by SanthoshVarathan on 01/07/17.
 */
class matrix{
    int r,c;
    matrix(int row,int col){
        r = row;
        c = col;
    }
    int getProductCost(matrix a, matrix b){
        return (a.c==b.r)?a.r*a.c*b.c:-1;
    }
}
public class MatrixMultiplication {
    Map<Map<matrix,matrix>,Integer> costMap = new HashMap<>();
    public static void printOptimalParanthesization(matrix matArray[],int start,int end){

    }
    public static void main(String ar[]){
        int input[] = {40, 20, 30, 10, 30};
        matrix matArray[] = new matrix[input.length-1];

        for(int i=0;i<input.length-1;i++)
            matArray[i] = new matrix(input[i],input[i+1]);
        printOptimalParanthesization(matArray,0,matArray.length-1);
    }
}
