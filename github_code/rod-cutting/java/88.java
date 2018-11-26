import java.io.*;
import java.util.*;
import java.text.*;
import java.math.*;
import java.util.regex.*;

public class RodCutting {
    /*
 * Complete the function below.
 */

    static int rodCutting(int[] iArray) {
        int rodLength = iArray.length;
        
        


    }
    
    
    static int getMaxPrice(int n, int[] iArray){
        
        if(n==0) return 0;
        if(n==1) return iArray[0];
        int max =Integer.MIN_VALUE;
        for(int i=1; i<=n; i++){
            int temp = getMaxPrice(n-i, iArray)+getMaxPrice(i, iArray)
            if(temp>max){
                max=temp;
            }
        }
        freturn max;
        
    }
    
    
    

    public static void main(String[] args) throws IOException{
        Scanner in = new Scanner(System.in);
        final String fileName = System.getenv("OUTPUT_PATH");
        BufferedWriter bw = new BufferedWriter(new FileWriter(fileName));
        int res;
        
        int _iArray_size = 0;
        _iArray_size = Integer.parseInt(in.nextLine());
        int[] _iArray = new int[_iArray_size];
        int _iArray_item;
        for(int _iArray_i = 0; _iArray_i < _iArray_size; _iArray_i++) {
            _iArray_item = Integer.parseInt(in.nextLine());
            _iArray[_iArray_i] = _iArray_item;
        }
        
        res = rodCutting(_iArray);
        bw.write(String.valueOf(res));
        bw.newLine();
        
        bw.close();
    }
}