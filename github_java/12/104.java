import java.nio.file.*;

public class Hamming {
	
	private static int[][] G_7_4 = {{ 1, 1, 0, 1},
									{ 1, 0, 1, 1},
									{ 1, 0, 0, 0},
									{ 0, 1, 1, 1},
									{ 0, 1, 0, 0},
									{ 0, 0, 1, 0},
									{ 0, 0, 0, 1}};
	private static int[][] H_7_4 = {{ 1, 0, 1, 0, 1, 0, 1},
									{ 0, 1, 1, 0, 0, 1, 1},
									{ 0, 0, 0, 1, 1, 1, 1}};
	
	public static void encode_7_4 (String inFile, String oFile){
		String inData = readFile(inFile);//string of raw unencoded bits
		int[][] tmpData = new int[4][1];//input to matrix multiplication
		int[] outData = new int[inData.length()*2];//encoded data array
		int[][] tmpOut = new int[7][1];//output from matrix multiplication
		int inPos, outPos;//position within data in and data out arrays
		inPos = outPos = 0;
		for(int i=0; i<(inData.length()/4); i++){//input data must have bit length divisible by 4 (should always)
			for(int j=0; j<4; j++){//create array to feed into matrix mult
				tmpData[j][0] = (int)(inData.charAt(inPos)-'0');
				inPos++;
System.out.printf("%d", tmpData[j][0]);
			} System.out.printf(" : tmpData\n");
			
			tmpOut = multiply(G_7_4, tmpData);

			outData[outPos] = 0;
			outPos++;
			for(int j=0; j<7; j++){//copy result of mult to outData
				outData[outPos] = tmpOut[j][0];
				outPos++;
System.out.printf("%d", tmpOut[j][0]);
			} System.out.printf(" : tmpOut\n");
		}
		//debug prints
		for(int i=0; i<inData.length(); i++){
			System.out.printf(Integer.toBinaryString(inData.charAt(i)-'0' & 0xFF));
		} System.out.printf(" : inData\n");
		for(int i=0; i<outData.length; i++){
			System.out.printf("%d", outData[i]);
		} System.out.printf(" : outData\n\n");
		
		writeFile(outData);
	}
	
	public static void decode_7_4 (String inFile, String oFile){
		String inData = readFile(inFile);//string of raw encoded bits
		int[][] checkData = new int[8][1];//data for matrix multiplication check
		int[][] checkOut = new int[3][1];//result of matrix mult
		int[] outData = new int[inData.length()/2];
		int checkSum, inPos = 0, outPos = 0;//inPos is position within encoded array
		for(int i=0; i<(inData.length()/8); i++){
			for(int j=0; j<8; j++){
				checkData[j][0] = (int)(inData.charAt(inPos)-'0');
				inPos++;
System.out.printf("%d", checkData[j][0]);
			}
System.out.println(" : checkData");
			
			checkOut = multiply(H_7_4, checkData);
			checkSum = 0;
			for(int j=0; j<3; j++){
				checkSum += checkOut[j][0]*(2^j);
			}
System.out.println(checkSum);
			if(checkSum != 0)//flip bit at position checkSum
				checkData[checkSum][0] = (checkData[checkSum+1][0])%2;
			
			for(int j=1; j<8; j++){
				if(j!=1 && j!=2 &&j!=4){
					outData[outPos] = checkData[j][0];
					outPos++;
System.out.printf("%d", checkData[j][0]);
				}
			} System.out.println();
		}
		
	}
	
	public static void encode_15_11 (String inFile, String oFile){
		
	}
	public static void decode_15_11 (String inFile, String oFile){
		
	}
	
	private static String readFile(String fileName){
		try{
			Path path = Paths.get(fileName);
			byte[] raw = Files.readAllBytes(path);
			String data = "";
			for(int i=0; i<raw.length; i++){
				data += Integer.toBinaryString(raw[i] & 0xFF);
			}
System.out.println("readFile: "+data);
			return data;
			
		} catch(Exception e) {
			e.printStackTrace();
			return null;
		}
	}
	
	private static void writeFile(int[] data){
		System.out.println("writeFile not yet defined");
	}
	
	//matrix multiplication adapted from code found at http://www.javawithus.com/programs/matrix-multiplication
	private static int[][] multiply(int[][] a, int[][] b) {
	       int rowsInA = a.length;
	       int columnsInA = a[0].length; // same as rows in B
	       int columnsInB = 1;
	       int[][] c = new int[rowsInA][columnsInB];
	       for (int i = 0; i < rowsInA; i++) {
	           for (int j = 0; j < columnsInB; j++) {
	               for (int k = 0; k < columnsInA; k++) {
	                   c[i][j] = (c[i][j] + a[i][k] * b[k][j])%2; //matrix position mod 2
	               }
	           }
	       }
	       return c;
	   }
}
