import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.DataOutputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.OutputStreamWriter;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Hashtable;


public class merge {

	public static Integer bufferSize = 1024;		
	public static Integer lexiconEndIndex = 0;	
	public static Integer lexiconStartIndex = 0;	
	public static ArrayList<String> lexiconBuffer = new ArrayList<String>();
	public static ArrayList<Integer> iiBuffer = new ArrayList<Integer>();

	public static void main(String[] args) {
		
		iiReader("data/all1.txt","data/final.txt");	
		return;
	}

	
	public static void iiReader(String inputFilename, String outputFilename) {			
		try {
			BufferedReader reader = new BufferedReader(new FileReader(inputFilename));
			String tmpstr = null;
			String[] tmpList;
			ArrayList<String> outBuffer = new ArrayList<String>();	
			
			while ((tmpstr = reader.readLine()) != null) {		
				tmpList = tmpstr.split(":");						
				if(tmpList.length==0) {
					continue;
				}
				if(outBuffer.size() == 0) {					
					outBuffer.add(tmpList[0]);
					outBuffer.add(tmpList[1]);
					continue;
				}
				
				else {				
					if(outBuffer.get(0).equals((tmpList)[0])){	
						outBuffer.add(tmpList[1]);	
					}
					
					else {			
						iiWriterPrepare(outBuffer, outputFilename);
						outBuffer.clear();
						outBuffer.add(tmpList[0]);
						outBuffer.add(tmpList[1]);
					}
				}	
			}

			iiWriterPrepare(outBuffer, outputFilename);		
			lexiconWriter("data/Lexicon.txt");
			iiBinWriter("data/final.txt");
			reader.close();	
			
		}catch (Exception e) {
			e.printStackTrace();
		}
	}
	
	
	
	public static void iiWriter(ArrayList<String> outBuffer, String fileName) {
		try {
			File writename = new File(fileName);
			writename.createNewFile();
			OutputStreamWriter write = new OutputStreamWriter(new FileOutputStream(writename, true),"ASCII");
			BufferedWriter out = new BufferedWriter(write, bufferSize);
			
			Hashtable<Integer, String> sortTable = new Hashtable<Integer, String>();
			
			String termContent = outBuffer.get(0) + ":";
			ArrayList<Integer> sortList = new ArrayList<Integer>();
			
			for (Integer j = 1; j<outBuffer.size(); j++) {
				Integer headPageid = Integer.parseInt(outBuffer.get(j).split(",")[0]);
				sortList.add(headPageid);
				sortTable.put(headPageid, outBuffer.get(j));
			}
			
			Collections.sort(sortList);
			
			for (Integer j = 0; j< sortList.size(); j++) {
				termContent += sortTable.get(sortList.get(j));
			}
			out.write(termContent);
			out.write("\n");			
			out.close();
			
		}catch (Exception e) {
			e.printStackTrace();
		}
	}
	
	
	
	
	
	
	public static void iiWriterPrepare(ArrayList<String> outBuffer, String fileName) {
		try {
			
			Hashtable<Integer, String> sortTable = new Hashtable<Integer, String>();				
			
			String termContent = "";								
			String lexiconContent = outBuffer.get(0) + ":" + Integer.toString(lexiconStartIndex) + ",";		
			
			ArrayList<Integer> sortList = new ArrayList<Integer>();
			
			for (Integer j = 1; j<outBuffer.size(); j++) {
				Integer headPageid = Integer.parseInt(outBuffer.get(j).split(",")[0]);		
				sortList.add(headPageid);							
				sortTable.put(headPageid, outBuffer.get(j));			
			}
			
			Collections.sort(sortList);						
			
			for (Integer j = 0; j< sortList.size(); j++) {
				termContent += sortTable.get(sortList.get(j)); 
			}
			
			String[] tmpList = termContent.split(",");
			
			for (Integer j = 0; j<tmpList.length; j++) {		
				lexiconEndIndex += 1;
				iiBuffer.add(Integer.parseInt(tmpList[j]));
			}
			
			lexiconContent += Integer.toString(lexiconEndIndex-1);		
			lexiconContent += ",";
			lexiconContent += Integer.toString((lexiconEndIndex-lexiconStartIndex)/2);
			lexiconStartIndex = lexiconEndIndex;
			
			lexiconBuffer.add(lexiconContent);
			
			if(iiBuffer.size() > 10000000) {
				iiBinWriter(fileName);
				iiBuffer.clear();
			}
			
			if(lexiconBuffer.size() > 100000) {
				lexiconWriter("data/Lexicon.txt");	
				lexiconBuffer.clear();
			}
	
		}catch (Exception e) {
			e.printStackTrace();
		}	
	}
	
	
	public static void iiBinWriter(String fileName) {
		try{
			File writename = new File(fileName);
			writename.createNewFile();
			DataOutputStream out = new DataOutputStream(new FileOutputStream(fileName, true));
			
			for(Integer j = 0; j<iiBuffer.size(); j++) {
				out.writeInt(Integer.valueOf(iiBuffer.get(j)));
			}
			
			out.close();
		}catch (Exception e) {
			e.printStackTrace();
		}	
	}
	
	public static void lexiconWriter(String fileName) {		
		try {															
		File writename = new File(fileName);
		writename.createNewFile();
		OutputStreamWriter write = new OutputStreamWriter(new FileOutputStream(writename, true),"ASCII");
		BufferedWriter out = new BufferedWriter(write, bufferSize);
		for(Integer j = 0; j<lexiconBuffer.size(); j++) {
			out.write(lexiconBuffer.get(j));
			out.write("\n");
		}
		out.close();
		
		} catch (Exception e) {
			e.printStackTrace();
		}
}		

}



