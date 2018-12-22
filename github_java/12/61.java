package io.raspberrywallet.manager.cryptography.sharedsecret.blakley.JLinAlg;

/**
 * This includes some different methods of multiplying two matrices. 
 * The standard method of the Matrix class is the school-method.
 * All the other stuff is to be considered experimental stuff.
 * 
 * @author Andreas
 *
 */

public class MatrixMultiplication {

	private static int STRASSEN_ORIGINAL_TRUNCATION_POINT = 48;
	private static int STRASSEN_WINOGRAD_TRUNCATION_POINT = 48;

	private static void checkDimensions(Matrix m1, Matrix m2)
		throws InvalidOperationException {
		if (m1.getCols() != m2.getRows()) {
			throw new InvalidOperationException(
				"Tried to multiply a matrix with "
					+ m1.getCols()
					+ " columns and a matrix with "
					+ m2.getRows()
					+ " rows");
		}
	}

	/**
	 * Uses the standard method for multiplication of Matrix-objects.
	 * Asymptotic runtime: 0(n^3)
	 * @param m1
	 * @param m2
	 * @return m1 multiplied by m2
	 * @throws InvalidOperationException
	 */
	public static Matrix simple(Matrix m1, Matrix m2)
		throws InvalidOperationException {
		checkDimensions(m1, m2);

		int resultRows = m1.getRows();
		int resultCols = m2.getCols();

		Matrix resultMatrix = new Matrix(resultRows, resultCols);

		for (int i = 1; i <= resultRows; i++) {
			for (int j = 1; j <= resultCols; j++) {
				resultMatrix.set(i, j, m1.getRow(i).multiply(m2.getCol(j)));
			}
		}
		return resultMatrix;
	}

	/**
	 * This could be considered the school-method of multiplying matrices.
	 * Asymptotic runtime: 0(n^3)
	 * @param m1
	 * @param m2
	 * @return m1 multiplied by m2
	 * @throws InvalidOperationException
	 */
	
	public static Matrix school(Matrix m1, Matrix m2)
		throws InvalidOperationException {
		checkDimensions(m1, m2);

		int resultRows = m1.getRows();
		int resultCols = m2.getCols();

		FieldElement[][] m1Entries = m1.getEntries();
		FieldElement[][] m2Entries = m2.getEntries();

		FieldElement instance = m1.get(1, 1);
		FieldElement[][] resultEntries =
			new FieldElement[resultRows][resultCols];

		for (int i = 0; i < resultRows; i++) {
			for (int j = 0; j < resultCols; j++) {
				resultEntries[i][j] = instance.zero();
				for (int k = 0; k < m2Entries.length; k++) {
					resultEntries[i][j] =
						resultEntries[i][j].add(
							m1Entries[i][k].multiply(m2Entries[k][j]));
				}
			}
		}
		return new Matrix(resultEntries);
	}

	/**
	 * The original Strassen-Algorithm for matrix-multiplication.
	 * Runtime: approximately O(2.6)
	 * @param m1
	 * @param m2
	 * @return m1 multiplied by m2
	 * @throws InvalidOperationException
	 */
	public static Matrix strassenOriginal(Matrix m1, Matrix m2) {

		checkDimensions(m1, m2);

		if (m1.getRows() <= STRASSEN_ORIGINAL_TRUNCATION_POINT) {
			return m1.multiply(m2);
		}

		int endIndex = m1.getRows();
		int splitIndex = endIndex / 2;

		Matrix a11 = m1.getMatrix(1, splitIndex, 1, splitIndex);
		Matrix a12 = m1.getMatrix(1, splitIndex, splitIndex + 1, endIndex);
		Matrix a21 = m1.getMatrix(splitIndex + 1, endIndex, 1, splitIndex);
		Matrix a22 =
			m1.getMatrix(splitIndex + 1, endIndex, splitIndex + 1, endIndex);

		Matrix b11 = m2.getMatrix(1, splitIndex, 1, splitIndex);
		Matrix b12 = m2.getMatrix(1, splitIndex, splitIndex + 1, endIndex);
		Matrix b21 = m2.getMatrix(splitIndex + 1, endIndex, 1, splitIndex);
		Matrix b22 =
			m2.getMatrix(splitIndex + 1, endIndex, splitIndex + 1, endIndex);

		Matrix p1 = strassenOriginal(a11.add(a22), b11.add(b22));
		Matrix p2 = strassenOriginal(a21.add(a22), b11);
		Matrix p3 = strassenOriginal(a11, b12.subtract(b22));
		Matrix p4 = strassenOriginal(a22, b21.subtract(b11));
		Matrix p5 = strassenOriginal(a11.add(a12), b22);
		Matrix p6 = strassenOriginal(a21.subtract(a11), b11.add(b12));
		Matrix p7 = strassenOriginal(a12.subtract(a22), b21.add(b22));

		Matrix c11 = p1.add(p4).subtract(p5).add(p7);
		Matrix c12 = p3.add(p5);
		Matrix c21 = p2.add(p4);
		Matrix c22 = p1.add(p3).subtract(p2).add(p6);

		FieldElement[][] c11Entries = c11.getEntries();
		FieldElement[][] c12Entries = c12.getEntries();
		FieldElement[][] c21Entries = c21.getEntries();
		FieldElement[][] c22Entries = c22.getEntries();

		FieldElement[][] cEntries =
			new FieldElement[m1.getRows()][m2.getRows()];

		for (int i = 0; i < c11.getRows(); i++) {
			for (int j = 0; j < c11.getCols(); j++) {
				cEntries[i][j] = c11Entries[i][j];
			}
		}

		for (int i = 0; i < c12.getRows(); i++) {
			int offset = splitIndex;
			for (int j = 0; j < c12.getCols(); j++) {
				cEntries[i][j + splitIndex] = c12Entries[i][j];
			}
		}

		for (int i = 0; i < c21.getRows(); i++) {
			int offset = splitIndex;
			for (int j = 0; j < c21.getCols(); j++) {
				cEntries[i + splitIndex][j] = c21Entries[i][j];
			}
		}

		for (int i = 0; i < c22.getRows(); i++) {
			int offset = splitIndex;
			for (int j = 0; j < c22.getCols(); j++) {
				cEntries[i + splitIndex][j + splitIndex] = c22Entries[i][j];
			}
		}

		return new Matrix(cEntries);
	}

