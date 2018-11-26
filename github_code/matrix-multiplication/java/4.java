package ch.fhnw.prcpp;

public class Matrix {
	
	static {
		System.loadLibrary("MatrixCalculation");
	}

	double[] matrix;
	int height, width;
	
	public Matrix( int height, int width) {
		this.width = width;
		this.height = height;
		
		this.matrix = new double[height*width];
		
		for (int i = 0; i < this.matrix.length; i++) {
			this.matrix[i] = Math.random();
		}
	}
	
	public Matrix( int height, int width, double val) {
		this.width = width;
		this.height = height;
		
		this.matrix = new double[height*width];
		
		for (int i = 0; i < this.matrix.length; i++) {
			this.matrix[i] = val;
		}
	}
	
	public Matrix(int height, int width, double[] m) {
		if (height * width != m.length) throw new IllegalArgumentException("Illegal Matrix Dimensions!");
		this.height = height;
		this.width = width;
		this.matrix = m;
	}
	
	public Matrix multiply(Matrix b) {
		
		if (width != b.height) throw new IllegalArgumentException("Can't multiply with this matrix!");
		
		double[] r = new double[height*b.width];
		r = multiplyJ(matrix, b.matrix, r, height, width, b.width);

		return new Matrix(height,b.width, r);
	}
	
	public Matrix power(int k) {
		if (width != height) throw new IllegalArgumentException("Can't power with this matrix!");
		if (k < 1) throw new IllegalArgumentException("Can't power with this exponent!");
		if (k == 1) return this;
		else {
			double[] tmp = this.matrix;
			double[] empty = (new Matrix(height, width, 0)).matrix;
			for (int i=1; i < k; i++) {
				multiplyJ(tmp, this.matrix, empty, height, width, width);
			}
		return new Matrix(height, width, tmp);
		}
	}
	
	private double[] multiplyJ(double[] a, double[] b, double[] r, int ah, int aw, int bw) {
		double sum;
		for (int in = 0; in < ah; in++) {
			for (int il = 0; il < bw; il++) {
				
				int iR = in * bw + il; // Index of the result matrix
				sum = 0.0;
				for (int im = 0; im < aw; im++) {
					sum += a[in * aw + im] * b[im * bw + il];
				}
				r[iR] = sum;
			}				
		}
		return r;
	}
	
	public Matrix multiplyNative(Matrix matrix) {
		Matrix r = new Matrix(this.height, matrix.width, 0);
		multiplyC(this.matrix, matrix.matrix, r.matrix, this.height, this.width, matrix.width);
		return r;
	}
	
	public Matrix powerNative(int k) {
		if (width != height) throw new IllegalArgumentException("Can't power with this matrix!");
		if (k < 1) throw new IllegalArgumentException("Can't power with this exponent!");
		if (k == 1) return this;
		else {
			Matrix r = this;
			powerC(this.matrix, r.matrix, this.width, k);
		return r;
		}
	}
	
	native void powerC(double[] a, double[] r, int d, int k);
	
	/***
	 * Matrix-multiplication
	 * calculates a x b and returns result in r
	 * 
	 * @param a		First Matrix
	 * @param b		Second Matrix
	 * @param r		Result Matrix
	 * @param ah	Height of first Matrix
	 * @param aw	Width of first Matrix = Height of second Matrix
	 * @param bw	Width of second Matrix
	 */
	native void multiplyC(double[] a, double[] b, double[] r, int ah, int aw, int bw);
	
	public boolean equals(Matrix matrix) {
	
		boolean b = true;
		for (int i = 0; i < this.matrix.length; i++) {
			b = b && (this.matrix[i] == matrix.matrix[i]);
			}
		return b;
		
	}
	
	public String toString() {
		
		StringBuilder sb = new StringBuilder();
		
		for (int i = 0; i < this.matrix.length; i++) {
			sb.append(this.matrix[i]+" ");
			if ((i+1) % this.width == 0) sb.append("\n");
		}
		return sb.toString();
	}

}
