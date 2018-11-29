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

	public static Integer bufferSize = 1024;		// inputbuffer and outputbuffer size setting
	public static Integer lexiconEndIndex = 0;	// save the start index for the current word
	public static Integer lexiconStartIndex = 0;	// save the end index for the current word
	public static ArrayList<String> lexiconBuffer = new ArrayList<String>();
	public static ArrayList<Integer> iiBuffer = new ArrayList<Integer>();

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		iiReader("data/all1.txt","data/final.txt");	// provide the input and output filename
		return;
	}

	// read the input inverted index file, call write function for each different term
	public static void iiReader(String inputFilename, String outputFilename) {			
		try {
			BufferedReader reader = new BufferedReader(new FileReader(inputFilename));
			String tmpstr = null;
			String[] tmpList;
			ArrayList<String> outBuffer = new ArrayList<String>();	// store the previous term and it's inverted index, used for comparing and writing
			
			while ((tmpstr = reader.readLine()) != null) {		// read line by line
				tmpList = tmpstr.split(":");						// split each line into two parts:    term and it's inverted index
				if(tmpList.length==0) {
					continue;
				}
				if(outBuffer.size() == 0) {					// initialize the outBuffer using the first term
					outBuffer.add(tmpList[0]);
					outBuffer.add(tmpList[1]);
					continue;
				}
				
				else {				
					if(outBuffer.get(0).equals((tmpList)[0])){	
						outBuffer.add(tmpList[1]);	// if current term is same with previous term, then add this part of inverted index into outBuffer 				
					}
					
					else {			// if new word, call iiBinWriter to write outBuffer, clear it, and reset the outBuffer with the new word
						iiWriterPrepare(outBuffer, outputFilename);
						outBuffer.clear();
						outBuffer.add(tmpList[0]);
						outBuffer.add(tmpList[1]);
					}
				}	
			}

			iiWriterPrepare(outBuffer, outputFilename);		// write the last part of outBuffer
			lexiconWriter("data/Lexicon.txt");
			iiBinWriter("data/final.txt");
			reader.close();	
			
		}catch (Exception e) {
			e.printStackTrace();
		}
	}
	
	
	// iiWriter is an ascii writer, use only in testing
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
	
	
	
	// this function is binary format writer
	// sort and merge several parts of content for the same term 
	// write the inverted index final file, call lexicon ascii writer for this term
	public static void iiWriterPrepare(ArrayList<String> outBuffer, String fileName) {
		try {
			
			Hashtable<Integer, String> sortTable = new Hashtable<Integer, String>();				// Dictionary for fast lookup during sorting
			
			String termContent = "";								// store the sorted content for inverted index
			String lexiconContent = outBuffer.get(0) + ":" + Integer.toString(lexiconStartIndex) + ",";		// store the content for lexicon writer
			
			ArrayList<Integer> sortList = new ArrayList<Integer>();
			
			for (Integer j = 1; j<outBuffer.size(); j++) {
				Integer headPageid = Integer.parseInt(outBuffer.get(j).split(",")[0]);		// get the first pageID for each string
				sortList.add(headPageid);							// add to a list for sorting
				sortTable.put(headPageid, outBuffer.get(j));			// add to dictionary
			}
			
			Collections.sort(sortList);						// sort the head
			
			for (Integer j = 0; j< sortList.size(); j++) {
				termContent += sortTable.get(sortList.get(j)); // piece the several doc,freq,doc,freq  |  doc,freq,doc,freq   together in ascending order
			}
			
			String[] tmpList = termContent.split(",");
			
			for (Integer j = 0; j<tmpList.length; j++) {		// for each number, write into file using binary format
				lexiconEndIndex += 1;
				iiBuffer.add(Integer.parseInt(tmpList[j]));
			}
			
			lexiconContent += Integer.toString(lexiconEndIndex-1);		// prepare content for lexicon writing
			lexiconContent += ",";
			lexiconContent += Integer.toString((lexiconEndIndex-lexiconStartIndex)/2);
			lexiconStartIndex = lexiconEndIndex;
			
			lexiconBuffer.add(lexiconContent);
			
			if(iiBuffer.size() > 10000000) {
				iiBinWriter(fileName);
				iiBuffer.clear();
			}
			
			if(lexiconBuffer.size() > 100000) {
				lexiconWriter("data/Lexicon.txt");	// call lexiconWriter to write into lexicon file
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
	
	public static void lexiconWriter(String fileName) {		// call once for each different term, append new content to the same file 
		try {															// in format -  term:headIndex,endIndex,number of pages
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



