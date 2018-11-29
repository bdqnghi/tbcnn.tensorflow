package Tools;
import Classes.*;

public class Matrixmultiplication {

	public static void main(String[] args) {
		// TODO Auto-generated method stub

		
//		int DimXA = 4;
//		int DimYA = 3;
//		double[][] MatrixarrayA = {
//				{1,3,5,6},
//				{4,2,2,8},
//				{6,0,4,8}
//				};
//		
//		int DimXB = 4;
//		int DimYB = DimXA;
//		double[][] MatrixarrayB = {
//								{9,7,5,2},
//								{2,3,1,4},
//								{5,3,5,2},
//								{1,5,2,3}
//				
//		};
		

		
		
		double[][] MatrixarrayB = {{0},{0},{1}};
		
//		Matrix MatrixA = new Matrix(DimXA,DimYA,MatrixarrayA);
//		Matrix MatrixB = new Matrix(DimXB,DimYB,MatrixarrayB);
//		
//		Matrix MatrixC = Multiplymatrix(MatrixA,MatrixB);
		
			Matrix MatrixA = new Matrix(1,3,MatrixarrayB);
			Matrix MatrixB = Rotationsmatrix.RMatrix(Math.PI/6, "x");
			Matrix MatrixC = Rotationsmatrix.RMatrix(Math.PI/6, "y");
			Matrix MatrixD = Rotationsmatrix.RMatrix(Math.PI/4, "x");
			Matrix MatrixE = Rotationsmatrix.RMatrix(Math.atan(0.2), "x");
		
		
			Matrix[] Matrixlist = new Matrix[5];
			Matrixlist[0] = MatrixA;
			Matrixlist[1] = MatrixB;
			Matrixlist[2] = MatrixC;
			Matrixlist[3] = MatrixD;
			Matrixlist[4] = MatrixE;
			
			
			Matrix MatrixS = Methods.sukzessiveMatrixmultiplication(Matrixlist);
		
		
		for (int i1 = 0;i1 < MatrixS.DimY;i1++){
			System.out.println();
			for (int i2 = 0;i2 < MatrixS.DimX;i2++){
				System.out.print(" " + MatrixS.Matrixarray[i1][i2]);
			}
		}

		
		System.out.println();
		System.out.println();
		System.out.println(Methods.vektorbetrag(Methods.extractSpaltenvektor(MatrixS, 0)));
		
//		for (int i1 = 0;i1 < MatrixA.DimY;i1++){
//			System.out.println();
//			for (int i2 = 0;i2 < MatrixA.DimX;i2++){
//				System.out.print(" " + MatrixA.Matrixarray[i1][i2]);
//		}
//	}
}
		
	public static Matrix Multiplymatrix(Matrix MatrixA, Matrix MatrixB){
		double[][] Matrixarray = new double[MatrixA.DimY][MatrixB.DimX];
		Matrix MatrixC = new Matrix(MatrixB.DimX,MatrixA.DimY,Matrixarray);
		
		for (int i1 = 0;i1 < MatrixC.DimY;i1++){
			for (int i2 = 0;i2 < MatrixC.DimX;i2++){
				MatrixC.Matrixarray[i1][i2] = Methods.skalarprodukt(Methods.extractZeilenvektor(MatrixA,i1),Methods.extractSpaltenvektor(MatrixB, i2));
			}
		}
		return MatrixC;
	}
	
}