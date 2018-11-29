import java.util.StringTokenizer;
import java.io.*;
import java.util.Hashtable;
import java.lang.Math.*;

class Levenshtein {
	//declaration table hash du fichier txt : le lexique (mot, lemme)
	public Hashtable<char[], char[]> HT; 
	//déclaration table hash (distance, mot)
	public Hashtable<char[], Integer> Dist;
	//public char[] candidat;
	public int distance_min;
	public int seuil_max;
	
	
	public Levenshtein(char[] motS, String fichier) {
		this.HT = new Hashtable<char[], char[]>();
		this.Dist = new Hashtable<char[], Integer>();
		this.distance_min = -1;
		//Cat.java
		BufferedReader br=null;
		String chaine;
		int longueur_motS = motS.length;
		int cout_insert = 1;
		int cout_suppress = 1;
		int cout_substitute;
		int[][] distance_tmp;
		
		try {
	         try {
	             br = new BufferedReader(new FileReader(fichier));
	             //pour chaque ligne du fichier entré en paramètre 
	             while ((chaine=br.readLine())!=null){
	            	StringTokenizer token = new StringTokenizer(chaine);
	            	char[] motL = token.nextToken().toCharArray();
	            	Integer lg_motL = motL.length;
	            	int longueur_motL = (int) lg_motL;
	            	HT.put(motL,token.nextToken().toCharArray());
	            	distance_tmp = new int[longueur_motS + 1][longueur_motL + 1];
	            	distance_tmp[0][0] = 0;
	            	for (int i = 1; i <= longueur_motS; i++) {
	            		distance_tmp[i][0] = distance_tmp[i-1][0] + cout_suppress;
	            	}
	            	for (int j = 1; j <= longueur_motL; j++) {
	            		distance_tmp[0][j] = distance_tmp[0][j-1] + cout_insert;
	            	}
	            	for (int i = 1; i <= longueur_motS; i++){
	            		for (int j = 1; j <= longueur_motL; j++){
	            			if(motS[i-1] == motL[j-1]) {
	            				cout_substitute = 0;
	            			}
	            			else {
	            				cout_substitute = 1;
	            			}
	            			int d1 = distance_tmp[i-1][j-1] + cout_substitute;
	            			int d2 = distance_tmp[i-1][j] + cout_suppress;
	            			int d3 = distance_tmp[i][j-1] + cout_insert;
	            			//calcul du di min
	            			int tmp = Math.min(d1, d2);
	            			distance_tmp[i][j] = Math.min(tmp, d3);
	            		}
	            	}
	            	//détermine le seuil pour la distance maximale acceptée entre le motS et le motL
	            	//lemmes candidats
	            	this.Dist.put(motL, distance_tmp[longueur_motS][longueur_motL]);
					//récupère la distance minimale 
	            	if((this.distance_min ==-1) || (distance_tmp[longueur_motS][longueur_motL] < this.distance_min)) {
	            		this.distance_min = distance_tmp[longueur_motS][longueur_motL];
	            	}
	             }
	         } 
	         catch(EOFException e) {
	              br.close();
	              }
	         } 
	    catch(FileNotFoundException e) {
	         System.out.println("fichier inconnu : " + fichier);
	         } 
	    catch(IOException e) {
	         System.out.println("IO Exception");
	         }
	    }
	
}
