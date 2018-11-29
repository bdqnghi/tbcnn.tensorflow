package org.processmining.plugins.predictive_monitor.bpm.clustering;

import java.util.ArrayList;
import java.util.Enumeration;
import java.util.List;

import org.processmining.plugins.predictive_monitor.bpm.clustering.data_structures.Entry;
import org.processmining.plugins.predictive_monitor.bpm.clustering.data_structures.Operation;

import weka_predictions.core.Attribute;
import weka_predictions.core.Instance;
import weka_predictions.core.NormalizableDistance;


public class EditDistance  extends NormalizableDistance{

    
    // private List<String> initialString;
    //private List<String> finalString;
    private Entry entryTable[][];

   
   // public EditDistance(List<String> x, List<String> y) {
    public EditDistance() {
/*        this.initialString = x;
        this.finalString = y;*/
    }

   
    //public int computeEditDistance() {
    public int computeEditDistance(List<String> initialString, List<String> finalString) {
        entryTable = new Entry[finalString.size() + 1][initialString.size() + 1];
        entryTable[0][0] = new Entry(0, Operation.NOOP); // initial state
        
        for (int i = 0; i < finalString.size() + 1; i++) {
            for (int j = 0; j < initialString.size() + 1; j++) {
                if (i == 0 && j == 0) {
                    continue;
                }

                int minCost = Integer.MAX_VALUE;
                Operation minCostOp = null;

                if (i > 0 && j > 0 && initialString.get(j - 1).equals(finalString.get(i - 1))) {
                    int c = entryTable[i - 1][j - 1].getCost() + Operation.OK.cost;
                    if (c < minCost) {
                        minCost = c;
                        minCostOp = Operation.OK;
                    }
                }

                if (i > 0 && j > 0) {
                    int c = entryTable[i - 1][j - 1].getCost() + Operation.REPLACE.cost;
                    if (c < minCost) {
                        minCost = c;
                        minCostOp = Operation.REPLACE;
                    }
                }

                if (i > 0) {
                    int c = entryTable[i - 1][j].getCost() + Operation.INSERT.cost;
                    if (c < minCost) {
                        minCost = c;
                        minCostOp = Operation.INSERT;
                    }
                }

                if (j > 0) {
                    int c = entryTable[i][j - 1].getCost() + Operation.DELETE.cost;
                    if (c < minCost) {
                        minCost = c;
                        minCostOp = Operation.DELETE;
                    }
                }

                entryTable[i][j] = new Entry(minCost, minCostOp);
            }
        }
        
        return entryTable[finalString.size()][initialString.size()].getCost();
    }
    
    
    //public double computeNormalizedEditDistance() {
    	//int editDistance = computeEditDistance();	
    public double computeNormalizedEditDistance(List<String> initialString, List<String> finalString) {
    	int editDistance = computeEditDistance(initialString, finalString);
    	int max = Math.max(initialString.size(),finalString.size());
    	double normalizedEditDistance = 0.0;
    	if (max>0)
    		normalizedEditDistance = ((double) editDistance)/(initialString.size()+finalString.size());
		return normalizedEditDistance;
    }
   
    //public double computeNormalizedSimilarity() {
    	//double normalizedEditDistance = computeNormalizedEditDistance();
    public double computeNormalizedSimilarity( List<String> initialString, List<String> finalString) {
    	double normalizedEditDistance = computeNormalizedEditDistance(initialString, finalString);
		return (1-normalizedEditDistance);
    }


	public String getRevision() {
		// TODO Auto-generated method stub
		return null;
	}


	public String globalInfo() {
		// TODO Auto-generated method stub
		return null;
	}


	protected double updateDistance(double currDist, double diff) {
		System.out.println("******************************************* THIS FUNCTION SHOULD NOT BE CALLED ... PLEASE CHEKC IT ****************************");
		return 0;
	}
	
	  /**
	   * Calculates the distance between two instances.
	   * 
	   * @param first 	the first instance
	   * @param second 	the second instance
	   * @return 		the distance between the two given instances
	   */
	  public double distance(Instance firstInstance, Instance secondInstance) {
		  List<String> first = transformToStringList(firstInstance);
		  List<String> second = transformToStringList(secondInstance);
	    return computeNormalizedEditDistance(first, second);
	  }

	private List<String> transformToStringList(Instance firstInstance) {
		List<String> stringList = new ArrayList<String>();
		Enumeration<Attribute> attributeEnum = firstInstance.enumerateAttributes();
		while (attributeEnum.hasMoreElements()){
			Attribute attribute = attributeEnum.nextElement();
			stringList.add(firstInstance.stringValue(attribute));
		}
		return stringList;
	}


}