	/**
	 * The Algorithm of Strassen-Winograd for matrix-multiplication.
	 * Runtime: ?
	 * @param m1
	 * @param m2
	 * @return m1 multiplied by m2
	 * @throws InvalidOperationException
	 */
	
	public static Matrix strassenWinograd(Matrix m1, Matrix m2) {
		checkDimensions(m1, m2);

		if (m1.getRows() <= STRASSEN_WINOGRAD_TRUNCATION_POINT) {
			return m1.multiply(m2);
		}

		int endIndex = m1.getRows();
		int splitIndex = endIndex / 2;

		Matrix a11 = m1.getMatrix(1, splitIndex, 1, splitIndex);
		Matrix a12 = m1.getMatrix(1, splitIndex, splitIndex + 1, endIndex);
		Matrix a21 = m1.getMatrix(splitIndex + 1, endIndex, 1, splitIndex);
		Matrix a22 =
			m1.getMatrix(splitIndex + 1, endIndex, splitIndex + 1, endIndex);

		Matrix b11 = m2.getMatrix(1, splitIndex, 1, splitIndex);
		Matrix b12 = m2.getMatrix(1, splitIndex, splitIndex + 1, endIndex);
		Matrix b21 = m2.getMatrix(splitIndex + 1, endIndex, 1, splitIndex);
		Matrix b22 =
			m2.getMatrix(splitIndex + 1, endIndex, splitIndex + 1, endIndex);

		Matrix s1 = a21.add(a22);
		Matrix s2 = s1.subtract(a11);
		Matrix s3 = a11.subtract(a21);
		Matrix s4 = a12.subtract(s2);

		Matrix t1 = b12.subtract(b11);
		Matrix t2 = b22.subtract(t1);
		Matrix t3 = b22.subtract(b12);
		Matrix t4 = b21.subtract(t2);

		Matrix p1 = strassenOriginal(a11, b11);
		Matrix p2 = strassenOriginal(a12, b21);
		Matrix p3 = strassenOriginal(s1, t1);
		Matrix p4 = strassenOriginal(s2, t2);
		Matrix p5 = strassenOriginal(s3, t3);
		Matrix p6 = strassenOriginal(s4, b22);
		Matrix p7 = strassenOriginal(a22, t4);

		Matrix u1 = p1.add(p2);
		Matrix u2 = p1.add(p4);
		Matrix u3 = u2.add(p5);
		Matrix u4 = u3.add(p7);
		Matrix u5 = u3.add(p3);
		Matrix u6 = u2.add(p3);
		Matrix u7 = u6.add(p6);

		FieldElement[][] c11Entries = u1.getEntries();
		FieldElement[][] c12Entries = u7.getEntries();
		FieldElement[][] c21Entries = u4.getEntries();
		FieldElement[][] c22Entries = u5.getEntries();

		FieldElement[][] cEntries =
			new FieldElement[m1.getRows()][m2.getRows()];

		for (int i = 0; i < u1.getRows(); i++) {
			for (int j = 0; j < u1.getCols(); j++) {
				cEntries[i][j] = c11Entries[i][j];
			}
		}

		for (int i = 0; i < u7.getRows(); i++) {
			int offset = splitIndex;
			for (int j = 0; j < u7.getCols(); j++) {
				cEntries[i][j + splitIndex] = c12Entries[i][j];
			}
		}

		for (int i = 0; i < u4.getRows(); i++) {
			int offset = splitIndex;
			for (int j = 0; j < u4.getCols(); j++) {
				cEntries[i + splitIndex][j] = c21Entries[i][j];
			}
		}
		
		for (int i = 0; i < u5.getRows(); i++) {
			int offset = splitIndex;
			for (int j = 0; j < u5.getCols(); j++) {
				cEntries[i + splitIndex][j] = c21Entries[i][j];
			}
		}

		return new Matrix(cEntries);

	}

}
