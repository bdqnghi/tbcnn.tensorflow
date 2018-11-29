package correctiontool;

import java.util.ArrayList;
import java.util.Collections;

import org.apache.commons.lang3.StringUtils;
public class LevenshteinDistance {
	public String[] Data;
	
	public LevenshteinDistance(String [] data){
		Data = data;
	}
	
	class DataDistance implements Comparable<DataDistance>{
		private String ClassName;
		private int distance;
		
		public String getClassName() {
			return ClassName;
		}

		public void setClassName(String className) {
			ClassName = className;
		}

		public int getDistance() {
			return distance;
		}

		public void setDistance(int distance) {
			this.distance = distance;
		}
		
		public DataDistance(String data, int distance) {
			this.ClassName = data;
			this.distance = distance;
		}

		@Override
		public int compareTo(DataDistance comparableDistance) {
			int compareQuantity = ((DataDistance) comparableDistance).getDistance();
			return this.distance - compareQuantity;
		}
		
	}
	
	public String bestMatch(String candidate){
		String bestString = null ;
		ArrayList<DataDistance> Datadist = new ArrayList<DataDistance>();
		
		for (String modelData: Data){			
			DataDistance obj = new DataDistance(modelData, distance(candidate, modelData));
			Datadist.add(obj);	
		}
		Collections.sort(Datadist);
//		System.out.println(Datadist.get(0).getClassName());
	
		if(Datadist.size() != 0 ){
			if(Datadist.get(0).distance != 15000000){
				bestString = Datadist.get(0).getClassName();
			}
		}
		
		return bestString;
	}
	 public static Integer distance(String candidate, String modelData) {
	        candidate = candidate.toLowerCase();
	        modelData = modelData.toLowerCase();
	        // i == 0
	        int [] costs = new int [modelData.length() + 1];
	        for (int j = 0; j < costs.length; j++)
	            costs[j] = j;
	        for (int i = 1; i <= candidate.length(); i++) {
	            // j == 0; nw = lev(i - 1, j)
	            costs[0] = i;
	            int nw = i - 1;
	            for (int j = 1; j <= modelData.length(); j++) {
	                int cj = Math.min(1 + Math.min(costs[j], costs[j - 1]), candidate.charAt(i - 1) == modelData.charAt(j - 1) ? nw : nw + 1);
	                nw = costs[j];
	                costs[j] = cj;
	            }
	        }
//	        if (costs[modelData.length()] >= modelData.length()){
//	        	if(StringUtils.containsIgnoreCase(modelData,candidate)||StringUtils.containsIgnoreCase(candidate,modelData)){
//	        		return costs[modelData.length()];
//	        	}
//	        	return 15000000;
//	        }else{
//	        	return costs[modelData.length()];
//	        }
	        return costs[modelData.length()];
	        
	    }
	 
	    public static void main(String [] args) {
	        String [] data = { "kitten", "sitting", "saturday", "sunday", "rosettacode", "raisethysword" };
	        for (int i = 0; i < data.length; i += 2){
//	            System.out.println("distance(" + data[i] + ", " + data[i+1] + ") = " + distance(data[i], data[i+1]));
	            }
//	        System.out.println("distance(" + "Cow" + ", " + "Piglet" + ") = " + distance("cowsas", "cow"));
//	       System.out.println(new LevenshteinDistance(data).bestMatch("kitten")); 
	       new LevenshteinDistance(data).bestMatch("Sitting");
	    }

}
