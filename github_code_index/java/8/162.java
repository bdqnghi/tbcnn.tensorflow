import java.util.ArrayList;
//import java.util.HashSet;
//import java.util.Set;

public class Levenshtein {
	public static int Calculate(ArrayList<String> str1, ArrayList<String> str2) {
		double diff = (double) Math.abs(str1.size() - str2.size())
				/ (str1.size() > str2.size() ? str1.size() : str2.size());
		if (str1.size() >= str2.size()) {
			if (str1.size() <= 10 && str2.size() <= 10 || diff <= 0.25)
				return LevenshteinDistance(str2, str1, str2.size() - 1, str1.size() - 1);
			else
				return 0;
		} else {
			if (str1.size() <= 10 && str2.size() <= 10 || diff <= 0.25)
				return LevenshteinDistance(str1, str2, str1.size() - 1, str2.size() - 1);
			else
				return 0;
		}
	}

	private static int LevenshteinDistance(ArrayList<String> minstr, ArrayList<String> maxstr, int minlength,
			int maxlength) {
		double left_top, top, left;
		double LevenshteinDistance = (double) maxlength * (100 - Application.getRate()) / 100;
		double[] matrix_before = new double[maxlength + 1];
		double[] matrix_after = new double[maxlength + 1];
		// System.out.print(matrix_before[0] + " ");
		for (int i = 1; i <= maxlength; i++) {
			matrix_before[i] = (double) i;
			// System.out.print(matrix_before[i] + " ");
		}
		// System.out.println();
		Application.getWithout().getAndAdd(minlength);
		for (int i = 1; i <= minlength; i++) {
			matrix_after[0] = i;
			// System.out.print(matrix_after[0] + " ");
			for (int j = 1; j <= maxlength; j++) {
				left = matrix_after[j - 1];
				top = matrix_before[j];
				left_top = matrix_before[j - 1];
				double min = left > top ? top : left;
				if (min >= left_top) {
					// matrix_after[j] = left_top + (flag ? (str1.get(i).equals(str2.get(j)) ? 0 :
					// 1) : GetWeight(str1.get(i), str2.get(j)));
					matrix_after[j] = left_top + (minstr.get(i).equals(maxstr.get(j)) ? 0 : 1);
				} else {
					matrix_after[j] = min + 1;
				}
				// System.out.print(matrix_after[j] + " ");
			}
			if (Application.isUseImport() && matrix_after[maxlength - minlength + i] > LevenshteinDistance) {
				Application.getWith().getAndAdd(i);
				return 0;
			}
			matrix_before = matrix_after;
			matrix_after = new double[maxlength + 1];
			// System.out.println();
		}
		Application.getWith().getAndAdd(minlength);
		LevenshteinDistance = matrix_before[maxlength];
		return (int) ((1 - (double) LevenshteinDistance / maxlength) * 100);
	}

	// private static double GetWeight(String str1 , String str2) {
	// Set<String> str1set = Application.getSynonym().get(str1);
	// Set<String> str2set = Application.getSynonym().get(str2);
	// Set<String> result = new HashSet<>();
	// if(str1set ==null || str2set == null)
	// return str1.equals(str2) ? 0f : 1f;
	// double weight = 0f;
	// if(str1set.size() > 1 && str2set.size() > 1)
	// weight = 0.4f;
	// else
	// weight = 0.2f;
	// result.addAll(str1set);
	// result.retainAll(str2set);
	// if(result.size()>0)
	// return weight;
	// return 1f;
	// }
}