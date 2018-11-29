package com.santhosh.hackerrank.algorithm.morganstanleycontest;

import java.math.BigInteger;
import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;
import java.util.StringTokenizer;

import com.santhosh.hackerrank.algorithm.sorting.ShellSortString;

public class SortString4WithShellSort {
public static void sortStringArray(String[] inputList,int tokensInList,int listCount,int key,boolean isReverse,boolean isNumeric) throws InterruptedException{
	ShellSortString sort=new ShellSortString();
	
		
		String[] keyList=new String[listCount];
		
		Map<String,Integer> keyListPositions=new HashMap<>();
		
		for(int i=0;i<listCount;i++) {
			keyList[i]=inputList[(i*tokensInList)
			                       +(key-1)];
			keyListPositions.put(keyList[i], i);
		}
		//keylist sort
		sort.shellSort(keyList,isNumeric);
		
		if(isReverse) {
			for(int i=keyList.length-1;i>=0;i--) {
		       	 String keyValue=keyList[i];
		       	
		       	 int keyPos=keyListPositions.get(keyValue);
		       	 for (int k=(keyPos)*tokensInList;k<((keyPos+1)*tokensInList);k++) {
		       		System.out.print(inputList[k]+" ");
					inputList[k]="-1";
		       	 }
		       	System.out.println();
			}  
		}
		else {
			for(int i=0;i<keyList.length;i++) {
		       	 String keyValue=keyList[i];
		       	 int keyPos=keyListPositions.get(keyValue);
		       	 for (int k=(keyPos)*tokensInList;k<((keyPos+1)*tokensInList);k++) {
		       		System.out.print(inputList[k]+" ");
					inputList[k]="-1";
		       	 }
		       	System.out.println();
		       	/*for(int k=0;k<listCount;k++) {
					if(inputList[(k*tokensInList)
			                       +(key-1)].equals(keyValue)) {
						for(int j=(k*tokensInList);j<(k+1)*tokensInList;j++) {
							System.out.print(inputList[j]+" ");
							inputList[j]="-1";
						}
						System.out.println();
					}
				}*/
			}  
		}
	}
	public static int compare(String key1,String key2,boolean isNumericCompare) {
		if(isNumericCompare) {
		  return compareStringsNumeric(key1,key2);	
		}
		
		return key1.compareTo(key2);		
	}
	
	public static int compareStringsNumeric(String a,String b){
		if(a.length()<b.length()){
			return -1;
		}
		else if(a.length()>b.length()){
			return 1;
		}
		 return new BigInteger(a).compareTo(new BigInteger(b));
	}
	
	/**
	 * @param argss
	 * @throws InterruptedException 
	 * @throws NumberFormatException 
	 */
	public static void main(String[] args) throws NumberFormatException, InterruptedException {
		Scanner scan=new Scanner(System.in);
        int numberOfList=Integer.parseInt(scan.nextLine().trim());
        StringTokenizer listTokenizer=null;
        @SuppressWarnings("unchecked")
		String[] numberList=new String[numberOfList*(10^5)];
        int counter=0;
        
        for(int i=0;i<numberOfList;i++) {       
        	 String stringList=scan.nextLine();
        	 listTokenizer =new StringTokenizer(stringList);
        	 while(listTokenizer.hasMoreTokens()) {
        		 numberList[counter]=(listTokenizer.nextToken());
        		 counter++;
        
        	 }
        	 
        }
        String options=scan.nextLine();
        listTokenizer =new StringTokenizer(options);
        String key=listTokenizer.nextToken();
        String isReverse=listTokenizer.nextToken();
        String comparisonType=listTokenizer.nextToken();
        int tokensInString=counter/numberOfList;
        
        
        sortStringArray(numberList,tokensInString,numberOfList,Integer.parseInt(key),Boolean.parseBoolean(isReverse),(comparisonType.equals("numeric")?true:false));
	}

}
