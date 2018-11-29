/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package fr.univ_tours.li.jaligon.falseto.Similarity.Session;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.io.Writer;
import fr.univ_tours.li.jaligon.falseto.Generics.Generics;
import fr.univ_tours.li.jaligon.falseto.Generics.Generics.EditDistanceOperatorType;
import static fr.univ_tours.li.jaligon.falseto.Generics.Generics.EditDistanceOperatorType.DELETION;
import static fr.univ_tours.li.jaligon.falseto.Generics.Generics.EditDistanceOperatorType.INSERTION;
import static fr.univ_tours.li.jaligon.falseto.Generics.Generics.EditDistanceOperatorType.MATCH_MISMATCH;
import static fr.univ_tours.li.jaligon.falseto.Generics.Generics.EditDistanceOperatorType.STOP;
import fr.univ_tours.li.jaligon.falseto.QueryStructure.QuerySession;
import fr.univ_tours.li.jaligon.falseto.Similarity.Query.Similarity;

/**
 *
 * @author Elisa
 */
public class SmithWaterman extends SessionComparison {

    public double[][] similarityMatrix; //TODO set private
    private Matrix matrix;
    //private double[][] costMatrix;
    public CellInfoEditDistance[][] costMatrix; //TODO set private
    protected double openingGapCost;
    protected double extendingGapCost;
    private double thre;

    public SmithWaterman(Matrix similarityMatrix, double openingGapcost, double extendingGapCost, QuerySession s1, QuerySession s2, double thre, double alpha, double beta, double gamma) {
        super(s1, s2, thre, alpha, beta, gamma);
        this.similarityMatrix = similarityMatrix.getScores();
        this.openingGapCost = openingGapcost;
        this.extendingGapCost = extendingGapCost;
        this.row += 1;
        this.column += 1;
        //this.costMatrix=new double[n][m];
        this.costMatrix = new CellInfoEditDistance[row][column];
        this.matrix = similarityMatrix;
        this.thre = thre;
    }

    public Similarity computeSimilarity() {
        int columnIndex = 0;
        int rowIndex = 0;
        
        CellInfoEditDistance ci = new CellInfoEditDistance(Integer.MIN_VALUE, 0, 0, Generics.EditDistanceOperatorType.NOOPERATION, 0);

        int i, j = 0;
        //Initialize matrix cost
        for (i = 0; i < row; i++) // initialize the first column
        {
            costMatrix[i][0] = new CellInfoEditDistance(0, i, 0, Generics.EditDistanceOperatorType.STOP, similarityMatrix[i][0]);
        }
        //costMatrix[i][0]=0;
        for (j = 0; j < column; j++) // initialize the first row
        //costMatrix[0][j]=0;
        {
            costMatrix[0][j] = new CellInfoEditDistance(0, 0, j, Generics.EditDistanceOperatorType.STOP, similarityMatrix[0][j]);
        }
        for (i = 1; i < row; i++)// for each row
        {
            for (j = 1; j < column; j++) // for each column
            {
                /*costMatrix[i][j]=Math.max(
                 costMatrix[i-1][j-1] + similarityMatrix[i][j],
                 Math.max(computeMaxOnRow(i,j),
                 Math.max(computeMaxOnColumn(i,j),0)));*/
                costMatrix[i][j] = updateFormula(i, j);
                if (costMatrix[i][j].getSimilarity() >= ci.getSimilarity()) {
                    columnIndex = j;
                    rowIndex = i;
                    ci = new CellInfoEditDistance(costMatrix[i][j].getSimilarity(), i, j, Generics.EditDistanceOperatorType.NOOPERATION, similarityMatrix[i][j]);
                }

            }
        }
        //printMatrixLight(Generics.MATRIX_SMITHWATERMAN_FILE);

        //System.out.print("Column Index : " + columnIndex+" ");
        //System.out.print("Row Index : " + rowIndex);


        //Normalization
        normalize(ci);
        return ci;
    }

    private Similarity normalize(CellInfoEditDistance ci) {
        double sumRho = 0;
        int minLength = Math.min(this.s1.size(), this.s2.size());
        for (int k = 0; k < minLength; k++) {
            sumRho += this.matrix.increasing_function(k, k);
        }
        //System.out.println(ci.getSimilarity() + " " + sumRho);
        double normalizedSimilarity = ci.getSimilarity() / ((1.0 - thre) * sumRho);

        //System.out.println(normalizedSimilarity);
        ci.setSimilarity(normalizedSimilarity);

        return ci;

    }

    private void printMatrix(String fileName) {
        Writer output = null;

        try {
            File file = new File(fileName);
            output = new BufferedWriter(new FileWriter(file));
            for (int i = 0; i < row; i++) {
                for (int j = 0; j < column; j++) {
                    output.write(String.valueOf(costMatrix[i][j].getQuerySimilarity()) + " " + String.valueOf(costMatrix[i][j].getSimilarity()) + " " + costMatrix[i][j].getOperator() + ", ");
                }
                //output.write(d[i][j]+", ");
                output.write("\n");
            }
            output.close();
        } catch (IOException e) {
            System.out.print(e);
        }
    }
    
    private void printMatrixLight(String fileName) {
        Writer output = null;

        try {
            File file = new File(fileName);
            output = new BufferedWriter(new FileWriter(file));
            for (int i = 0; i < row; i++) {
                for (int j = 0; j < column; j++) {
                    output.write(String.valueOf((double)Math.round(costMatrix[i][j].getQuerySimilarity()*10000)/10000) 
                            + " " + String.valueOf((double)Math.round(costMatrix[i][j].getSimilarity()*10000)/10000) 
                            + " " + costMatrix[i][j].getOperator().toString().substring(0, 3) + "\t");
                }
                //output.write(d[i][j]+", ");
                output.write("\n");
            }
            output.close();
        } catch (IOException e) {
            System.out.print(e);
        }
    }

