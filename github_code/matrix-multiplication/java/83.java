import java.io.DataInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.nio.ByteBuffer;

public class Matrix {
	private double[][] matrix;
	private int rows;
	private int cols;
	private String filePath;

	Matrix(int rows, int cols) {
		this.rows = rows;
		this.cols = cols;
		filePath = null;
		matrix = new double[rows][cols];
	}

	Matrix(String filePath) {
		this.filePath = filePath;
		matrix = null;
		rows = 0;
		cols = 0;
	}

	Matrix(double[][] matrix) {
		this.matrix = matrix;
		rows = matrix.length;
		cols = matrix[0].length;
	}

	public double[][] getMatrix() {
		return matrix;
	}

	public void setValueOnPos(int row, int col, double value) {
		matrix[row][col] = value;
	}

	public double getValueOnPos(int row, int col) {
		return matrix[row][col];
	}

	public int getRows() {
		return rows;
	}

	public int getCols() {
		return cols;
	}

	public String getFilePath() {
		return filePath;
	}

	public void setFilePath(String filePath) {
		this.filePath = filePath;
	}

	public Matrix multiply(Matrix right) {
		Matrix result = new Matrix(new double[rows][right.getCols()]);
		MultiplicationTask task = new MultiplicationTask(this, right, result);

		for (int i = 0; i < rows; i++) {
			task.multiplyRowByColumn(this, right, result, i);
		}

		System.out.println("End of multiplication");
		return result;
	}

	public void load() throws FileNotFoundException, IOException {
		File file = new File(filePath);
		try (DataInputStream in = new DataInputStream(new FileInputStream(file))) {

			byte[] bs = new byte[(int) file.length()];

			while (in.read(bs) != -1) {
			}

			ByteBuffer byteBuffer = ByteBuffer.wrap(bs);
			this.rows = byteBuffer.getInt();
			this.cols = byteBuffer.getInt();
			
			double[] doubles = new double[bs.length / 8];
			for (int i = 0; i < doubles.length; i++) {
				doubles[i] = byteBuffer.getDouble(i * 8);
			}

			double[][] m = new double[this.rows][this.cols];
			int cnt = 1;
			for (int i = 0; i < this.rows; i++) {
				for (int j = 0; j < this.cols; j++) {
					if (cnt == doubles.length)
						break;
					m[i][j] = doubles[cnt];
					cnt++;
				}
			}
			this.matrix = m;
		}
	}

	public void print() {
		System.out.print("array[" + rows + "][" + cols + "] = {");
		for (int i = 0; i < 2; i++) {
			System.out.print("{");
			for (int j = 0; j < cols; j++) {

				System.out.print(" " + matrix[i][j] + ",");
			}
			System.out.println("} ");
		}
		System.out.println("}");
	}

}
