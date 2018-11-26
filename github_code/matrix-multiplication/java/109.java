import java.io.IOException;
import java.util.*;
import java.util.AbstractMap.SimpleEntry;
import java.util.Map.Entry;

import org.apache.hadoop.fs.Path;
import org.apache.hadoop.conf.*;
import org.apache.hadoop.io.*;
import org.apache.hadoop.mapreduce.*;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.input.TextInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;
import org.apache.hadoop.mapreduce.lib.output.TextOutputFormat;

public class MatrixMapper extends Mapper<LongWritable, Text, Text, Text> {
    
    public void map(LongWritable key, Text value, Context context) throws IOException, InterruptedException {
        Configuration conf = context.getConfiguration();
        /*
         * Row column count
         */
        int aMatrixRows = MatrixMultiplication.getIntFromString(conf.get("m"));
        int bMatrixColumns = MatrixMultiplication.getIntFromString(conf.get("p"));

        int s = MatrixMultiplication.getIntFromString(conf.get("s")); // Number of rows in a block in A.
        int t = MatrixMultiplication.getIntFromString(conf.get("t")); // Number of columns in a block in A = number of rows in a block in B.
        int v = MatrixMultiplication.getIntFromString(conf.get("v")); // Number of columns in a block in B.

        int mPerS = aMatrixRows/s; // Number of blocks in each column of A.
        int pPerV = bMatrixColumns/v; // Number of blocks in each row of B.

        //represents a line from the input file
        String inputLine = value.toString();
        String[] matrixData = inputLine.split(",");
        Text outputKey = new Text();
        Text outputValue = new Text();

        //if this is of the first matrix
        if (matrixData[0].equals(MatrixMultiplication.MATRIX_A_ID)) {
            //i,j are row and column values
            int i = MatrixMultiplication.getIntFromString(matrixData[1]);
            int j = MatrixMultiplication.getIntFromString(matrixData[2]);
            //for each entry generate the duplicated entries so that they can distributed in the nodes for the reducer step
            for (int index = 0; index < pPerV; index++) {
                outputKey.set(MatrixMultiplication.getStringFromInteger(i/s) + "," + MatrixMultiplication.getStringFromInteger(j/t) + "," + MatrixMultiplication.getStringFromInteger(index));
                outputValue.set(MatrixMultiplication.MATRIX_A_ID+"," + MatrixMultiplication.getStringFromInteger(i%s) + "," + MatrixMultiplication.getStringFromInteger(j%t) + "," + matrixData[3]);
                context.write(outputKey, outputValue);
            }
        } else {
            int j = MatrixMultiplication.getIntFromString(matrixData[1]);
            int k = MatrixMultiplication.getIntFromString(matrixData[2]);
            for (int index = 0; index < mPerS; index++) {
                outputKey.set(MatrixMultiplication.getStringFromInteger(index) + "," + MatrixMultiplication.getStringFromInteger(j/t) + "," + MatrixMultiplication.getStringFromInteger(k/v));
                outputValue.set(MatrixMultiplication.MATRIX_B_ID+"," + MatrixMultiplication.getStringFromInteger(j%t) + "," + MatrixMultiplication.getStringFromInteger(k%v) + "," + matrixData[3]);
                context.write(outputKey, outputValue);
            }
        }
    }

}