    public CellInfoEditDistance updateFormula(int row, int column) {
        //CellInfo ci=new CellInfo();
        double diagonal = (double) costMatrix[row - 1][column - 1].getSimilarity() + similarityMatrix[row][column];
        double left = computeMaxOnRow(row, column);
        double up = computeMaxOnColumn(row, column);
        double stop = 0;
        EditDistanceOperatorType op = EditDistanceOperatorType.MATCH_MISMATCH;
        double max = -1;
        if (diagonal >= max) {
            op = EditDistanceOperatorType.MATCH_MISMATCH;
            max = diagonal;
        }
        if (left > max) {
            op = EditDistanceOperatorType.INSERTION;
            max = left;
        }
        if (up > max) {
            op = EditDistanceOperatorType.DELETION;
            max = up;
        }
        if (stop > max) {
            op = EditDistanceOperatorType.STOP;
            max = stop;
        }


        return new CellInfoEditDistance(max,
                row,
                column,
                op,
                similarityMatrix[row][column]);
    }

    public double getPenalityGap(int numberOfGap) {
        //Affine penality gap
        return (double) (openingGapCost + (double) extendingGapCost * numberOfGap);
    }

    public double computeMaxOnRow(int i, int j) {
        double max = -Float.MIN_VALUE;
        for (int k = i; k > 0; k--) {
            double h = (double) (costMatrix[i - k][j].getSimilarity() + getPenalityGap(k));
            if (h > max) {
                max = h;
            }
        }
        return max;
    }

    public double computeMaxOnColumn(int i, int j) {
        double max = -Float.MIN_VALUE;
        for (int k = j; k > 0; k--) {
            double h = (double) (costMatrix[i][j - k].getSimilarity() + getPenalityGap(k));
            if (h > max) {
                max = h;
            }
        }
        return max;
    }
    
   /**
    * Returns the number of queries successfully aligned in the subsequence that
    * ends in the alignment point
    * @return 
    */
    public int getBestSubsequenceLength(){
        CellInfoEditDistance endPoint = new CellInfoEditDistance(Integer.MIN_VALUE, 0, 0, Generics.EditDistanceOperatorType.NOOPERATION, 0);
        int topRow = 0, topColumn = 0;
        for(int i=1; i<row; i++){
            for(int j=1; j<column; j++){
                //Search for the highest similarity with a MATCH_MISMATCH operation
                if(costMatrix[i][j].getSimilarity() >= endPoint.getSimilarity() && costMatrix[i][j].getOperator().equals(Generics.EditDistanceOperatorType.MATCH_MISMATCH)) {
                    endPoint = new CellInfoEditDistance(costMatrix[i][j].getSimilarity(), i, j, 
                            Generics.EditDistanceOperatorType.NOOPERATION, costMatrix[i][j].getQuerySimilarity());
                    topRow = i;
                    topColumn = j;
                }
            }
        }
        
        boolean next = true;
        int length = 0;
        while(next){
            //Browse back the costMatrix
            switch(costMatrix[topRow][topColumn].getOperator()){
                case MATCH_MISMATCH:
                    topRow--;
                    topColumn--;
                    length++;
                    break;
                case INSERTION: 
                    topRow--;
                    break;
                case DELETION: 
                    topColumn--;
                    break;
                case STOP:
                    next = false;
            }
        }
        return length;
    }
    
    /**
     * Returns the CellInfoEditDistance corresponding to the first query in
     * the subsequence that ends in the alignment point
     * @return 
     */
    public CellInfoEditDistance getFirstMatchingQueryInBestSubsequence(){
        CellInfoEditDistance startPoint = new CellInfoEditDistance(Integer.MIN_VALUE, 0, 0, Generics.EditDistanceOperatorType.NOOPERATION, 0);
        int topRow = 0, topColumn = 0;
        for(int i=1; i<row; i++){
            for(int j=1; j<column; j++){
                //Search for the highest similarity with a MATCH_MISMATCH operation
                if(costMatrix[i][j].getSimilarity() >= startPoint.getSimilarity() && costMatrix[i][j].getOperator().equals(Generics.EditDistanceOperatorType.MATCH_MISMATCH)) {
                    startPoint = new CellInfoEditDistance(costMatrix[i][j].getSimilarity(), i, j, 
                            Generics.EditDistanceOperatorType.NOOPERATION, costMatrix[i][j].getQuerySimilarity());
                    topRow = i;
                    topColumn = j;
                }
            }
        }
        
        boolean next = true;
        int length = 0;
        while(next){
            //Browse back the costMatrix
            switch(costMatrix[topRow][topColumn].getOperator()){
                case MATCH_MISMATCH:
                    if(length>0)
                        startPoint = new CellInfoEditDistance(costMatrix[topRow][topColumn].getSimilarity(), topRow, topColumn, 
                                Generics.EditDistanceOperatorType.NOOPERATION, costMatrix[topRow][topColumn].getQuerySimilarity());
                    topRow--;
                    topColumn--;
                    length++;
                    break;
                case INSERTION: 
                    topRow--;
                    break;
                case DELETION: 
                    topColumn--;
                    break;
                case STOP:
                    next = false;
            }
        }
        return startPoint;
    }
}
