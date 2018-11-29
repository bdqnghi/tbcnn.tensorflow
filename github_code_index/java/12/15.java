import java.util.concurrent.RecursiveTask;

class MatrixMultiplication extends RecursiveTask<Matrix> {
  
  /** The fork threshold. */
  private static final int FORK_THRESHOLD = 128;

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


  /**
   * If threshold reached, multiply nonrecursively.
   * Else, fork and send work to pool.
   */
  
  @Override
  public Matrix compute() {//the method that every worker will call when they start work
      if (this.dimension <= FORK_THRESHOLD) {
          return Matrix.nonRecursiveMultiply(m1, m2, m1Row, m1Col, m2Row, m2Col, dimension);
      }

      int size = dimension / 2;
      Matrix result = new Matrix(dimension);
      
      MatrixMultiplication t1 = new MatrixMultiplication(m1, m2, m1Row, m1Col + size,
        m2Row + size, m2Col, size);
      MatrixMultiplication t2 = new MatrixMultiplication(m1, m2, m1Row, m1Col, m2Row,
        m2Col, size);
      MatrixMultiplication t3 = new MatrixMultiplication(m1, m2, m1Row, m1Col + size,
        m2Row + size, m2Col + size, size);
      MatrixMultiplication t4 = new MatrixMultiplication(m1, m2, m1Row, m1Col, m2Row,
        m2Col + size, size);
      MatrixMultiplication t5 = new MatrixMultiplication(m1, m2, m1Row + size, m1Col + size,
        m2Row + size, m2Col, size);
      MatrixMultiplication t6 = new MatrixMultiplication(m1, m2, m1Row + size, m1Col,
        m2Row, m2Col, size);
      MatrixMultiplication t7 = new MatrixMultiplication(m1, m2, m1Row + size, m1Col + size,
        m2Row + size, m2Col + size, size);
      MatrixMultiplication t8 = new MatrixMultiplication(m1, m2, m1Row + size, m1Col,
        m2Row, m2Col + size, size);

      t1.fork();
      t2.fork();
      t3.fork();
      t4.fork();
      t5.fork();
      t6.fork();
      t7.fork();
      t8.fork();

      Matrix m8 = t8.join();
      Matrix m7 = t7.join();
      for (int i = 0; i < size; i++) {
          double[] m1m = m8.m[i];
          double[] m2m = m7.m[i];
          double[] r1m = result.m[i + size];
          for (int j = 0; j < size; j++) {
              r1m[j + size] = m1m[j] + m2m[j];
          }
      }
      
      Matrix m6 = t6.join();
      Matrix m5 = t5.join();
      for (int i = 0; i < size; i++) {
          double[] m1m = m6.m[i];
          double[] m2m = m5.m[i];
          double[] r1m = result.m[i + size];
          for (int j = 0; j < size; j++) {
              r1m[j] = m1m[j] + m2m[j];
          }
      }
      
      Matrix m4 = t4.join();
      Matrix m3 = t3.join();
      for (int i = 0; i < size; i++) {
          double[] m1m = m4.m[i];
          double[] m2m = m3.m[i];
          double[] r1m = result.m[i];
          for (int j = 0; j < size; j++) {
              r1m[j + size] = m1m[j] + m2m[j];
          }
      }
      
      Matrix m2 = t2.join();
      Matrix m1 = t1.join();
      for (int i = 0; i < size; i++) {
          double[] m1m = m2.m[i];
          double[] m2m = m1.m[i];
          double[] r1m = result.m[i];
          for (int j = 0; j < size; j++) {
              r1m[j] = m1m[j] + m2m[j];
          }
      }
      
      return result;
  }
}
