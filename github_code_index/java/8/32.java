import java.io.*;

public class Editdistance {

	String[] dna1;
	String[] dna2;
	public void read(){
		try{
			BufferedReader br = new BufferedReader(new FileReader("dna.txt"));
			dna1 = br.readLine().split("");
			dna2 = br.readLine().split("");
			br.close();
		}
		catch(IOException e){
			System.out.println("Error Reading");
		}
	}
	public void printDNA(){
		for (int i = 0; i < dna1.length; i++){
			System.out.print(dna1[i]);
		}
		System.out.println();
		for (int i = 0; i < dna2.length; i++){
			System.out.print(dna2[i]);
		}
	}
	public void dPTable(){
		int i;
		int j;
		int c;
		int row = dna1.length + 1;
		int col = dna2.length + 1;
		
		int[][] table = new int[row][col];
		for( i = 0; i < row; i++) table[i][0] = i;
		for( j = 0; j < col; j++) table[0][j] = j;
		
		for(i = 1; i < row; i++) {
			for(j = 1; j < col; j++){
				if(dna1[i-1].equals(dna2[j-1])) c = 0;
				else c = 1;
				table[i][j] = mini(table[i-1][j] + 1, table[i][j-1] + 1, table[i-1][j-1] + c );
			}
		}
		
		System.out.println("Edit Distance: " + table[row-1][col-1] + "\n\n");
		System.out.print("      ");
		for(i = 0; i < row -1; i++) System.out.print(dna1[i] + "  ");
		for(i = 0; i < row; i++){
			System.out.println();
			for(j = 0; j < col; j++){
				if(i == 0 && j == 0) System.out.print("   ");
				if(j == 0 && i > 0) System.out.print(dna2[i-1] + "  ");
				if (table [i][j] < 10) System.out.print(table[i][j]+ "  ");
				else System.out.print(table[i][j]+ " ");
			}
		}
		
	}
	public int mini(int a, int b, int c){
		if (a <= b && a <= c) return a;
		if (b <= a && b <= c) return b;
		if (c <= a && c <= b) return c;
		else return -20;
	}
}
