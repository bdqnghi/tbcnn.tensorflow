package RR.prediction.clusterers.CanopySVM;




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


	
	
	public Instance[][] matrix(int canopySize, int csvSize, Instances data, Canopy canopy) {
		Instance[][] matrix = new Instance[canopySize][csvSize]; 
		try {

			
			
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
	
	
	
		
	public ArrayList<String> saveClusters(Instance[][] matrix, int outliers,String prefix, String dir1) {

		
		
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
