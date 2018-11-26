package lab5;

import java.util.concurrent.RecursiveTask;

class MatrixMultiplication extends RecursiveTask<Matrix> {
  /** The serial version UID of this class. */
  public static final long serialVersionUID = 1;

  /** The matrix to multiply with. */
  private Matrix m1;

  /** The matrix to multiply with. */
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
   * The dimension of the input (sub)-matrices and the size
   * of the output matrix.
   */
  private int dimension;

  /**
   * The threshold to determine whether to continue split the task.
   */
  private static final int THRESHOLD = 128;

  /**
   * Constructor of new matrix multiplication task.
   * @param  m1 The matrix to multiply with.
   * @param  m2 The matrix to multiply with.
   * @param  m1Row The starting row of m1.
   * @param  m1Col The starting col of m1.
   * @param  m2Row The starting row of m2.
   * @param  m2Col The starting col of m2.
   * @param  dimension The dimension of the input (sub)-matrices and the size
   *     of the output matrix.
   */
  MatrixMultiplication(Matrix m1, Matrix m2,
      int m1Row, int m1Col, int m2Row, int m2Col, int dimension) {
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
    if (this.dimension <= THRESHOLD) {
      return Matrix.multiplyNonRecursively(m1, m2, m1Row, m1Col, m2Row, m2Col, dimension);
    } else {
      int size = dimension / 2;
      Matrix result = new Matrix(dimension);

      MatrixMultiplication a11b11 = new MatrixMultiplication(m1, m2, m1Row, m1Col, m2Row,
          m2Col, size);
      MatrixMultiplication a12b21 = new MatrixMultiplication(m1, m2, m1Row, m1Col + size,
          m2Row + size, m2Col, size);

      MatrixMultiplication a11b12 = new MatrixMultiplication(m1, m2, m1Row, m1Col, m2Row,
          m2Col + size, size);
      MatrixMultiplication a12b22 = new MatrixMultiplication(m1, m2, m1Row, m1Col + size,
          m2Row + size, m2Col + size, size);

      MatrixMultiplication a21b11 = new MatrixMultiplication(m1, m2, m1Row + size, m1Col,
          m2Row, m2Col, size);
      MatrixMultiplication a22b21 = new MatrixMultiplication(m1, m2, m1Row + size, m1Col + size,
          m2Row + size, m2Col, size);

      MatrixMultiplication a21b12 = new MatrixMultiplication(m1, m2, m1Row + size, m1Col,
          m2Row, m2Col + size, size);
      MatrixMultiplication a22b22 = new MatrixMultiplication(m1, m2, m1Row + size, m1Col + size,
          m2Row + size, m2Col + size, size);

      a11b11.fork();
      a12b21.fork();
      a11b12.fork();
      a12b22.fork();
      a21b11.fork();
      a22b21.fork();
      a21b12.fork();

      Matrix a22b22m = a22b22.compute();
      Matrix a21b12m = a21b12.join();

      for (int i = 0; i < size; i++) {
        double[] m1m = a21b12m.m[i];
        double[] m2m = a22b22m.m[i];
        double[] r1m = result.m[i + size];
        for (int j = 0; j < size; j++) {
          r1m[j + size] = m1m[j] + m2m[j];
        }
      }

      Matrix a22b21m = a22b21.join();
      Matrix a21b11m = a21b11.join();

      for (int i = 0; i < size; i++) {
        double[] m1m = a21b11m.m[i];
        double[] m2m = a22b21m.m[i];
        double[] r1m = result.m[i + size];
        for (int j = 0; j < size; j++) {
          r1m[j] = m1m[j] + m2m[j];
        }
      }

      Matrix a12b22m = a12b22.join();    
      Matrix a11b12m = a11b12.join();

      for (int i = 0; i < size; i++) {
        double[] m1m = a12b22m.m[i];
        double[] m2m = a11b12m.m[i];
        double[] r1m = result.m[i];
        for (int j = 0; j < size; j++) {
          r1m[j + size] = m1m[j] + m2m[j];
        }
      }

      Matrix a12b21m = a12b21.join();
      Matrix a11b11m = a11b11.join();

      for (int i = 0; i < size; i++) {
        double[] m1m = a11b11m.m[i];
        double[] m2m = a12b21m.m[i];
        double[] r1m = result.m[i];
        for (int j = 0; j < size; j++) {
          r1m[j] = m1m[j] + m2m[j];
        }
      }
      return result;
    }
  }
}
