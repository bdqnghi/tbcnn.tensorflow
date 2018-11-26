package de.lab4inf.wrb.matrix;

public class SerialMultiplier {

	public static Matrix multiply(Matrix A, Matrix B) throws IllegalArgumentException {
		/*
		 * Fehlerbehandlung
		 */
		
		if(A.getM() == null || B.getM() == null)
			throw new IllegalArgumentException("Matrizen können nicht null sein");
		
		if(A.getCols() != B.getRows())
			throw new IllegalArgumentException("Matrizen sind nicht kompatibel für Matrix-Multiplication");
		
		/**
		 * Algo
		 */
		
		Matrix res = new Matrix(A.getRows(), B.getCols());
		
		for(int rowA = 0; rowA < A.getRows(); rowA++) {
			for(int colB = 0; colB < B.getCols(); colB++) {
				double sum = .0;
				for(int colA = 0; colA < A.getCols(); colA++) {
					sum += A.get(rowA, colA) * B.get(colA, colB);
				}
				res.set(rowA, colB, sum);
			}
		}
		
		return res;
	}
}
