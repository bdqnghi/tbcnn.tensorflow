import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
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

/**
 * This is the main class which initiates everything
 */
public class MatrixMultiplication {

    public static final String MATRIX_A_ID = "A";
    public static final String MATRIX_B_ID = "B";

    public static void main(String[] args) throws Exception {

        if(args.length != 1){
            System.out.println("Wrong inputs");
            return;
        }

        //read configs for the test
        File configFile = new File("Configs/"+args[0]);
        BufferedReader b = new BufferedReader(new FileReader(configFile));
        String configLine;
        if ((configLine = b.readLine()) == null){
            System.out.println("Could not read the configurations");
            return;
        }

        String[] configs = configLine.split(",");
        if(configs.length != 3){
            System.out.println("Config file content is invalid");
            return;
        }


        //Create a new configuration object to pass the configs to hadoop nodes
        Configuration conf = new Configuration();
        // m and n denotes the dimensions of matrix A.
        // m = number of rows
        // n = number of columns
        conf.set("m", configs[0]); //2
        conf.set("n", configs[1]); //5
        // n and p denotes the dimensions of matrix B
        // n = number of rows
        // p = number of columns
        conf.set("p", configs[2]); //3

        conf.set("s", configs[0]); // Number of rows in a block in A.
        conf.set("t", configs[1]); // Number of columns in a block in A = number of rows in a block in B.
        conf.set("v", configs[2]); // Number of columns in a block in B.
 
        Job matrixJob = new Job(conf, "Matrix-Multiplication");
        matrixJob.setJarByClass(MatrixMultiplication.class);
        matrixJob.setOutputKeyClass(Text.class);
        matrixJob.setOutputValueClass(Text.class);

        //set the mapper and reducer
        matrixJob.setMapperClass(MatrixMapper.class);
        matrixJob.setReducerClass(MatrixReducer.class);
 
        matrixJob.setInputFormatClass(TextInputFormat.class);
        matrixJob.setOutputFormatClass(TextOutputFormat.class);

        //set where to take the input from
        FileInputFormat.addInputPath(matrixJob, new Path("Input/"+args[0]));
        //set to where to write the output file
        FileOutputFormat.setOutputPath(matrixJob, new Path("Output"));
 
        matrixJob.waitForCompletion(true);
    }

    public static Integer getIntFromString(String input){
        return Integer.parseInt(input);
    }

    public static String getStringFromInteger(Integer input){
        return Integer.toString(input);
    }

    public static Float getFloatFromString(String input){
        return Float.parseFloat(input);
    }
}
