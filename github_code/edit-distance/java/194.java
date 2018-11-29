package algorithm.levenshtein;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Enumeration;
import java.util.Hashtable;
import java.util.List;

import data.Dot;




/*
 * Classe permettant de definir et exploiter la distance de Levenshtein afin
 * de l'exploiter pour la reconnaissance
 */
public class Levenshtein {

	private Hashtable<String, String> strings; //cles=exemples d'entrainement, elements=classes
	private DistancesTable distances; //table permettant de precalculer les distances
	private int[][] costTable; //table avec des couts prefixes
	private boolean withCostTable; //utilisation ou non de la table de couts prefixes

	public Levenshtein(){
		strings = new Hashtable<String, String>();
		withCostTable = false;
	}
	
	public Levenshtein(boolean withCostTable){
		strings = new Hashtable<String, String>();
		this.withCostTable = withCostTable;
		costTable = new int[8][8];
		for(int i = 0; i < 8; i++)
			for(int j = 0; j < 8; j++){
				int tmp = Math.abs(i-j);
				if(tmp == 5) tmp = 3;
				if(tmp == 6) tmp = 2;
				if(tmp == 7) tmp = 1;
				costTable[i][j] = tmp;
			}
	}

	/*
	 * pre: -
	 * post: renvoie le min de trois nombres
	 */
	private int minimum (int a, int b, int c) {
		int mi;

		mi = a;
		if (b < mi) {
			mi = b;
		}
		if (c < mi) {
			mi = c;
		}
		return mi;

	}


	/*
	 * pre: s et t deux strings de taille non nulle
	 * post: la distance de Levenshtein entre le string s et t est renvoyee
	 */
	public double distance (String s, String t) {
		int d[][]; // matrice permettant de calculer la distance de Levenshtein suivant la programmation dynamique
		int n; // longueur de s
		int m; // longueur de t
		int i; 
		int j; 
		char s_i; // ieme caractere de s
		char t_j; // jeme caractere de t
		int cost; // cout

		n = s.length ();
		m = t.length ();
		if (n == 0) {
			return m;
		}
		if (m == 0) 
			return n;
		
		d = new int[n+1][m+1];

		for(i = 0; i <= n; i++) 
			d[i][0] = i;

		for(j = 0; j <= m; j++)
			d[0][j] = j;

		for (i = 1; i <= n; i++) {
			s_i = s.charAt (i - 1);
			for (j = 1; j <= m; j++) {
				t_j = t.charAt (j - 1);
				if (s_i == t_j) 
					cost = 0;
				else{
					cost = 1;
					if(withCostTable)
						cost = costTable[((int)s_i)-48][((int)t_j)-48];
				}
				d[i][j] = minimum (d[i-1][j]+1, d[i][j-1]+1, d[i-1][j-1] + cost);
			}
		}
		
		return d[n][m];
	}

	/*
	 * pre: s et t deux strings de taille non nulle
	 * post: la distance de Levenshtein normalisee 1 entre le string s et t est renvoyee
	 */
	public double normalizedDistance1(String s, String t){
		return distance(s,t)/Math.max(s.length(),t.length());
	}

	/*
	 * pre: s et t deux strings de taille non nulle
	 * post: la distance de Levenshtein normalisee 2 entre le string s et t est renvoyee
	 */
	public double normalizedDistance2(String s, String t){
		return distance(s,t)/(s.length() + t.length());
	}

	/*
	 * pre: s et t deux strings de taille non nulle
	 * post: la distance de Levenshtein normalisee 3 entre le string s et t est renvoyee
	 */
	public double normalizedDistance3(String s, String t){
		double dist = distance(s,t);
		return dist*2/(s.length() + t.length() + dist);
	}

	/*
	 * pre: s et t deux strings de taille non nulle
	 * 		0 <= normalisation <= 3
	 * post: la distance de Levenshtein non normalisee, normalisee 1, normalisee 2 et normalisee 3
	 * 		 entre le string s et t est renvoyee respectivement en fonction des normalisation 0, 1, 2 et 3 
	 */
	public double distance(String s, String t, int normalisation){
		switch(normalisation){
		case 0: return distance(s,t);
		case 1: return normalizedDistance1(s, t);
		case 2: return normalizedDistance2(s, t);
		case 3: return normalizedDistance3(s, t);
		default: return -1;
		}
	}

	/*
	 * pre: -
	 * post: gesture est ajoute aux exemples d'entrainement
	 */
	public void addTemplate(String name, List<Dot> gesture){
		strings.put(Utils.transform(gesture),name);
	}

	/*
	 * pre: -
	 * post: gesture est ajoute aux exemples d'entrainement
	 */
	public void addTemplate(String name, String gesture){
		strings.put(gesture, name);
	}

	/*
	 * pre: -
	 * post: gesture est ajoute aux exemples d'entrainement
	 */
	public void removeTemplate(String gesture){
		strings.remove(gesture);
	}


	public void preCompute(){
		preCompute(0);
	}

	/*
	 * pre: -
	 * post: les distances entre les exemples d'entrainement sont precalcules 
	 * 		 en fonction de la normalisation
	 */
	public void preCompute(int normalisation){
		distances = new DistancesTable();
		double distance;
		Enumeration<String> e1 = strings.keys();
		Enumeration<String> e2;
		for(int i = 0; i < strings.size(); i++){
			String key1 = e1.nextElement();
			e2 = strings.keys();
			for(int j = 0; j <= i; j++){
				String key2 = e2.nextElement();
				distance = distance(key1, key2, normalisation);
				distances.put(key1, key2, distance);
				distances.put(key2, key1, distance);
			}
		}
	}

