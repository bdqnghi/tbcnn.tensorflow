package com.ikaver.aagarwal.fjavaexamples;

import com.ikaver.aagarwal.common.FJavaConf;
import com.ikaver.aagarwal.common.FastStopwatch;
import com.ikaver.aagarwal.common.problems.MatrixMultiplication;
import com.ikaver.aagarwal.fjava.FJavaPool;
import com.ikaver.aagarwal.fjava.FJavaTask;

public class FJavaMatrixMultiplication extends FJavaTask implements
MatrixMultiplication {

  private FastStopwatch watch;
  private float[][] A;
  private float[][] B;
  private float[][] C;
  private int aRow, aCol, bRow, bCol, cRow, cCol;
  private int size;

  private FJavaPool pool;

  public FJavaMatrixMultiplication(FJavaPool pool) {
    this.pool = pool;
    // No need to initialize watch here.
  }

  public FJavaMatrixMultiplication(float[][] A, float[][] B, float[][] C,
      int size, int rowA, int colA, int rowB, int colB, int rowC, int colC) {
    this.A = A;
    this.B = B;
    this.C = C;
    this.size = size;
    this.aRow = rowA;
    this.aCol = colA;
    this.bRow = rowB;
    this.bCol = colB;
    this.cRow = rowC;
    this.cCol = colC;
    if (FJavaConf.shouldTrackStats()) {
      watch = new FastStopwatch();
    }
  }

  public void multiply(float[][] a, float[][] b, float[][] result) {
    this.pool.run(new FJavaMatrixMultiplication(a, b, result, a.length, 0, 0,
        0, 0, 0, 0));
  }

  @Override
  public void compute() {
    if (FJavaConf.shouldTrackStats()) {
      watch.start();
    }
    if (size <= FJavaConf.getMatrixMultiplicationSequentialThreshold()) {
      multiplySeq();
      if (FJavaConf.shouldTrackStats()) {
        addComputeTime(watch.end());
      }
      return;
    }

    int mid = size / 2;
    if (FJavaConf.shouldTrackStats()) {
      addComputeTime(watch.end());
    }
    FJavaSeq seq1 = new FJavaSeq(new FJavaMatrixMultiplication(A, B, C, mid,
        aRow, aCol, bRow, bCol, cRow, cCol), new FJavaMatrixMultiplication(A,
            B, C, mid, aRow, aCol + mid, bRow + mid, bCol, cRow, cCol));
    FJavaSeq seq2 = new FJavaSeq(new FJavaMatrixMultiplication(A, B, C, mid,
        aRow, aCol, bRow, bCol + mid, cRow, cCol + mid),
        new FJavaMatrixMultiplication(A, B, C, mid, aRow, aCol + mid, bRow
            + mid, bCol + mid, cRow, cCol + mid));
    FJavaSeq seq3 = new FJavaSeq(new FJavaMatrixMultiplication(A, B, C, mid,
        aRow + mid, aCol, bRow, bCol, cRow + mid, cCol),
        new FJavaMatrixMultiplication(A, B, C, mid, aRow + mid, aCol + mid,
            bRow + mid, bCol, cRow + mid, cCol));
    FJavaSeq seq4 = new FJavaSeq(new FJavaMatrixMultiplication(A, B, C, mid,
        aRow + mid, aCol, bRow, bCol + mid, cRow + mid, cCol + mid),
        new FJavaMatrixMultiplication(A, B, C, mid, aRow + mid, aCol + mid,
            bRow + mid, bCol + mid, cRow + mid, cCol + mid));
    seq1.runAsync(this);
    seq2.runAsync(this);
    seq3.runAsync(this);
    seq4.runSync(this);
    sync();
  }

  @Override
  public String toString() {
    return String.format("MMult: %d %d %d %d %d %d (%d)", aRow, aCol, bRow,
        bCol, cRow, cCol, size);
  }

  private void multiplySeq() {
    for (int j = 0; j < size; j += 2) {
      if(j % 16 == 0) this.tryLoadBalance();
      for (int i = 0; i < size; i += 2) {

        float[] a0 = A[aRow + i];
        float[] a1 = A[aRow + i + 1];

        float s00 = 0.0F;
        float s01 = 0.0F;
        float s10 = 0.0F;
        float s11 = 0.0F;

        for (int k = 0; k < size; k += 2) {

          float[] b0 = B[bRow + k];

          s00 += a0[aCol + k] * b0[bCol + j];
          s10 += a1[aCol + k] * b0[bCol + j];
          s01 += a0[aCol + k] * b0[bCol + j + 1];
          s11 += a1[aCol + k] * b0[bCol + j + 1];

          float[] b1 = B[bRow + k + 1];

          s00 += a0[aCol + k + 1] * b1[bCol + j];
          s10 += a1[aCol + k + 1] * b1[bCol + j];
          s01 += a0[aCol + k + 1] * b1[bCol + j + 1];
          s11 += a1[aCol + k + 1] * b1[bCol + j + 1];
        }

        C[cRow + i][cCol + j] += s00;
        C[cRow + i][cCol + j + 1] += s01;
        C[cRow + i + 1][cCol + j] += s10;
        C[cRow + i + 1][cCol + j + 1] += s11;
      }
    }
  }

}
