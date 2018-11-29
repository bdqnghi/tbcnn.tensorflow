public class DivConqMM
{
	public static int[][] matrixMultiplication(
        int[][] m1, int[][] m2, int rowA, int colA, 
        int rowB, int colB, int size)
    {

    int[][] m3= new int[size][size];

    if(size==1)
        m3[0][0]= m1[rowA][colA]*m2[rowB][colB];

    else{

        int newSize= size/2;
         sumMatrix(m3, 

            matrixMultiplication(m1, m2, rowA, colA, rowB, colB, newSize),
            matrixMultiplication(m1, m2, rowA, colA+newSize, rowB+ newSize, colB, newSize),
        0, 0);

         sumMatrix(m3, 

            matrixMultiplication(m1, m2, rowA, colA, rowB, colB + newSize, newSize),
            matrixMultiplication(m1, m2, rowA, colA+newSize, rowB+ newSize, colB+newSize, newSize),
        0, newSize);

         sumMatrix(m3, 

            matrixMultiplication(m1, m2, rowA+ newSize, colA, rowB, colB, newSize),
            matrixMultiplication(m1, m2, rowA+ newSize, colA+newSize, rowB+ newSize, colB, newSize),
        newSize, 0);

         sumMatrix(m3, 

            matrixMultiplication(m1, m2, rowA+ newSize, colA, rowB, colB+newSize, newSize),
            matrixMultiplication(m1, m2, rowA+ newSize, colA+newSize, rowB+ newSize, colB+newSize, newSize),
        newSize, newSize);
    }

    return m3;

}


private static void sumMatrix(int[][] m3, int[][] m1, int[][] m2,int rowC, int colC){
    int n = m1.length;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {  
            m3[i + rowC][j + colC] = m1[i][j] + m2[i][j];
        }
    }
}
}