	public String recognize(String gesture){
		return recognize(gesture, 0, 1);
	}

	/*
	 * pre: gesture un string de taille non nulle
	 * 		0 <= normalisation <= 3
	 * post: la classe de gesture est renvoyee en fonction de la normalisation
	 */
	public String recognize(String gesture, int normalisation){
		double minScore = Integer.MAX_VALUE;
		String toReturn = "";
		Enumeration<String> e = strings.keys();
		while(e.hasMoreElements()){
			String key = e.nextElement();
			double dist;
			if(distances != null){
				double d = distances.get(key,gesture);
				if(d != -1.0)
					dist = d;
				else
					dist = distance(key,gesture,normalisation);
			}
			else
				dist = distance(key,gesture,normalisation);
			if(dist < minScore){
				minScore = dist;
				toReturn = strings.get(key);
			}
		}
		return toReturn;
	}
	
	/*
	 * pre: gesture un string de taille non nulle
	 * 		0 <= normalisation <= 3
	 * 		knn >= 1
	 * post: la classe de gesture est renvoyee en fonction de la normalisation
	 * 		 et du nombre knn de plus proches voisins
	 */
	public String recognize(String gesture, int normalisation, int knn){
		List<Result> results = new ArrayList<Result>();
		Enumeration<String> e = strings.keys();
		while(e.hasMoreElements()){
			String key = e.nextElement();
			double dist;
			if(distances != null){
				double d = distances.get(key,gesture);
				if(d != -1.0)
					dist = d;
				else
					dist = distance(key,gesture,normalisation);
			}
			else
				dist = distance(key,gesture,normalisation);
			results.add(new Result(key,dist));
			}
		Collections.sort(results, new Result());
		Hashtable<String, Integer> numberItemByClass = new Hashtable<String, Integer>();
		for(int i = 0; i < knn; i++){
			String classe = strings.get(results.get(i).name);
			if(numberItemByClass.get(classe) == null)
				numberItemByClass.put(classe,1);
			else
				numberItemByClass.put(classe, numberItemByClass.get(classe)+1);
		}
		Enumeration<String> e2 = numberItemByClass.keys();
		String toReturn = e2.nextElement();
		while(e2.hasMoreElements()){
			String key = e2.nextElement();
			if(numberItemByClass.get(key) > numberItemByClass.get(toReturn))
				toReturn = key;
		}
		
		return toReturn;
	}
	
	
	/*
	 * pre: gesture un string de taille non nulle
	 * 		0 <= normalisation <= 3
	 * 		knn >= 1
	 * post: les classes de gesture sont renvoyees en fonction de la normalisation
	 * 		 et pour chacun des 1 -> knn plus proches voisins
	 */
	public String[] recognizeForAllKnn(String gesture, int normalisation, int knn){
		List<Result> results = new ArrayList<Result>();
		double minScore = Integer.MAX_VALUE;
		Enumeration<String> e = strings.keys();
		while(e.hasMoreElements()){
			String key = e.nextElement();
			double dist;
			if(distances != null){
				double d = distances.get(key,gesture);
				if(d != -1.0)
					dist = d;
				else
					dist = distance(key,gesture,normalisation);
			}
			else
				dist = distance(key,gesture,normalisation);
			results.add(new Result(key,dist));
		}
		Collections.sort(results, new Result());
		Object[] numberItemByClass = new Object[knn];
		for(int i = 0; i < knn; i++)
			numberItemByClass[i] = new Hashtable<String, Integer>();
		for(int i = 0; i < knn; i++){
			for(int j = 0; j <= i; j++){
				String classe = strings.get(results.get(j).name);
				if(((Hashtable)numberItemByClass[i]).get(classe) == null)
					((Hashtable)numberItemByClass[i]).put(classe,1);
				else
					((Hashtable)numberItemByClass[i]).put(classe, ((Hashtable<String, Integer>)numberItemByClass[i]).get(classe)+1);
			}
		}
		String[] toReturn = new String[knn];
		for(int i = 0; i < knn; i++){
			Enumeration<String> e2 = ((Hashtable<String, Integer>)numberItemByClass[i]).keys();
			toReturn[i] = e2.nextElement();
			while(e2.hasMoreElements()){
				String key = e2.nextElement();
				if(((Hashtable<String, Integer>)numberItemByClass[i]).get(key) > ((Hashtable<String, Integer>)numberItemByClass[i]).get(toReturn[i]))
					toReturn[i] = key;
			}
		}
		return toReturn;
	}

	public String closerGesture(String gesture){
		return closerGesture(gesture, 0);
	}

	
	/*
	 * pre: gesture un string de taille non nulle
	 * 		1 <= normalisation <= 4
	 * post: la geste le plus proche de gesture est renvoyee en fonction 
	 * 		 de la normalisation et du nombre knn de plus proches voisins
	 */
	public String closerGesture(String gesture, int normalisation){
		double minScore = Integer.MAX_VALUE;
		String toReturn = "";
		Enumeration<String> e = strings.keys();
		while(e.hasMoreElements()){
			String key = e.nextElement();
			double dist;
			if(distances != null){
				double d = distances.get(key,gesture);
				if(d != -1.0)
					dist = d;
				else
					dist = distance(key,gesture,normalisation);
			}
			else
				dist = distance(key,gesture,normalisation);
			if(dist < minScore){
				minScore = dist;
				toReturn = key;
			}
		}
		return toReturn;
	}



	public static void main (String[] args){
		System.out.println(new Levenshtein().distance("122355552222","123555321777"));
	}

}