package com.dennisjonsson.visualization.test;

import com.dennisjonsson.annotation.VisualClass;
import com.dennisjonsson.annotation.Visualize;
import com.dennisjonsson.annotation.markup.AbstractType;
import java.util.Arrays;


public class QuickSortVisual{
public static com.dennisjonsson.annotation.log.ast.ASTLogger logger = 
com.dennisjonsson.annotation.log.ast.ASTLogger.instance(new com.dennisjonsson.annotation.log.ast.SourceHeader("QuickSortVisual",new String [] { "package com.dennisjonsson.visualization.test;","","import com.dennisjonsson.annotation.VisualClass;","import com.dennisjonsson.annotation.Visualize;","import com.dennisjonsson.annotation.markup.AbstractType;","import java.util.Arrays;","","@VisualClass","public class QuickSort {","","    public static void sort(int[] array) {","        quickSort(array, 0, array.length - 1);","    }","","    public static void quickSort(@Visualize(abstractType = 'array') int[] arr, int low, int high) {","        if (arr == null || arr.length == 0)","            return;","        if (low >= high)","            return;","        int middle = low + (high - low) / 2;","        int pivot = arr[middle];","        int i = low, j = high;","        while (i <= j) {","            while (arr[i] < pivot) {","                i++;","            }","            while (arr[j] > pivot) {","                j--;","            }","            if (i <= j) {","                int temp = arr[i];","                arr[i] = arr[j];","                arr[j] = temp;","                i++;","                j--;","            }","        }","        if (low < j)","            quickSort(arr, low, j);","        if (high > i)","            quickSort(arr, i, high);","    }","}"},"",new com.dennisjonsson.annotation.markup.DataStructure [] {  com.dennisjonsson.annotation.markup.DataStructureFactory.getDataStructure("array","int[]","com.dennisjonsson.visualization.test.QuickSort quickSort arr")},new com.dennisjonsson.visualization.test.app.MyInterpreter(),"C:.Users.dennis.Documents.NetBeansProjects.annotation-test"));

    public static void sort(int[] array) {
        quickSort(eval("com.dennisjonsson.visualization.test.QuickSort quickSort arr", write(null, array, 3, 1), 3, new int[] { 14, 14 }), 0, array.length - 1);
    }

    public static void quickSort( int[] arr, int low, int high) {
        if (arr == null || arr.length == 0)
            return;
        if (low >= high)
            return;
        int middle = low + (high - low) / 2;
        int pivot = eval("pivot", write("com.dennisjonsson.visualization.test.QuickSort quickSort arr", arr[read("com.dennisjonsson.visualization.test.QuickSort quickSort arr", 0, middle)], 0, 1), 0, new int[] { 23, 23 });
        int i = low, j = high;
        while (i <= j) {
            while (eval(null, arr[read("com.dennisjonsson.visualization.test.QuickSort quickSort arr", 0, i)], 2, new int[] { 26, 26 }) < pivot) {
                i++;
            }
            while (eval(null, arr[read("com.dennisjonsson.visualization.test.QuickSort quickSort arr", 0, j)], 2, new int[] { 29, 29 }) > pivot) {
                j--;
            }
            if (i <= j) {
                int temp = eval("temp", write("com.dennisjonsson.visualization.test.QuickSort quickSort arr", arr[read("com.dennisjonsson.visualization.test.QuickSort quickSort arr", 0, i)], 0, 1), 0, new int[] { 33, 33 });
                eval("com.dennisjonsson.visualization.test.QuickSort quickSort arr", arr[read("com.dennisjonsson.visualization.test.QuickSort quickSort arr", 0, i)] = write("com.dennisjonsson.visualization.test.QuickSort quickSort arr", arr[read("com.dennisjonsson.visualization.test.QuickSort quickSort arr", 0, j)], 0, 0), 0, new int[] { 34, 34 });
                eval("com.dennisjonsson.visualization.test.QuickSort quickSort arr", arr[read("com.dennisjonsson.visualization.test.QuickSort quickSort arr", 0, j)] = write("temp", temp, 1, 0), 0, new int[] { 35, 35 });
                i++;
                j--;
            }
        }
        if (low < j)
            quickSort(eval("com.dennisjonsson.visualization.test.QuickSort quickSort arr", write("com.dennisjonsson.visualization.test.QuickSort quickSort arr", arr, 1, 1), 3, new int[] { 41, 41 }), low, j);
        if (high > i)
            quickSort(eval("com.dennisjonsson.visualization.test.QuickSort quickSort arr", write("com.dennisjonsson.visualization.test.QuickSort quickSort arr", arr, 1, 1), 3, new int[] { 43, 43 }), i, high);
    }

public static int eval( String targetId, int value, int expressionType, int [] line){
logger.eval("QuickSortVisual", targetId, value, expressionType, line);
return value;
}
public static int write(String name, int value, int sourceType, int targetType ){
logger.write("QuickSortVisual", name, value, sourceType, targetType);
return value;
}
public static int[] eval( String targetId, int[] value, int expressionType, int [] line){
logger.eval("QuickSortVisual", targetId, java.util.Arrays.copyOf(value,value.length), expressionType, line);
return value;
}
public static int[] write(String name, int[] value, int sourceType, int targetType ){
logger.write("QuickSortVisual", name, java.util.Arrays.copyOf(value,value.length), sourceType, targetType);
return value;
}
public static int[][] eval( String targetId, int[][] value, int expressionType, int [] line){
logger.eval("QuickSortVisual", targetId, new com.dennisjonsson.annotation.log.ast.LogUtils<int[][]>().deepCopy(value), expressionType, line);
return value;
}
public static int[][] write(String name, int[][] value, int sourceType, int targetType ){
logger.write("QuickSortVisual", name, new com.dennisjonsson.annotation.log.ast.LogUtils<int[][]>().deepCopy(value), sourceType, targetType);
return value;
}
public static int read(String name,int dimension, int index ){ 
logger.read("QuickSortVisual", name ,index ,dimension);
return index; 
}
}
