import java.util.concurrent.RecursiveTask;

class MatrixMultiplication extends RecursiveTask<Matrix> {
  
  /** The fork threshold. */
  private static final int FORK_THRESHOLD = 64;

  /** The first matrix to multiply with. */
  private Matrix m1;

  /** The second matrix to multiply with. */
  private Matrix m2;

  /** The starting row of m1. */
  private int m1Row;

  /** The starting col of m1. */
  private int m1Col;

  /** The starting row of m2. */
  private int m2Row;

  /** The starting col of m2. */
  private int m2Col;

  /**
   * The dimension of the input (sub)-matrices and the size of the output
   * matrix.
   */
  private int dimension;

  /**
   * A constructor for the Matrix Multiplication class.
   * @param  m1 The matrix to multiply with.
   * @param  m2 The matrix to multiply with.
   * @param  m1Row The starting row of m1.
   * @param  m1Col The starting col of m1.
   * @param  m2Row The starting row of m2.
   * @param  m2Col The starting col of m2.
   * @param  dimension The dimension of the input (sub)-matrices and the size
   *     of the output matrix.
   */
  MatrixMultiplication(Matrix m1, Matrix m2, int m1Row, int m1Col, int m2Row,
                       int m2Col, int dimension) {
    this.m1 = m1;
    this.m2 = m2;
    this.m1Row = m1Row;
    this.m1Col = m1Col;
    this.m2Row = m2Row;
    this.m2Col = m2Col;
    this.dimension = dimension;
  }


  @Override
  public Matrix compute() {
    // If the matrix is small enough, just multiply non-recursively.
    if (dimension <= FORK_THRESHOLD) {
      return Matrix.nonRecursiveMultiply(m1, m2, m1Row, m1Col, m2Row, m2Col, dimension);
    }
    
    // Else, cut the matrix into four blocks of equal size, recursively
    // multiply then sum the multiplication result.
    int size = dimension / 2;
    Matrix result = new Matrix(dimension);

    MatrixMultiplication s1 = new MatrixMultiplication(m1, m2, m1Row, m1Col, m2Row,
        m2Col, size);
    MatrixMultiplication s2 = new MatrixMultiplication(m1, m2, m1Row, m1Col + size,
        m2Row + size, m2Col, size);    
    MatrixMultiplication s3 = new MatrixMultiplication(m1, m2, m1Row, m1Col, m2Row,
        m2Col + size, size);
    MatrixMultiplication s4 = new MatrixMultiplication(m1, m2, m1Row, m1Col + size,
        m2Row + size, m2Col + size, size);
    MatrixMultiplication s5 = new MatrixMultiplication(m1, m2, m1Row + size, m1Col,
        m2Row, m2Col, size);
    MatrixMultiplication s6 = new MatrixMultiplication(m1, m2, m1Row + size, m1Col + size,
        m2Row + size, m2Col, size);    
    MatrixMultiplication s7 = new MatrixMultiplication(m1, m2, m1Row + size, m1Col,
        m2Row, m2Col + size, size);
    MatrixMultiplication s8 = new MatrixMultiplication(m1, m2, m1Row + size, m1Col + size,
        m2Row + size, m2Col + size, size);

    s8.fork();
    s7.fork();
    s6.fork();
    s5.fork();
    s4.fork();
    s3.fork();
    s2.fork();
    //s1.fork();

    
    Matrix a11b11 = s1.compute();
    Matrix a12b21 = s2.join();
    Matrix a11b12 = s3.join();
    Matrix a12b22 = s4.join();
    Matrix a21b11 = s5.join();
    Matrix a22b21 = s6.join();
    Matrix a21b12 = s7.join();
    Matrix a22b22 = s8.join();

    /*Matrix a11b11 = recursiveMultiply(m1, m2, m1Row, m1Col, m2Row,
        m2Col, size);
    Matrix a12b21 = recursiveMultiply(m1, m2, m1Row, m1Col + size,
        m2Row + size, m2Col, size);
    Matrix a11b11 = s1.compute();
    Matrix a12b21 = s2.join();*/

    for (int i = 0; i < size; i++) {
      double[] m1m = a11b11.m[i];
      double[] m2m = a12b21.m[i];
      double[] r1m = result.m[i];
      for (int j = 0; j < size; j++) {
        r1m[j] = m1m[j] + m2m[j];
      }
    }

    /*Matrix a11b12 = recursiveMultiply(m1, m2, m1Row, m1Col, m2Row,
        m2Col + size, size);
    Matrix a12b22 = recursiveMultiply(m1, m2, m1Row, m1Col + size,
        m2Row + size, m2Col + size, size);
    Matrix a11b12 = s3.join();
    Matrix a12b22 = s4.join();*/

    for (int i = 0; i < size; i++) {
      double[] m1m = a11b12.m[i];
      double[] m2m = a12b22.m[i];
      double[] r1m = result.m[i];
      for (int j = 0; j < size; j++) {
        r1m[j + size] = m1m[j] + m2m[j];
      }
    }

    /*Matrix a21b11 = recursiveMultiply(m1, m2, m1Row + size, m1Col,
        m2Row, m2Col, size);
    Matrix a22b21 = recursiveMultiply(m1, m2, m1Row + size, m1Col + size,
        m2Row + size, m2Col, size);
    Matrix a21b11 = s5.join();
    Matrix a22b21 = s6.join();*/

    for (int i = 0; i < size; i++) {
      double[] m1m = a21b11.m[i];
      double[] m2m = a22b21.m[i];
      double[] r1m = result.m[i + size];
      for (int j = 0; j < size; j++) {
        r1m[j] = m1m[j] + m2m[j];
      }
    }

    /*Matrix a21b12 = recursiveMultiply(m1, m2, m1Row + size, m1Col,
        m2Row, m2Col + size, size);
    Matrix a22b22 = recursiveMultiply(m1, m2, m1Row + size, m1Col + size,
        m2Row + size, m2Col + size, size);
    Matrix a21b12 = s7.join();
    Matrix a22b22 = s8.join();*/

    for (int i = 0; i < size; i++) {
      double[] m1m = a21b12.m[i];
      double[] m2m = a22b22.m[i];
      double[] r1m = result.m[i + size];
      for (int j = 0; j < size; j++) {
        r1m[j + size] = m1m[j] + m2m[j];
      }
    }
    return result;
  }
}
