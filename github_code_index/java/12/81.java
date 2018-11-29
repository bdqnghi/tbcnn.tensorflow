package com.ikaver.aagarwal.seq;

import com.ikaver.aagarwal.common.FJavaConf;
import com.ikaver.aagarwal.common.problems.MatrixMultiplication;

public class SeqMatrixMultiplication implements MatrixMultiplication {

  public void multiply(float[][] A, float[][] B, float[][] result) {
    //assume a, b, c = (2^n x 2^n)
    multiply(A,B,result,A.length,0,0,0,0,0,0);
  }

  private void multiply(float [][]A, float[][]B, float[][]C, int size,
      int aRow, int aCol, int bRow, int bCol, int cRow, int cCol) {
    if(size <= FJavaConf.getMatrixMultiplicationSequentialThreshold()) {
      multiplySeq(A,B,C,size,
          aRow,aCol,bRow,bCol,cRow,cCol);
      return;
    }
    int mid = size/2;
    multiply(A, B, C, mid, aRow, aCol,     bRow,     bCol, cRow, cCol);
    multiply(A, B, C, mid, aRow, aCol+mid, bRow+mid, bCol, cRow, cCol);
    
    multiply(A, B, C, mid, aRow, aCol,     bRow,     bCol+mid, cRow, cCol+mid);
    multiply(A, B, C, mid, aRow, aCol+mid, bRow+mid, bCol+mid, cRow, cCol+mid);
    
    multiply(A, B, C, mid, aRow+mid, aCol,     bRow,     bCol,     cRow+mid, cCol);
    multiply(A, B, C, mid, aRow+mid, aCol+mid, bRow+mid, bCol, cRow+mid, cCol);
    
    multiply(A, B, C, mid, aRow+mid, aCol,     bRow,     bCol+mid, cRow+mid, cCol+mid);
    multiply(A, B, C, mid, aRow+mid, aCol+mid, bRow+mid, bCol+mid, cRow+mid, cCol+mid);
  }
  
  private void multiplySeq(float [][] A, float [][] B, float [][] C, int size,
      int aRow, int aCol, int bRow, int bCol, int cRow, int cCol) {
    for (int j = 0; j < size; j+=2) {
      for (int i = 0; i < size; i +=2) {

        float[] a0 = A[aRow+i];
        float[] a1 = A[aRow+i+1];

        float s00 = 0.0F; 
        float s01 = 0.0F; 
        float s10 = 0.0F; 
        float s11 = 0.0F; 

        for (int k = 0; k < size; k+=2) {

          float[] b0 = B[bRow+k];

          s00 += a0[aCol+k]   * b0[bCol+j];
          s10 += a1[aCol+k]   * b0[bCol+j];
          s01 += a0[aCol+k]   * b0[bCol+j+1];
          s11 += a1[aCol+k]   * b0[bCol+j+1];

          float[] b1 = B[bRow+k+1];

          s00 += a0[aCol+k+1] * b1[bCol+j];
          s10 += a1[aCol+k+1] * b1[bCol+j];
          s01 += a0[aCol+k+1] * b1[bCol+j+1];
          s11 += a1[aCol+k+1] * b1[bCol+j+1];
        }

        C[cRow+i]  [cCol+j]   += s00;
        C[cRow+i]  [cCol+j+1] += s01;
        C[cRow+i+1][cCol+j]   += s10;
        C[cRow+i+1][cCol+j+1] += s11;
      }
    }
  }

}
