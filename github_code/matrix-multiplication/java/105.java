package com.figer.algorithm.algs4.utils;

import com.google.common.base.Preconditions;

/**
 * Created by figer on 16/03/2017.
 *
 * 矩阵向量表方法:https://zh.wikipedia.org/wiki/%E7%9F%A9%E9%99%A3%E4%B9%98%E6%B3%95
 */
public final class Matrix {
  /**
   * 向量点乘,一个向量使用一组实数表示为(x,y,z,...)
   */
  public static double dot(double[] x, double[] y){
    Preconditions.checkNotNull(x);
    Preconditions.checkNotNull(y);
    Preconditions.checkArgument(x.length == y.length);
    double result = 0;
    for (int i = 0; i < x.length; i++) {
      result += x[i]*y[i];
    }
    return result;
  }

  /**
   * 矩阵和矩阵之积
   *
   * A(m,n) * B(n,p) = C(m,p)
   *
   * 理解矩阵乘法:
   * http://www.ruanyifeng.com/blog/2015/09/matrix-multiplication.html
   */
  public static double[][] mult(double[][] a, double[][] b){
    Preconditions.checkNotNull(a);
    Preconditions.checkNotNull(b);
    Preconditions.checkNotNull(a.length == b[0].length);
    double c[][] = new double[a.length][b[0].length];
    for (int i = 0; i < c.length; i++) {
      double x[] = a[i];
      for (int j = 0; j < c[i].length; j++) {
        double y[] = new double[b.length];
        for (int k = 0; k < a[i].length; k++) {
          y[k] = b[k][j];
        }
        c[i][j] += dot(x, y);
      }
    }
    return c;
  }


  /**
   * 转置矩阵
   */
  public static double[][] transponse(double[][] a){
    Preconditions.checkNotNull(a);
    double aT[][] = new double[a[0].length][a.length];
    for (int i = 0; i < a.length; i++) {
      for (int j = 0; j < a[i].length; j++) {
        aT[j][i] = a[i][j];
      }
    }
    return aT;
  }

  /**
   *矩阵和向量之积 (m,n) * (n,1) = (m,1)
   */
  public static double[] mult(double[][] a, double[] y){
    Preconditions.checkNotNull(a);
    Preconditions.checkNotNull(y);
    int m = a.length;//行
    int n = a[0].length;//列
    Preconditions.checkArgument(y.length == n, String.format("Illegal matrix dimensions. x as a (%d,1) matrix, but matrix A column is %d", y.length, n));
    double[] temp = new double[m];

    for (int i = 0; i < m; i++) {
      double x[]  = a[i];
      temp[i] = dot(x, y);
    }
    return temp;
  }

  /**
   *向量和矩阵之积   as (1,n) * (n,m) = (1,m)
   */
  public static double[] mult(double[] x, double[][] a){
    Preconditions.checkNotNull(a);
    Preconditions.checkNotNull(x);

    int m = a.length;//行
    Preconditions.checkArgument(m == x.length, String.format("Illegal matrix dimensions. x as a (1,%d) matrix, but matrix A row is %d", x.length, m));

    double[] temp = new double[m];

    double[][] transponseA = transponse(a);

    for (int i = 0; i < m; i++) {
      double y[] = transponseA[i];
      temp[i] = dot(x, y);
    }
    return temp;
  }

  public static void main(String[] args) {
    double[] x = {1,1,3};
    double[] y = {2,2,2};
    System.out.println(dot(x, y));

    double a[][] = new double[][]{{1,0,2}, {-1, 3, 1}};
    double b[][] = new double[][]{{3,1}, {2,1}, {1,0}};
    double c[][] = mult(a, b);
    printMatrix(c);

    printMatrix(a);
    printMatrix(transponse(a));

    double vector[] = {1,1,3};
    double a1[][] = {{1,2,3},{5,6,7},{8,9,10},{11,12,13}};

    System.out.println("==================");
    printMatrix(a1);
    System.out.println("----");
    printMatrix(vector2RowMatrix(vector));
    System.out.println("----");
    System.out.println("矩阵和向量之积:");
    printMatrix(vector2RowMatrix(mult(a1, vector)));
    System.out.println("==================");

    double a2[][] = {{1,2,3},{5,6,7},{8,9,10}};
    printMatrix(vector2ColumnMatrix(vector));
    System.out.println("----");
    printMatrix(a2);
    System.out.println("----");
    System.out.println("向量和矩阵之积:");
    printMatrix(vector2ColumnMatrix(mult(vector, a2)));
    System.out.println("==================");
  }

  //(1,n)
  public static double[][] vector2ColumnMatrix(double[] x){
    double a[][] = new double[1][x.length];
    a[0] = x;
    return a;
  }

  //(n,1)
  public static double[][] vector2RowMatrix(double[] x){
    double a[][] = new double[x.length][1];
    for (int i = 0; i < x.length; i++) {
      a[i][0] = x[i];
    }
    return a;
  }

  private static void printMatrix(double[][] c){
    for (int i = 0; i < c.length; i++) {
      for (int j = 0; j < c[i].length; j++) {
        System.out.printf("%-9.0f", c[i][j]);
      }
      System.out.println();
    }
  }
}
