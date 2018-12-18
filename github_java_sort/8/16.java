import java.util.Arrays;
import java.util.Random;

public class quickSort      
{    
	public static float[] data;
	public static int[] arr;
	public static int sum=0;

    public static void main(String[] args){
        int length, ipivot, iwall, size, L, R;
        float pivot, wall;
        int[] indx;
        
        
        size=100000;
        quickSort.data = getArray(size);  
        quickSort.arr = getArr(size);

        System.out.println(Arrays.toString(quickSort.data));
        
        length=getLength(quickSort.data);         
        ipivot=length-1;
        pivot=quickSort.data[ipivot];        
        iwall=0;
        wall=quickSort.data[iwall];        
        L=iwall;
        R=ipivot;
        compareArray(pivot, wall, L, R, iwall);

        while(true){        	
        	
        	indx = searchArr(); 
            
            
            ipivot=indx[1];
            pivot=quickSort.data[ipivot];        
            iwall=indx[0];
            wall=quickSort.data[iwall];        
            L=iwall;
            R=ipivot;
            compareArray(pivot, wall, L, R, iwall);

            
        	if(quickSort.sum==quickSort.arr.length){
        		break;
        	}
        	
        	}

        System.out.println(Arrays.toString(quickSort.data));           
    }    
    
    static float[] getArray(int size){ 
    	
        Random r = new Random();    	
    	float[] floats = new float[size];
        for (int i = 0; i < floats.length; i++) {
            floats[i] = r.nextFloat();
          }
        return floats;    	
    }
    
    static int[] getArr(int size){ 
    	
    	int[] ints = new int[size];
        for (int i = 0; i < ints.length; i++) {
            ints[i] = 0;
          }
        return ints;    	
    } 
  
    static int[] searchArr(){ 

        int[] indx = new int[2];
        int diff;
        
        
        for (int i = 0; i < quickSort.arr.length; i++) {      	
        	if(quickSort.arr[i]==0){        		
        		indx[0]=i;
        		break;        			
        	}     				
     	}
    	
        
        for (int i = indx[0]+1; i < quickSort.arr.length; i++) {   
        	if(quickSort.arr[i]==1){        		
        		indx[1]=i-1;
        		break;        			
        	}  
        	else if(i==(quickSort.arr.length-1) && quickSort.arr[i]==0){        		
        		indx[1]=i;
        		break;        			
        	} 
     	}
        
        diff=indx[1]-indx[0];
        if(diff==0){
        	quickSort.arr[indx[0]]=1;
        }
        
        return indx;    	
    } 
    
    static int getLength(float[] arr){    	
    	return arr.length;    	
    }
    
    static void compareArray(float pivot, float wall, int L, int R, int iwall){
        
    	for (int i = L; i <= R; i++) {
     		if(quickSort.data[i]<pivot){
     			quickSort.data[iwall]=quickSort.data[i];
     			quickSort.data[i]=wall;
     			iwall++;
     			wall=quickSort.data[iwall];			
     		}
     		else if(i==R){
     			quickSort.data[iwall]=quickSort.data[i];
     			quickSort.data[i]=wall;
     			wall=quickSort.data[iwall];
     		}
            
     	}
    	    	
    	
    	quickSort.arr[iwall]=1;
    	quickSort.sum+=1;
    	 	     	
    }
    
}