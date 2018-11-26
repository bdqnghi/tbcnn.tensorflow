import java.util.ArrayList;

/**
 * class of implementing BucketSort
 * 
 * crate N bucket based on how many element have
 * 
 * @author Chieh Lee
 * @version 06/01/2016
 * 
 */
public class Bucketsort {

	/**
	 * ArrayList<Double> this is going to be sorted
	 */
	ArrayList<Double> input;
	/**
	 * ArrayList<ArrayList<Double>> represent bucket use for BucketSort
	 */
	ArrayList<ArrayList<Double>> bucket;

	/**
	 * 
	 * generate the random double size N ArrayList and generate the
	 * corresponding size bucket
	 * 
	 * @param s
	 */
	private void generateArray(int s) {
		this.input = new ArrayList<Double>();
		for (int i = 0; i < s; i++) {
			this.input.add(Math.random());
		}
		bucket = new ArrayList<ArrayList<Double>>();
		for (int k = 0; k < s; k++) {
			bucket.add(new ArrayList<Double>());
		}
	}

	/**
	 * 
	 * assigning each element to the corresponding bucket base on N There's Nth
	 * bucket which their range are distributed equally by 1/N
	 * 
	 * @param n
	 */
	public void createBuckets(int n) {
		bucket = new ArrayList<ArrayList<Double>>();
		for (int k = 0; k < n; k++) {
			bucket.add(new ArrayList<Double>());
		}
		double nd = n;
		double range = 1 / nd;
		for (int i = 0; i < n; i++) {
			int idx = (int) ((Math.ceil((this.input.get(i) / range)) - 1));
			int curSize = bucket.get(idx).size();
			if (curSize == 0) {
				bucket.get(idx).add(this.input.get(i));
			} else {
				bucket.get(idx).add(this.input.get(i));
				QuickSort qSorter = new QuickSort();
				qSorter.input = bucket.get(idx);
				qSorter.sort(0, qSorter.input.size() - 1);
			}

		}

	}

	/**
	 * 
	 * flatten out the bucket into a single sorted ArrayList<Double>
	 * 
	 * @param n
	 * @return
	 */
	private ArrayList<Double> flatten(int n) {
		ArrayList<Double> f = new ArrayList<Double>();
		for (int i = 0; i < n; i++) {
			f.addAll(this.bucket.get(i));
		}
		return f;
	}

	/**
	 * 
	 * main
	 * 
	 * @param args
	 */
	public static void main(String[] args) {
		try {
			Bucketsort sorter = new Bucketsort();
			int n = Integer.parseInt(args[0]);
			sorter.generateArray(n);

			// actual sorting part
			long startTime = System.nanoTime();
			sorter.createBuckets(n);
			long endTime = System.nanoTime();
			System.out.println(endTime - startTime);

			if (n < 100) {
				System.out.println(sorter.flatten(n));
			}
		} catch (ArrayIndexOutOfBoundsException e) {
			System.out.println("pleae insert a valid input");

		}

	}
}
