package RR.prediction.clusterers.CanopySVM;

/**
 * This class is created in order to do all the necessary work for the Canopy clustering.
 * <p>
 * @author      Damir Olejar
 * @version     1.0
 * @version		WEKA 3.7
 */


import java.io.BufferedWriter;
import java.io.FileWriter;
import java.util.ArrayList;
import RR.prediction.classifiers.SVM.SVM;
import weka.clusterers.Canopy;
import weka.core.Attribute;
import weka.core.DenseInstance;
import weka.core.Instance;
import weka.core.Instances;

public class CanopyWork {


	/**
	 * Returns a 2D array of Instance, as a bucket-sort of clusters, to help separating and sorting the data as fast as possible
	 * 
	 * @param canopySize The number of clusters created by the Canopy clustering.
	 * @param csvSize The number of rows in a CSV file.
	 * @param data The CSV as Instances.
	 * @param canopy the instance of Canopy to decide which row from CSV (data) belongs to which cluster.
	 * @return Instance[][] the 2D matrix of inputted CSV split into clusters as Instance(s).
	 */
	
	public Instance[][] matrix(int canopySize, int csvSize, Instances data, Canopy canopy) {
		Instance[][] matrix = new Instance[canopySize][csvSize]; // [Canopy size][CSV size]
		try {

			// create the cluster maximum matrix for a bucket-sort
			// bucket-sort the instances from a CSV
			for (int y = 0; y < csvSize; y++) {
				Instance check = data.get(y);
				double classified = canopy.clusterInstance(check);

				matrix[(int) Math.round(classified)][y] = check;
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
		return matrix;
	}
	
	
	
	/**
	 * Models and saves the cluster-models to a directory
	 * 
	 * @param matrix The bucket-sorted Instances per cluster.
	 * @param outliers minimum number of data (exclusive) per cluster. Recommended minimum is 60.
	 * @param dir1 The directory where to save the clusters.
	 * @return ArrayList<String> The list of the modeled/saved clusters, with their paths.
	 */	
	public ArrayList<String> saveClusters(Instance[][] matrix, int outliers,String prefix, String dir1) {

		// save CSVs to a dir, and if CSV contains less than outliers, ignore it
		// as an outlier
		ArrayList<String> files = new ArrayList<String>();
		int filenameSuffix = 0;
		int depth = matrix[0].length;
		int width = matrix.length;
		for (int y = 0; y < width; y++) {
			ArrayList<Instance> cannopyN = new ArrayList<Instance>();
			int countData = 0;
			for (int r = 0; r < depth; r++) {
				Instance dbl = matrix[y][r];
				if (dbl != null) {
					cannopyN.add(dbl);
					countData++;
				}
			}

			if (countData > outliers) {
				writeInstanceToFile(dir1, prefix, "" + filenameSuffix, cannopyN);
				files.add(dir1 + prefix + filenameSuffix + ".csv");
				filenameSuffix++;
			}
		}
		return files;
	}
	

	/**
	 * Trains SVM from the clustered data
	 * 
	 * @param files The location of the CSVs to load.
	 * @param options The SVM options for training with the loaded CSV.
	 * @return ArrayList<String> The list of the modeled/saved clusters, with their paths.
	 */	
	public ArrayList<String> trainAndSaveClusters(ArrayList<String> files, String options) {
		ArrayList<String> svmFiles = new ArrayList<String>();
		for (int t = 0; t < files.size(); t++) {
			String filename = files.get(t);
			SVM svm = new SVM();
			svm.loadCSV(filename);
			svm.buildModel(options);
			String toSave = filename.substring(0, filename.lastIndexOf("."))
					+ ".model";
			svm.saveModelToFile(toSave);
			svmFiles.add(toSave);

		}
		return svmFiles;

	}
	
	
	/**
	 * Creates and Instance from the row of data, with the specified delimiters.
	 * 
	 * @param row The delimited row of data.
	 * @param delimiters The delimiters to use in order to separate the data in a row.
	 * @return Instance The converted row to Instance.
	 */	
	public Instance makeInstance(String row, String delimiters) {
		Instance ret = null;
		try {
			String[] split = row.split(delimiters);
			int sz = split.length;
			double[] raw = new double[split.length];
			for (int t = 0; t < sz; t++) {
				raw[t] = Double.parseDouble(split[t]);
			}
			ArrayList<Attribute> atts = new ArrayList<Attribute>(sz);
			for (int t = 0; t < sz + 1; t++) {
				atts.add(new Attribute("name" + t, t));
			}
			ret = (Instance) new DenseInstance(1.0, raw);
		} catch (Exception e) {
			e.printStackTrace();
		}
		return ret;
	}
	
	
	
	/**
	 * Writes Instances to CSV, Private method.
	 */		
	private void writeInstanceToFile(String dir, String prefix, String suffix, ArrayList<Instance> instanceArr) {
		try {
			BufferedWriter out = new BufferedWriter(new FileWriter(dir
					+ prefix + suffix + ".csv"));
			for (int t = 0; t < instanceArr.size(); t++) {
				Instance get = instanceArr.get(t);
				out.write(get.toString() + "\n");
			}
			out.close();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	
}
