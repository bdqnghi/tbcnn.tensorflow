import java.io.IOException;

import org.apache.hadoop.io.Text;

import org.apache.hadoop.mapred.JobConf;
import org.apache.hadoop.mapred.MapReduceBase;
import org.apache.hadoop.mapred.Mapper;
import org.apache.hadoop.mapred.OutputCollector;
import org.apache.hadoop.mapred.Reporter;

public class MatrixMultiplicationOneMapper extends MapReduceBase implements Mapper<Text, Text, Text, Text>
{
  private String matrixName = "";
  private long   count      = 0;

  @Override
  public void map(Text key, Text value, OutputCollector<Text, Text> output, Reporter reporter) throws IOException
  {
    String [] values = value.toString().trim().split(" ");
    if (matrixName.equalsIgnoreCase(MatrixMultiplicationOneDriver.MATRIX_NAME_M))
    {
      String i = key.toString();
      for (int j = 0; j < values.length; j++)
      {
        for (int k = 0; k < count; k++)
        {
          output.collect(new Text(i + MatrixMultiplicationOneDriver.SEPARATOR + Integer.toString(k)), 
              new Text(matrixName + MatrixMultiplicationOneDriver.SEPARATOR + j + MatrixMultiplicationOneDriver.SEPARATOR + values[j]));
        }
      }
    }
    else
    {
      String j = key.toString();
      for (int k = 0; k < values.length; k++)
      {
        for (int i = 0; i < count; i++)
        {
          output.collect(new Text(Integer.toString(i) + MatrixMultiplicationOneDriver.SEPARATOR + Integer.toString(k)), 
              new Text(matrixName + MatrixMultiplicationOneDriver.SEPARATOR + j + MatrixMultiplicationOneDriver.SEPARATOR + values[k]));
        }
      }
    }
  }

  @Override
  public void configure(JobConf conf)
  {
    String[] fileNameTokens = conf.get("map.input.file", "XYZ").split("/");
    matrixName = fileNameTokens[fileNameTokens.length - 1].substring(0, 1);
    if (matrixName.equalsIgnoreCase(MatrixMultiplicationOneDriver.MATRIX_NAME_M))
    {
      count = conf.getInt(MatrixMultiplicationOneDriver.COLUMN_COUNTERS
          + MatrixMultiplicationOneDriver.SEPARATOR + MatrixMultiplicationOneDriver.MATRIX_NAME_N, 0);
    }
    else
    {
      count = conf.getInt(MatrixMultiplicationOneDriver.ROW_COUNTERS
          + MatrixMultiplicationOneDriver.SEPARATOR + MatrixMultiplicationOneDriver.MATRIX_NAME_M, 0);
    }
  }
}
